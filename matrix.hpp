/*******************************************************************************
\File matrix.hpp
\Author Timothy Lee Ke Xin
\Par DP email: timothykexin.lee@digipen.edu.sg
\Par Course: RSE 1202
\Par Section: Adding Exceptions to matrix Class Template
\Par Programming Assignment #9
\Date 28-03-2022

  \Brief
   The purpose of this laboratory is to implement a error handling capabilities
   to the template matrix<> class which uses the DRY (Do not Repeat Yourself) 
   principle. The DRY principle is done with vector class. There are three 
   error handling classes, InvalidDimension, IndexOutOfBounds, and 
   IncompatibleMatrices. These three are rather self explanatory where the 
   first, catches the creation of a matrix with invalid dimensions (negative),
   the second, catches potential access to out of bounds elements, and the 
   third, catches for modification of matrices with different rows.
   Refer to function level documentation for function description.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <string>

namespace hlp2 {

    class InvalidDimension : public std::exception {
    private:
        int Row;
        int Column;

    public:

        /**********************************************************************/
        /*!
            \brief
            Non-default constructor using the std::istream is param to 
            initialize the private objects such that what() can determine the 
            specific error, row or column.

            \param is
            Creates a reference of the istream object.
        */
        /**********************************************************************/
        InvalidDimension(int const& r, int const& c) : Row(r), Column(c) {}
        

        /**********************************************************************/
        /*!
            \brief
            Virtual const char pointer as the return. When this function is 
            called, it returns a message to explain to the user of the type 
            of error that was caught, rather than vague abort or so message.

            \param msg
            The string message to be sent when an error is caught and the 
            function is called to explain to the user, the type of fault.
        */
        /**********************************************************************/
        virtual const char* what() const noexcept { 
            static std::string msg;
            msg = "Invalid Dimension Exception: ";

            if (Row < 0 && Column < 0) {
                msg += std::to_string(Row);
                msg += " and ";
                msg += std::to_string(Column);
                msg += " are invalid dimensions for rows and columns 
                        respectively";
                return msg.c_str();
            }
            else if (Column < 0) {
                msg += std::to_string(Column);
                msg += " is an invalid dimension for columns";
                return msg.c_str();
            }
            else { //row < 0
                msg += std::to_string(Row);
                msg += " is an invalid dimension for rows";
                return msg.c_str();
            }
        }
    };

    class IndexOutOfBounds : public std::exception {
    private:
        int Index;

    public:

        /**********************************************************************/
        /*!
            \brief
            Non-default constructor using the std::istream is param to 
            initialize the private object.

            \param is
            Creates a reference of the istream object.
        */
        /**********************************************************************/
        IndexOutOfBounds(int const& i) : Index(i) {}
        

        /**********************************************************************/
        /*!
            \brief
            Virtual const char pointer as the return. When this function is 
            called, it returns a message to explain to the user of the type 
            of error that was caught, rather than vague abort or so message.

            \param msg
            The string message to be sent when an error is caught and the 
            function is called to explain to the user, the type of fault.
        */
        /**********************************************************************/
        virtual const char* what() const noexcept { 
            static std::string msg;
            msg = "Index Out Of Bounds Exception: ";
            msg += std::to_string(Index);
            msg += " is an invalid index for rows";
            return msg.c_str();
        }
    };

    class IncompatibleMatrices : public std::exception {
    private:
        std::string operation;
        int lRows, lCols; //Left Matrix
        int rRows, rCols; //Right Matrix

    public:

        /**********************************************************************/
        /*!
            \brief
            Non-default constructor using the std::istream is param to 
            initialize the private objects such that what() can print out the 
            data for the specific error.

            \param is
            Creates a reference of the istream object.
        */
        /**********************************************************************/
        IncompatibleMatrices(std::string const& op, int const& l_r, 
                            int const& l_c, int const& r_r, int const& r_c): 
        operation(op), lRows(l_r), lCols(l_c), rRows(r_r), rCols(r_c) {}


        /**********************************************************************/
        /*!
            \brief
            Virtual const char pointer as the return. When this function is 
            called, it returns a message to explain to the user of the type 
            of error that was caught, rather than vague abort or so message.

            \param msg
            The string message to be sent when an error is caught and the 
            function is called to explain to the user, the type of fault.
        */
        /**********************************************************************/
        virtual const char* what() const noexcept { 
            static std::string msg;
            msg = "Incompatible Matrices Exception: ";
            msg += operation;
            msg += " of LHS matrix with dimensions ";
            msg += std::to_string(lRows);
            msg += " X ";
            msg += std::to_string(lCols);
            msg += " and RHS matrix with dimensions ";
            msg += std::to_string(rRows);
            msg += " X ";
            msg += std::to_string(rCols);
            msg += " is undefined";
            return msg.c_str();
        }
    };

    template<typename T>
    class matrix {
    public:
        using size_type = int;

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
        Non-default constructor. Throws an error if invalid dimensions were 
        set.

    \param row
        Rows of the matrix.

    \param col
        Columns of the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T>::matrix(size_type row, size_type col):
    rows {row}, cols {col} {
        if (rows < 0 || cols < 0)
            throw InvalidDimension{rows, cols};
        mat = {(size_t)row, std::vector<T>((size_t)col)};
    }


    /**************************************************************************/
    /*!
    \brief
        Copy constructor. Throws an error if invalid dimensions were 
        set.

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
    rows {rhs.rows}, cols {rhs.cols} {
        
        if (rows < 0 || cols < 0)
            throw InvalidDimension{rows, cols};
        
        mat = {(size_t)rhs.rows, std::vector<T>((size_t)rhs.cols)};
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
        template matrix at the specified index. Throws an error if there is 
        an attempt to access an element out of range.

    \param index
        Index, location, of the matrix element.
    */
    /**************************************************************************/
    template<typename T>
    std::vector<T>& matrix<T>::operator[](size_type index) {
        if (index < 0 || index >= rows)
            throw IndexOutOfBounds(index);
        return mat[index];
    }


    /**************************************************************************/
    /*!
    \brief
        Const subscript operator overload. Returns a reference to the vector 
        class template matrix at the specified index. Throws an error if there 
        is an attempt to access an element out of range.

    \param index
        Index, location, of the matrix element.
    */
    /**************************************************************************/
    template<typename T>
    const std::vector<T>& matrix<T>::operator[](size_type index) const {
        if (index < 0 || index >= rows)
            throw IndexOutOfBounds(index);
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
        matrix containing the sum of the matrices. Throws an error if the 
        matrices don't have the same dimensions.

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
        if (rows != rhs.rows)
            throw IncompatibleMatrices("Addition", rows, cols, 
                                        rhs.rows, rhs.cols);
        
        matrix<T> tmp(rows, cols);
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
        the matrix containing the sum of the matrices. Throws an error if the 
        matrices don't have the same dimensions.

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
        if (rows != rhs.rows)
            throw IncompatibleMatrices("Addition", rows, cols, 
                                        rhs.rows, rhs.cols);
        
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
        the matrix containing the subtracted of the matrices. Throws an error 
        if the matrices don't have the same dimensions.


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
        if (rows != rhs.rows)
            throw IncompatibleMatrices("Subtraction", rows, cols,
                                        rhs.rows, rhs.cols);

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
        to the matrix containing the subtracted of the matrices. Throws an error 
        if the matrices don't have the same dimensions.

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
        if (rows != rhs.rows)
            throw IncompatibleMatrices("Subtraction", rows, cols, 
                                        rhs.rows, rhs.cols);
        
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
        the matrix containing the multiplied matrices. Throws an error if the 
        matrices don't have the same dimensions.


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
        if (rows != rhs.rows)
            throw IncompatibleMatrices("Multiplication", rows, cols, 
                                        rhs.rows, rhs.cols);
        
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
        reference to the matrix containing the multiplied matrices. Throws an 
        error if the matrices don't have the same dimensions.


    \param rhs
        Const reference to the matrix.
    */
    /**************************************************************************/
    template<typename T>
    matrix<T>& matrix<T>::operator*=(matrix<T> const& rhs) {
        if (rows != rhs.rows)
            throw IncompatibleMatrices("Multiplication", rows, cols, 
                                        rhs.rows, rhs.cols);
        
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