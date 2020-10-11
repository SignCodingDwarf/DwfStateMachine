/*!
 * @file teststatemachine.cpp
 * @brief Class used to test AbstractPeriodicStateMachine
 * @author SignC0dingDw@rf
 * @date 10 october 2020
 *
 * Implementation of class instrumenting AbstractPeriodicStateMachine for behavior test purport. <br>
 * Inherits from AbstractPeriodicStateMachine
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

TestStateMachine::~TestStateMachine()
{
    endComputation();
}

DwfStateMachine::DwfState TestStateMachine::getCurrentState() const
{
    return m_current_state;
}

uint32_t TestStateMachine::onDeadEndStateCalled() const
{
    return m_on_dead_en_state_called;
}

uint32_t TestStateMachine::periodicACalled() const
{
    return m_timer_a_timeout;
}

uint32_t TestStateMachine::periodicBCalled() const
{
    return m_timer_b_timeout;
}

uint32_t TestStateMachine::periodicCCalled() const
{
    return m_timer_c_timeout;
}

uint32_t TestStateMachine::periodicFCalled() const
{
    return m_timer_f_timeout;
}

void TestStateMachine::waitForTransition()
{
    std::unique_lock<std::mutex> lk(m_transition_mutex);
    m_transition_semaphore.wait(lk, [this]{return m_transition_triggered.load();});

    m_transition_triggered=false; // Reset transition
}

void TestStateMachine::endComputation()
{
    std::unique_lock<std::mutex> lk(m_blocking_mutex);
    m_computation_done=true;
    m_blocking_semaphore.notify_one();
}

void TestStateMachine::setupTransitionMap()
{
    std::pair<EventSystem::DwfEvent, TransitionFunction> transAtoB(EventSystem::DwfEvent(1), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionAtoB(std::move(event));});
    std::pair<EventSystem::DwfEvent, TransitionFunction> transAtoC(EventSystem::DwfEvent(3), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionAtoC(std::move(event));});
    std::pair<EventSystem::DwfEvent, TransitionFunction> transAtoD(EventSystem::DwfEvent(5), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionAtoD(std::move(event));});
    std::pair<EventSystem::DwfEvent, TransitionFunction> transAtoE(EventSystem::DwfEvent(6), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionAtoE(std::move(event));});
    std::pair<EventSystem::DwfEvent, TransitionFunction> transAtoF(EventSystem::DwfEvent(7), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionAtoF(std::move(event));});
    EventTransitionMap transitionsA({transAtoB, transAtoC, transAtoD, transAtoF});
    EventTransitionMap transitionsB({{EventSystem::DwfEvent(2), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionToA(std::move(event));}}});
    EventTransitionMap transitionsC({{EventSystem::DwfEvent(4), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionToA(std::move(event));}}});
    EventTransitionMap transitionsF({{EventSystem::DwfEvent(4), [this](std::unique_ptr<EventSystem::DwfEvent>&& event){transitionFtoA(std::move(event));}}});
    m_transition_map.insert({DwfStateMachine::DwfState(A), transitionsA});
    m_transition_map.insert({DwfStateMachine::DwfState(B), transitionsB});
    m_transition_map.insert({DwfStateMachine::DwfState(C), transitionsC});
    m_transition_map.insert({DwfStateMachine::DwfState(F), transitionsF});
}

void TestStateMachine::setupStateFunctionMap()
{
    m_periodic_function_maps.insert({DwfStateMachine::DwfState(A), [this](){periodicA();}});
    m_periodic_function_maps.insert({DwfStateMachine::DwfState(B), [this](){periodicB();}});
    m_periodic_function_maps.insert({DwfStateMachine::DwfState(C), [this](){periodicC();}});
    m_periodic_function_maps.insert({DwfStateMachine::DwfState(F), [this](){periodicF();}});
}

void TestStateMachine::onDeadEndState(const std::exception& e)
{
    ++m_on_dead_en_state_called;
}

void TestStateMachine::transitionAtoB(std::unique_ptr<EventSystem::DwfEvent>&& event)
{
    startTimer();
    m_current_state = DwfStateMachine::DwfState(B);
    m_transition_triggered=true;
    m_transition_semaphore.notify_one();
}

void TestStateMachine::transitionAtoC(std::unique_ptr<EventSystem::DwfEvent>&& event)
{
    startTimer();
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
    m_current_state = DwfStateMachine::DwfState(E);

    // Simulate long computation (for saturation test)
    std::unique_lock<std::mutex> lk(m_blocking_mutex);
    m_blocking_semaphore.wait(lk, [this]{return m_computation_done.load();});
}

void TestStateMachine::transitionAtoF(std::unique_ptr<EventSystem::DwfEvent>&& event)
{
    startTimer();
    m_current_state = DwfStateMachine::DwfState(F);
    m_transition_triggered=true;
    m_transition_semaphore.notify_one();
}

void TestStateMachine::transitionFtoA(std::unique_ptr<EventSystem::DwfEvent>&& event)
{
    EvChangePeriod* evChangePeriod = static_cast<EvChangePeriod*>(event.get());
    changePeriodAndStop(evChangePeriod->getPeriod());
    m_current_state = DwfStateMachine::DwfState(A);
    m_transition_triggered=true;
    m_transition_semaphore.notify_one();
}

void TestStateMachine::transitionToA(std::unique_ptr<EventSystem::DwfEvent>&& event)
{
    if(*event == EventSystem::DwfEvent(2))
    {
        stopTimer(); // timer stopped only on transition B -> A
    }
    else if(*event == EventSystem::DwfEvent(4)) // Change period event
    {
        EvChangePeriod* evChangePeriod = static_cast<EvChangePeriod*>(event.get());
        changePeriodAndStart(evChangePeriod->getPeriod());
    }

    m_current_state = DwfStateMachine::DwfState(A);
    m_transition_triggered=true;
    m_transition_semaphore.notify_one();
}

void TestStateMachine::periodicA()
{
    m_timer_a_timeout++;
}

void TestStateMachine::periodicB()
{
    m_timer_b_timeout++;
}

void TestStateMachine::periodicC()
{
    m_timer_c_timeout++;
    std::this_thread::sleep_for (std::chrono::milliseconds(15u)); // Simulate long computation
}

void TestStateMachine::periodicF()
{
    m_timer_f_timeout++;
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
