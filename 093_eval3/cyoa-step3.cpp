#include <sys/stat.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "page.h"
#include "story.h"

void check_story_valid(Story & story) {
  story.check_links_valid();
  story.check_page_reachable();
  story.check_results_exist();
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "error: require exactly 1 argument, <dir_name>, exit" << std::endl;
    return EXIT_FAILURE;
  }

  struct stat buffer;
  std::string dirName = argv[1];

  if (stat((&dirName)->c_str(), &buffer) != 0) {
    std::cerr << "error: directory \"" << dirName << "\" does not exist, exit"
              << std::endl;
  }

  try {
    Story story(dirName);
    check_story_valid(story);
    story.compute_depths();
  }
  catch (CustomException & e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
