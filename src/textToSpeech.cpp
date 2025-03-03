/**
 * @brief textToSpeech.cpp class for converting string-based text to audible output
 * @authors Noah Kellett, Mert Osoydan
*/

#include "textToSpeech.h"
#include "fileEncoder.h"

/**
 * @brief textWriteCallback writes data received from a successful HTTP request
 * @param contents The data to written
 * @param size The size of the content
 * @param nmemb The number of members
 * @param userp The user data that text is written to
 * @returns size_t, the total size of the callback (the size of the call * the number of members)
 * @authors Noah Kellett, Mert Osoydan
*/
static size_t textWriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Declared early for textToSpeechAPIRequest to realize function exists
bool isValidWavHeader(const std::string& audioContent);

/**
 * @brief textToSpeechAPIRequest requests a connection to the google translation services via the curl library
 * @param text The string data that will be translated to audio file data
 * @param languageCode The selected language code that the 
 * @returns nothing, the function is void
 * @authors Noah Kellett, Mert Osoydan
*/
void textToSpeechAPIRequest(const std::string& text, const std::string& languageCode) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    // Curl initilization
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    // Curl was initialized successfully
    if(curl) {
        
        // Connection request
        std::string apiKey = ""; // Include your actual Google Cloud API key
        std::string url = "https://texttospeech.googleapis.com/v1/text:synthesize?key=" + apiKey;

        // std::string jsonPayload = "{\"input\":{\"text\":\"" + text + "\"},\"voice\":{\"languageCode\":\"" + languageCode + "\",\"name\":\"" + languageCode + "-Wavenet-D\"},\"audioConfig\":{\"audioEncoding\":\"LINEAR16\"}}";
        std::string jsonPayload = "{\"input\":{\"text\":\"" + text + "\"},\"voice\":{\"languageCode\":\"" + languageCode + "\"},\"audioConfig\":{\"audioEncoding\":\"LINEAR16\"}}";

        // Data needed for curl usage
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, textWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {

            Json::Value jsonResponse;
            Json::Reader reader;

            if(reader.parse(readBuffer, jsonResponse)) {

                // Extract the audio content (base64 encoded)
                std::string audioContentBase64 = jsonResponse["audioContent"].asString();
                
                // Decode the base64 audio content
                std::string audioContent = decodeFileFromBase64(audioContentBase64);

                // Check if the WAV file is valid after decoding
                if(isValidWavHeader(audioContent)){
                    std::cout << "WAV file is valid and will proceed to save it to a file!" << std::endl;
                    // Save the decoded audio to a WAV file
                    std::ofstream wavFile("textToSpeechOutput.wav", std::ios::binary);
                    if(wavFile.write(audioContent.c_str(), audioContent.size())) {
                        std::cout << "Audio content saved to textToSpeechOutput.wav" << std::endl;
                    } else {
                        std::cerr << "Failed to save audio content." << std::endl;
                    }

                    // Close file to avoid memory leaks
                    wavFile.close();

                } else {
                    std::cerr << "WAV file is not valid and will not proceed to save it to a file!" << std::endl;
                }
            } else {
                std::cerr << "Failed to parse the response as JSON." << std::endl;
            }
        }

        // Memory clean up of curl variables
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    // Overall memory clean up
    curl_global_cleanup();
}

/**
 * @brief isValidWavHeader verifies a wav file has a valid file header
 * @param audioContent The string for the header of the WAV file 
 * @returns a boolean, if the wav file is valid or invalid
 * @authors Noah Kellett
*/
bool isValidWavHeader(const std::string& audioContent) {
    
    // Content size is smaller than the minimum size of a wav header
    if (audioContent.size() < 44) {
        std::cerr << "File too small to be a valid WAV file." << std::endl;
        return false;
    }

    // Check the RIFF header
    if (audioContent.substr(0, 4) != "RIFF") {
        std::cerr << "Missing RIFF header." << std::endl;
        return false;
    }

    // Check the WAVE format
    if (audioContent.substr(8, 4) != "WAVE") {
        std::cerr << "Missing WAVE format." << std::endl;
        return false;
    }

    // Check the fmt subchunk (just checking for the "fmt " text)
    if (audioContent.substr(12, 4) != "fmt ") {
        std::cerr << "Missing 'fmt ' subchunk." << std::endl;
        return false;
    }

    // Check the data subchunk (just checking for the "data" text)
    if (audioContent.find("data") == std::string::npos) {
        std::cerr << "Missing 'data' subchunk." << std::endl;
        return false;
    }

    std::cout << "WAV header is valid." << std::endl;
    return true;
}
