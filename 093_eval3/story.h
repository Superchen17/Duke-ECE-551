#ifndef __STORY_H__
#define __STORY_H__

#include <map>

#include "page.h"

/**
 * @brief Story class to represent a playable story adventure game
 */
class Story {
 private:
  std::map<std::size_t, Page>
      content; /** a map object to hold the page number, and the page's content */
  std::size_t totalPages; /** total number of pages in the story */

 public:
  /**
   * default constructor
   * set number of pages to 0
   */
  Story() : totalPages(0) {}

  /**
   * overloaded constructor
   * @param std::string & dirName: the name of the directory
   */
  Story(const std::string & dirName);

  /**
   * destructor
   * all members trival, nothing to do
   */
  ~Story() {}

  /**
   * append a Page object to an Story object
   * @param const Page & page: Page object to be appended
   */
  void add_page(const Page & page);

  /**
   * check if all links from all pages are valid from a Story obect
   * no link should point to a non-existing page
   */
  void check_links_valid() const;

  /**
   * check if all pages are reachable from at least another page
   */
  void check_page_reachable();

  /**
   * check if result page exists,
   * at least a WIN and a LOSE page should exist
   */
  void check_results_exist();

  /**
   * compute the depth of each page in the Story object 
   * implemented with BFS
   */
  void compute_depths();

  /**
   * display all possible solutions of a Story objeect
   * implemented with BFS
   */
  void display_solutions();

  /**
   * display the content of a Story object
   */
  void display_content() const;

  /**
   * play the game, accepts user input from console or file
   */
  void play_game();
};

#endif
