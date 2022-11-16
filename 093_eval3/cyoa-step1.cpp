#include <cstdlib>
#include <iostream>

#include "page.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "error, require exactly 1 argument: <in_file_name>, exit" << std::endl;
    return EXIT_FAILURE;
  }

  try {
    Page p(argv[1]);
    std::cout << p;
  }
  catch (CustomException & e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
