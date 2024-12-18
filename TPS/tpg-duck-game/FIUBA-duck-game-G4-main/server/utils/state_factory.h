#ifndef STATE_FACTORY
#define STATE_FACTORY

#include <cstdint>

// class BulletStateType2;
// class DuckStateType2;
#include "state.h"

#include <memory>


template <typename T>
class StateFactory{
private:
    std::unordered_map<T, std::shared_ptr<State<T>>> states;
public:
    StateFactory() {}

    // Prohibir copia
    StateFactory(const StateFactory&) = delete;
    StateFactory& operator=(const StateFactory&) = delete;

    // Constructor por movimiento
    StateFactory(StateFactory&& other) noexcept
        : states(std::move(other.states)) {}

    // Operador de asignación por movimiento
    StateFactory& operator=(StateFactory&& other) noexcept {
        if (this != &other) {
            states = std::move(other.states);
        }
        return *this;
    }

    void add(const T& type_id, std::shared_ptr<State<T>> new_state) {
        states[type_id] = std::move(new_state);
    }

    std::shared_ptr<State<T>> get(const T& type_id) {
        if (states.find(type_id) != states.end()) {
            return states[type_id];
        }
        return nullptr;
    }

    virtual ~StateFactory() {
        states.clear();
    }
};



// class DuckStateFactory2 : public StateFactory<DuckStateType2> {

// public:
//     DuckStateFactory2(uint8_t _player_id)  {
//         (void)_player_id;
//         add(DuckStateType2::JUMP, std::make_shared<State>());    
//     }

//     ~DuckStateFactory2() {}
// };


// class BulletStateFactory : public StateFactory<BulletStateType2> {

// public:
//     BulletStateFactory() {}

//     ~BulletStateFactory() {}
// };
#endif
