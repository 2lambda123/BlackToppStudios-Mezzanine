//© Copyright 2010 - 2012 BlackTopp Studios Inc.
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
#ifndef _uipagedcontainer_cpp
#define _uipagedcontainer_cpp

#include "UI/pagedcontainer.h"
#include "UI/pageprovider.h"
#include "UI/screen.h"

namespace Mezzanine
{
    namespace UI
    {
        const String PagedContainer::TypeName               = "PagedContainer";
        const String PagedContainer::EventChildFocusGained  = "ChildFocusGained";

        PagedContainer::PagedContainer(Screen* Parent) :
            LayoutContainer(Parent),
            LastFocusedChild(NULL),
            XProvider(NULL),
            YProvider(NULL)
            {  }

        PagedContainer::PagedContainer(const String& RendName, Screen* Parent) :
            LayoutContainer(RendName,Parent),
            LastFocusedChild(NULL),
            XProvider(NULL),
            YProvider(NULL)
            {  }

        PagedContainer::PagedContainer(const String& RendName, const UnifiedRect& RendRect, Screen* Parent) :
            LayoutContainer(RendName,RendRect,Parent),
            LastFocusedChild(NULL),
            XProvider(NULL),
            YProvider(NULL)
            {  }

        PagedContainer::~PagedContainer()
        {
            if( this->XProvider != NULL )
                this->XProvider->_SetContainer(NULL);
            if( this->YProvider != NULL )
                this->YProvider->_SetContainer(NULL);
        }

        void PagedContainer::ProtoSerializeImpl(XML::Node& SelfRoot) const
        {
            this->Widget::ProtoSerializeImpl(SelfRoot);
            this->ProtoSerializePageData(SelfRoot);
        }

        void PagedContainer::ProtoDeSerializeImpl(const XML::Node& SelfRoot)
        {
            this->Widget::ProtoDeSerializeImpl(SelfRoot);
            this->ProtoDeSerializePageData(SelfRoot);
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Utility

        void PagedContainer::SetWorkAreaSize(const UnifiedVec2& Area)
        {
            if( this->WorkAreaSize != Area ) {
                this->WorkAreaSize = Area;
            }
        }

        const UnifiedVec2& PagedContainer::GetWorkAreaSize() const
        {
            return this->WorkAreaSize;
        }

        Vector2 PagedContainer::GetActualWorkAreaSize() const
        {
            if( this->ParentQuad != NULL ) {
                return this->WorkAreaSize.CalculateActualDimensions(this->ParentQuad->GetActualSize());
            }else{
                return Vector2(0.0,0.0);
            }
        }

        void PagedContainer::UpdateDimensions(const Rect& OldSelfRect, const Rect& NewSelfRect)
        {
            this->LayoutContainer::UpdateDimensions(OldSelfRect,NewSelfRect);
            /*if( this->XProvider != NULL ) {
                this->XProvider->ConfigureProviderMetaData(this->ActDims.Size,this->GetActualWorkAreaSize());
            }//*/
            /*if( this->YProvider != NULL && this->YProvider != this->XProvider ) {
                this->YProvider->ConfigureProviderMetaData(this->ActDims.Size,this->GetActualWorkAreaSize());
            }//*/
        }

        Widget* PagedContainer::GetLastFocusedWidget() const
        {
            return this->LastFocusedChild;
        }

        PagedContainer::ProviderMode PagedContainer::GetProviderConfig() const
        {
            if( this->XProvider != NULL && this->YProvider != NULL ) {
                return ( this->XProvider == this->YProvider ? PagedContainer::PM_Single_XY : PagedContainer::PM_Dual_XY );
            }else if( this->XProvider != NULL ) {
                return PagedContainer::PM_Single_X;
            }else if( this->YProvider != NULL ) {
                return PagedContainer::PM_Single_Y;
            }else{
                return PagedContainer::PM_Error;
            }
        }

        PagedContainer::ProviderMode PagedContainer::GetProviderConfig(const PageProvider* Prov) const
        {
            if( this->XProvider == Prov && this->YProvider == Prov ) {
                return PagedContainer::PM_Single_XY;
            }else if( this->XProvider == Prov ) {
                return PagedContainer::PM_Single_X;
            }else if( this->YProvider == Prov ) {
                return PagedContainer::PM_Single_Y;
            }else{
                return PagedContainer::PM_Error;
            }
        }

        PageProvider* PagedContainer::GetXProvider() const
            { return this->XProvider; }

        PageProvider* PagedContainer::GetYProvider() const
            { return this->YProvider; }

        void PagedContainer::UnbindProvider(PageProvider* Prov)
        {
            if( this->XProvider == Prov ) {
                this->XProvider->_SetContainer(NULL);
                this->XProvider = NULL;
            }
            if( this->YProvider == Prov ) {
                this->YProvider->_SetContainer(NULL);
                this->YProvider = NULL;
            }
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Child Management

        void PagedContainer::AddChild(Widget* Child)
        {
            this->QuadRenderable::AddChild(Child);
            Child->Subscribe(Widget::EventFocusGained,this);
        }

        void PagedContainer::RemoveChild(Widget* Child)
        {
            if( this->LastFocusedChild == Child ) {
                this->LastFocusedChild = NULL;
            }
            Child->Unsubscribe(Widget::EventFocusGained,this);
            this->QuadRenderable::RemoveChild(Child);
        }

        void PagedContainer::RemoveAllChildren()
        {
            this->LastFocusedChild = NULL;
            for( ChildIterator It = this->ChildWidgets.begin() ; It != this->ChildWidgets.end() ; ++It )
            {
                this->ClearParenthood( *It );
                (*It)->Unsubscribe(Widget::EventFocusGained,this);
            }
            this->ChildWidgets.clear();
            this->_MarkDirty();
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Serialization

        void PagedContainer::ProtoSerializePageData(XML::Node& SelfRoot) const
        {
            if( this->XProvider != NULL || this->YProvider != NULL ) {
                XML::Node PageDataNode = SelfRoot.AppendChild( PagedContainer::GetSerializableName() + "PageData" );
                if( PageDataNode.AppendAttribute("Version").SetValue("1") )
                {
                    if( this->XProvider != NULL ) {
                        XML::Node XProviderNode = PageDataNode.AppendChild("XProvider");
                        if( XProviderNode.AppendAttribute("Name").SetValue( this->XProvider->GetName() ) &&
                            XProviderNode.AppendAttribute("Config").SetValue( this->GetProviderConfig( this->XProvider ) ) )
                        {
                            return;
                        }else{
                            SerializeError("Create XML Attribute Values",PagedContainer::GetSerializableName() + "PageData",true);
                        }
                    }

                    if( this->YProvider != NULL ) {
                        XML::Node YProviderNode = PageDataNode.AppendChild("YProvider");
                        if( YProviderNode.AppendAttribute("Name").SetValue( this->YProvider->GetName() ) &&
                            YProviderNode.AppendAttribute("Config").SetValue( this->GetProviderConfig( this->YProvider ) ) )
                        {
                            return;
                        }else{
                            SerializeError("Create XML Attribute Values",PagedContainer::GetSerializableName() + "PageData",true);
                        }
                    }

                    return;
                }else{
                    SerializeError("Create XML Attribute Values",PagedContainer::GetSerializableName() + "PageData",true);
                }
            }
        }

        void PagedContainer::ProtoSerializeProperties(XML::Node& SelfRoot) const
        {
            this->LayoutContainer::ProtoSerializeProperties(SelfRoot);

            XML::Node PropertiesNode = SelfRoot.AppendChild( PagedContainer::GetSerializableName() + "Properties" );

            if( PropertiesNode.AppendAttribute("Version").SetValue("1") )
            {
                XML::Node WorkAreaSizeNode = PropertiesNode.AppendChild("WorkAreaSize");
                this->WorkAreaSize.ProtoSerialize(WorkAreaSizeNode);

                return;
            }else{
                SerializeError("Create XML Attribute Values",PagedContainer::GetSerializableName() + "Properties",true);
            }
        }

        void PagedContainer::ProtoDeSerializePageData(const XML::Node& SelfRoot)
        {
            XML::Attribute CurrAttrib;
            XML::Node PageDataNode = SelfRoot.GetChild( PagedContainer::GetSerializableName() + "PageData" );

            if( !PageDataNode.Empty() ) {
                if(PageDataNode.GetAttribute("Version").AsInt() == 1) {
                    XML::Node XProviderNode = PageDataNode.GetChild("XProvider");
                    if( !XProviderNode.Empty() ) {
                        String ProviderName;
                        ProviderMode ProviderConfig;

                        CurrAttrib = XProviderNode.GetAttribute("Name");
                        if( !CurrAttrib.Empty() )
                            ProviderName = CurrAttrib.AsString();

                        CurrAttrib = XProviderNode.GetAttribute("Config");
                        if( !CurrAttrib.Empty() )
                            ProviderConfig = static_cast<ProviderMode>( CurrAttrib.AsWhole() );

                        if( !ProviderName.empty() ) {
                            /// @todo This is a blind cast and can cause some issues if the configuration is edited externally such that the named
                            /// widget isn't a provider.  Some check may being added may be warrented.
                            PageProvider* Casted = static_cast<PageProvider*>( this->ParentScreen->GetWidget(ProviderName) );
                            if( Casted ) {
                                switch( ProviderConfig )
                                {
                                    case PagedContainer::PM_Single_X:    this->SetXProvider(Casted);          break;
                                    case PagedContainer::PM_Single_Y:    this->SetYProvider(Casted);          break;
                                    case PagedContainer::PM_Single_XY:   this->SetProviders(Casted,Casted);   break;
                                    default:                             /* Do Nothing */                     break;
                                }
                            }
                        }
                    }

                    XML::Node YProviderNode = PageDataNode.GetChild("YProvider");
                    if( !YProviderNode.Empty() ) {
                        String ProviderName;
                        ProviderMode ProviderConfig;

                        CurrAttrib = YProviderNode.GetAttribute("Name");
                        if( !CurrAttrib.Empty() )
                            ProviderName = CurrAttrib.AsString();

                        CurrAttrib = YProviderNode.GetAttribute("Config");
                        if( !CurrAttrib.Empty() )
                            ProviderConfig = static_cast<ProviderMode>( CurrAttrib.AsWhole() );

                        if( !ProviderName.empty() ) {
                            /// @todo This is a blind cast and can cause some issues if the configuration is edited externally such that the named
                            /// widget isn't a provider.  Some check may being added may be warrented.
                            PageProvider* Casted = static_cast<PageProvider*>( this->ParentScreen->GetWidget(ProviderName) );
                            if( Casted ) {
                                switch( ProviderConfig )
                                {
                                    case PagedContainer::PM_Single_X:    this->SetXProvider(Casted);          break;
                                    case PagedContainer::PM_Single_Y:    this->SetYProvider(Casted);          break;
                                    case PagedContainer::PM_Single_XY:   this->SetProviders(Casted,Casted);   break;
                                    default:                             /* Do Nothing */                     break;
                                }
                            }
                        }
                    }
                }else{
                    MEZZ_EXCEPTION(Exception::INVALID_VERSION_EXCEPTION,"Incompatible XML Version for " + (PagedContainer::GetSerializableName() + "PageData") + ": Not Version 1.");
                }
            }else{
                MEZZ_EXCEPTION(Exception::II_IDENTITY_NOT_FOUND_EXCEPTION,PagedContainer::GetSerializableName() + "PageData" + " was not found in the provided XML node, which was expected.");
            }
        }

        void PagedContainer::ProtoDeSerializeProperties(const XML::Node& SelfRoot)
        {
            this->LayoutContainer::ProtoDeSerializeProperties(SelfRoot);

            //XML::Attribute CurrAttrib;
            XML::Node PropertiesNode = SelfRoot.GetChild( PagedContainer::GetSerializableName() + "Properties" );

            if( !PropertiesNode.Empty() ) {
                if(PropertiesNode.GetAttribute("Version").AsInt() == 1) {
                    XML::Node WorkAreaSizeNode = PropertiesNode.GetChild("WorkAreaSize");
                    if( !WorkAreaSizeNode.Empty() ) {
                        this->WorkAreaSize.ProtoDeSerialize(WorkAreaSizeNode);
                    }
                }else{
                    MEZZ_EXCEPTION(Exception::INVALID_VERSION_EXCEPTION,"Incompatible XML Version for " + (PagedContainer::GetSerializableName() + "Properties") + ": Not Version 1.");
                }
            }else{
                MEZZ_EXCEPTION(Exception::II_IDENTITY_NOT_FOUND_EXCEPTION,PagedContainer::GetSerializableName() + "Properties" + " was not found in the provided XML node, which was expected.");
            }
        }

        String PagedContainer::GetSerializableName()
        {
            return PagedContainer::TypeName;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Internal Event Methods

        void PagedContainer::_OnChildFocusGained(const String& ChildName)
        {
            ChildFocusEventArguments Args(PagedContainer::EventChildFocusGained,this->Name,ChildName);
            this->FireEvent(Args);
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Internal Methods

        void PagedContainer::_NotifyEvent(const EventArguments& Args)
        {
            if( Args.EventName == Widget::EventFocusGained ) {
                const WidgetEventArguments& WidArgs = static_cast<const WidgetEventArguments&>(Args);
                Widget* EventWidget = this->GetChild(WidArgs.WidgetName);
                if( EventWidget != NULL ) {
                    this->LastFocusedChild = EventWidget;
                    this->_OnChildFocusGained( this->LastFocusedChild->GetName() );
                }
            }
        }
    }//UI
}//Mezzanine

#endif
