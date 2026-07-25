#include "textTranslation.h"
#include <cstdlib>   // for getenv()

using namespace std;

size_t translationWriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/*
This function performs the translation by making an HTTP POST request to the Google Translate API.
*/
void translateText(const std::string& sourceText, const std::string& sourceLang, const std::string& targetLang, const std::string& apiKey) {
    CURL *curl = curl_easy_init();                                                                              // Initialize the curl session
    CURLcode res;
    std::string readBuffer;
    if(curl) {
        char* output = curl_easy_escape(curl, sourceText.c_str(), sourceText.length());                         //Include the text to be translated in the HTTP request
        if(output) {
            std::string escapedText(output);
            curl_free(output);                                                                                  // It's important to free the output string to avoid memory leaks
            std::string url = "https://translation.googleapis.com/language/translate/v2?key=" + apiKey;         // URL that goes to the API using the unique API key
            std::string postData = "q=" + escapedText + "&source=" + sourceLang + "&target=" + targetLang;      // Data to be sent in the POST request, which includes the encoded text to translate and the source and target language codes.

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, translationWriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            res = curl_easy_perform(curl);                                                                      // Execute the HTTP request
            if(res != CURLE_OK)                                                                                 // If there is an error print it out
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            else { // If there is no error, parse the response JSON and save it
                Json::Value jsonData;
                Json::Reader jsonReader;
                if(jsonReader.parse(readBuffer, jsonData)) {
                    std::string translatedText = jsonData["data"]["translations"][0]["translatedText"].asString();

                    // Open the file and write the translated text to it
                    std::ofstream outFile("translatedText.txt");
                    if (outFile.is_open()) {
                        outFile << translatedText;
                        outFile.close();
                        std::cout << "Translated text has been saved to translatedText.txt" << std::endl;
                    } else {
                        std::cerr << "Failed to open file for writing the translated text." << std::endl;
                    }
                }
            }
        }
        curl_easy_cleanup(curl);
    }
}

string TranslateText(const std::string& sourceText, const std::string& sourceLang, const std::string& targetLang, const std::string& apiKey) {
    CURL *curl = curl_easy_init();                                                                              // Initialize the curl session
    CURLcode res;
    std::string readBuffer;
    std::string translatedText;
    if(curl) {
        char* output = curl_easy_escape(curl, sourceText.c_str(), sourceText.length());                         //Include the text to be translated in the HTTP request
        if(output) {
            std::string escapedText(output);
            curl_free(output);                                                                                  // It's important to free the output string to avoid memory leaks
            std::string url = "https://translation.googleapis.com/language/translate/v2?key=" + apiKey;         // URL that goes to the API using the unique API key
            std::string postData = "q=" + escapedText + "&source=" + sourceLang + "&target=" + targetLang;      // Data to be sent in the POST request, which includes the encoded text to translate and the source and target language codes.

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, translationWriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);                                                                      // Execute the HTTP request
            if(res != CURLE_OK)                                                                                 // If there is an error print it out
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            else {                                                                                              // If there is no error read the response JSON and print it
                Json::Value jsonData;
                Json::CharReaderBuilder builder;
                std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
                std::string errors;
                
                if(reader->parse(readBuffer.c_str(), readBuffer.c_str() + readBuffer.size(), &jsonData, &errors)) {
                    translatedText = jsonData["data"]["translations"][0]["translatedText"].asString();
                    std::cout << "Translated Text: " << translatedText << std::endl;
                }
            }
        }
        curl_easy_cleanup(curl);
    }
            return translatedText;
}


void translate(const std::string& filePath){
    const char* env_apiKey = std::getenv("GOOGLE_TRANSLATE_API_KEY");
    if (!env_apiKey) {
        std::cerr << "Error: GOOGLE_TRANSLATE_API_KEY environment variable not set!" << std::endl;
        return;
    }
    std::string apiKey(env_apiKey);
    std::string sourceLanguage = "en";
    std::string targetLanguage = "es";

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    translateText(buffer.str(), sourceLanguage, targetLanguage, apiKey);
}
