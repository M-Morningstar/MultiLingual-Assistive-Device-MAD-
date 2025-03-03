#ifndef SPEECH_TO_TEXT_H
#define SPEECH_TO_TEXT_H

#include <string>
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <json/json.h>

// Reads encoded audio from a file and returns it as a string.
std::string readEncodedAudioFromFile(const std::string& filePath);

// Sends encoded audio to Google's Speech-to-Text API and saves the transcription.
void speechToText(const std::string& apiKey, std::string encodedAudioPath);

#endif // SPEECH_TO_TEXT_H
