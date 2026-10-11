#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct {
	int KL,GT,PA;
	char ten[25];
} dovat;
typedef int bang[50][100];
dovat* read_file(int *n, int *w){
	FILE *f=fopen("Test13.txt","r");
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
void print_result(dovat* a, int n, int m) {
	int tongGT=0, tongKL=0;
	printf("Phuong an cai balo1 su dung quy hoach dong\n");
	printf("|---|--------------------|-------|-------|-------|\n");
	printf("|STT|Ten do vat          |  KL   |  GT   |  PA   |\n");
	printf("|---|--------------------|-------|-------|-------|\n");
	for(int i=0; i < n; i++) {
		printf("|%-3d|%-20s|%-7d|%-7d|%-7d|\n",i+1,a[i].ten,a[i].KL,a[i].GT,a[i].PA);
		tongGT +=a[i].GT*a[i].PA;
		tongKL +=a[i].KL*a[i].PA;
	}
	printf("|---|--------------------|-------|-------|-------|\n");
	printf("Trong luong cua balo = %5d\n",m);
	printf("Tong trong luong     = %5d\n" , tongKL);
	printf("Tong gia tri         = %5d\n", tongGT);
}
void create_table(dovat *a, int n, int m, bang F, bang X) {
	for(int i=0; i<=m; i++) {
		X[0][i]=i/ a[0].KL;
		F[0][i]= X[0][i]*a[0].GT;
	}
	for(int i=1; i < n;i++) {
		for(int j=0; j<=m; j++) {
			F[i][j]=F[i-1][j];
			X[i][j]=0;
			int PA_max=j/a[i].KL;
			for(int k=1; k<= PA_max; k++) {
				if(k*a[i].GT + F[i-1][j-k*a[i].KL] > F[i][j]) {
					F[i][j]=k*a[i].GT + F[i-1][j-k*a[i].KL];
					X[i][j]=k;
				}
			}	
		}	
	}
}
void in_bang(int F[][100], int X[][100], int soluongdv, int tl_balo) {
	for(int i=0; i<soluongdv; i++) {
		for(int j=0; j <= tl_balo; j++) {
			printf("%-2d%-3d|",X[i][j], F[i][j]);
		}
		printf("\n");
	}
}
void search_bang(dovat* a, int n, int m, bang X) {
	for(int i=n-1; i>=0; i--) {
		a[i].PA=X[i][m];
		m-=X[i][m]*a[i].KL;
	}
}
int main() {
	int n=0, m=0;
	dovat* a;
	bang F,X;
	a=read_file(&n,&m);
	create_table(a,n,m,F,X);
	in_bang(F,X,n,m);
	search_bang(a,n,m,X);
	print_result(a,n,m);
	free(a);
	return 0;
}
	
