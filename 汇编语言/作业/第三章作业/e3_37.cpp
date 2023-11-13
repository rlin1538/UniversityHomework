#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    int a, b;
    printf("输入两个数：");
    scanf("%d %d", &a, &b);

    _asm {
        MOV EAX, a
        MOV EBX, b

        CMP EAX, 0
        JG LAB_1
        NEG EAX
     LAB_1:
        CMP EBX, 0
        JG LAB_2
        NEG EBX
     LAB_2:
        MOV CX, AX
        MOV DX, BX
        AND EAX, 4294901760
        AND EBX, 4294901760
        MOV AX, DX
        MOV BX, CX
        MOV ECX, EAX
        MOV EAX, EBX
        MOV EBX, ECX
        MOV a, EAX
        MOV b, EBX
    }
    printf("a=%x\nb=%x", a,b);
    return 0;
}