//
// Created by valio_stoyanov on 11/13/18.
//

#ifndef DETERMINISTIC_FINITE_AUTOMATON_DFA_H
#define DETERMINISTIC_FINITE_AUTOMATON_DFA_H

#include <set>
#include <map>
#include <vector>
#include <cassert>

template<typename AlphabetType, typename StateType>
class DFA {
  std::set<AlphabetType> alphabet_;
  std::set<StateType> states_;
  std::set<StateType> final_states_;
  StateType start_state_;
  StateType current_state_;
  std::map<std::pair<StateType, AlphabetType>, StateType> delta_;
 public:
  DFA(const std::set<AlphabetType>& alphabet,
      const StateType& start_state,
      bool final = false);
  DFA(const std::set<AlphabetType>& alphabet,
      const std::set<StateType>& states,
      const std::set<StateType>& final_states,
      const StateType& start_state,
      const std::map<std::pair<StateType, AlphabetType>, StateType>& delta);

  const std::set<AlphabetType>& GetAlphabet() const;
  const std::set<StateType>& GetStates() const;
  const std::set<StateType>& GetFinalStates() const;
  const StateType& GetStartState() const;
  const std::map<std::pair<StateType, AlphabetType>, StateType>& GetDelta() const;

  void AddState(const StateType& state, bool final = false);
  void AddTransition(const std::pair<StateType, AlphabetType>&, const StateType&);
  void AddTransition(const StateType&, AlphabetType, const StateType&);

  void Clear();

  const StateType& CurrentState() const;

  bool operator()() const;
  bool operator()(AlphabetType);
  bool operator()(const std::vector<AlphabetType>&);
};

template<typename AlphabetType, typename StateType>
DFA<AlphabetType, StateType>::DFA(const std::set<AlphabetType>& alphabet,
    const StateType& start_state,
    bool final)
    : alphabet_(alphabet), start_state_(start_state), current_state_(start_state) {
  AddState(start_state, final);
}

template<typename AlphabetType, typename StateType>
DFA<AlphabetType, StateType>::DFA(const std::set<AlphabetType>& alphabet,
               const std::set<StateType>& states,
               const std::set<StateType>& final_states,
               const StateType& start_state,
               const std::map<std::pair<StateType, AlphabetType>, StateType>& delta)
    : alphabet_(alphabet),
      states_(states),
      start_state_(start_state),
      final_states_(final_states),
      delta_(delta),
      current_state_(start_state) {}

template<typename AlphabetType, typename StateType>
void DFA<AlphabetType, StateType>::AddState(const StateType& state, bool final) {
  states_.insert(state);
  if (final) final_states_.insert(state);
}

template<typename AlphabetType, typename StateType>
void DFA<AlphabetType, StateType>::AddTransition(const std::pair<StateType, AlphabetType>& from, const StateType& to) {
  assert(alphabet_.count(from.second) > 0 && "Cannot add transition with letter that is not in the alphabet");
  assert(states_.count(from.first) && states_.count(to) && "Cannot add transition from/to non-existing state");
  delta_.insert(std::pair<std::pair<StateType, AlphabetType>, StateType>(from, to));
}

template<typename AlphabetType, typename StateType>
void DFA<AlphabetType, StateType>::AddTransition(const StateType& from_state, AlphabetType letter, const StateType& to_state) {
  AddTransition(std::pair<StateType, AlphabetType>(from_state, letter), to_state);
}

template<typename AlphabetType, typename StateType>
const StateType& DFA<AlphabetType, StateType>::CurrentState() const {
  assert(states_.size() && "CurrentState(): no states provided");
  return current_state_;
}

template<typename AlphabetType, typename StateType>
void DFA<AlphabetType, StateType>::Clear() {
  current_state_ = start_state_;
}

template<typename AlphabetType, typename StateType>
bool DFA<AlphabetType, StateType>::operator()() const {
  return final_states_.count(current_state_) > 0;
}

template<typename AlphabetType, typename StateType>
bool DFA<AlphabetType, StateType>::operator()(AlphabetType letter) {
  std::pair<StateType, AlphabetType> key(current_state_, letter);
  if (delta_.count(key)) {
    auto it = delta_.find(key);
    current_state_ = it->second;
  }
  return (*this)();
}

template<typename AlphabetType, typename StateType>
bool DFA<AlphabetType, StateType>::operator()(const std::vector<AlphabetType>& word) {
  for (auto& letter: word)
    (*this)(letter);
  return (*this)();
}

template<typename AlphabetType, typename StateType>
const std::set<AlphabetType>& DFA<AlphabetType, StateType>::GetAlphabet() const {
  return alphabet_;
}

template<typename AlphabetType, typename StateType>
const std::set<StateType>& DFA<AlphabetType, StateType>::GetStates() const {
  return states_;
}

template<typename AlphabetType, typename StateType>
const std::set<StateType>& DFA<AlphabetType, StateType>::GetFinalStates() const {
  return final_states_;
}

template<typename AlphabetType, typename StateType>
const StateType& DFA<AlphabetType, StateType>::GetStartState() const {
  return start_state_;
}

template<typename AlphabetType, typename StateType>
const std::map<std::pair<StateType, AlphabetType>, StateType>& DFA<AlphabetType, StateType>::GetDelta() const {
  return delta_;
}

#endif //DETERMINISTIC_FINITE_AUTOMATON_DFA_H
