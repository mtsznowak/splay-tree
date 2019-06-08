#include "splay.h"

int main() {
  SplayTree<int> splay;
  splay.Insert(3);
  splay.Insert(5);
  splay.Insert(2);
  splay.Insert(10);
  splay.Insert(5);
  splay.Insert(0);
  splay.Insert(7);
  splay.Insert(1);
  splay.Insert(12);
  if (splay.Contains(5)) {
    std::cout << "contains\n";
  } else {
    std::cout << "doesn't contain\n";
  }

  splay.DebugPrint();
  splay.Remove(5);

  if (splay.Contains(5)) {
    std::cout << "contains\n";
  } else {
    std::cout << "doesn't contain\n";
  }
  return 0;
}
