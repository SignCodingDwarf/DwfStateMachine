/*!
 * @file abstractstatemachine.h
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

#ifndef DWF_STATE_MACHINE_H
#define DWF_STATE_MACHINE_H

#include "dwfstate.h"
#include "abstracteventprocessor.h"
#include <unordered_map>
#include <functional>

/*!
* @namespace DwfStateMachine
* @brief A namespace used to regroup all elements related to state machines
*/
namespace DwfStateMachine
{
    /*! @class AbstractStateMachine
    * @brief Class representing event based state machine.
    *
    * Class representing an event based state machine.
    * On event reception, computations are performed by a transition function called from a map with entries being event type and current state.
    * Inherits from AbstractEventProcessor.
    * Abstract class. You must derive it and fill the table of transitions
    *
    * Call behavior of a daughter class should be
    * - DaughterStateMachine state_mach(<initial_state>);
    * - state_mach.setupAndStart();
    *
    * You must redefine the function setupTransitionMap() to construct the desired transition map during setupAndStart phase.
    *
    * You must redefine the function onDeadEndState() which defines the class behavior if a state has no associated transition
    * (i.e. m_transition_map.at(state) throws an exception).
    *
    */
    class AbstractStateMachine : public EventSystem::AbstractEventProcessor
    {
    public:
        /*! @typedef TransitionFunction
        *  @brief Signature of a transition function
        */
        using TransitionFunction = std::function<void(std::unique_ptr<EventSystem::DwfEvent>&&)>;

        /*! @typedef EventTransitionMap
        *  @brief Map associating an event with the triggered transition
        */
        using EventTransitionMap = std::unordered_map<EventSystem::DwfEvent, TransitionFunction, EventSystem::EventHasher>;

        /*! @typedef TransitionMap
        *  @brief Map associating a state with its supported events and the triggered transition
        */
        using TransitionMap = std::unordered_map<DwfState, EventTransitionMap, StateHasher>;

        /*!
        * @brief Constructor of AbstractStateMachine class
        * @param initial_state : Initial State of the machine.
        * @param max_element_nb : Max number of elements that can be stored in event queue. Default indicates no size limitation.
        *
        * Constructor of the AbstractStateMachine class defining initial state, and setting event processing.
        *
        */
        AbstractStateMachine(DwfState initial_state, size_t max_element_nb = DwfContainers::DwfQueue< std::unique_ptr<EventSystem::DwfEvent> >::C_NO_SIZE_LIMIT);

        /*!
        * @brief Configure state machine and start event processing
        *
        * Create the transition map using method setupTransitionMap.
        * Start event processing.
        *
        */
        void setupAndStart();

    protected:
        /*!
        * @brief Process received event
        * @param event : latest event extracted from event queue
        *
        * Selects a transition function to call depending on current state and event type.
        * Calls it with received event as argument.
        * Virtual method
        *
        */
        virtual void processEvent(std::unique_ptr<EventSystem::DwfEvent>&& event);

        /*!
        * @brief Fill the transition map
        *
        * Purely Virtual method
        *
        */
        virtual void setupTransitionMap() = 0;

        /*!
        * @brief Dead end state reaching handler
        * @param e : exception generated when trying to find transition function associated to current state
        *
        * When reaching a state which has no event/TransitionFunction map associated, you cannot get out of this state.
        * We call this a "dead end state". This may be a desired behavior or a design flaw in your state machine.
        * This method is used to handle such a situation, in your daughter class..
        * Purely Virtual method
        *
        */
        virtual void onDeadEndState(const std::exception& e) = 0;

        DwfState m_current_state; /*!< Current state.*/

        TransitionMap m_transition_map; /*!< List of possible transition functions depending on current_state and events. Protected so that child class can setup map content easily.*/
    };
}
#endif // DWF_STATE_MACHINE_H

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
