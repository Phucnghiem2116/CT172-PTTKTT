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
void read_file(record a[], int *n) {
	FILE *f=fopen("data1.txt", "r");
	int i=0;
	if(f==NULL) {
		printf("Loi mo file khong thanh cong!\n");
		return;
	}
	else {
		printf("Mo file thanh cong !!!\n");
		while(!feof(f)) {
			fscanf(f,"%d %f", &a[i].key, &a[i].other);
			i++;
		}
	}
	*n=i;
	fclose(f);
}
void bubbleSort(record a[], int n) {
	for(int i=0; i<n-1;i++) {
		for(int j=n-1; j>=1; j--) { 
			if(a[j].key < a[j-1].key) swap(&a[j], &a[j-1]);
 			}
 		}
}
void inDS(record a[], int n) {
	for(int i=0; i<n; i++) {
		printf("%3d %5d %8.2f", i+1, a[i].key, a[i].other);
		printf("\n");
	}
}
int main() {
	printf("Bubble_Sort\n");
	int n;
	record a[100];
	read_file(a, &n);
	if(n!=0) {
		printf("Du lieu truoc khi sap xep\n");
	}
	inDS(a, n);
	bubbleSort(a ,n);
	printf("Du lieu sau khi sap xep\n");
	inDS(a, n);
	return 0;
}
