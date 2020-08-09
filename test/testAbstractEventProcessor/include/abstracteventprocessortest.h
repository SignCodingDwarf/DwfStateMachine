/*!
 * @file abstracteventprocessortest.h
 * @brief Class implementing AbstractEventProcessor unit tests.
 * @author SignC0dingDw@rf
 * @date 08 August 2020
 *
 * Definition of class performing AbstractEventProcessor unit tests. <br>
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

#ifndef ABSTRACT_EVENT_PROCESSOR_TEST_H
#define ABSTRACT_EVENT_PROCESSOR_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Portability.h>

/*! @class AbstractEventProcessorTest
* @brief Unit tests of AbstractEventProcessorTest class
*
* Inherits from TestFixture
*
*/
class AbstractEventProcessorTest : public CPPUNIT_NS::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(AbstractEventProcessorTest);
        CPPUNIT_TEST(testDeletion);
        CPPUNIT_TEST(testPush);
        CPPUNIT_TEST(testSizeLimit);
        CPPUNIT_TEST(testInheritance);
    CPPUNIT_TEST_SUITE_END();

public:
    /*!
    * @brief Constructor of the AbstractEventProcessorTest class
    *
    * Does nothing.
    *
    */
    AbstractEventProcessorTest();

    /*!
    * @brief Desctructor of the AbstractEventProcessorTest class
    *
    * Does nothing.
    *
    */
    ~AbstractEventProcessorTest();

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
    * @brief Check deletion
    *
    * 0) Create pointer to TestEventProcessor. Start event processing.
    * 1) Wait a little bit to make sure we are waiting for events.
    * 2) Force Deletion.
    *
    * No memory error should appear.
    *
    */
    void testDeletion();

    /*!
    * @brief Check pushing events
    *
    * 0) Create TestEventProcessor.
    * 1) Push a few events with different IDs.
    * 2) Start event processing.
    * 3) Push a few other events with different IDs.
    * 4) Check number of events received.
    * 5) Check order of IDs received.
    *
    */
    void testPush();

    /*!
    * @brief Check pushing events behavior if event queue has size limitation
    *
    * 0) Create TestEventProcessor with queue of size N and very long computation time.
    * 1) Push N+1 events with different IDs. Check no exception is raised.
    * 2) Start event processor
    * 3) Push N events with different IDs. Check no exception is raised.
    * 4) Push event and check exception is raised.
    *
    */
    void testSizeLimit();

    /*!
    * @brief Check processing events behavior with subtypes of Dwf::Events
    *
    * 0) Create TestEventProcessor and start it.
    * 1) Push a few IntEvents and StrEvents
    * 2) Check IntEvents content
    * 3) Check StrEvents content
    *
    */
    void testInheritance();

};

#endif // ABSTRACT_EVENT_PROCESSOR_TEST_H

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
