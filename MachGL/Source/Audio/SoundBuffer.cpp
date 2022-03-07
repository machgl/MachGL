/*

    MachGL (Alpha)

 */

#include "../../../Headers/Audio/SoundBuffer.h"
#include "../../../Headers/API/API.h"
#include "../../../Headers/API/OpenAL/OpenALSoundBuffer.h"

namespace MachGL {
    namespace Audio {
    
        MACH_SOUND_BUFFER SoundBuffer::createSoundBuffer() {

            switch (AudioAPI::getAudioAPI()) {

                case AudioAPI::API::MACH_OPEN_AL: return make_sPoint<OpenALSoundBuffer>();
                default: return make_sPoint<OpenALSoundBuffer>();
            }
        }
    }
}