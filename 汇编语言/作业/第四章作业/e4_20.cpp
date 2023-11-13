#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    char str_1[100] = "";
    char str_2[100] = "";
    int ans = 0;
    int len;
    printf("输入包含两行字符串:\n");
    gets_s(str_1);
    gets_s(str_2);
    printf("第二行字符数：");
    scanf("%d",&len);

    _asm {
        LEA ESI, str_1
        LEA EDI, str_2
        XOR EBX,EBX
    NEXT_1:
        LODSB
        INC EBX
        CMP AL, 0
        JE NOT_FOUND
        LEA EDI, str_2
        MOV ECX, [len]
    NEXT_2:
        SCASB
        LOOPNE NEXT_2
        JNZ NEXT_1
    FOUND:
        MOV ans, EBX
        JMP OVER
    NOT_FOUND:
        MOV ans, -1
    OVER:
    }

    printf("第一个相同字符位置为：%d\n", ans);
    return 0;
}