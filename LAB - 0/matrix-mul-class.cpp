#include <iostream>
using namespace std;

class Matrix {
    public:
        Matrix(int n,int m) : n{n},m{m},a{new int*[n]}{} 
        void Input();
        void Output();
        int** Multiply(Matrix);
    private :
        int **a;
        int n, m;
};

void Matrix::Input() {
    for(int i = 0; i < this->n; i++) {
        a[i] = new int[this->m];
        for(int j = 0; j < this->m; j++) {
            cin >> a[i][j];
        }
    }
}

void Matrix::Output() {
    for(int i = 0; i < this->n; i++) {
        
        for(int j = 0; j < this->m; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int** Matrix::Multiply(Matrix mat) {
    int n1{this->n},m1{this->m};
    int n2{mat.n},m2{mat.m};

    if(m1 != n2)
        return nullptr;

    int** newMat = new int*[n1];

    for(int i = 0; i < n1; i++) {
        *(newMat+i) = new int[m2];
        for(int j = 0; j < m2; j++) {
            int temp{0};
            for(int k = 0; k < m1; k++) {
                temp += this->a[i][k] * mat.a[k][j];
            }
            newMat[i][j] = temp;
        }
    }
    return newMat;
}

int main() {
    int n1,m1,n2,m2;
    cin >> n1 >> m1;
    Matrix mat1(n1,m1);
    mat1.Input();

    cin >> n2 >> m2;
    Matrix mat2(n2,m2);
    mat2.Input();
    
    int** newMatrix = mat1.Multiply(mat2);
    if(newMatrix == nullptr) {
        cout << "Invalid Matrix Dimensions" << endl;
        return 0;
    }

    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < m2; j++) {
            cout << newMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}