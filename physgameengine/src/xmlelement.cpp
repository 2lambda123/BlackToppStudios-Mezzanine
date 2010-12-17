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

#ifndef _xmlelement_cpp
#define _xmlelement_cpp

#include "xmlelement.h"
#include "exception.h"

#include <sstream>

#define TIXML_USE_TICPP
#include <ticpp.h>

namespace phys
{
    namespace xml
    {
        //Inherited members


        //Members
        Element::Element (ticpp::Element *Meta, bool FirstTimeUsed)
        {
            this->Wrapped = Meta;
            if (FirstTimeUsed)
                { this->TakeOwnerOfWrapped(); }
        }

        Element::Element ()
        {
            this->Wrapped = new ticpp::Element();
            this->TakeOwnerOfWrapped();
        }

        Element::Element (const std::string &Value)
        {
            this->Wrapped = new ticpp::Element(Value);
            this->TakeOwnerOfWrapped();
        }

        Element::Element (const std::string &Value, const std::string &Text)
        {
            this->Wrapped = new ticpp::Element(Value, Text);
            this->TakeOwnerOfWrapped();
        }

        Element::~Element()
            {}

        Element* Element::GetPointerFromWrapped(ticpp::Element* Meta)
        {
            Element* Other;
            try {
                //Most likely cause of failure is ticpp::Node::GetBasePointer() returns 0
                Other = static_cast<Element*>( Meta->GetBasePointer()->GetUserData() );
            } catch (ticpp::Exception e) {
                std::stringstream temp;
                temp << "Could not Create phys::xml::Element from invalid pointer." << std::endl << e.what() << std::endl << "Details: " << e.m_details;
                throw Exception (temp.str());
            }

            //If there is no pointer inside TinyXML to our node, then it doesn't exist, so make it Otherwise use what is there
            if(0 == Other)
                { Other = new Element(Meta, true); }
            return Other;
        }

        Base::XMLComponentType Element::GetType() const
            { return Base::isElement; }

        std::istream& operator>> (std::istream &In, xml::Element &Elem)
            { return In >> *(static_cast <ticpp::Element*>(Elem.Wrapped)); }

        std::ostream& operator<< (std::ostream &Out, xml::Element &Elem)
            { return Out << *(static_cast <ticpp::Element*>(Elem.Wrapped)); }

        Attribute* Element::FirstAttribute() const
            { return Attribute::GetPointerFromWrapped( static_cast<ticpp::Element*>(this->Wrapped)->FirstAttribute(true) ); }

        Attribute* Element::LastAttribute() const
            { return Attribute::GetPointerFromWrapped(static_cast<ticpp::Element*>(this->Wrapped)->LastAttribute(true) ); }

        void Element::SetAttribute(const String &Name, const String& Value)
            { static_cast<ticpp::Element*>(this->Wrapped)->SetAttribute(Name, Value); }

        void Element::SetAttribute(const String &Name, const Whole& Value)
            { static_cast<ticpp::Element*>(this->Wrapped)->SetAttribute(Name, Value); }

        void Element::SetAttribute(const String &Name, const Real& Value)
            { static_cast<ticpp::Element*>(this->Wrapped)->SetAttribute(Name, Value); }

        String Element::GetText() const
            { return static_cast<ticpp::Element*>(this->Wrapped)->GetText(true); }

        void Element::SetText(const String& Value)
            { static_cast<ticpp::Element*>(this->Wrapped)->SetText(Value); }

        void Element::SetText(const Whole& Value)
            { static_cast<ticpp::Element*>(this->Wrapped)->SetText(Value); }

        void Element::SetText(const Real& Value)
            { static_cast<ticpp::Element*>(this->Wrapped)->SetText(Value); }

        String Element::GetAttribute (const String& Name) const
            { return static_cast<ticpp::Element*>(this->Wrapped)->GetAttribute(Name); }

        bool Element::HasAttribute (const String& Name) const
            { return static_cast<ticpp::Element*>(this->Wrapped)->HasAttribute(Name); }

        void Element::RemoveAttribute (const String& Name)
            { static_cast<ticpp::Element*>(this->Wrapped)->RemoveAttribute(Name); }
    }// \xml
}// \phys

#endif // \_xmlelement_cpp
