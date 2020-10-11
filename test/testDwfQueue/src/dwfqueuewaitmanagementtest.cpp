/*!
 * @file dwfqueuewaitmanagement.cpp
 * @brief Class implementing DwfQueue wait management unit tests.
 * @author SignC0dingDw@rf
 * @date 11 July 2020
 *
 * Implementation of class performing DwfQueue wait management unit tests. <br>
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

#include "dwfqueuewaitmanagementtest.h"
#include "dwfqueue.h"
#include <memory>
#include <stdexcept>
#include <thread>
#include <chrono>

CPPUNIT_TEST_SUITE_REGISTRATION(DwfQueueWaitManagementTest);

DwfQueueWaitManagementTest::DwfQueueWaitManagementTest()
{
}

DwfQueueWaitManagementTest::~DwfQueueWaitManagementTest()
{
}

void DwfQueueWaitManagementTest::setUp()
{
}

void DwfQueueWaitManagementTest::tearDown()
{
}

void DwfQueueWaitManagementTest::waitManagementCopy()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue<int> testQueue;
    std::mutex synchro_mutex;
    std::condition_variable synchro_cv;
    bool unblocking_pops_done = false;
    bool blocking_pop_ready = false;

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                       1 : Spawn popper thread                      ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    const std::function<void(void)> threadFunction = [&testQueue, &synchro_mutex, &synchro_cv, &unblocking_pops_done, &blocking_pop_ready]()
    {
        int popped = 21;
        testQueue.pop(popped);

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Popped element should not be modified if no elements are received in queue", 21, popped);

        testQueue.pop(popped); // Still doing nothing

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Popped element should not be modified if no elements are received in queue", 21, popped);

        // Wait for unblocking waits
        {
            std::unique_lock<std::mutex> lk(synchro_mutex);
            unblocking_pops_done = true;
            lk.unlock();
            synchro_cv.notify_one();
        }

        {
            std::unique_lock<std::mutex> lk(synchro_mutex);
            synchro_cv.wait(lk, [&blocking_pop_ready]{return blocking_pop_ready;});
        }

        testQueue.pop(popped); // now blocking

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Blocking pop should exit only if element was pushed", 47, popped);
    };
    std::thread readingThread(threadFunction);

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                         2 : Disable Waiting                        ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    testQueue.disableWait();

    {
        std::unique_lock<std::mutex> lk(synchro_mutex);
        synchro_cv.wait(lk, [&unblocking_pops_done]{return unblocking_pops_done;});
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          4 : Enable Waiting                        ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    testQueue.enableWait();

    {
        std::unique_lock<std::mutex> lk(synchro_mutex);
        blocking_pop_ready = true;
        lk.unlock();
        synchro_cv.notify_one();
    }

    testQueue.push(47);

    readingThread.join();
}

void DwfQueueWaitManagementTest::waitManagementMove()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue< std::unique_ptr<int> > testQueue;
    std::mutex synchro_mutex;
    std::condition_variable synchro_cv;
    bool unblocking_pops_done = false;
    bool blocking_pop_ready = false;

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                       1 : Spawn popper thread                      ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    const std::function<void(void)> threadFunction = [&testQueue, &synchro_mutex, &synchro_cv, &unblocking_pops_done, &blocking_pop_ready]()
    {
        std::unique_ptr<int> popped(new int(21));
        testQueue.pop(popped);

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Popped element should not be modified if no elements are received in queue", 21, *popped);

        testQueue.pop(popped); // Still doing nothing

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Popped element should not be modified if no elements are received in queue", 21, *popped);

        // Wait for unblocking waits
        {
            std::unique_lock<std::mutex> lk(synchro_mutex);
            unblocking_pops_done = true;
            lk.unlock();
            synchro_cv.notify_one();
        }

        {
            std::unique_lock<std::mutex> lk(synchro_mutex);
            synchro_cv.wait(lk, [&blocking_pop_ready]{return blocking_pop_ready;});
        }

        testQueue.pop(popped); // now blocking

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Blocking pop should exit only if element was pushed", 47, *popped);
    };
    std::thread readingThread(threadFunction);

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                         2 : Disable Waiting                        ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    testQueue.disableWait();

    {
        std::unique_lock<std::mutex> lk(synchro_mutex);
        synchro_cv.wait(lk, [&unblocking_pops_done]{return unblocking_pops_done;});
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          4 : Enable Waiting                        ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    testQueue.enableWait();

    {
        std::unique_lock<std::mutex> lk(synchro_mutex);
        blocking_pop_ready = true;
        lk.unlock();
        synchro_cv.notify_one();
    }

    std::unique_ptr<int> pushed(new int(47));
    testQueue.push(std::move(pushed));

    readingThread.join();
}

void DwfQueueWaitManagementTest::waitManagementDeletion()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue< std::unique_ptr<int> >* w_queue = new DwfContainers::DwfQueue< std::unique_ptr<int> >();

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                       1 : Spawn popper thread                      ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    const std::function<void(void)> threadFunction = [&w_queue]()
    {
        std::unique_ptr<int> popped;
        w_queue->pop(popped);
    };
    std::thread readingThread(threadFunction);

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           2 : Delete Queue                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(100)); // Wait a little bit to make sure we are waiting for event
    delete w_queue;

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           3 : Join Thread                          ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    readingThread.join();
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
