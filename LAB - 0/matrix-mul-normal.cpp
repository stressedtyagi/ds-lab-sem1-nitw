#include <iostream>
using namespace std;

int main() {
    int n1,m1,n2,m2;
    cin >> n1 >> m1;
    int** mat1 = new int*[n1];
    for(int i = 0; i < n1; i++) {
        mat1[i] = new int[m1];
        for(int j = 0; j < m1; j++) {
            cin >> mat1[i][j];
        }
    }
    
    cin >> n2 >> m2;
    int** mat2 = new int*[n2];
    for(int i = 0; i < n2; i++) {
        mat2[i] = new int[m2];
        for(int j = 0; j < m2; j++) {
            cin >> mat2[i][j];
        }
    }

    if(m1 != n2) {
        cout << "Invalid Matrix Dimensions" << endl;
        return 0;
    }
    int** newMatrix = new int*[n1];
    for(int i = 0; i < n1; i++) {
        *(newMatrix+i) = new int[m2];
        for(int j = 0; j < m2; j++) {
            int temp{0};
            for(int k = 0; k < m1; k++) {
                temp += mat1[i][k] * mat2[k][j];
            }
            *(*(newMatrix + i) + j) = temp;
        }
    }
   

    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < m2; j++) {
            cout << newMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}