// #ifndef EVENT_FACTORY_h
// #define EVENT_FACTORY_h

#ifndef EVENT_FACTORY_h
#define EVENT_FACTORY_h

#include <cstdint>
#include <map>
#include <memory>

#include "../../common/action_events.h"
#include "../utils/factory.h"

#include "event.h"
#include "event_move_left.h"
#include "event_move_right.h"
#include "event_jump.h"
#include "event_crouch.h"
#include "event_trigger.h"
#include "event_trigger_out.h"
#include "event_idle.h"
#include "event_drop_gun.h"

class EventFactory{
private:

    // cppcheck-suppress unusedStructMember
    std::map<ActionEvent, std::shared_ptr<Event>> events;

    // cppcheck-suppress unusedStructMember
    uint8_t player_id;

public:
    explicit EventFactory(const uint8_t& _player_id) : player_id(_player_id) {
        events[ActionEvent::MOVE_LEFT] = std::make_shared<EventMoveLeft>(player_id);
        events[ActionEvent::MOVE_RIGHT] = std::make_shared<EventMoveRight>(player_id);
        events[ActionEvent::JUMP] = std::make_shared<EventJump>(player_id);
        events[ActionEvent::CROUCH] = std::make_shared<EventCrouch>(player_id);
        events[ActionEvent::TRIGGER] = std::make_shared<EventTrigger>(player_id);
        events[ActionEvent::TRIGGER_OUT] = std::make_shared<EventTriggerOut>(player_id);
        events[ActionEvent::IDLE] = std::make_shared<EventIdle>(player_id);
        events[ActionEvent::DROP_GUN] = std::make_shared<EventDropGun>(player_id);
    }
    
    EventFactory(const EventFactory& _other): EventFactory(_other.player_id) {}

    std::shared_ptr<Event> get(const ActionEvent& event_id) {
        return events[event_id];
    }

    ~EventFactory(){};
};

#endif  // EVENT_FACTORY_h
// // #ifndef EVENT_FACTORY_h
// // #define EVENT_FACTORY_h

// // #include <cstdint>
// // #include <map>

// // #include "../../common/action_events.h"

// // #include "event_player.h"

// // class EventFactory {
// // private:
// //     // cppcheck-suppress unusedStructMember
// //     std::map<ActionEvent, EventPlayer*> map_event;

// //     // cppcheck-suppress unusedStructMember
// //     uint8_t& player_id;

// // public:
// //     explicit EventFactory(uint8_t& _player_id);
// //     explicit EventFactory(const EventFactory& _other);

// //     EventPlayer* get(ActionEvent id_event);

// //     ~EventFactory();
// // };

// // #endif  // EVENT_FACTORY_h


// #ifndef EVENT_FACTORY_h
// #define EVENT_FACTORY_h

// #include <cstdint>
// #include <map>
// #include <memory>

// #include <iostream>

// #include "../../common/action_events.h"
// #include "../utils/factory.h"

// #include "event_player.h"
// #include "event_move_left.h"
// #include "event_move_right.h"
// #include "event_jump.h"
// #include "event_crouch.h"
// #include "event_shoot.h"
// #include "event_idle.h"

// class EventFactory : public Factory<ActionEvent, EventPlayer>{
// private:

//     // cppcheck-suppress unusedStructMember
//     uint8_t player_id;

// public:
//     explicit EventFactory(const uint8_t& _player_id) : player_id(_player_id) {
//         std::cout << "se creo un factory de player " << (int)player_id << std::endl;
//         add(ActionEvent::MOVE_LEFT,     std::make_shared<EventMoveLeft>(player_id));
//         add(ActionEvent::MOVE_RIGHT,    std::make_shared<EventMoveRight>(player_id));
//         add(ActionEvent::JUMP,          std::make_shared<EventJump>(player_id));
//         add(ActionEvent::CROUCH,        std::make_shared<EventCrouch>(player_id));
//         add(ActionEvent::SHOOT,         std::make_shared<EventShoot>(player_id));
//         add(ActionEvent::IDLE,          std::make_shared<EventIdle>(player_id));
//     }

//     void add(const ActionEvent& event_id, EventPlayer* event){
//         events[event_id] = event;
//     }

//     // Constructor de movimiento
//     EventFactory(EventFactory&& other) noexcept 
//         : Factory<ActionEvent, EventPlayer>(std::move(other)),
//         player_id(other.player_id) {}

//     EventFactory(const EventFactory&) = delete;
//     EventFactory& operator=(const EventFactory&) = delete;

//     // Operador de asignación por movimiento
//     EventFactory& operator=(EventFactory&& other) noexcept {
//         if (this != &other) {
//             Factory<ActionEvent, EventPlayer>::operator=(std::move(other));
//             // player_id = std::move(other.player_id);
//         }
//         return *this;
//     }

//     ~EventFactory() {}
// };

// #endif 
