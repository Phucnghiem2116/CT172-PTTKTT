#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int PA;
	int menhgia;
	char donvi[20];
} tien;
tien* read_file(int *n) {
	int i=0;
	FILE *f=fopen("ATM.txt","r");
	tien* ds=(tien*)malloc(sizeof(tien));
	if(f==NULL) {
		printf("Mo file khong thanh cong !!!");
		*n=0;
		return NULL;
	}
	else {
		printf("Mo file thanh cong !!!");
		while(! feof(f)) {
			fscanf(f,"%d %[^\n]", &ds[i].menhgia, ds[i].donvi);
			ds[i].PA=0;
			i++;
			ds=(tien*)realloc(ds, sizeof(tien)*(i+1));
		}
	}
	fclose(f);
	*n=i;
	return ds;
}
void insertionSort(tien* ds,int n) {
	for(int i=1; i<n; i++) {
		int j=i;
		while(j>0 && ds[j-1].menhgia< ds[j].menhgia) {
			tien temp= ds[j];
			ds[j]=ds[j-1];
			ds[j-1]=temp;
		j--;
		}
	}
}
void inDS(tien* ds, int n, int Giatrirut, int Tiendarut) {
	printf("\nDANH SACH CAC MENH GIA TIEN\n");
    printf("|%-3s|%-10s|%-20s|%-10s|\n", "STT", "MENH GIA", "DON VI", "PA");
    printf("================================================\n");
    for(int i=0; i<n; i++) {
    	printf("|%-3d|%-10d|%-20s|%-10d|\n",i+1, ds[i].menhgia, ds[i].donvi, ds[i].PA);
    }
    printf("================================================\n");
    printf("So tien can rut: %d\n", Giatrirut);
    printf("So tien da rut ra: %d\n", Tiendarut);
    printf("So tien con lai chua rut: %d\n", Giatrirut - Tiendarut);
    return;
}
void greedy(tien* ds,int n ,int Giatrirut, int *Tiendarut) {
	int i=0;
	while(i < n && Giatrirut > 0) {
		ds[i].PA = Giatrirut / ds[i].menhgia;
		*Tiendarut += ds[i].PA * ds[i].menhgia;
		Giatrirut -= ds[i].PA * ds[i].menhgia;
		i++;
	}

}	
int main() {
	int n;
	int Tiendarut=0;
	int Giatrirut=0;
	tien* ds=read_file(&n);
	insertionSort(ds, n);
    inDS(ds, n, Giatrirut, Tiendarut);
    printf("Nhap so tien can rut: ");
    scanf("%d", &Giatrirut);
    greedy(ds,n, Giatrirut, &Tiendarut);
    inDS(ds, n, Giatrirut, Tiendarut);
    free(ds);
    return 0;
}
    
	
