#ifndef DISJOINT_SET_DISJOINT_SET_H
#define DISJOINT_SET_DISJOINT_SET_H

#include <vector>
#include <unordered_map>

class DisjointSet {
  size_t size_;
  std::vector<size_t> parent_;
  std::vector<size_t> rank_;
 public:
  explicit DisjointSet(size_t size) : size_(size), parent_(size), rank_(size) {
    for (size_t i = 0; i < size_; ++i) {
      parent_[i] = i;
      rank_[i] = 0;
    }
  }

  size_t Find(size_t x) {
    if (parent_[x] != x) parent_[x] = Find(parent_[x]);
    return parent_[x];
  }

  void Union(size_t x, size_t y) {
    size_t x_root = Find(x);
    size_t y_root = Find(y);

    if (x_root == y_root) return;

    if (rank_[x] < rank_[y]) parent_[x_root] = y_root;
    else parent_[y_root] = x_root;

    if (rank_[x_root] == rank_[y_root])
      ++rank_[x_root];
  }

  bool SameSet(size_t x, size_t y) {
    return Find(x) == Find(y);
  }

  template <typename T>
  static std::unordered_map<T, size_t> DefaultMapping(const std::vector<T>& v) {
    std::unordered_map<T, size_t> mapping;
    for (size_t i = 0; i < v.size(); ++i)
      mapping[v[i]] = i;
    return mapping;
  }
};

#endif //DISJOINT_SET_DISJOINT_SET_H
