#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>


template<typename T>
class Matrix2D {
    T** data_ = nullptr;
    size_t n_ = 0, m_ = 0;
    static constexpr const double EPS = 1e-9;

private:
    class Matrix1D {
        size_t size_ = 0;
        T* arr_ = nullptr;
    
    public:
        Matrix1D(T* arr, size_t size): arr_(arr), size_(size) {}

        T& operator[](size_t i) const {
            if (i >= size_) { throw std::invalid_argument("Matrix1D: index out of range!"); }
            return arr_[i];
        }
    };

    // ================ support functions ================ // 
    void freeData() noexcept {
        if (data_ == nullptr) { return; }
        for (size_t i = 0; i < n_; ++i) { delete[] data_[i]; }
        delete[] data_;
        n_ = m_ = 0;
        data_ = nullptr;
    }
    
    void stealInfo(Matrix2D&& other) {
        if (this != &other) { 
            freeData(); 
            n_ = other.n_;
            m_ = other.m_;
            std::swap(data_, other.data_); 
        } 
    }

    void copyData(const Matrix2D& other) {
        if (this == &other) { return; }
        freeData();
        if (other.n_ * other.m_ == 0) { return; }

        n_ = other.n_;
        m_ = other.m_;
        data_ = new T*[n_];
        
        for (size_t i = 0; i < n_; ++i) {
            data_[i] = new T[m_];
            for (size_t j = 0; j < m_; ++j) { data_[i][j] = other.data_[i][j]; }
        }
    }

    void checkDimensionsSum(const Matrix2D& other) const {
        if (other.n_ != n_ || other.m_ != m_) {
            throw std::invalid_argument("Matrix dimensions incompatible for addition!");
        }
    }

    void checkDimensionsMul(const Matrix2D& other) const {
        if (m_ != other.n_) {
            throw std::invalid_argument("Matrix dimensions incompatible for multiplication!");
        }
    }

    void checkIndexes(size_t i, size_t j) const {
        if (i >= n_ || j >= m_) {
            throw std::invalid_argument("Matrix2D: index out of range!");
        }
    }
    // =^^^^^^^^^^^^^^= support functions =^^^^^^^^^^^^^^= // 

public:
    void initialization() noexcept {
        for (size_t i = 0; i < n_; ++i) {
            for (size_t j = 0; j < m_; ++j) {
                data_[i][j] = T{};
            }
        }
    }

    // ===================== ctor`s ====================== // 
    explicit Matrix2D(size_t n, size_t m): n_(n), m_(m) {
        if (n * m == 0) { return; }

        data_ = new T*[n_];
        for (size_t i = 0; i < n_; ++i) {
            data_[i] = new T[m_];
        }
    }

    explicit Matrix2D(size_t n = 0): Matrix2D(n, n) {}

    explicit Matrix2D(const std::vector<T>& diag): Matrix2D(diag.size(), diag.size()) {
        initialization();
        for (size_t i = 0; i < n_; ++i) { data_[i][i] = diag[i]; }
    }

    explicit Matrix2D(T* diag, size_t size): Matrix2D(size, size) {
        initialization();
        for (size_t i = 0; i < n_; ++i) { data_[i][i] = diag[i]; }
    }

    Matrix2D(Matrix2D&& other) noexcept { 
        stealInfo(std::move(other));
    }
    
    Matrix2D(const Matrix2D& other) {
        copyData(other);
    }
    // =^^^^^^^^^^^^^^^^^^^= ctor`s =^^^^^^^^^^^^^^^^^^^^= // 

    // ================ copy/move optor`s ================ // 
    Matrix2D& operator=(Matrix2D&& other) noexcept {
        stealInfo(std::move(other));
        return *this;
    }

    Matrix2D& operator=(const Matrix2D& other) {
        copyData(other);
        return *this;
    }
    // =^^^^^^^^^^^^^^= copy/move optor`s =^^^^^^^^^^^^^^= // 

    // ================ addition optor`s ================= // 
    Matrix2D operator+(const Matrix2D& other) const {
        checkDimensionsSum(other);
        
        Matrix2D result(*this);
        result += other;
        return result;
    }

    Matrix2D& operator+=(const Matrix2D& other) {
        checkDimensionsSum(other);

        for (size_t i = 0; i < n_; ++i) {
            for (size_t j = 0; j < m_; ++j) {
                data_[i][j] += other.data_[i][j];
            }
        }
        return *this;
    }

    Matrix2D operator+(T scalar) const {
        Matrix2D result(*this);
        result += scalar;
        return result;
    }

    Matrix2D& operator+=(T scalar) {
        for (size_t i = 0; i < n_; ++i) {
            for (size_t j = 0; j < m_; ++j) {
                data_[i][j] += scalar;
            }
        }
        return *this;
    }
    // =^^^^^^^^^^^^^^= addition optor`s =^^^^^^^^^^^^^^^= // 

    // ============= multiplication optor`s ============== // 
    Matrix2D operator*(const Matrix2D& other) const {
        checkDimensionsMul(other);
        
        Matrix2D result(n_, other.m_);
        result.initialization();
        for (size_t i = 0; i < n_; ++i) {
            for (size_t j = 0; j < other.m_; ++j) {
                for (size_t k = 0; k < other.n_; ++k) {
                    result.data_[i][j] += data_[i][k] * other.data_[k][j];
                }
            }
        }

        return result;
    }

    Matrix2D& operator*=(const Matrix2D& other) {
        *this = *this * other;
        return *this;
    }

    Matrix2D operator*(T scalar) const {
        Matrix2D result(*this);
        result *= scalar;
        return result;
    }

    Matrix2D& operator*=(T scalar) {
        for (size_t i = 0; i < n_; ++i) {
            for (size_t j = 0; j < m_; ++j) {
                data_[i][j] *= scalar;
            }
        }
        return *this;
    }
    // =^^^^^^^^^^^= multiplication optor`s =^^^^^^^^^^^^= // 

    bool operator==(const Matrix2D& other) const noexcept {
        if (n_ != other.n_ || m_ != other.m_) { return false; }
        
        const bool flag = std::is_floating_point<T>::value; 
        const T eps = flag ? T(EPS) : T{};

        for (size_t i = 0; i < n_; ++i) {
            for (size_t j = 0; j < m_; ++j) {
                T diff = data_[i][j] - other.data_[i][j];

                if (!flag && diff != eps) { return false; } 
                if ( flag && std::abs(diff) > eps) { return false; }
            }
        }
        return true;
    }

    bool operator!=(const Matrix2D& other) const noexcept {
        return !(*this == other);
    }

    explicit operator T() const noexcept {
        T sum = T{};
        for (size_t i = 0; i < n_; ++i) {
            for (size_t j = 0; j < m_; ++j) {
                sum += data_[i][j];
            }
        }
        return sum;
    }

    Matrix1D operator[](size_t i) {
        checkIndexes(i, 0);
        return Matrix1D(data_[i], m_);
    }

    size_t rows() const { return n_; }
    size_t cols() const { return m_; }

    ~Matrix2D() { freeData(); }

    friend std::ostream& operator<<(std::ostream& os, const Matrix2D& matrix) {
        for (size_t i = 0; i < matrix.n_; ++i) {
            for (size_t j = 0; j < matrix.m_; ++j) {
                os << matrix.data_[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};