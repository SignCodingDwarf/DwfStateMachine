/*!
 * @file abstractstatemachine.cpp
 * @brief Class representing event based state machine.
 * @author SignC0dingDw@rf
 * @date 09 August 2020
 *
 * Class representing an event based state machine.
 * In such state machines, all computations are performed when receiving an event.
 * Inherits from AbstractEventProcessor.
 * Abstract class.
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

#include "abstractstatemachine.h"

namespace DwfStateMachine
{
    AbstractStateMachine::AbstractStateMachine(DwfState initial_state, size_t max_element_nb) : EventSystem::AbstractEventProcessor(max_element_nb), m_current_state(initial_state)
    {
    }

    void AbstractStateMachine::setupAndStart()
    {
        // Setup transition map
        setupTransitionMap();

        // Start event processing
        start();
    }

    void AbstractStateMachine::processEvent(std::unique_ptr<EventSystem::DwfEvent>&& event)
    {
        EventTransitionMap ev_tr_map;
        TransitionFunction tr_function;
        bool has_transition_map=true;

        try
        {
            ev_tr_map=m_transition_map.at(m_current_state);
        }
        catch (const std::exception& e)
        {
            onDeadEndState(e);
            has_transition_map=false;
        }

        if(has_transition_map)
        {
            try
            {
                tr_function=ev_tr_map.at(*event);
            }
            catch (const std::exception&)
            {
                // If there is no transition associated with event for current state, we do nothing.
                // Indeed in some states, it is perfectly legit to choose to ignore events.
            }
            if(tr_function)
            {
                tr_function(std::move(event));
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
