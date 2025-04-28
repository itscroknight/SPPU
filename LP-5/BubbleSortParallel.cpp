#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Parallel Bubble Sort using OpenMP (Odd-Even Transposition Sort)
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            // Even phase
            #pragma omp parallel for
            for (int j = 0; j < n-1; j += 2) {
                if (arr[j] > arr[j+1]) {
                    swap(arr[j], arr[j+1]);
                }
            }
        } else {
            // Odd phase
            #pragma omp parallel for
            for (int j = 1; j < n-1; j += 2) {
                if (arr[j] > arr[j+1]) {
                    swap(arr[j], arr[j+1]);
                }
            }
        }
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
        arr1[i] = rand() % 1000;
    }
    arr2 = arr1; // Copy for parallel sort

    // Sequential Sort
    double start = omp_get_wtime();
    sequentialBubbleSort(arr1);
    double end = omp_get_wtime();
    cout << "Time taken by Sequential Bubble Sort: " << (end - start) << " seconds" << endl;

    // Parallel Sort
    start = omp_get_wtime();
    parallelBubbleSort(arr2);
    end = omp_get_wtime();
    cout << "Time taken by Parallel Bubble Sort: " << (end - start) << " seconds" << endl;

    return 0;
}
//g++ BubbleSortParallel.cpp -fopenmp -o BubbleSortParallel

