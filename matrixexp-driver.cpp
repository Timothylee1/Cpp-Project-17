#include "matrix.hpp"
#include <string>
#include <complex>
#include <iostream>
#include <exception>
#include <array>

// declare all functions private to this file in anonymous namespace
namespace {
  void test_invaliddimension();
  void test_indexoutofbounds();
  void test_incompatibility();
  void test_functionality();
} // end anonymous namespace

int main(int argc, char **argv) {
  int constexpr num_of_tests {4};

  int test_num {0};
  if (argc > 1) {
    test_num = std::stoi(argv[1]);
    // test_num must be in range [1, num_of_tests] because we've 4 tests
    // if test_num == 0, then we run all num_of_tests tests ...
    test_num = (test_num < 0) ? 0 : (test_num > num_of_tests) ? num_of_tests : test_num;
  }

  using TPF = void (*)();
  std::array<TPF, num_of_tests> Tests {
    test_invaliddimension, // 1 - correct output is in test-invaliddimension.txt
    test_indexoutofbounds, // 2 - correct output is in test-indexoutofbounds.txt
    test_incompatibility,  // 3 - correct output is in test-incompatibility.txt
    test_functionality     // 4 - correct output is in test-functionality.txt
  };

  if (test_num == 0) { // correct output when argv[1] is "0" is in test-all.txt
    for (TPF x : Tests) {
      x();
    }
  } else if (test_num > 0 && test_num <= num_of_tests) {
    Tests[test_num - 1]();
  }
}

// define functions private to this file in anonymous namespace 
namespace {
void test_invaliddimension() {
  std::cout << "-----------TEST INVALID DIMENSION-----------\n";
  
  // check for InvalidDimension with negative rows
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = -2, cols = 2;
    hlp2::matrix<int> mm(rows, cols);
  } catch (std::exception const& e) {
    std::cout << e.what() << "\n";
  }
  
  // check for InvalidDimension with negative columns
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = 2, cols = -4;
    hlp2::matrix<int> mm(rows, cols);
  } catch (std::exception const& e) {
    std::cout << e.what() << "\n";
  }
  
  // check for InvalidDimension with negative rows and columns
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = -2, cols = -4;
    hlp2::matrix<int> mm(rows, cols);
  } catch (std::exception const& e) {
    std::cout << e.what() << "\n";
  }
}

void test_indexoutofbounds() {
  std::cout << "-----------TEST OUT-OF-BOUNDS ACCESS-----------\n";

  // check for IndexOutOfBounds by accessing out-of-bounds row mm[2][1]
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = 2, cols = 2;
    hlp2::matrix<int> mm(rows, cols);
    mm[0][0] = 1; mm[0][1] = 2;
    mm[1][0] = 3; mm[rows][1] = 4;
  } catch (hlp2::IndexOutOfBounds const& e) {
    std::cout << e.what() << "\n";
  }
  
  // check for IndexOutOfBounds by accessing out-of-bounds row
  // for const matrix: cmm[2][1]
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = 2, cols = 2;
    hlp2::matrix<int> mm(rows, cols);
    mm[0][0] = 1; mm[0][1] = 2;
    mm[1][0] = 3; mm[1][1] = 4;
    hlp2::matrix<int> const cmm(mm);
    int tmp = cmm[rows][1];
    std::cout << "cmm[2][1]: " << tmp << std::endl;
  } catch (hlp2::IndexOutOfBounds const& e) {
    std::cout << e.what() << "\n";
  }
  
  // check for IndexOutOfBounds by accessing out-of-bounds row
  // for const matrix: cmm[-1][1]
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = 2, cols = 2;
    hlp2::matrix<int> mm(rows, cols);
    mm[0][0] = 1; mm[0][1] = 2;
    mm[1][0] = 3; mm[1][1] = 4;
    hlp2::matrix<int> const cmm(mm);
    int tmp = cmm[-1][1];
    std::cout << "cmm[-2][1]: " << tmp << std::endl;
  } catch (hlp2::IndexOutOfBounds const& e) {
    std::cout << e.what() << "\n";
  }
  
  // check for IndexOutOfBounds by accessing out-of-bounds row mm[-1][1]
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = 2, cols = 2;
    hlp2::matrix<int> mm(rows, cols);
    mm[0][0] = 1; mm[0][1] = 2;
    mm[1][0] = 3; mm[-1][1] = 4;
  } catch (hlp2::IndexOutOfBounds const& e) {
    std::cout << e.what() << "\n";
  }
}

void test_incompatibility() {
  std::cout << "-----------TEST INCOMPATIBILITY-----------\n";

  // check for IncompatibleMatrices with op+= (lhs is 2x2 and rhs is 3x2)
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = 2, cols = 2;
    hlp2::matrix<int> m(rows, cols);
    m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
    hlp2::matrix<int> mm(m); // 2 x 2 matrix
    hlp2::matrix<int> nn(cols+1, cols);
    mm += nn;
  } catch (hlp2::IncompatibleMatrices const& e) {
    std::cout << e.what() << "\n";
  }
  
  // check for IncompatibleMatrices with op= (lhs is 2x2 and rhs is 3x2)
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = 2, cols = 2;
    hlp2::matrix<int> m(rows, cols);
    m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
    hlp2::matrix<int> mm(m); // 2 x 2 matrix
    hlp2::matrix<int> nn(cols+1, cols);
    hlp2::matrix<int> oo = mm + nn;
  } catch (hlp2::IncompatibleMatrices const& e) {
    std::cout << e.what() << "\n";
  }
  
  // check for IncompatibleMatrices with op-= (lhs is 2x2 and rhs is 3x2)
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = 2, cols = 2;
    hlp2::matrix<int> m(rows, cols);
    m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
    hlp2::matrix<int> mm(m); // 2 x 2 matrix
    hlp2::matrix<int> nn(cols+1, cols);
    mm -= nn;
  } catch (hlp2::IncompatibleMatrices const& e) {
    std::cout << e.what() << "\n";
  }
  
  // check for IncompatibleMatrices with op+= (lhs is 2x2 and rhs is 3x2)
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = 2, cols = 2;
    hlp2::matrix<int> m(rows, cols);
    m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
    hlp2::matrix<int> mm(m); // 2 x 2 matrix
    hlp2::matrix<int> nn(cols+1, cols);
    hlp2::matrix<int> oo = mm + nn;
  } catch (hlp2::IncompatibleMatrices const& e) {
    std::cout << e.what() << "\n";
  }
  
  // check for IncompatibleMatrices with op*= (lhs is 2x2 and rhs is 3x2)
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = 2, cols = 2;
    hlp2::matrix<int> m(rows, cols);
    m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
    hlp2::matrix<int> mm(m); // 2 x 2 matrix
    hlp2::matrix<int> nn(cols+1, cols);
    mm *= nn;
  } catch (hlp2::IncompatibleMatrices const& e) {
    std::cout << e.what() << "\n";
  }
  
  // check for IncompatibleMatrices with op* (lhs is 2x2 and rhs is 3x2)
  try {
    // size_type must be int!!!
    hlp2::matrix<int>::size_type rows = 2, cols = 2;
    hlp2::matrix<int> m(rows, cols);
    m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
    hlp2::matrix<int> mm(m); // 2 x 2 matrix
    hlp2::matrix<int> nn(cols+1, cols);
    hlp2::matrix<int> oo = mm * nn;
  } catch (hlp2::IncompatibleMatrices const& e) {
    std::cout << e.what() << "\n";
  }
}

void test_functionality() {
  std::cout << "-----------TEST MATRIX TEMPLATE CLASS-----------\n";

  // PART 1 - MATRIX OF int NUMBERS.

  // create a matrix and check its dimensions.
  hlp2::matrix<int> a(2, 4);
  std::cout << "matrix a has " << a.Rows() << " rows and " 
            << a.Cols() << " columns" << "\n\n";
  std::cout << "matrix a:" << '\n';
  std::cout << a << '\n';

  // create a 2 x 2 matrix of integers.
  hlp2::matrix<int> m(2, 2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;
  std::cout << "matrix m:" << '\n';
  std::cout << m << '\n';

  // create a const 2 x 2 matrix of integers.
  hlp2::matrix<int> const mcon(m);
  std::cout << "matrix mcon:" << '\n';
  std::cout << mcon << '\n';

  // create another 2 x 2 matrix of integers.
  hlp2::matrix<int> n(2, 2);
  n[0][0] = 3; n[0][1] = 1;
  n[1][0] = 7; n[1][1] = 2;
  std::cout << "matrix n:" << '\n';
  std::cout << n << '\n';
 
  // perform comparisons of matrices.
  hlp2::matrix<int> mCopy(2, 2);
  mCopy[0][0] = 1; mCopy[0][1] = 2;
  mCopy[1][0] = 3; mCopy[1][1] = 4;
  if (m == mCopy) {
    std::cout << "m and mCopy are equal." << '\n';
  } else {
    std::cout << "m and mCopy are NOT equal." << '\n';
  }
  if (m != n) {
    std::cout << "m and n are NOT equal." << '\n';
  } else {
    std::cout << "m and n are equal." << '\n';
  }
  std::cout << '\n';

  // add 2 matrices of integers.
  hlp2::matrix<int> iAdd = m + n;
  std::cout << "iAdd = m + n" << '\n';
  std::cout << iAdd << '\n';  

  // subtract 2 matrices of integers.
  hlp2::matrix<int> iSub = m - n;
  std::cout << "iSub = m - n" << '\n';
  std::cout << iSub << '\n';

  // multiply 2 matrices of integers.
  hlp2::matrix<int> iMul = m * n;
  std::cout << "iMul = m * n" << '\n';
  std::cout << iMul << '\n';

  // multiply a matrix of integers with an integer.
  hlp2::matrix<int> iScalarMul = 2 * m;
  std::cout << "iScalarMul = 2 * m" << '\n';
  std::cout << iScalarMul << '\n';
  iScalarMul = n * 3;
  std::cout << "iScalarMul = n * 3" << '\n';
  std::cout << iScalarMul << '\n';

  // compound addition of matrix of integers.
  m += n;
  std::cout << "m += n" << '\n';
  std::cout << m << '\n';
  std::cout << "iAdd:" << '\n';
  std::cout << iAdd << '\n';
  if (m == iAdd) {
    std::cout << "m and iAdd are equal." << '\n';
  } else {
    std::cout << "m and iAdd are NOT equal." << '\n';
  }
  std::cout << '\n';

  // compound subtraction of matrix of integers.
  m -= 2 * n;
  std::cout << "m -= 2 * n" << '\n';
  std::cout << m << '\n';
  std::cout << "iSub:" << '\n';
  std::cout << iSub << '\n';
  if (m == iSub) {
    std::cout << "m and iSub are equal." << '\n';
  } else {
    std::cout << "m and iSub are NOT equal." << '\n';
  }
  std::cout << '\n';

  // compound addition and multiplication of matrix of integers.
  m += n;
  m *= n;
  std::cout << "m += n" << '\n';
  std::cout << "m *= n" << '\n';
  std::cout << m << '\n';
  std::cout << "iMul * 2:" << '\n';
  std::cout << iMul * 2<< '\n';
  if (m != iMul) {
    std::cout << "m and iMul are NOT equal." << '\n';
  } else {
    std::cout << "m and iMul are equal." << '\n';
  }
  std::cout << '\n';

  // compound multiplication of a matrix of integers with an integer.
  m *= 10;
  std::cout << "m *= 10" << '\n';
  std::cout << m << '\n';

  // testing multiplication of non-square integer matrices
  hlp2::matrix<int> ma(2, 2);
  ma[0][0] = 1; ma[0][1] = 2;
  ma[1][0] = 3; ma[1][1] = 4;
  hlp2::matrix<int> mb(2, 3);
  mb[0][0] = 1; mb[0][1] = 2; mb[0][2] = 3;
  mb[1][0] = 4; mb[1][1] = 5; mb[1][2] = 6;

  // multiply 2 matrices of integer numbers.
  hlp2::matrix<int> mc = ma * mb;
  std::cout << "mc = ma * mb" << '\n';
  std::cout << mc << '\n';

  // PART 2 - MATRIX OF COMPLEX NUMBERS.

  // create 5 complex numbers.
  std::complex<int> c1(1, 0), c2(0, 1), c3(-1, 0), c4(0, -1), c5(1, 2);

  // create a 2 x 2 matrix of complex numbers.
  hlp2::matrix<std::complex<int>> cm(2, 2);
  cm[0][0] = c1; cm[0][1] = c2;
  cm[1][0] = c3; cm[1][1] = c4;
  std::cout << "matrix cm:" << '\n';
  std::cout << cm << '\n';

  // create another 2 x 2 matrix of complex numbers.
  hlp2::matrix<std::complex<int>> cn(2, 2);
  cn[0][0] = c2; cn[0][1] = c3;
  cn[1][0] = c4; cn[1][1] = c5;
  std::cout << "matrix cn:" << '\n';
  std::cout << cn << '\n';

  // add 2 matrices of complex numbers.
  hlp2::matrix<std::complex<int>> cAdd = cm + cn;
  std::cout << "cAdd = cm + cn" << '\n';
  std::cout << cAdd << '\n';

  // subtract 2 matrices of complex numbers.
  hlp2::matrix<std::complex<int>> cSub = cm - cn;
  std::cout << "cSub = cm - cn" << '\n';
  std::cout << cSub << '\n';

  // multiply 2 matrices of complex numbers.
  hlp2::matrix<std::complex<int>> cMul = cm * cn;
  std::cout << "cMul = cm * cn" << '\n';
  std::cout << cMul << '\n';

  // create 2 complex numbers.
  std::complex<int> cScalar1(4, 0);
  std::complex<int> cScalar2(5, 0);
  // multiply a complex number with a matrix of complex numbers.
  hlp2::matrix<std::complex<int>> cScalarMul = cScalar1 * cm;
  std::cout << "cScalarMul = 4 * cm" << '\n';
  std::cout << cScalarMul << '\n';
  cScalarMul = cn * cScalar2;
  std::cout << "cScalarMul = cn * 5" << '\n';
  std::cout << cScalarMul << '\n';

  // compound addition of matrix of complex numbers.
  cm += cn;
  std::cout << "cm += cn" << '\n';
  std::cout << cm << '\n';
  std::cout << "cAdd:" << '\n';
  std::cout << cAdd << '\n';
  if (cm == cAdd) {
    std::cout << "cm and cAdd are equal." << '\n';
  } else {
    std::cout << "cm and cAdd are NOT equal." << '\n';
  }
  std::cout << '\n';

  // compound subtraction of matrix of complex numbers.
  std::complex<int> cScalar3 = 2;
  cm -= cScalar3 * cn;
  std::cout << "cm -= 2 * cn" << '\n';
  std::cout << cm << '\n';
  std::cout << "cSub:" << '\n';
  std::cout << cSub << '\n';
  if (cm == cSub) {
    std::cout << "cm and cSub are equal." << '\n';
  } else {
    std::cout << "cm and cSub are NOT equal." << '\n';
  }
  std::cout << '\n';

  // compound addition and multiplication of matrix of complex numbers.
  cm += cn;
  cm *= cn;
  std::cout << "cm += cn" << '\n';
  std::cout << "cm *= cn" << '\n';
  std::cout << "cm:\n" << cm << '\n';
  std::cout << "cMul:" << '\n';
  std::cout << cMul << '\n';
  if (cm != cMul) {
    std::cout << "cm and cMul are NOT equal." << '\n';
  } else {
    std::cout << "cm and cMul are equal." << '\n';
  }
  std::cout << '\n';

  // compound multiplication of matrix of complex numbers with a complex number.
  std::complex<int> cScalar4(10, 0);
  cm *= cScalar4;
  std::cout << "cm *= 10" << '\n';
  std::cout << cm << '\n';

  // PART 3 - MATRIX OF std::string

  // create a 3 x 3 matrix of std::strings.
  hlp2::matrix<std::string> ms1(3, 3);
  std::cout << "matrix ms1:" << '\n';
  std::cout << ms1 << '\n';

  ms1[0][0] = "ab"; ms1[0][1] = "bc"; ms1[0][2] = "cd";
  ms1[1][0] = "de"; ms1[1][1] = "ef"; ms1[1][2] = "fg";
  ms1[2][0] = "gh"; ms1[2][1] = "hi"; ms1[2][2] = "ij";
  std::cout << "matrix ms1:" << '\n';
  std::cout << ms1 << '\n';
  std::cout << '\n';

  // copy construct a 3 x 3 matrix of std::strings
  hlp2::matrix<std::string> const ms2(ms1);
  std::cout << "ms2 has " << ms2.Rows() << " rows and " << ms2.Cols()
            << " columns.\n";
  if (ms2 == ms1) {
    std::cout << "ms1 and ms2 are equal." << '\n';
  } else {
    std::cout << "ms1 and ms2 are NOT equal." << '\n';
  }
  std::cout << '\n';

  // add two 3 x 3 matrices with elements of type std::strings
  hlp2::matrix<std::string> ms3 = ms1 + ms2;
  std::cout << "matrix ms3:" << '\n';
  std::cout << ms3;
}

} // end anonymous namespace
