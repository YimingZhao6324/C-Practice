#include <iostream>
#include <vector>

using namespace std;
int a1, a2, b1, b2;

class Mat {
public:
    Mat(int rows, int cols) : m_rows(rows), m_cols(cols), m_data(rows, vector<int>(cols, 0)) {}

    void set(int row, int col, int value) {
        m_data[row][col] = value;
    }

    int get(int row, int col) const {
        return m_data[row][col];
    }

    void print() const {
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                cout << m_data[i][j] << " ";
            }
            cout << endl;
        }
    }

    const Mat operator+(const Mat& other) const {
        Mat result(m_rows, m_cols);
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                result.set(i, j, m_data[i][j] + other.get(i, j));
            }
        }
        return result;
    }

    const Mat operator-(const Mat& other) const {
        Mat result(m_rows, m_cols);
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                result.set(i, j, m_data[i][j] - other.get(i, j));
            }
        }
        return result;
    }

    const Mat operator*(const Mat& other) const {
        if (m_cols != other.m_rows) {
            cout << "Error: Matrices cannot be multiplied because of its incompatible dimensions." << endl;
            return Mat(0, 0); 
        }

        Mat result(m_rows, other.m_cols);
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < other.m_cols; ++j) {
                for (int k = 0; k < m_cols; ++k) {
                    result.set(i, j, result.get(i, j) + m_data[i][k] * other.get(k, j));
                }
            }
        }
        return result;
    }

private:
    int m_rows;
    int m_cols;
    vector<vector<int>> m_data;
};


int main() {
	Mat A(2, 2);
	A.set(0, 0, 1);
	A.set(0, 1, 1);
	A.set(1, 0, 2);
	A.set(1, 1, 2);

	Mat B(2, 2);
	B.set(0, 0, 1);
	B.set(0, 1, 1);
	B.set(1, 0, 2);
	B.set(1, 1, 4);
	
	Mat C = A + B;
	Mat D = A - B;
	Mat E = A * B;
	cout << "A + B :" << endl;
	C.print();
	cout << "A - B :" << endl;
	D.print();
	cout << "A  * B :" << endl;
	E.print();

	system("pause");
	return 0;
}
