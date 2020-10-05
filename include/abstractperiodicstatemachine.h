/*!
 * @file abstractperiodicstatemachine.h
 * @brief Class representing event based state machine with periodic execution of computation.
 * @author SignC0dingDw@rf
 * @date 03 October 2020
 *
 * Class representing an event based state machine with periodic execution of computation.
 * In such state machines, computations and state changes can be performed either when receiving an event or periodically.
 * Periodic execution is based on a timer that must be explicitely started.
 * Inherits from AbstractStateMachine.
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

#ifndef ABSTRACT_PERIODIC_STATE_MACHINE_H
#define ABSTRACT_PERIODIC_STATE_MACHINE_H

#include "abstractstatemachine.h"
#include "dwftimer.h"

/*!
* @namespace DwfStateMachine
* @brief A namespace used to regroup all elements related to state machines
*/
namespace DwfStateMachine
{
    /*! @class AbstractPeriodicStateMachine
    * @brief Class representing event based state machine with periodic execution of computation.
    *
    * Class representing an event based state machine with periodic execution of computation.
    * On event reception, computations are performed by a transition function called from a map with entries being event type and current state.
    * Some computations are also performed periodically based on a timer execution.
    * Timer is not started by default and should be started when reaching appropriate state in the transition function.
    * Inherits from AbstractStateMachine.
    * Abstract class. You must derive it and fill the table of transitions and table of periodic functions
    *
    * Call behavior of a daughter class should be
    * - DaughterPeriodicStateMachine state_mach(<initial_state>,<initial_period>);
    * - state_mach.setupAndStart();
    *
    * You must redefine the function setupStateFunctionMap() to construct the desired periodic function map during setupAndStart phase.
    *
    * You must redefine the function setupTransitionMap() to construct the desired transition map during setupAndStart phase.
    *
    * You must redefine the function onDeadEndState() which defines the class behavior if a state has no associated transition
    * (i.e. m_transition_map.at(state) throws an exception).
    *
    */
    class AbstractPeriodicStateMachine : public AbstractStateMachine
    {
    public:
        /*! @typedef PeriodicFunction
        *  @brief Signature of a function called periodically
        */
        using PeriodicFunction = std::function<void(void)>;

        /*! @typedef PeriodicFunctionMap
        *  @brief Map associating a state with associated periodic computation function
        */
        using PeriodicFunctionMap = std::unordered_map<DwfState, PeriodicFunction, StateHasher>;

        /*!
        * @brief Constructor of AbstractStateMachine class
        * @param initial_state : Initial State of the machine.
        * @param default_period : Defined default period of state machine.
        * @param max_element_nb : Max number of elements that can be stored in event queue. Default indicates no size limitation.
        *
        * Constructor of the AbstractStateMachine class defining initial state, setting event processing and configuring periodic timer.
        *
        */
        template< class Rep, class Period >
        AbstractPeriodicStateMachine(DwfState initial_state, const std::chrono::duration<Rep,Period>& initial_period, size_t max_element_nb = DwfContainers::DwfQueue< std::unique_ptr<EventSystem::DwfEvent> >::C_NO_SIZE_LIMIT);

        /*!
        * @brief Destructor of AbstractPeriodicStateMachine class
        *
        * Does nothing (assumes DwfTimer class stops timer at destruction)
        *
        */
        virtual ~AbstractPeriodicStateMachine();

        /*!
        * @brief Configure state machine and start event processing
        *
        * Create the state function map using setupStateFunctionMap.
        * Create the transition map using method setupTransitionMap.
        * Start event processing.
        * Final virtual method
        *
        */
        virtual void setupAndStart() final;

    protected:
        /*!
        * @brief Fill the transition map
        *
        * Purely Virtual method
        *
        */
        virtual void setupTransitionMap() = 0;

        /*!
        * @brief Fill the state function map
        *
        * Purely Virtual method
        *
        */
        virtual void setupStateFunctionMap() = 0;

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

        /*!
        * @brief Start control timer
        *
        */
        void startTimer();

        /*!
        * @brief Stop control timer
        *
        */
        void stopTimer();

        /*!
        * @brief Set timer period and (re)start it
        * @param period : Defined new period of state machine.
        *
        * Stop timer then change its period.
        * Finally timer is (re)started.
        *
        */
        template< class Rep, class Period >
        void changePeriodAndStart(const std::chrono::duration<Rep,Period>& period);

        /*!
        * @brief Set timer period and keep it stopped
        * @param period : Defined new period of state machine.
        *
        * Stop timer then change its period.
        * The timer is not (re)started
        *
        */
        template< class Rep, class Period >
        void changePeriodAndStop(const std::chrono::duration<Rep,Period>& period);

        PeriodicFunctionMap m_periodic_function_maps; /*!< Map associating periodic computations with machine states.*/

    private:
        /*!
        * @brief Call the function associated with current state
        *
        * Handler called on periodic timer timeout.
        * If current state is associated with periodic function, run it. Otherwise do nothing.
        *
        */
        void callStateFunction();

        DwfTime::DwfTimer m_periodic_timer; /*!< Timer controlling execution of periodic computations.*/
    };

    template< class Rep, class Period >
    AbstractPeriodicStateMachine::AbstractPeriodicStateMachine(DwfState initial_state, const std::chrono::duration<Rep,Period>& initial_period, size_t max_element_nb) : AbstractStateMachine(initial_state, max_element_nb), m_periodic_timer()
    {
        // Timer configuration
        m_periodic_timer.setSingleShot(false);
        m_periodic_timer.callOnTimeout([this](){callStateFunction();});
        m_periodic_timer.setPeriod(initial_period);
    }

    template< class Rep, class Period >
    void AbstractPeriodicStateMachine::changePeriodAndStart(const std::chrono::duration<Rep,Period>& period)
    {
        // Stop timer and change period
        changePeriodAndStop(period);

        // (Re)start timer
        startTimer();
    }

    template< class Rep, class Period >
    void AbstractPeriodicStateMachine::changePeriodAndStop(const std::chrono::duration<Rep,Period>& period)
    {
        // Stop timer
        stopTimer();

        // New period
        m_periodic_timer.setPeriod(period);
    }
}
#endif // ABSTRACT_PERIODIC_STATE_MACHINE_H

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
