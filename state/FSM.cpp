#include "FSM.hpp"
#include <algorithm>
#include <iostream>

FSM::FSM() {}

FSM::~FSM() { 
	//std::cout << "destroying FSM" << std::endl;
}

std::shared_ptr<State> FSM::findOrCreate(int id) {
    std::shared_ptr<State> state = 0;
    auto search = states_.find(id);
    if (search != states_.end()) {
        // already exists
        state = search->second;
    } else {
        state = std::make_shared<State>(id);
        states_.insert(std::pair<int, std::shared_ptr<State>>(id, state));
    }
    return state;
}

void FSM::addTransition(const int id, const char t, const int id2,
                        const bool accepting) {
    std::shared_ptr<State> start = findOrCreate(id);
    if (states_.size() == 1) {
        initState_ = start;
    }
    std::shared_ptr<State> end = findOrCreate(id2);
    if (accepting) {
        end->accepting_ = true;
    }
    start->addTransition(t, end);
}

bool FSM::testString(const std::string& test) {
    currentState_ = initState_;
    for (uint i = 0; i < test.size(); i++) {
        currentState_ = currentState_->nextState(test[i]).lock();
        if (currentState_ == 0) {
            return false;
        }
    }
    return currentState_->accepting_;
}

void FSM::print() {
    std::for_each(states_.begin(), states_.end(),
                  [](const std::pair<int, std::shared_ptr<State>> x) {
                      x.second->print();
                  });
}

void testString(FSM& fsm, const std::string& str) {
    std::cout << str << ": " << (fsm.testString(str) ? "accepted" : "rejected")
              << std::endl;
}

int main() {
    FSM fsm;
    fsm.addTransition(1, 'f', 2, false);
    fsm.addTransition(2, 's', 3, false);
    fsm.addTransition(2, 'i', 5, false);
    fsm.addTransition(3, 'm', 4, true);
    fsm.addTransition(4, 'f', 2, false);
    fsm.addTransition(5, 'n', 6, true);
    testString(fsm, "fsm");
    testString(fsm, "fsmfsm");
    testString(fsm, "fin");
    testString(fsm, "finlay");
    testString(fsm, "cf");
    return 0;
}
