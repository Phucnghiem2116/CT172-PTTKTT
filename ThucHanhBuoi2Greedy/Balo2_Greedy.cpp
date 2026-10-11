#include<stdio.h>
#include<stdlib.h>
typedef struct {
	float KL,GT,DG;
	int PA;
	int SL;
	char ten[20];
} dovat;
dovat* read_file(int *n, int *w) {
	dovat* dsdv=(dovat*)malloc(sizeof(dovat));
	FILE *f=fopen("CaiBalo2.txt","r");
	int i=0;
	if(f==NULL) {
		printf("Loi mo file khong thanh cong !!!");
		*w=0;
	}
	else {
		printf("Mo file thanh cong");
		fscanf(f,"%d",w);
		while(!feof(f)) {
			fscanf(f,"%f %f %d %[^\n]",&dsdv[i].KL, &dsdv[i].GT,&dsdv[i].SL, &dsdv[i].ten);
			dsdv[i].DG=dsdv[i].GT/dsdv[i].KL;
			dsdv[i].PA=0;
			i++;
			dsdv =(dovat*)realloc(dsdv, sizeof(dovat)*(i+1));
		}
	}
		*n=i;
		return dsdv;
}
void inDS(dovat* dsdv, int n, float TGT, float TKL) {
	printf("===================================================\n");
	printf("|%-20s|%-5s|%-5s|%-5s|%-5s|%-5s|\n","Ten do vat","KL","GT","DG","PA","SL");
	for(int i=0; i<n; i++) {
		printf("|%-20s|%-5.2f|%-5.2f|%-5.2f|%-5d|%-5d|\n",dsdv[i].ten,dsdv[i].KL,dsdv[i].GT,dsdv[i].DG,dsdv[i].PA,dsdv[i].SL);
	}
	printf("===================================================\n");
	printf("Tong khoi luong: %.2f\n",TKL);
	printf("Tong gia tri: %.2f\n", TGT);
	printf("===================================================\n");
}
void insertionSort(dovat* dsdv, int n) {
	for(int i=1; i<n; i++) {
		int j=i;
		while(j>0 && dsdv[j-1].DG < dsdv[j].DG) {
			dovat temp=dsdv[j];
			dsdv[j]=dsdv[j-1];
			dsdv[j-1]=temp;
			j--;
		}
	}
}
void greedy(int n, int w, dovat* dsdv, float *TKL, float *TGT) {
	int i=0;
	while(w>0 && i<n) {
		int temp=w / dsdv[i].KL;
		if(temp > dsdv[i].SL) temp=dsdv[i].SL;
		dsdv[i].PA=temp;
		*TKL += temp*dsdv[i].KL;
		*TGT += temp*dsdv[i].GT;
		w-=temp*dsdv[i].KL;
		i++;
	}
}
int main() {
	int n,w;
	dovat *dsdv;
	float TGT=0, TKL=0;
	dsdv= read_file(&n, &w);
	inDS(dsdv,n,TKL,TGT);
	insertionSort(dsdv,n);
	printf("DANH SACH DO VAT SAU KHI DA SAP XEP\n");
	inDS(dsdv,n,TKL,TGT);
	greedy(n,w,dsdv,&TKL,&TGT);
	printf("PHUONG AN TIM DUOC BANG THUAT TOAN THAM AN\n");
    inDS(dsdv, n, TGT, TKL);
    free(dsdv);
    return 0;
}	
