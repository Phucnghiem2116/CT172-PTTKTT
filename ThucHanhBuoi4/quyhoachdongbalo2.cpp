#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int KL,GT,PA,SL;
	char ten[25];
} dovat;
typedef int bang[50][100];
dovat* read_file(int *n, int *m) {
	FILE *f=fopen("Test2.txt","r");
	int i=0;
	dovat* a=(dovat*)malloc(sizeof(dovat));
	if(f==NULL) printf("Mo file khong thanh cong");
	else {
		printf("Mo file thanh cong\n");
		fscanf(f,"%d",m);
		while(!feof(f)) {
			fscanf(f,"%d %d %d %[^\n]",&a[i].KL,&a[i].GT,&a[i].SL,&a[i].ten);
			a[i].PA=0;
			i++;
			a=(dovat*)realloc(a, sizeof(dovat)*(i+1));
		}
	}
	*n=i;
	fclose(f);
	return a;
}
void print_result(dovat* a, int n, int m) {
	int TGT=0, TKL=0;
	printf("|===|====================|=======|=======|=======|=======|\n");
	printf("|STT|Ten do vat          |   KL  |   GT  |   PA  |   SL  |\n");
	printf("|===|====================|=======|=======|=======|=======|\n");
	for(int i=0; i<n; i++) {
		printf("|%-3d|%-20s|%-8d|%-8d|%-8d|%-8d|\n",i+1, a[i].ten, a[i].KL,a[i].GT, a[i].PA,a[i].SL);
		TKL += a[i].KL*a[i].PA;
		TGT += a[i].GT*a[i].PA;
	}
	printf("|===|====================|=======|=======|=======|=======|\n");
	printf("Trong luong cua balo = %5d\n",m);
	printf("Tong trong luong     = %5d\n" , TKL);
	printf("Tong gia tri         = %5d\n", TGT);
}
void in_bang(int F[][100], int X[][100], int n, int m) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<=m; j++) {
			printf("%-2d%-3d|", X[i][j], F[i][j]);
		}
		printf("\n");
	}
}
void tra_bang(dovat* a, int n, int m, bang X) {
	for(int i=n-1; i>=0; i--) {
		a[i].PA=X[i][m];
		m-= X[i][m]*a[i].KL;
	}
}
void create_table(dovat* a, int n, int m, bang F, bang X) {
	for(int j=0; j<=m; j++) {
		int PA_max=j/a[0].KL;
		if(PA_max > a[0].SL) PA_max=a[0].SL;
		X[0][j]=j/a[0].KL;
		F[0][j]= X[0][j]*a[0].GT;	
	}
	for(int i=1; i < n; i++) {
		for(int j=0; j < m; j++) {
			F[i][j]=F[i-1][j];
			X[i][j]=0;
			int PA_max=j/a[i].KL;
			for(int k=1; k<=PA_max; k++) {
				if(k*a[i].GT + F[i-1][j-k*a[i].KL] > F[i][j]) {
					F[i][j]=k*a[i].GT + F[i-1][j-k*a[i].KL];
					X[i][j]=k;
				}
			}
		}
	}
}
int main() {
	int n=0, m=0;
	dovat* a;
	bang F,X;
	a=read_file(&n,&m);
	create_table(a,n,m,F,X);
	in_bang(F,X,n,m);
	tra_bang(a,n,m,X);
	print_result(a,n,m);
	free(a);
	return 0;
}
