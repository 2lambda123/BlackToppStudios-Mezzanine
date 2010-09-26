//© Copyright 2010 BlackTopp Studios Inc.
/* This file is part of The PhysGame Engine.

    The PhysGame Engine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The PhysGame Engine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The PhysGame Engine.  If not, see <http://www.gnu.org/licenses/>.
*/
/* The original authors have included a copy of the license specified above in the
   'Docs' folder. See 'gpl.txt'
*/
/* We welcome the use of The PhysGame anyone, including companies who wish to
   Build professional software and charge for their product.

   However there are some practical restrictions, so if your project involves
   any of the following you should contact us and we will try to work something
   out:
    - DRM or Copy Protection of any kind(except Copyrights)
    - Software Patents You Do Not Wish to Freely License
    - Any Kind of Linking to Non-GPL licensed Works
    - Are Currently In Violation of Another Copyright Holder's GPL License
    - If You want to change our code and not add a few hundred MB of stuff to
        your distribution

   These and other limitations could cause serious legal problems if you ignore
   them, so it is best to simply contact us or the Free Software Foundation, if
   you have any questions.

   Joseph Toppi - toppij@gmail.com
   John Blackwood - makoenergy02@gmail.com
*/

#ifndef _xmlbase_h
#define _xmlbase_h

//This next line is required for TiCPP to function
#define TIXML_USE_TICPP

#include <ticpp.h>

ticpp::Base* Wrapped;

namespace phys
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @namespace xml
    /// @brief The components to load, save, modify, and use XML will be stored here
    /// @details This is where objects that help with loading, saving, and
    /// manipulating xml documents will reside. This components found here are simply
    /// a tight wrapper around TinyXMLcpp with some integration with the rest of the
    /// physgame engine to allow some enhanced functionality (like using Ogre's nifty
    /// File loading system).\n
    /// Here is the original Copyright notice that came with our copy of TiCPP, and show
    /// That the huge copy pastes we performed are ok. This license does not apply
    /// to our code and is shown here explicitly show that we are in compliance with
    /// this license: \n \n TiCPP License: \n \n
    /// http://code.google.com/p/ticpp/ \n
    /// Copyright (c) 2006 Ryan Pusztai, Ryan Mulder \n \n
    /// Permission is hereby granted, free of charge, to any person obtaining a copy of \n
    /// this software and associated documentation files (the "Software"), to deal in \n
    /// the Software without restriction, including without limitation the rights to \n
    /// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of \n
    /// the Software, and to permit persons to whom the Software is furnished to do so, \n
    /// subject to the following conditions: \n \n
    /// The above copyright notice and this permission notice shall be included in all \n
    /// copies or substantial portions of the Software. \n \n
    /// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR \n
    /// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS \n
    /// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR \n
    /// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER \n
    /// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN \n
    /// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. \n\n
    ///     www.sourceforge.net/projects/tinyxml \n
    /// Original code (2.0 and earlier )copyright (c) 2000-2006 Lee Thomason (www.grinninglizard.com) \n
    /// This software is provided 'as-is', without any express or implied \n
    /// warranty. In no event will the authors be held liable for any \n
    /// damages arising from the use of this software. \n \n
    /// Permission is granted to anyone to use this software for any \n
    /// purpose, including commercial applications, and to alter it and \n
    /// redistribute it freely, subject to the following restrictions: \n \n
    /// 1. The origin of this software must not be misrepresented; you must \n
    /// not claim that you wrote the original software. If you use this \n
    /// software in a product, an acknowledgment in the product documentation \n
    /// would be appreciated but is not required. \n \n
    /// 2. Altered source versions must be plainly marked as such, and \n
    /// must not be misrepresented as being the original software. \n \n
    /// 3. This notice may not be removed or altered from any source \n
    /// distribution. \n  \n

    namespace xml
    {
        ///////////////////////////////////////////////////////////////////////////////
        /// @class Base
        /// @headerfile xmlbase.h
        /// @brief A set of all functionality that all XML components must implement
        /// @details
        class Base
        {
            private:
                /// @internal
                /// @brief A pointer to the Library level object we are wrapping to implement this functionality
                ticpp::Base* Wrapped;

            public:


                /// @brief This is used to identify what kind of component you are working with, in conjunction with the GetType() function
                enum XMLComponentType
                {
                    Attribute,              /**< Indicates the XMLComponent is an attribute, and not a node */
                    Node,                   /**< Indicates the XMLComponent is a node and nothing else */
                    Comment,                /**< Indicates the XMLComponent is a node and */
                    Declaration,            /**< Indicates the XMLComponent is a node and */
                    Document,               /**< Indicates the XMLComponent is a node and */
                    Element,                /**< Indicates the XMLComponent is a node and */
                    StyleSheetReference,    /**< Indicates the XMLComponent is a node and */
                    Text,                   /**< Indicates the XMLComponent is a node and */
                    Unknown                 /**< Indicates the XMLComponent is a node and */
                };

                /// @brief This Will be by Child classes to aid in identification
                /// @return Classes that inherit from this are expected to return an XMLComponentType that indicates what kind of XML component they are.
                virtual XMLComponentType GetType() = 0;

                /// @brief Return the position, in the original source file, of this node or attribute.
                /// @details Return the position, in the original source file, of this node or attribute. The row and column are 1-based.
                /// (That is the first row and first column is 1,1). If the returns values are 0 or less, then the parser does not have
                /// a row and column value. \n \n
                /// Generally, the row and column value will be set when the Document::Load(), Document::LoadFile(), or any Node::Parse()
                /// is called. It will NOT be set when the DOM was created from operator>>. \n \n
                /// The values reflect the initial load. Once the DOM is modified programmatically (by adding or changing nodes and
                /// attributes) the new values will NOT update to reflect changes in the document. \n \n
                /// There is a minor performance cost to computing the row and column. Computationcan be disabled if
                /// Document::SetTabSize() is called with 0 as the value.
                /// @return Returns an int.
                int Row() const;

                /// @brief Return the position, in the original source file, of this node or attribute.
                /// @details See Row()
                /// @return Returns an int.
                int Column() const;

                // @brief Set a pointer to arbitrary user data.
                // @param user This can be a pointer to any data that is required.
                // @details Sometimes it is too useful to be able to apply extras information, this seems to be the most appropriate place for that functionality.
                //void SetUserData (void *user);
                // @brief Get a pointer to arbitrary user data.
                // @details Returns gibberish (not always 0) if SetUserData was not called. Could be invalid, or not, make sure that you set it if you plan on
                // using it, and set See SetUserData(void*) .
                // @return This returns a pointer to something, it is up to you (or the game programmer) to determine what that means.
                //void* GetUserData();
                // @brief See GetUserData()
                //const void* GetUserData () const;


                /// @brief A simple empty virtual destructor for compatibility and ease of customization.
                virtual ~Base();



        }; // /Base
    }// /xml
}// /phys

/// @brief Streaming output operator for XML Documents
/// @details This converts the data of an XML Document into a stream Ideal for sending to a log or cout
/// @param stream This is the stream we send our data to.
/// @return This returns an std::ostream which now contains our data.
std::ostream& operator << (std::ostream& stream, const phys::xml::Base& x);


#endif