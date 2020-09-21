/*!
 * @file dwftimerstatictimerstest.cpp
 * @brief Class implementing DwfTimer static timer methods unit tests.
 * @author SignC0dingDw@rf
 * @date 26 September 2020
 *
 * Implementation of class implementing DwfTimer static timer methods unit tests.. <br>
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

#include "dwftimerstatictimerstest.h"
#include "dwftimer.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DwfTimerStaticTimersTest);

DwfTimerStaticTimersTest::DwfTimerStaticTimersTest()
{
}

DwfTimerStaticTimersTest::~DwfTimerStaticTimersTest()
{
}

void DwfTimerStaticTimersTest::setUp()
{
}

void DwfTimerStaticTimersTest::tearDown()
{
}

/*! @class TimeDelta
* @brief Fonctor class to measure elapsed time in timer
*
*/
class TimeDelta
{
public:
    /*!
    * @brief Constructor of the TimeDelta class
    *
    * Inits reference point for elapsed time measurement
    *
    */
    TimeDelta(std::chrono::seconds timer_duration) : m_start_time(std::chrono::steady_clock::now()), m_timer_duration(timer_duration), m_called(false)
    {
    }

    /*!
    * @brief Check elapsed time
    *
    * Test that elapsed time since object construction is equal to expected timer duration.
    *
    */
    void operator()()
    {
        std::chrono::seconds elapsed=std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now()-m_start_time);
        m_called=true;

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Timer duration does not match expected duration", m_timer_duration.count(), elapsed.count());
    }

    /*!
    * @brief Check operator() has been called
    * @return true if it was called, false otherwise
    *
    */
    bool wasCalled() const
    {
        return m_called;
    }

private:
    std::chrono::steady_clock::time_point m_start_time; /*!< Start time for duration measurement.*/
    std::chrono::seconds m_timer_duration; /*!< Expected timer duration in seconds.*/
    bool m_called; /*!< Flag indicating that operator() method has been called.*/
};

void DwfTimerStaticTimersTest::testStaticSingleShot()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::chrono::seconds timer_duration(2);
    TimeDelta delta(timer_duration);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Duration measurement not done", false, delta.wasCalled());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                           1 : Start Timer                          ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    DwfTime::DwfTimer::startSingleShot(timer_duration, std::ref(delta)); // Pass functor as ref to update member
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Duration measurement done", true, delta.wasCalled());
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
