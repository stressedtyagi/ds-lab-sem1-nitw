/* 
Design a program to implement the following sorting algorithms on integer data.

Bubble Sort [Optional]
Selection Sort [Optional]
Insertion Sort
Merge Sort
Quick Sort
The program should have a menu with options to

generate an array of random numbers,
call the various sorting algorithms on the array, and
print the array.
[The student should practice to write sorting algorithms on other data types including structures and class objects; and other possible ways they can be implemented/used] 
*/
#include <iostream>
#include <math.h>
using namespace std;
void print(int a[], int n) {
    for(int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}
void copy(int a[], int b[], int n) {
    for(int i = 0; i < n; i++) {
        b[i] = a[i];
    }
}
void bubbleSort(int[],int);
void selectionSort(int[],int);
void insertionSort(int[],int);
void merge(int*,int,int,int);
void mergeSort(int*,int,int);
void quickSort(int*,int,int);
int partition(int*,int,int);
int main() {
    int n;
    cout << "Enter number of elements in array : ";
    cin >> n;
    int a[n];
    srand((unsigned)time(0)); 
    for(int i = 0; i < n; i++) {
        a[i] = (rand()%(n+1));
    }

    cout << "Inital Array : ";
    print(a,n);

    cout << "--------------------------------------------------------------" << endl;
    int b[n];
    copy(a,b,n);
    bubbleSort(b,n);
    cout << "1. Array after bubble sort : ";
    print(b,n);
    cout << "--------------------------------------------------------------" << endl;
    
    cout << "--------------------------------------------------------------" << endl;
    copy(a,b,n);
    selectionSort(b,n);
    cout << "2. Array after selection sort : ";
    print(b,n);
    cout << "--------------------------------------------------------------" << endl;


    cout << "--------------------------------------------------------------" << endl;
    copy(a,b,n);
    insertionSort(b,n);
    cout << "3. Array after insertion sort : ";
    print(b,n);
    cout << "--------------------------------------------------------------" << endl;

    cout << "--------------------------------------------------------------" << endl;
    copy(a,b,n);
    mergeSort(b,0,n-1);
    cout << "4. Array after merge sort : ";
    print(b,n);
    cout << "--------------------------------------------------------------" << endl;

    cout << "--------------------------------------------------------------" << endl;
    copy(a,b,n);
    quickSort(b,0,n-1);
    cout << "5. Array after quick sort : ";
    print(b,n);
    cout << "--------------------------------------------------------------" << endl;

    return 0;
}

void bubbleSort(int a[], int n) {
    bool checkFlag{true};
    for(int i = 0; i < n-1 && checkFlag; i++) {
        checkFlag = false;
        for(int j = 0; j < n-i-1; j++) {
            if(a[j] > a[j+1]) {
                swap(a[j],a[j+1]);
                checkFlag = true;
            }
        }
    }
}

void selectionSort(int a[], int n) {
    for(int i = 0;i < n-1; i++) {
        int min = i;
        for(int j = i+1;j < n; j++) {
            if(a[j] < a[min]) {
                min = j;
            }
        }
        swap(a[i],a[min]);
    }
}

void insertionSort(int a[], int n) {
    for(int i = 0; i < n; i++) {
        int pivot = a[i];
        int j = i - 1;
        for( ; j >= 0; j--) {
            if(a[j] > pivot) {
                a[j+1] = a[j];
            }else {
                break;
            }
        }
        a[j+1] = pivot;
    }
}

void mergeSort(int *a, int start,int end) {
    if(start < end) {
        int mid = start + (end - start)/2;      
        // same as (start+end)/2 ... used this to avoid integer overflow
        mergeSort(a,0,mid);
        mergeSort(a,mid+1,end);
        merge(a,start,mid,end);
    }
}

void merge(int *a, int start,int mid,int end) {
    int *res = new int[end-start+1];
    int n = mid;
    int m = end;
    int k{0};
    int i{start}, j{mid+1};
    while(i <= n && j <= m) {
        if(a[i] < a[j])
            res[k++] = a[i++];
        else if (a[i] > a[j])
            res[k++] = a[j++];
        else {
            res[k++] = a[i++];
            res[k++] = a[j++];
        }
    }

    while(i <= n)
        res[k++] = a[i++];

    while(j <= m)
        res[k++] = a[j++];
    i = 0;
    for(int l = start; i < k; l++) {
        a[l] = res[i];
        i++;  
    }
}

void quickSort(int *a, int l, int h) {
    if(l < h) {
        int par = partition(a,l,h);
        quickSort(a,l,par);
        quickSort(a,par+1,h);
    }
}

int partition(int *a, int l, int h) {
    int pivot{a[l]};
    int i{l-1}, j{h+1};
    while(true) {
        do {
            i++;
        } while (a[i] < pivot);
        do {
            j--;
        } while (a[j] > pivot);
        if(i >= j) return j;
        swap(a[i],a[j]);
    }
}