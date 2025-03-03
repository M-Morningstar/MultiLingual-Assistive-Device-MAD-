#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <filesystem> // Include the filesystem library for path manipulation

#include "displayMain.h"
#include "terminalDemo.h"

using namespace std;
namespace fs = std::filesystem;


int main() {
    std::cout << "Program has started" << std::endl;
    string temp;
   
    while(1){
        cout<<endl<<"Enter 1 for Display LED, 2 for terminal(demo), 3 for settings, 4 to view history: ";

        getline(cin, temp);
        
        for(auto& x: temp){
            x= tolower(x);
        }
        
        if(!temp.compare("1")){
            cout<<"Display LED mode activated\n";
            // Call Display LED class
            runDisplay();
        } else if(!temp.compare("2")) { 
            std::cout<<"Terminal based demo mode activated\n";
            // Call terminal demo mode
            runTerminal();
        } else if(!temp.compare("3")) { 
            std::cout<<"Settings: \n";
            cout<<endl<<"Enter 1 to View and 2 to change settings: ";

            getline(cin, temp);
        
             for(auto& x: temp){
               x= tolower(x);
              }


            if(!temp.compare("1")){
                std::string filename = "settings.txt";

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

            // Output the file contents
           std::cout << "Defult Language to translate from: " << fileContent.substr(0,2)<<std::endl;
              std::cout << "Defult Language to translate To: " << fileContent.substr(2,2)<<std::endl;
           std::cout << "Defult Translating method: " << fileContent.substr(4,3)<<std::endl;


            } else if(!temp.compare("2")){

                std::ofstream outFile("Settings.txt");

              // Check if the file is opened successfully
              if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
            return 1;
           }

          // Prompt the user to enter the string in three stages
          std::string stage1, stage2, stage3;
         std::cout << "Enter two characters for stage 1: ";
         std::cin >> stage1;
          std::cout << "Enter two characters for stage 2: ";
          std::cin >> stage2;
          std::cout << "Enter two characters for stage 3: ";
          std::cin >> stage3;

           // Concatenate the input from all stages
               std::string userInput = stage1 + stage2 + stage3;

           // Write the user input to the file
           outFile << userInput;

              // Close the file
             outFile.close();
                 std::cout << "Settings have been updated successfully!" << std::endl;

 
            }else{
              cout<<endl<<"Invalid input"<<endl;
            }
            
        }  else if(!temp.compare("4")) { 
            std::cout<<"History: \n";
             std::string filename = "HistoryLog.txt"; // Path to the file, assuming it is one directory higher

             // Get the absolute path of the file
              fs::path filePath = fs::canonical(filename);

              // Open the file
             std::ifstream file(filePath);

           // Check if the file is opened successfully
          if (!file.is_open()) {
              std::cerr << "Error opening file: " << filename << std::endl;
               return 1;
          }

           // Read and print each line of the file
           std::string line;
    
            while (std::getline(file, line)) {
             std::cout << line << std::endl;
            }

             // Close the file
             file.close();
            
        }  else {
            std::cerr<<"Invalid input please ask again!\n"; 
        }
    }

    std::cout << "Program is exiting." << std::endl;
    return 0;
}