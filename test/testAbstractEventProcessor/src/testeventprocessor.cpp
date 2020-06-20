/*!
 * @file testeventprocessor.cpp
 * @brief Class used to test AbstractEventProcessor
 * @author SignC0dingDw@rf
 * @date 12 July 2020
 *
 * Implementation of class instrumenting AbstractEventProcessor for behavior test purport. <br>
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

#include "testeventprocessor.h"
#include <iostream>

TestEventProcessor::TestEventProcessor(size_t max_element_nb, std::chrono::duration<int,std::milli> process_duration) : EventSystem::AbstractEventProcessor(max_element_nb),
    m_processed_events_number(0), m_process_duration(process_duration)
{
}

uint32_t TestEventProcessor::getProcessedEventsNumber() const
{
    return m_processed_events_number;
}

std::vector<EventSystem::EventID> TestEventProcessor::getReceivedIds() const
{
    return m_received_ids;
}

std::vector<int> TestEventProcessor::getIntEventsVal() const
{
    return m_int_event_vals;
}


std::vector<std::string> TestEventProcessor::getStrEventsVal() const
{
    return m_str_event_vals;
}


void TestEventProcessor::processEvent(std::unique_ptr<EventSystem::DwfEvent>&& event)
{
    ++m_processed_events_number;
    m_received_ids.push_back(event->getId());

    // Simulate computation duration (for saturation tests)
    std::this_thread::sleep_for(m_process_duration);

    switch(event->getId())
    {
        case 27:
        {
            IntEvent* int_ev = static_cast<IntEvent*>(event.get());
            m_int_event_vals.push_back(int_ev->getVal());
            break;
        }
        case 31:
        {
            StrEvent* str_ev = static_cast<StrEvent*>(event.get());
            m_str_event_vals.push_back(str_ev->getVal());
            break;
        }
    }
}

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
