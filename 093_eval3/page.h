#ifndef __PAGE_H__
#define __PAGE_H__

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

typedef std::pair<std::size_t, std::string> navigator;
typedef std::map<std::size_t, std::size_t> naviLinks;

/**
 * @brief custom exception class to raise an error
 */
class CustomException : public std::exception {
 private:
  const char * errMsg; /** custom error message */

 public:
  /**
   * default constructor
   */
  CustomException() : errMsg("error: invalid line format") {}

  /**
   * overloaded constructor
   * @param const char * _errMsg: custom error message
   */
  CustomException(const char * _errMsg) : errMsg(_errMsg) {}

  /**
   * overloaded what() method
   */
  virtual const char * what() const throw() { return this->errMsg; }
};

/**
 * @brief Page class to hold all information of a page in a story
 */
class Page {
 private:
  std::vector<navigator> navigators; /** vector to hold the page's navigation panel */
  std::vector<std::string> text;     /** vector to hold the page's story text */
  naviLinks links;                   /** vector to hold the page's link options */
  std::string result; /** if the page is a end page, set to 'WIN' or 'LOSE' */
  bool isEnd;         /** set to true if the page contains 'WIN' or 'LOSE' */

  /**
   * check the format of filename
   * must comform with pageX.txt where X is parseable integer
   * otherwise throw exceptions
   */
  void check_name_format(std::string fileName);

 public:
  /**
   * default constructor
   */
  Page() : result(""), isEnd(false) {}

  /**
   * overloaded constructor
   * @param std::string fileName: input file name
   */
  Page(std::string fileName);

  /**
   * destructor of Page class
   * all class member are trival, nothing to be done
   */
  ~Page(){};

  /**
   * get the navigation link from Page class
   */
  const naviLinks & get_navi_links() const;

  /**
   * overloaded stream insertion operator for Page class
   * @param std::ostream & stream: stream object to be overloaded
   * @param const Page & page: reference to the Page object
   * @return std::ostream & operator<<: overloaded stream insertion operator
   */
  friend std::ostream & operator<<(std::ostream & stream, const Page & page);
  friend class Story;
};

#endif
