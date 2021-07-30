#include <iostream>
using namespace std;

void Input(int **a, int n, int m) {
    for(int i = 0; i < n; i++) {
        a[i] = new int[m];
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
}

void Output(int** mat,int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int** Multiply(int** mat1, int** mat2, int n1, int n2, int m1, int m2) {
    if(m1 != n2)
        return nullptr;

    int** newMat = new int*[n1];

    for(int i = 0; i < n1; i++) {
        *(newMat+i) = new int[m2];
        for(int j = 0; j < m2; j++) {
            int temp{0};
            for(int k = 0; k < m1; k++) {
                temp += mat1[i][k] * mat2[k][j];
            }
            newMat[i][j] = temp;
        }
    }
    return newMat;
}

int main() {
    int n1,m1,n2,m2;
    cin >> n1 >> m1;
    int** mat1 = new int*[n1];
    Input(mat1,n1,m1);
    
    cin >> n2 >> m2;
    int** mat2 = new int*[n2];
    Input(mat2,n2,m2);

    int** newMatrix = Multiply(mat1,mat2,n1,m1,n2,m2);
    if(newMatrix == nullptr) {
        cout << "Invalid Matrix Dimensions" << endl;
        return 0;
    }

    Output(newMatrix,n1,m2);
    return 0;
}