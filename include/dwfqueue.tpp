/*!
 * @file dwfqueue.cpp
 * @brief Class defining a thread safe queue.
 * @author SignC0dingDw@rf
 * @date 18 June 2020
 *
 * Class defining a thread safe size-limited queue.
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

#include "dwfqueue.h"
#include <stdexcept>

namespace DwfContainers
{
    template<class T>
    const size_t DwfQueue<T>::C_NO_SIZE_LIMIT=0;

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                     Constructors and Destructor                    ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    DwfQueue<T>::DwfQueue(size_t max_element_nb) : m_max_element_nb(max_element_nb), m_wait_disabled(false)
    {
    }

    template<class T>
    DwfQueue<T>::~DwfQueue()
    {
        disableWait();
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                            Size Getters                            ///
    ///                                                                    ///
    /////////////////////////////////////////////////////////////////////////
    template<class T>
    bool DwfQueue<T>::empty() const
    {
        std::unique_lock<std::mutex> datalock(m_data_mutex);
        return m_queue.empty();
    }

    template<class T>
    size_t DwfQueue<T>::size() const
    {
        std::unique_lock<std::mutex> datalock(m_data_mutex);
        return m_queue.size();
    }

    template<class T>
    bool DwfQueue<T>::full() const
    {
        if(m_max_element_nb == C_NO_SIZE_LIMIT) // Can't be full if no size limit
        {
            return false;
        }
        else // Otherwise check if we have reached max element number
        {
            std::unique_lock<std::mutex> datalock(m_data_mutex);
            return m_queue.size() == m_max_element_nb;
        }
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                          Wait management                           ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    void DwfQueue<T>::disableWait()
    {
        m_wait_disabled=true;
        m_control_content.notify_all(); // For all threads to exit waiting state
    }

    template<class T>
    void DwfQueue<T>::enableWait()
    {
        m_wait_disabled=false;
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                                Push                                ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    void DwfQueue<T>::push(const T& element)
    {
        if(full())
        {
            throw std::runtime_error("Queue is full. Cannot add element");
        }
        std::unique_lock<std::mutex> datalock(m_data_mutex);
        m_queue.push(element);
        datalock.unlock();
        m_control_content.notify_one();
    }

    template<class T>
    void DwfQueue<T>::push(T&& element)
    {
        if(full())
        {
            throw std::runtime_error("Queue is full. Cannot add element");
        }
        std::unique_lock<std::mutex> datalock(m_data_mutex);
        m_queue.push(std::move(element));
        datalock.unlock();
        m_control_content.notify_one();
    }

    //////////////////////////////////////////////////////////////////////////
    ///                                                                    ///
    ///                                Pop                                 ///
    ///                                                                    ///
    //////////////////////////////////////////////////////////////////////////
    template<class T>
    void DwfQueue<T>::pop(T& element)
    {
        std::unique_lock<std::mutex> datalock(m_data_mutex);
        if(!m_wait_disabled) // Do nothing if we disabled wait
        {
            m_control_content.wait(datalock, [this](){return !m_queue.empty() || m_wait_disabled;}); // Only exit wait if queue is not empty or if deletion has been requested
            element = m_queue.front();
            m_queue.pop();
        }
    }

    template<class T>
    void DwfQueue<T>::pop(T&& element)
    {
        std::unique_lock<std::mutex> datalock(m_data_mutex);
        if(!m_wait_disabled) // Do nothing if we disabled wait
        {
            m_control_content.wait(datalock, [this](){return !m_queue.empty() || m_wait_disabled;}); // Only exit wait if queue is not empty or if deletion has been requested
            element = std::move(m_queue.front());
            m_queue.pop();
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

