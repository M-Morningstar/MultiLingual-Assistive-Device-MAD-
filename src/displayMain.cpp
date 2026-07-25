/**
 * @brief displayMain.cpp class for running program on a display
 * @authors Fuad Ghareeb, Mert Osoydan
*/

// including all created header files
#include "displayMain.h"
#include "speechToText.h"
#include "fileEncoder.h"
#include "audioRecorder.h"
#include "textTranslation.h"
#include <cstdlib>   // for getenv()

/*
//This class is fully commented out because it requires wiring.pi and lcd libraries that can only be downloaded on rasberypi directly
//This way you can use ctrl + A to highlight the entirety of the class then ctrl + / to uncomment all the code if you ever run it on a rasberypi

using namespace std;
const char* audioFilePath = "output.wav";
const char* base64FilePath = "encodedAudio.txt";

time_t now = time(0);
char* dt = ctime(&now);

string translateApiKey = std::getenv("GOOGLE_TRANSLATE_API_KEY") ? std::getenv("GOOGLE_TRANSLATE_API_KEY") : "";
string speechApiKey = std::getenv("GOOGLE_STT_API_KEY") ? std::getenv("GOOGLE_STT_API_KEY") : "";
string textToTranslate = "Hello, how are you this fine sunday evening.";
string sourceLanguage = "en";
string targetLanguage = "tr";
string translatedText = "tr";


void textToTextTranslation() {
    const char* str;
    string temp;
    fstream historyLog("HistoryLog.txt", ios::app);
    historyLog << endl << dt;
    historyLog.close();

    while(1) {    
        while(1) {
            lcdClear(lcd);
            lcdPosition(lcd, 0, 0);
            lcdPuts(lcd, "Choose a language");
            lcdPosition(lcd, 0, 1);
            lcdPuts(lcd, "to Translate from:");
            delay(2000);
            
            cout << endl << "Choose a language to Translate from or type h for help: ";
            getline(cin, temp);

            for(auto& x: temp) {
                x = tolower(x);
            }
            
            if (!temp.compare("h")) {
                lcdClear(lcd);
                lcdPosition(lcd, 0, 0);
                lcdPuts(lcd, "Use ISO 639-2");
                lcdPosition(lcd, 0, 1);
                lcdPuts(lcd, "example: en");
                delay(2000);
                cout << "Use ISO 639-2 standard." << endl << "example: en for English and es for Spanish." << endl << "D for default" << endl;
                delay(3000);
            } else if (!temp.compare("d")) { 
                break;    
            }  else {
                sourceLanguage = temp; 
                break;
            }
        }

        while(1) {
            lcdClear(lcd);
            lcdPosition(lcd, 0, 0);
            lcdPuts(lcd, "Choose a language");
            lcdPosition(lcd, 0, 1);
            lcdPuts(lcd, "to Translate into:");
            delay(2000);
            cout << "Choose a language to Translate into or type h for help: ";
    
            getline(cin, temp);
            for(auto& x: temp) {
                x = tolower(x);
            }

            if (!temp.compare("h")) {
                cout << "Use ISO 639-2 standard." << endl << "example: en for English and es for Spanish" << endl << "d for default" << endl;
            } else if (!temp.compare("d")) { 
                break;
            } else {
                targetLanguage = temp; 
                break;
            }
        }
        
        lcdClear(lcd);
        lcdPosition(lcd, 0, 0);
        lcdPrintf(lcd, "You are currently");
        lcdPosition(lcd, 0, 1);
        lcdPrintf(lcd, "translating from %s", sourceLanguage.c_str());
        delay(2000);
        cout << "You are currently translating from " << sourceLanguage << " into " << targetLanguage << endl << endl;
        temp = "Translating from " + sourceLanguage + " to " + targetLanguage;
        str = temp.c_str();

        fstream historyLog("HistoryLog.txt", ios::app);
        historyLog << "Translating from " << sourceLanguage << " into " << targetLanguage << endl;
        historyLog.close();

        while(1) {
            lcdClear(lcd);
            lcdPosition(lcd, 0, 0);
            lcdPuts(lcd, "What do you need");
            lcdPosition(lcd, 0, 1);
            lcdPuts(lcd, "me to translate:");
            delay(2000);
            cout << "What do you need me to translate: ";
            getline(cin, temp);
            
            for(auto& x: temp) {
                x = tolower(x);
            }
            
            if (!temp.compare("h")) {
                temp = "Translating from " + sourceLanguage + " to " + targetLanguage;
                str = temp.c_str();
                cout << "You are currently translating from " << sourceLanguage << " into " << targetLanguage << endl << "To change languages press c or e to exit: ";
                getline(cin, temp);
                if (!temp.compare("c")) {
                    break;
                } else if (!temp.compare("e")) {
                    exit(0);
                }
            } else {
                textToTranslate = temp; 
                translatedText = TranslateText(textToTranslate, sourceLanguage, targetLanguage, translateApiKey);
                
                fstream historyLog("HistoryLog.txt", ios::app);

                historyLog << sourceLanguage << ": " << temp << endl << targetLanguage << ": " << translatedText << endl;
                historyLog.close();
                
                str = translatedText.c_str();
            }
        }
    }
}


void speechToTextTranslation() {
    while(1) {
        string temp;
        printToLCD("Speech to Text accepts English speech only!");
        lcdPosition(lcd, 0, 1);
        printToLCD("Choose a language");
        lcdPosition(lcd, 0, 2);
        printToLCD("to Translate to:");
        
        cout << endl << "Choose a language to Translate to: ";
        getline(cin, temp);

        targetLanguage = temp;

        printToLCD("Recording audio...");
        recordAudio(audioFilePath);

        printToLCD("Encoding audio to Base64...");
        encodeFileToBase64(audioFilePath, base64FilePath);

        printToLCD("Sending audio to Speech-to-Text API...");
        speechToText(speechApiKey, base64FilePath);

        translate("transcript.txt");

        std::string filePath = "transcript.txt";
        std::ifstream transcript(filePath);
        std::string content;

        if (transcript) {
            std::ostringstream ss;
            ss << transcript.rdbuf(); // Reading data
            content = ss.str(); // Storing the data
        } else {
            printToLCD("Could not open the file:");
            printToLCD(filePath.c_str());
            delay(2000);
        }

        translateText(content, sourceLanguage, targetLanguage, translateApiKey);

        std::ifstream translated("translatedText.txt");
        std::string line;

        if (translated.is_open()) {
            while (std::getline(translated, line)) {
                printToLCD(line.c_str());
                delay(1000); // Delay to display each line
            }
            translated.close();
        } else {
            printToLCD("Unable to open file");
            delay(2000);
        }

        printToLCD("Do you want to keep going?(y/n)");
        getline(cin, temp);

        if(temp.compare("n")){
            break;
        }
    }
    // Code for speech-to-text translation
}


void textToSpeechTranslation() {
    const char* str;
    string temp;
    string voiceLanguage;

    while(1) {    
        while(1) {
            lcdClear(lcd);
            lcdPosition(lcd, 0, 0);
            lcdPuts(lcd, "Choose a language");
            lcdPosition(lcd, 0, 1);
            lcdPuts(lcd, "to Translate from:");
            delay(2000);
            cout << endl << "Choose a language to Translate from or type h for help: ";
            getline(cin, temp);

            for(auto& x: temp) {
                x = tolower(x);
            }
            
            if (!temp.compare("h")) {
                lcdClear(lcd);
                lcdPosition(lcd, 0, 0);
                lcdPuts(lcd, "Use ISO 639-2");
                lcdPosition(lcd, 0, 1);
                lcdPuts(lcd, "example: en");
                delay(2000);
                cout << "Use ISO 639-2 standard." << endl << "example: en for English and es for Spanish." << endl << "D for default" << endl;
                delay(3000);
            } else if (!temp.compare("d")) { 
                sourceLanguage = "en";
                break;    
            }  else if (isValidLanguageCode(temp)) {
                sourceLanguage = temp;
                break;
            } else {
                lcdClear(lcd);
                lcdPosition(lcd, 0, 0);
                lcdPuts(lcd, "Invalid language");
                lcdPosition(lcd, 0, 1);
                lcdPuts(lcd, "Please use ISO 639-2");
                delay(2000);
                cout << "Invalid language output. Please use the ISO 639-2 standard." << endl << "example: en for English and es for Spanish." << endl;
                delay(3000);
            }
        }
        
        while(1) {
            lcdClear(lcd);
            lcdPosition(lcd, 0, 0);
            lcdPuts(lcd, "Choose a language");
            lcdPosition(lcd, 0, 1);
            lcdPuts(lcd, "to Translate into:");
            delay(2000);
            cout << "Choose a language to Translate into or type h for help: ";
    
            getline(cin, temp);
            for(auto& x: temp) {
                x = tolower(x);
            }

            if (!temp.compare("h")) {
                cout << "Use ISO 639-2 standard." << endl << "example: en for English and es for Spanish" << endl << "for the full list visit: https://www.sitepoint.com/iso-2-letter-language-codes/" << endl;
                delay(3000);
            } else if (!temp.compare("d")) { 
                break;
            } else {
                targetLanguage = temp; 
                break;
            }
        }
        
        lcdClear(lcd);
        lcdPosition(lcd, 0, 0);
        lcdPrintf(lcd, "You are currently");
        lcdPosition(lcd, 0, 1);
        lcdPrintf(lcd, "translating from %s", sourceLanguage.c_str());
        delay(2000);
        cout << "You are currently translating from " << sourceLanguage << " into " << targetLanguage << endl << endl;
        temp = "Translating from " + sourceLanguage + " to " + targetLanguage;
        str = temp.c_str();

        while(1) {
            lcdClear(lcd);
            lcdPosition(lcd, 0, 0);
            lcdPuts(lcd, "What do you need");
            lcdPosition(lcd, 0, 1);
            lcdPuts(lcd, "me to translate:");
            delay(2000);
            cout << "What do you need me to translate: ";
            getline(cin, temp);
            
            for(auto& x: temp) {
                x = tolower(x);
            }
            
            if (!temp.compare("h")) {
                temp = "Translating from " + sourceLanguage + " to " + targetLanguage;
                str = temp.c_str();
                cout << "You are currently translating from " << sourceLanguage << " into " << targetLanguage << endl << "To change languages press c or e to exit: ";
                getline(cin, temp);
                if (!temp.compare("c")) {
                    break;
                } else if (!temp.compare("e")) {
                    exit(0);
                }
            } else {
                textToTranslate = temp;

                translatedText = TranslateText(textToTranslate, sourceLanguage, targetLanguage, translateApiKey);

                voiceLanguage = convertToGoogleVoiceFormat(targetLanguage);

                textToSpeechAPIRequest(translatedText, voiceLanguage);

                cout << "Audio content saved will now proceed to resample!" << endl;

                // resampleWav("textToSpeechOutput.wav", "ttsResampled.wav");

                cout << "Audio file created do you want to play it:(y/n) ";
                getline(cin, temp);

                if (temp == "y") {
                    playWAV("textToSpeechOutput.wav");
                }
            }
        }
    }
    // Code for text-to-speech translation
}

*/


/**
 * @brief runDisplay starts program on a display
 * @returns an integer for the exits status of the method
 * @authors Fuad Ghareeb, Mert Osoydan
*/
int runDisplay(){
    std::cout << "Run Display is working make sure you are running it on a rasbery pi with Wiring.pi and lcd libraries\n";

    /*
    
    int lcd;
    wiringPiSetup();
    lcd = lcdInit(2,16,8, LCD_RS, LCD_E, LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
    string methodChoice;
    
    lcdClear(lcd);
    lcdPuts(lcd, "choose a method");
    delay(1200);
    lcdClear(lcd);
    
    
    getline(cin, methodChoice);

    for (auto &x : methodChoice) {
        x = tolower(x);
    }

    if (methodChoice == "h") {
        cout << "Use ISO 639-2 standard." << endl;
        cout << "example: TtT for text-to-text, StT for speech-to-text and TtS for text-to-speech." << endl;
    } else if (methodChoice == "ttt") {
        textToTextTranslation();
    } else if (methodChoice == "stt") {
        speechToTextTranslation();
    } else if (methodChoice == "tts") {
        textToSpeechTranslation();
    } else {
        cerr << "Invalid translation method selected. Please use 'TtT', 'StT', or 'TtS'." << endl;
    }
        
    */
    return 0;
}
