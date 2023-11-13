#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    char buff[100] = "";
    char leng[10] = "";
    scanf("%s", buff);

    _asm {
        PUSH EDI
        LEA EDI, buff
        XOR ECX, ECX
        XOR AL, AL
        XOR EDX, EDX
        DEC EDI
    COUNT :
        INC EDI
        CMP [EDI], 97
        JE ADD_ONE
        CMP [EDI], 101
        JE ADD_ONE
        CMP [EDI], 105
        JE ADD_ONE
        CMP [EDI], 111
        JE ADD_ONE
        CMP [EDI], 117
        JE ADD_ONE
        CMP [EDI], 65
        JE ADD_ONE
        CMP [EDI], 69
        JE ADD_ONE
        CMP [EDI], 73
        JE ADD_ONE
        CMP [EDI], 79
        JE ADD_ONE
        CMP [EDI], 85
        JE ADD_ONE
        JMP NEXT_ONE
    ADD_ONE:
        INC EDX
    NEXT_ONE:
        CMP AL, [EDI]
        LOOPNE COUNT
        MOV EAX, EDX
        PUSH ESI
        LEA ESI, leng
        MOV ECX, 3 //位数
        PUSH EBX
        MOV EBX, 8
    NEXT:
        XOR EDX, EDX
        DIV EBX
        ADD DL, '0'
        MOV[ESI + ECX - 1], DL
        LOOP NEXT
        MOV BYTE PTR[ESI + 3], 0
        MOV EAX, ESI
        POP EBX
        POP ESI
        POP EDI
    }

    printf("元音字母个数=%s\n", leng);
    return 0;
}