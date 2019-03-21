#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;
typedef unsigned int UINT;

void DES_CBC_Enc(*BYTE p_text,*BYTE c_text,*BYTE IV,*BYTE key,*int msg_len);
void DES_CBC_Dec(*BYTE c_text,*BYTE d_text,*BYTE IV,*BYTE key,*int msg_len);


void DES_CBC_Enc(*BYTE p_text,*BYTE c_text,*BYTE IV,*BYTE key,int msg_len)
{
	int i,j;
	int block_count;
	BYTE iv = IV;

	block_count = (msg_len%8)?(msg_len/8+1):(msg_len/8);

	for(i=0; i<block_count; i++)
	{
		for(j=0;j<8;j++)
		{
			p_text[i*8+j] = p_text[i*8+j]^iv[j]; /* 2. 48 bit XOR between p_text and IV: S-box */
		}
		/* DES암호화*/
		DES_Encryption(&p_text[i*8], &c_text[i*8], key);

		iv = c_text[i*8];
	}
}

void DES_CBC_Dec(*BYTE c_text,*BYTE d_text,*BYTE IV,*BYTE key,int msg_len)
{
	int i,j;
	int block_count;

	block_count = (msg_len%8)?(msg_len/8+1):(msg_len/8);

	for(i=0; i<block_count; i++)
	{
		if(i==0)
		{
			DES_Decryption(&c_text[i*8], &d_text[i*8], key);
			for(j=0;j<8;j++)
			{
				d_text[i*8+j] = d_text[i*8+j]^IV[j]; 
			} 
		}
		else
		{
			DES_Decryption(&c_text[i*8], &d_text[i*8], key);
			for(j=0;j<8;j++)
			{
				d_text[i*8+j] = d_text[i*8+j]^c_text[(i-1)*8+j]; 
			} 
		}
	}
}

void DES_CFB_Enc(*BYTE p_text,*BYTE c_text,*BYTE IV,*BYTE key,int msg_len)
{
	int i,j;
	int block_count;
	BYTE iv = IV;
	BYTE encryptedIV[9] = {0,};

	block_count = (msg_len%8)?(msg_len/8+1):(msg_len/8);

	for(i=0; i<block_count; i++)
	{
		DES_Encryption(iv,encryptedIV,key);
		for(j=0; j<8; j++)
		{
			c_text[i*8+j] = p_text[i*8+j]^encryptedIV[j];
			iv[j] = c_text[i*8+j];
		}
	}	
}

void DES_CFB_Dec(*BYTE c_text,*BYTE d_text,*BYTE IV,*BYTE key,int msg_len)
{
	int i,j;
	int block_count;
	BYTE iv = IV;
	BYTE encryptedIV[9] = {0,};

	block_count = (msg_len%8)?(msg_len/8+1):(msg_len/8);

	for(i=0; i<block_count; i++)
	{
		DES_Encryption(iv,encryptedIV,key);
		for(j=0; j<8; j++)
		{
			d_text[i*8+j] = c_text[i*8+j]^encryptedIV[j];
		}
	}
}