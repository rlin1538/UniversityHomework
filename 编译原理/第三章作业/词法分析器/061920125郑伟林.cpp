//061920125郑伟林

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* keyword[] = {"void", "int", "float", "char", "if", "else",
                "while", "do", "return", "main","switch","case",
                "default","double","struct","break","long","enum",
                "typedef","union","unsigned","short","continue"};
int keywordNum = 23;
int line = 1;
int errorNum = 0;
char ch;
char word[20];
int errorLine[50];

//去除空行
void removeEmpty(FILE *fpr, FILE *fpw) 
{
    char buf[1024];
    while (!feof(fpr))
    {
        fgets(buf, 1024, fpr);
        if (buf[0] != '\n')
        {
            fputs(buf, fpw);
        }
    }
}
//去除注释
void removeNote(FILE *fpr, FILE *fpw) 
{
    char ch;
    ch = fgetc(fpr);

    if (ch == '/') //处理单行注释
    {
        while (ch != '\n')
        {
            ch = fgetc(fpr);
        }
        fseek(fpr, -1, 1);
    }
    else if (ch == '*') //处理多行注释
    {
        ch = fgetc(fpr);
        while (ch != '*' && (fgetc(fpr) != '/'))
        {
            fseek(fpr, -1, 1);
            fgetc(fpr);
            if (fgetc(fpr) == EOF) //如果缺少注释结束则报错
            {
                printf("LexicalError,");
                fprintf(fpw, "LexicalError,");
                break;
            }
        }
        ch = fgetc(fpr);
    }
    else //否则为/界符
    {
        printf("< / >\t"); //6
        fprintf(fpw, "< / >\t");
    }
}
//清除word数组
void clearWord()
{
    for (int i = 0; i < 20; i++)
    {
        word[i] = '\0';
    }
}
//查询保留字
int reserve(char *name)
{
    int i;
    for (i = 0; i < keywordNum; i++)
    {
        if (strcmp(name, keyword[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}
//判断ch是否为字母
bool isLetter(char ch)
{
    // if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    //     return 1;
    // else
    //     return 0;
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? true : false;
}
//判断ch是否为数字
bool isNumber(char ch)
{
    // if (ch >= '0' && ch <= '9')
    //     return 1;
    // else
    //     return 0;
    return (ch >= '0' && ch <= '9') ? true : false;
}
//逐字扫描文件
void scanner(FILE *fpr, FILE *fpw)
{
    while (!feof(fpr))
    {
        int i = 0;
        ch = fgetc(fpr);
        //换行
        if (ch == '\n')
        {
            line++;
            printf("\n");
            fprintf(fpw, "\n");
            ch = fgetc(fpr);
        }
        //空格
        if (ch == ' ')
        {
            while (ch == ' ') //忽略空格
            {
                ch = fgetc(fpr);
            }
        }
        //标识符
        if (isLetter(ch) || (ch == '_'))
        {
            word[i++] = ch;

            ch = fgetc(fpr);
            while (isLetter(ch) || isNumber(ch))
            {
                word[i++] = ch;
                ch = fgetc(fpr);
            }

            int flag = reserve(word);
            if (flag != -1)
            {
                printf("< Keyword: %s >\t", word); //是关键字写入文件output
                fprintf(fpw, "< Keyword: %s >\t", word);
                clearWord();
            }
            else
            {
                printf("< identifier: %s >\t", word); //是标识符，写入文件output
                fprintf(fpw, "< identifier: %s >\t", word);
                clearWord();
            }

            fseek(fpr, -1, 1); //识别标识符/关键字完毕，退回一个字符
        }
        //数
        else if (isNumber(ch))
        {
            word[i++] = ch;

            ch = fgetc(fpr);
            if (ch == '.')
            {
                word[i++] = ch;

                ch = fgetc(fpr);
                while (isNumber(ch))
                {
                    word[i++] = ch;
                    ch = fgetc(fpr);
                }

                printf("< number: %s >\t", word); //浮点数，写入文件
                fprintf(fpw, "< number: %s >\t", word);
                clearWord();
            }
            else if (isLetter(ch))
            {
                printf("LexicalError,");

                errorLine[errorNum++] = line;
                fprintf(fpw, "LexicalError,");

                while (isLetter(ch))
                    ch = fgetc(fpr);

                clearWord();
            }
            else
            {
                while (isNumber(ch))
                {
                    word[i++] = ch;
                    ch = fgetc(fpr);
                }

                printf("< number:%s >\t", word); //是整数，将（2，word）写入output文件
                fprintf(fpw, "< number:%s >\t", word);
                clearWord();
            }

            fseek(fpr, -1, 1);
        }
        //其它情况
        else
        {
            switch (ch)
            {
            case '+':
                printf("< + >\t"); //3
                fprintf(fpw, "< + >\t");
                break;
            case '-':
                word[i++] = ch;

                ch = fgetc(fpr);
                if (isNumber(ch))
                {
                    while (isNumber(ch))
                    {
                        word[i++] = ch;
                        ch = fgetc(fpr);
                    }

                    printf("< %s >\t", word); //负数，写入文件
                    fprintf(fpw, "< %s >\t", word);
                    clearWord();
                }

                else
                {
                    printf("< - >\t"); //4
                    fprintf(fpw, "< - >\t");
                }

                fseek(fpr, -1, 1);
                break;
            case '*':
                printf("< * >\t"); //5
                fprintf(fpw, "< * >\t");
                break;
            case '/':
                removeNote(fpr, fpw);
                break;
            case '=':
                ch = fgetc(fpr);
                if (ch == '=')
                {
                    printf("< == >\t"); //12
                    fprintf(fpw, "<,== >\t");
                }
                else
                {
                    fseek(fpr, -1, 1);
                    printf("< = >\t"); //16
                    fprintf(fpw, "< = >\t");
                }
                break;
            case '<':
                ch = fgetc(fpr);
                if (ch == '=')
                {
                    printf("< <= >\t"); //9
                    fprintf(fpw, "< <= >\t");
                }
                else
                {
                    printf("< < >\t"); //8
                    fprintf(fpw, "< < >\t");
                    fseek(fpr, -1, 1);
                }
                break;
            case '>':
                ch = fgetc(fpr);
                if (ch == '=')
                {
                    printf("< >= >\t"); //11
                    fprintf(fpw, "< >= >\t");
                }
                else
                {
                    printf("< > >\t"); //10
                    fprintf(fpw, "< > >\t");
                    fseek(fpr, -1, 1);
                }
                break;
            case '!':
                ch = fgetc(fpr);
                if (ch == '=')
                {
                    printf("< != >\t"); //13
                    fprintf(fpw, "< != >\t");
                }
                else
                {
                    fseek(fpr, -1, 1);
                }
                break;
            case '&':
                ch = fgetc(fpr);
                if (ch == '&')
                {
                    printf("< && >\t"); //14
                    fprintf(fpw, "< && >\t");
                }
                else
                {
                    fseek(fpr, -1, 1);
                }
                break;
            case '|':
                ch = fgetc(fpr);
                if (ch == '|')
                {
                    printf("< || >\t"); //15
                    fprintf(fpw, "< || >\t");
                }
                else
                {
                    fseek(fpr, -1, 1);
                }
                break;
            case '(':
                printf("< ( >\t"); //17
                fprintf(fpw, "< ( >\t");
                break;
            case ')':
                printf("< ) >\t"); //18
                fprintf(fpw, "< ) >\t");
                break;
            case '[':
                printf("< [ >\t"); //19
                fprintf(fpw, "< [ >\t");
                break;
            case ']':
                printf("< ] >\t"); //20
                fprintf(fpw, "< ] >\t");
                break;
            case '{':
                printf("< { >\t"); //21
                fprintf(fpw, "< { >\t");
                break;
            case '}':
                printf("< } >\t"); //22
                fprintf(fpw, "< } >\t");
                break;
            case ';':
                printf("< ; >\t"); //23
                fprintf(fpw, "< ; >\t");
                break;
            case ',':
                printf("< , >\t"); //24
                fprintf(fpw, "< , >\t");
                break;
                /*    default:
                    //错误
                printf("< error>");*/
            }
        }
    }
}

int main()
{
    char Filename[20];
    FILE *fpr, *fpw;

    printf("Input file name:");
    scanf("%s", Filename);
    fpr = fopen(Filename, "r");

    FILE *fpr1 = fopen("code.txt", "w");
    removeEmpty(fpr, fpr1);
    fclose(fpr1); //临时存放处理过空行的代码

    FILE *fpr2 = fopen("code.txt", "r");

    //printf("请输入写出文件地址：");
    //scanf("%s", Filename);
    fpw = fopen("decode.txt", "w");

    scanner(fpr2, fpw);

    printf("\nline: %d\n", line);

    if (errorNum > 0)
    {
        fprintf(fpw, "\nLexical error on line: ");
        printf("\nLexical error on line: ");
        for (int i = 0; i < errorNum; i++)
        {
            fprintf(fpw, "%d,", errorLine[i]);
            printf("%d,", errorLine[i]);
        }
    }

    return 0;
}