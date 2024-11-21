#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
using namespace std;

template<typename T>
class Matrix {
	vector<T> data;
	unsigned int cols, rows;

private:
    static Matrix getMinor(unsigned row, unsigned col) {
        unsigned n = rows - 1;
        Matrix<T> M(n, n);
        int i = 0;
        int j = 0;
        while (i < n*n) {
            if (j/cols != row && j%cols != col) {
                M.data[i++] = data[j++];
            } else {
                j++;
            }
        }
        return M;
    }

public:

    Matrix(vector<T> data, unsigned rows, unsigned cols): data(data), rows(rows), cols(cols) {}
	// создание матрицы, заполненных value
	Matrix(unsigned rows, unsigned cols, int value = 0): rows(rows), cols(cols) {
        data.resize(rows*cols, value);
    }

	// создание единичной матрицы
	static Matrix Identity(unsigned rows) {
        vector<T> data;
        data.resize(rows*rows);
        int i = 0;
        int j = 0;
        while (i < rows) {
            data[i+j*rows] = 1;
            i++;
            j++;
        }
        return Matrix(data, rows, rows);
    }

	// создание случайной матрицы с заданным детерминантом
	static Matrix getSpecificDeterminantSimple(unsigned n, T determinant) {
        Matrix<T> new_matrix = Identity(n);
        int randInd = rand() % n;
        new_matrix(randInd, randInd) = determinant;
        return new_matrix;
    }

    static Matrix getSpecificDeterminantTriangle(unsigned n, T determinant) {
        Matrix<T> new_matrix = Identity(n);
        int randInd = rand() % n;
        new_matrix(randInd, randInd) = determinant;
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                new_matrix(i, j) = rand() % 5;
            }
        }
        return new_matrix;
    }
    
    void print_matrix() const {
        for (int i = 0; i < rows*cols; i++) {
            cout << data[i] << " ";
            if ((i+1) % cols == 0) {
                cout << endl;
            }
        }
        cout << endl;
    }

	unsigned int get_rows() const {
        return rows;
    }
	unsigned int get_cols() const {
        return cols;
    }

	Matrix& transpose() {
        vector<T> temp(rows * cols);
        int i = 0;
        for (unsigned i = 0; i < rows; i++) {
            for (unsigned j = 0; j < cols; j++) {
                temp[j * rows + i] = data[i * cols + j];
            }
        }
        swap(rows, cols);
        data = temp;
        return *this;
    }

	Matrix transpose() const {
       vector<T> temp = data;
       Matrix new_matrix = Matrix(temp, rows, cols);
       new_matrix.transpose();
       return new_matrix;
    }

	T& operator()(unsigned row, unsigned col) {
        return data[row*cols+col];
    }
	T operator()(unsigned row, unsigned col) const {
        return data[row*cols+col];
    }

    T getDeterminant() {
        if (rows != cols) {
            return T();
        } else {
            if (rows == 2) {
                return data[0]*data[3] - data[1]*data[2];
            } else {
                T res = 0;
                for (int i = 0; i < cols; i++) {
                    T a = data[i];
                    if (a) {
                        res += pow(-1, i) * a * (getMinor(0, i).getDeterminant());
                    }
                }
                return res;
            }
        }
    }
	
};

int main() {
    Matrix<int> m1 = Matrix<int>::getSpecificDeterminantTriangle(5, 3);
    Matrix<int> m2 = Matrix<int>::getSpecificDeterminantTriangle(10, 4);
    Matrix<int> m3 = Matrix<int>::getSpecificDeterminantSimple(50, 5);
    Matrix<int> m4 = Matrix<int>::getSpecificDeterminantSimple(100, 6);

    // m1.Matrix::print_matrix();

    cout << m1.Matrix::getDeterminant() << endl;
    cout << m2.Matrix::getDeterminant() << endl;
    cout << m3.Matrix::getDeterminant() << endl;
    cout << m4.Matrix::getDeterminant() << endl;
}   