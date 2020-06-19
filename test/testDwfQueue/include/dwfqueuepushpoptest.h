/*!
 * @file dwfqueuepushpoptest.h
 * @brief Class implementing DwfQueue push and pop unit tests.
 * @author SignC0dingDw@rf
 * @date 15 June 2020
 *
 * Definition of class performing DwfQueue push and pop unit tests. <br>
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

#ifndef DWF_QUEUE_PUSH_POP_TEST_H
#define DWF_QUEUE_PUSH_POP_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Portability.h>

/*! @class DwfQueuePushPopTest
* @brief Unit tests of DwfQueue push and pop
*
* Inherits from TestFixture
*
*/
class DwfQueuePushPopTest : public CPPUNIT_NS::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(DwfQueuePushPopTest);
        CPPUNIT_TEST(testPushPopCopy);
        CPPUNIT_TEST(testPushPopMove);
        CPPUNIT_TEST(testPushPopCopyFull);
        CPPUNIT_TEST(testPushPopMoveFull);
        CPPUNIT_TEST(testPopBlockingCopy);
        CPPUNIT_TEST(testPopBlockingMove);
    CPPUNIT_TEST_SUITE_END();

public:
    /*!
    * @brief Constructor of the DwfQueuePushPopTest class
    *
    * Does nothing.
    *
    */
    DwfQueuePushPopTest();

    /*!
    * @brief Desctructor of the DwfQueuePushPopTest class
    *
    * Does nothing.
    *
    */
    ~DwfQueuePushPopTest();

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
    * @brief Check push and pop behavior, copy version
    *
    * 0) Create an integer queue.
    * 1) Push a few integers in it.
    * 2) Pop them and check they are extracted in order.
    *
    */
    void testPushPopCopy();

    /*!
    * @brief Check push and pop behavior, move version
    *
    * 0) Create an unique_ptr<int> queue.
    * 1) Push a few unique_ptr in it. Check they are moved.
    * 2) Pop them and check they are extracted in order.
    *
    */
    void testPushPopMove();

    /*!
    * @brief Check push and pop behavior when queue is full
    *
    * 0) Create an integer queue.
    * 1) Push elements until it is full
    * 2) Check that next push triggers an exception
    * 3) Pop element and try to push to check it is available again
    *
    */
    void testPushPopCopyFull();

    /*!
    * @brief Check push and pop behavior, move version, when queue is full
    *
    * 0) Create an unique_ptr<int> queue.
    * 1) Push elements until it is full
    * 2) Check that next push triggers an exception
    * 3) Pop element and try to push to check it is available again
    *
    */
    void testPushPopMoveFull();


    /*!
    * @brief Check pop is indeed
    *
    * 0) Create an int queue.
    * 1) Spawn a waiting thread and wait for elements
    * 2) Wait a bit to check pop does not go out and push elements
    *
    */
    void testPopBlockingCopy();

    /*!
    * @brief Check pop is indeed
    *
    * 0) Create an unique_ptr<int> queue.
    * 1) Spawn a waiting thread and wait for elements
    * 2) Wait a bit to check pop does not go out and push elements
    *
    */
    void testPopBlockingMove();
};

#endif // DWF_QUEUE_PUSH_POP_TEST_H

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
