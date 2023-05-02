/*******************************************************************************
\File matrix.hpp
\Author Timothy Lee Ke Xin
\Par DP email: timothykexin.lee@digipen.edu.sg
\Par Course: RSE 1202
\Par Section: matrix Class Template using DRY Principle
\Par Programming Assignment #8
\Date 22-03-2022

  \Brief
   The purpose of this laboratory is to implement a template matrix<> class 
   using the DRY (Do not Repeat Yourself) principle. This is done with vector
   class. Refer to function level documentation for function description.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <cstddef>          // need this for size_t

namespace hlp2 {

    template<typename T>
    class matrix {
    public:
        using size_type = size_t;

        matrix(size_type row, size_type col); //non-default constructor
        matrix(matrix<T> const& rhs); //copy constructor

        std::vector<T>& operator[](size_type index);
        const std::vector<T>& operator[](size_type index) const;

        void operator=(matrix<T> const& rhs);
        bool operator==(matrix<T> const& rhs) const;
        bool operator!=(matrix<T> const& rhs);
        matrix<T> operator+(matrix<T> const& rhs);
        matrix<T>& operator+=(matrix<T> const& rhs);
        matrix<T> operator-(matrix<T> const& rhs);
        matrix<T>& operator-=(matrix<T> const& rhs);
        matrix<T> operator*(matrix<T> const& rhs);

        matrix<T>& operator*=(matrix<T> const& rhs);
        matrix<T>& operator*=(T rhs);

        size_type Rows() const;
        size_type Cols() const;

     private:
        size_type rows;
        size_type cols;
        std::vector<std::vector<T>> mat;
    };

    /**************************************************************************/
    /*!
    \brief
        Non-default constructor.

    \param row
        Rows of the matrix.

    \param col
        Columns of the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T>::matrix(size_type row, size_type col):
    rows {row}, cols {col}, mat {row, std::vector<T>(col)} {}


    /**************************************************************************/
    /*!
    \brief
        Copy constructor.

    \param rhs
        Reference to the matrix.

    \param i
        Rows of the matrix.

    \param j
        Columns of the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T>::matrix(matrix<T> const& rhs):
    rows {rhs.rows}, cols {rhs.cols}, mat {rows,std::vector<T>(cols)}
     {
        for(size_type i {}; i < rows; ++i) {
            for(size_type j {}; j < cols; ++j) {
                mat[i][j] = rhs[i][j];
            }
        }
    }


    /**************************************************************************/
    /*!
    \brief
        Subscript operator overload. Returns a reference to the vector class 
        template matrix at the specified index.

    \param index
        Index, location, of the matrix element.
    */
    /**************************************************************************/
    template<typename T>
    std::vector<T>& matrix<T>::operator[](size_type index) {
        return mat[index];
    }


    /**************************************************************************/
    /*!
    \brief
        Const subscript operator overload. Returns a reference to the vector 
        class template matrix at the specified index.

    \param index
        Index, location, of the matrix element.
    */
    /**************************************************************************/
    template<typename T>
    const std::vector<T>& matrix<T>::operator[](size_type index) const {
        return mat[index];
    }


    /**************************************************************************/
    /*!
    \brief
        Copy assignment overload. Does not have a return value.

    \param rhs
        Const reference to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    void matrix<T>::operator=(matrix<T> const& rhs) {
        rows = rhs.rows;
        cols = rhs.cols;
        for(size_type i {}; i < rows; ++i) {
            for(size_type j {}; j < cols; ++j) {
                mat[i][j] = rhs[i][j]; 
            }
        }
    }


    /**************************************************************************/
    /*!
    \brief
        Const equality operator overload. Returns a bool, true or false.

    \param rhs
        Const reference to the matrix.

    \param i
        Represents the rows to the matrix.

    \param j
        Represents the columns to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    bool matrix<T>::operator==(matrix<T> const& rhs) const {
         if((rows == rhs.rows)&&(cols == rhs.cols)) {
            for(size_type i {}; i < rows; ++i) {
                for(size_type j {}; j < cols; ++j) {
                    if(mat[i][j] == rhs[i][j]) {
                        continue;
                    }
                    else {
                        return false;
                    } 
                }
            }
            return true;
        }
        else {
            return false;
        }
    }
    

    /**************************************************************************/
    /*!
    \brief
        Operator!= overload, checks if matrix are not equal. Returns a bool.

    \param rhs
        Const reference to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    bool matrix<T>::operator!=(matrix<T> const& rhs) {
        if(*this == rhs) {
            return false;
        }
        else {
            return true;
        }
    }


    /**************************************************************************/
    /*!
    \brief
        Operator+ overload, adds the matrix elements. Returns the name of the 
        matrix containing the sum of the matrices.

    \param rhs
        Const reference to the matrix.

    \param i
        Represents the rows to the matrix.

    \param j
        Represents the columns to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T> matrix<T>::operator+(matrix<T> const& rhs) {
        matrix<T> tmp(rows,cols);
        for(size_type i {}; i < rows; ++i) {
            for(size_type j {}; j < cols; ++j) {
                tmp[i][j] = mat[i][j] + rhs[i][j];
            }
        }
        return tmp;
    }


    /**************************************************************************/
    /*!
    \brief
        Operator+= overload, adds the matrix elements. Returns a reference to 
        the matrix containing the sum of the matrices.

    \param rhs
        Const reference to the matrix.

    \param i
        Represents the rows to the matrix.

    \param j
        Represents the columns to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T>& matrix<T>::operator+=(matrix<T> const& rhs) {

        for(size_type i {}; i < rows; ++i) {
            for(size_type j {}; j < cols; ++j) {
                mat[i][j] += rhs[i][j];
            }
        }
        return *this;
    }


    /**************************************************************************/
    /*!
    \brief
        Operator- overload, subtracts the matrix elements. Returns the name of 
        the matrix containing the subtracted of the matrices.

    \param rhs
        Const reference to the matrix.

    \param i
        Represents the rows to the matrix.

    \param j
        Represents the columns to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T> matrix<T>::operator-(matrix<T> const& rhs) {

        matrix<T> tmp(rows, cols);
        for(size_type i {}; i < rows; ++i) {
            for(size_type j {}; j < cols; ++j) {
                tmp[i][j] = mat[i][j] - rhs[i][j];
            }
        }
        return tmp;
    }


    /**************************************************************************/
    /*!
    \brief
        Operator-= overload, subtracts the matrix elements. Returns a reference 
        to the matrix containing the subtracted of the matrices.

    \param rhs
        Const reference to the matrix.

    \param i
        Represents the rows to the matrix.

    \param j
        Represents the columns to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T>& matrix<T>::operator-=(matrix<T> const& rhs) {

        for(size_type i {}; i < rows; ++i) {
            for(size_type j {}; j < cols; ++j) {
                mat[i][j] -= rhs[i][j];
            }
        }
        return *this;
    }


    /**************************************************************************/
    /*!
    \brief
        Operator* overload, multiplies the matrix elements. Returns the name of 
        the matrix containing the multiplied matrices.

    \param rhs
        Const reference to the matrix.

    \param i
        Represents the rows to the matrix.

    \param j
        Represents the columns to the matrix.

    \param k
        Represents the rows/columns to the other matrices.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T> matrix<T>::operator*(matrix<T> const& rhs) {

        matrix<T> tmp(rows, rhs.cols);
        for(size_type i {}; i < rows; ++i) {
            for(size_type j {}; j < rhs.cols; ++j) {
                for(size_type k {}; k < cols; ++k) {
                    tmp.mat[i][j] += mat[i][k] * rhs.mat[k][j];
                }
            }
        }
        return tmp;
    }
    

    /**************************************************************************/
    /*!
    \brief
        Operator*= overload, multiplies the matrix elements. Returns the 
        reference to the matrix containing the multiplied matrices.

    \param rhs
        Const reference to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T>& matrix<T>::operator*=(matrix<T> const& rhs) {
        *this = *this * rhs;
        return *this;
    }

    
    /**************************************************************************/
    /*!
    \brief
        Operator*= overload, multiplies the matrix elements with rhs. Returns the 
        reference to the matrix containing the multiplied matrix.

    \param rhs
        Const reference to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T>& matrix<T>::operator*=(T rhs) {
        *this = *this * rhs;
        return *this;
    }

    
    /**************************************************************************/
    /*!
    \brief
        Operator* overload, multiplies the matrix elements with rhs. Returns the 
        name of the matrix containing the multiplied matrices. This is to aid
        in the matrix class template declared operator* and operator*= 
        overloads, for matrix * typename T rhs.

    \param lhs
        Const reference to the matrix.
        
    \param rhs
        Object to be multiplied with.

    \param i
        Represents the rows to the matrix.

    \param j
        Represents the columns to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T> operator*(matrix<T>const& lhs, T rhs) {
        matrix<T> tmp(lhs.Rows(), lhs.Cols()); 

        for(typename matrix<T>::size_type i {}; i < lhs.Rows(); ++i) {
            for(typename matrix<T>::size_type j {}; j < lhs.Cols(); ++j) {
                tmp[i][j] = lhs[i][j] * rhs;
            }
        }
        return tmp;
    }

    
    /**************************************************************************/
    /*!
    \brief
        Operator* overload, multiplies the matrix elements with lhs. Returns the 
        name of the matrix containing the multiplied matrices. This is to aid
        in the matrix class template declared operator* and operator*= 
        overloads, for typename T lhs * matrix.
        
    \param lhs
        Object to be multiplied with.

    \param rhs
        Const reference to the matrix.

    \param i
        Represents the rows to the matrix.

    \param j
        Represents the columns to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T> operator*(T lhs, matrix<T>& rhs) {
        matrix<T> tmp(rhs.Rows(), rhs.Cols()); 
        for(typename matrix<T>::size_type i {}; i < rhs.Rows(); ++i) {
            for(typename matrix<T>::size_type j {}; j < rhs.Cols(); ++j) {
                tmp[i][j] = lhs * rhs[i][j];
            }
        }
        return tmp;
    }
    

    /**************************************************************************/
    /*!
    \brief
        operator<< overload for outstream printing

    \param rhs
        Const reference to the matrix.

    \param os
        Output stream reference to the object.

    \param i
        Represents the rows to the matrix.

    \param j
        Represents the columns to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    std::ostream& operator<<(std::ostream& os, matrix<T> const& rhs) {
        for(typename matrix<T>::size_type i {}; i < rhs.Rows(); ++i) {
            for(typename matrix<T>::size_type j {}; j < rhs.Cols(); ++j) {
                if(j > 0) {
                    os << " ";
                }   
                os<<rhs[i][j];
            }
            os<<"\n";
        }
        return os;
    }
    
    
    /**************************************************************************/
    /*!
    \brief
        Returns the private data of the number of rows in the matrix.
    */
    /**************************************************************************/
    template<typename T>
    typename matrix<T>::size_type matrix<T>::Rows() const {
        return rows;
    }


    /**************************************************************************/
    /*!
    \brief
        Returns the private data of the number of columns in the matrix.
    */
    /**************************************************************************/
    template<typename T>
    typename matrix<T>::size_type matrix<T>::Cols() const {
        return cols;
    }


}// end of hlp2