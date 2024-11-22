#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
using namespace std;


#include <iostream>
using namespace std;


template<typename T>
class subvector {

T *mas;
unsigned int top;
unsigned int capacity; 

private:
    void swap(subvector<T> & rhs) {
        T* temp_mas = mas;
        unsigned int temp_top = top;
        unsigned int temp_cap = capacity;
        mas = rhs.mas;
        top = rhs.top;
        capacity = rhs.capacity;
        rhs.mas = temp_mas;
        rhs.top = temp_top;
        rhs.capacity = temp_cap;
    }

public:
    //конструктор
    subvector(): mas(nullptr), top(0), capacity(0) {
    };

    //конструктор, заполняющий value
    subvector(unsigned n, T value): top(n), capacity(2*n) {
        T* temp = new T[capacity];
        for (int i = 0; i < top; i++) {
            temp[i] = value;
        }
        mas = temp;
    }

    //деструктор
    ~subvector() {
        delete[]mas;
    }

    //конструктор копирования
    subvector(const subvector<T> &rhs) {
        top = rhs.top;
        capacity = rhs.capacity;
        T *new_mas = new T[capacity];
        for (int i = 0; i < top; i++) {
            new_mas[i] = rhs.mas[i];
        }
        mas = new_mas;
    }

    //оператор присваивания копированием
    subvector& operator= (const subvector<T> &rhs) {
        if (this != &rhs) {
            top = rhs.top;
            capacity = rhs.capacity;
            T *new_mas = new T[capacity];
            for (int i = 0; i < top; i++) {
                new_mas[i] = rhs.mas[i];
            }
            if (mas) {
                T *temp = mas;
                mas = new_mas;
                delete[]temp;
            }
            else {
                mas = new_mas;
            }

        }
        return *this;
    }

    //конструктор перемещенея 
    subvector (subvector<T>&& rhs) {
        mas = rhs.mas;
        top = rhs.top;
        capacity = rhs.capacity;
        delete[]rhs.mas;
        rhs.mas = nullptr;
        rhs.top = 0;
        rhs.capacity = 0;
    }

    //оператор присваивания перемещением
    subvector& operator= (subvector<T>&& rhs) {
        if (this != &rhs) {
            swap(rhs);
        }
        return *this;
    }

    void print_vecor() const {
        for (int i = 0; i < top; i++) {
            cout << mas[i] << " "; 
        }
        cout << endl;
    }

    unsigned int get_top() const {
        return top;
    }

    unsigned int get_capacity() const {
        return capacity;
    }

    bool push_back(const T& d) {
        if (mas) {
            if (top + 1 <= capacity) {
                mas[top++] = d;
            } else {
                capacity = capacity * 2;
                T *new_mas = new T[capacity];
                for (int i = 0; i < top; i++) {
                    new_mas[i] = mas[i];
                }
                new_mas[top++] = d;
                T *temp = mas;
                mas = new_mas;
                delete[]temp;
            }
        } else {
            capacity = (capacity + 10) * 2;
            T *new_mas = new T[capacity];
            new_mas[top++] = d;
            mas = new_mas;
        }
        return 1;
    } // добавление элемента в конец недовектора с выделением дополнительной памяти при необходимости

    T pop_back() {
        if (top) {
            top--;
            return mas[top];
        } else {
            return T();
        }
    } // удаление элемента с конца недовектора, значение удаленного элемента вернуть (если недовектор пустой, вернуть T{})
    bool resize(unsigned int new_capacity) {
        if (new_capacity > 0) {
            capacity = new_capacity;
            T *new_mas = new T[capacity];
            if (top > capacity) {
                top = capacity;
            }
            for (int i = 0; i < top; i++) {
                new_mas[i] = mas[i];
            }
            T *temp = mas;
            mas = new_mas;
            delete[]temp;
            return 1;
        } else {
            capacity = 0;
            top = 0;
            T *temp = mas;
            mas = nullptr;
            delete[]temp;
            return 0;
        } 
    } // увеличить емкость недовектора 

    void shrink_to_fit() {
        resize(top);     
    } // очистить неиспользуемую память, переехав на новое место с уменьшением capacity до top
    void clear() {
        top = 0;
    } // очистить содержимое недовектора, занимаемое место при этом не меняется

    T& operator[](int i) {
        if (i < top) {
            return mas[i];
        } else {
            return mas[top-1];
        }
    }

    T operator[](int i) const{
        if (i < top) {
            return mas[i];
        } else {
            return mas[top-1];
        }
    }
};

template<typename T>
class Matrix {
	subvector<T> data;
	unsigned int cols, rows;

private:
    Matrix getMinor(unsigned row, unsigned col) {
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

    Matrix(subvector<T> const &data, unsigned rows, unsigned cols): data(data), rows(rows), cols(cols) {}
	// создание матрицы, заполненных value
	Matrix(unsigned rows, unsigned cols, int value = 0): rows(rows), cols(cols) {
        subvector<T> temp(rows*rows, 0);
        data = temp;
    }

	// создание единичной матрицы
	static Matrix Identity(unsigned rows) {
        subvector<T> data(rows*rows, 0);
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
        subvector<T> temp(rows * cols, 0);
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
       subvector<T> temp = data;
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
    Matrix<int> M(2, 2);
    Matrix<int> m1 = Matrix<int>::getSpecificDeterminantTriangle(5, 3);
    Matrix<int> m2 = Matrix<int>::getSpecificDeterminantTriangle(10, 4);
    Matrix<int> m3 = Matrix<int>::getSpecificDeterminantSimple(50, 5);
    Matrix<int> m4 = Matrix<int>::getSpecificDeterminantSimple(100, 6);

    m1.print_matrix();

    cout << m1.getDeterminant() << endl;
    cout << m2.getDeterminant() << endl;
    cout << m3.getDeterminant() << endl;
    cout << m4.getDeterminant() << endl;
}   