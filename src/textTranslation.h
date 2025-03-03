#ifndef TEXT_TRANSLATION_H
#define TEXT_TRANSLATION_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>

// Performs the translation by making an HTTP POST request to the Google Translate API.
void translateText(const std::string& sourceText, const std::string& sourceLang, const std::string& targetLang, const std::string& apiKey);

// Translates text and returns the translated string.
std::string TranslateText(const std::string& sourceText, const std::string& sourceLang, const std::string& targetLang, const std::string& apiKey);

// Reads text from a file and uses the translateText function to translate it.
void translate(const std::string& filePath);

#endif // TEXT_TRANSLATION_H
