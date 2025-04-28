#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int minVal = arr[0];
    int maxVal = arr[0];
    long long sum = 0;

    // Parallel Reduction
    #pragma omp parallel for reduction(min:minVal) reduction(max:maxVal) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal)
            minVal = arr[i];
        if (arr[i] > maxVal)
            maxVal = arr[i];
        sum += arr[i];
    }

    double average = (double)sum / n;

    cout << "Minimum value: " << minVal << endl;
    cout << "Maximum value: " << maxVal << endl;
    cout << "Sum of elements: " << sum << endl;
    cout << "Average of elements: " << average << endl;

    return 0;
}
