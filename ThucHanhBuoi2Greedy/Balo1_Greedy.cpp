#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float KL;
    float GT;
    int PA;
    float DG;
    char ten[20];
}DoVat;

DoVat* readFile(int *n, int *W){
    DoVat* dsdv = (DoVat*)malloc(sizeof(DoVat));
    int i = 0;
    FILE *f = fopen("CaiBalo1.txt", "r");
    if(f == NULL){
        printf("Khong the mo file");
        *W = 0;
    }
    else{
        printf("Mo file thanh cong\n");
        fscanf(f, "%d", W);
        while(!feof(f)){
            fscanf(f, "%f %f %[^\n]", &dsdv[i].KL, &dsdv[i].GT, &dsdv[i].ten);
            dsdv[i].DG = dsdv[i].GT/ dsdv[i].KL;
            dsdv[i].PA = 0;
            i++;
            dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
        }
    }
    *n = i;
    return dsdv;
}

void inDS(DoVat* dsdv, int n, float TGT, float TKL){
    printf("==============================================\n");
    printf("|%-20s|%-5s|%-5s|%-5s|%-5s|\n", "TEN DO VAT", "KL", "GT", "DG", "PA");
    for(int i = 0; i<n; i++){
        printf("|%-20s|%-5.2f|%-5.2f|%-5.2f|%-5d|\n", dsdv[i].ten, dsdv[i].KL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
    }
    printf("==============================================\n");
    printf("Tong khoi luong: %.2f\n", TKL);
    printf("Tong gia tri: %.2f\n", TGT);
    printf("==============================================\n");
}

void InsertionSort(DoVat *dsdv, int n){
    for(int i = 0; i<n-1; i++){
        int j = i+1;
        while(j > 0 && dsdv[j].DG > dsdv[j-1].DG){
            DoVat temp = dsdv[j];
            dsdv[j] = dsdv[j-1];
            dsdv[j-1] = temp;
            j--;
        }
    }
}

void Greedy(int n, int W, DoVat *dsdv, float *TGT, float *TKL){
    int i = 0;
    while(W > 0 && i < n){
        int temp  = W/dsdv[i].KL;    
        dsdv[i].PA = temp;
        *TGT += temp*dsdv[i].GT;
        *TKL += temp*dsdv[i].KL;
        W -= temp*dsdv[i].KL;
        i++;
    }
}

int main(){
    int n, W;
    DoVat *dsdv;
    float TKL = 0, TGT = 0;
    dsdv = readFile(&n, &W);
    inDS(dsdv, n, TGT, TKL);
    InsertionSort(dsdv, n);
    printf("DANH SACH DO VAT SAU KHI DA SAP XEP\n");
    inDS(dsdv, n, TGT, TKL);
    Greedy(n, W, dsdv, &TGT, &TKL);
    printf("PHUONG AN TIM DUOC BANG THUAT TOAN THAM AN\n");
    inDS(dsdv, n, TGT, TKL);
    free(dsdv);
    return 0;
}
