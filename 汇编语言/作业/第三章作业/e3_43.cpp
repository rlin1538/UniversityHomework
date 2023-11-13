#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    char buff[100] = "";
    int len = 0;
    char leng[10] = "";
    scanf("%s", buff);

    _asm {
        LEA EDI, buff
        XOR ECX, ECX
        XOR AL, AL
        DEC EDI
    COUNT:
        INC EDI
        CMP AL, [EDI]
        LOOPNE COUNT
        NOT ECX
        MOV EAX, ECX
        LEA ESI, leng
        MOV ECX, 3 //位数
        MOV EBX, 10
            NEXT:
        XOR EDX,EDX
        DIV EBX
        ADD DL,'0'
        MOV [ESI + ECX-1],DL
        LOOP NEXT
        MOV BYTE PTR[ESI+3],0
    }

    printf("length=%s\n", leng);
    return 0;
}