#ifndef QUEUE_EVENTS
#define QUEUE_EVENTS

#include "../../common/queue.h"

#include "event.h"

#include <memory> 

#define MAX_EVENTS_QUEUE 100

class QueueEvents: public Queue<std::shared_ptr<Event>> {
public:
    QueueEvents(): Queue<std::shared_ptr<Event>>(MAX_EVENTS_QUEUE) {}
    ~QueueEvents() {}
};

#endif
