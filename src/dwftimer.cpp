/*!
 * @file dwftimer.cpp
 * @brief Class defining an event-based timer.
 * @author SignC0dingDw@rf
 * @date 30 September 2020
 *
 * Class defining an event-based timer. Timer can be either single-shot or periodic.
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

#include "dwftimer.h"

namespace DwfTime
{
    DwfTimer::DwfTimer() : m_started(false), m_is_single_shot(true), m_timer_period(std::chrono::microseconds(0u))
    {

    }

    DwfTimer::~DwfTimer()
    {
        stop();
    }

    void DwfTimer::callOnTimeout(TimeoutFunction called_on_timeout)
    {
        if(!m_started) // We do not alter object if timer is running
        {
            m_called_on_timeout = called_on_timeout;
        }
    }

    bool DwfTimer::isStarted() const
    {
        return m_started;
    }

    void DwfTimer::setSingleShot(bool is_single_shot)
    {
        if(!m_started) // We do not alter object if timer is running
        {
            m_is_single_shot = is_single_shot;
        }
    }

    void DwfTimer::start()
    {
        stop(); // Stop timer

        // Restart it
        m_started=true;
        m_wait_thread=std::thread([this]{waitTimeout();});
    }

    void DwfTimer::waitTimeout()
    {
        std::chrono::microseconds computation_time(0); // Duration of computation
        std::chrono::microseconds timer_duration(0);
        do
        {
            timer_duration=m_timer_period-computation_time; // Reduced timer period by computation duration to keep average execution
            std::unique_lock<std::mutex> lock(m_cv_mutex);
            if(m_timeout_wait.wait_for(lock,timer_duration) == std::cv_status::timeout) // If we didn't exit on timeout, we do nothing
            {
                std::chrono::steady_clock::time_point start_time=std::chrono::steady_clock::now();
                if(m_called_on_timeout) // If we have something to do
                {
                    m_called_on_timeout();
                }
                computation_time=std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-start_time); // Compute function execution duration to adjust loop time
            }
        }while(m_started && !m_is_single_shot); // Execute while started or not single shot timer
        m_started=false; // Timer is stopped
    }

    void DwfTimer::stop()
    {
        m_started = false;
        {
            std::unique_lock<std::mutex> lock(m_cv_mutex);
            m_timeout_wait.notify_one();
        }
        if(m_wait_thread.joinable())
        {
            m_wait_thread.join();
        }
    }
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
