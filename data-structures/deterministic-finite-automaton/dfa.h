//
// Created by valio_stoyanov on 11/13/18.
//

#ifndef DETERMINISTIC_FINITE_AUTOMATON_DFA_H
#define DETERMINISTIC_FINITE_AUTOMATON_DFA_H

#include <set>
#include <map>
#include <vector>
#include <cassert>

template<typename T, typename S>
class DFA {
  std::set<T> alphabet_;
  std::set<S> states_;
  S start_state_;
  std::set<S> final_states_;
  std::map<std::pair<S, T>, S> delta_;
  S current_state_;
 public:
  explicit DFA(const S& start_state, bool final = false);
  DFA(const std::set<T>& alphabet,
      const std::set<S>& states,
      const S& start_state,
      const std::set<S>& final_states,
      const std::map<std::pair<S, T>, S>& delta);
  void AddState(const S& state, bool final = false);
  void AddTransition(const std::pair<S, T>&, const S&);
  void AddTransition(const S&, const T&, const S&);
  const S& CurrentState() const;
  void Clear();
  bool operator()() const;
  bool operator()(const T&);
  bool operator()(const std::vector<T>&);
};

template<typename T, typename S>
DFA<T, S>::DFA(const S& start_state, bool final)
    : start_state_(start_state), current_state_(start_state) {
  AddState(start_state, final);
}

template<typename T, typename S>
DFA<T, S>::DFA(const std::set<T>& alphabet,
               const std::set<S>& states,
               const S& start_state,
               const std::set<S>& final_states,
               const std::map<std::pair<S, T>, S>& delta)
    : alphabet_(alphabet),
      states_(states),
      start_state_(start_state),
      final_states_(final_states),
      delta_(delta),
      current_state_(start_state) {}

template<typename T, typename S>
void DFA<T, S>::AddState(const S& state, bool final) {
  states_.insert(state);
  if (final) final_states_.insert(state);
}

template<typename T, typename S>
void DFA<T, S>::AddTransition(const std::pair<S, T>& from, const S& to) {
  assert(states_.count(from.first) && states_.count(to) && "Cannot add transition from/to non-existing state");
  delta_.insert(std::pair<std::pair<S, T>, S>(from, to));
}

template<typename T, typename S>
void DFA<T, S>::AddTransition(const S& from_state, const T& letter, const S& to_state) {
  AddTransition(std::pair<S, T>(from_state, letter), to_state);
}

template<typename T, typename S>
const S& DFA<T, S>::CurrentState() const {
  assert(states_.size() && "CurrentState(): no states provided");
  return current_state_;
}

template<typename T, typename S>
void DFA<T, S>::Clear() {
  current_state_ = start_state_;
}

template<typename T, typename S>
bool DFA<T, S>::operator()() const {
  return final_states_.count(current_state_) > 0;
}

template<typename T, typename S>
bool DFA<T, S>::operator()(const T& letter) {
  std::pair<S, T> key(current_state_, letter);
  if (delta_.count(key)) {
    auto it = delta_.find(key);
    current_state_ = it->second;
  }
  return (*this)();
}

template<typename T, typename S>
bool DFA<T, S>::operator()(const std::vector<T>& word) {
  for (auto& letter: word)
    (*this)(letter);
  return (*this)();
}

#endif //DETERMINISTIC_FINITE_AUTOMATON_DFA_H
