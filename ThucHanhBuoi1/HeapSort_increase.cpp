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
void pushDown(record a[], int first, int last) {
	int f=first;
	while( f<= (last-1)/2) {
		int L=2*f+1 , R=2*f+2;
		if(last==L) {
			if(a[f].key < a[L].key) swap(&a[f], &a[L]);
		return;
		}
		if( (a[f].key < a[L].key) && a[L].key >= a[R].key) {
			swap(&a[f], &a[L]);
			f=L;
		}
		else if((a[f].key < a[R].key) && a[L].key < a[R].key) {
			swap(&a[f], &a[R]);
			f=R;
		}
		else return;
	}
}
void heapSort(record a[], int n) {
	for(int i=(n-2)/2; i>=0; i--) {
		pushDown(a, i, n-1);
	}
	for(int i=n-1; i>=1;i--) {
		swap(&a[0], &a[i]);
		pushDown(a,0,i-1);
	}
	swap(&a[0], &a[1]);
}
void read_file(record a[], int *n) {
	FILE *f=fopen("data.txt", "r");
	int i=0;
	if(f==NULL) printf("Mo file khong thanh cong!!!");
	else {
		printf("Mo file thanh cong!!!\n");
		while(!feof(f)) {
			fscanf(f,"%d %f", &a[i].key, &a[i].other);
			i++;
		}
	}
	*n=i;
	fclose(f);
}
void inDS(record arr[], int n){
	for(int i = 0; i< n; i++){
		printf("%3d %5d %8.2f", i+1, arr[i].key, arr[i].other);
		printf("\n");
	}
}
int main() {
	printf("Heap_Sort\n");
	int n;
	record a[100];
	read_file(a,&n);
	if(n!=0) {
		printf("Du lieu truoc khi sap xep\n");
	}
	inDS(a,n);
	heapSort(a,n);
	printf("Du lieu sau khi sap xep\n");
	inDS(a,n);
	return 0;
}
