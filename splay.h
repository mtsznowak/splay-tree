#pragma once
#include <iostream>

template <typename T>
struct SplayNode {
  SplayNode* left;
  SplayNode* right;
  SplayNode* parent;
  T value;
};

template <typename T>
class SplayTree {
 public:
  bool Contains(T value);
  void Insert(T value);
  void Remove(T value);
  void DebugPrint();

 private:
  SplayNode<T>* root_ = nullptr;
  void Splay(SplayNode<T>* node);
  void Rotate(SplayNode<T>* node);
  void DebugPrintPriv(SplayNode<T>* c);
};

template <typename T>
bool SplayTree<T>::Contains(T value) {
  SplayNode<T>* cur = root_;

  if (root_ == nullptr) {
    return false;
  }

  if (root_->value == value) {
    return true;
  }

  while (cur->value != value) {
    if (value > cur->value) {
      if (!cur->right) {
        break;
      }
      cur = cur->right;
    } else {
      if (!cur->left) {
        break;
      }
      cur = cur->left;
    }
  }

  Splay(cur);

  return root_->value == value;
}

template <typename T>
void SplayTree<T>::Insert(T value) {
  if (!Contains(value)) {
    SplayNode<T>* newNode = new SplayNode<T>();
    newNode->value = value;
    newNode->parent = nullptr;

    if (root_ && root_->value > value) {
      newNode->left = root_->left;
      newNode->right = root_;
      if (newNode->left) {
        newNode->left->parent = newNode;
      }
      newNode->right->parent = newNode;
      newNode->right->left = nullptr;
    } else if (root_) {
      newNode->right = root_->right;
      newNode->left = root_;
      newNode->left->parent = newNode;
      if (newNode->right) {
        newNode->right->parent = newNode;
      }
      newNode->left->right = nullptr;
    }

    root_ = newNode;
  }
}

template <typename T>
void SplayTree<T>::Remove(T value) {
  if (Contains(value)) {
    SplayNode<T>* left = root_->left;
    SplayNode<T>* right = root_->right;
    delete root_;
    if (!left) {
      root_ = right;
      right->parent = nullptr;
    } else if (!right) {
      root_ = left;
      left->parent = nullptr;
    } else {
      left->parent = nullptr;
      root_ = left;
      Contains(right->value);
      right->parent = root_;
      root_->right = right;
    }
  }
}

template <typename T>
void SplayTree<T>::Splay(SplayNode<T>* node) {
  while (node != root_) {
    if (node->parent == root_) {
      Rotate(node);
    } else if ((node == node->parent->left) ==
               (node->parent < node->parent->parent->left)) {
      Rotate(node->parent);
      Rotate(node);
    } else {
      Rotate(node);
      Rotate(node);
    }
  }
}

template <typename T>
void SplayTree<T>::Rotate(SplayNode<T>* node) {
  if (node == root_) {
    return;
  }

  SplayNode<T>* parent = node->parent;
  SplayNode<T>* gparent = parent->parent;
  if (node == node->parent->left) {
    if (node->right) {
      node->right->parent = parent;
    }

    parent->left = node->right;
    parent->parent = node;

    node->parent = gparent;
    node->right = parent;
  } else {
    if (node->left) {
      node->left->parent = parent;
    }

    parent->right = node->left;
    parent->parent = node;

    node->parent = gparent;
    node->left = parent;
  }

  if (root_ == parent) {
    root_ = node;
  } else {
    if (gparent->right == parent) {
      gparent->right = node;
    } else {
      gparent->left = node;
    }
  }
}

template <typename T>
void SplayTree<T>::DebugPrint() {
  std::cout << "[";
  DebugPrintPriv(root_);
  std::cout << "]\n";
}

template <typename T>
void SplayTree<T>::DebugPrintPriv(SplayNode<T>* c) {
  if (c == nullptr) {
    return;
  }
  DebugPrintPriv(c->left);
  std::cout << c->value << ", ";
  DebugPrintPriv(c->right);
}
