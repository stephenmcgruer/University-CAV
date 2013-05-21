//! \author Stephen McGruer

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <cstdio>
#include <vector>

namespace computer_animation {

//! \class Matrix
//! \brief Represents an n-by-m matrix.
//!
//! Supports element access via the () operator - e.g. f(4,2)
//! to access the fourth row, second column element. Also
//! supports matrix multiplication, but not *=.
template <typename T> class Matrix {
  public:
    //! \brief Creates a rows-by-cols sized matrix.
    Matrix(int rows, int cols);

    //! \brief Returns the matrix size.
    int size() const { return num_rows_ * num_cols_; }

    //! \brief Returns the number of rows that the matrix has.
    int num_rows() const { return num_rows_; }

    //! \brief Returns the number of columns that the matrix has.
    int num_cols() const { return num_cols_; }

    //! \brief Returns the element in the row-th row, col-th column.
    T operator() (int row, int col) const;

    //! \brief Returns the element in the row-th row, col-th column.
    T& operator() (int row, int col);

    //! \brief Prints out the matrix in a (reasonably) human-readable format.
    void PrintMatrix();

    //! \brief Multiplies two matrices together.
    //!
    //! If the two matrices cannot be multiplied (i.e. if they are the wrong
    //! size), then an empty matrix is returned.
    template <typename V> friend Matrix<V> operator*(const Matrix<V>&,
        const Matrix<V>&);

  private:
    // The matrix data is stored in a flat structure.
    std::vector<T> data_;
    int num_rows_;
    int num_cols_;
};
}

#endif  // SRC_MATRIX_H_
