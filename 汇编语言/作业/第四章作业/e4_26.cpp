#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    char str[512] = "";
    int len;
    printf("输入一行字符串:\n");
    gets_s(str);

    _asm {
        LEA ESI, str
        XOR EAX,EAX
        XOR EBX,EBX
        XOR EDX,EDX
    NEXT_ONE:
        LODSB
        CMP AL, 0
        JE END
        MOV ECX, 7
    NEXT:
        CMP ECX, -1
        JLE NEXT_ONE
        BT EAX,ECX
        JC JUDGE
        INC EBX
        JMP DEC_ONE
    JUDGE:
        CMP EBX,EDX
        JLE CLEAR
        MOV EDX,EBX
    CLEAR:
        XOR EBX,EBX
    DEC_ONE:
        DEC ECX
        JMP NEXT
    END:
        CMP EBX, EDX
        JLE OVER
        MOV EDX, EBX
    OVER:
        MOV len, EDX
    }

    printf("0最多连续个数为：%d", len);
    return 0;
    
}