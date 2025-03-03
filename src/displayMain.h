/**
 * @brief displayMain.h header file for providing functionality for displayMain.cpp
 * @authors Fuad Ghareeb, Mert Osoydan
*/

#ifndef DISPLAY_MAIN_H
#define DISPLAY_MAIN_H

// All imported libraries necessary for translation
// as well as text-to-speech and speech-to-text
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <json/json.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <portaudio.h>
#include <vector>
#include <base64.hpp>
// Raspberry Pi required libraries
// #include <wiringPi.h>
// #include <lcd.h>

// Raspberry Pi required constants
// #define LCD_RS 25
// #define LCD_E 24
// #define LCD_D0 29
// #define LCD_D1 28
// #define LCD_D2 27
// #define LCD_D3 26
// #define LCD_D4 23
// #define LCD_D5 22
// #define LCD_D6 21
// #define LCD_D7 14

/**
 * @brief runDisplay starts program on a display
 * @returns an itneger for the exits status of the method
 * @authors Mert Osoydan
*/
int runDisplay();


#endif
