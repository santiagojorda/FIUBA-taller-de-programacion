#ifndef QUEUE_GAME_STATE
#define QUEUE_GAME_STATE

#include "../../common/queue.h"

#include "game_state.h"

class QueueGameState: public Queue<GameState_t> {
public:
    QueueGameState() {}
    ~QueueGameState() {}
};

#endif
