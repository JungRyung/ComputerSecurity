#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showByteBit(unsigned char *input, int stringSize);

int main()
{
	unsigned char testChar = 0x26;
	unsigned char plus = 0x02;
	unsigned char mask = 0x80;
	unsigned char testString[8] = {'a','b','c','d','e','f','g','h'};
	unsigned int testUINT = 0x01;

	int i,j;

	printf("testChar : %c\n",testChar );

	testChar=testChar+plus;

	printf("increased testChar : %c\n",testChar );
	
	printf("shifted testChar : %c\n",testChar<<1);

	printf("{\n");
	for(i=0 ;i<8 ;i++)
	{
		if(i == 7)
		{
			if(testChar&(mask>>i))
				printf("1\n");
			else
				printf("0\n");
		}
		else
		{
			if(testChar&(mask>>i))
				printf("1 ,");
			else
				printf("0 ,");
		}
	}
	printf("{\n");


	showByteBit(testString, 8);

	printf("testUINT : %u\n",testUINT );
	testUINT|= 0x02;
	printf("added testUINT : %u\n", testUINT);
		

	return 0;
}

void showByteBit(unsigned char *input, int stringSize)
{
	int i,j;
	unsigned char mask = 0x80;

	printf("{\n");
	for(i=0 ; i<stringSize ; i++)
	{
		for(j=0 ; j<8 ; j++)
		{
			if(j == 7)
			{
				if(input[i]&(mask>>j))
					printf("1\n");
				else
					printf("0\n");
			}
			else
			{
				if(input[i]&(mask>>j))
					printf("1 ,");
				else
					printf("0 ,");
			}
		}
		
	}
	printf("{\n");
}