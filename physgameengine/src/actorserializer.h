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
#ifndef _actorserializer_h
#define _actorserializer_h

#include "actorrigid.h"
#include "actormanager.h"
#include "datatypes.h"
#include "serialization.h"
#include "xmldoc.h"

/// @file This is where the declarations of any Serializers or DeSerializers for actors will go.


namespace phys
{

    /// @brief This creates Rigid body actors and inserts them into a given ActorManager.
    class ActorRigidDeSerializer : public DeSerializer <ActorRigid>
    {
        #ifdef PHYSXML

        private:
            ActorManager* Target;

        public:

            /// @brief Constructor
            /// @param DeSerializeTarget A pointer to the actor manager that will be populated with deserialized actors.
            explicit ActorRigidDeSerializer(ActorManager* DeSerializeTarget = 0)
                    : Target(DeSerializeTarget)
            {}

            virtual ActorRigid* ProtoDeSerialize(const xml::Node& OneNode);

            virtual void ProtoDeSerializeAll(const xml::Node& OneNode);

        #endif // \PHYSXML
    };
}






#endif
