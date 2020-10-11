/*!
 * @file dwftimer.h
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

#ifndef DWF_TIMER_H
#define DWF_TIMER_H

#include <chrono>
#include <atomic>
#include <functional>
#include <thread>
#include <condition_variable>
#include <mutex>

/*!
* @namespace DwfTime
* @brief A namespace used to regroup all elements related to time management
*/
namespace DwfTime
{
    /*! @class DwfTimer
    * @brief Class defining an event-based timer
    *
    * Timer can be either single-shot or periodic.
    * Class also allows to statically start a single shot timer.
    * Interface is freely based on QTimer : https://doc.qt.io/qt-5/qtimer.html
    * Timeout is waited using a condition variable so that it can be interrupted with minimal time loss (i.e. without having to wait for wait to complete).
    *
    */
    class DwfTimer
    {
    public:
        /*! @typedef TimeoutFunction
        *  @brief Signature of a function to call on timeout
        */
        using TimeoutFunction = std::function<void(void)>;

        //////////////////////////////////////////////////////////////////////////
        ///                                                                    ///
        ///                           Static members                           ///
        ///                                                                    ///
        //////////////////////////////////////////////////////////////////////////
        /*!
        * @brief Start a single shot timer
        * @param timer_duration : duration of timer before timeout
        * @param called_on_timeout : call to perform on timeout
        *
        * Service if you need to delay call of a function by a certain duration.
        * Timer cannot be stopped.
        * Function is not called in a new thread, but you can detach it in another thread.
        * Static method.
        *
        */
        template< class Rep, class Period >
        static void startSingleShot(const std::chrono::duration<Rep,Period>& timer_duration, TimeoutFunction called_on_timeout);

        //////////////////////////////////////////////////////////////////////////
        ///                                                                    ///
        ///                     Constructors and Destructor                    ///
        ///                                                                    ///
        //////////////////////////////////////////////////////////////////////////
        /*!
        * @brief Constructor of DwfTimer class
        *
        * Constructor of the DwfTimer class.
        * Default constructed timer is a not started, single shot timer with an execution period of 0 (i.e. function is called instantly) and no timeout function to call.
        *
        */
        DwfTimer();

        /*!
        * @brief Destructor of DwfTimer class
        *
        * Stop timer thread if launched.
        *
        */
        ~DwfTimer();

        //////////////////////////////////////////////////////////////////////////
        ///                                                                    ///
        ///                            Configuration                           ///
        ///                                                                    ///
        //////////////////////////////////////////////////////////////////////////
        /*!
        * @brief Set function to call on timeout
        * @param called_on_timeout : function to call on timeout
        *
        * Set function to call on timer timeout.
        * This function can only be set if timer is not running.
        *
        */
        void callOnTimeout(TimeoutFunction called_on_timeout);

        /*!
        * @brief Indicate if timer is single shot
        * @param is_single_shot : true if timer is single shot, false if it is periodic
        *
        * Set to true to get a single shot timer and flase to get a periodic timer
        * Can only be set if timer is not running.
        *
        */
        void setSingleShot(bool is_single_shot);

        /*!
        * @brief Set timer period or duration
        * @param timer_period : timer period or duration
        *
        * Set period of a periodic timer or duration of a single shot timer
        * Can only be set if timer is not running.
        *
        */
        template< class Rep, class Period >
        void setPeriod(const std::chrono::duration<Rep,Period>& timer_period);

        //////////////////////////////////////////////////////////////////////////
        ///                                                                    ///
        ///                              Getters                               ///
        ///                                                                    ///
        //////////////////////////////////////////////////////////////////////////
        /*!
        * @brief Indicates if timer is started
        * @return true if timer is started false otherwise
        *
        * Constant method.
        *
        */
        bool isStarted() const;

        //////////////////////////////////////////////////////////////////////////
        ///                                                                    ///
        ///                           Start and Stop                           ///
        ///                                                                    ///
        //////////////////////////////////////////////////////////////////////////
        /*!
        * @brief Start timer or restart timer
        *
        * Start timer in a dedicated thread.
        * If timer is running, it is stopped before being restarted.
        *
        */
        void start();

        /*!
        * @brief Stop timer
        *
        * Stop timer and join wait thread.
        *
        */
        void stop();

    private:
        /*!
        * @brief Function used to wait for timer timeout and execute desired function
        */
        void waitTimeout();

        std::atomic<bool> m_started; /*!< Flag indicating if timer has been started.*/

        TimeoutFunction m_called_on_timeout; /*!< Function to call on timer timeout.*/

        std::atomic<bool> m_is_single_shot; /*!< Flag indicating if timer has been started.*/

        std::chrono::microseconds m_timer_period; /*!< Timer period in microseconds.*/

        mutable std::mutex m_cv_mutex; /*!< Mutex protecting the condition variable. */

        std::condition_variable m_timeout_wait; /*!< Condition variable used to wait for timeout. */

        std::thread m_wait_thread; /*!< Thread in which wait and called function are to be executed. */
    };

    template< class Rep, class Period >
    void DwfTimer::startSingleShot(const std::chrono::duration<Rep, Period>& timer_duration, TimeoutFunction called_on_timeout)
    {
        std::this_thread::sleep_for(timer_duration);
        called_on_timeout();
    }

    template< class Rep, class Period >
    void DwfTimer::setPeriod(const std::chrono::duration<Rep,Period>& timer_period)
    {
        if(!m_started) // We do not alter object if timer is running
        {
            m_timer_period = std::chrono::duration_cast<std::chrono::microseconds>(timer_period);
        }
    }

}

#endif //DWF_TIMER_H

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
