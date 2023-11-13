#include<iostream>
#include<string.h>
#define MAX_SIZE 256
using namespace std;


char flag[12];
int p=0,symbol,sum,num;
char *keyword[6]={"do","while","if","then","begin","end"};

 void sc(char string[])
{
	char x;

	for(int i=0;i<12;i++)
	{
		flag[i]=NULL;
	}
	x=string[p];
	p++;
	while(x==' ')
	{
		x=string[p];
		p++;
	}
	if((x>='a' and x<='z') or (x>='A' and x<='Z'))
	{
		int num=0;
		while((x>='a' and x<='z') or (x>='A' and x<='Z') or (x>='0' and x<='9'))
		{
			flag[num]=x;
			num++;
			x=string[p];
			p++;		
		}
		flag[num]='\0';
		p--;
		symbol=7;
		for(int i=0;i<6;i++)
		{
			if(strcmp(flag,keyword[i])==0)
			{
				symbol=i+1;
				break;
			}
		}
	}
	else if((x>='0' and x<='9'))
    {
        {
            sum=0;
            while((x>='0' and x<='9'))
            {
                sum=sum*10 + x-'0';
                x=string[p];
                p++;
            }
        }
        p--;
        symbol=8;
    }
    else switch(x)
    {
        case'<':
			num=0;
			flag[num]=x;
			num++;
            x=string[p];
            p++;
            if(x=='>')
            {
                symbol=9;
                flag[num++]=x;
            }
            else if(x=='=')
            {
                symbol=10;
                flag[num++]=x;
            }
            else
            {
                symbol=11;
                p--;
            }
            break;
        case'>':
			num=0;
			flag[num]=x;
			num++;
            x=string[p];
            p++;
            if(x=='=')
            {
                symbol=12;
                flag[num]=x;
                num++;
            }
            else
            {
                symbol=13;
                p--;
            }
            break;
        case':':
			num=0;
			flag[num]=x;
			num++;
            x=string[p];
            p++;
            if(x=='=')
            {
                symbol=14;
                flag[num]=x;
                num++;
            }
            else
            {
                symbol=15;
                p--;
            }
            break;
        case'*':
			symbol=16;
			flag[0]=x;
			break;
        case'/':
			symbol=17;
			flag[0]=x;
			break;
        case'+':
			symbol=18;
			flag[0]=x;
			break;
        case'-':
			symbol=19;
			flag[0]=x;
			break;
        case'=':
			symbol=20;
			flag[0]=x;
			break;
        case';':
			symbol=21;
			flag[0]=x;
			break;
        case'(':
			symbol=22;
			flag[0]=x;
			break;
        case')':
			symbol=23;
			flag[0]=x;
			break;
        case'#':
			symbol=0;
			flag[0]=x;
			break;
        default: 
			symbol=-1;
			break;
    }
}



int main()
{
	char a;
	char string[MAX_SIZE];
	int strlen=0;
	for(int i=0;i<MAX_SIZE;i++)
		string[i]=NULL;
	do
	{
		cin.get(a);
		string[strlen]=a;
		strlen++;
	}
	while(a!='#');
	do{
		sc(string);
		switch(symbol)
        {
        case 8:
        	printf("<%d,%d>\n",symbol,sum);
        	break;
        case -1:
        	printf("Error!\n");
        	break;
        default:
        	printf("<%d,%s>\n",symbol, flag);
        	break;
        }
	}

	while(symbol!=0);
 } 

