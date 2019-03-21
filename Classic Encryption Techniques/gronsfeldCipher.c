/***********************************
		INCLUDE
************************************/
#include <stdio.h>
#include <string.h>

/***********************************
		Declare Functions
************************************/
void Encryption_gronsfeld(char *str, char *key);	//암호화 함수
void Decryption_gronsfeld(char *str, char *key);	//복호화 함수

/***********************************
		Main Function
************************************/
int main()
{
	int i=0, select=1;
	char str[50]={0,}, key[16]={0,};

	printf("암호문 또는 평문을 입력: ");
	gets(str);
	printf("암호는 1번, 복호는 2번 선택: ");
	scanf("%d", &select);
	getchar();
	printf("키 값 입력: ");
	gets(key);


	if(select==1)		// 암호화
	{
		Encryption_gronsfeld(str, key);	//암호화 함수
	}
	else if(select==2)	// 복호화
	{
		Decryption_gronsfeld(str, key);	//복호화 함수
	}
	else
		;

	return 0;
}

/***********************************
		Define Functions
************************************/

void Encryption_gronsfeld(char *str, char *key)	// 암호화 함수
{
	int i=0, j=0;
	int str_size=strlen(str);
	int Key_Size=strlen(key);

	for(i=0; i<str_size; i++){
		j=i%Key_Size;

		if((str[i]>='a')&&(str[i]<='z'))	// 소문자일 경우
		{
			str[i]-='a';	key[j]-='0';		// key값(숫자)은 ASCII코드 48번 부터 시작하기 때문에 48을 빼준다
			if((str[i]+key[j])<0)
			{
				str[i]+=26;
			}
			str[i]=(str[i]+key[j])%26;
			str[i]+='a';	key[j]+='0';
		}
		else if((str[i]>='A')&&(str[i]<='Z'))	// 대문자일 경우
		{
			str[i]-='A';	key[j]-='0';		// 대문자의 경우도 동일하게 key값에 48을 빼준다
			if((str[i]+key[j])<0)
			{
				str[i]+=26;
			}
			str[i]=(str[i]+key[j])%26;
			str[i]+='A';	key[j]+='0';
		}
	}

	printf("\n암호화된 결과 출력: ");
	puts(str);
}
void Decryption_gronsfeld(char *str, char *key)	// 복호화 함수
{
	int i=0, j=0;
	int str_size=strlen(str);
	int Key_Size=strlen(key);

	for(i=0; i<str_size; i++)
	{
		j=i%Key_Size;

		if((str[i]>='a')&&(str[i]<='z'))	// 소문자일 경우
		{
			str[i]-='a';	key[j]-='0';		// key값(숫자)은 ASCII코드 48번 부터 시작하기 때문에 48을 빼준다
			if((str[i]-key[j])<0)
			{
				str[i]+=26;
			}
			str[i]=(str[i]-key[j])%26;
			str[i]+='a';	key[j]+='0';
		}
		else if((str[i]>='A')&&(str[i]<='Z'))	// 대문자일 경우
		{
			str[i]-='A';	key[j]-='0';		// 대문자의 경우도 동일하게 key값에 48을 빼준다
			if((str[i]-key[j])<0)
			{
				str[i]+=26;
			}
			str[i]=(str[i]-key[j])%26;
			str[i]+='A';	key[j]+='0';
		}
	}
	
	printf("\n복호화된 결과 출력: ");
	puts(str);
}