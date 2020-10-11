/*!
 * @file dwftimersingleshottest.cpp
 * @brief Class implementing DwfTimer single shot unit tests.
 * @author SignC0dingDw@rf
 * @date 27 September 2020
 *
 * Implementation of class implementing DwfTimer single shot unit tests. <br>
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

#include "dwftimersingleshottest.h"
#include "dwftimer.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DwfTimerSingleShotTest);

DwfTimerSingleShotTest::DwfTimerSingleShotTest()
{
}

DwfTimerSingleShotTest::~DwfTimerSingleShotTest()
{
}

void DwfTimerSingleShotTest::setUp()
{
}

void DwfTimerSingleShotTest::tearDown()
{
}

void DwfTimerSingleShotTest::testTimeout()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    uint32_t called=0u; // Number of calls to timeout method
    std::mutex cv_mutex;
    std::condition_variable timeout_wait;

    DwfTime::DwfTimer timer;
    timer.setSingleShot(true);
    timer.setPeriod(std::chrono::milliseconds(500));
    timer.callOnTimeout([&called, &cv_mutex, &timeout_wait]{
        ++called;
        std::unique_lock<std::mutex> lock(cv_mutex);
        timeout_wait.notify_one();});

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should not be started", false, timer.isStarted());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                        1 : First Execution                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.start();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be started", true, timer.isStarted());

    {
        std::unique_lock<std::mutex> lock(cv_mutex);
        std::cv_status wait_status = timeout_wait.wait_for(lock,std::chrono::milliseconds(510)); // Slightly more than timer duration to let it end
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout on waiting for timer to trigger", std::cv_status::no_timeout, wait_status);
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer timeout handler should be called", 1u, called);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped", false, timer.isStarted());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                         2 : Second Execution                       ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.setPeriod(std::chrono::milliseconds(200)); // Change duration
    timer.start();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be started", true, timer.isStarted());

    {
        std::unique_lock<std::mutex> lock(cv_mutex);
        std::cv_status wait_status = timeout_wait.wait_for(lock,std::chrono::milliseconds(210)); // Slightly more than timer duration to let it end
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout on waiting for timer to trigger", std::cv_status::no_timeout, wait_status);
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer timeout handler should be called", 2u, called);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped", false, timer.isStarted());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           3 : Test Restart                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.start();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be started", true, timer.isStarted());

    std::this_thread::sleep_for(std::chrono::milliseconds(90)); // Wait a little bit

    timer.start(); // Restart timer

    {
        std::unique_lock<std::mutex> lock(cv_mutex);
        std::cv_status wait_status = timeout_wait.wait_for(lock,std::chrono::milliseconds(120)); // Slightly more than timer duration but less than total timer duration
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer execution still not complete due to reset", std::cv_status::timeout, wait_status);
    }

    {
        std::unique_lock<std::mutex> lock(cv_mutex);
        std::cv_status wait_status = timeout_wait.wait_for(lock,std::chrono::milliseconds(100)); // Slightly more than timer duration (including previous wait) to let it end
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer execution still not complete due to reset", std::cv_status::no_timeout, wait_status);
    }
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer timeout handler should be called", 3u, called);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped", false, timer.isStarted());
}

void DwfTimerSingleShotTest::testStop()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    uint32_t called=0u; // Number of calls to timeout method

    DwfTime::DwfTimer timer;
    timer.setSingleShot(true);
    timer.setPeriod(std::chrono::milliseconds(200));
    timer.callOnTimeout([&called]{++called;});

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should not be started", false, timer.isStarted());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             1 : Start                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.start();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be started", true, timer.isStarted());
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Wait a little bit but not long enough for timer to end

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              2 : Stop                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.stop();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer timeout handler should not be called", 0u, called);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped", false, timer.isStarted());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                            3 : Restart                             ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.start();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be started", true, timer.isStarted());
    std::this_thread::sleep_for(std::chrono::milliseconds(210)); // Wait enough time so that timer ends

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer timeout handler should be called", 1u, called);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped", false, timer.isStarted());
}

void DwfTimerSingleShotTest::testDelete()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    uint32_t called=0u; // Number of calls to timeout method

    DwfTime::DwfTimer* timer = new DwfTime::DwfTimer();
    timer->setSingleShot(true);
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

void DwfTimerSingleShotTest::testStartedConfigure()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    uint32_t called=0u; // Number of calls to timeout method
    uint32_t alternate_called=0u; // Number of calls to timeout method
    std::mutex cv_mutex;
    std::condition_variable timeout_wait;

    DwfTime::DwfTimer timer;
    timer.setSingleShot(true);
    timer.setPeriod(std::chrono::milliseconds(200));
    timer.callOnTimeout([&called, &cv_mutex, &timeout_wait]{
        ++called;
        std::unique_lock<std::mutex> lock(cv_mutex);
        timeout_wait.notify_one();});

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should not be started", false, timer.isStarted());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             1 : Start                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.start();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be started", true, timer.isStarted());
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Wait a little bit but not long enough for timer to end

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          2 : Change config                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    timer.setPeriod(std::chrono::milliseconds(400));
    timer.callOnTimeout([&alternate_called, &cv_mutex, &timeout_wait]{
        ++alternate_called;
        std::unique_lock<std::mutex> lock(cv_mutex);
        timeout_wait.notify_one();});

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           3 : End Timer                            ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    {
        std::unique_lock<std::mutex> lock(cv_mutex);
        std::cv_status wait_status = timeout_wait.wait_for(lock,std::chrono::milliseconds(200)); // Slightly more than timer duration to let it end
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout on waiting for timer to trigger", std::cv_status::no_timeout, wait_status);
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer timeout handler should be called", 1u, called);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Alternate timer timeout handler should not be called", 0u, alternate_called);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer should be stopped", false, timer.isStarted());
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
