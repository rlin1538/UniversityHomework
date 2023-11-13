#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint64_t);

/* We use the `readline' library to provide more flexibility to read from stdin. */
char *rl_gets()
{
  static char *line_read = NULL;

  if (line_read)
  {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read)
  {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args)
{
  cpu_exec(-1);
  return 0;
}

static int cmd_x(char *args)
{
  //分割字符串，得到起始位置和要读取的次数
  char *num = strtok(NULL, " ");
  char *addr_s = strtok(NULL, " ");
  int n = 0, c = 1;
  for (int i = strlen(num) - 1; i >= 0; i--)
  {
    n += (num[i] - '0') * c;
    c *= 10;
  }

  uint32_t dword, temp, addr = 0;
  bool isSuccess=false;
  addr = expr(addr_s, &isSuccess);
  if (!isSuccess)
  {
    printf("Bad Expression!\n");
    return 0;
  }
  /*c=1;
    for (int i = strlen(addr_s)-1; addr_s[i]!='x'; i--)
    {
      if (addr_s[i]>='0' && addr_s[i]<='9')
      {
        addr+=(addr_s[i]-'0')*c;
      }
      else if (addr_s[i]>='a' && addr_s[i]<='f')
      {
        addr+=(addr_s[i]-'a'+10)*c;
      }
      c*=16;
    }*/

  //循环使用 vaddr_read 函数来读取内存
  printf("Address    Dword block ... Byte sequence\n");
  for (int i = 0; i < n; i++)
  {
    uint16_t byte_seq[4] = {0};
    dword = vaddr_read(addr, 4); //如何调用，怎么传递参数，请阅读代码
    temp = dword;
    for (int j = 0; j < 4; j++)
    {
      byte_seq[j] = temp % 256;
      temp /= 256;
    }

    //每次循环将读取到的数据用 printf 打印出来
    printf("0x%08x  0x%08x ... %02x %02x %02x %02x\n",
           addr, dword, byte_seq[0], byte_seq[1], byte_seq[2], byte_seq[3]); //如果你不知道应该打印什么，可以参考参考输出形式
    addr += 4;
  }
  return 0;
}

static int cmd_p(char *args)
{
  bool isSuccess;
  uint32_t ans;

  ans = expr(args, &isSuccess);
  if (isSuccess)
  {
    printf("%d\n", ans);
  }
  else
  {
    printf("Bad Expression!\n");
  }

  return 0;
}

static int cmd_w(char *args)
{
  if (args == NULL)
  {
    printf("Bad Expression!\n");
    return 0;
  }

  set_watchpoint(args);

  return 0;
}

static int cmd_d(char *args)
{
  int t;
  if (args==NULL)
  {
    printf("Please input Watchpoint NO!\n");
    return 0;
  }
  
  sscanf(args,"%d",&t);
  if (!delete_watchpoint(t))
    printf("Can't delete watchpoint %s\n",args);
  else
    printf("Delete watchpoint #%s\n",args);

  return 0;
}

static int cmd_info(char *args)
{
  // 分割字符
  if (strlen(args) != 1 || ((args[0] != 'r') && (args[0] != 'w')))
  {
    printf("Unknown command info '%s'\n", args);
    return 0;
  }
  // 判断子命令是否是r
  if (args[0] == 'r')
  {
    // 依次打印所有寄存器
    // 这里给个例子：打印出 eax 寄存器的值
    for (int i = 0; i < 8; i++)
      printf("%s:\t0x%08x\t%d\n", regsl[i], cpu.gpr[i]._32, cpu.gpr[i]._32);
    for (int i = 0; i < 8; i++)
      printf("%s:\t0x%04x\t%d\n", regsw[i], cpu.gpr[i]._16, cpu.gpr[i]._16);
    for (int i = 0; i < 4; i++)
      printf("%s:\t0x%02x\t%d\t%s:\t0x%02x\t%d\n",
             regsb[i], cpu.gpr[i]._8[0], cpu.gpr[i]._8[0], regsb[i + 4], cpu.gpr[i]._8[1], cpu.gpr[i]._8[1]);

    return 0;
  }
  else if (args[0] == 'w')
  {
    // 这里我们会在 PA1.3 中实现
    list_watchpoint();
  }
  return 0;
}

static int cmd_si(char *args)
{
  if (args == NULL)
  {
    cpu_exec(1);
    return 0;
  }

  if (args[0] == '-')
  {
    if (args[1] == '1' && strlen(args) == 2)
    {
      cpu_exec(-1);
    }
    else
      printf("Unknown comand si '%s'\n", args);
  }
  else
  {
    for (int i = 0; i < strlen(args); i++)
    {
      if (args[i] < '0' || args[i] > '9')
      {
        printf("Unknown command si '%s'\n", args);
        return 0;
      }
    }
    int c = 1;
    int n = 0;
    for (int i = strlen(args) - 1; i >= 0; i--)
    {
      n += (args[i] - '0') * c;
      c *= 10;
    }
    cpu_exec(n);
  }
  return 0;
}
static int cmd_q(char *args)
{
  return -1;
}

static int cmd_help(char *args);

static struct
{
  char *name;
  char *description;
  int (*handler)(char *);
} cmd_table[] = {
    {"help", "Display informations about all supported commands", cmd_help},
    {"c", "Continue the execution of the program", cmd_c},
    {"q", "Exit NEMU", cmd_q},
    {"si", "Single step execution", cmd_si},
    {"info", "info r: Print register status;  info w: Print watchpoint", cmd_info},
    {"x", "Take the EXPR as the starting memory address, output n consecutive 4 bytes in hexadecimal form", cmd_x},
    {"p", "Expression solving", cmd_p},
    {"w", "Add watchpoint",cmd_w},
    {"d","d NO: Delete watchpoint#NO",cmd_d}

    /* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args)
{
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL)
  {
    /* no argument given */
    for (i = 0; i < NR_CMD; i++)
    {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else
  {
    for (i = 0; i < NR_CMD; i++)
    {
      if (strcmp(arg, cmd_table[i].name) == 0)
      {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void ui_mainloop(int is_batch_mode)
{
  if (is_batch_mode)
  {
    cmd_c(NULL);
    return;
  }

  while (1)
  {
    char *str = rl_gets();
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL)
    {
      continue;
    }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end)
    {
      args = NULL;
    }

#ifdef HAS_IOE
    extern void sdl_clear_event_queue(void);
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i++)
    {
      if (strcmp(cmd, cmd_table[i].name) == 0)
      {
        if (cmd_table[i].handler(args) < 0)
        {
          return;
        }
        break;
      }
    }

    if (i == NR_CMD)
    {
      printf("Unknown command '%s'\n", cmd);
    }
  }
}
