/*!
 * @file abstractperiodicstatemachinetest.h
 * @brief Class implementing AbstractPeriodicStateMachine unit tests.
 * @author SignC0dingDw@rf
 * @date 10 October 2020
 *
 * Definition of class performing AbstractPeriodicStateMachine unit tests. <br>
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

#ifndef ABSTRACT_PERIODIC_STATE_MACHINE_TEST_H
#define ABSTRACT_PERIODIC_STATE_MACHINE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Portability.h>

/*! @class AbstractPeriodicStateMachineTest
* @brief Unit tests of AbstractPeriodicStateMachine class
*
* Inherits from TestFixture
*
*/
class AbstractPeriodicStateMachineTest : public CPPUNIT_NS::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(AbstractPeriodicStateMachineTest);
        CPPUNIT_TEST(testDeletion);
    //    CPPUNIT_TEST(testSizeLimit);
        CPPUNIT_TEST(testDeadEndState);
        CPPUNIT_TEST(testTimerStartStop);
        CPPUNIT_TEST(testTimerChangePeriod);
        CPPUNIT_TEST(testTimerChangePeriodStop);
    CPPUNIT_TEST_SUITE_END();

public:
    /*!
    * @brief Constructor of the AbstractStateMachineTest class
    *
    * Does nothing.
    *
    */
    AbstractPeriodicStateMachineTest();

    /*!
    * @brief Desctructor of the AbstractStateMachineTest class
    *
    * Does nothing.
    *
    */
    ~AbstractPeriodicStateMachineTest();

    /*!
    * @brief Prepare execution environment of every test
    *
    * Does nothing.
    *
    */
    void setUp();

    /*!
    * @brief Cleanup environment after execution of each test
    *
    * Does nothing.
    *
    */
    void tearDown();

    /*!
    * @brief Check deletion
    *
    * 0) Create pointer to TestStateMachine. Start event processing.
    * 1) Wait a little bit to make sure we are waiting for events.
    * 2) Trigger transition A->B to launch timer
    * 3) Wait a little bit more for timer to run
    * 4) Force Deletion.
    *
    * No memory error should appear.
    *
    */
    void testDeletion();

    /*!
    * @brief Check pushing events behavior if event queue has size limitation
    *
    * 0) Create TestStateMachine with queue of size N.
    * 1) Push N+1 events. Check no exception is raised.
    * 2) Start state machine.
    * 3) Push N events triggering transition with long computation time. Check no exception is raised.
    * 4) Push event and check exception is raised.
    *
    */
    void testSizeLimit();

    /*!
    * @brief Check behavior when reaching a dead end state
    *
    * 0) Create TestStateMachine.
    * 1) Start event processing.
    * 2) Push event to go to dead end state.
    * 3) Push events on dead en state.
    * 4) Check onDeadEndState calls.
    *
    */
    void testDeadEndState();

    /*!
    * @brief Check periodic activities start stop behavior
    *
    * 0) Create TestStateMachine and start it.
    * 1) Run transitions A->B to start timer.
    * 2) Stop timer by running B->A after a while and check how many transitions were triggered.
    * 3) Wait and check no transition has been called while in state A.
    *
    */
    void testTimerStartStop();

    /*!
    * @brief Check period management
    *
    * 0) Create TestStateMachine and start it.
    * 1) Run transitions A->C to start timer.
    * 2) Wait and check that despite long calculations, period is respected.
    * 3) Transition C->A to change period.
    * 4) Wait and check that period was changed.
    *
    */
    void testTimerChangePeriod();

    /*!
    * @brief Check period management and timer stop
    *
    * 0) Create TestStateMachine and start it.
    * 1) Run transitions A->F to start timer.
    * 2) Wait and check period.
    * 3) Transition F->A to change period and stop timer.
    * 4) Wait and check timer is stopped.
    * 5) Run transitions A->F to start timer.
    * 6) Wait and check that period was changed.
    *
    */
    void testTimerChangePeriodStop();

};

#endif // ABSTRACT_PERIODIC_STATE_MACHINE_TEST_H

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
