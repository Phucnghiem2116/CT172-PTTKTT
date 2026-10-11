#include<stdio.h>
#include<stdlib.h>
typedef struct {
	float KL,GT,DG;
	int PA;
	char ten[20];
} dovat;
void swap(dovat *a, dovat *b) {
	dovat temp=*a;
	*a=*b;
	*b=temp;
}
dovat* read_file(int *n, float *w) {
	FILE *f=fopen("CaiBalo1.txt","r");
	int i=0;
	dovat *a=(dovat*)malloc(sizeof(dovat));
	if(f==NULL) {
		printf("Mo file khong thanh cong");
		*n=0;
		}
	else {
		printf("Mo file thanh cong\n");
		fscanf(f, "%f", w);
		while(!feof(f)) {
			fscanf(f,"%f %f %[^\n]", &a[i].KL, &a[i].GT, &a[i].ten);
			a[i].DG=a[i].GT/a[i].KL;
			a[i].PA=0;
			i++;
			a=(dovat*)realloc(a, sizeof(dovat)*(i+1));
			}
	}
	*n=i;
	fclose(f);
	return a;	
}
void nhanhcan(dovat* dsdv, int n, float GT_hientai, float KL_conlai, int PA_tam[],int i, float *GT_max) {
	for(int so_luong=(int)(KL_conlai/dsdv[i].KL); so_luong>=0; so_luong--) {
		float KL_moi= KL_conlai - so_luong*dsdv[i].KL;
		float GT_moi= GT_hientai + so_luong*dsdv[i].GT;
		float can_tren=GT_moi;
		if( i < n-1) can_tren += KL_moi*dsdv[i+1].DG;
		if(can_tren > *GT_max) {
			PA_tam[i]=so_luong;
			if(i==n-1 || KL_moi==0) {
				if(GT_moi > *GT_max) {
					*GT_max=GT_moi;
					for(int k=0; k<n; k++) {
						dsdv[k].PA=PA_tam[k];
					}
			}
		}
		else nhanhcan(dsdv, n, GT_moi, KL_moi, PA_tam, i + 1, GT_max);
		PA_tam[i]=0;
		}
	}		
}
void InDS(dovat* dsdv, int n){
    printf("-------------------------------------------\n");
    printf("|%-20s|%-5s|%-5s|%-4s|%-3s|\n", "Ten", "KL", "GT", "DG", "PA");
    printf("-------------------------------------------\n");
    for(int i = 0; i<n; i++){
        printf("|%-20s|%-5.2f|%-5.2f|%-4.2f|%-3d|\n", dsdv[i].ten, dsdv[i].KL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
    }
    printf("-------------------------------------------\n");
}
void InsertionSort(dovat* dsdv, int n){
    for(int i = 0; i<n-1; i++){
        int j = i+1;
        while(j > 0 && dsdv[j].DG > dsdv[j-1].DG){
            swap(&dsdv[j], &dsdv[j-1]);
            j--;
        }
    }
}
int main() {
	int n;
    float w;
    dovat *dsdv = read_file(&n, &w);
    InsertionSort(dsdv, n);
    InDS(dsdv, n);
    int *PA_tam = (int*)calloc(n, sizeof(int));
    float GT_max = 0;
    nhanhcan(dsdv, n, 0, w, PA_tam, 0, &GT_max);

    printf("\nPhuong an toi uu:\n");
    InDS(dsdv, n);
    printf("Tong gia tri lon nhat: %.2f\n", GT_max);

    free(dsdv);
    free(PA_tam);
    return 0;
}

