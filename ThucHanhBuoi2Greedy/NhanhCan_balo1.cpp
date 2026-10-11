#include <stdio.h>
#include <stdlib.h>
typedef struct{
    float DG, KL, GT;
    char ten[25];
    int PA;
}DoVat;

DoVat *readFile(int *n, float *W){
    FILE *f = fopen("CaiBalo1.txt", "r");
    DoVat *dsdv = (DoVat*)malloc(sizeof(DoVat));
    int i = 0;
    if(f == NULL){
        *W = 0;
        printf("Khong the mo file\n");
    }
    else{
        printf("Dang doc file....\n");
        fscanf(f, "%f", W);
        while(!feof(f)){
            fscanf(f, "%f %f %[^\n]", &dsdv[i].KL, &dsdv[i].GT, &dsdv[i].ten);
            dsdv[i].PA = 0;
            dsdv[i].DG = dsdv[i].GT/dsdv[i].KL;
            i++;
            dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat) * (i+1));
        }
    }
    *n = i;
    fclose(f);
    return dsdv;
}

// TGT
// TL Con lai
//Can tren

void swap(DoVat *dv1, DoVat* dv2){
    DoVat temp = *dv1;
    *dv1 = *dv2;
    *dv2 = temp;
}

void InsertionSort(DoVat* dsdv, int n){
    for(int i = 0; i<n-1; i++){
        int j = i+1;
        while(j > 0 && dsdv[j].DG > dsdv[j-1].DG){
            swap(&dsdv[j], &dsdv[j-1]);
            j--;
        }
    }
}

void CreateRoot(float *V, float *TGT, float *CT, float W, float DGMax, float *GTLNTT){
    *TGT = 0;
    *V =  W;
    *CT = (*V) * DGMax;
    *GTLNTT = 0;
}

void InDS(DoVat* dsdv, int n){
    printf("-------------------------------------------\n");
    printf("|%-20s|%-5s|%-5s|%-4s|%-3s|\n", "Ten", "KL", "GT", "DG", "PA");
    printf("-------------------------------------------\n");
    for(int i = 0; i<n; i++){
        printf("|%-20s|%-5.2f|%-5.2f|%-4.2f|%-3d|\n", dsdv[i].ten, dsdv[i].KL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
    }
    printf("-------------------------------------------\n");
}
//GTLNTT
//TGT
//CT
//Trong luong con lai: V
void Cap_Nhat_PA(int PATT[], DoVat* dsdv, int n, float *GTLNTT, float TGT){
    if(TGT > *GTLNTT){
        *GTLNTT = TGT;
        for(int i = 0; i<n; i++){
            dsdv[i].PA = PATT[i];
        }
    }
}



void NhanhCan(DoVat *dsdv, int n, int STTDV, int PATT[], float *V, float *TGT, float *CT, float *GTLNTT){
    int j;
    int PAmax = *V/dsdv[STTDV].KL;
    for(j = PAmax; j>=0; j--){
        *TGT = *TGT + j* dsdv[STTDV].GT;
        *V = *V - j*dsdv[STTDV].KL;

        if(STTDV == n-1){     //da di den do vat cuoi cung
            PATT[STTDV] = j;
            Cap_Nhat_PA(PATT, dsdv, n, GTLNTT, *TGT);
        }
        else{                            
            *CT = *TGT + (*V) * dsdv[STTDV+1].DG;
            if(*CT > *GTLNTT){
                PATT[STTDV] = j;
                NhanhCan(dsdv, n, STTDV + 1, PATT, V, TGT, CT, GTLNTT);
            }
        }

        //Backtracking
        PATT[STTDV] = 0;
        *TGT = *TGT - j* dsdv[STTDV].GT;
        *V = *V + j*dsdv[STTDV].KL;
    }
}


int main(){
    int n;
    float W;
    DoVat* dsdv = readFile(&n, &W);
    float V, TGT, GTLNTT, CT;
    InsertionSort(dsdv, n);
    InDS(dsdv, n);
    int *PATT = (int*)malloc(sizeof(int) * n);
    CreateRoot(&V, &TGT, &CT,  W, dsdv[0].DG, &GTLNTT);
    NhanhCan(dsdv, n, 0, PATT, &V, &TGT, &CT, &GTLNTT);
    printf("Phuong an toi uu:\n");
    InDS(dsdv, n);
    free(dsdv);
    free(PATT);
    return 0;
}
