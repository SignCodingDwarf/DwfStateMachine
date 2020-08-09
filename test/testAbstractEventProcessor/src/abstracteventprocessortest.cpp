/*!
 * @file abstracteventprocessortest.cpp
 * @brief Class implementing AbstractEventProcessor unit tests.
 * @author SignC0dingDw@rf
 * @date 08 August 2020
 *
 * Implementation of class performing AbstractEventProcessor unit tests. <br>
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

#include "abstracteventprocessortest.h"
#include "testeventprocessor.h"

#include <chrono>

CPPUNIT_TEST_SUITE_REGISTRATION(AbstractEventProcessorTest);

AbstractEventProcessorTest::AbstractEventProcessorTest()
{
}

AbstractEventProcessorTest::~AbstractEventProcessorTest()
{
}

void AbstractEventProcessorTest::setUp()
{
}

void AbstractEventProcessorTest::tearDown()
{
}

void AbstractEventProcessorTest::testDeletion()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestEventProcessor* ev_processor = new TestEventProcessor();
    ev_processor->start();

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              1 : Wait                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::this_thread::sleep_for (std::chrono::milliseconds(100));


    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             2 : Delete                             ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    delete ev_processor;
}

void AbstractEventProcessorTest::testPush()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestEventProcessor ev_processor;
    uint32_t event_nb=10;

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              1 : Push                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(EventSystem::EventID i=1; i<=event_nb; ++i)
    {
        std::unique_ptr<EventSystem::DwfEvent> ev(new EventSystem::DwfEvent(i));
        ev_processor.pushEvent(std::move(ev));
    }

    // Wait a little bit for events to be processed
    std::this_thread::sleep_for (std::chrono::milliseconds(100));

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             2 : Start                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    ev_processor.start();

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              3 : Push                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(EventSystem::EventID i=event_nb+1; i<=2*event_nb; ++i)
    {
        std::unique_ptr<EventSystem::DwfEvent> ev(new EventSystem::DwfEvent(i));
        ev_processor.pushEvent(std::move(ev));
    }

    // Wait a little bit for events to be processed
    std::this_thread::sleep_for (std::chrono::milliseconds(100));

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                       4 : Check event number                       ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    CPPUNIT_ASSERT_EQUAL_MESSAGE("All events after start should have been processed", event_nb, ev_processor.getProcessedEventsNumber());

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                        5 : Check event order                       ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::vector<EventSystem::EventID> received_ids = ev_processor.getReceivedIds();
    for(uint32_t i=1; i<=received_ids.size(); ++i)
    {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Events have not been received in order", i+event_nb, received_ids[i-1]);
    }
}

void AbstractEventProcessorTest::testSizeLimit()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestEventProcessor ev_processor(5, std::chrono::milliseconds(1000));

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              2 : Push                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(EventSystem::EventID i=1; i<=7; ++i)
    {
        std::unique_ptr<EventSystem::DwfEvent> ev(new EventSystem::DwfEvent(i));
        CPPUNIT_ASSERT_NO_THROW_MESSAGE("Pushing events when not started causes no exception because events are dropped",ev_processor.pushEvent(std::move(ev)));
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                             2 : Start                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    ev_processor.start();

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              3 : Push                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    for(EventSystem::EventID i=1; i<=5; ++i)
    {
        std::unique_ptr<EventSystem::DwfEvent> ev(new EventSystem::DwfEvent(i));
        CPPUNIT_ASSERT_NO_THROW_MESSAGE("Pushing events when queue is not full should not trigger exception",ev_processor.pushEvent(std::move(ev)));
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                        4 : Push on full queue                      ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<EventSystem::DwfEvent> ev(new EventSystem::DwfEvent(12));
    CPPUNIT_ASSERT_THROW_MESSAGE("Pushing events when queue is full should trigger exception",ev_processor.pushEvent(std::move(ev)), std::runtime_error);

}

void AbstractEventProcessorTest::testInheritance()
{
    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              0 : Init                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    TestEventProcessor ev_processor;
    ev_processor.start();

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                              1 : Push                              ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::unique_ptr<IntEvent> ev(new IntEvent(23));
    std::unique_ptr<StrEvent> ev2(new StrEvent("Chewbacca"));
    std::unique_ptr<IntEvent> ev3(new IntEvent(45));
    std::unique_ptr<StrEvent> ev4(new StrEvent("is a wookie"));
    std::unique_ptr<IntEvent> ev5(new IntEvent(67));
    std::unique_ptr<IntEvent> ev6(new IntEvent(89));

    ev_processor.pushEvent(std::move(ev));
    ev_processor.pushEvent(std::move(ev2));
    ev_processor.pushEvent(std::move(ev3));
    ev_processor.pushEvent(std::move(ev4));
    ev_processor.pushEvent(std::move(ev5));
    ev_processor.pushEvent(std::move(ev6));

    // Wait a little bit for events to be processed
    std::this_thread::sleep_for (std::chrono::milliseconds(100));

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                        2 : Check int events                        ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::vector<int> received_int_vals = ev_processor.getIntEventsVal();
    size_t int_vals_size = 4;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should have received 4 int events", int_vals_size, received_int_vals.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Error on event 0", 23, received_int_vals[0]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Error on event 1", 45, received_int_vals[1]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Error on event 2", 67, received_int_vals[2]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Error on event 3", 89, received_int_vals[3]);

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                        3 : Check str events                        ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    std::vector<std::string> received_str_vals = ev_processor.getStrEventsVal();
    size_t str_vals_size = 2;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should have received 2 str events", str_vals_size, received_str_vals.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Error on event 0", std::string("Chewbacca"), received_str_vals[0]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Error on event 1", std::string("is a wookie"), received_str_vals[1]);
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
