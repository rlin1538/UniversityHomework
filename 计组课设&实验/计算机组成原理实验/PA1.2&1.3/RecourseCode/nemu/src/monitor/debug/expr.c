#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>

enum
{
  TK_NOTYPE = 256,
  TK_EQ,
  TK_NUM,
  TK_DNUM, //负号
  TK_REG,
  DEREF,
  TK_UEQ,
  TK_OR,
  TK_AND,

  /* TODO: Add more token types */

};

static struct rule
{
  char *regex;
  int token_type;
} rules[] = {

    /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

    {" +", TK_NOTYPE},                 // spaces
    {"0x[a-fA-F0-9]+|[0-9]+", TK_NUM}, // number
    {"\\$[a-z]{2,3}", TK_REG},         //register
    {"\\(", '('},                      //left parenthese
    {"\\)", ')'},                      //right parenthese
    {"\\*", '*'},                      // multiply
    {"\\/", '/'},                      // divide
    {"\\+", '+'},                      // plus
    {"\\-", '-'},                      // reduce
    {"==", TK_EQ},                     // equal
    {"!=", TK_UEQ},
    {"&&", TK_AND},
    {"\\|\\|", TK_OR},
    {"!", '!'},
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]))

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i++)
  {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0)
    {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token
{
  int type;
  char *str;
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e)
{
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0')
  {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i++)
    {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
      {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);
        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type)
        {
        case TK_NOTYPE:
          break;
        default:
          tokens[nr_token].type = rules[i].token_type;
          // if (substr_len >= 32)
          if (tokens[nr_token].str)
            free(tokens[nr_token].str);
          tokens[nr_token].str = (char *)malloc(sizeof(char) * substr_len + 1);
          strncpy(tokens[nr_token].str, substr_start, substr_len);
          tokens[nr_token].str[substr_len] = '\0';
          nr_token++; //记录已识别信息
        }

        break;
      }
    }

    if (i == NR_REGEX)
    {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

uint32_t find_dominated_op(int p, int q, bool *success)
{
  //忽略括号中的运算符，然后对外层所有运算符判断优先级，选最低的最右侧运算符
  int posOfPlusOrReduce = -1;
  int posOfMultiplyOrDivide = -1;
  int posOfEqOrUeq = -1;
  int posOfAnd = -1;
  int posOfOr = -1;
  int numOfParenthese = 0;
  *success = true;

  for (int i = p; i <= q; i++)
  {
    switch (tokens[i].type)
    {
    case '(':
      numOfParenthese++;
      continue;
    case ')':
      numOfParenthese--;
      continue;
    }
    if (numOfParenthese == 0)
    {
      switch (tokens[i].type)
      {
      case '-':
      case '+':
        posOfPlusOrReduce = i;
        break;
      case '*':
      case '/':
        posOfMultiplyOrDivide = i;
        break;
      case TK_EQ:
      case TK_UEQ:
        posOfEqOrUeq = i;
        break;
      case TK_AND:
        posOfAnd = i;
        break;
      case TK_OR:
        posOfOr = i;
        break;

      default:
        break;
      }
    }
  }

  if (posOfPlusOrReduce == -1 && posOfMultiplyOrDivide == -1 && posOfEqOrUeq == -1 && posOfAnd == -1 && posOfOr == -1)
  {
    *success = false;
    return -1;
  }

  if (posOfOr != -1)
    return posOfOr;
  else if (posOfAnd != -1)
    return posOfAnd;
  else if (posOfEqOrUeq != -1)
    return posOfEqOrUeq;
  else if (posOfPlusOrReduce != -1)
    return posOfPlusOrReduce;
  else
    return posOfMultiplyOrDivide;
}

bool check_parentheses(int p, int q)
{
  if (strcmp(tokens[p].str, "(") != 0 || strcmp(tokens[q].str, ")") != 0)
    return false;

  int k = p + 1;
  int ps = 0;
  char *s;
  s = (char *)malloc(nr_token * (sizeof(char)));
  while (k < q)
  {
    switch (tokens[k].type)
    {
    case '(':
      s[ps++] = '(';
      break;
    case ')':
      ps--;
      if (ps < 0)
        return false;
      break;

    default:
      break;
    }
    k++;
  }
  if (ps == 0)
    return true;
  else
    return false;
}

uint32_t eval(int p, int q)
{
  if (p > q)
  {
    /* Bad expression */
    assert(0);
  }
  else if (p == q)
  {
    /* Single token.
        * For now this token should be a number.
        * Return the value of the number.
        */
    if (tokens[p].type == TK_REG)
    {
      for (int i = 0; i < 8; i++)
      {
        if (strcmp(tokens[p].str + 1, regsl[i]) == 0)
          return cpu.gpr[i]._32;
        if (strcmp(tokens[p].str + 1, regsw[i]) == 0)
          return cpu.gpr[i]._16;
        if (strcmp(tokens[p].str + 1, regsb[i]) == 0)
          return reg_b(i);
      }
      if (strcmp(tokens[p].str + 1, "eip") == 0)
        return cpu.eip;
      printf("%s is not exist!\n", tokens[p].str);
      assert(0);
    }

    uint32_t radix = 1, num = 0;
    if (tokens[p].str[0] == '0' && tokens[p].str[1] == 'x') //Hex number
    {
      for (int i = strlen(tokens[p].str) - 1; i > 1; i--)
      {
        if (tokens[p].str[i] >= '0' && tokens[p].str[i] <= '9')
          num += radix * (tokens[p].str[i] - '0');
        else
          num += radix * (tokens[p].str[i] - 'a' + 10);
        radix *= 16;
      }
    }
    else
    {
      for (int i = strlen(tokens[p].str) - 1; i >= 0; i--)
      {
        num += radix * (tokens[p].str[i] - '0');
        radix *= 10;
      }
    }
    if (tokens[p].type == TK_DNUM)
      num = 0 - num;
    if (tokens[p].type == DEREF)
      return vaddr_read(num, 4);
    return num;
  }
  else if (check_parentheses(p, q) == true)
  {
    /* The expression is surrounded by a matched pair of parentheses.
        * If that is the case, just throw away the parentheses.
        */
    return eval(p + 1, q - 1);
  }
  else
  {
    bool isSuccess;

    switch (tokens[p].type)
    {
    case TK_DNUM:
      return 0 - eval(p + 1, q);
    case DEREF:
      return vaddr_read(eval(p + 1, q), 4);
    case '!':
      return !(eval(p + 1, q));
    default:
      break;
    }
    uint32_t op = find_dominated_op(p, q, &isSuccess);
    if (!isSuccess)
      assert(0);
    uint32_t val1 = eval(p, op - 1);
    uint32_t val2 = eval(op + 1, q);
    switch (tokens[op].type)
    {
    case '+':
      return val1 + val2;
    case '-':
      return val1 - val2;
    case '*':
      return val1 * val2;
    case '/':
      return val1 / val2;
    case TK_EQ:
      return (val1 == val2);
    case TK_UEQ:
      return (val1 != val2);
    case TK_AND:
      return (val1 && val2);
    case TK_OR:
      return (val1 || val2);
    default:
      assert(0);
    }
  }
}

uint32_t expr(char *e, bool *success)
{
  if (!make_token(e))
  {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  for (int i = 0; i < nr_token; i++)
  {
    if (tokens[i].type == '*' && (i == 0 || (tokens[i - 1].type != TK_NUM && tokens[i - 1].type != ')')))
      tokens[i].type = DEREF;
    if (tokens[i].type == '-' && (i == 0 || (tokens[i - 1].type != TK_NUM && tokens[i - 1].type != ')')))
      tokens[i].type = TK_DNUM;
  }
  *success = true;

  return eval(0, nr_token - 1);
}
