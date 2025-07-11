#ifndef Matrix
#define Matrix
#include <ostream>


template <typename T, int N>
// this class basically its job is to help with the double brackets
// this of it as normally need to put a vector in a vector to get this 
// to get the same outcome have to put a class in a class to achieve similar things
class MatRow {
public:
    T* row_data;
    MatRow(T* ptr) : row_data(ptr) {}

    T& operator[](int j) {
        return row_data[j];
    }

    const T& operator[](int j) const {
        return row_data[j];
    }
};

template <typename T, int M, int N>
class Mat {
public:
    

    Mat();
    Mat(const T* list);

    MatRow<T, N> operator[](int i);
    const MatRow<T, N> operator[](int i) const;

    Mat<T, M, N> operator+(const Mat<T, M, N>& other) const;
    Mat<T, M, N> operator-(const Mat<T, M, N>& other) const;
    Mat<T, M, N> operator*(T scalar) const;
    Mat<T, M, N> operator+(T scalar) const;

    // helpers
    Mat<T, 1, N> row(int i) const;
    Mat<T, M, 1> col(int i) const;

    template <int P>
    Mat<T, M, P> operator*(const Mat<T, N, P>& other) const;

    Mat<T, N, M> transpose() const;
    T length() const;

    T det();
    
    // returns the number of rows or N value
    T NVal() const;
    // returns the number of cols or M value
    T MVal() const;

    Mat<T, M, N> normalized() const;
private:
    T data[N*M];
    bool isVec;
};


template <typename T, int M, int N>
Mat<T, M, N>::Mat() {
    if(M == 1 || N == 1){
        isVec = true;
    }else{
        isVec = false;
    }
    for (int i = 0; i < M*N; i++){
        data[i] = T(0);
    }
}

template <typename T, int M, int N>
Mat<T, M, N>::Mat(const T* list) {
    if(M == 1 || N == 1){
        isVec = true;
    }else{
        isVec = false;
    }
    for (int i = 0; i < M*N; i++){
        data[i] = list[i];
    }
}

template <typename T, int M, int N>
MatRow<T, N> Mat<T, M, N>::operator[](int i) {
    return MatRow<T, N>(&data[i * N]);
}

template <typename T, int M, int N>
const MatRow<T, N> Mat<T, M, N>::operator[](int i) const {
    return MatRow<T, N>(const_cast<T*>(&data[i * N]));
}

template <typename T, int M, int N>
Mat<T, M, N> Mat<T, M, N>::operator+(const Mat<T, M, N>& other) const {
    Mat<T, M, N> result;
    for (int i = 0; i < N*M; ++i) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

template <typename T, int M, int N>
Mat<T, M, N> Mat<T, M, N>::operator+(T scalar) const {
    Mat<T, M, N> result;
    for (int i = 0; i < N*M; ++i) {
        result.data[i] = data[i] + scalar;
    }
    return result;
}

template <typename T, int M, int N>
Mat<T, M, N> Mat<T, M, N>::operator-(const Mat<T, M, N>& other) const {
    Mat<T, M, N> result;
    for (int i = 0; i < N*M; ++i) {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

template <typename T, int M, int N>
Mat<T, M, N> Mat<T, M, N>::operator*(T scalar) const {
    Mat<T, M, N> result;
    for (int i = 0; i < N*M; ++i) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

template <typename T, int M, int N>
T Mat<T, M, N>::length() const {
    return 0;
}


// These two functions M and N return the size of the matrix
template <typename T, int M, int N>
T Mat<T, M, N>::MVal() const {
    return M;
}
template <typename T, int M, int N>
T Mat<T, M, N>::NVal() const {
    return N;
}

template <typename T, int M, int N>
T Mat<T,M,N>::det() {
    if (M != N){
        return 0;
    }
    if(N == 1){
        return data[0];
    }

}

// normalizes the matrix
template <typename T, int M, int N>
Mat<T, M, N> Mat<T, M, N>::normalized() const {
    
}


// matrix matrix multiplication
template <typename T, int M, int N>
template <int P>
Mat<T, M, P> Mat<T, M, N>::operator*(const Mat<T, N, P>& other) const {
    Mat<T, M, P> results;
    T val;
    for (int w = 0; w < M; w++){
        for (int j = 0; j < P; j++){
            val = 0;
            for(int i = 0; i < N; i++){
                val += data[N*w + i] * other.data[P*i + j];
            }
            results.data[P*w + j] = val;
        }
    }
    if(M == 1 || P == 1){
        isVec = true;
    }else{
        isVec = false;
    }
    return results;
}

// helpers
template <typename T, int M, int N>
Mat<T, 1, N> Mat<T, M, N>::row(int r) const {
    Mat<T, 1, N> result;
    for (int i = 0; i < M; i++){
        result.data[i] = data[r*N + i];
    }
    return result;
}
template <typename T, int M, int N>
Mat<T, M, 1> Mat<T, M, N>::col(int c) const {
    Mat<T, M, 1> result;
    for (int i = 0; i < N; i++){
        result.data[i] = data[N*i + c];
    }
    return result;
}


// this function will transpose a matrix 
template <typename T, int M, int N>
Mat<T, N, M> Mat<T, M, N>::transpose() const {
    Mat<T, N, M> result;

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            result.data[j*M + i] = data[i*N + j];
        }
    }
    return result;
}

template <typename T, int M, int N>
std::ostream& operator<<(std::ostream& os, const Mat<T, M, N>& mat) {
    os << "Matrix: R " << M << " | C " << N << "\n";
    for (int i = 0; i < M; ++i) {
        os << "[ ";
        for (int j = 0; j < N; ++j) {
            os << mat[i][j] << " ";
        }
        os << "]\n";
    }
    return os;
}

#endif 