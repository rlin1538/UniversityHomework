#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    char str[512] = "";
    int num_posi,num_ou;
    printf("输入一行字符串:\n");
    gets_s(str);

    _asm {
        LEA ESI, str
        XOR ECX,ECX
        XOR EDX,EDX
        XOR EBX,EBX
    NEXT:
        LODSB
        CMP AL, 0
        JE END
        TEST AL, 1
        SETZ BL
        ADD EDX, EBX
        RCL AL,1
        SETNC BL
        ADD ECX, EBX
        JMP NEXT
    END:
        MOV num_posi, ECX
        MOV num_ou, EDX
    }

    printf("正数字符：%d\n偶数字符：%d",num_posi,num_ou);
    return 0;

}