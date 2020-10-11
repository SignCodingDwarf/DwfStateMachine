/*!
 * @file dwftimerperiodictest.cpp
 * @brief Class implementing DwfTimer periodic timer unit tests.
 * @author SignC0dingDw@rf
 * @date 30 September 2020
 *
 * Implementation of class performing DwfTimer periodic timer unit tests. <br>
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

#include "dwftimerperiodictest.h"
#include "dwftimer.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DwfTimerPeriodicTest);

DwfTimerPeriodicTest::DwfTimerPeriodicTest()
{
}

DwfTimerPeriodicTest::~DwfTimerPeriodicTest()
{
}

void DwfTimerPeriodicTest::setUp()
{
}

void DwfTimerPeriodicTest::tearDown()
{
}

void DwfTimerPeriodicTest::testStartStop()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    uint32_t called=0u; // Number of calls to timeout method

    DwfTime::DwfTimer timer;
    timer.setSingleShot(false);
    timer.setPeriod(std::chrono::milliseconds(50));
    timer.callOnTimeout([&called]{++called;});

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should not be started", false, timer.isStarted());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           1 : Start timer                          ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.start();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be started", true, timer.isStarted());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Wait about 20 timer execution

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///               2 : Stop and check number of executions              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.stop();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should not be started", false, timer.isStarted());

    // Number of executions should be 20. Yet we do not control precisely the time when stop is called compared to loop calls so we add a margin to make sure test passes.
    CPPUNIT_ASSERT_MESSAGE("Number of timeout function execution should be right", (19u <= called) && (called <= 21u));

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              3 : Restart                           ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.setPeriod(std::chrono::milliseconds(25)); // Change period
    called=0u; // Reset counter
    timer.start();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be started", true, timer.isStarted());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Wait about 40 timer execution

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///               4 : Stop and check number of executions              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.stop();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should not be started", false, timer.isStarted());

    // Number of executions should be 40. Yet we do not control precisely the time when stop is called compared to loop calls so we add a margin to make sure test passes.
    CPPUNIT_ASSERT_MESSAGE("Number of timeout function execution should be right", (39u <= called) && (called <= 41u));
}

void DwfTimerPeriodicTest::testDelete()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    uint32_t called=0u; // Number of calls to timeout method

    DwfTime::DwfTimer* timer = new DwfTime::DwfTimer();
    timer->setSingleShot(false);
    timer->setPeriod(std::chrono::milliseconds(200));
    timer->callOnTimeout([&called]{++called;});

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should not be started", false, timer->isStarted());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             1 : Start                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer->start();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be started", true, timer->isStarted());
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Wait a little bit but not long enough for timer to end

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             2 : Delete                             ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    delete timer;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer timeout handler should not be called", 0u, called);
}

void DwfTimerPeriodicTest::testStartedConfigure()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    uint32_t called=0u; // Number of calls to timeout method
    uint32_t alternate_called=0u; // Number of calls to timeout method

    DwfTime::DwfTimer timer;
    timer.setSingleShot(false);
    timer.setPeriod(std::chrono::milliseconds(100));
    timer.callOnTimeout([&called]{++called;});

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should not be started", false, timer.isStarted());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             1 : Start                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.start();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be started", true, timer.isStarted());
    std::this_thread::sleep_for(std::chrono::milliseconds(40)); // Wait a little bit but not long enough for timer to end

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          2 : Change config                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.setPeriod(std::chrono::milliseconds(400));
    timer.callOnTimeout([&alternate_called]{++alternate_called;});

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          3 : Stop Timer                            ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for(std::chrono::milliseconds(380)); // Wait a few timer executions
    timer.stop();

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer timeout handler should be called with the right period", 4u, called);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Alternate timer timeout handler should not be called", 0u, alternate_called);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped", false, timer.isStarted());
}

void DwfTimerPeriodicTest::testPeriod()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    uint32_t called=0u; // Number of calls to timeout method

    DwfTime::DwfTimer timer;
    timer.setSingleShot(false);
    timer.setPeriod(std::chrono::milliseconds(50));
    timer.callOnTimeout([&called]{++called;std::this_thread::sleep_for(std::chrono::milliseconds(30));}); // Sleep simulates long computation period in regard to exepected period

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should not be started", false, timer.isStarted());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           1 : Start timer                          ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.start();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be started", true, timer.isStarted());
    std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // Wait about 80 timer execution (if wrong computation, number will be about 50)

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///               2 : Stop and check number of executions              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.stop();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should not be started", false, timer.isStarted());

    // Number of executions should be 80. Yet we do not control precisely the time when stop is called compared to loop calls so we add a margin to make sure test passes.
    printf("\n   Number of executions : %u\n",called);
    CPPUNIT_ASSERT_MESSAGE("Number of timeout function execution should be right", (79u <= called) && (called <= 81u));
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
