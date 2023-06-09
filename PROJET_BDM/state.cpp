#include "State.h"

State::State(int id){
    id_State = id;
    switch(id_State){

    case 0 :
        deleteMatrix = {
            {false, false, false, false, false, false, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false}
        }; break;
    case 1 :
        deleteMatrix = {
            {false, false, false, false, false, false, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, false, false, false, false, false},
            {false, false, true, false, false, false, false, false},
            {false, false, true, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false}
        }; break;
    case 2 :
        deleteMatrix = {
            {false, false, false, false, false, false, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, false, false, false, false},
            {false, false, true, true, false, false, false, false},
            {false, false, true, true, false, false, false, false},
            {false, false, false, true, false, false, false, false},
            {false, false, false, false, false, false, false, false}
        }; break;
    case 3 :
        deleteMatrix = {
            {false, false, false, false, false, false, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, false, false, false},
            {false, false, true, true, true, false, false, false},
            {false, false, true, true, true, false, false, false},
            {false, false, false, true, false, false, false, false},
            {false, false, false, false, false, false, false, false}
        }; break;
    case 4 :
        deleteMatrix = {
            {false, false, false, false, false, false, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, false, false, false},
            {false, false, false, true, false, false, false, false},
            {false, false, false, false, false, false, false, false}
        }; break;
    case 5 :
        deleteMatrix = {
            {false, false, false, false, false, false, false, false},
            {false, true, true, true, true, true, false, false},
            {false, true, true, true, true, true, false, false},
            {false, true, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, true, false, false},
            {false, false, true, true, true, false, false, false},
            {false, false, false, true, false, false, false, false},
            {false, false, false, false, false, false, false, false}
        }; break;
    }
}
