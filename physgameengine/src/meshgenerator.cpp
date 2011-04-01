//� Copyright 2010 - 2011 BlackTopp Studios Inc.
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
// Parts of this source file contain code from Ogre Preceadural.  Below is the license for Ogre
// Proceadural, and the source will have markers indicating which segments of code are under
// Ogre Proceadural's license.  All other code not indicated is under GPL licence mentioned above.
/*
-----------------------------------------------------------------------------
For the latest info, see http://code.google.com/p/ogre-procedural/

Copyright (c) 2010 Michael Broutin

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
#ifndef _meshgenerator_cpp
#define _meshgenerator_cpp

#include <Ogre.h>
#include "meshgenerator.h"

namespace phys
{
    MeshGenerator::MeshGenerator()
    {
    }

    MeshGenerator::~MeshGenerator()
    {
    }

    void MeshGenerator::CreateBoxMesh(const String& MeshName, const String& MaterialName, const Vector3& HalfExtents)
    {
        Vector3 Half = HalfExtents;
        Ogre::MaterialPtr TheMaterial = Ogre::MaterialManager::getSingleton().getByName(MaterialName);
        String GroupName = TheMaterial->getGroup();

        Ogre::ManualObject* box = new Ogre::ManualObject("TempMan");
        box->begin(MaterialName);
        //Front
        box->position(-Half.X,-Half.Y,Half.Z);  box->normal(0,0,1);  box->textureCoord(0,1);
        box->position(Half.X,-Half.Y,Half.Z);   box->normal(0,0,1);  box->textureCoord(1,1);
        box->position(Half.X,Half.Y,Half.Z);    box->normal(0,0,1);  box->textureCoord(1,0);
        box->position(-Half.X,Half.Y,Half.Z);   box->normal(0,0,1);  box->textureCoord(0,0);
        //Back
        box->position(Half.X,-Half.Y,-Half.Z);  box->normal(0,0,-1); box->textureCoord(0,1);
        box->position(-Half.X,-Half.Y,-Half.Z); box->normal(0,0,-1); box->textureCoord(1,1);
        box->position(-Half.X,Half.Y,-Half.Z);  box->normal(0,0,-1); box->textureCoord(1,0);
        box->position(Half.X,Half.Y,-Half.Z);   box->normal(0,0,-1); box->textureCoord(0,0);
        //Left
        box->position(-Half.X,-Half.Y,-Half.Z); box->normal(-1,0,0); box->textureCoord(0,1);
        box->position(-Half.X,-Half.Y,Half.Z);  box->normal(-1,0,0); box->textureCoord(1,1);
        box->position(-Half.X,Half.Y,Half.Z);   box->normal(-1,0,0); box->textureCoord(1,0);
        box->position(-Half.X,Half.Y,-Half.Z);  box->normal(-1,0,0); box->textureCoord(0,0);
        //Right
        box->position(Half.X,-Half.Y,Half.Z);   box->normal(1,0,0);  box->textureCoord(0,1);
        box->position(Half.X,-Half.Y,-Half.Z);  box->normal(1,0,0);  box->textureCoord(1,1);
        box->position(Half.X,Half.Y,-Half.Z);   box->normal(1,0,0);  box->textureCoord(1,0);
        box->position(Half.X,Half.Y,Half.Z);    box->normal(1,0,0);  box->textureCoord(0,0);
        //Top
        box->position(-Half.X,Half.Y,Half.Z);   box->normal(0,1,0);  box->textureCoord(0,1);
        box->position(Half.X,Half.Y,Half.Z);    box->normal(0,1,0);  box->textureCoord(1,1);
        box->position(Half.X,Half.Y,-Half.Z);   box->normal(0,1,0);  box->textureCoord(1,0);
        box->position(-Half.X,Half.Y,-Half.Z);  box->normal(0,1,0);  box->textureCoord(0,0);
        //Bottom
        box->position(-Half.X,-Half.Y,-Half.Z); box->normal(0,-1,0); box->textureCoord(0,1);
        box->position(Half.X,-Half.Y,-Half.Z);  box->normal(0,-1,0); box->textureCoord(1,1);
        box->position(Half.X,-Half.Y,Half.Z);   box->normal(0,-1,0); box->textureCoord(1,0);
        box->position(-Half.X,-Half.Y,Half.Z);  box->normal(0,-1,0); box->textureCoord(0,0);

        box->triangle(0,1,2);    box->triangle(0,2,3);    //Front
        box->triangle(4,5,6);    box->triangle(4,6,7);    //Back
        box->triangle(8,9,10);   box->triangle(8,10,11);  //Left
        box->triangle(12,13,14); box->triangle(12,14,15); //Right
        box->triangle(16,17,18); box->triangle(16,18,19); //Top
        box->triangle(20,21,22); box->triangle(20,22,23); //Bottom

        box->end();
        Ogre::MeshPtr boxmesh = box->convertToMesh(MeshName, GroupName);
        boxmesh->_setBounds(Ogre::AxisAlignedBox(-Half.X,-Half.Y,-Half.Z,Half.X,Half.Y,Half.Z));
        Real FirstCheck = Half.X > Half.Y ? Half.X : Half.Y;
        Real Largest = FirstCheck > Half.Z ? FirstCheck : Half.Z;
        boxmesh->_setBoundingSphereRadius(1.4 * Largest);
        delete box;
    }

    void MeshGenerator::CreateCylinderMesh(const String& MeshName, const String& MaterialName, const Vector3& HalfExtents, const Vector3& AxisOrientation, const Whole& CircleRes, const Whole& Segments)
    {
/// Start of MIT(Ogre Proceadural) License ///
        if(AxisOrientation != Vector3::Unit_Y())
            return;
        if(HalfExtents.X != HalfExtents.Z)
            return;

        Vector3 Half = HalfExtents;
        Ogre::MaterialPtr TheMaterial = Ogre::MaterialManager::getSingleton().getByName(MaterialName);
        String GroupName = TheMaterial->getGroup();

        Real deltaAngle = (Ogre::Math::TWO_PI / CircleRes);
        Real deltaHeight = (Half.X * 2)/(Real)Segments;
        Real radius = Half.X;
        Whole offset = 0;

        Ogre::ManualObject* cylinder = new Ogre::ManualObject("TempMan");
        cylinder->begin(MaterialName);

        for (int i = 0; i <= Segments; i++)
        {
            for (int j = 0; j < CircleRes; j++)
            {
                Real x0 = radius * cosf(j*deltaAngle);
                Real z0 = radius * sinf(j*deltaAngle);
                cylinder->position(x0, (i*deltaHeight) - Half.Y, z0);
                cylinder->normal(Ogre::Vector3(x0,0,z0).normalisedCopy());
                cylinder->textureCoord(j/(Real)CircleRes, i/(Real)Segments);

                if (i != Segments)
                {
                    cylinder->index(offset + CircleRes + 1);
                    cylinder->index(offset);
                    cylinder->index(offset + CircleRes);
                    cylinder->index(offset + CircleRes + 1);
                    cylinder->index(offset + 1);
                    cylinder->index(offset);
                }
                offset ++;
            }
		}

		//low cap
		int centerIndex = offset;
		cylinder->position(0,-Half.Y,0);
		cylinder->normal(Ogre::Vector3::NEGATIVE_UNIT_Y);
		cylinder->textureCoord(0,1);
		offset++;
		for (int j=0;j<=CircleRes;j++)
		{
			Real x0 = radius * cosf(j*deltaAngle);
			Real z0 = radius * sinf(j*deltaAngle);

			cylinder->position(x0,-Half.Y, z0);
			cylinder->normal(Ogre::Vector3::NEGATIVE_UNIT_Y);
			cylinder->textureCoord(j/(Real)CircleRes,0.0);
			if (j!=CircleRes)
			{
				cylinder->index(centerIndex);
				cylinder->index(offset);
				cylinder->index(offset+1);
			}
			offset++;
		}

		// high cap
		centerIndex = offset;
		cylinder->position(0,Half.Y,0);
		cylinder->normal(Ogre::Vector3::UNIT_Y);
		cylinder->textureCoord(0,0);
		offset++;
		for (int j=0;j<=CircleRes;j++)
		{
			Real x0 = radius * cosf(j*deltaAngle);
			Real z0 = radius * sinf(j*deltaAngle);

			cylinder->position(x0, Half.Y, z0);
			cylinder->normal(Ogre::Vector3::UNIT_Y);
			cylinder->textureCoord(j/(Real)CircleRes,1);
			if (j!=CircleRes)
			{
				cylinder->index(centerIndex);
				cylinder->index(offset+1);
				cylinder->index(offset);
			}
			offset++;
		}

		cylinder->end();
        Ogre::MeshPtr cylindermesh = cylinder->convertToMesh(MeshName, GroupName);
        cylindermesh->_setBounds(Ogre::AxisAlignedBox(-Half.X,-Half.Y,-Half.Z,Half.X,Half.Y,Half.Z));
        Real FirstCheck = Half.X > Half.Y ? Half.X : Half.Y;
        Real Largest = FirstCheck > Half.Z ? FirstCheck : Half.Z;
        cylindermesh->_setBoundingSphereRadius(1.4 * Largest);
        delete cylinder;
/// End of MIT(Ogre Proceadural) License ///
    }

    void MeshGenerator::CreateSphereMesh(const String& MeshName, const String& MaterialName, const Real& Radius, const Real& Rings, const Real& Segments)
    {
        Ogre::MaterialPtr TheMaterial = Ogre::MaterialManager::getSingleton().getByName(MaterialName);
        String GroupName = TheMaterial->getGroup();

        Real RingAngle = (Ogre::Math::PI / Rings);
        Real SegAngle = (2 * Ogre::Math::PI / Segments);
        Whole VertIndex = 0;

        Ogre::ManualObject* sphere = new Ogre::ManualObject("TempMan");
        sphere->begin(MaterialName);

        for( Whole ring = 0 ; ring <= Rings ; ring++ ) {
        Real r0 = Radius * sinf (ring * RingAngle);
        Real y0 = Radius * cosf (ring * RingAngle);

            // Generate the group of segments for the current ring
            for( Whole seg = 0 ; seg <= Segments ; seg++ ) {
                Real x0 = r0 * sinf(seg * SegAngle);
                Real z0 = r0 * cosf(seg * SegAngle);

                // Add one vertex to the strip which makes up the sphere
                sphere->position( x0, y0, z0);
                sphere->normal(Ogre::Vector3(x0, y0, z0).normalisedCopy());
                sphere->textureCoord((Real) seg / (Real) Segments, (Real) ring / (Real) Rings);

                if (ring != Rings) {
                    // each vertex (except the last) has six indicies pointing to it
                    sphere->index(VertIndex + Segments + 1);
                    sphere->index(VertIndex);
                    sphere->index(VertIndex + Segments);
                    sphere->index(VertIndex + Segments + 1);
                    sphere->index(VertIndex + 1);
                    sphere->index(VertIndex);
                    VertIndex++;
                }
            }
        }

        sphere->end();
        Ogre::MeshPtr spheremesh = sphere->convertToMesh(MeshName, GroupName);
        spheremesh->_setBounds(Ogre::AxisAlignedBox(-Radius,-Radius,-Radius,Radius,Radius,Radius));
        spheremesh->_setBoundingSphereRadius(Radius);
        delete sphere;
    }
}

#endif
