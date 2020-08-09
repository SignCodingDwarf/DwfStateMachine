/*!
 * @file teststatemachine.h
 * @brief Class used to test AbstractStateMachine
 * @author SignC0dingDw@rf
 * @date 05 September 2020
 *
 * Definition of class instrumenting AbstractStateMachine for behavior test purport. <br>
 * Inherits from AbstractStateMachine
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

#ifndef TEST_STATE_MACHINE_H
#define TEST_STATE_MACHINE_H

#include "abstractstatemachine.h"
#include <mutex>
#include <condition_variable>

/*! @class TestStateMachine
* @brief Class used to test AbstractStateMachine
*
* Inherits from AbstractStateMachine
* The machine has 5 states : A(0), B(1), C(2), D(3), E(4) and following transitions :
* A -> B (Ev1, transitionAtoB)
* B -> A (Ev2, transitionToA)
* A -> C (Ev3, transitionAtoC)
* C -> A (Ev4, transitionToA)
* A -> D (Ev5, transitionAtoD)
* A -> E (Ev6, transitionAtoE)
*
*/
class TestStateMachine : public DwfStateMachine::AbstractStateMachine
{
public:
    enum StatesId
    {
        A=0,
        B=1,
        C=2,
        D=3,
        E=4
    };

    /*!
    * @brief Constructor of TestStateMachine class
    * @param max_element_nb : Max number of elements that can be stored in event queue. Default indicates no size limitation.
    *
    */
    TestStateMachine(size_t max_element_nb = DwfContainers::DwfQueue< std::unique_ptr<EventSystem::DwfEvent> >::C_NO_SIZE_LIMIT);

    DwfStateMachine::DwfState getCurrentState() const;

    /*!
    * @brief Get onDeadEndState counter
    * @return Number of times onDeadEndState has been called
    *
    */
    uint32_t onDeadEndStateCalled() const;

    /*!
    * @brief Get transitionAtoB counter
    * @return Number of times transitionAtoB has been called
    *
    */
    uint32_t transitionAtoBCalled() const;

    /*!
    * @brief Get transitionAtoC counter
    * @return Number of times transitionAtoC has been called
    *
    */
    uint32_t transitionAtoCCalled() const;

    /*!
    * @brief Get transitionBtoA counter
    * @return Number of times transitionBtoA has been called
    *
    */
    uint32_t transitionBtoACalled() const;

    /*!
    * @brief Get transitionCtoA counter
    * @return Number of times transitionCtoA has been called
    *
    */
    uint32_t transitionCtoACalled() const;

    /*!
    * @brief Wait for a transition to be trigerred
    *
    * Blocking call while a transition has not been trigerred.
    * Resets m_transition_triggered to false
    *
    */
    void waitForTransition();

protected:
    /*!
    * @brief Fill the transition map
    *
    * Virtual method
    *
    */
    virtual void setupTransitionMap();

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
    virtual void onDeadEndState(const std::exception& e);

private:
    /*!
    * @brief Transition from A to B state
    * @param event : Received event for transition
    *
    */
    void transitionAtoB(std::unique_ptr<EventSystem::DwfEvent>&& event);

    /*!
    * @brief Transition from A to C state
    * @param event : Received event for transition
    *
    */
    void transitionAtoC(std::unique_ptr<EventSystem::DwfEvent>&& event);

    /*!
    * @brief Transition from A to D state
    * @param event : Received event for transition
    *
    */
    void transitionAtoD(std::unique_ptr<EventSystem::DwfEvent>&& event);

    /*!
    * @brief Transition from A to E state
    * @param event : Received event for transition
    *
    * Has a sleep to simulate long computation time.
    *
    */
    void transitionAtoE(std::unique_ptr<EventSystem::DwfEvent>&& event);

    /*!
    * @brief Transition ta A state
    * @param event : Received event for transition
    *
    * Can transiton from B or C state. Event is used to determine state from which transition comes from.
    *
    */
    void transitionToA(std::unique_ptr<EventSystem::DwfEvent>&& event);

    std::atomic<uint32_t> m_on_dead_en_state_called; /*!< Counter of onDeadEndState calls.*/
    std::atomic<uint32_t> m_transition_a_to_b_called; /*!< Counter of transitionAtoB calls.*/
    std::atomic<uint32_t> m_transition_a_to_c_called; /*!< Counter of transitionAtoC calls.*/
    std::atomic<uint32_t> m_transition_b_to_a_called; /*!< Counter of transitionToA with Ev2 calls.*/
    std::atomic<uint32_t> m_transition_c_to_a_called; /*!< Counter of transitionToA with Ev4 calls.*/

    std::atomic<bool> m_transition_triggered; /*!< Flag indicating if a transition has been triggered lately.*/

    mutable std::mutex m_transition_mutex; /*!< Mutex used to protect transition semaphore.*/
    mutable std::condition_variable m_transition_semaphore; /*!< Condition variable used to wait for a transition to be triggered.*/

};

#endif // TEST_STATE_MACHINE_H

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
