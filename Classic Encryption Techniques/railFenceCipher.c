/***********************************
        INCLUDE
************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
/***********************************
        Declare Functions
************************************/
void Encryption_railFence(char *text, int key); // 암호화 함수
void Decryption_railFence(char *text, int key); // 복호화 함수

/***********************************
        Main Function
************************************/
int main()
{
    char text[64];
    int select=0, key=0;
 
    while(1)
    {
        printf("암호는 1번, 복호는 2번 선택: ");
        scanf("%d", &select);
        if(select != 1|2)
            printf("다시 입력해주세요.\n");
        else
            break;
        while(getchar() != '\n');
    }

    printf("Rail의 개수: ");
    scanf("%d", &key);
    
    if(select==1){
        printf("평문 입력: ");
        scanf("%s", text);
    }
    else if(select==2){
        printf("암호문 입력: ");
        scanf("%s", text);
    }
    else
    ;

    if(select==1){
        Encryption_railFence(text, key);
    }
    else if(select==2){
        Decryption_railFence(text, key);
    }
    else
    ;
 
    return 0;
}


/***********************************
        Define Functions
************************************/

void Encryption_railFence(char *text, int key)  // 암호화 함수
{ 
    int i, j, k = -1, row = 0, col = 0;
    int textLength = strlen(text);
    char railMatrix[key][textLength];   //rail을 이차원 배열로 구현
 
    for(i = 0; i < key; ++i)
        for(j = 0; j < textLength; ++j)
            railMatrix[i][j] = '\n';
 
    for(i = 0; i < textLength; ++i){
        railMatrix[row][col++] = text[i];
 
        if(row == 0 || row == key-1)
            k= k * (-1);
 
        row = row + k;
    }
 
    printf("\n암호화된 결과 출력: ");
 
    for(i = 0; i < key; ++i)
        for(j = 0; j < textLength; ++j)
            if(railMatrix[i][j] != '\n')
                printf("%c", railMatrix[i][j]);

    printf("\n");
}
 
void Decryption_railFence(char *text, int key){
    int i, j, k = -1, row = 0, col = 0, m = 0;
    int textLength = strlen(text);
    char railMatrix[key][textLength];
 
    for(i = 0; i < key; ++i)
        for(j = 0; j < textLength; ++j)
            railMatrix[i][j] = '\n';
 
    for(i = 0; i < textLength; ++i){
        railMatrix[row][col++] = '*';
 
        if(row == 0 || row == key-1)
            k= k * (-1);
 
        row = row + k;
    }
 
    for(i = 0; i < key; ++i)
        for(j = 0; j < textLength; ++j)
            if(railMatrix[i][j] == '*')
                railMatrix[i][j] = text[m++];
 
    row = col = 0;
    k = -1;
 
    printf("\n암호화된 결과 출력: ");
 
    for(i = 0; i < textLength; ++i){
        printf("%c", railMatrix[row][col++]);
 
        if(row == 0 || row == key-1)
            k= k * (-1);
 
        row = row + k;
    }

    printf("\n");
}