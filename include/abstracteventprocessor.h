/*!
 * @file abstracteventprocessor.h
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

#ifndef ABSTRACT_EVENT_PROCESSOR_H
#define ABSTRACT_EVENT_PROCESSOR_H

#include "dwfevent.h"
#include "dwfqueue.h"
#include <memory>
#include <thread>
#include <atomic>

/*!
* @namespace EventSystem
* @brief A namespace used to regroup all elements related to envent processing systems
*/
namespace EventSystem
{
    /*! @class AbstractEventProcessor
    * @brief Class defining common fonctionnlaties to an event processor.
    *
    * Class implementing an event processor i.e. a class receiving events in a fifo and processing them in reception order.
    * Event processing starts once method start() has been called. Before that, all received events are dropped.
    * Abstract class. Should be derived to implement process_event method to define application specific event processing actions.
    *
    */
    class AbstractEventProcessor
    {
    public:
        /*!
        * @brief Constructor of AbstractEventProcessor class
        * @param max_element_nb : Max number of elements that can be stored in event queue. Default indicates no size limitation.
        *
        * Constructor of the AbstractEventProcessor class setting event queue size limitation.
        *
        */
        AbstractEventProcessor(size_t max_element_nb = DwfContainers::DwfQueue< std::unique_ptr<DwfEvent> >::C_NO_SIZE_LIMIT);

        /*!
        * @brief Destructor of AbstractEventProcessor class
        *
        * Stop event processing
        *
        */
        virtual ~AbstractEventProcessor();

        /*!
        * @brief Push an event using move semantics
        * @param event : event to push to queue
        *
        * Push an event if queue is not full.
        * If queue is full, throws an exception. And element is not moved.
        *
        */
        void pushEvent(std::unique_ptr<DwfEvent>&& event);

        /*!
         * @brief Start processing events
         *
         * Spawn the event procesing thread and allows events to be pushed in event queue.
         *
         */
        void start();

        /*!
         * @brief Stop processing events
         *
         * Stop event procssing thread and clear event queue.
         *
         */
        void stop();

    protected:
        /*!
        * @brief Process received event
        * @param event : latest event extracted from event queue
        *
        * Purely virtual method
        *
        */
        virtual void processEvent(std::unique_ptr<DwfEvent>&& event) = 0;

    private:
        DwfContainers::DwfQueue< std::unique_ptr<DwfEvent> > m_event_queue; /*!< Events queue.*/

        std::atomic<bool> m_start_event_processing; /*!< Flag indicating whether event are being processed.*/

        std::thread m_event_processing_thread; /*!< Thread processing events on reception.*/

        /*!
        * @brief Wait for events to be received to process them.
        *
        * Method run in the event processing thread.
        * Wait for events, get them from queue and process them.
        *
        */
        void waitEvents();
    };
}
#endif //ABSTRACT_EVENT_PROCESSOR_H

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
