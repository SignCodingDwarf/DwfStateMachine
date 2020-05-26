#ifndef DWFEVENT_H
#define DWFEVENT_H

#include <stdint.h>

typedef uint32_t EventID; // Definition of type used to identify events

class DwfEvent
{
public:
    DwfEvent(EventID id);

    bool operator==(const DwfEvent& ref);

protected:
    EventID m_id;
};

#endif // DWFEVENT_H
