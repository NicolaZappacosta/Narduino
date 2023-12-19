#ifndef FLIGHT_COMPUTER_STRUCTS_H
#define FLIGHT_COMPUTER_STRUCTS_H

#include "../navigation/navigation_structs.h"

enum FC_STATE{
    FC_IDLE,
    FC_RESET,
    FC_INITIALIZATION,
    FC_STATIC_TUNING,
    FC_DYNAMIC_TUNING, // implement when 9 DOF is available
    FC_NOMINAL,
    FC_AUGMENTED_NOMINAL,
};

struct STATE_MACHINE{
    FC_STATE FcState;
    NAVIGATION_STATE NavState;
};

struct FlightComputerState{
    STATE_MACHINE StateMachine;
};
#endif