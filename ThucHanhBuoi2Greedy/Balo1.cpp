#include<stdio.h>
#include<stdlib.h>
typedef struct {
	float KL,GT,DG;
	int PA;
	char ten[20];
} dovat;
dovat* read_file(int *w, int *n) {
	FILE *f=fopen("CaiBalo1.txt","r");
	int i=0;
	dovat* dsdv=(dovat*)malloc(sizeof(dovat));
	if(f==NULL) {
		printf("Loi khong the mo file !!!");
		*w=0;
		return NULL;
	}
	else {
		printf("Mo file thanh cong");
		fscanf(f,"%d", w);
		while(!feof(f)) {
			fscanf(f,"%f %f %[^\n]", &dsdv[i].KL, &dsdv[i].GT, &dsdv[i].ten);
			dsdv[i].DG=dsdv[i].GT/ dsdv[i].KL;
			dsdv[i].PA=0;
			i++;
			dsdv=(dovat*)realloc(dsdv, sizeof(dovat)*(i+1));
		}
	}
	*n=i;
	return dsdv;
}
void inDS(dovat* dsdv, int n, float TGT, float TKL) {
	printf("==============================================\n");
	printf("|%-20s|%-5s|%-5s|%-5s|%-5s|\n", "TEN DO VAT", "KL", "GT", "DG", "PA");
	for(int i=0; i<n; i++) {
		printf("|%-20s|%-5.2f|%-5.2f|%-5.2f|%-5d|\n", dsdv[i].ten,dsdv[i].KL,dsdv[i].GT,dsdv[i].DG,dsdv[i].PA);
	}
	printf("==============================================\n");
	printf("Tong khoi luong: %.2f\n",TKL);
	printf("Tong gia tri: %.2f\n",TGT);
	printf("==============================================\n");
}
void insertionSort(dovat* dsdv, int n) {
	for(int i=1; i<n; i++){
		int j=i;
		while(j>0 && dsdv[j].DG > dsdv[j-1].DG) {
			dovat temp= dsdv[j];
			dsdv[j]=dsdv[j-1];
			dsdv[j-1]=temp;
			j--;
		}
	}
}
void greedy(int n, int w, dovat *dsdv, float *TGT, float *TKL) {
	int i=0;
	while( w>0 && i < n) {
		int temp= w/ dsdv[i].KL;
		dsdv[i].PA=temp;
		*TGT += temp*dsdv[i].GT;
		*TKL += temp*dsdv[i].KL;
		w -= temp* dsdv[i].KL;
		i++;
	}
}
int main() {
	int n,w;
	float TGT=0, TKL=0;
	dovat* dsdv;
	dsdv= read_file(&w, &n);
	inDS(dsdv,n,TGT, TKL);
	insertionSort(dsdv,n);
	printf("DANH SACH DO VAT SAU KHI DA SAP XEP\n");
	inDS(dsdv,n ,TGT, TKL);
	greedy(n,w,dsdv, &TGT,&TKL);
	printf("PHUONG AN TIM DUOC BANG THUAT TOAN THAM AN\n");
    inDS(dsdv, n, TGT, TKL);
    free(dsdv);
    return 0;
}
