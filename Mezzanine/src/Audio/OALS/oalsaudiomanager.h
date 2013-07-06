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
// Copyright (c) 2008-2010 Raynaldo (Wildicv) Rivera, Joshua (Dark_Kilauea) Jones
// This file is part of the "cAudio Engine"
// For conditions of distribution and use, see copyright notice in cAudio-ZLIBLicense.txt
#ifndef _audiooalsaudiomanager_h
#define _audiooalsaudiomanager_h

#include "Audio/audiomanager.h"
#include "Threading/workunit.h"

// OpenAL forward declares
#ifndef OALS_STRUCTS_DECLARED
struct ALCdevice;
struct ALCcontext;
#endif //OALS_STRUCTS_DECLARED

namespace Mezzanine
{
    namespace Audio
    {
        namespace OALS
        {
            class Sound;
            class Recorder;
            class EffectsHandler;
            class SoundScapeManager;
            class AudioManager;

            /// @brief Do the work each frame for the AudioManager
            class AudioWorkUnit : public Threading::DefaultWorkUnit
            {
                private:
                    /// @brief The AudioManager to work with
                    OALS::AudioManager* Target;
                public:
                    /// @brief Create
                    /// @param TargetManager The manager to work with.
                    AudioWorkUnit(OALS::AudioManager *TargetManager);

                    /// @brief Do the actual
                    /// @param CurrentThreadStorage Resources that this work unit will use.
                    virtual void DoWork(Threading::DefaultThreadSpecificStorage::Type& CurrentThreadStorage);

                    /// @brief Virtual destructor
                    virtual ~AudioWorkUnit();
            };

            ///////////////////////////////////////////////////////////////////////////////
            /// @brief This is the base manager class for the Audio subsystem and it's operations.
            /// @details
            ///////////////////////////////////////////////////////////////////////////////
            class MEZZ_LIB SoundTypeHandler
            {
            public:
                /// @brief Basic container type for Sound storage by this class.
                typedef std::vector<OALS::Sound*>       SoundContainer;
                /// @brief Iterator type for Sound instances stored by this class.
                typedef SoundContainer::iterator        SoundIterator;
                /// @brief Const Iterator type for Sound instances stored by this class.
                typedef SoundContainer::const_iterator  ConstSoundIterator;

                ///////////////////////////////////////////////////////////////////////////////
                // Public Data Members

                /// @brief Whether or not this type of sound is muted.
                bool Mute;
                /// @brief The volume currently set for this type of sound.
                Real Volume;
                /// @brief Sound storage.
                //SoundContainer TypeSounds;

                ///////////////////////////////////////////////////////////////////////////////
                // Construction and Destruction

                /// @brief Class constructor.
                SoundTypeHandler() : Mute(false), Volume(1.0) {}
                /// @brief Class destructor.
                ~SoundTypeHandler() {}
            };//SoundTypeHandler

            ///////////////////////////////////////////////////////////////////////////////
            /// @brief This is the OALS AudioManager implementation.
            /// @details
            ///////////////////////////////////////////////////////////////////////////////
            class MEZZ_LIB AudioManager : public Audio::AudioManager
            {
                /// @brief The AudioWorkUnit needs access to internals of this manager
                friend class AudioWorkUnit;
            public:
                /// @brief Basic container type for @ref OALS::Sound storage by this class.
                typedef std::vector<OALS::Sound*>                   SoundContainer;
                /// @brief Iterator type for @ref OALS::Sound instances stored by this class.
                typedef SoundContainer::iterator                    SoundIterator;
                /// @brief Const Iterator type for @ref OALS::Sound instances stored by this class.
                typedef SoundContainer::const_iterator              ConstSoundIterator;
                /// @brief Basic container type for storing @ref OALS::Sound instances by type in this class.
                typedef std::map<UInt16,SoundTypeHandler*>          SoundTypesContainer;
                /// @brief Iterator type for @ref OALS::Sound instances stored by type in this class.
                typedef SoundTypesContainer::iterator               SoundTypesIterator;
                /// @brief Const Iterator type for @ref OALS::Sound instances stored by type in this class.
                typedef SoundTypesContainer::const_iterator         ConstSoundTypesIterator;
                /// @brief Basic container type for @ref OALS::Recorder storage by this class.
                typedef std::vector<OALS::Recorder*>                RecorderContainer;
                /// @brief Iterator type for @ref OALS::Recorder instances stored by this class.
                typedef RecorderContainer::iterator                 RecorderIterator;
                /// @brief Const Iterator type for @ref OALS::Recorder instances stored by this class.
                typedef RecorderContainer::const_iterator           ConstRecorderIterator;
                /// @brief Basic container type for @ref OALS::SoundScapeManager instances registered to this class.
                typedef std::vector<OALS::SoundScapeManager*>       SoundScapeManagerContainer;
                /// @brief Iterator type for @ref OALS::SoundScapeManager instances registered to this class.
                typedef SoundScapeManagerContainer::iterator        SoundScapeManagerIterator;
                /// @brief Const Iterator type for @ref OALS::SoundScapeManager instances registered to this class.
                typedef SoundScapeManagerContainer::const_iterator  ConstSoundScapeManagerIterator;
            protected:
                /// @internal
                /// @brief A pointer to the internal device this manager and all it's operations take place on.
                ALCdevice* InternalDevice;
                /// @internal
                /// @brief A pointer to the context used for the management of all non-spacialized audio.
                ALCcontext* NonSpacialContext;
                /// @internal
                /// @brief A pointer to the handler for all EFX related operations.
                OALS::EffectsHandler* EffHandler;
                /// @internal
                /// @brief A pointer to the system Music Player.
                MusicPlayer* MPlayer;
                /// @internal
                /// @brief Mute variable for all @ref iSound instances.
                bool MasterMute;
                /// @internal
                /// @brief Volume modifier for all @ref iSound instances.
                Real MasterVolume;
                /// @internal
                /// @brief The output frequency of the rendered audio belonging to the non-spacial context.
                Integer ContextOutputFrequency;
                /// @internal
                /// @brief The name of the current device being used for audio playback.
                String CurrentDeviceName;
                /// @internal
                /// @brief A vector containing
                StringVector AvailablePlaybackDevices;
                /// @internal
                /// @brief
                StringVector AvailableRecorderDevices;
                /// @internal
                /// @brief Container storing all @ref OALS::Sound instances.
                SoundContainer Sounds;
                /// @internal
                /// @brief Container storing all @ref OALS::Sound instances by their type.
                mutable SoundTypesContainer SoundsByType;
                /// @internal
                /// @brief Container storing all @ref OALS::Recorder instances.
                RecorderContainer Recorders;
                /// @internal
                /// @brief Container storing all @ref OALS::SoundScapeManager instances registered to this manager.
                SoundScapeManagerContainer SoundScapeManagers;
                /// @internal
                /// @brief The workunit this will use to complete its updates.
                AudioWorkUnit* AudioWork;

                /// @internal
                /// @brief Gets a SoundTypeHandler by type ID if it exists, or creates a new one if it does not.
                /// @note Unlike GetSoundTypeHandler(const UInt16 Type) const, this method will always return a valid pointer.
                /// @param Type A UInt16 that is the ID for the type of Sound instances to get the handler for.
                /// @return Returns a pointer to the requested SoundTypeHandler.
                virtual SoundTypeHandler* GetOrCreateSoundTypeHandler(const UInt16 Type) const;
                /// @internal
                /// @brief Gets the handler storing information on a specific type of Sound instance.
                /// @param Type A UInt16 that is the ID for the type of Sound instances to get the handler for.
                /// @return Returns a pointer to the SoundTypeHandler requested, or NULL if it does not exist.
                virtual SoundTypeHandler* GetSoundTypeHandler(const UInt16 Type) const;
                /// @internal
                /// @brief Gets the handler storing information on a specific type of Sound instance.
                /// @exception If this method fails to find the requested handler, it will throw a "II_IDENTITY_NOT_FOUND_EXCEPTION" exception.
                /// @param Type A UInt16 that is the ID for the type of Sound instances to get the handler for.
                /// @return Returns a pointer to the SoundTypeHandler requested.
                virtual SoundTypeHandler* GetSoundTypeHandlerExcept(const UInt16 Type) const;

                /// @internal
                /// @brief Gets the name of the Root XML Node of this object when it is serialized.
                /// @return Returns a String containing the name of the XML Node for this manager.
                virtual String GetObjectRootNodeName() const;
                /// @internal
                /// @brief Adds all of this classes current configuration to an XML node.
                /// @param SettingsRootNode The XML Node the current settings will be applied to.
                virtual void AppendCurrentSettings(XML::Node& SettingsRootNode);
                /// @internal
                /// @brief Applies a group of configuration settings to this manager.
                /// @param Group The Settings Group to update this managers state with.
                virtual void ApplySettingGroupImpl(ObjectSettingGroup* Group);

                /// @internal
                /// @brief Gets all the avaialable devices on this system and puts them into easier to access string vectors.
                virtual void GetAvailableDeviceNames();
            public:
                /// @brief Class Constructor.
                AudioManager();
                /// @brief XML constructor.
                /// @param XMLNode The node of the xml document to construct from.
                AudioManager(XML::Node& XMLNode);
                /// @brief Class Destructor.
                virtual ~AudioManager();

                ///////////////////////////////////////////////////////////////////////////////
                // Utility

                /// @copydoc Audio::AudioMananger::GetEffectsHandler() const
                virtual iEffectsHandler* GetEffectsHandler() const;
                /// @copydoc Audio::AudioMananger::GetMusicPlayer() const
                virtual MusicPlayer* GetMusicPlayer() const;

                ///////////////////////////////////////////////////////////////////////////////
                // Sound Management

                /// @copydoc Audio::AudioMananger::CreateSound(const UInt16)
                virtual iSound* CreateSound(const UInt16 Type);
                /// @copydoc Audio::AudioMananger::CreateSound(const UInt16, Resource::DataStreamPtr, const Audio::Encoding)
                virtual iSound* CreateSound(const UInt16 Type, Resource::DataStreamPtr Stream, const Audio::Encoding Encode);
                /// @copydoc Audio::AudioMananger::CreateSound(const UInt16, Resource::DataStreamPtr, const UInt32, const Audio::BitConfig)
                virtual iSound* CreateSound(const UInt16 Type, Resource::DataStreamPtr Stream, const UInt32 Frequency, const Audio::BitConfig Config);
                /// @copydoc Audio::AudioMananger::CreateSound(const UInt16, const String&, const String&, const String&)
                virtual iSound* CreateSound(const UInt16 Type, const String& FileName, const String& Group);
                /// @copydoc Audio::AudioMananger::CreateSound(const UInt16, const String&, const Char8*, const UInt32, const Audio::Encoding)
                virtual iSound* CreateSound(const UInt16 Type, const String& StreamName, Char8* Buffer, const UInt32 Length, const Audio::Encoding Encode);
                /// @copydoc Audio::AudioMananger::CreateSound(const UInt16, const String&, const Char8*, const UInt32, const UInt32, const Audio::BitConfig)
                virtual iSound* CreateSound(const UInt16 Type, const String& StreamName, Char8* Buffer, const UInt32 Length, const UInt32 Frequency, const Audio::BitConfig Config);
                /// @copydoc Audio::AudioMananger::GetSound(const UInt32) const
                virtual iSound* GetSound(const UInt32 Index) const;
                /// @copydoc Audio::AudioMananger::GetNumSounds() const
                virtual UInt32 GetNumSounds() const;
                /// @copydoc Audio::AudioMananger::DestroySound(iSound* ToBeDestroyed)
                virtual void DestroySound(iSound* ToBeDestroyed);
                /// @copydoc Audio::AudioMananger::DestroyAllSounds()
                virtual void DestroyAllSounds();

                ///////////////////////////////////////////////////////////////////////////////
                // Volume Management

                /// @copydoc Audio::AudioMananger::SetTypeVolume(const UInt16, const Real)
                virtual void SetTypeVolume(const UInt16 Type, const Real Vol);
                /// @copydoc Audio::AudioMananger::GetTypeVolume(const UInt16) const
                virtual Real GetTypeVolume(const UInt16 Type) const;
                /// @copydoc Audio::AudioMananger::MuteType(const UInt16, bool)
                virtual void MuteType(const UInt16 Type, bool Enable);
                /// @copydoc Audio::AudioMananger::IsTypeMuted(const UInt16) const
                virtual bool IsTypeMuted(const UInt16 Type) const;

                /// @copydoc Audio::AudioMananger::SetMasterVolume(const Real&)
                virtual void SetMasterVolume(const Real& Master);
                /// @copydoc Audio::AudioMananger::GetMasterVolume() const
                virtual Real GetMasterVolume() const;
                /// @copydoc Audio::AudioMananger::Mute(bool)
                virtual void SetMasterMute(bool Enable);
                /// @copydoc Audio::AudioMananger::IsMuted() const
                virtual bool IsMuted() const;

                ///////////////////////////////////////////////////////////////////////////////
                // Recorder Management

                /// @copydoc Audio::AudioMananger::CreateRecorder()
                virtual iRecorder* CreateRecorder();
                /// @copydoc Audio::AudioMananger::GetRecorder(const UInt32) const
                virtual iRecorder* GetRecorder(const UInt32 Index) const;
                /// @copydoc Audio::AudioMananger::GetNumRecorders() const
                virtual UInt32 GetNumRecorders() const;
                /// @copydoc Audio::AudioMananger::DestroyRecorder(iRecorder*)
                virtual void DestroyRecorder(iRecorder* ToBeDestroyed);
                /// @copydoc Audio::AudioMananger::DestroyAllRecorders()
                virtual void DestroyAllRecorders();

                ///////////////////////////////////////////////////////////////////////////////
                // Playback Device Management

                /// @copydoc Audio::AudioMananger::GetCurrentPlaybackDeviceName() const
                virtual String GetCurrentPlaybackDeviceName() const;

                /// @copydoc Audio::AudioMananger::GetAvailablePlaybackDeviceName(const Whole&) const
                virtual String GetAvailablePlaybackDeviceName(const Whole& Index) const;
                /// @copydoc Audio::AudioMananger::GetAvailablePlaybackDeviceCount() const
                virtual Whole GetAvailablePlaybackDeviceCount() const;
                /// @copydoc Audio::AudioMananger::GetDefaultPlaybackDeviceName() const
                virtual String GetDefaultPlaybackDeviceName() const;
                /// @copydoc Audio::AudioMananger::PlaybackDeviceNameValid(const String&) const
                virtual bool PlaybackDeviceNameValid(const String& DeviceName) const;

                /// @copydoc Audio::AudioMananger::InitializePlaybackDevice(const String&, const Integer)
                virtual bool InitializePlaybackDevice(const String& DeviceName, const Integer OutputFrequency = 44100);
                /// @copydoc Audio::AudioMananger::ShutdownPlaybackDevice()
                virtual void ShutdownPlaybackDevice();

                ///////////////////////////////////////////////////////////////////////////////
                // Recording Device Management

                /// @copydoc Audio::AudioMananger::GetAvailableRecordingDeviceName(const UInt32)
                virtual String GetAvailableRecordingDeviceName(const UInt32 Index);
                /// @copydoc Audio::AudioMananger::GetAvailableRecordingDeviceCount()
                virtual UInt32 GetAvailableRecordingDeviceCount();
                /// @copydoc Audio::AudioMananger::GetDefaultRecordingDeviceName()
                virtual String GetDefaultRecordingDeviceName();

                ///////////////////////////////////////////////////////////////////////////////
                // Inherited from Managerbase and Management Functions

                /// @copydoc ManagerBase::Initialize()
                virtual void Initialize();
                /// @copydoc ManagerBase::DoMainLoopItems()
                virtual void DoMainLoopItems();
                /// @copydoc ManagerBase::GetImplementationTypeName()
                virtual String GetImplementationTypeName() const;

                /// @brief Get the workunit this manager will use
                /// @return An AudioWorkUnit pointer to the currently
                AudioWorkUnit* GetAudioWorkUnit();

                ///////////////////////////////////////////////////////////////////////////////
                // Internal Methods

                /// @internal
                /// @brief Gets the 2D context owned by this manager.
                ALCcontext* _GetNonSpacialContext() const;
                /// @internal
                /// @brief Gets the open audio device owned by this manager.
                ALCdevice* _GetAudioDevice() const;
                /// @copydoc Audio::AudioMananger::_RegisterSoundScapeManager(Audio::SoundScapeManager*)
                void _RegisterSoundScapeManager(Audio::SoundScapeManager* Manager);
                /// @copydoc Audio::AudioMananger::_UnregisterSoundScapeManager(Audio::SoundScapeManager*)
                void _UnregisterSoundScapeManager(Audio::SoundScapeManager* Manager);
            };//AudioManager
        }//OALS
    }//Audio
}//Mezzanine

#endif
