/*!
 * @file dwfqueuewaitmanagement.h
 * @brief Class implementing DwfQueue wait management unit tests.
 * @author SignC0dingDw@rf
 * @date 11 July 2020
 *
 * Definition of class performing DwfQueue wait management unit tests. <br>
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

#ifndef DWF_QUEUE_WAIT_MANAGEMENT_TEST_H
#define DWF_QUEUE_WAIT_MANAGEMENT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Portability.h>
#include "dwfstate.h"

/*! @class DwfQueueWaitManagementTest
* @brief Unit tests of DwfQueue wait management
*
* Inherits from TestFixture
*
*/
class DwfQueueWaitManagementTest : public CPPUNIT_NS::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(DwfQueueWaitManagementTest);
        CPPUNIT_TEST(waitManagementCopy);
        CPPUNIT_TEST(waitManagementMove);
        CPPUNIT_TEST(waitManagementDeletion);
    CPPUNIT_TEST_SUITE_END();

public:
    /*!
    * @brief Constructor of the DwfQueueWaitManagementTest class
    *
    * Does nothing.
    *
    */
    DwfQueueWaitManagementTest();

    /*!
    * @brief Desctructor of the DwfQueueWaitManagementTest class
    *
    * Does nothing.
    *
    */
    ~DwfQueueWaitManagementTest();

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
    * @brief Check wait management behavior copy version
    *
    * 0) Create an int queue.
    * 1) Spawn a waiting thread and wait for elements.
    * 2) Disable waiting and check thread exits without any element being pushed.
    * 3) Try to wait again and check that thread does not wait
    * 4) Enable waiting and check that an element must be pushed for wait to end.
    *
    */
    void waitManagementCopy();

    /*!
    * @brief Check wait management behavior move verion
    *
    * 0) Create an unique_ptr<int> queue.
    * 1) Spawn a waiting thread and wait for elements.
    * 2) Disable waiting and check thread exits without any element being pushed.
    * 3) Try to wait again and check that thread does not wait
    * 4) Enable waiting and check that an element must be pushed for wait to end.
    *
    */
    void waitManagementMove();

    /*!
    * @brief Check wait management behavior when deleting queue
    *
    * 0) Create a pointer on unique_ptr<int> queue.
    * 1) Spawn a waiting thread and wait for elements.
    * 2) Delete existing queue.
    * 3) Join waiting thread
    *
    * No test is really performed, the aim is simply to check no memory error are produced when deleting queue
    *
    */
    void waitManagementDeletion();
};

#endif // DWF_QUEUE_WAIT_MANAGEMENT_TEST_H

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
