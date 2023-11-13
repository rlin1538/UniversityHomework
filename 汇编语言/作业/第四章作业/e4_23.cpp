#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    char str_1[512] = "";
    char str_2[16] = "";
    int len;
    printf("输入一行字符串:\n");
    gets_s(str_1);

    _asm {
        LEA EAX, str_1
        LEA EDI, str_2
        PUSH EAX
        CALL STRLEN
        POP ECX
        MOV len, EAX
        PUSH EAX
        CALL NUM_STR
        POP ECX
    }

    printf("长度为：%d\n十六进制长度：%sH", len, str_2);
    return 0;
    _asm {
    STRLEN:
        PUSH EBP
        MOV EBP,ESP
        PUSH EDI
        MOV EDI,[EBP+8]
        XOR AL,AL
        MOV ECX,-1
        REPNZ SCASB
        NOT ECX
        DEC ECX
        MOV EAX, ECX
        POP EDI
        POP EBP
        RET
    }
    _asm{
    NUM_STR:
        PUSH EBP
        MOV EBP, ESP
        MOV EDX, [EBP+8]
        MOV ECX, 8
        PUSH EBX
    NEXT:
        MOV EAX, EDX
        ROR EDX, 4
        AND EAX, 15
        PUSH EAX
        CALL BIT_ASCII
        POP EBX
        MOV BYTE PTR[EDI + ECX - 1], AL
        LOOP NEXT
        
        MOV [EDI+8],0
        POP EBX
        POP EBP
        RET
    }

    _asm {
    BIT_ASCII:
        PUSH EBP
        MOV EBP, ESP
        MOV EAX, [EBP+8]
        ADD EAX, 48
        CMP EAX, 57
        JLE OK
        ADD EAX, 7
    OK:
        POP EBP
        RET
    }
}