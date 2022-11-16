#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

void sort_and_display(std::vector<std::string> & contents) {
  std::sort(contents.begin(), contents.end());
  for (std::string s : contents) {
    std::cout << s << std::endl;
  }
}

void sort_from_file(int numFiles, char ** fileNames) {
  for (int i = 1; i < numFiles; i++) {
    std::string curr;
    std::vector<std::string> contents;

    std::ifstream f;
    f.open(fileNames[i], std::ifstream::in);
    if (!f.is_open()) {
      std::cerr << "error opening input file, exit" << std::endl;
      exit(EXIT_FAILURE);
    }

    while (std::getline(f, curr)) {
      contents.push_back(curr);
    }
    f.close();

    sort_and_display(contents);
  }
}

void sort_from_input() {
  std::string curr;
  std::vector<std::string> contents;

  while (std::getline(std::cin, curr)) {
    contents.push_back(curr);
  }

  sort_and_display(contents);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    //* read from std::cin
    sort_from_input();
  }
  else {
    //* read from file
    sort_from_file(argc, argv);
  }
  return EXIT_SUCCESS;
}
