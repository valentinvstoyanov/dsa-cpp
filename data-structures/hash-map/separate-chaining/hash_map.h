//
// Created by valentinvstoyanov on 31.01.19.
//

#ifndef SEPARATE_CHAINING_HASHMAP_H
#define SEPARATE_CHAINING_HASHMAP_H

#include <vector>
#include <functional>

template<typename K, typename V, typename Hasher = std::hash<K>, typename Equal = std::equal_to<K>>
class HashMap {
  static const size_t kDefaultMapSize = 64;

  using Pair = std::pair<K, V>;
  using Chain = std::vector<Pair>;
  using Map = std::vector<Chain>;

  using ChainIt = typename Chain::iterator;
  using MapIt = typename Map::iterator;

  Map map_;
  size_t size_;
  float max_load_factor_;

  Hasher hasher_;
  Equal key_equal_;

  size_t IndexByKey(const K& key) {
    return hasher_(key) % map_.size();
  }

  MapIt ChainByKey(const K& key) {
    return map_.begin() + IndexByKey(key);
  }

  bool ShouldRehash() const {
    return LoadFactor() > max_load_factor_;
  }
 public:
  explicit HashMap(size_t n = 0, Hasher hasher = Hasher(), Equal equal = Equal())
      : map_(n == 0 ? kDefaultMapSize : n), size_(0), hasher_(hasher), key_equal_(equal), max_load_factor_(1.0) {}

  class Iterator {
    Map* map_;
    MapIt chain_;
    ChainIt element_;

    friend HashMap;

    explicit Iterator(Map& map)
        : map_(&map) {
      chain_ = map_->begin();
      element_ = chain_->begin();
      FindNextValid();
    }

    Iterator(Map& map, MapIt chain, ChainIt element)
      : map_(&map), chain_(chain), element_(element) {}

    void Increment() {
      ++element_;
      FindNextValid();
    }

    void FindNextValid() {
      if (element_ != chain_->end())
        return;

      do ++chain_;
      while (chain_ != map_->end() && chain_->empty());

      element_ = chain_ == map_->end() ? map_->back().end() : chain_->begin();
    }
   public:
    std::pair<const K, V>& operator*() const {
      return reinterpret_cast<std::pair<const K, V>&>(*element_);
    }

    std::pair<const K, V>* operator->() {
      return &(operator*());
    }

    Iterator operator++(int) {
      Iterator cpy = *this;
      Increment();
      return cpy;
    }

    Iterator& operator++() {
      Increment();
      return *this;
    }

    bool operator==(const Iterator& other) const {
      return map_ == other.map_ && chain_ == other.chain_ && element_ == other.element_;
    }

    bool operator!=(const Iterator& other) const {
      return !(*this == other);
    }
  };

  Iterator Begin() {
    return Iterator(map_);
  }

  Iterator End() {
    return Iterator(map_, map_.end(), map_.back().end());
  }

  bool Empty() const {
    return size_ == 0;
  }

  size_t Size() const {
    return size_;
  }

  float LoadFactor() const {
    return float(size_) / map_.size();
  }

  float MaxLoadFactor() const {
    return max_load_factor_;
  }

  void MaxLoadFactor(float max_load_factor) {
    max_load_factor_ = max_load_factor;
    if (ShouldRehash())
      Rehash(size_t(size_ / max_load_factor_) + 1);
  }

  size_t ChainCount() const {
    return map_.size();
  }

  void Clear() {
    map_.clear();
    size_ = 0;
  }

  void Rehash(size_t chains_count) {
    if (chains_count <= map_.size())
      return;

    Map temp_map(chains_count);
    map_.swap(temp_map);

    for (auto& chain: temp_map) {
      for (auto& element: chain)
        ChainByKey(element.first)->push_back(std::make_pair(element.first, element.second));

      chain.clear();
    }
  }

  Iterator Find(const K& key) {
    MapIt chain = ChainByKey(key);

    for (auto element_it = chain->begin(); element_it != chain->end(); ++element_it)
      if (key_equal_(key, element_it->first))
        return Iterator(map_, chain, element_it);

    return End();
  }

  Iterator Insert(const K& key, const V& value) {
    if (ShouldRehash())
      Rehash(map_.size() * 2);

    MapIt chain = ChainByKey(key);

    for (auto element_it = chain->begin(); element_it != chain->end(); ++element_it) {
      if (key_equal_(key, element_it->first)) {
        element_it->second = value;
        return Iterator(map_, chain, element_it);
      }
    }

    auto element_it = chain->insert(chain->end(), std::make_pair(key, value));
    ++size_;
    return Iterator(map_, chain, element_it);
  }

  V& operator[](const K& key) {
    auto it = Find(key);
    if (it == End()) return Insert(key, V())->second;
    return it->second;
  }

  Iterator Erase(Iterator it) {
    if (it == End())
      return it;

    it.element_ = it.chain_->erase(it.element_);
    it.FindNextValid();
    --size_;
    return it;
  }

  Iterator Erase(const K& key) {
    return Erase(Find(key));
  }
};

#endif //SEPARATE_CHAINING_HASHMAP_H
