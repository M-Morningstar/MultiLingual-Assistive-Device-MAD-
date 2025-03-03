/**
 * @brief audioRecorder.h header file for providing functionality for audioRecorder.cpp
 * @authors Mert Osoydan
*/

#ifndef AUDIO_RECORDER_H
#define AUDIO_RECORDER_H

#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <portaudio.h>

// Constant values
#define SAMPLE_RATE 48000
#define FRAMES_PER_BUFFER 512

typedef struct {
    short* recordedSamples; // Pointer to dynamically allocated memory holding audio samples
    size_t numSamples;      // Number of samples recorded
    size_t maxSamples;      // Maximum number of samples that can currently be held in recordedSamples
} AudioData;

/**
 * @brief checkErr checks the current status of port audio use and if an error has occured
 * @param err A typedef variable for if an error has occured when compared with it's integer value
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
void checkErr(PaError err);

/**
 * @brief paTestCallback verifies space and sample requirements for recording audio
 * @param inputBuffer The audio data given by a user's input audio device/microphone
 * @param outputBuffer The audio data given to a user through their chosen output device
 * @param framesPerBuffer The amount of time provided for "recording" a user's input
 * @param timeInfo Amount of time, expressed in seconds, for the buffers in the function
 * @param statusFlags Flag bits required for a Port Audio callback function
 * @param userData A space for data that is will be output or input to be stored
 * @returns an integer that represents if the function should continue or abort operations
 * @authors Mert Osoydan
*/
int paTestCallback(
    const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData
);

/**
 * @brief saveToWav saves recorded audio as a .wav file to be used in Google Speech-to-Text API
 * @param filename The name of the file the audio will be saved in
 * @param data The recorded audio to be saved to a file
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
void saveToWav(const char* filename, AudioData* data);

/**
 * @brief recordAudio 
 * @param err A typedef variable for if an error has occured when compared with it's integer value
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
void recordAudio(const char* outputFilename);

#endif // AUDIO_RECORDER_H

