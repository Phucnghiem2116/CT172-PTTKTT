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
void read_file(record arr[], int *n) {
	FILE *f=fopen("data.txt", "r");
	int i=0;
	if(f==NULL) {
		printf("Mo file khong thanh cong");
		return;
	}
	else {
		printf("Mo file thanh cong");
		while(! feof(f)) {
			fscanf(f,"%d %f", &arr[i].key, &arr[i].other);
			i++;
		}
	}
	*n=i;
	fclose(f);
}
void insertionSort(record arr[], int n) {
	for(int i=1; i<n; i++) {
		int j=i;
		while(j>0 && arr[j-1].key  > arr[j].key){ 	
			swap(&arr[j-1], &arr[j]);
			j--;
		}
	}
}
void printArray(record arr[], int n) {
	for(int i=0; i<n; i++) {
		printf("%3d %5d %8.2f", i+1, arr[i].key, arr[i].other);
		printf("\n");
	}
}
int main(){
	printf("InsertionSort: \n\n");
	record arr[100];
	int n;
	read_file(arr, &n);
	if(n != 0){
		printf("Du lieu truoc khi sap xep: \n");
	}
	printArray(arr, n);
	insertionSort(arr, n);
	printf("\nDu lieu sau khi sap xep: \n");
	printArray(arr, n);
	return 0;
}
	
