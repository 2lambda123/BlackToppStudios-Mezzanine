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

#ifndef _graphicsimage_cpp
#define _graphicsimage_cpp

#include "Graphics/image.h"
#include <Ogre.h>

#ifdef LoadImage
#undef LoadImage
#endif

namespace Mezzanine
{
    namespace Graphics
    {
        ///////////////////////////////////////////////////////////////////////////////
        /// @class InternalImageData
        /// @brief This class is used to store the internal structures needed by the Image class.
        ///////////////////////////////////////
        class MEZZ_LIB InternalImageData
        {
        public:
            /// @internal
            /// @brief The internal representation of the Image.
            Ogre::Image GraphicsImage;
        };//InternalTextureData

        ///////////////////////////////////////////////////////////////////////////////
        // Image Methods

        Image::Image()
            { this->IID = new InternalImageData(); }

        Image::~Image()
            { delete this->IID; }

        ///////////////////////////////////////////////////////////////////////////////
        // Utility Methods

        UInt32 Image::GetWidth() const
            { return this->IID->GraphicsImage.getWidth(); }

        UInt32 Image::GetHeight() const
            { return this->IID->GraphicsImage.getHeight(); }

        UInt32 Image::GetDepth() const
            { return this->IID->GraphicsImage.getDepth(); }

        Graphics::PixelFormat Image::GetFormat() const
            { return static_cast<Graphics::PixelFormat>( this->IID->GraphicsImage.getFormat() ); }

        UInt8 Image::GetBitsPerPixel() const
            { return this->IID->GraphicsImage.getBPP(); }

        Whole Image::GetNumFaces() const
            { return this->IID->GraphicsImage.getNumFaces(); }

        Whole Image::GetNumMipMaps() const
            { return this->IID->GraphicsImage.getNumMipmaps(); }

        UInt8* Image::GetImageData()
            { return static_cast<UInt8*>( this->IID->GraphicsImage.getData() ); }

        const UInt8* Image::GetImageData() const
            { return static_cast<const UInt8*>( this->IID->GraphicsImage.getData() ); }

        Whole Image::GetSize() const
            { return this->IID->GraphicsImage.getSize(); }

        Whole Image::GetRowSpan() const
            { return this->IID->GraphicsImage.getRowSpan(); }

        Image& Image::FlipAroundXAxis()
        {
            this->IID->GraphicsImage.flipAroundX();
            return *this;
        }

        Image& Image::FlipAroundYAxis()
        {
            this->IID->GraphicsImage.flipAroundY();
            return *this;
        }

        void Image::SetColourAt(const Whole X, const Whole Y, const Whole Z, const ColourValue& Colour)
            { this->IID->GraphicsImage.setColourAt(Colour.GetOgreColourValue(),X,Y,Z); }

        ColourValue Image::GetColourAt(const Whole X, const Whole Y, const Whole Z) const
            { return this->IID->GraphicsImage.getColourAt(X,Y,Z); }

        ///////////////////////////////////////////////////////////////////////////////
        // Loading Methods

        Image& Image::LoadImage(const String& ResourceName, const String& ResourceGroup)
        {
            this->IID->GraphicsImage.load(ResourceName,ResourceGroup);
            return *this;
        }

        Image& Image::LoadImage(UInt8* Data, const UInt32 Width, const UInt32 Height, const Graphics::PixelFormat Format, const Boole AutoDelete, const Whole NumFaces, const UInt8 NumMipMaps)
        {
            this->IID->GraphicsImage.loadDynamicImage(Data,Width,Height,1,static_cast<Ogre::PixelFormat>(Format),AutoDelete,NumFaces,NumMipMaps);
            return *this;
        }

        Image& Image::LoadImage(UInt8* Data, const UInt32 Width, const UInt32 Height, const UInt32 Depth, const Graphics::PixelFormat Format, const Boole AutoDelete, const Whole NumFaces, const UInt8 NumMipMaps)
        {
            this->IID->GraphicsImage.loadDynamicImage(Data,Width,Height,Depth,static_cast<Ogre::PixelFormat>(Format),AutoDelete,NumFaces,NumMipMaps);
            return *this;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Internal Methods

        Ogre::Image& Image::_GetInternalImage() const
            { return this->IID->GraphicsImage; }
    }//Graphics
}//Mezzanine

#endif
