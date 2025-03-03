/**
 * @brief textToSpeech.h header file for functionality to convert string-based text to audible output
 * @authors Noah Kellett, Mert Osoydan
*/

#ifndef TEXTTOSPEECH_H
#define TEXTTOSPEECH_H

#include <string>
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <json/json.h>

/**
 * @brief textToSpeechAPIRequest requests a connection to the google translation services via the curl library
 * @param text The string data that will be translated to audio file data
 * @param languageCode The selected language code that the 
 * @returns nothing, the function is void
 * @authors Noah Kellett, Mert Osoydan
*/
void textToSpeechAPIRequest(const std::string& text, const std::string& languageCode);

/**
 * @brief isValidWavHeader verifies a wav file has a valid file header
 * @param audioContent The string for the header of the WAV file 
 * @returns a boolean, if the wav file is valid or invalid
 * @authors Noah Kellett
*/
bool isValidWavHeader(const std::string& audioContent);

#endif // TEXTTOSPEECH_H

