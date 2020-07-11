/*!
 * @file dwfqueuepushpoptest.cpp
 * @brief Class implementing DwfQueue push and pop unit tests.
 * @author SignC0dingDw@rf
 * @date 11 July 2020
 *
 * Implementation of class performing DwfQueue push and pop unit tests. <br>
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

#include "dwfqueuepushpoptest.h"
#include "dwfqueue.h"
#include <memory>
#include <stdexcept>
#include <thread>
#include <chrono>

CPPUNIT_TEST_SUITE_REGISTRATION(DwfQueuePushPopTest);

DwfQueuePushPopTest::DwfQueuePushPopTest()
{
}

DwfQueuePushPopTest::~DwfQueuePushPopTest()
{
}

void DwfQueuePushPopTest::setUp()
{
}

void DwfQueuePushPopTest::tearDown()
{
}

void DwfQueuePushPopTest::testPushPopCopy()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue<int> testQueue;

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          1 : Push Elements                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(int i=1; i<=100; ++i)
    {
        testQueue.push(3*i);
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           2 : Pop Elements                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(int i=1; i<=100; ++i)
    {
        // Element popped
        int popped=0;
        testQueue.pop(popped);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Elements not extracted in order of push", 3*i, popped);
    }
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Queue should be empty if all elements are popped", true, testQueue.empty());
}

void DwfQueuePushPopTest::testPushPopMove()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue< std::unique_ptr<int> > testQueue;

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          1 : Push Elements                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(int i=1; i<=100; ++i)
    {
        std::unique_ptr<int> pushed_ptr(new int(4*i));
        testQueue.push(std::move(pushed_ptr));
        bool pointer_empty=true;
        if(pushed_ptr)
        {
            pointer_empty = false;
        }
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Unique pointers should be moved after push", true, pointer_empty);
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           2 : Pop Elements                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(int i=1; i<=100; ++i)
    {
        // Element popped
        std::unique_ptr<int> popped;
        testQueue.pop(popped);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Elements not extracted in order of push", 4*i, *popped);
    }
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Queue should be empty if all elements are popped", true, testQueue.empty());
}

void DwfQueuePushPopTest::testPushPopCopyFull()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue<int> testQueue(5);

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           1 : Fill Queue                           ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(int i=1; i<=5; ++i)
    {
        testQueue.push(i);
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                      2 : Push triggers exception                   ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    CPPUNIT_ASSERT_THROW_MESSAGE("Push on full queue should throw exception", testQueue.push(1), std::runtime_error);

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                 3 : Pop Element and push should work               ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    int popped = 0;
    testQueue.pop(popped);
    CPPUNIT_ASSERT_NO_THROW_MESSAGE("After popping push should be available again", testQueue.push(1));
}

void DwfQueuePushPopTest::testPushPopMoveFull()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue< std::unique_ptr<int> > testQueue(3);

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           1 : Fill Queue                           ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(int i=1; i<=3; ++i)
    {
        std::unique_ptr<int> pushed(new int(i));
        testQueue.push(std::move(pushed));
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                      2 : Push triggers exception                   ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<int> pushed(new int(3));
    CPPUNIT_ASSERT_THROW_MESSAGE("Push on full queue should throw exception", testQueue.push(std::move(pushed)), std::runtime_error);

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                 3 : Pop Element and push should work               ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<int> popped;
    testQueue.pop(popped);
    CPPUNIT_ASSERT_NO_THROW_MESSAGE("After popping push should be available again", testQueue.push(std::move(popped)));
}

void DwfQueuePushPopTest::testPopBlockingCopy()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue<int> testQueue;

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                       1 : Spawn popper thread                      ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    const std::function<void(void)> threadFunction = [&testQueue]()
    {
        for(int i=1; i <= 10; ++i)
        {
            int popped;
            testQueue.pop(popped);
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Pop should get elements in order", i*10, popped);
        }
    };
    std::thread readingThread(threadFunction);

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          2 : Push Elements                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(int i=1; i<=10; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        testQueue.push(10*i);
    }

    readingThread.join();
}

void DwfQueuePushPopTest::testPopBlockingMove()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue< std::unique_ptr<int> > testQueue;

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                       1 : Spawn popper thread                      ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    const std::function<void(void)> threadFunction = [&testQueue]()
    {
        for(int i=1; i <= 10; ++i)
        {
            std::unique_ptr<int> popped;
            testQueue.pop(popped);
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Pop should get elements in order", i*10, *popped);
        }
    };
    std::thread readingThread(threadFunction);

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          2 : Push Elements                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(int i=1; i<=10; ++i)
    {
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        std::unique_ptr<int> pushed(new int(10*i));
        testQueue.push(std::move(pushed));
    }

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
