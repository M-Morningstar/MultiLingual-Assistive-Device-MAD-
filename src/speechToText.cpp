#include "speechToText.h"

std::string readEncodedAudioFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the file content into the stringstream
    return buffer.str(); // Convert the stringstream to string and return
}

size_t speechWriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void speechToText(const std::string& apiKey, std::string encodedAudioPath) {
    std::string base64EncodedAudio = readEncodedAudioFromFile(encodedAudioPath);

    CURL* curl = curl_easy_init();
    std::string readBuffer;       // This is to hold the response from the API
    if (curl) {
        std::string url = "https://speech.googleapis.com/v1/speech:recognize?key=" + apiKey;
        std::string postData = R"({"config":{"encoding":"LINEAR16","sampleRateHertz":48000,"languageCode":"en-US"},"audio":{"content":")" + base64EncodedAudio + R"("}})";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        
        // Set headers
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set up the write callback to capture the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, speechWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request and check for errors
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Parse the response
            Json::Value root;
            Json::Reader reader;
            bool parsingSuccessful = reader.parse(readBuffer, root); // Parse the JSON response
            if (!parsingSuccessful) {
                std::cerr << "Failed to parse the response data as JSON" << std::endl;
            } else {
                // Assuming the response format from the API and extracting the transcription
                const Json::Value& results = root["results"];
                for (const auto& result : results) {
                    const Json::Value& alternatives = result["alternatives"];
                    for (const auto& alternative : alternatives) {
                        std::string transcript = alternative["transcript"].asString();
                        // Write the transcript to a file
                        std::ofstream outFile("transcript.txt", std::ios_base::out | std::ios_base::trunc); // Open in append mode
                        if (outFile.is_open()) {
                            outFile << transcript << std::endl;
                            outFile.close();
                        } else {
                            std::cerr << "Failed to open file for writing the transcript." << std::endl;
                        }
                    }
                }
            }
        }
        // Cleanup
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}