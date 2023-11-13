#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    char buff[100] = "";
    char leng[100] = "";
    printf("输入十二进制（大写）:");
    scanf("%s", buff);

    _asm {
        PUSH EDI
        LEA EDI, buff
        XOR EDX, EDX
        XOR EAX, EAX
        DEC EDI
    COUNT :
        INC EDI
        CMP [EDI], 0
        JE END_COUNT
        MOV AL, [EDI]
        SUB AL, '0'
        CMP AL, 9
        JLE NEXT_ONE
        SUB AL, 7
    NEXT_ONE:
        IMUL EDX, 12
        ADD EDX, EAX
        CMP [EDI], 0
        LOOPNE COUNT
    END_COUNT:
        MOV EAX, EDX
        PUSH ESI
        LEA ESI, leng
        MOV ECX, 10 //位数
        PUSH EBX
        MOV EBX, 13
    NEXT:
        XOR EDX, EDX
        DIV EBX
        ADD DL, '0'
        CMP DL, '9'
        JLE NEXT_NUM
        ADD DL, 7
    NEXT_NUM:
        MOV[ESI + ECX - 1], DL
        LOOP NEXT
        MOV BYTE PTR[ESI + 10], 0
        POP EBX
        POP ESI
        POP EDI
    }

    printf("十三进制=%s\n", leng);
    return 0;
}