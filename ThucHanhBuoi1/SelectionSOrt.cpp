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
void SelectionSort(record arr[], int n) {
	for(int i=0; i<n-1; i++) {
		int index_min=i;
		for(int j=i+1; j<n; j++) {
			if(arr[j].key < arr[index_min].key) {
				index_min=j;
			}
		}
		swap(&arr[index_min], &arr[i]);
	}
}
void read_file(record arr[],int *n) {
	int i=0;
	FILE *f=fopen("data.txt","r");
	if(f==NULL) {
		printf("Mo file khong thanh cong");
		return;
	}
	else {
		while(!feof(f)) {
			fscanf(f,"%d %f", &arr[i].key, &arr[i].other);
			i++;
		}
	}
	*n=i;
	fclose(f);
}
void inDS(record arr[], int n) {
	for(int i=0; i<n; i++) {
		printf("%3d %5d %8.2f", i+1, arr[i].key, arr[i].other);
		printf("\n");
	}	
}
int main() {
	printf("Selection_Sort\n");
	int n;
	record arr[100];
	read_file(arr, &n);
	if(n!=0) {
		printf("Du lieu truoc khi sap xep: \n");
	}
	inDS(arr, n);
	SelectionSort(arr, n);
	printf("\nDu lieu sau khi sap xep: \n");
	inDS(arr, n);
	return 0;
}
	
	
