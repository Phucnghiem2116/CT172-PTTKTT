#include<stdio.h>
#include<stdlib.h>
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
	FILE *f=fopen("data.txt", "r");
	int i=0;
	if(f==NULL) printf("Loi mo file");
	else {
		printf("Mo file thanh cong\n");
		while(! feof(f)) {
			fscanf(f,"%d %f", &a[i].key , &a[i].other);
			i++;
		}
	}
	*n=i;
	fclose(f);
}
void inDS(record a[], int n) {
	for(int i=0; i<n; i++) {
		printf("%-3d %-5d %-8.2f\n",
		i+1,a[i].key, a[i].other);
	}
}
void bubble(record a[],int n) {
	for(int i=0; i<n; i++) {
		for(int j=n-1; j>i; j--) {
			if(a[j].key < a[j-1].key) {
			swap(&a[j], &a[j-1]);
		}
		}
	}
}
void insertion(record a[], int n) {
	for(int i=1; i<n; i++) {
		int j=i;
		while(j>0 && a[j].key > a[j-1].key) {
			swap(&a[j],&a[j-1]);
			j--;
		}
	}
}
void selection(record a[], int n) {
	for(int i=0; i<n-1; i++) {
		int min= a[i].key;
		int min_index=i;
		for(int j=i+1; j<n; j++) {
			if(a[j].key < min) {
				min=a[j].key;
				min_index=j;
			}
		}
		swap(&a[i],&a[min_index]);
	}
}
void push_down(record a[], int first, int last) {
	int f=first;
	while(f<= (last-1)/2) {
		int L=2*f+1, R=2*f+2;
		if(last==L) {
			if(a[f].key > a[L].key) swap(&a[f], &a[L]);
			else return;
		}
		else {
			if(a[f].key > a[L].key && a[L].key <= a[R].key) {
				swap(&a[f],&a[L]);
				f=L;
			}
			else if(a[f].key > a[R].key && a[L].key > a[R].key) {
				swap(&a[f],&a[R]);
				f=R;
			}
			else return;
		}
	}
}
void heap(record a[], int n) {
	for(int i=(n-2)/2; i>=0; i--) {
		push_down(a,i,n-1);
	}
	for(int i=n-1; i>=2; i--) {
		swap(&a[0], &a[i]);
		push_down(a,0,i-1);
	}
	swap(&a[0], &a[1]);	
}

int find_pivot(record a[], int i, int j) {
	int first=a[i].key;
	for(int k=i+1; k<=j; k++) {
		if(a[k].key != first) return (a[k].key>first) ? k:i;
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
void quick(record a[], int i, int j) {
	int pivot=find_pivot(a,i,j);
	if(pivot != -1) {
		int k= partition(a,i,j, a[pivot].key);
		quick(a,i,k-1);
		quick(a,k,j);
	}
}
int main() {
	int n;
	record a[100];
	read_file(a,&n);
	printf("Du lieu truoc khi sap xep\n");
	inDS(a,n);
	printf("Du lieu sau khi sap xep\n");
	quick(a,0,n-1);
	inDS(a,n);
	return 0;
}
