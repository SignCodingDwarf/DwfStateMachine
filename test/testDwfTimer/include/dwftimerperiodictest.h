/*!
 * @file dwftimerperiodictest.h
 * @brief Class implementing DwfTimer periodic timer unit tests.
 * @author SignC0dingDw@rf
 * @date 30 September 2020
 *
 * Definition of class performing DwfTimer periodic timer unit tests. <br>
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

#ifndef DWF_TIMER_PERIODIC_TEST_H
#define DWF_TIMER_PERIODIC_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Portability.h>
#include "dwfstate.h"

/*! @class DwfTimerPeriodicTest
* @brief Unit tests of DwfTimer periodic behavior
*
* Inherits from TestFixture
*
*/
class DwfTimerPeriodicTest : public CPPUNIT_NS::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(DwfTimerPeriodicTest);
        CPPUNIT_TEST(testStartStop);
        CPPUNIT_TEST(testDelete);
        CPPUNIT_TEST(testStartedConfigure);
        CPPUNIT_TEST(testPeriod);
    CPPUNIT_TEST_SUITE_END();

public:
    /*!
    * @brief Constructor of the DwfTimerPeriodicTest class
    *
    * Does nothing.
    *
    */
    DwfTimerPeriodicTest();

    /*!
    * @brief Desctructor of the DwfTimerPeriodicTest class
    *
    * Does nothing.
    *
    */
    ~DwfTimerPeriodicTest();

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
    * @brief Check periodic timer start stop behavior
    *
    * 0) Create a periodic timer.
    * 1) Start it and let it run during some time.
    * 2) Stop it and check it executed the required number of times.
    * 3) Start it again with different period
    * 4) Stop it and check it executed the required number of times.
    *
    */
    void testStartStop();

    /*!
    * @brief Check behavior on deletion
    *
    * 0) Create and configure periodic timer.
    * 1) Start it
    * 2) Delete it and check it is stopped without calling timeout method
    *
    */
    void testDelete();

    /*!
    * @brief Check configuration behavior with started timer
    *
    * 0) Create and configure periodic timer.
    * 1) Start it.
    * 2) Try changing configuration.
    * 3) Stop timer and check configuration was not changed
    *
    */
    void testStartedConfigure();

    /*!
    * @brief Check periodic timer respect of given period with long computations
    *
    * 0) Create a periodic timer and associate it a function that takes a long computation time
    * 1) Start it and let it run during some time.
    * 2) Stop it and check it executed the required number of times.
    *
    */
    void testPeriod();
};

#endif // DWF_TIMER_PERIODIC_TEST_H

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
