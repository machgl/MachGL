/*

	Mach::GL (Alpha)

*/

#include "../../Headers/Audio/SoundSource.h"
#include "../../../Headers/API/API.h"
#include "../../Headers/API/OpenAL/OpenALSoundSource.h"

namespace MachGL {
	namespace Audio {

		MACH_SOUND_SOURCE SoundSource::createSoundSource() {

			switch (AudioAPI::getAudioAPI()) {

				case AudioAPI::API::MACH_OPEN_AL: return make_sPoint<OpenALSoundSource>();
				default: return make_sPoint<OpenALSoundSource>();
			}
		}
	}
}