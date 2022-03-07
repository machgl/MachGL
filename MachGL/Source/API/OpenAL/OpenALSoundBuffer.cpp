/*

    MachGL (Alpha)

 */

#include "../../../Headers/API/OpenAL/OpenALSoundBuffer.h"

#define MINIMP3_IMPLEMENTATION
#include "minimp3.h"
#include "minimp3_ex.h"

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"


namespace MachGL {
    namespace Audio {

        AudioFileFormats OpenALSoundBuffer::getFormat(const std::string& filename) {
            
            std::filesystem::path path = filename;
            std::string extension = path.extension().string();

            if (extension == ".mp3") return AudioFileFormats::MP3;
            if (extension == ".ogg") return AudioFileFormats::OGG;
            return AudioFileFormats::UNKNOWN;
        }

        ALenum OpenALSoundBuffer::getALFormat(uint32_t channels) {
            
            switch (channels) {

                case 1: return AL_FORMAT_MONO16;
                case 2: return AL_FORMAT_STEREO16;
                default: return 0;
            }
        }

        const std::string& OpenALSoundBuffer::getVorbisError(const int& errorCode) {

            switch (errorCode) {

                case -128: return "Error reading the file";
                case -129: return "Internal logic fault: bug or heap/stack corruption";
                case -132: return "Bitstream does not contain any Vorbis data";
                case -133: return "Invalid Vorbis bitstream header";
                case -134: return "Vorbis version mismatch";
                default: return "";
            }
        }

        ALuint OpenALSoundBuffer::loadOggFromFile(const std::string& filename) {

            uint32_t bufferID = 0;
            const ov_callbacks callbacks{ read, seek, nullptr, tell };
            std::ifstream stream;
            OggVorbis_File file;
 
            stream.open(filename, std::ios::binary);

            if (stream.is_open())
                MACH_MSG("Loaded: " + filename);
            else {
                MACH_ERROR_MSG("Could not open: " + filename);
                return 0;
            }

            int result = ov_open_callbacks(&stream, &file, nullptr, 0, callbacks);
            
            if (result < 0) {
             
                MACH_ERROR_MSG("Error opening file: " + filename + " " + getVorbisError(result));
                return 0;
            }
        
            vorbis_info* vi = ov_info(&file, -1);
            auto sampleRate = vi->rate;
            auto channels = vi->channels;
            auto alFormat = getALFormat(channels);

            uint64_t samples = ov_pcm_total(&file, -1);
            float trackLength = (float)samples / (float)sampleRate;
            uint32_t bufferSize = 2 * channels * samples;
            uint8_t* audioScratchBuffer = new uint8_t[bufferSize];

            uint8_t* oggBuffer = audioScratchBuffer;
            uint8_t* bufferPtr = oggBuffer;
            int eof = 0;

            while (!eof) {

                int currentSection;
                long length = ov_read(&file, (char*)bufferPtr, 4096, 0, 2, 1, &currentSection);
                bufferPtr += length;

                if (length == 0)
                        eof = 1;
                else if (length < 0) 
                    MACH_ERROR_MSG("Corrupt bitstream section in: " + filename);
            }

            ov_clear(&file);

            uint32_t size = bufferPtr - oggBuffer;

            alGenBuffers(1, &bufferID);
            alBufferData(bufferID, alFormat, oggBuffer, size, sampleRate);
                
            return bufferID;
        }

        ALuint OpenALSoundBuffer::loadMP3FromFile(const std::string& filename) {
            
            ALuint bufferID;
            mp3dec_file_info_t fileInfo;
            mp3dec_t mp3Decoder;

            if (mp3dec_load(&mp3Decoder, filename.c_str(), &fileInfo, NULL, NULL))
                MACH_ERROR_MSG("Could not load: " + filename);
            else 
                MACH_MSG("Loaded: " + filename);
            
            uint32_t size = fileInfo.samples * sizeof(mp3d_sample_t);

            auto sampleRate = fileInfo.hz;
            auto channels = fileInfo.channels;
            auto alFormat = getALFormat(channels);
            float lengthInSeconds = size / (fileInfo.avg_bitrate_kbps * 1024.0f);

            alGenBuffers(1, &bufferID);
            alBufferData(bufferID, alFormat, fileInfo.buffer, size, sampleRate);

            return bufferID;
        }



        void OpenALSoundBuffer::addSoundEffect(AudioFile& audioFile) {

            std::string filename = audioFile.getFilename();

            if (getFormat(filename) == AudioFileFormats::MP3) audioFile.setBufferID(loadMP3FromFile(filename));
            if (getFormat(filename) == AudioFileFormats::OGG) audioFile.setBufferID(loadOggFromFile(filename));

            m_soundEffects.push_back(audioFile);
        }

        void OpenALSoundBuffer::removeSoundEffect(AudioFile& audioFile) {

            for (size_t i = 0; i < m_soundEffects.size(); i++) {

                if (m_soundEffects[i].getBufferID() == audioFile.getBufferID()) {

                    alDeleteBuffers(1, &m_soundEffects[i].getBufferID());
                    m_soundEffects.erase(m_soundEffects.begin() + i);
                }
            }
        }

        OpenALSoundBuffer::~OpenALSoundBuffer() {

            for (size_t i = 0; i < m_soundEffects.size(); i++)
                alDeleteBuffers(1, &m_soundEffects[i].getBufferID());
        }
    }
}