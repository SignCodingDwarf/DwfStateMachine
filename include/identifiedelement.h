/*!
 * @file identifiedelement.h
 * @brief Class representing elements that can be compared using an identifier.
 * @author SignC0dingDw@rf
 * @date 24 July 2020
 *
 * Template class representing any element that is represented by an id. <br>
 * Two elements are considered identical if their id is identical regardless of any payload they may carry. <br>
 * Id class should contain operator== and copy constructor.
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

#ifndef IDENTIFIED_ELEMENT_H
#define IDENTIFIED_ELEMENT_H

#include <functional>

/*!
* @namespace DwfCommon
* @brief A namespace used to regroup all elements common to dwarven projects
*/
namespace DwfCommon {
    /*! @class IdentifiedElement
    * @brief Class allowing to manage elements represented by an id
    * @tparam T : type of the identifier. Should have operator== and copy constructor
    *
    */
    template<class T>
    class IdentifiedElement
    {
    public:
        /*!
        * @brief Constructor of the IdentifiedElement class
        * @param id : Value of the element id.
        *
        * Constructor of the IdentifiedElement class defining element id.
        *
        */
        IdentifiedElement(T id);

        /*!
        * @brief Overload of operator==
        * @param ref : Element to be compared with.
        * @return true if element have the same id, false otherwise
        *
        * Overload of comparison operator. Only compares IDs to determine element equality.
        *
        */
        bool operator==(const IdentifiedElement<T>& ref) const;

        /*!
        * @brief Get element ID
        * @return Id of the element
        *
        * Constant method
        *
        */
        T getId() const;

    private:
        T m_id; /*!< Id of the element. */
    };

    /*! @class ElementHasher
    * @brief Class allowing to compute hash of an IdentifiedElement.
    * @tparam T : type of the identifier. std::hash<T> should be defined.
    *
    * Compute hash of an IdentifiedElement to use it in unordered containers.
    * Hash is computed only on the element id.
    *
    */
    template<class T>
    struct ElementHasher
    {
        /*!
        * @brief Overload of operator()
        * @param element : element to be hashed
        * @return Hash of the IdentifiedElement
        *
        * Constant method
        *
        */
        std::size_t operator()(const IdentifiedElement<T>& element) const
        {
            return std::hash<T>()(element.getId());
        }
    };
}

#include "identifiedelement.tpp"

#endif // IDENTIFIED_ELEMENT_H

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
