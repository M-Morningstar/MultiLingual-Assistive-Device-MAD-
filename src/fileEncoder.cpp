/**
 * @brief fileEncoder.cpp class for encoding to, and decoding from, a file in binary and base64
 * @authors Mert Osoydan
*/

#include "fileEncoder.h"

/**
 * @brief readFileAsBinary converts a file to readable text/strings from the binary within the file
 * @param filePath The directory/file path that the file can be located at
 * @returns a string that is the contents of the file after converting to strings
 * @authors Mert Osoydan
*/
std::string readFileAsBinary(const std::string& filePath) {
    // Open the file in binary mode
    std::ifstream file(filePath, std::ios::binary);
    // Read the file into a vector
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
    // Convert the binary data to a string (assuming the file is not too large)
    std::string binaryData(buffer.begin(), buffer.end());
    return binaryData;
}

/**
 * @brief saveToFile saves given content to the given file/path
 * @param content The content that will be saved into the file/path
 * @param filePath The directory/file path of the file that will have string data saved to it
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
void saveToFile(const std::string& content, const std::string& filePath) {
    std::ofstream outFile(filePath);
    // Successfully opens the file
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
        std::cout << "Content has been saved to " << filePath << std::endl;
    } else {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
    }
}

/**
 * @brief encodeFileToBase64 encodes binary data within a file into base64 data in another file
 * @param filePath The directory/file path of the file that will be read as binary
 * @param outputPath The directory/file path of the file that will save the base 64 encoding
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
void encodeFileToBase64(const char* filePath, const std::string& outputPath) {
    std::string binaryData = readFileAsBinary(filePath);
    // Use the base64 library to encode
    std::string encodedAudio = base64::to_base64(binaryData);

    saveToFile(encodedAudio, outputPath);
}

/**
 * @brief decodeFileFromBase64 decodes encoded base64 data from within a file into decoded data
 * @param encodedString the encoded data that will be converted from base64
 * @returns a string, the decoded base64 encoded data
 * @authors Mert Osoydan
*/
std::string decodeFileFromBase64(const std::string& encodedString) {
    std::cout << "File decoder started running!" << std::endl;
    std::string decodedData = base64::from_base64(encodedString);
    std::cout << "File decoder finished running!" << std::endl;
    return decodedData;
}

/**
 * @brief decodeTest Test for decoding string data
 * @param text The string that will be decoded
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
void decodeTest(std::string text){
    std::cout << "File decoder test running!" << std::endl;
    std::string decodedData = base64::from_base64(text);
    std::cout << "File decoder test ended!" << std::endl;
}
