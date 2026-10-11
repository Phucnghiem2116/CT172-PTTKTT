#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int STT;
    int TL;
    int GT;
    char ten[20];
    int PA;
}DoVat;


DoVat* readFile(int *so_luong_dv, int *tl_balo){
    DoVat* ds = (DoVat*)malloc(sizeof(DoVat));
    FILE* f = fopen("Balo1.txt","r");
    int i = 0;
    if(f == NULL){
        printf("Khong the mo file\n");
        *tl_balo = 0;
    }
    else{
        fscanf(f, "%d", tl_balo);
        while(!feof(f)){
            fscanf(f, "%d %d %[^\n]", &ds[i].TL, &ds[i].GT, &ds[i].ten);
            ds[i].STT = i;
            ds[i].PA = 0;
            i++;
            ds = (DoVat*)realloc(ds, sizeof(DoVat)*(i+1));
        }
    }
    *so_luong_dv = i;
    return ds;
}


//F[k,V]: gia tri tai vi tri thu k,V
//X[k,V]: so luong do vat k khi con V trong balo
void QuyHoachDong(DoVat* ds, int so_luong_dv, int tl_balo, int F[][100], int X[][100]){
    for(int i = 0; i < so_luong_dv; i++){
        for(int j = 0; j<= tl_balo; j++){
            if(i==0){
                X[i][j] = j/ ds[i].TL;
                F[i][j] = X[i][j] * ds[i].GT;
            }
            else{
                int sl_max = j/ds[i].TL;
                int xk = 0;
                int gt_max = F[i-1][j-xk*ds[i].TL] + xk*ds[i].GT;
                for(int sl = 0; sl <= sl_max; sl++){
                    int temp = F[i-1][j - sl*ds[i].TL] + sl*ds[i].GT;
                    if(temp > gt_max){
                        xk = sl;
                        gt_max = temp;
                    }
                }
                F[i][j] = gt_max;
                X[i][j] = xk;
            }
        }
    }
}

void InBang(int F[][100], int X[][100], int so_luong_dv, int tl_balo){
    for(int i = 0; i<so_luong_dv; i++){
        for(int j = 0; j<=tl_balo; j++){
            printf("%-2d%-3d|", X[i][j], F[i][j]);
        }
        printf("\n");
    }
}

void Trabang(DoVat *dsdv, int sl_do_vat, int tl_balo, int X[][100], int F[][100]){
    int V = tl_balo;
    for(int k = sl_do_vat -1; k>=0; k--){
        dsdv[k].PA = X[k][V];
        V = V - X[k][V] * dsdv[k].TL;
    }
}

void InKetQua(DoVat *dsdv, int sl_do_vat, int tl_balo){
    int tong_tl = 0;
    int tong_gt = 0;
    printf("PHUONG AN TIM DUOC KHI SU DUNG QHD: \n");
    printf("|---------------------------------------------------|\n");
    printf("|%-3s|%-20s|%-8s|%-7s|%-9s|\n", "STT", "TEN DO VAT", "TLUONG", "GIA TRI", "PHUONG AN");
    printf("|---------------------------------------------------|\n");
    for(int i = 0; i< sl_do_vat; i++){
        printf("|%-3d|%-20s|%-8d|%-7d|%-9d|\n", dsdv[i].STT, dsdv[i].ten, dsdv[i].TL, dsdv[i].GT, dsdv[i].PA);
        tong_tl += dsdv[i].PA * dsdv[i].TL;
        tong_gt += dsdv[i].PA * dsdv[i].GT;
    }
    printf("|---------------------------------------------------|\n");
    printf("Tong trong luong = %-9d\n", tong_tl);
    printf("Tong gia tri = %-9d\n", tong_gt);
}

int main(){
    int so_luong_dv, tl_balo;
    DoVat *ds = readFile(&so_luong_dv, &tl_balo);
    int F[50][100] = {0};
    int X[50][100] = {0};
    QuyHoachDong(ds, so_luong_dv, tl_balo, F, X);
    InBang(F, X, so_luong_dv, tl_balo);
    Trabang(ds, so_luong_dv, tl_balo, X, F);
    InKetQua(ds, so_luong_dv, tl_balo);
    printf("Thuat toan ket thuc\n");
    return 0;
}
/*
|   0 0|   0 0|   0 0|   4 1|   4 1|   4 1|   8 2|   8 2|   8 2|  12 3
|   0 0|   0 0|   0 0|   4 0|   5 1|   5 1|   8 0|   9 1|  10 2|  12 0
|   0 0|   0 0|   0 0|   4 0|   5 0|   6 1|   8 0|   9 0|  10 0|  12 0
|   0 0|   0 0|   3 1|   4 0|   6 2|   7 1|   9 3|  10 2|  12 4|  13 3
|   0 0|   1 1|   3 0|   4 0|   6 0|   7 0|   9 0|  10 0|  12 0|  13 0

0 0  |0 0  |0 0  |1 4  |1 4  |1 4  |2 8  |2 8  |2 8  |3 12 |
0 0  |0 0  |0 0  |0 4  |1 5  |1 5  |0 8  |1 9  |2 10 |0 12 |
0 0  |0 0  |0 0  |0 4  |0 5  |1 6  |0 8  |0 9  |0 10 |0 12 |
0 0  |0 0  |1 3  |0 4  |2 6  |1 7  |3 9  |2 10 |4 12 |3 13 |
0 0  |1 1  |0 3  |0 4  |0 6  |0 7  |0 9  |0 10 |0 12 |0 13 |
*/
