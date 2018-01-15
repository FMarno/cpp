#ifndef FSM_h
#define FSM_h

#include "State.hpp"
#include <map>
#include <memory>

class FSM {
  private:
    std::map<int, std::shared_ptr<State>> states_;
    std::shared_ptr<State> initState_;
    std::shared_ptr<State> currentState_;
    std::shared_ptr<State> findOrCreate(int id);

  public:
    FSM();
    ~FSM();
    void addTransition(const int id, const char t, const int id2,
                       const bool accepting);
    bool testString(const std::string& test);
    void print();
};

#endif
