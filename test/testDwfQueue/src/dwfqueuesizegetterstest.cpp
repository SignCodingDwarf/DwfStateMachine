/*!
 * @file dwfqueuesizegetterstest.cpp
 * @brief Class implementing DwfQueue size getters unit tests.
 * @author SignC0dingDw@rf
 * @date 11 June 2020
 *
 * Implementation of class performing DwfQueue size getters unit tests. <br>
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

#include "dwfqueuesizegetterstest.h"
#include "dwfqueue.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DwfQueueSizeGettersTest);

DwfQueueSizeGettersTest::DwfQueueSizeGettersTest()
{
}

DwfQueueSizeGettersTest::~DwfQueueSizeGettersTest()
{
}

void DwfQueueSizeGettersTest::setUp()
{
}

void DwfQueueSizeGettersTest::tearDown()
{
}

void DwfQueueSizeGettersTest::testEmpty()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue<int> testQueue;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Queue is empty at creation", true, testQueue.empty());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          1 : Push Element                          ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    // Element pushed
    testQueue.push(1);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Queue is not empty if elements are pushed", false, testQueue.empty());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           2 : Pop Element                          ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    // Element popped
    int popped=0;
    testQueue.pop(popped);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Queue is not empty if all elements are popped", true, testQueue.empty());
}

void DwfQueueSizeGettersTest::testSize()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue<size_t> testQueue;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Initial size is 0", size_t(0), testQueue.size());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                      1 : Size increase on push                     ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    // Push a few elements
    for(size_t i = 1; i <= 10; ++i)
    {
        testQueue.push(i);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Size is not correctly increased when pushing elements", i, testQueue.size());
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                       2 : Size decrease on pop                     ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    // Pop them
    for(size_t i = 1; i <= 10; ++i)
    {
        size_t elem;
        testQueue.pop(elem);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Size is not correctly decreased when popping elements", 10-i, testQueue.size());
    }
}

void DwfQueueSizeGettersTest::testFullNoLimit()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue<int> testQueue;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Queue is not full at init", false, testQueue.full());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           1 : Push a lot                           ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(int i=0; i<1000000; ++i)
    {
        testQueue.push(i);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Unlimited Queue is never full", false, testQueue.full());
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///          2 : Same with explicit no size limit construction         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfContainers::DwfQueue<int> testQueue2(DwfContainers::DwfQueue<int>::C_NO_SIZE_LIMIT);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Queue is not full at init", false, testQueue2.full());
    for(int i=0; i<1000000; ++i)
    {
        testQueue2.push(i);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Unlimited Queue is never full", false, testQueue2.full());
    }
}

void DwfQueueSizeGettersTest::testFullLimit()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    size_t queueSize=20;
    DwfContainers::DwfQueue<size_t> testQueue(20);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Queue is not full at init", false, testQueue.full());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///            1 : Push elements until we reach size limit - 1         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(size_t i=1; i<=queueSize-1; ++i)
    {
        testQueue.push(i);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Queue is not full till max size is reached", false, testQueue.full());
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                  2 : Push element to make queue full               ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    testQueue.push(42);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Queue is now full", true, testQueue.full());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                            3 : Pop element                         ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    size_t elem=0;
    testQueue.pop(elem);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("popping element makes queue no longer full", false, testQueue.full());
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
