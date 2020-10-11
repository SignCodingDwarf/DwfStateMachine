/*!
 * @file abstractstatemachinetest.cpp
 * @brief Class implementing AbstractStateMachine unit tests.
 * @author SignC0dingDw@rf
 * @date 05 September 2020
 *
 * Implementation of class performing AbstractStateMachine unit tests. <br>
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

#include "abstractstatemachinetest.h"
#include "teststatemachine.h"

#include <chrono>

CPPUNIT_TEST_SUITE_REGISTRATION(AbstractStateMachineTest);

AbstractStateMachineTest::AbstractStateMachineTest()
{
}

AbstractStateMachineTest::~AbstractStateMachineTest()
{
}

void AbstractStateMachineTest::setUp()
{
}

void AbstractStateMachineTest::tearDown()
{
}

void AbstractStateMachineTest::testDeletion()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestStateMachine* st_mach = new TestStateMachine();
    st_mach->setupAndStart();

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              1 : Wait                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(100));


    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             2 : Delete                             ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    delete st_mach;
}

void AbstractStateMachineTest::testSizeLimit()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestStateMachine st_mach(5);
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

void AbstractStateMachineTest::testDeadEndState()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestStateMachine st_mach;
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

void AbstractStateMachineTest::testTransitions()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestStateMachine st_mach;
    st_mach.setupAndStart();
    CPPUNIT_ASSERT_MESSAGE("Initial state is A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          1 : Transitions                           ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    uint32_t nb_loops=10u;
    for(uint32_t i=1; i<=nb_loops; ++i)
    {
        std::unique_ptr<EventSystem::DwfEvent> evB(new EventSystem::DwfEvent(1));
        st_mach.pushEvent(std::move(evB));
        st_mach.waitForTransition();
        CPPUNIT_ASSERT_MESSAGE("Go to state B", DwfStateMachine::DwfState(TestStateMachine::B) == st_mach.getCurrentState());

        std::unique_ptr<EventSystem::DwfEvent> evAB(new EventSystem::DwfEvent(2));
        st_mach.pushEvent(std::move(evAB));
        st_mach.waitForTransition();
        CPPUNIT_ASSERT_MESSAGE("Go to state A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());

        std::unique_ptr<EventSystem::DwfEvent> evC(new EventSystem::DwfEvent(3));
        st_mach.pushEvent(std::move(evC));
        st_mach.waitForTransition();
        CPPUNIT_ASSERT_MESSAGE("Go to state C", DwfStateMachine::DwfState(TestStateMachine::C) == st_mach.getCurrentState());

        std::unique_ptr<EventSystem::DwfEvent> evAC(new EventSystem::DwfEvent(4));
        st_mach.pushEvent(std::move(evAC));
        st_mach.waitForTransition();
        CPPUNIT_ASSERT_MESSAGE("Go to state A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());
    }

    // A last transition to have different numbers
    std::unique_ptr<EventSystem::DwfEvent> evB(new EventSystem::DwfEvent(1));
    st_mach.pushEvent(std::move(evB));
    st_mach.waitForTransition();
    CPPUNIT_ASSERT_MESSAGE("Go to state B", DwfStateMachine::DwfState(TestStateMachine::B) == st_mach.getCurrentState());

    std::unique_ptr<EventSystem::DwfEvent> evAB(new EventSystem::DwfEvent(2));
    st_mach.pushEvent(std::move(evAB));
    st_mach.waitForTransition();
    CPPUNIT_ASSERT_MESSAGE("Go to state A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                     2 : Check transitions calls                    ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Transitions A to B", nb_loops+1, st_mach.transitionAtoBCalled());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Transitions A to C", nb_loops, st_mach.transitionAtoCCalled());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Transitions B to A", nb_loops+1, st_mach.transitionBtoACalled());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Transitions C to A", nb_loops, st_mach.transitionCtoACalled());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                         3 : No transition                          ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<EventSystem::DwfEvent> evN(new EventSystem::DwfEvent(42));
    st_mach.pushEvent(std::move(evN));
    std::this_thread::sleep_for (std::chrono::milliseconds(100)); // Wait a little bit for event to be processed
    CPPUNIT_ASSERT_MESSAGE("Stay in state A", DwfStateMachine::DwfState(TestStateMachine::A) == st_mach.getCurrentState());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Transitions A to B", nb_loops+1, st_mach.transitionAtoBCalled());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Transitions A to C", nb_loops, st_mach.transitionAtoCCalled());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Transitions B to A", nb_loops+1, st_mach.transitionBtoACalled());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Transitions C to A", nb_loops, st_mach.transitionCtoACalled());
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
