/**
 * @brief languageCodes.h header file for keeping and comparing all language codes in translations
 * @authors Mert Osoydan
*/

#ifndef LANGUAGECODES_H
#define LANGUAGECODES_H

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>

/**
 * @brief isValidLanguageCode checks if a given code is a valid ISO 639-1 language code in the map
 * @param code The language code having it's validity verified
 * @returns a boolean for if the lanuage provided is valid or invalid
 * @authors Mert Osoydan
*/
bool isValidLanguageCode(const std::string& code);

/**
 * @brief convertToGoogleVoiceFormat converts language code to google's version of a language code
 * @param isoCode The language code to be converted into a google language code
 * @returns a string representing the new code that will be used to identify the selected language
 * @authors Mert Osoydan
*/
std::string convertToGoogleVoiceFormat(const std::string& isoCode);

#endif // LANGUAGECODES_H

