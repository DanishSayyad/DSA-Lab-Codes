<<<<<<< HEAD

#include<iostream>
#include<fstream>
#include<string>
#include "Sorts.h"

using namespace std;

void display(int A[], int n) {
	cout<<endl;
	for(int i = 0; i < n; i++)
		cout<<A[i]<<"\t";
	return;
}

void readFile(string name, int A[], int s) {
	ifstream f1; 
	f1.open(name, ios::in);
	if(!f1) return;
	int i = 0;
	string s1;
	
	for(int i = 0; i < s; i++) {
		if(!getline(f1,s1)) {
			 cerr<<"File not open";
			return;
		}
		A[i] = stoi(s1);
	}
}

void Merge(int A[], int s, int m, int e){
	int tempA[e - s + 1];
	int i = s, j = m + 1, k = 0;
	while(i <= m && j <= e){
		if(A[i] < A[j]){
			tempA[k] = A[i];
			i++;		
		}
		else {
			tempA[k] = A[j];
			j++;
		}
		k++;
	
	}
	while(i <= m)
		tempA[k++] = A[i++];
		
	while(j <= e)
		tempA[k++] = A[j++];
		
	for(int i = s, k = 0; i <= e; i++, k++){
		A[i] = tempA[k];
	
	}
	return;	

}

void Msort(int A[], int s, int e) {
	if(s == e) return;
	int m = (s + e) /2;
	Msort(A, s, m);
	Msort(A, m + 1, e);
	Merge(A, s, m, e);
	return;
}

void MergeSort(char* file, int s) {
	int arr[s];
	readFile(file, arr, s);
	Msort(arr, 0, s-1);
	cout<<"\n";
	display(arr, s);
	return;
}

int partition(int a[], int s, int e) {
    int pivot = a[s];
    int i = s + 1, j = e;
    while (i <= j) {
        while (i <= e && a[i] < pivot) i++;
        while (j >= s + 1 && a[j] > pivot) j--;
        if (i < j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
    // swap pivot into its correct position
    int temp = a[s];
    a[s] = a[j];
    a[j] = temp;
    return j;
}

void qsort(int a[], int s, int e) {
	if(s >= e) return;
	
	int p = partition(a, s, e);
	qsort(a, s, p-1);
	qsort(a, p+1, e);
}

void QuickSort(char* file, int s) {
	int arr[s];
	readFile(file, arr, s);	
	qsort(arr, 0, s-1);
	display(arr, s);
	return;
}
=======

#include<iostream>
#include<fstream>
#include<string>
#include "Sorts.h"

using namespace std;

void display(int A[], int n) {
	cout<<endl;
	for(int i = 0; i < n; i++)
		cout<<A[i]<<"\t";
	return;
}

void readFile(string name, int A[], int s) {
	ifstream f1; 
	f1.open(name, ios::in);
	if(!f1) return;
	int i = 0;
	string s1;
	
	for(int i = 0; i < s; i++) {
		if(!getline(f1,s1)) {
			 cerr<<"File not open";
			return;
		}
		A[i] = stoi(s1);
	}
}

void Merge(int A[], int s, int m, int e){
	int tempA[e - s + 1];
	int i = s, j = m + 1, k = 0;
	while(i <= m && j <= e){
		if(A[i] < A[j]){
			tempA[k] = A[i];
			i++;		
		}
		else {
			tempA[k] = A[j];
			j++;
		}
		k++;
	
	}
	while(i <= m)
		tempA[k++] = A[i++];
		
	while(j <= e)
		tempA[k++] = A[j++];
		
	for(int i = s, k = 0; i <= e; i++, k++){
		A[i] = tempA[k];
	
	}
	return;	

}

void Msort(int A[], int s, int e) {
	if(s == e) return;
	int m = (s + e) /2;
	Msort(A, s, m);
	Msort(A, m + 1, e);
	Merge(A, s, m, e);
	return;
}

void MergeSort(char* file, int s) {
	int arr[s];
	readFile(file, arr, s);
	Msort(arr, 0, s-1);
	cout<<"\n";
	display(arr, s);
	return;
}

int partition(int a[], int s, int e) {
    int pivot = a[s];
    int i = s + 1, j = e;
    while (i <= j) {
        while (i <= e && a[i] < pivot) i++;
        while (j >= s + 1 && a[j] > pivot) j--;
        if (i < j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
    // swap pivot into its correct position
    int temp = a[s];
    a[s] = a[j];
    a[j] = temp;
    return j;
}

void qsort(int a[], int s, int e) {
	if(s >= e) return;
	
	int p = partition(a, s, e);
	qsort(a, s, p-1);
	qsort(a, p+1, e);
}

void QuickSort(char* file, int s) {
	int arr[s];
	readFile(file, arr, s);	
	qsort(arr, 0, s-1);
	display(arr, s);
	return;
}
>>>>>>> 995501c532bde0fcac677ba09c133489afa1eb8b
