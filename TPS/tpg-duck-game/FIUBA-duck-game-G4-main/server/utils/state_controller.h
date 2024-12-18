#ifndef STATE_CONTROLLER_H
#define STATE_CONTROLLER_H

#include <memory>
#include "state_factory.h"
#include "state.h"

#include "../attributes/positionable.h"

class GameLogic;

template <typename T>
class StateController {
protected:
    std::shared_ptr<State<T>> current_state;
    std::shared_ptr<StateFactory<T>> state_factory;

public:
    StateController(std::shared_ptr<StateFactory<T>> _state_factory) : 
        current_state(nullptr),
        state_factory(_state_factory){}

    void set_state(const T& new_state_type){
        if (current_state) {
            current_state->finish();
        }
        
        current_state = state_factory->get(new_state_type);
        if (current_state) {
            current_state->start();
        } else { // deberia enviar una excepcion
            std::cout << "No se pudo crear el estado" << std::endl;
        }
    }

    void update(Positionable& positionable, GameLogic& game_logic, Direction& direction) {
        if (current_state) {
            current_state->update_state(positionable, game_logic, direction);
        }
    }

    bool is_in_state(const T& state_type)  const {
        return current_state && current_state->get_id() == state_type;
    }

    ~StateController(){
        // delete state_factory;
    }
    
};

#endif
