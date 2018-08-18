#include <cstdlib>
#include <iostream>
#include "Matrix.h"

int main(int argc, char *argv[])
{
  int a[1][3] = {1,1,1};
  matrix::Matrix<int,1,3> A(a);

  int b[3][1] = {{1},{1},{1}};
  matrix::Matrix<int,3,1> B(b);

  std::cout << A << std::endl;
  std::cout << B << std::endl;

  matrix::Matrix<int,1,1> C = A*B;

  std::cout << C << std::endl;


  std::cout << matrix::Matrix<int,10,10>::identity() << std::endl;

  return EXIT_SUCCESS;
}
