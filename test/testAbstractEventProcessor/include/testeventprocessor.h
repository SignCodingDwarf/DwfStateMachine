/*!
 * @file testeventprocessor.h
 * @brief Class used to test AbstractEventProcessor
 * @author SignC0dingDw@rf
 * @date 12 July 2020
 *
 * Definition of class instrumenting AbstractEventProcessor for behavior test purport. <br>
 * Inherits from AbstractEventProcessor
 *
 */

/*
MIT License

Copyright (c) 2020 SignC0dingDw@rf

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
Copywrong (w) 2020 SignC0dingDw@rf. All profits reserved.

This program is dwarven software: you can redistribute it and/or modify
it provided that the following conditions are met:

   * Redistributions of source code must retain the above copywrong
     notice and this list of conditions and the following disclaimer
     or you will be chopped to pieces AND eaten alive by a Bolrag.

   * Redistributions in binary form must reproduce the above copywrong
     notice, this list of conditions and the following disclaimer in
     the documentation and other materials provided with it or they
     will be axe-printed on your stupid-looking face.

   * Any commercial use of this program is allowed provided you offer
     99% of all your benefits to the Dwarven Tax Collection Guild.

   * This software is provided "as is" without any warranty and especially
     the implied warranty of merchantability or fitness to purport.
     In the event of any direct, indirect, incidental, special, examplary
     or consequential damages (including, but not limited to, loss of use;
     loss of data; beer-drowning; business interruption; goblin invasion;
     procurement of substitute goods or services; beheading; or loss of profits),
     the author and all dwarves are not liable of such damages even
     the ones they inflicted you on purpose.

   * If this program "does not work", that means you are an elf
     and are therefore too stupid to use this program.

   * If you try to copy this program without respecting the
     aforementionned conditions, then you're wrong.

You should have received a good beat down along with this program.
If not, see <http://www.dwarfvesaregonnabeatyoutodeath.com>.
*/

#ifndef TEST_EVENT_PROCESSOR_H
#define TEST_EVENT_PROCESSOR_H

#include "abstracteventprocessor.h"
#include <vector>
#include <chrono>
#include <string>

/*! @class IntEvent
* @brief Example event class with data member as int
*
* Inherits from DwfEvent
*
*/
class IntEvent : public EventSystem::DwfEvent
{
public:
    IntEvent(int val) : EventSystem::DwfEvent(27), m_val(val)
    {
    }

    int getVal() const
    {
        return m_val;
    }

private:
    int m_val; /*!< Event content.*/
};

/*! @class StrEvent
* @brief Example event class with string data member
*
* Inherits from DwfEvent
*
*/
class StrEvent : public EventSystem::DwfEvent
{
public:
    StrEvent(std::string val) : EventSystem::DwfEvent(31), m_val(val)
    {
    }

    std::string getVal() const
    {
        return m_val;
    }

private:
    std::string  m_val; /*!< Event content.*/
};

/*! @class TestEventProcessor
* @brief Class used to test AbstractEventProcessor
*
* Inherits from AbstractEventProcessor
*
*/
class TestEventProcessor : public EventSystem::AbstractEventProcessor
{
public:
    /*!
    * @brief Constructor of TestEventProcessor class
    * @param max_element_nb : Max number of elements that can be stored in event queue. Default indicates no size limitation.
    * @param process_duration : Duration of event processing. Default indicates processing takes no time.
    *
    */
    TestEventProcessor(size_t max_element_nb = DwfContainers::DwfQueue< std::unique_ptr<EventSystem::DwfEvent> >::C_NO_SIZE_LIMIT, std::chrono::duration<int,std::milli> process_duration=std::chrono::milliseconds(0));

    /*!
    * @brief Get number of processed events
    * @return Get counter of processEvent calls
    *
    * Constant method.
    *
    */
    uint32_t getProcessedEventsNumber() const;

    /*!
    * @brief Get list of received ids
    * @return List of received ids in order of reception
    *
    * Constant method.
    *
    */
    std::vector<EventSystem::EventID> getReceivedIds() const;

    /*!
    * @brief Get list of received IntEvent content
    * @return List of received IntEvent content in order of reception
    *
    * Constant method.
    *
    */
    std::vector<int> getIntEventsVal() const;

    /*!
    * @brief Get list of received StrEvent content
    * @return List of received StrEvent content in order of reception
    *
    * Constant method.
    *
    */
    std::vector<std::string> getStrEventsVal() const;

protected:
    /*!
    * @brief Process received event
    * @param event : latest event extracted from event queue
    *
    * Increments event counters and store event ids
    *
    */
    virtual void processEvent(std::unique_ptr<EventSystem::DwfEvent>&& event);

private:
    std::atomic<uint32_t> m_processed_events_number; /*!< Counter of processed events.*/

    std::vector<EventSystem::EventID> m_received_ids; /*!< Events queue.*/

    std::chrono::duration<int,std::milli> m_process_duration; /*!< Duration of event processing to simulate long computations.*/

    std::vector<int> m_int_event_vals; /*!< List of received int events values.*/

    std::vector<std::string> m_str_event_vals; /*!< List of received str event values.*/
};

#endif // TEST_EVENT_PROCESSOR_H

//  ______________________________
// |                              |
// |    ______________________    |
// |   |                      |   |
// |   |         Sign         |   |
// |   |        C0ding        |   |
// |   |        Dw@rf         |   |
// |   |         1.0          |   |
// |   |______________________|   |
// |                              |
// |______________________________|
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |__|
