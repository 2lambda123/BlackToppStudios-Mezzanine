//© Copyright 2010 Joseph Toppi and John Blackwood
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
#ifndef _linegroup_cpp
#define _linegroup_cpp

#include "datatypes.h"
#include "physvector.h"


namespace phys
{
    // Just a forward declaration to make wrapping some functionality to engine internals easier.
    class World;
    namespace internal
    {
            class Line3D;
    }

    class LineGroup
    {
        public:
            LineGroup(World *Parent_);
            ~LineGroup(void);

            void addPoint(const PhysVector3 &p);
            const PhysVector3 getPoint(unsigned short index) const;
            unsigned short getNumPoints(void) const;
            void updatePoint(unsigned short index, const PhysVector3 &value);
            void drawLine(const PhysVector3 &start, const PhysVector3 &end);
            void drawLines(void);

            //Real getSquaredViewDepth(const Camera *cam) const;
            Real getBoundingRadius(void) const;

        private:
            World *Parent;
            internal::Line3D *LineData;
    };
}

#endif
