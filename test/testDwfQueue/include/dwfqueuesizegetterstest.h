/*!
 * @file dwfqueueziegetterstest.h
 * @brief Class implementing DwfQueue size getters unit tests.
 * @author SignC0dingDw@rf
 * @date 11 June 2020
 *
 * Definition of class performing DwfQueue size getters unit tests. <br>
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

#ifndef DWF_QUEUE_SIZE_GETTERS_TEST_H
#define DWF_QUEUE_SIZE_GETTERS_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Portability.h>
#include "dwfstate.h"

/*! @class DwfQueueSizeGettersTest
* @brief Unit tests of DwfQueue size getters
*
* Inherits from TestFixture
*
*/
class DwfQueueSizeGettersTest : public CPPUNIT_NS::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(DwfQueueSizeGettersTest);
        CPPUNIT_TEST(testEmpty);
        CPPUNIT_TEST(testSize);
        CPPUNIT_TEST(testFullNoLimit);
        CPPUNIT_TEST(testFullLimit);
    CPPUNIT_TEST_SUITE_END();

public:
    /*!
    * @brief Constructor of the DwfQueueSizeGettersTest class
    *
    * Does nothing.
    *
    */
    DwfQueueSizeGettersTest();

    /*!
    * @brief Desctructor of the DwfQueueSizeGettersTest class
    *
    * Does nothing.
    *
    */
    ~DwfQueueSizeGettersTest();

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
    * @brief Check empty behavior
    *
    * 0) Check that at init queue is empty.
    * 1) Check that pushing element makes queue not empty.
    * 2) Check that queue is empty after element is popped.
    *
    */
    void testEmpty();

    /*!
    * @brief Check size behavior
    *
    * 0) Check that at init size is 0.
    * 1) Push a few elements and check that size increases.
    * 2) Pop elements and check that size decreases.
    *
    */
    void testSize();

    /*!
    * @brief Check full behavior when no size limit has been defined
    *
    * 0) Construst queue with default constructor (should have no size limit).
    * 0) Check that queue is not full at init
    * 1) Push a lot of elements and check that it is still not full.
    * 2) Do the same by explicitly calling constructor with C_NO_SIZE_LIMIT as queue size.
    *
    */
    void testFullNoLimit();

    /*!
    * @brief Check full behavior when a size limit has been defined
    *
    * 0) Construst queue with a size.
    * 0) Check that queue is not full at init.
    * 1) Push elements up to size-1 and check it is still not full.
    * 2) Push a last element and check it is now full.
    * 3) Pop an element an check it is no longer full.
    *
    */
    void testFullLimit();
};

#endif // DWF_QUEUE_SIZE_GETTERS_TEST_H

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
