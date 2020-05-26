#include "dwfevent.h"

DwfEvent::DwfEvent(EventID id): m_id(id)
{
}

bool DwfEvent::operator==(const DwfEvent& ref)
{
    return (m_id == ref.m_id);
}
