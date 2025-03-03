#include "wavPlayer.h"

using namespace std;

int playWAV(const char* filePath) {
    // Initialize SDL.
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Load WAV file.
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    if (SDL_LoadWAV(filePath, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        std::cerr << "Failed to load WAV file! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Open audio device.
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0) {
        std::cerr << "Failed to open audio device! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeWAV(wavBuffer);
        SDL_Quit();
        return 1;
    }

    // Play audio.
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

    // Wait until finished playing.
    while (SDL_GetQueuedAudioSize(deviceId) > 0) {
        SDL_Delay(100);
    }

    // Clean up.
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();

    return 0;
}





// Function to play WAV file using libao
// int playWAV(const char* filePath) {
//     std::cout << "Play WAV function started running!" << std::endl;
//     std::ifstream file(filePath, std::ios::binary);
//     WAVHeader header;

//     if (!file.read((char*)&header, sizeof(header))) {
//         std::cerr << "Error reading WAV file header." << std::endl;
//         return 1;
//     }

//     // Basic validation of WAV header
//     if (std::strncmp(header.riff_header, "RIFF", 4) || std::strncmp(header.wave_header, "WAVE", 4)) {
//         std::cerr << "Invalid WAV file format." << std::endl;
//         return 1;
//     }

//     // Initialize libao
//     ao_initialize();
//     int default_driver = ao_default_driver_id();
//     ao_sample_format format;
//     memset(&format, 0, sizeof(format));

//     format.bits = header.bit_depth;
//     format.channels = header.num_channels;
//     format.rate = header.sample_rate;
//     format.byte_format = AO_FMT_LITTLE; // Assumes little endian format

//     std::cout << "Attempting to open device with the following format:" << std::endl;
//     std::cout << "Bits per Sample: " << format.bits << std::endl;
//     std::cout << "Channels: " << format.channels << std::endl;
//     std::cout << "Sample Rate: " << format.rate << std::endl;
//     std::cout << "Byte Format: " << (format.byte_format == AO_FMT_LITTLE ? "Little Endian" : 
//                         (format.byte_format == AO_FMT_BIG ? "Big Endian" : "Native Endian")) << std::endl;



//     std::cout << "Trying to open audio device!" << std::endl;

//     ao_option option;
//     option.key = "driver";
//     option.value = "default";
//     option.next = NULL;

//     ao_device* device = ao_open_live(default_driver, &format, &option);

//     if (device == NULL) {
//         std::cerr << "Error opening device" << std::endl;
//         return 1;
//     }

//     // Read and play the rest of the WAV file
//     std::vector<char> buffer(BUF_SIZE);
//     while (!file.eof()) {
//         file.read(buffer.data(), buffer.size());
//         size_t bytesRead = file.gcount();

//         if (!ao_play(device, buffer.data(), bytesRead)) {
//             std::cerr << "Error playing WAV file." << std::endl;
//             ao_close(device);
//             ao_shutdown();
//             return 1;
//         }
//     }

//     ao_close(device);
//     ao_shutdown();

//     std::cout << "Play WAV function finished running!" << std::endl;
//     return 0;
// }
