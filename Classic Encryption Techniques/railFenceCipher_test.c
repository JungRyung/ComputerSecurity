/***********************************
        INCLUDE
************************************/
#include<stdio.h>
#include<string.h>
 
/***********************************
        Declare Functions
************************************/
void Encryption_railFence(char *text, int key);
void Decryption_railFence(char *text, int key);

/***********************************
        Main Function
************************************/
int main(){
    char text[64];
    int select=0, key=0;
 
    printf("암호는 1번, 복호는 2번 선택: ");
    scanf("%d", &select);

    printf("Rail의 개수: ");
    scanf("%d", &key);
    
    if(select==1){
        printf("평문입력: ");
        scanf("%s", text);
    }
    else if(select==2){
        printf("암호문 입력: ");
        scanf("%s", text);
    }
    else
    ;

    if(select==1)       // 암호화 부분
    {  
        Encryption_railFence(text, key);
    }
    else if(select==2)  // 복호화 부분
    {
        Decryption_railFence(text, key);
    }
    else
    ;
 
    return 0;
}


/***********************************
        Define Functions
************************************/

void Encryption_railFence(char *text, int key){
    int i, j, k = -1, row = 0, col = 0;
    int textLength = strlen(text);
    char railMatrix[key][textLength];
 
    for(i = 0; i < key; ++i)            // 평문을 나누어 담을 배열에 공백을 삽입
        for(j = 0; j < textLength; ++j)
            railMatrix[i][j] = '\n';
 
    for(i = 0; i < textLength; ++i)     // 해당 평문을 지그재그 형태로 railMatrix에 담는다
    {    
        railMatrix[row][col++] = text[i];
 
        if(row == 0 || row == key-1)    // row값이 0에 도달했을 경우에는 row값이 다시 증가하도록, row값이 최대에 도달했을 겨우에는row값이 다시 감소하도록 설정한다
            k= k * (-1);
 
        row = row + k;                  // row값이 계속 증가하거나 감소하도록 하는 부분
    }
 
    printf("\n암호화된 결과 출력: ");
 
    for(i = 0; i < key; ++i)
        for(j = 0; j < textLength; ++j) // 암호문을 row순서대로 출력한다
            if(railMatrix[i][j] != '\n')    
                printf("%c", railMatrix[i][j]); // 공백이 아닌경우만 출력한다

    printf("\n");
}
 
void Decryption_railFence(char *text, int key){
    int i, j, k = -1, row = 0, col = 0, m = 0;
    int textLength = strlen(text);
    char railMatrix[key][textLength];
 
    for(i = 0; i < key; ++i)            // 암호문을 나누어 담을 배열에 공백을 삽입
        for(j = 0; j < textLength; ++j)
            railMatrix[i][j] = '\n';
 
    for(i = 0; i < textLength; ++i){    // 지그재그 형태로 암호문이 실제로 들어오는 부분에 임의의 문자 *를 삽입
        railMatrix[row][col++] = '*';
 
        if(row == 0 || row == key-1)    // row값이 0에 도달했을 경우에는 row값이 다시 증가하도록, row값이 최대에 도달했을 경우에는row값이 다시 감소하도록 설정한다
            k= k * (-1);
 
        row = row + k;
    }
 
    for(i = 0; i < key; ++i)            // 임의의 문자 *에 암호문을 나누어 담아서 암호화 할 때 생성했던 railMatrix를 복원한다.
        for(j = 0; j < textLength; ++j)
            if(railMatrix[i][j] == '*')
                railMatrix[i][j] = text[m++];
 
    row = col = 0;
    k = -1;
 
    printf("\n암호화된 결과 출력: ");
 
    for(i = 0; i < textLength; ++i){    // railMatrix를 지그재그형태로 출력해서 평문으로 복원한다.
        printf("%c", railMatrix[row][col++]);
 
        if(row == 0 || row == key-1)
            k= k * (-1);
 
        row = row + k;
    }

    printf("\n");
}