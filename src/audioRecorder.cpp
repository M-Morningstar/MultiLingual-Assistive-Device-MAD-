/**
 * @brief audioRecorder.cpp class for recording audio from a user's device
 * @authors Mert Osoydan
*/
#include "audioRecorder.h"

/**
 * @brief checkErr checks the current status of port audio use and if an error has occured
 * @param err A typedef variable for if an error has occured when compared with it's integer value
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
void checkErr(PaError err){
    if(err != paNoError){
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief paTestCallback verifies space and sample requirements for when it will record audio
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
) {
    // Cast userData to AudioData*
    AudioData* data = (AudioData*)userData;
    short* in = (short*)inputBuffer;
    
    // Calculate the new total number of samples after adding the incoming frames
    size_t newSamplesTotal = data->numSamples + framesPerBuffer;

    // Ensure we have enough space for the new samples
    if(newSamplesTotal > data->maxSamples) {
        return paAbort;
    }

    // Copy the incoming samples to the recordedSamples buffer
    memcpy(data->recordedSamples + data->numSamples, in, framesPerBuffer * sizeof(short));
    
    // Update the number of samples recorded
    data->numSamples += framesPerBuffer;

    return paContinue;
}

/**
 * @brief saveToWav saves recorded audio as a .wav file to be used in Google Speech-to-Text API
 * @param filename The name of the file the audio will be saved in
 * @param data The recorded audio to be saved to a file
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
// Used to save the recorded audio as a WAV file to then send it to the Google Cloud Speech-to-Text API
void saveToWav(const char* filename, AudioData* data) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", filename);
        return;
    }

    int sampleRate = SAMPLE_RATE;
    int numChannels = 1; // Mono recording
    int bitsPerSample = 16; // Using int16_t or short, hence 16 bits per sample

    int byteRate = sampleRate * numChannels * (bitsPerSample / 8);
    int blockAlign = numChannels * (bitsPerSample / 8);

    size_t subchunk2Size = data->numSamples * numChannels * (bitsPerSample / 8);
    size_t chunkSize = 36 + subchunk2Size;

    // Writing the RIFF header
    fwrite("RIFF", sizeof(char), 4, file);
    fwrite(&chunkSize, sizeof(chunkSize), 1, file);
    fwrite("WAVE", sizeof(char), 4, file);

    // Writing the fmt subchunk
    fwrite("fmt ", sizeof(char), 4, file);
    int subchunk1Size = 16; // For PCM
    fwrite(&subchunk1Size, sizeof(subchunk1Size), 1, file);
    short audioFormat = 1; // PCM = 1
    fwrite(&audioFormat, sizeof(audioFormat), 1, file);
    fwrite(&numChannels, sizeof(numChannels), 1, file);
    fwrite(&sampleRate, sizeof(sampleRate), 1, file);
    fwrite(&byteRate, sizeof(byteRate), 1, file);
    fwrite(&blockAlign, sizeof(blockAlign), 1, file);
    fwrite(&bitsPerSample, sizeof(bitsPerSample), 1, file);

    // Writing the data subchunk
    fwrite("data", sizeof(char), 4, file);
    fwrite(&subchunk2Size, sizeof(subchunk2Size), 1, file);
    fwrite(data->recordedSamples, sizeof(short), data->numSamples, file);

    fclose(file);
}

/**
 * @brief recordAudio 
 * @param err A typedef variable for if an error has occured when compared with it's integer value
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
void recordAudio(const char* outputFilename){
    AudioData data = {0};

    PaError err = Pa_Initialize();
    checkErr(err);

    size_t totalSamples = SAMPLE_RATE * 5; // 10 seconds of audio
    size_t requiredMemory = totalSamples * sizeof(short); // Total memory required

    data.recordedSamples = (short*)malloc(requiredMemory);
    if (!data.recordedSamples) {
        printf("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    data.maxSamples = totalSamples;
    
    int numDevices = Pa_GetDeviceCount();
    printf("Number of devices: %d\n", numDevices);  

    if(numDevices < 0){
        printf("Error getting device count.\n");
        exit(EXIT_FAILURE);
    }else if(numDevices == 0){
        printf("There are no available audio devices on this machine.\n");
        exit(EXIT_SUCCESS);
    } 

    const PaDeviceInfo* deviceInfo;

    for (int i = 0; i < numDevices; i++){
        deviceInfo = Pa_GetDeviceInfo(i);
        printf("Device %d:\n", i);
        printf("  name: %s\n", deviceInfo->name);
        printf("  maxInputChannels: %d\n", deviceInfo->maxInputChannels);
        printf("  maxOutputChannels: %d\n", deviceInfo->maxOutputChannels);
        printf("  defaultSampleRate: %f\n", deviceInfo->defaultSampleRate);
    }

    int inputDevice = 2;                    // Pick the input device here
    // int outputDevice = 1;                // Pick the output device here

    PaStreamParameters inputParameters;
    // PaStreamParameters outputParameters;

    memset(&inputParameters, 0, sizeof(inputParameters));
    inputParameters.channelCount = 1;
    inputParameters.device = inputDevice;
    inputParameters.hostApiSpecificStreamInfo = NULL;       // Might need to change depending if we need to include Cloud stt API format here
    inputParameters.sampleFormat = paInt16;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputDevice)->defaultLowInputLatency;

    PaStream* stream;
    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        NULL,               // No output needed since this is only recording
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paNoFlag,
        paTestCallback,
        &data
    );
    checkErr(err);
    printf("Starting stream!\n");
    err = Pa_StartStream(stream);
    checkErr(err);

    Pa_Sleep(5 * 1000);

    err = Pa_StopStream(stream);
    checkErr(err);
    printf("Stopped stream!\n");

    err = Pa_CloseStream(stream);
    checkErr(err);
    
    err = Pa_Terminate();
    checkErr(err);

    // After recording is stopped call the function to save it as a WAV file
    saveToWav(outputFilename, &data);

    // Free allocated memory
    free(data.recordedSamples);
}