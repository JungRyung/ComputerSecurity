/***********************************
		INCLUDE
************************************/
#include <stdio.h>
#include <string.h>

/***********************************
		Declare Functions
************************************/
void Encryption_AffineCipher(char *str, int key1, int key2);
void Decryption_AffineCipher(char *str, int key1, int key2);

/***********************************
		Main Function
************************************/
int main(){
	int key1=0, key2=0;
	int encryptFlag = 0;
	char str[50]={0,};

	printf("평문 또는 암호문을 입력하시오: ");
	gets(str);

	printf("암호는 1번, 복호는 2번 선택: ");
	scanf("%d",&encryptFlag);

	printf("키 값을 두개 입력하시오: ");
	scanf("%d %d",&key1,&key2);


	if(encryptFlag == 1)		//암호화 작업
	{
		Encryption_AffineCipher(str, key1, key2);	//암호화 함수
	}
	else if(encryptFlag == 2)	//복호화 작업
	{
		Decryption_AffineCipher(str, key1, key2);	//복호화 함수
	}else
	;

	return 0;
}


/***********************************
		Define Functions
************************************/

void Encryption_AffineCipher(char *str, int key1, int key2)	// 암호화 함수
{
	int i=0;
	int str_size=strlen(str);

	for(i=0; i<str_size; i++)	
	{
		if((str[i]>='A')&&(str[i]<='Z'))	// 대문자일 경우
		{
			str[i]-='A';
			if((key1*str[i]+key2)<0)	
			{
				str[i]+=26;
			}

			str[i]=(key1*str[i]+key2)%26;	// affine cryptosystem 적용하여 암호화
			str[i]+='A';
		}else if((str[i]>='a')&&(str[i]<='z'))	// 소문자일 경우
		{
			str[i]-='a';

			if((key1*str[i]+key2)<0)
			{
				str[i]+=26;
			}

			str[i]=(key1*str[i]+key2)%26;	// affine cryptosystem 적용하여 암호화
			str[i]+='a';
		}
		else
			;
	}	

	printf("\n암호화된 결과 출력: ");
	puts(str);
}

void Decryption_AffineCipher(char *str, int key1, int key2)	// 복호화 함수
{
	int i=0;
	int key1_inv=0;
	int str_size=strlen(str);

	while(1)	//복호화 할 때 필요한 key1의 inverse key를 생성
	{
		key1_inv++;
		if((key1*key1_inv)%26==1)	//key1에 곱한값에 26을 mod했을 경우 1이 되는 값을 탐색
		{
			break;
		}
	}

	for(i=0; i<str_size; i++)
	{
		if((str[i]>='A')&&(str[i]<='Z'))	// 대문자일 경우
		{
			str[i]-='A';
			if(key1_inv*(str[i]-key2)<0)
			{
				str[i]+=26;
			}

			str[i]=(key1_inv*(str[i]-key2))%26;	// inverse key를 이용하여 복호화
			str[i]+='A';
		}else if((str[i]>='a')&&(str[i]<='z'))	// 소문자일 경우
		{
			str[i]-='a';

			if(key1_inv*(str[i]-key2)<0)
			{
				str[i]+=26;
			}

			str[i]=key1_inv*(str[i]-key2)%26;	// inverse key를 이용하여 복호화
			str[i]+='a';
		}
		else
		;
	}	

	printf("\n복호화된 결과 출력: ");
	puts(str);

	return 0;
}