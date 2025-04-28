#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    int n;
    // cout << "\nName: Shriharsh Deshmukh\nRoll No.62 \t Div.A\n";
    cout << "\nEnter the size of the square matrices (e.g. 3 for 3x3): ";
    cin >> n;

    float A[n][n], B[n][n], C[n][n];

    cout << "\nEnter elements of Matrix A:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "\nEnter elements of Matrix B:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> B[i][j];

// Initialize result matrix C to zero
#pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = 0;

    double start = omp_get_wtime();

// Matrix multiplication using OpenMP
#pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];

    double end = omp_get_wtime();

    cout << "\nResultant Matrix C = A x B:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << C[i][j] << "\t";
        cout << endl;
    }

    cout << "\n Matrix multiplication done using OpenMP.";
    cout << "\n Time taken: " << end - start << " seconds\n";

    return 0;
}

// Run Commands (Ubuntu Terminal):
// g++ -fopenmp  7_HPC_application_for_AI-ML_domain.cpp -o hpc_ml
//  ./hpc_ml

// Run Commands (VS Code):
// g++ -fopenmp -o hpc_ml 7_HPC_application_for_AI-ML_domain.cpp
// .\hpc_ml

//****Output Example:****

// Enter the size of the square matrices (e.g. 3 for 3x3): 2

// Enter elements of Matrix A:
// 1 2
// 3 4

// Enter elements of Matrix B:
// 5 6
// 7 8

// Resultant Matrix C = A x B:
// 19      22
// 43      50

// Matrix multiplication done using OpenMP.
// Time taken: 0 seconds