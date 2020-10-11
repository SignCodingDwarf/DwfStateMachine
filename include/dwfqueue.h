/*!
 * @file dwfqueue.h
 * @brief Class defining a thread safe queue.
 * @author SignC0dingDw@rf
 * @date 11 October 2020
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

#ifndef DWF_QUEUE_H
#define DWF_QUEUE_H

#include <queue>
#include <cstdint>
#include <mutex>
#include <condition_variable>
#include <atomic>

/*!
* @namespace DwfContainers
* @brief A namespace used to regroup all elements related to data containers
*/
namespace DwfContainers
{
    /*! @class DwfQueue
    * @brief Class a thread safe size-limited queue
    * @tparam T : type of elements stored in queue
    *
    * Queue size limitation (if any) is defined at queue creation and cannot be changed afterwards.
    *
    */
    template<class T>
    class DwfQueue
    {
    public:
        static const size_t C_NO_SIZE_LIMIT; /*!< Definition of a specific value to indicate queue has no size limitation.*/

        //////////////////////////////////////////////////////////////////////////
        ///                                                                    ///
        ///                     Constructors and Destructor                    ///
        ///                                                                    ///
        //////////////////////////////////////////////////////////////////////////
        /*!
        * @brief Constructor of DwfQueue class
        * @param max_element_nb : Max number of elements that can be stored in queue. Default indicates no size limitation.
        *
        * Constructor of the DwfQueue class setting queue size limitation.
        *
        */
        DwfQueue(size_t max_element_nb = C_NO_SIZE_LIMIT);

        /*!
        * @brief Destructor of DwfQueue class
        *
        * Activates the deletion flag and send a global notification ensuring all waiting thread are freed.
        * Flag also ensures no other thread start waiting
        *
        */
        ~DwfQueue();

        //////////////////////////////////////////////////////////////////////////
        ///                                                                    ///
        ///                            Size Getters                            ///
        ///                                                                    ///
        //////////////////////////////////////////////////////////////////////////
        /*!
        * @brief Indicated whether queue is empty
        * @return true if queue is empty, false otherwise
        *
        * Const method
        *
        */
        bool empty() const;

        /*!
        * @brief Indicates number of elements stored in queue
        * @return Number of elements in queue
        *
        * Const method
        *
        */
        size_t size() const;

        /*!
        * @brief Indicates if queue has reached its size limitation
        * @return true queue is full, false otherwise
        *
        * Const method
        * If the queue is not size limited, this method always returns false
        *
        */
        bool full() const;

        //////////////////////////////////////////////////////////////////////////
        ///                                                                    ///
        ///                          Wait management                           ///
        ///                                                                    ///
        //////////////////////////////////////////////////////////////////////////
        /*!
        * @brief Disable wait of elements in queue
        *
        * Disable wait for queue to contain element in pop method.
        * Also unlocks all waiting threads.
        * Especially used during queue desctruction
        *
        */
        void disableWait();

        /*!
        * @brief Enable wait for elements in queue
        *
        */
        void enableWait();

        //////////////////////////////////////////////////////////////////////////
        ///                                                                    ///
        ///                               Clear                                ///
        ///                                                                    ///
        //////////////////////////////////////////////////////////////////////////
        /*!
        * @brief Delete all elements in queue
        *
        */
        void clear();

        //////////////////////////////////////////////////////////////////////////
        ///                                                                    ///
        ///                                Push                                ///
        ///                                                                    ///
        //////////////////////////////////////////////////////////////////////////
        /*!
        * @brief Push an element by copy
        * @param element : Reference to the element to push to queue
        *
        * Push an element if queue is not full and notify one of the waiting threads that an element is available.
        * If queue is full, throws an exception.
        *
        */
        void push(const T& element);

        /*!
        * @brief Push an element using move semantics
        * @param element : Reference to the element to push to queue
        *
        * Push an element if queue is not full and notify one of the waiting threads that an element is available.
        * If queue is full, throws an exception. And element is not moved.
        *
        */
        void push(T&& element);

        //////////////////////////////////////////////////////////////////////////
        ///                                                                    ///
        ///                                Pop                                 ///
        ///                                                                    ///
        //////////////////////////////////////////////////////////////////////////
        /*!
        * @brief Pop an element by copy
        * @param element : Reference to the element to copy queue head to
        *
        * Wait for an element to be available in queue then copy it to argument and remove it from queue.
        * Calling to pop locks current thread until an element has been pushed to queue.
        *
        */
        void pop(T& element);

    private:
        std::queue<T> m_queue; /*!< Elements container.*/

        const size_t m_max_element_nb; /*!< Maximum size of the queue.*/

        mutable std::mutex m_data_mutex; /*!< Mutex controlling access to the container data.*/

        std::condition_variable m_control_content; /*!< Condition variable used to wait for data in the queue.*/

        std::atomic<bool> m_wait_disabled; /*!< Flag indicating that waiting for elements is disabled (ex: when queue is deleted). All waiting thread must be notified and no thread can wait any longer. */
    };
}

#include "dwfqueue.tpp"

#endif //DWF_QUEUE_H

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
