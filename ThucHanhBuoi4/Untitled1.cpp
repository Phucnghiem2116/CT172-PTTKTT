#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int KL,GT,PA;
	char ten[25];
} dovat;
typedef int bang[50][100];
dovat* read_file(int *n, int *w){
	FILE *f=fopen("Test13(2).txt","r");
	dovat* a=(dovat*)malloc(sizeof(dovat));
	int i=0;
	fscanf(f,"%d",w);
	if(f==NULL) {
		printf("Mo file khong thanh cong");
	}
	else {
	printf("Mo file thanh cong\n");	
	while(!feof(f)) {
		a=(dovat*)realloc(a, sizeof(dovat)*(i+1));
		fscanf(f,"%d %d %[^\n]", &a[i].KL, &a[i].GT,&a[i].ten);
		a[i].PA=0;
		i++;
	}
	}
	*n=i;
	fclose(f);
	return a;
}
void in_bang( int soluongdv, int tl_balo,int F[][100], int X[][100]) {
	for(int i=0; i<soluongdv; i++) {
		for(int j=0; j <= tl_balo; j++) {
			printf("%-2d%-3d|",X[i][j], F[i][j]);
		}
		printf("\n");
	}
}
void in_ketqua(dovat* a, int n,int m) {
	int tongKL=0, tongGT=0;
	printf("--------------------------------------\n");
	printf("|%-3s|%-20s|%-5s|%-5s|%-5s|\n", "STT", "Ten do vat", "KL", "GT", "PA");
	printf("--------------------------------------\n");
	for(int i=0; i<n; i++) {
		printf("|%-3d|%-20s|%-5d|%-5d|%-5d|\n",i+1,a[i].ten,a[i].KL,a[i].GT,a[i].PA);
		tongGT +=a[i].GT*a[i].PA;
		tongKL +=a[i].KL*a[i].PA;
	}
	printf("--------------------------------------\n");
	printf("Phuong an (theo thu tu DG giam dan): X(");
	for(int i=0; i<n-1; i++){
		printf("%d,", a[i].PA);
	}	
	printf("%d)\n", a[n-1].PA);
	printf("Trong luong cua balo = %5d\n",m);
	printf("Tong trong luong     = %5d\n" , tongKL);
	printf("Tong gia tri         = %5d\n", tongGT);
}
void tra_bang(dovat* a, int n, int m, bang X) {
	for(int i=n-1; i>=0; i--) {
		a[i].PA=X[i][m];
		m-= X[i][m]*a[i].KL;
	}
}
int min(int a, int b) {
	return a < b ? a : b;
}

void tao_bang(dovat* a, int n, int m,bang F ,bang X) {
	for(int j=0; j<=m; j++) {
		X[0][j]= (j >= a[0].KL);
		F[0][j]=X[0][j]*a[0].GT;
	}
	for(int i=1; i<n; i++) {
		for(int j=0; j <=m; j++) {
			F[i][j]=F[i-1][j];
			X[i][j]=0;
			if((j >=a[i].KL)&& (a[i].GT + F[i-1][j-a[i].KL] > F[i][j])) {
				F[i][j]=a[i].GT + F[i-1][j-a[i].KL];
				X[i][j]=1;
			}
		}
	}
}
int main() {
	int n,m;
	dovat* a;
	bang F,X;
	a=read_file(&n,&m);
	tao_bang(a,n,m,F,X);
	in_bang(n,m,F,X);
	tra_bang(a,n,m,X);
	in_ketqua(a,n,m);
	free(a);
	return 0;
}
