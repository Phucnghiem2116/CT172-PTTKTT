#include<stdio.h>
#include<stdlib.h>
typedef struct {
	float KL,GT,DG;
	int PA;
	char ten[20];
} dovat;
dovat* read_file(int *n, int *w) {
	dovat* dsdv=(dovat*)malloc(sizeof(dovat));
	FILE *f=fopen("CaiBalo3.txt","r");
	int i=0;
	if(f==NULL) {
		printf("Loi mo file khong thanh cong!!!");
		*w=0;
	}
	else {
		printf("Mo file thanh cong");
		fscanf(f,"%d", w);
		while(!feof(f)) {
			fscanf(f,"%f %f %[^\n]", &dsdv[i].KL,&dsdv[i].GT,&dsdv[i].ten);
			dsdv[i].DG=dsdv[i].GT/dsdv[i].KL;
			dsdv[i].PA=0;
			i++;
			dsdv=(dovat*)realloc(dsdv, sizeof(dovat)*(i+1));
		}
	}
	*n=i;
	return dsdv;
}
void inDS(dovat* dsdv,int n, float TKL, float TGT) {
	printf("===============================================\n");
	printf("|%-20s|%-5s|%-5s|%-5s|%-5s|\n","Ten do vat","KL","GT","DG");
	for(int i=0; i<n; i++) {
		printf("|%-20s|%-5.2f|%-5.2f|%-5.2f|%-5d|\n",dsdv[i].ten,dsdv[i].KL,dsdv[i].KL,dsdv[i].DG,dsdv[i].PA);
	}
	printf("===============================================\n");
	printf("Tong khoi luong: %.2f\n",TKL);
	printf("Tong gia tri: %.2f\n",TGT);
	printf("===============================================\n");
}
void insertionSort(dovat* dsdv, int n) {
	for(int i=0; i<n-1;i++) {
		int j=i+1;
		while(j>0 && dsdv[j].DG > dsdv[j-1].DG) {
			dovat temp=dsdv[j];
			dsdv[j]=dsdv[j-1];
			dsdv[j-1]=temp;
			j--;
		}
	}
}
void greedy(int n, int w, dovat* dsdv, float *TKL, float *TGT) {
	int i=0;
	while(w>0 && n>i) {
		int temp= w/dsdv[i].KL;
		if(temp>1) temp=1;
		dsdv[i].PA=temp;
		*TKL+=temp*dsdv[i].KL;
		*TGT+= temp*dsdv[i].GT;
		w-=temp*dsdv[i].KL;
		i++;
	}
}
int main() {
	int n,w;
	float TGT=0, TKL=0;
	dovat* dsdv;
	dsdv=read_file(&n,&w);
	inDS(dsdv,n,TKL,TGT);
	insertionSort(dsdv,n);
	printf("Danh sach do vat sau khi sap xep\n");
	inDS(dsdv,n,TKL,TGT);
	greedy(n,w,dsdv,&TKL,&TGT);
	printf("Phuong an sau khi dung thuat toan tham an\n");
	inDS(dsdv,n,TKL,TGT);
	free(dsdv);
	return 0;
}
	
		
