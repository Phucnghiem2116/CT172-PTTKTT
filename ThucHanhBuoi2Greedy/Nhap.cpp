#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef struct {
    float trongLuong;
    int dau, cuoi;
} Canh;

void hoanDoi(Canh *a, Canh *b) {
    Canh temp = *a;
    *a = *b;
    *b = temp;
}

void sapXepTheoTrongLuong(Canh *dsCanh, int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(dsCanh[i].trongLuong > dsCanh[j].trongLuong)
                hoanDoi(&dsCanh[i], &dsCanh[j]);
        }
    }
}

void docFile(Canh **dsCanh, int *soDinh) {    
    FILE *f = fopen("TSP.txt", "r");
    *dsCanh = (Canh*)malloc(sizeof(Canh));
    fscanf(f, "%d", soDinh);    
    int k = 0;
    for(int i = 0; i < *soDinh; i++) {
        for(int j = 0; j < *soDinh; j++) {
            if(j < i) {
                *dsCanh = (Canh*)realloc(*dsCanh, sizeof(Canh)*(k+1));                
                fscanf(f, "%f", &(*dsCanh)[k].trongLuong);
                (*dsCanh)[k].dau = j;
                (*dsCanh)[k].cuoi = i;
                k++;
            } else {
                float temp;
                fscanf(f, "%f", &temp);    
            }
        }    
    }
    fclose(f);
}

void inDanhSachCanh(Canh *dsCanh, int n) {    
    for(int i = 0; i < n; i++) {
        printf("%3d   %c%c   %5.2f\n", i+1, dsCanh[i].dau + 97, dsCanh[i].cuoi + 97, dsCanh[i].trongLuong);
    }
}

void khoiTaoRung(int parent[], int n) {
    for(int i = 0; i < n; i++)
        parent[i] = i;
}

int timGoc(int parent[], int u) {
    while(u != parent[u])
        u = parent[u];
    return u;
}

int coTaoChuTrinh(int gocU, int gocV) {
    return gocU == gocV;
}

int coDinhBaCanh(Canh *tapCanh, int n, Canh canhMoi) {
    int demDau = 1, demCuoi = 1;
    for(int i = 0; i < n; i++) {
        if(tapCanh[i].dau == canhMoi.dau || tapCanh[i].cuoi == canhMoi.dau)
            demDau++;
        if(tapCanh[i].dau == canhMoi.cuoi || tapCanh[i].cuoi == canhMoi.cuoi)
            demCuoi++;
        if(demDau == 3 || demCuoi == 3)
            return 1;
    }
    return 0;
}

void thamLam(Canh *dsCanh, int soDinh, int soCanh) {
    Canh *tapCanhChon;
    float tongTrongLuong = 0;
    tapCanhChon = (Canh*)malloc(sizeof(Canh));
    int parent[MAX_N];
    khoiTaoRung(parent, soDinh);
    int k = 0;

    for(int i = 0; i < soCanh && k < soDinh; i++) {        
        if(!coDinhBaCanh(tapCanhChon, k, dsCanh[i])) {
            int gocU = timGoc(parent, dsCanh[i].dau);
            int gocV = timGoc(parent, dsCanh[i].cuoi);
            if(!coTaoChuTrinh(gocU, gocV) || (coTaoChuTrinh(gocU, gocV) && k == soDinh-1)) {
                tapCanhChon = (Canh*)realloc(tapCanhChon, sizeof(Canh)*(k+1));
                tapCanhChon[k++] = dsCanh[i];
                parent[gocV] = gocU;
                tongTrongLuong += dsCanh[i].trongLuong;
            }
        }
    }

    inDanhSachCanh(tapCanhChon, k);
    printf("Tong do dai cac canh: %.2f\n", tongTrongLuong);
    free(tapCanhChon);
}

int main() {
    int soDinh = 0;
    Canh *dsCanh;
    docFile(&dsCanh, &soDinh);
    int soCanh = soDinh * (soDinh - 1) / 2;

    printf("Cac canh da cho:\n");
    inDanhSachCanh(dsCanh, soCanh);

    sapXepTheoTrongLuong(dsCanh, soCanh);
    printf("\nCac canh sau khi sap xep:\n");    
    inDanhSachCanh(dsCanh, soCanh);    

    printf("\nPhuong an:\n");    
    thamLam(dsCanh, soDinh, soCanh);

    free(dsCanh);
}

