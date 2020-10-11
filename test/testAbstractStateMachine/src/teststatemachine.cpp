/*!
 * @file teststatemachine.cpp
 * @brief Class used to test AbstractStateMachine
 * @author SignC0dingDw@rf
 * @date 05 September 2020
 *
 * Implementation of class instrumenting AbstractStateMachine for behavior test purport. <br>
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

#include "teststatemachine.h"
#include <chrono>
#include <iostream>

TestStateMachine::TestStateMachine(size_t max_element_nb) : DwfStateMachine::AbstractStateMachine(DwfStateMachine::DwfState(A), max_element_nb), m_on_dead_en_state_called(0),
    m_transition_a_to_b_called(0), m_transition_a_to_c_called(0), m_transition_b_to_a_called(0), m_transition_c_to_a_called(0), m_transition_triggered(false)
{
}

DwfStateMachine::DwfState TestStateMachine::getCurrentState() const
{
    return m_current_state;
}

uint32_t TestStateMachine::onDeadEndStateCalled() const
{
    return m_on_dead_en_state_called;
}

uint32_t TestStateMachine::transitionAtoBCalled() const
{
    return m_transition_a_to_b_called;
}

uint32_t TestStateMachine::transitionAtoCCalled() const
{
    return m_transition_a_to_c_called;
}

uint32_t TestStateMachine::transitionBtoACalled() const
{
    return m_transition_b_to_a_called;
}

uint32_t TestStateMachine::transitionCtoACalled() const
{
    return m_transition_c_to_a_called;
}

void TestStateMachine::waitForTransition()
{
    std::unique_lock<std::mutex> lk(m_transition_mutex);
    m_transition_semaphore.wait(lk, [this]{return m_transition_triggered.load();});

    m_transition_triggered=false; // Reset transition
}

void TestStateMachine::setupTransitionMap()
{
    std::pair<EventSystem::DwfEvent, TransitionFunction> transAtoB(EventSystem::DwfEvent(1), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionAtoB(std::move(event));});
    std::pair<EventSystem::DwfEvent, TransitionFunction> transAtoC(EventSystem::DwfEvent(3), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionAtoC(std::move(event));});
    std::pair<EventSystem::DwfEvent, TransitionFunction> transAtoD(EventSystem::DwfEvent(5), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionAtoD(std::move(event));});
    std::pair<EventSystem::DwfEvent, TransitionFunction> transAtoE(EventSystem::DwfEvent(6), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionAtoE(std::move(event));});
    EventTransitionMap transitionsA({transAtoB, transAtoC, transAtoD, transAtoE});
    EventTransitionMap transitionsB({{EventSystem::DwfEvent(2), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionToA(std::move(event));}}});
    EventTransitionMap transitionsC({{EventSystem::DwfEvent(4), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionToA(std::move(event));}}});
    m_transition_map.insert({DwfStateMachine::DwfState(A), transitionsA});
    m_transition_map.insert({DwfStateMachine::DwfState(B), transitionsB});
    m_transition_map.insert({DwfStateMachine::DwfState(C), transitionsC});
}

void TestStateMachine::onDeadEndState(const std::exception& e)
{
    ++m_on_dead_en_state_called;
}

void TestStateMachine::transitionAtoB(std::unique_ptr<EventSystem::DwfEvent>&& event)
{
    ++m_transition_a_to_b_called;
    m_current_state = DwfStateMachine::DwfState(B);
    m_transition_triggered=true;
    m_transition_semaphore.notify_one();
}

void TestStateMachine::transitionAtoC(std::unique_ptr<EventSystem::DwfEvent>&& event)
{
    ++m_transition_a_to_c_called;
    m_current_state = DwfStateMachine::DwfState(C);
    m_transition_triggered=true;
    m_transition_semaphore.notify_one();
}

void TestStateMachine::transitionAtoD(std::unique_ptr<EventSystem::DwfEvent>&& event)
{
    m_current_state = DwfStateMachine::DwfState(D);
    m_transition_triggered=true;
    m_transition_semaphore.notify_one();
}

void TestStateMachine::transitionAtoE(std::unique_ptr<EventSystem::DwfEvent>&& event)
{
    // Simulate computation duration (for saturation tests)
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    m_current_state = DwfStateMachine::DwfState(E);
}

void TestStateMachine::transitionToA(std::unique_ptr<EventSystem::DwfEvent>&& event)
{
    if(*event == EventSystem::DwfEvent(2))
    {
        ++m_transition_b_to_a_called;
    }
    else if(*event == EventSystem::DwfEvent(4))
    {
        ++m_transition_c_to_a_called;
    }
    m_current_state = DwfStateMachine::DwfState(A);
    m_transition_triggered=true;
    m_transition_semaphore.notify_one();
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
