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
#ifndef _audioaudiomanager_cpp
#define _audioaudiomanager_cpp

#include "Audio/audiomanager.h"
#include "Audio/recorder.h"
#include "Audio/sound.h"
#include "Audio/effectshandler.h"
#include "Audio/soundscapemanager.h"
#include "Audio/decoder.h"
#include "Audio/decoderfactory.h"
#include "exception.h"

namespace Mezzanine
{
    namespace Audio
    {
        template<> AudioManager* Singleton<AudioManager>::SingletonPtr = 0;

        AudioManager::AudioManager()
        {
        }

        AudioManager::AudioManager(XML::Node& XMLNode)
        {
        }

        AudioManager::~AudioManager()
        {
            this->DestroyAllDecoderFactories();
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Utility

        ///////////////////////////////////////////////////////////////////////////////
        // Sound Management

        ///////////////////////////////////////////////////////////////////////////////
        // Convenience Creation Methods

        iSound* AudioManager::CreateAmbientSound(const String& SoundName, const String& FileName, const String& Group)
            { return this->CreateSound(Audio::ST_Ambient,SoundName,FileName,Group); }
        iSound* AudioManager::CreateDialogSound(const String& SoundName, const String& FileName, const String& Group)
            { return this->CreateSound(Audio::ST_Dialog,SoundName,FileName,Group); }
        iSound* AudioManager::CreateEffectSound(const String& SoundName, const String& FileName, const String& Group)
            { return this->CreateSound(Audio::ST_Effect,SoundName,FileName,Group); }
        iSound* AudioManager::CreateMusicSound(const String& SoundName, const String& FileName, const String& Group)
            { return this->CreateSound(Audio::ST_Music,SoundName,FileName,Group); }

        iSound* CreateAmbientSound(const String& SoundName, const Char8* Buffer, const UInt32 Length, const Audio::Encoding Encode)
            { return this->CreateSound(Audio::ST_Ambient,SoundName,Buffer,Length,Encode); }
        iSound* CreateDialogSound(const String& SoundName, const Char8* Buffer, const UInt32 Length, const Audio::Encoding Encode)
            { return this->CreateSound(Audio::ST_Dialog,SoundName,Buffer,Length,Encode); }
        iSound* CreateEffectSound(const String& SoundName, const Char8* Buffer, const UInt32 Length, const Audio::Encoding Encode)
            { return this->CreateSound(Audio::ST_Effect,SoundName,Buffer,Length,Encode); }
        iSound* CreateMusicSound(const String& SoundName, const Char8* Buffer, const UInt32 Length, const Audio::Encoding Encode)
            { return this->CreateSound(Audio::ST_Music,SoundName,Buffer,Length,Encode); }

        iSound* CreateAmbientSound(const String& SoundName, const Char8* Buffer, const UInt32 Length, const UInt32 Frequency, const Audio::BitConfig Config)
            { return this->CreateSound(Audio::ST_Ambient,SoundName,Buffer,Length,Frequency,Config); }
        iSound* CreateDialogSound(const String& SoundName, const Char8* Buffer, const UInt32 Length, const UInt32 Frequency, const Audio::BitConfig Config)
            { return this->CreateSound(Audio::ST_Dialog,SoundName,Buffer,Length,Frequency,Config); }
        iSound* CreateEffectSound(const String& SoundName, const Char8* Buffer, const UInt32 Length, const UInt32 Frequency, const Audio::BitConfig Config)
            { return this->CreateSound(Audio::ST_Effect,SoundName,Buffer,Length,Frequency,Config); }
        iSound* CreateMusicSound(const String& SoundName, const Char8* Buffer, const UInt32 Length, const UInt32 Frequency, const Audio::BitConfig Config)
            { return this->CreateSound(Audio::ST_Music,SoundName,Buffer,Length,Frequency,Config); }

        iSound* CreateAmbientSound(const String& SoundName, DataStreamPtr Stream, const Audio::Encoding Encode)
            { return this->CreateSound(Audio::ST_Ambient,SoundName,Stream,Encode); }
        iSound* CreateDialogSound(const String& SoundName, DataStreamPtr Stream, const Audio::Encoding Encode)
            { return this->CreateSound(Audio::ST_Dialog,SoundName,Stream,Encode); }
        iSound* CreateEffectSound(const String& SoundName, DataStreamPtr Stream, const Audio::Encoding Encode)
            { return this->CreateSound(Audio::ST_Effect,SoundName,Stream,Encode); }
        iSound* CreateMusicSound(const String& SoundName, DataStreamPtr Stream, const Audio::Encoding Encode)
            { return this->CreateSound(Audio::ST_Music,SoundName,Stream,Encode); }

        iSound* CreateAmbientSound(const String& SoundName, DataStreamPtr Stream, const UInt32 Frequency, const Audio::BitConfig Config)
            { return this->CreateSound(Audio::ST_Ambient,SoundName,Stream,Frequency,Config); }
        iSound* CreateDialogSound(const String& SoundName, DataStreamPtr Stream, const UInt32 Frequency, const Audio::BitConfig Config)
            { return this->CreateSound(Audio::ST_Dialog,SoundName,Stream,Frequency,Config); }
        iSound* CreateEffectSound(const String& SoundName, DataStreamPtr Stream, const UInt32 Frequency, const Audio::BitConfig Config)
            { return this->CreateSound(Audio::ST_Effect,SoundName,Stream,Frequency,Config); }
        iSound* CreateMusicSound(const String& SoundName, DataStreamPtr Stream, const UInt32 Frequency, const Audio::BitConfig Config)
            { return this->CreateSound(Audio::ST_Music,SoundName,Stream,Frequency,Config); }

        ///////////////////////////////////////////////////////////////////////////////
        // Volume Management

        ///////////////////////////////////////////////////////////////////////////////
        // Convenience Type Volume Methods

        void AudioManager::SetAmbientVolume(const Real& Ambient)
            { this->SetTypeVolume(Audio::ST_Ambient,Ambient); }
        Real AudioManager::GetAmbientVolume() const
            { return this->GetTypeVolume(Audio::ST_Ambient); }
        void AudioManager::MuteAmbient(bool Enable)
            { this->MuteType(Audio::ST_Ambient,Enable); }
        bool AudioManager::IsAmbientMuted() const
            { return this->IsTypeMuted(Audio::ST_Ambient); }

        void AudioManager::SetDialogVolume(const Real& Dialog)
            { this->SetTypeVolume(Audio::ST_Dialog,Ambient); }
        Real AudioManager::GetDialogVolume() const
            { return this->GetTypeVolume(Audio::ST_Dialog); }
        void AudioManager::MuteDialog(bool Enable)
            { this->MuteType(Audio::ST_Dialog,Enable); }
        bool AudioManager::IsDialogMuted() const
            { return this->IsTypeMuted(Audio::ST_Dialog); }

        void AudioManager::SetEffectVolume(const Real& Effect)
            { this->SetTypeVolume(Audio::ST_Effect,Ambient); }
        Real AudioManager::GetEffectVolume() const
            { return this->GetTypeVolume(Audio::ST_Effect); }
        void AudioManager::MuteEffect(bool Enable)
            { this->MuteType(Audio::ST_Effect,Enable); }
        bool AudioManager::IsEffectMuted() const
            { return this->IsTypeMuted(Audio::ST_Effect); }

        void AudioManager::SetMusicVolume(const Real& Music)
            { this->SetTypeVolume(Audio::ST_Music,Ambient); }
        Real AudioManager::GetMusicVolume() const
            { return this->GetTypeVolume(Audio::ST_Music); }
        void AudioManager::MuteMusic(bool Enable)
            { this->MuteType(Audio::ST_Music,Enable); }
        bool AudioManager::IsMusicMuted() const
            { return this->IsTypeMuted(Audio::ST_Music); }

        ///////////////////////////////////////////////////////////////////////////////
        // Audio Device

        ///////////////////////////////////////////////////////////////////////////////
        // Decoder Management

        void AudioManager::AddDecoderFactory(iDecoderFactory* ToBeAdded)
        {
            std::pair<bool,DecoderFactoryIterator> Result = this->DecoderFactories.insert(std::pair<Audio::Encoding,iDecoderFactory*>(ToBeAdded->GetSupportedEncoding(),ToBeAdded));
            return Result.first;
        }

        bool AudioManager::DecoderFactoryExists(const AudioFileFormat Format)
        {
            return this->DecoderFactories.count(Format);
        }

        iDecoderFactory* AudioManager::GetDecoderFactory(const AudioFileFormat Format)
        {
            DecoderFactoryIterator FactIt = this->DecoderFactories.find(Format);
            if( FactIt != this->DecoderFactories.end() ) return (*FactIt);
            else return NULL;
        }

        void AudioManager::RemoveDecoderFactory(iDecoderFactory* ToBeRemoved)
        {
            this->RemoveDecoderFactory(ToBeRemoved->GetSupportedEncoding());
        }

        void AudioManager::RemoveDecoderFactory(const AudioFileFormat Format)
        {
            this->DecoderFactories.erase(Format);
        }

        void AudioManager::RemoveAllDecoderFactories()
        {
            this->DecoderFactories.clear();
        }

        void AudioManager::DestroyDecoderFactory(iDecoderFactory* ToBeDestroyed)
        {
            this->DestroyDecoderFactory(ToBeDestroyed->GetSupportedEncoding());
        }

        void AudioManager::DestroyDecoderFactory(const AudioFileFormat Format)
        {
            DecoderFactoryIterator FactIt = this->DecoderFactories.find(Format);
            if( FactIt != this->DecoderFactories.end() )
            {
                this->DecoderFactories.erase(FactIt);
                delete (*FactIt);
            }
        }

        void AudioManager::DestroyAllDecoderFactories()
        {
            for( DecoderFactoryIterator FactIt = this->DecoderFactories.begin() ; FactIt != this->DecoderFactories.end() ; ++FactIt )
            {
                delete (*FactIt);
            }
            this->DecoderFactories.clear();
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Inherited from Managerbase

        ManagerType AudioManager::GetInterfaceType() const
            { return ManagerBase::AudioManager; }
    }//Audio
}//Mezzanine

#endif
