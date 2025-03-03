#ifndef WAVPLAYER_H
#define WAVPLAYER_H
#define SDL_MAIN_HANDLED

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <SDL.h>

// Buffer size for reading the WAV file
#define BUF_SIZE 4096

// WAV Header structure
struct WAVHeader {
    char riff_header[4]; // Contains "RIFF"
    int wav_size;        // Size of the WAV portion of the file, which follows the first 8 bytes
    char wave_header[4]; // Contains "WAVE"
    char fmt_header[4];  // Contains "fmt " (includes trailing space)
    int fmt_chunk_size;  // Should be 16 for PCM
    short audio_format;  // Should be 1 for PCM. 3 for IEEE Float
    short num_channels;
    int sample_rate;
    int byte_rate;       // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
    short sample_alignment; // num_channels * Bytes Per Sample
    short bit_depth;        // Number of bits per sample
};

// Function prototype to play WAV file
int playWAV(const char* filePath);

#endif // WAVPLAYER_H
