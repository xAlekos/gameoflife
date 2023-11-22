#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define M 25
#define N 55



struct casella{
    int vive;
    char sprite;
};

typedef struct casella** matrice;

matrice creamatrice(int m, int n){
    matrice b;
    b = (matrice)malloc(M*sizeof(struct casella*));
    for(int i=0;i<M;i++)
        b[i] = (struct casella*) malloc (N*sizeof(struct casella));
    return b;
}

void stampamappa(matrice mappa,int m,int n){
    int i,j;
    printf("\n");
    for(i=0;i<m;i++){
        printf("\t");
        for(j=0;j<n;j++){
            printf("%c",mappa[i][j].sprite);
        }
        printf("\n");
    }
}


void inizializzamappa(matrice mappa,int m,int n){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            mappa[i][j].sprite=' ';
            mappa[i][j].vive=0;
            if(j==0 || j== N-1){
                mappa[i][j].sprite='|';
                mappa[i][j].vive=2;
            }
            if(i==0 || i== M-1){
                mappa[i][j].sprite='-';
                mappa[i][j].vive=2;
            }
        }
    }
    stampamappa(mappa,M,N);
}

void checkvive(matrice mappa, int i,int j){
    int vicini=0;
    if(mappa[i][j].vive==2)
        return;
    if(mappa[i-1][j].sprite=='*')
        vicini+=1;
    if(mappa[i+1][j].sprite=='*')
        vicini+=1;
    if(mappa[i][j+1].sprite=='*')
        vicini+=1;
    if(mappa[i][j-1].sprite=='*')
        vicini+=1;
    if(mappa[i-1][j+1].sprite=='*')
        vicini+=1;
    if(mappa[i-1][j-1].sprite=='*')
        vicini+=1;
     if(mappa[i+1][j+1].sprite=='*')
        vicini+=1;
    if(mappa[i+1][j-1].sprite=='*')
        vicini+=1;
    if(mappa[i][j].sprite=='*'){
        if(vicini<2)
            mappa[i][j].vive=0;
        else if(vicini==2 || vicini == 3)
            mappa[i][j].vive=1;
        else if(vicini>3)
            mappa[i][j].vive=0;
    }
    if(mappa[i][j].sprite==' ' && vicini == 3){
            mappa[i][j].vive=1;
    }
}

void aggiornavive(matrice mappa, int m,int n){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(mappa[i][j].vive!=2)
                checkvive(mappa,i,j);
        }
    }
}

void resetvive(matrice mappa, int m, int n){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(mappa[i][j].vive!=2)
                mappa[i][j].vive=0;
        }
    }
}

void aggiornamappa(matrice mappa, int m, int n){
    int i,j;
    fflush(stdout);
    sleep(1);
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(mappa[i][j].vive==0)
                mappa[i][j].sprite=' ';
            if(mappa[i][j].vive==1)
                mappa[i][j].sprite='*';
        }
    }
    resetvive(mappa,m,n);
    system("clear");
    stampamappa(mappa,m,n);
}

void accendicasella(matrice mappa, int i, int j){
    mappa[i][j].sprite='*';
    system("clear");
    stampamappa(mappa,M,N);
}

void input(matrice mappa){
    int sceltai,sceltaj;
    printf("\nINSERISCI COORD, -1 PER TERMINARE\n");
    do{
        scanf("%d %d",&sceltai,&sceltaj);
        if(sceltai>0 && sceltai<M && sceltaj>0 && sceltaj<N)
            accendicasella(mappa,sceltai,sceltaj);
    }
    while(sceltai!=-1 || sceltaj!=-1);
    
}


int main()
{
    matrice mappa=creamatrice(M,N);
    inizializzamappa(mappa,M,N);
    input(mappa);
    int generazione = 0;
    while(1){
        printf("Generazione : %d\n",generazione++);
        aggiornavive(mappa,M,N);
        aggiornamappa(mappa,M,N);
    }
    return 0;
}
