#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    const int N = 3;
    vector<vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<vector<int>> B = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    vector<vector<int>> C(N, vector<int>(N, 0));

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];

 
    cout << "Matrix A:\n";
    for (auto& row : A) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    cout << "Matrix B:\n";
    for (auto& row : B) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    cout << "Result Matrix C = A * B:\n";
    for (auto& row : C) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    return 0;
}
