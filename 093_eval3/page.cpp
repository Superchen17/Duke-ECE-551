#include "page.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

void Page::check_name_format(std::string fileName) {
  std::size_t dirDel = fileName.find_last_of("/");
  std::string fileNoDir = fileName.substr(dirDel + 1);

  // check if fileName has "page" as first substring
  std::size_t pageInd = fileNoDir.find("page");
  if (pageInd == std::string::npos || pageInd != 0) {
    throw CustomException("error: filename no page keyword, exit");
  }

  // check if everything between page and .txt is a number
  std::size_t periodInd = fileNoDir.find_last_of(".");
  if (periodInd == std::string::npos) {
    throw CustomException("error: filename no period, exit");
  }

  std::string pageNumStr = fileNoDir.substr(4, periodInd - 4);
  for (std::size_t i = 0; i < pageNumStr.length(); i++) {
    if (!std::isdigit(pageNumStr[i])) {
      throw CustomException("error: file page number not int, exit");
    }
  }

  // check if suffix is txt
  std::string fileSuffix = fileNoDir.substr(periodInd + 1);
  if (fileSuffix != "txt") {
    throw CustomException("error: file not txt, exit");
  }
}

Page::Page(std::string fileName) {
  check_name_format(fileName);

  std::ifstream f;
  f.open(fileName, std::ifstream::in);

  if (f.peek() == std::ifstream::traits_type::eof()) {
    throw CustomException("error: file empty, exit");
  }

  // check file open
  if (!f.is_open()) {
    throw CustomException("error: file not opened, exit");
  }

  this->isEnd = false;
  int progFlag = 0;
  std::size_t linkCounter = 1;
  std::string curr;
  std::set<std::size_t> linkNumHolder;

  while (std::getline(f, curr)) {
    if (curr[0] != '#' && (progFlag == 0 || progFlag == 2)) {
      if (progFlag == 0 && (curr.compare("WIN") == 0 || curr.compare("LOSE") == 0)) {
        this->isEnd = true;
        this->result = curr;
        progFlag = 1;
      }
      else {
        progFlag = 2;
        std::size_t delPos = curr.find(':');

        // check delimiter exists
        if (delPos == std::string::npos) {
          throw CustomException("error: navigator without colon, exit");
        }
        // check if no key
        if (delPos == 0) {
          throw CustomException("error: navigator without key, exit");
        }

        std::string naviNumStr = curr.substr(0, delPos);
        std::string naviDesc = curr.substr(delPos + 1);

        // check page number is number
        std::size_t naviNumInt = 0;
        for (std::size_t i = 0; i < naviNumStr.length(); i++) {
          if (!std::isdigit(naviNumStr[i])) {
            throw CustomException("error: navigator page not a number, exit");
          }
          naviNumInt = naviNumInt * 10 + naviNumStr[i] - '0';
        }

        std::pair<std::size_t, std::string> navi = std::make_pair(naviNumInt, naviDesc);
        this->navigators.push_back(navi);
        this->links[linkCounter] = naviNumInt;

        linkCounter++;
      }
    }
    else if (progFlag == 3 || progFlag == 4) {
      progFlag = 4;
      this->text.push_back(curr);
    }
    else if (curr[0] == '#' && (progFlag == 1 || progFlag == 2)) {
      progFlag = 3;
    }
    else {
      throw CustomException("error: other format error");
    }
  }
  f.close();
}

const naviLinks & Page::get_navi_links() const {
  return this->links;
}

std::ostream & operator<<(std::ostream & stream, const Page & page) {
  // get the story line of the page
  std::vector<std::string>::const_iterator textIt = page.text.begin();
  while (textIt != page.text.end()) {
    stream << *textIt << std::endl;
    ++textIt;
  }

  stream << std::endl;

  // check if the page is a result page (win/lose)
  if (page.isEnd) {
    if (page.result.compare("WIN") == 0) {
      stream << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (page.result.compare("LOSE") == 0) {
      stream << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    else {
      throw CustomException("error: undefined result, must be \"WIN\" or \"LOSE\"");
    }
  }
  // if not a result page, display all links
  else {
    stream << "What would you like to do?" << std::endl;
    stream << std::endl;

    naviLinks::const_iterator linksIt = page.links.begin();
    std::vector<navigator>::const_iterator naviIt = page.navigators.begin();
    while (linksIt != page.links.end()) {
      stream << " " << linksIt->first << ". " << naviIt->second << std::endl;
      ++linksIt;
      ++naviIt;
    }
  }

  return stream;
}
