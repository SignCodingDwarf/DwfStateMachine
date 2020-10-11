/*!
 * @file abstracteventprocessor.cpp
 * @brief Class defining common fonctionnlaties to an event processor.
 * @author SignC0dingDw@rf
 * @date 11 October 2020
 *
 * Class implementing an event processor i.e. a class receiving events in a fifo and processing them in reception order.
 * Abstract class. Should be derived to implement process_event method to define application specific event processing actions.
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

#include "abstracteventprocessor.h"

namespace EventSystem
{
    AbstractEventProcessor::AbstractEventProcessor(size_t max_element_nb): m_event_queue(max_element_nb), m_start_event_processing(false), m_event_processing_thread()
    {
    }

    AbstractEventProcessor::~AbstractEventProcessor()
    {
        stop();
    }

    void AbstractEventProcessor::pushEvent(std::unique_ptr<DwfEvent>&& event)
    {
        if(m_start_event_processing) // Drop received events while  processing is not started
        {
            m_event_queue.push(std::move(event));
        }
    }

    void AbstractEventProcessor::start()
    {
        if(!m_start_event_processing)
        {
            m_start_event_processing = true; // Activate event procesing flag
            m_event_processing_thread = std::thread([this]{waitEvents();});
        }
    }

    void AbstractEventProcessor::stop()
    {
        if(m_start_event_processing)
        {
            m_start_event_processing = false;
            m_event_queue.clear(); // Clear event queue
            m_event_queue.disableWait(); // Force exit of queue waiting thread to unlock waiter thread

            if(m_event_processing_thread.joinable())
            {
                m_event_processing_thread.join(); // Wait for thread to complete execution
            }
        }
    }

    void AbstractEventProcessor::waitEvents()
    {
        while(m_start_event_processing) // Do wait until exit has been requested
        {
            std::unique_ptr<DwfEvent> element; // Init to nullptr
            m_event_queue.pop(element); // Wait for events

            if(element) // If we have content in element. We can have empty element if we forced exit
            {
                processEvent(std::move(element));
            }
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
