#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

// Merge two subarrays
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Parallel Merge Sort using OpenMP
void parallelMergeSort(vector<int>& arr, int left, int right, int depth = 0) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        if (depth >= 4) {  // control the depth of parallelism
            sequentialMergeSort(arr, left, mid);
            sequentialMergeSort(arr, mid + 1, right);
        } else {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallelMergeSort(arr, left, mid, depth + 1);

                #pragma omp section
                parallelMergeSort(arr, mid + 1, right, depth + 1);
            }
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr1(n), arr2(n);
    srand(time(0));

    // Random array generation
    for (int i = 0; i < n; i++) {
        arr1[i] = rand() % 10000;
    }
    arr2 = arr1; // Copy for parallel sort

    // Sequential Sort
    double start = omp_get_wtime();
    sequentialMergeSort(arr1, 0, n-1);
    double end = omp_get_wtime();
    cout << "Time taken by Sequential Merge Sort: " << (end - start) << " seconds" << endl;

    // Parallel Sort
    start = omp_get_wtime();
    parallelMergeSort(arr2, 0, n-1);
    end = omp_get_wtime();
    cout << "Time taken by Parallel Merge Sort: " << (end - start) << " seconds" << endl;

    return 0;
}
