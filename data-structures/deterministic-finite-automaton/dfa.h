//
// Created by valio_stoyanov on 11/13/18.
//

#ifndef DETERMINISTIC_FINITE_AUTOMATON_DFA_H
#define DETERMINISTIC_FINITE_AUTOMATON_DFA_H

#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <functional>

template<typename State, typename Char = char, typename String = std::basic_string<Char>>
class DFA {
  using TransitionMap = std::unordered_map<Char, State>;
  using StateMap = std::unordered_map<State, TransitionMap>;

  using OptionalState = std::optional<State>;

  StateMap states_;
  OptionalState start_;
  std::unordered_set<State> finals_;
 public:
  bool AddState(const State& state, bool final = false) {
    auto state_it = states_.find(state);

    if (state_it != states_.end())
      return false;

    states_.insert(std::make_pair(state, TransitionMap()));

    if (final)
      finals_.insert(state);

    if (states_.size() == 1)
      start_ = state;

    return true;
  }

  bool AddTransition(const State& from, const Char& with, const State& to) {
    auto from_it = states_.find(from);

    if (from_it == states_.end() || states_.find(to) == states_.end())
      return false;

    TransitionMap& transitions = from_it->second;
    if (transitions.find(with) != transitions.end())
      return false;

    transitions.insert(std::make_pair(with, to));
    return true;
  }

  bool RemoveState(const State& state) {
    auto state_it = states_.find(state);

    if (state_it == states_.end())
      return false;

    states_.erase(state_it);
    for (state_it = states_.begin(); state_it != states_.end(); ++state_it) {
      TransitionMap& transitions = state_it->second;
      for (auto transition_it = transitions.begin(); transition_it != transitions.end(); ++transition_it) {
        if (transition_it->second == state) {
          transitions.erase(transition_it);
          break;
        }
      }
    }

    auto finals_it = finals_.find(state);
    if (finals_it != finals_.end())
      finals_.erase(finals_it);

    if (start_ && state == *start_)
      start_ = {};

    return true;
  }

  bool RemoveTransition(const State& from, const State& to) {
    auto state_it = states_.find(from);

    if (state_it == states_.end() || states_.find(to) == states_.end())
      return false;

    TransitionMap& transitions = state_it->second;
    for (auto transition_it = transitions.begin(); transition_it != transitions.end(); ++transition_it) {
      if (transition_it->second == to) {
        transitions.erase(transition_it);
        return true;
      }
    }
    return false;
  }

  bool RemoveTransition(const State& from, const Char& with) {
    auto state_it = states_.find(from);
    if (state_it == states_.end())
      return false;

    TransitionMap& transitions = state_it->second;
    auto transition_it = transitions.find(with);
    if (transition_it == transitions.end())
      return false;

    transitions.erase(transition_it);
    return true;
  }

  void SetStartState(const State& start) {
    assert(states_.find(start) != states_.end() && "To set start state you need to add it first");
    start_ = start;
  }

  OptionalState delta(const State& from, const Char& with) const {
    auto state_it = states_.find(from);
    if (state_it == states_.end())
      return {};

    const TransitionMap& transitions = state_it->second;
    auto transition_it = transitions.find(with);
    if (transition_it == transitions.end())
      return {};

    return transition_it->second;
  }

  OptionalState deltaStar(const State& from, const String& with) const {
    State current = from;

    for (size_t i = 0; i < with.size(); ++i)
      if (OptionalState next = delta(current, with[i]))
        current = *next;
      else
        return {};

    return current;
  }

  bool isFinal(const State& state) const {
    return finals_.find(state) != finals_.end();
  }

  bool Recognizes(const State& from, const String& with) const {
    OptionalState result = deltaStar(from, with);
    return result ? isFinal(*result) : false;
  }

  bool Recognizes(const String& str) const {
    assert(start_ && "No start state to begin with");
    return Recognizes(*start_, str);
  }

  bool operator()(const String& str) const {
    return Recognizes(str);
  }

  bool operator()(const State& from, const String& with) const {
    return Recognizes(from, with);
  }

  size_t StatesCount() const {
    return states_.size();
  }

  size_t FinalStatesCount() const {
    return finals_.size();
  }

  const State& StartState() const {
    assert(start_ && "No start state to return");
    return *start_;
  }
};

#endif //DETERMINISTIC_FINITE_AUTOMATON_DFA_H
