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
#ifndef _sound_h
#define _sound_h

#include "crossplatformexport.h"
#include "datatypes.h"
#include "vector3.h"

namespace cAudio
{
    class IAudioManager;
    class IAudioSource;
}

namespace phys
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @class Sound
    /// @headerfile sound.h
    /// @brief This is an instance of a sound that can be played and manipulated.
    /// @details This is a an instance of a sound that can be played, have effects
    /// applied to it, paused, stopped, triggered and other such crazyness.
    ///////////////////////////////////////////////////////////////////////////////
    class PHYS_LIB Sound
    {
        friend class SoundManager;
        protected:
            cAudio::IAudioSource* SoundSource;
            cAudio::IAudioManager* Manager;
        public:
            /// @brief Class Constructor.  Internal use only.
            /// @details The Class costructor.  Should not be called manually, use the sound manager instead.
            Sound();
            /// @brief Class Constructor.  Internal use only.
            /// @details The Class costructor.  Should not be called manually, use the sound manager instead.
            /// @param Source Pointer to the sound source.
            Sound(cAudio::IAudioSource* Source, cAudio::IAudioManager* manager);
            /// @brief Class destructor.
            /// @details The class destructor.
            ~Sound();
            /// @brief Plays the sound.
            /// @details Plays the sound with the same settings as the last time it was played.
            void Play();
            /// @brief Plays the sound in 2D mode.
            /// @details This will play the sound without altering it by it's position in 3D space.  Ideal
            /// for music and ambient sounds.
            /// @param Loop Whether or not the sound should restart once it's done playing.
            void Play2d(bool Loop=false);
            /// @brief Plays the sound in 3D mode.
            /// @details This will play the sound and alter it's properties based on it's location in 3D space.
            /// Sounds can sound like they are coming more from one direction then another, etc..
            /// @param Position The location in 3D space where the sound originates.
            /// @param SoundStrength The higher the sound strength, the further away you can hear the sound, not
            /// the same as volume.
            /// @param Loop Whether or not the sound should restart once it's done playing.
            void Play3d(Vector3 Position, Real SoundStrength=1.0, bool Loop=false);
            /// @brief Pauses the sound.
            /// @details Pauses the sound.
            void Pause();
            /// @brief Stops the sound.
            /// @details Stops the sound.
            void Stop();
            /// @brief Sets whether this sound should loop.
            /// @details Sets whether this sound should restart once it's done playing.
            /// @param ToLoop Whether or not this sound should restart
            void Loop(bool ToLoop);
            /// @brief Allows you to go to a specific point in the sound.
            /// @details This function will allow you to jump ahead or rewind to any specific
            /// point in the sound.
            /// @param Seconds How many seconds into the sound you want to jump to.
            /// @param Relative Whether or not you want the jump to be relative to where the sound
            /// is at the time of calling this function.
            void Seek(Real Seconds, bool Relative);
            /// @brief Gets the total size of the sound in seconds.
            /// @details This function will return the amount of seconds of the sound.
            /// @return Returns a Real that is the size in seconds.
            Real GetTotalAudioTime();
            /// @brief Gets the total size of the sound in memory.
            /// @details This function will return the total size of the sound in memory.
            /// @return Returns a Real that is the size in memory.
            int GetTotalAudioSize();
            /// @brief Gets the original compressed size of the sound.
            /// @details This function will return the compressed size of the sound.
            /// @return Returns a Real that is the original compressed size.
            int GetCompressedAudioSize();
            /// @brief Gets the current position in the audio stream in seconds.
            /// @details This function will get the current position of the sound in the audio stream.
            /// @return Returns the current position in the audio stream in seconds.
            Real GetCurrentAudioTime();
            /// @brief Gets the current position in the audio stream in bytes.
            /// @details This function will get the current position of the sound in the audio stream.
            /// @return Returns the current position in the audio stream in bytes.
            int GetCurrentAudioPosition();
            /// @brief Gets the current position in the original audio stream in bytes.
            /// @details This function will get the current position of the sound in the original audio stream.
            /// @return Returns the current position in the original audio stream in bytes.
            int GetCurrentCompressedAudioPosition();
            /// @brief Checks to see if the sound is currently playing.
            /// @details Checks to see if the sound is currently playing.
            /// @return Returns whether or not the sound is currently playing.
            bool IsPlaying();
            /// @brief Checks to see if the sound is currently paused.
            /// @details Checks to see if the sound is currently paused.
            /// @return Returns whether or not the sound is currently paused.
            bool IsPaused();
            /// @brief Checks to see if the sound is currently stopped.
            /// @details Checks to see if the sound is currently stopped.
            /// @return Returns whether or not the sound is currently stopped.
            bool IsStopped();
            /// @brief Checks to see if the sound is currently set to loop.
            /// @details Checks to see if the sound is currently set to loop.
            /// @return Returns whether or not the sound is currently set to loop.
            bool IsLooping();
            /// @brief Sets the position of the sound source.
            /// @details This function will set the position of the source to be used
            /// with the sound in 3D mode.
            /// @param Position The new position of the sound source.
            void SetPosition(Vector3 Position);
            /// @brief Sets the velocity of the sound source.
            /// @details This function will set the velocity of the source to be used
            /// with the sound in 3D mode.
            /// @param Velocity The new velocity of the sound source.
            void SetVelocity(Vector3 Velocity);
            /// @brief Sets the direction the sound source is facing.
            /// @details This function will set the direction the sound source is facing
            /// to be used with the sound in 3D mode.
            /// @param Direction The new direction of the sound source.
            void SetDirection(Vector3 Direction);
            /// @brief Sets the Rolloff factor used to attenuate the sound over a distance.
            /// @details This function will set how much the sound source will attenuate over
            /// a distance.  Larger values will make the sound attenuate faster/shorter distnaces,
            /// smaller values will make the sound carry better.
            /// @param Rolloff The factor at which the sound will attenuate.
            void SetRolloffFactor(Real Rolloff);
            /// @brief Sets the strength of the sound source.
            /// @details This function will set the strength of the sound, which will determine how well
            /// the sound from this sound source will carry over a distance.
            /// @param SoundStrength The strength of the sound.  Default: 1.0
            void SetStrength(Real SoundStrength);
            /// @brief Sets the distance from the sound source where attenuation will start.
            /// @details This function will set the distance from the sound source where attenuation
            /// effects will start being applied.
            /// @param MinDistance The distance at which attenuation effects start being applied.
            void SetMinDistance(Real MinDistance);
            /// @brief Sets the distance from the sound source where attenuation will stop.
            /// @details This function will set the distance from the sound source where attenuation
            /// effects will stop being applied.
            /// @param MaxDistance The distance at which attenuation effects stop being applied.
            void SetMaxDistance(Real MaxDistance);
            /// @brief Sets the pitch of the sound source.
            /// @details This function will set the pitch of the sound source.  Note: higher values
            /// will speed up the playback of the sound.  Default: 1.0
            /// @param Pitch The new pitch of the sound.
            void SetPitch(Real Pitch);
            /// @brief Sets the current volume of the sound source before effects.
            /// @details This function will set the current volume of the sound source before effects
            /// (like attenuation) are applied.
            /// @param Volume The current volume of the sound source to be applied.
            void SetVolume(Real Volume);
            /// @brief Sets the minimum volume the sound source can achieve.
            /// @details This function will set the minimum volume the sound source can achieve after
            /// effects(like attenuation) have been applied.
            /// @param MinVolume The minimum volume allowed for the sound source.
            void SetMinVolume(Real MinVolume);
            /// @brief Sets the maximum volume the sound source can achieve.
            /// @details This function will set the maximum volume the sound source can achieve after
            /// effects(like attenuation) have been applied.
            /// @param MaxVolume The maximum volume allowed for the sound source.
            void SetMaxVolume(Real MaxVolume);
            /// @brief Sets the inner cone angle of the sound source if you want the sound to be projected as a cone.
            /// @details This function will set the angle for the inner cone which the sound will be projected.  The
            /// cone will open up in the direction set by SetDirection().  Sounds are at their loudest only if the
            /// listener is within the inner cone.
            /// @param InnerAngle The angle of the inner cone.  Range is: 0.0 to 360.0.  Default: 360.0 (broadcast)
            void SetInnerConeAngle(Real InnerAngle);
            /// @brief Sets the outer cone angle of the sound source if you want the sound to be projected as a cone.
            /// @details This function will set the angle for the outer cone which the sound will be projected.  The
            /// cone will open up in the direction set by SetDirection().  Sounds connot be heard if the listener is
            /// outside the outer cone.
            /// @param OuterAngle The angle of the outer cone.  Range is: 0.0 to 360.0.  Default: 360.0 (broadcast)
            void SetOuterConeAngle(Real OuterAngle);
            /// @brief Sets how much the volume is scaled in the outer cone.
            /// @details This function will set how much the volume is scaled by for sounds in the outer
            /// cone of the sound source.
            /// @param OuterVolume The scale for volume for sounds in the outer cone.
            void SetOuterConeVolume(Real OuterVolume);
            /// @brief Sets the doppler strength, which impacts the doppler effect.
            /// @details This function will set the doppler strength of the sound source, which can
            /// enhance or diminish the doppler effect given off by this sound source.  Default: 1.0
            /// @param DopStr The doppler strength to be applied to this sound source.
            void SetDopplerStrength(Real DopStr);
            /// @brief Sets the doppler velocity vector.
            /// @details In most cases you shouldn't need to call this as this is handled by the engine.
            /// Is called every time position, velocity, or direction is altered.
            /// @param Velocity A vector3 representing the doppler velocity to be applied.
            void SetDopplerVelocity(Vector3 Velocity);
            /// @brief Moves the sound source.
            /// @details This function will set both the position and velocity of the sound source.
            /// @param Position The new position of the sound source.
            void Move(Vector3 Position);
            /// @brief Gets the objects position.
            /// @details Gets the objects current position.
            /// @return Returns the objects current position.
            Vector3 GetPosition();
            /// @brief Gets the objects velocity.
            /// @details Gets the objects current velocity.
            /// @return Returns the objects current velocity.
            Vector3 GetVelocity();
            /// @brief Gets the objects direction.
            /// @details Gets the objects current direction.
            /// @return Returns the objects current direction.
            Vector3 GetDirection();
            /// @brief Gets the Rolloff factor of the sound source.
            /// @details This function will get the factor used in attenuating the source over distance.
            /// @return Returns the factor used in attenuating the source over distance.
            Real GetRolloffFactor();
            /// @brief Gets the Strength of the sound source.
            /// @details This function will get the strength of the source, which determines how well
            /// the sound carries over a distance.
            /// @return Returns the strength of the source.
            Real GetStrength();
            /// @brief Gets the distance at which sound attenuation will start.
            /// @details This function will get the distance at which sound attenuation will start.
            /// @return Returns the distance from the source where attenuation will start.
            Real GetMinDistance();
            /// @brief Gets the distance at which sound attenuation will stop.
            /// @details This function will get the distance at which sound attenuation will stop.
            /// @return Returns the distance from the source where attenuation will stop.
            Real GetMaxDistance();
            /// @brief Gets the pitch of the sound source.
            /// @details This function will get the pitch of the sound source.
            /// @return Returns the pitch of the source.
            Real GetPitch();
            /// @brief Gets the current volume of the sound source.
            /// @details This function will get the current volume of the sound source before effects are applied.
            /// @return Returns the source volume before attenuation and other effects.
            Real GetVolume();
            /// @brief Gets the minimum volume of the sound source.
            /// @details This function will get the minimum volume the sound source can be attenuated to.
            /// @return Returns the minimum volume that the source can be attenuated to.
            Real GetMinVolume();
            /// @brief Gets the Maximum volume of the sound source.
            /// @details This function will get the maximum volume the sound source can achieve.
            /// @return Returns the maximum volume that the source can achieve.
            Real GetMaxVolume();
            /// @brief Gets the inner cone angle of the sound source.
            /// @details This function will get the inner cone angle of the sound source.  See SetInnerConeAngle().
            /// @return Returns the angle of the inner sound cone of the source.
            Real GetInnerConeAngle();
            /// @brief Gets the outer cone angle of the sound source.
            /// @details This function will get the outer cone angle of the sound source.  See SetOuterConeAngle().
            /// @return Returns the angle of the outer sound cone of the source.
            Real GetOuterConeAngle();
            /// @brief Gets the outer cone volume of the sound source.
            /// @details This function will get the outer cone volume of the sound source.  See SetOuterConeVolume().
            /// @return Returns how much the volume of the source is scaled in the outer cone.
            Real GetOuterConeVolume();
            /// @brief Gets the Doppler Strength of the sound.
            /// @details This function will get the doppler strength, which enhances or diminishes the doppler effect.
            /// @return Returns the doppler strength.
            Real GetDopplerStrength();
            /// @brief Gets the doppler velocity vector.
            /// @details This function will get the override for the doppler velocity vector.
            /// @return Returns the override for the doppler velocity vector.
            Vector3 GetDopplerVelocity();
    }; // sound
}//phys

#endif
