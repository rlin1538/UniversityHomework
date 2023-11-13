#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    char s[4];
    unsigned short a, b;
    unsigned int c;
    for (int i = 0; i < 4; i++)
    {
        scanf("%c", &s[i]);
    }
    _asm {
        LEA EAX, s
        MOV BX, [EAX]
        MOV a, BX
        MOV BX, WORD PTR[EAX + 2]
        MOV b, BX
        MOV EBX, DWORD PTR[EAX]
        MOV c, EBX
    }

    //printf("%s", s);
    printf("a=%u, b=%u, c=%u\n", a, b, c);
    return 0;
}