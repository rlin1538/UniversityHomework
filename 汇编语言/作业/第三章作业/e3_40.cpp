#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
    char buff[20] = "";
    scanf("%s", buff);

    _asm {
        LEA ESI, buff
        XOR EDI, EDI
        LAB_FOR:
            MOV AL, [ESI + EDI]
            CMP AL,0
            JE LAB_END
            CMP AL,64   
            JLE LAB_MOVE    //小于A
            CMP AL,122
            JG LAB_MOVE  //大于z
            CMP AL,90
            JLE LAB_NEXT
            CMP AL,96
            JG LAB_NEXT
            LAB_MOVE:
                MOV EBX, EDI
                MOVE:
                MOV CL, [ESI + EBX +1]
                MOV [ESI + EBX], CL
                INC EBX
                CMP [ESI + EBX],0
                JE LAB_FOR
                JMP MOVE
            LAB_NEXT:
                INC EDI
                JMP LAB_FOR

        LAB_END:
    }

    printf("buff=%s\n", buff);
    return 0;
}