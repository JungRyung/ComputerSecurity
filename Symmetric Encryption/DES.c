#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DES.h"

#define BLOCK_SIZE 8
#define DES_ROUND 16

typedef size_t rsize_t;

void DES_Encryption(BYTE *p_text, BYTE *result, BYTE *key);
void DES_Decryption(BYTE *c_text, BYTE *result, BYTE *key);


int i;
int msg_len=0, block_count=0;/*메시지길이와블록수*/

BYTE p_text[128]={0,};/*평문*/
BYTE c_text[128]={0,};/*암호문*/
BYTE d_text[128]={0,};/*복호문*/
BYTE key[9]={0,}; /*비밀키*/

//BYTE *p_text = (BYTE *)malloc(sizeof(BYTE)*128);
//BYTE *c_text = (BYTE *)malloc(sizeof(BYTE)*128);
//BYTE *d_text = (BYTE *)malloc(sizeof(BYTE)*128);
//BYTE *key = (BYTE *)malloc(sizeof(BYTE)*8);

int main()
{
	

	/*평문입력*/
	printf("평문입력: ");
	gets((char *)p_text);
	//getchar();
	/*비밀키입력*/
	printf("비밀키입력: ");
	scanf("%s", key);

	//printf("입력한 64bit KEY :\n");
	//showByteBit(key, 8);

	/*메시지길이와블록수를계산*/
	msg_len=(rsize_t)strlen((char *)p_text);
	block_count=(msg_len%BLOCK_SIZE)?(msg_len/BLOCK_SIZE+1):(msg_len/BLOCK_SIZE);
	//printf("msg_len : %d\n",msg_len);
	//printf("block_count : %d\n",block_count);
	for(i=0; i<block_count; i++)
	{
		/* DES암호화*/
		//printf("p_text[%d] :\n", i*BLOCK_SIZE);
		//showByteBit(key, 8);
		DES_Encryption(&p_text[i*BLOCK_SIZE], &c_text[i*BLOCK_SIZE], key);
	}
	//printf("C_text : \n");
	//showByteBit(c_text, 8);
	/*암호문출력*/
	printf("\n암호문: ");
	for(i=0; i<(block_count*BLOCK_SIZE); i++)
	{
		printf("%c", c_text[i]);
	}
	printf("\n");
	
	for(i=0; i<block_count; i++)
	{
		
		DES_Decryption(&c_text[i*BLOCK_SIZE], &d_text[i*BLOCK_SIZE], key);	//복호화
	}
	printf("\n복호문: ");	//복호문 출력
	for(i=0; i<msg_len; i++)
	{
		printf("%c", d_text[i]);
	}
	printf("\n");
	

	return 0;
}

void DES_Encryption(BYTE *p_text, BYTE *result, BYTE *key)
{
	int i;
	BYTE data[BLOCK_SIZE]={0,};
	BYTE round_key[16][6]={0,};
	UINT L=0, R=0;
	Key_Expansion(key, round_key);/* Round Key생성*/
	IP(p_text, data);/*초기순열*/
	//printf("IP 통과한 평문 :\n");
	//showByteBit(data, 8);
	BtoW(data, &L, &R);/* 64bit블록을32bit로나눔*/
	//printf("BtoW 통과한 L :\n");
	//showUintBit(L, 32);
	//printf("BtoW 통과한 R :\n");
	//showUintBit(R, 32);
	/* DES Round 1~16 */
	for(i=0; i<DES_ROUND; i++)
	{
		L=L^f(R, round_key[i]);

		//printf("Round_%d L : \n", i);
		//showUintBit(L, 32);
		/*
		마지막라운드는Swap을하지않는다.*/
		if(i!=DES_ROUND-1)
		{
			swap(&L, &R);
		}
	}
	/* 32bit
	로나누어진블록을다시64bit 블록으로변환*/
	WtoB(L, R, data);
	IIP(data, result);
	//printf("result : \n");
	//showByteBit(result, 8);



}

void DES_Decryption(BYTE *c_text, BYTE *result, BYTE *key)
{
	int i;
	BYTE data[BLOCK_SIZE]={0,};
	BYTE round_key[16][6]={0,};
	UINT L=0, R=0;
	Key_Expansion(key, round_key);/*라운드키생성*/
	IP(c_text, data);/*초기순열*/
	BtoW(data, &L, &R);/* 64bit블록을32bit로나눔*/
	/* DES Roudn 1~16 */
	for(i=0; i<DES_ROUND; i++)
	{
		/*
		암호화와비교해서라운드키를역순으로적용*/
		L=L^f(R, round_key[DES_ROUND-i-1]);
		/*
		마지막라운드는Swap을하지않는다. */
		if(i!=DES_ROUND-1)
		{
			swap(&L, &R);
		}
	}
	/* 32bit
	로나누어진블록을다시64bit 블록으로변환*/
	WtoB(L, R, data);
	IIP(data, result); /*
	역초기순열*/
}

void 