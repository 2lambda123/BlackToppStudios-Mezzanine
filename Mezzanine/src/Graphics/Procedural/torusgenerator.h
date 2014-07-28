// © Copyright 2010 - 2014 BlackTopp Studios Inc.
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
/*
 -----------------------------------------------------------------------------
 This source file is part of ogre-procedural

 For the latest info, see http://code.google.com/p/ogre-procedural/

 Copyright (c) 2010-2013 Michael Broutin

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 -----------------------------------------------------------------------------
 */
#ifndef _graphicsproceduraltorusgenerator_h
#define _graphicsproceduraltorusgenerator_h

#include "Graphics/Procedural/meshgenerator.h"

namespace Mezzanine
{
    namespace Graphics
    {
        namespace Procedural
        {
            ///////////////////////////////////////////////////////////////////////////////
            /// @brief A generator class for a torus mesh.
            /// @details
            ///////////////////////////////////////
            class MEZZ_LIB TorusGenerator : public MeshGenerator<TorusGenerator>
            {
            protected:
                /// @internal
                /// @brief The radius of the primary ring of the torus.
                /// @remarks This radius does not encapsulate the complete AABB of the torus.  Add Toroidal radius to this value to get the full bounds.
                Real TorusPoloidalRadius;
                /// @internal
                /// @brief The radius of the secondary ring of the torus.
                /// @remarks This is the value for the "thickness" of the ring.
                Real TorusToroidalRadius;
                /// @internal
                /// @brief The resolution of the Poloidal ring.
                Whole NumPoloidalSeg;
                /// @internal
                /// @brief The resolution of the Toroidal ring.
                Whole NumToroidalSeg;
            public:
                /// @brief Class constructor.
                /// @param PoloidalRadius The radius of the primary ring of the torus.
                /// @param ToroidalRadius The radius of the secondary ring of the torus.
                /// @param PoloidalSeg The resolution of the primary ring of the torus.
                /// @param ToroidalSeg The resolution of the secondary ring of the torus.
                TorusGenerator(const Real PoloidalRadius, const Real ToroidalRadius, const Whole PoloidalSeg = 16, const Whole ToroidalSeg = 16);
                /// @brief Class destructor.
                virtual ~TorusGenerator();

                ///////////////////////////////////////////////////////////////////////////////
                // Utility

                /// @copydoc MeshGenerator::AddToTriangleBuffer(TriangleBuffer&) const
                virtual void AddToTriangleBuffer(TriangleBuffer& Buffer) const;

                ///////////////////////////////////////////////////////////////////////////////
                // Configuration

                /// @brief Sets the radius of the torus.
                /// @exception If the radius is set to 0 or less, a PARAMETERS_EXCEPTION will be thrown.
                /// @param PoloidalRadius The radius of the primary ring of the torus.
                /// @return Returns a reference to this.
                TorusGenerator& SetPoloidalRadius(const Real PoloidalRadius);
                /// @brief Sets the radius of the torus ring.  AKA it's thickness.
                /// @exception If the radius is set to 0 or less, a PARAMETERS_EXCEPTION will be thrown.
                /// @param ToroidalRadius The radius of the secondary ring of the torus.
                /// @return Returns a reference to this.
                TorusGenerator& SetToroidalRadius(const Real ToroidalRadius);

                /// @brief Sets the number of segments on the Poloidal ring.
                /// @exception If the number of segments is less than three, a PARAMETERS_EXCEPTION will be thrown.
                /// @param PoloidalSeg The resolution of the primary ring of the torus.
                /// @return Returns a reference to this.
                TorusGenerator& SetNumPoloidalSeg(const Whole PoloidalSeg);
                /// @brief Sets the number of segments along the guiding circle.
                /// @exception If the number of segments is less than three, a PARAMETERS_EXCEPTION will be thrown.
                /// @param ToroidalSegThe resolution of the secondary ring of the torus.
                /// @return Returns a reference to this.
                TorusGenerator& SetNumToroidalSeg(const Whole ToroidalSeg);
            };//TorusGenerator
        }//Procedural
    }//Graphics
}//Mezzanine

#endif
