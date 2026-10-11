#include<stdio.h>
typedef int keytype;
typedef float othertype;
typedef struct {
	keytype key;
	othertype other;
} record;
void swap(record *a, record *b) {
	record temp=*a;
	*a=*b;
	*b=temp;
}
int find_pivot(record a[], int i, int j){
	int firstkey=a[i].key;
	for(int k=i+1; k<=j; k++) {
		if(a[k].key != firstkey) {
			return a[k].key > firstkey ? k: i;
		}
	}
	return -1;
}
int partition(record a[], int L, int R, int pivot) {
	while(L<=R) {
		while(a[L].key < pivot) L++;
		while(a[R].key >= pivot) R--;
		if(L<R) swap(&a[L], &a[R]);
	}
	return L;
}
void quickSort(record a[], int i, int j) {
	int pivot=find_pivot(a,i,j);
	if(pivot != -1) {
		int k= partition(a,i,j,a[pivot].key);
		quickSort(a,i, k-1);
		quickSort(a, k, j);
	}
}
void read_file(record a[], int *n) {
	FILE *f=fopen("data.txt", "r");
	int i=0;
	if(f==NULL) {
		printf("Mo file khong thanh cong\n");
		return;
	}
	else {
		printf("Mo file thanh cong\n");
		while(!feof(f)) {
			fscanf(f, "%d %f", &a[i].key, &a[i].other);
			i++;
		}
	}
	*n=i;
	fclose(f);
}
void printData(record a[], int n) {
	for(int i=0; i<n; i++) {
		printf("%3d %5d %8.2f", i+1, a[i].key, a[i].other);
		printf("\n");
	}
}

int main (){
	record a[100];
	int n = 0;
	printf("Thuat toan Quick Sort\n");
	read_file(a, &n);
	printf("Du lieu truoc khi sap xep:\n");
	printData(a, n);
	quickSort(a, 0, n-1);
	printf("Du lieu sau khi sap xep:\n");
	printData(a, n);
	return 0;
}
