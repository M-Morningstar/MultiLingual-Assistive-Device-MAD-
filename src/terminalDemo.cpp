#include "terminalDemo.h"
#include "speechToText.h"
#include "fileEncoder.h"
#include "audioRecorder.h"
#include "textTranslation.h"
#include "textToSpeech.h"
#include "languageCodes.h"
#include "wavPlayer.h"

using namespace std;

    const char* audioFilePath = "output.wav";
    const char* base64FilePath = "encodedAudio.txt";

    time_t now = time(0);
    char* dt = ctime(&now);

    string translateApiKey = "";
    string speechApiKey = "";
    string textToTranslate = "Hello, how are you this fine sunday evening.";
    string sourceLanguage = "en";
    string targetLanguage = "tr";
    string translatedText = "tr";

void textToTextTranslation() {
    const char* str;
    string temp;
    fstream historyLog("HistoryLog.txt", ios::app);
    historyLog <<endl<<dt;
    // historyLog.close();

    while(1){    
        while(1){
            cout<<endl<<"Choose a language to Translate from or type h for help: ";
            getline(cin, temp);

            for(auto& x: temp){
                x= tolower(x);
            }
            
            if(temp == "h"){
                cout<<"Use ISO 639-2 standard."<<endl<<"example: en for English and es for Spanish."<<endl<< "D for defualt"<<endl;
        
            } else if(temp == "d") { 
                break;    
            }  else {
                sourceLanguage = temp; 
                break;
            }
        }
        

        while(1){
            cout<<"Choose a language to Translate into or type h for help: ";
    
            getline(cin, temp);
            for(auto& x: temp){
                x= tolower(x);
            }

            if(temp == "h"){
                cout<<"Use ISO 639-2 standard."<<endl<<"example: en for English and es for Spanish"<<endl<< "d for defualt"<<endl;
            } else if(temp == "d") { 
                break;
            } else {
                targetLanguage = temp; 
                break;
            }
        }
        
        cout<<"You are currently translating from "<<sourceLanguage<<" into "<<targetLanguage<<endl<<endl;
        temp = "Translating from " + sourceLanguage + " to " + targetLanguage;
        str = temp.c_str();

        // fstream historyLog("HistoryLog.txt", ios::app);
        historyLog<<"Translating from "<<sourceLanguage<<" into "<<targetLanguage<<endl;
        // historyLog.close();

        cout<<"What do you need me to translate: ";
        getline(cin, temp);
        
        for(auto& x: temp){
            x= tolower(x);
        }
            
        if(temp == "h"){
            temp = "Translating from " + sourceLanguage + " to " + targetLanguage;
            str = temp.c_str();
            cout<<"You are currently translating from "<<sourceLanguage<<" into "<<targetLanguage<<endl<< "To change languages press c or e to exit: ";
            getline(cin, temp);
            if(temp == "c"){
                continue;
            } else if(temp == "e") {
                exit(0);
            }
        
        } else {
            textToTranslate = temp; 
            translatedText = TranslateText(textToTranslate, sourceLanguage, targetLanguage, translateApiKey);
            
            // fstream historyLog("HistoryLog.txt", ios::app);

            historyLog<<sourceLanguage<<": "<<temp<<endl<<targetLanguage<<": "<<translatedText<<endl;
            historyLog.close();
            
            str = translatedText.c_str();
        }

        std::cout << "Do you want to keep going?(y/n)" << endl;
        getline(cin, temp);   

        if(temp == "n"){
            break;
        }
    }
}

void speechToTextTranslation() {
    fstream historyLog("HistoryLog.txt", ios::app);
    historyLog <<endl<<dt;
    // historyLog.close();
    // historyLog.close();
    while(1) {
        string temp;
        std::cout << "Speech to Text accepts English speech only!" << endl;

        while(1){
            cout<<"Choose a language to Translate into or type h for help: ";
    
            getline(cin, temp);
            for(auto& x: temp){
                x= tolower(x);
            }

            if(temp == "h"){
                cout<<"Use ISO 639-2 standard."<<endl<<"example: en for English and es for Spanish"<<endl<< "for the full list visit: https://www.sitepoint.com/iso-2-letter-language-codes/"<<endl;
            } else if(temp == "d") { 
                break;
            } else {
                targetLanguage = temp; 
                break;
            }
        }

        std::cout << "Recording audio..." << std::endl;
        recordAudio(audioFilePath);

        std::cout << "Encoding audio to Base64..." << std::endl;
        encodeFileToBase64(audioFilePath, base64FilePath);

        std::cout << "Sending audio to Speech-to-Text API..." << std::endl;
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
            std::cerr << "Could not open the file: " << filePath << std::endl;
        }

        translateText(content, sourceLanguage, targetLanguage, translateApiKey);
        //  fstream historyLog("HistoryLog.txt", ios::app);
        //  fstream historyLog("HistoryLog.txt", ios::app);
        historyLog<<"Translating from "<<sourceLanguage<<" into "<<targetLanguage<<endl;
        // historyLog.close();
        // historyLog.close();

        std::ifstream translated("translatedText.txt");
        std::string line;

        if (translated.is_open()) {
            while (std::getline(translated, line)) {
                std::cout << line << std::endl;
            }
            translated.close();
        } else {
            std::cerr << "Unable to open file" << std::endl;
        }

        //  fstream historyLog("HistoryLog.txt", ios::app);
        //  fstream historyLog("HistoryLog.txt", ios::app);

            historyLog<<sourceLanguage<<": "<<content<<endl<<targetLanguage<<": "<<line<<endl;
            // historyLog.close();

        std::cout << "Do you want to keep going?(y/n)" << endl;
        getline(cin, temp);

        if(temp == "n"){
            break;
        }
    }
    // Code for speech-to-text translation
}

void textToSpeechTranslation() {
    const char* str;
    string temp;
    string voiceLanguage;

    while(1){    
        while(1){
            cout<<endl<<"Choose a language to Translate from or type h for help: ";
            getline(cin, temp);

            for(auto& x: temp){
                x= tolower(x);
            }
            
            if(temp == "h"){
                cout<<"Use ISO 639-2 standard."<<endl<<"example: en for English and es for Spanish."<<endl<< "D for defualt"<<endl;
            } else if(temp == "d") { 
                sourceLanguage = "en";
                break;    
            }  else if(isValidLanguageCode(temp)) {
                sourceLanguage = temp;
                break;
            } else {
                std::cout << "Invalid language output. Please use the ISO 639-2 standard."<<endl<<"example: en for English and es for Spanish.";
            }
        }
        

        while(1){
            cout<<"Choose a language to Translate into or type h for help: ";
    
            getline(cin, temp);
            for(auto& x: temp){
                x= tolower(x);
            }

            if(temp == "h"){
                cout<<"Use ISO 639-2 standard."<<endl<<"example: en for English and es for Spanish"<<endl<< "for the full list visit: https://www.sitepoint.com/iso-2-letter-language-codes/"<<endl;
            } else if(temp == "d") { 
                break;
            } else if(isValidLanguageCode(temp)) {
                targetLanguage = temp; 
                break;
            } else {
                std::cout << "Invalid language output. Please use the ISO 639-2 standard."<<endl<<"example: en for English and es for Spanish.";
            }
        }
        
        cout<<"You are currently translating from "<<sourceLanguage<<" into "<<targetLanguage<<endl<<endl;
        temp = "Translating from " + sourceLanguage + " to " + targetLanguage;
        str = temp.c_str();

        cout<<"What do you need me to translate: ";
        getline(cin, temp);
        
        for(auto& x: temp){
            x= tolower(x);
        }
        
        if(temp == "h"){
            temp = "Translating from " + sourceLanguage + " to " + targetLanguage;
            str = temp.c_str();
            cout<<"You are currently translating from "<<sourceLanguage<<" into "<<targetLanguage<<endl<< "To change languages press c or e to exit: ";
            getline(cin, temp);
            if(temp == "c"){
                break;
            } else if(temp == "e") {
                exit(0);
            }
        
        } else {
            textToTranslate = temp;

            translatedText = TranslateText(textToTranslate, sourceLanguage, targetLanguage, translateApiKey);

            voiceLanguage = convertToGoogleVoiceFormat(targetLanguage);

            textToSpeechAPIRequest(translatedText, voiceLanguage);

            std:cout << "Audio content saved will now proceed to resample!" << std::endl;

            std::cout << "Audio file created do you want to play it:(y/n) ";
            getline(cin, temp);

            if(temp == "y"){
                playWAV("textToSpeechOutput.wav");
            }
        }   

        std::cout << "Do you want to keep going?(y/n)" << endl;
        getline(cin, temp);   

        if(temp == "n"){
            break;
        }
    }
}


int runTerminal(){
            std::string filename = "settings.txt"; // Replace with your file's name

             // Open the file
              std::ifstream file(filename);

                // Check if the file is opened successfully
            if (!file.is_open()) {
                std::cerr << "Error opening file: " << filename << std::endl;
             return 1;
           }

           // Read the file contents into a stringstream
              std::stringstream buffer;
             buffer << file.rdbuf();
    
             // Close the file
             file.close();

              // Extract the string from the stringstream
              std::string fileContent = buffer.str();

    

            sourceLanguage = fileContent.substr(0,2);
             targetLanguage = fileContent.substr(2,2);
             string method = fileContent.substr(4,3);




    string methodChoice;
    cout << "Initiating MADevice..." << endl;
    cout << "This is a prototype created by group 22 for CS3307." << endl;
    cout << "Here is how it works:" << endl;
    cout << "1. Choose a translation method" << endl;
    cout << "2. Choose a Language to translate from" << endl;
    cout << "3. Choose a language to translate to" << endl;
    cout << "4. Translate." << endl;  

    cout << endl << "Choose a translation method or type h for help or d for default: ";
    getline(cin, methodChoice);

    for (auto &x : methodChoice) {
        x = tolower(x);
    }

    if(methodChoice == "d"){
        methodChoice = method;
    }

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

    return 0;
}