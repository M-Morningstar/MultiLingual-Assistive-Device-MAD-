/**
 * @brief fileEncoder.h header file for encoding to, and decoding from, a file in binary and base64
 * @authors Mert Osoydan
*/

#ifndef FILE_ENCODER_H
#define FILE_ENCODER_H

// File and string manipulation libraries
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <base64.hpp>

/**
 * @brief readFileAsBinary converts a file to readable text/strings from the binary within the file
 * @param filePath The directory/file path that the file can be located at
 * @returns a string that is the contents of the file after converting to strings
 * @authors Mert Osoydan
*/
std::string readFileAsBinary(const std::string& filePath);

/**
 * @brief saveToFile saves given content to the given file/path
 * @param content The content that will be saved into the file/path
 * @param filePath The directory/file path of the file that will have string data saved to it
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
void saveToFile(const std::string& content, const std::string& filePath);

/**
 * @brief encodeFileToBase64 encodes binary data within a file into base64 data in another file
 * @param filePath The directory/file path of the file that will be read as binary
 * @param outputPath The directory/file path of the file that will save the base 64 encoding
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
void encodeFileToBase64(const char* filePath, const std::string& outputPath);

/**
 * @brief decodeFileFromBase64 decodes encoded base64 data from within a file into decoded data
 * @param encodedString the encoded data that will be converted from base64
 * @returns a string, the decoded base64 encoded data
 * @authors Mert Osoydan
*/
std::string decodeFileFromBase64(const std::string& encodedString);

/**
 * @brief decodeTest Test for decoding string data
 * @param text The string that will be decoded
 * @returns nothing, the function is void
 * @authors Mert Osoydan
*/
void decodeTest(std::string text);

#endif // FILE_ENCODER_H

