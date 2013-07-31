/* =========================================================================
   Copyright (c) 2010-2013, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.
   Portions of this software are copyright by UChicago Argonne, LLC.

                            -----------------
                  ViennaCL - The Vienna Computing Library
                            -----------------

   Project Head:    Karl Rupp                   rupp@iue.tuwien.ac.at

   (A list of authors and contributors can be found in the PDF manual)

   License:         MIT (X11), see file LICENSE in the base directory
============================================================================= */

/*
*
*   Tutorial:  Use ViennaCL within user-defined (i.e. your own) OpenCL contexts
*
*/


//
// include necessary system headers
//
#include <iostream>
#include <string>

//
// ViennaCL includes
//
#include "viennacl/vector.hpp"
#include "viennacl/matrix.hpp"
#include "viennacl/linalg/matrix_operations.hpp"
#include "viennacl/linalg/norm_2.hpp"
#include "viennacl/linalg/prod.hpp"


// Some helper functions for this tutorial:
#include "Random.hpp"


int main()
{
  typedef float       ScalarType;

  //
  // Part 1: Allocate some CUDA memory
  //
  std::size_t size = 10;

  std::vector<ScalarType> host_x(size, 1.0);
  std::vector<ScalarType> host_y(size, 2.0);

  std::cout << "Result on host: ";
  for (std::size_t i=0; i<size; ++i)
    std::cout << host_x[i] + host_y[i] << " ";
  std::cout << std::endl;

  //
  // Part 2: Now do the same within ViennaCL
  //

  viennacl::vector<ScalarType> vcl_vec1(&(host_x[0]), size, viennacl::MAIN_MEMORY); // Third parameter specifies that this is CUDA memory rather than host memory
  viennacl::vector<ScalarType> vcl_vec2(&(host_y[0]), size, viennacl::MAIN_MEMORY); // Third parameter specifies that this is CUDA memory rather than host memory

  vcl_vec1 = viennacl::scalar_vector<ScalarType>(size, ScalarType(1.0));
  vcl_vec2 = viennacl::scalar_vector<ScalarType>(size, ScalarType(2.0));

  vcl_vec1 += vcl_vec2;

  std::cout << "Result with ViennaCL: ";
  std::cout << vcl_vec1 << std::endl;

  //
  //  That's it.
  //
  std::cout << "!!!! TUTORIAL COMPLETED SUCCESSFULLY !!!!" << std::endl;

  return 0;
}
