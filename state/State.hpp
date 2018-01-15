#ifndef State_h
#define State_h

#include <iostream>
#include <map>
#include <memory>

class State {

    friend std::ostream& operator<<(std::ostream& os, const State& obj);

  private:
    const int id_;
    std::map<char, std::weak_ptr<State>> transitions_;

  public:
    State(int id);
    ~State();

    bool accepting_ = false;

    std::weak_ptr<State> nextState(char c);
    void addTransition(char c, std::weak_ptr<State> state);
    int getId();
    void print();
};

#endif
