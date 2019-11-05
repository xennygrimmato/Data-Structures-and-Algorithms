#include<stdio.h>
#include<conio.h>
#include<string.h>
void TOH(int n,char s,char d,char i)
{
	if(n==1)
	{
		printf("Move %d from %c to %c\n",n,s,d);
	}
	else
	{
		TOH(n-1,s,i,d);
		printf("Move %d from %c to %c\n",n,s,d);
		TOH(n-1,i,d,s);
	}
}
void main()
{
	int n;
	printf("Enter the number of discs:\n");
	scanf("%d",&n);
	TOH(n,'s','d','i');
	
}
