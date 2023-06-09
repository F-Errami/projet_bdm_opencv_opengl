#ifndef STATE_H
#define STATE_H
#include <vector>

class State{

public :
    State(int );
    int id_State;
    std::vector<std::vector<bool>> deleteMatrix;
};


#endif // STATE_H
