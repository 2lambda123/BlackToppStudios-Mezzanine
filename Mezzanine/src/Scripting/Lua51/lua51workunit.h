//© Copyright 2010 - 2013 BlackTopp Studios Inc.
/* This file is part of The Mezzanine Engine.

    The Mezzanine Engine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The Mezzanine Engine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Mezzanine Engine.  If not, see <http://www.gnu.org/licenses/>.
*/
/* The original authors have included a copy of the license specified above in the
   'Docs' folder. See 'gpl.txt'
*/
/* We welcome the use of the Mezzanine engine to anyone, including companies who wish to
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
#ifndef _lua51workunit_h
#define _lua51workunit_h

#include "datatypes.h"

#ifdef MEZZLUA51

#include "Scripting/Lua51/lua51script.h"

#include "Threading/workunit.h"

#include <vector>

/// @file
/// @brief This file has the declaration for a workunit that can execute lua script every frame


namespace Mezzanine
{
    namespace Scripting
    {
        namespace Lua
        {/*
            class MEZZ_LIB Lua51WorkUnit : public Threading::DefaultWorkUnit
            {
                private:
                    std::vector<CountedPtr<Lua51Script> > ScriptsToRun;

                    typedef std::vector<CountedPtr<Lua51Script> >::iterator iterator;

                    typedef std::vector<CountedPtr<Lua51Script> >::const_iterator const_iterator;
                public:

                    /// @brief Adds a script to be run once each frame.
                    /// @param
                    iterator push_back(CountedPtr<Lua51Script> FreshScript);

                    void erase(iterator Target);

                    iterator begin();
                    const_iterator begin() const;

                    iterator end();
                    const_iterator end() const;

                    /// @brief Runs all scripts that have been added to this work unit
                    virtual void DoWork(Threading::DefaultThreadSpecificStorage::Type& CurrentThreadStorage);
            };*/
        } // Lua
    } // Scripting

} // Mezzanine


#endif // MEZZLUA51
#endif // \_scriptinglua_h
