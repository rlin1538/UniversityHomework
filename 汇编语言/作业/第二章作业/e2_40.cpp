#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    int s[13] = { 2,3,4,5,6,7,8,9,10,11,12,13,14 };
    unsigned int ans;
    
    _asm {
        LEA EBX, s
        MOV ECX, 0
        MOV EDX, 0
        MOV ESI, 0

     PT1:
        MOV EAX, [EBX + ESI * 4]
        TEST AL, 01H
        JZ PTOU
        ADD ECX, EAX
        JMP PT2
     PTOU:
        ADD EDX, EAX
     PT2:
        INC ESI
        CMP ESI, 13
        JNZ PT1
        SUB ECX, EDX
        CMP ECX, 0
        JGE PT3
        NEG ECX
     PT3:
        MOV ans, ECX

    }

    //printf("%s", s);
    printf("ans=%u\n", ans);
    return 0;
}