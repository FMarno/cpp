#include "State.hpp"
#include <algorithm>
State::State(int id) : id_(id) {
    // std::cout << "creating state " << id_ << std::endl;
}

State::~State() {
    // std::cout << "destroying state " << id_ << std::endl;
}

std::weak_ptr<State> State::nextState(char c) {
    auto search = transitions_.find(c);
    return search->second;
}

void State::addTransition(char c, std::weak_ptr<State> state) {
    transitions_.insert(std::pair<char, std::weak_ptr<State>>(c, state));
}

int State::getId() { return id_; }

void State::print() {
    std::for_each(transitions_.begin(), transitions_.end(),
                  [this](const std::pair<char, std::weak_ptr<State>> x) {
                      std::cout << id_ << "\t" << x.first << "\t"
                                << *(x.second.lock()) << std::endl;
                  });
}

std::ostream& operator<<(std::ostream& os, const State& obj) {
    os << obj.id_;
    return os;
}
