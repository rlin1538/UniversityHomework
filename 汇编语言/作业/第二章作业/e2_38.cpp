#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    char s[20] = { 'a','b','c','d','a','b','c','d','a','b','c','d','a','b','c','d','a','b','c','d', };
    int sum1 = 0;
    int sum2 = 0;
    
    _asm {
        LEA EAX, s
        MOV EDX, -1
        MOV ECX, 0
        PT1:
            INC EDX
        PT2:
            CMP ECX, 10
            JE PT3
            MOV BX, WORD PTR[EAX + 2 * ECX]
            INC ECX
            CMP BX, 0
            JA PT1
            JMP PT2
            ;
        PT3:
            MOV sum1, EDX
        MOV EDX, -1
        MOV ECX, 0
        PT4 :
            INC EDX
        PT5 :
            CMP ECX, 5
            JE PT6
            MOV EBX, DWORD PTR[EAX + 4 * ECX]
            INC ECX
            CMP EBX, 0
            JB PT4
            JMP PT5
            ;
        PT6:
            MOV sum2, EDX

        //MOV ECX [EAX]
        //MOV c, ECX
    }

    //printf("%s", s);
    printf("sum1=%d\nsum2=%d", sum1,sum2);
    return 0;
}