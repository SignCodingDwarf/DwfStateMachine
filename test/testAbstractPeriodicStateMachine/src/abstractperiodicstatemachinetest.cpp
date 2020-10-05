/*!
 * @file abstractstatemachinetest.cpp
 * @brief Class implementing AbstractPeriodicStateMachine unit tests.
 * @author SignC0dingDw@rf
 * @date 10 October 2020
 *
 * Implementation of class performing AbstractPeriodicStateMachine unit tests. <br>
 * Inherits from TestFixture
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

#include "abstractperiodicstatemachinetest.h"
#include "teststatemachine.h"

#include <chrono>

CPPUNIT_TEST_SUITE_REGISTRATION(AbstractPeriodicStateMachineTest);

AbstractPeriodicStateMachineTest::AbstractPeriodicStateMachineTest()
{
}

AbstractPeriodicStateMachineTest::~AbstractPeriodicStateMachineTest()
{
}

void AbstractPeriodicStateMachineTest::setUp()
{
}

void AbstractPeriodicStateMachineTest::tearDown()
{
}

void AbstractPeriodicStateMachineTest::testDeletion()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestStateMachine* st_mach = new TestStateMachine(std::chrono::milliseconds(100u));
    st_mach->setupAndStart();

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              1 : Wait                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(50));

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                    2 : Transition to start timer                   ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<EventSystem::DwfEvent> evB(new EventSystem::DwfEvent(1));
    st_mach->pushEvent(std::move(evB));

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              3 : Wait                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(110));

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             4 : Delete                             ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    delete st_mach;
}

void AbstractPeriodicStateMachineTest::testSizeLimit()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestStateMachine st_mach(std::chrono::milliseconds(100u), 5);
    CPPUNIT_ASSERT_MESSAGE("Initial state is A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              2 : Push                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(int i=0;i<=7;++i)
    {
        std::unique_ptr<EventSystem::DwfEvent> ev(new EventSystem::DwfEvent(6));
        CPPUNIT_ASSERT_NO_THROW_MESSAGE("Pushing events when not started causes no exception because events are dropped",st_mach.pushEvent(std::move(ev)));
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             2 : Start                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    st_mach.setupAndStart();

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              3 : Push                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(EventSystem::EventID i=1; i<=5; ++i)
    {
        std::unique_ptr<EventSystem::DwfEvent> ev(new EventSystem::DwfEvent(6));
        CPPUNIT_ASSERT_NO_THROW_MESSAGE("Pushing events when queue is not full should not trigger exception",st_mach.pushEvent(std::move(ev)));
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                        4 : Push on full queue                      ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<EventSystem::DwfEvent> ev(new EventSystem::DwfEvent(6));
    CPPUNIT_ASSERT_THROW_MESSAGE("Pushing events when queue is full should trigger exception",st_mach.pushEvent(std::move(ev)), std::runtime_error);
}

void AbstractPeriodicStateMachineTest::testDeadEndState()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestStateMachine st_mach(std::chrono::milliseconds(100u));
    CPPUNIT_ASSERT_MESSAGE("Initial state is A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             1 : Start                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    st_mach.setupAndStart();

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              2 : Push                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<EventSystem::DwfEvent> ev(new EventSystem::DwfEvent(5));
    st_mach.pushEvent(std::move(ev));
    st_mach.waitForTransition();
    CPPUNIT_ASSERT_MESSAGE("Go to state D", DwfStateMachine::DwfState(TestStateMachine::D) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              3 : Push                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    uint32_t nb_events=10u;
    for(uint32_t i=1; i<=nb_events; ++i)
    {
        std::unique_ptr<EventSystem::DwfEvent> evDeadEnd(new EventSystem::DwfEvent(i));
        st_mach.pushEvent(std::move(evDeadEnd));
        CPPUNIT_ASSERT_MESSAGE("Stay in state D", DwfStateMachine::DwfState(TestStateMachine::D) == st_mach.getCurrentState());
        std::this_thread::sleep_for (std::chrono::milliseconds(100)); // Wait a little bit for event to be processed
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                    4 : Check onDeadEndState calls                  ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    CPPUNIT_ASSERT_EQUAL_MESSAGE("onDeadEndState should have been called for every event", nb_events, st_mach.onDeadEndStateCalled());
}

void AbstractPeriodicStateMachineTest::testTimerStartStop()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestStateMachine st_mach(std::chrono::milliseconds(20u));
    st_mach.setupAndStart();
    CPPUNIT_ASSERT_MESSAGE("Initial state is A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          1 : Transitions                           ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<EventSystem::DwfEvent> evB(new EventSystem::DwfEvent(1));
    st_mach.pushEvent(std::move(evB));
    st_mach.waitForTransition();
    CPPUNIT_ASSERT_MESSAGE("Go to state B", DwfStateMachine::DwfState(TestStateMachine::B) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           2 : Stop timer                           ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(210u)); // Wait a little bit for timer to run (should be 10 executions because we let last execution complete by adding a few ms)
    std::unique_ptr<EventSystem::DwfEvent> evA(new EventSystem::DwfEvent(2));
    st_mach.pushEvent(std::move(evA));
    st_mach.waitForTransition();
    CPPUNIT_ASSERT_MESSAGE("Go to state A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());

    uint32_t timeouts = st_mach.periodicBCalled();

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be running in state B", 0u, st_mach.periodicACalled());
    CPPUNIT_ASSERT_MESSAGE("Timer should be running in state B", (9u <= timeouts) && (timeouts <= 11u)); // interval so that timing issues are not relevant
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be running in state B", 0u, st_mach.periodicCCalled());
     CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be running in state B", 0u, st_mach.periodicFCalled());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                         3 : Timer stopped                          ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(150u)); // Wait a little bit to check timer is not running

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped in state A", 0u, st_mach.periodicACalled());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped in state A", timeouts, st_mach.periodicBCalled());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped in state A", 0u, st_mach.periodicCCalled());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped in state A", 0u, st_mach.periodicFCalled());
}

void AbstractPeriodicStateMachineTest::testTimerChangePeriod()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestStateMachine st_mach(std::chrono::milliseconds(20u));
    st_mach.setupAndStart();
    CPPUNIT_ASSERT_MESSAGE("Initial state is A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          1 : Transitions                           ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<EventSystem::DwfEvent> evC(new EventSystem::DwfEvent(3));
    st_mach.pushEvent(std::move(evC));
    st_mach.waitForTransition();
    CPPUNIT_ASSERT_MESSAGE("Go to state C", DwfStateMachine::DwfState(TestStateMachine::C) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          2 : Check period                          ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(2010u)); // Wait a little bit for timer to run (should be 100 executions because we let last execution complete by adding a few ms)
    uint32_t timeouts = st_mach.periodicCCalled();
    CPPUNIT_ASSERT_MESSAGE("Execution in state C should respect desired period", (99u <= timeouts) && (timeouts <= 101u)); // interval so that timing issues are not relevant


    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          3 : Change period                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<EvChangePeriod> evA(new EvChangePeriod(std::chrono::milliseconds(10u)));
    st_mach.pushEvent(std::move(evA));
    st_mach.waitForTransition();
    CPPUNIT_ASSERT_MESSAGE("Go to state A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                         4 : Period updated                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(150u)); // Wait a little bit to check timer is not running
    timeouts = st_mach.periodicACalled();
    CPPUNIT_ASSERT_MESSAGE("Execution in state A should respect desired period", (14u <= timeouts) && (timeouts <= 16u)); // interval so that timing issues are not relevant
}

void AbstractPeriodicStateMachineTest::testTimerChangePeriodStop()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestStateMachine st_mach(std::chrono::milliseconds(50u));
    st_mach.setupAndStart();
    CPPUNIT_ASSERT_MESSAGE("Initial state is A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          1 : Transitions                           ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<EventSystem::DwfEvent> evF(new EventSystem::DwfEvent(7));
    st_mach.pushEvent(std::move(evF));
    st_mach.waitForTransition();
    CPPUNIT_ASSERT_MESSAGE("Go to state F", DwfStateMachine::DwfState(TestStateMachine::F) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          2 : Check period                          ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(1010u)); // Wait a little bit for timer to run (should be 20 executions because we let last execution complete by adding a few ms)
    uint32_t timeouts = st_mach.periodicFCalled();
    CPPUNIT_ASSERT_MESSAGE("Execution in state F should respect desired period", (19u <= timeouts) && (timeouts <= 21u)); // interval so that timing issues are not relevant


    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          3 : Change period                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<EvChangePeriod> evA(new EvChangePeriod(std::chrono::milliseconds(30u)));
    st_mach.pushEvent(std::move(evA));
    st_mach.waitForTransition();
    CPPUNIT_ASSERT_MESSAGE("Go to state A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          4 : Timer stopped                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(150u)); // Wait a little bit to check timer is not running
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped", 0u, st_mach.periodicACalled());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped", timeouts, st_mach.periodicFCalled()); // Unchanged for F as well

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          5 : Transitions                           ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    evF=std::make_unique<EventSystem::DwfEvent>(7);
    st_mach.pushEvent(std::move(evF));
    st_mach.waitForTransition();
    CPPUNIT_ASSERT_MESSAGE("Go to state F", DwfStateMachine::DwfState(TestStateMachine::F) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                         6 : Period updated                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(185u)); // Wait a little bit to check timer is not running
    uint32_t timeouts_update = st_mach.periodicFCalled();
    CPPUNIT_ASSERT_MESSAGE("Period should be updated", (timeouts + 5u <= timeouts_update) && (timeouts_update <= timeouts + 7u)); // interval so that timing issues are not relevant
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
