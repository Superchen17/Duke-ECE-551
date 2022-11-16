#include "story.h"

#include <fstream>
#include <map>
#include <queue>
#include <stack>
#include <string>

Story::Story(const std::string & dirName) {
  this->totalPages = 0;
  std::size_t pageNum = 1;
  std::string pageName;

  // check if the page1.txt exists
  std::string pageOneName = dirName + "/page1.txt";
  std::ifstream f;
  f.open(pageOneName, std::ifstream::in);
  if (!f.is_open()) {
    throw CustomException("error: no page1.txt, exit");
  }
  f.close();

  // find all subsequent pages, and invoke Page constructor iteratively
  while (true) {
    pageName = dirName + "/page" + std::to_string(pageNum) + ".txt";
    std::ifstream f;
    f.open(pageName, std::ifstream::in);
    if (!f.is_open()) {
      break;
    }
    f.close();

    Page page(pageName);
    this->totalPages++;
    this->content[totalPages] = page;

    pageNum++;
  }
}

void Story::add_page(const Page & page) {
  this->totalPages++;
  this->content[totalPages] = page;
}

void Story::check_links_valid() const {
  std::map<std::size_t, Page>::const_iterator contentIt = this->content.begin();
  while (contentIt != this->content.end()) {
    naviLinks pageLinks = contentIt->second.get_navi_links();

    naviLinks::const_iterator pageLinksIt = pageLinks.begin();
    while (pageLinksIt != pageLinks.end()) {
      if (this->content.find(pageLinksIt->second) == this->content.end()) {
        throw CustomException("error: link pointing to invalid page, exit");
      }
      ++pageLinksIt;
    }
    ++contentIt;
  }
}

void Story::check_page_reachable() {
  // initialize visited array to false
  bool visited[this->totalPages];
  for (std::size_t i = 0; i < this->totalPages; i++) {
    visited[i] = false;
  }

  // first page may not be referenced by any other pages
  // but should be marked as visited
  visited[0] = true;

  // iterate through all pages and record their links
  for (std::size_t i = 1; i < totalPages + 1; i++) {
    naviLinks pageLinks = this->content[i].links;
    naviLinks::iterator pageLinksIt = pageLinks.begin();
    while (pageLinksIt != pageLinks.end()) {
      // if link is not current page, and is not visited, then mark as visited
      if (visited[pageLinksIt->second - 1] == false && pageLinksIt->second != i) {
        visited[pageLinksIt->second - 1] = true;
      }

      ++pageLinksIt;
    }
  }

  // go through modified visited array, check for any unvisited pages
  for (std::size_t i = 0; i < this->totalPages; i++) {
    if (visited[i] == false) {
      throw CustomException("error: unreferenced page found, exit");
    }
  }
}

void Story::check_results_exist() {
  bool winExist = false;
  bool loseExist = false;

  for (size_t i = 1; i < this->totalPages + 1; i++) {
    if (this->content[i].isEnd && this->content[i].result.compare("WIN") == 0) {
      winExist = true;
    }
    else if (this->content[i].isEnd && this->content[i].result.compare("LOSE") == 0) {
      loseExist = true;
    }
  }

  if (winExist == false || loseExist == false) {
    throw CustomException("error: story without ending, exit");
  }
}

void Story::compute_depths() {
  // use a map to record depths
  std::map<std::size_t, int> pageDepths;

  // initialize visited array to false
  bool visited[this->totalPages];
  for (std::size_t i = 0; i < this->totalPages; i++) {
    visited[i] = false;
  }

  // use a queue to help with BFS
  // push to queue when encountering a non-visited page
  std::queue<std::size_t> q;

  // start the computation from the 1st page
  q.push(1);
  visited[0] = true;
  pageDepths[1] = 0;

  // iterate until queue is empty
  while (!q.empty()) {
    std::size_t currPage = q.front();
    q.pop();

    naviLinks pageLinks = this->content[currPage].get_navi_links();
    naviLinks::iterator pageLinksIt = pageLinks.begin();

    // when encounter a new link, check if it is non-visited
    // then record its depth, and mark as visited
    while (pageLinksIt != pageLinks.end()) {
      if (visited[pageLinksIt->second - 1] == false) {
        q.push(pageLinksIt->second);
        visited[pageLinksIt->second - 1] = true;
        pageDepths[pageLinksIt->second] = pageDepths[currPage] + 1;
      }

      ++pageLinksIt;
    }
  }

  for (std::size_t i = 1; i < this->totalPages + 1; i++) {
    if (pageDepths.find(i) != pageDepths.end()) {
      std::cout << "Page " << i << ":" << pageDepths[i] << std::endl;
    }
    else {
      std::cout << "Page " << i << " is not reachable" << std::endl;
    }
  }
}

void Story::display_solutions() {
  // a queue is used to hold a path
  // a path is made of 2 parts: all nodes along the paths, and the status of visit of all nodes
  bool hasWon = false;
  std::vector<bool> visited(this->totalPages, 0);

  typedef std::pair<std::size_t, std::size_t> node;
  typedef std::pair<std::vector<node>, std::vector<bool> > path;

  std::queue<path> q;
  std::vector<node> tempNodes;
  tempNodes.push_back(std::make_pair(1, 0));
  std::vector<bool> tempVisited = visited;
  tempVisited[0] = true;

  q.push(std::make_pair(tempNodes, tempVisited));

  while (!q.empty()) {
    path currPath = q.front();
    q.pop();

    std::vector<node> currNodes = currPath.first;
    std::vector<bool> currVisited = currPath.second;

    Page currPage = this->content[currNodes.back().first];

    // if the current path has the last node as a WIN, display
    if (currPage.isEnd && currPage.result.compare("WIN") == 0) {
      std::vector<node>::iterator currNodesIt = currNodes.begin();
      while (currNodesIt != currNodes.end() - 1) {
        std::cout << currNodesIt->first << "(" << currNodesIt->second << "),";
        ++currNodesIt;
      }
      std::cout << currNodesIt->first << "(win)";

      std::cout << std::endl;
      hasWon = true;
    }
    // otherwise, look for the last node's link
    // extend the path, update its visited status, and push back to queue
    else {
      naviLinks links = currPage.get_navi_links();
      naviLinks::iterator linksIt = links.begin();

      std::size_t changeFlag = false;
      while (linksIt != links.end()) {
        std::size_t choice = linksIt->first;
        std::size_t nextNode = linksIt->second;
        if (currVisited[nextNode - 1] == false) {
          changeFlag = true;
          tempNodes = currNodes;
          tempNodes.back().second = choice;
          tempNodes.push_back(std::make_pair(nextNode, 0));
          tempVisited = currVisited;
          tempVisited[nextNode - 1] = true;
          q.push(std::make_pair(tempNodes, tempVisited));
        }
        ++linksIt;
      }
    }
  }
  if (hasWon == false) {
    std::cout << "This story is unwinnable!" << std::endl;
  }
}

void Story::display_content() const {
  std::map<std::size_t, Page>::const_iterator contentIt = this->content.begin();

  while (contentIt != this->content.end()) {
    std::cout << contentIt->first << std::endl;
    std::cout << std::endl;
    std::cout << contentIt->second << std::endl;
    ++contentIt;
  }
}

void Story::play_game() {
  Page & curr = content[1];
  while (!curr.isEnd) {
    std::cout << curr;

    std::size_t userChoise;
    std::cin >> userChoise;

    // check if input not number
    if (!std::cin.good()) {
      throw CustomException("error: illegal user input, numbers only, exit");
    }
    // check if input not a key in link
    if (curr.links.find(userChoise) == curr.links.end()) {
      throw CustomException("error: choise not found, exit");
    }

    curr = content[curr.links[userChoise]];
  }

  std::cout << curr;
}
