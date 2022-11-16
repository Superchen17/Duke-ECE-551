#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;

  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }

  if (pq.size() == 0) {
    return NULL;
  }

  while (pq.size() > 1) {
    Node * smallest1 = pq.top();
    pq.pop();
    Node * smallest2 = pq.top();
    pq.pop();

    pq.push(new Node(smallest1, smallest2));
  }

  Node * root = pq.top();

  return root;
}
