#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    char buff[100] = "";
    int ans = 0;
    printf("输入包含数字的字符串:");
    scanf("%s", buff);

    _asm {
        PUSH ESI
        LEA ESI,buff
        PUSH EBX
        XOR EBX,EBX
    LAB0:
        XOR EDX,EDX     //单个数累计
        XOR EAX,EAX     //一位
    LAB1:
        CMP [ESI],0     //结束判断
        JE NEXT
        CMP [ESI],'9'   //非数字判断
        JG NEXT
        CMP [ESI],47
        JLE NEXT
        IMUL EDX,10
        MOV AL,[ESI]
        AND AL,15
        ADD EDX,EAX
        INC ESI
        JMP LAB1
    NEXT:
        INC ESI
        ADD EBX,EDX
        CMP[ESI], 0     //结束判断
        JE LAB_END
        JMP LAB0
    LAB_END:
        MOV ans,EBX
        POP EBX
        POP ESI
    }

    printf("和为：%d\n", ans);
    return 0;
}