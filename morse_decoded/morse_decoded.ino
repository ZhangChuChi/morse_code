#include <iostream>
#include <cstring>
#include <string>
#include <map>
string decoded;
int key = 7;
int k,error_flag = 0,flag = 0;
//int start_time;
int up_time,down_time = 0,now_time = 0;
int duration = 0;
string morse_code[100] = {};//to recode the morse code,0 = ".",1 = "-",2 = ","
int count = 0;

std::map<std::string, char> morseToLetter = {
    {".-", 65}, {"-...", 66}, {"-.-.", 67}, {"-..", 68}, {".", 69},
    {"..-.", 70}, {"--.", 71}, {"....", 72}, {"..", 73}, {".---", 74},
    {"-.-", 75}, {".-..", 76}, {"--", 77}, {"-.", 78}, {"---", 79},
    {".--.", 80}, {"--.-", 81}, {".-.", 82}, {"...", 83}, {"-", 84},
    {"..-", 85}, {"...-", 86}, {".--", 87}, {"-..-", 88}, {"-.--", 89},
    {"--..", 90}, {"-----", 48}, {".----", 49}, {"..---", 50},
    {"...--", 51}, {"....-", 52}, {".....", 53}, {"-....", 54},
    {"--...", 55}, {"---..", 56}, {"----.", 57}, {".-.-.-", 46},
    {"---...", 58}, {"--..--", 44}, {"-.-.-.", 59}, {"..--..", 63},
    {"-...-", 61}, {".----.", 39}, {"-..-.", 47}, {"-.-.--", 33},
    {"....", 32}, {"..--.-", 95}, {".-..-.", 34}, {"-.--.", 40},
    {"-.--.-", 41}, {"...-..-", 36}, {"....", 38}, {".--.-.", 64}
};

string morse_decode(string morseCode){
    std::string morseCode;

    // std::cout << "Enter a coded Morse message (e.g., .- -... -.-.): ";
    // std::getline(std::cin, morseCode);
    
    std::string decodedMessage;
    std::string currentSymbol;
    for (char c : morseCode) {
      if (c == ',' || c == '/') {
        // A space or slash indicates the end of a Morse symbol
        if (!currentSymbol.empty()) {
          // Look up the Morse symbol in the map
          auto it = morseToLetter.find(currentSymbol);
          if (it != morseToLetter.end()) {
            // Convert to uppercase before adding to the decoded message
            decodedMessage += it->second;
          } else {
            // Handle unknown Morse symbols (optional)
            decodedMessage += "?";
          }
          currentSymbol.clear();
        }
      } else {
        currentSymbol += c;
      }
    }
      
    // Add the last Morse symbol (if any)
    if (!currentSymbol.empty()) {
      auto it = morseToLetter.find(currentSymbol);
      if (it != morseToLetter.end()) {
        decodedMessage += it->second;
      } else {
        decodedMessage += '?';
      }
    }
    
    // std::cout << "Decoded message: " << decodedMessage << std::endl;
    
    return decodedMessage;
}



void setup() {
  Serial.begin(9600);
//  start_time = millis();
  Serial.print("You need to test whether the button is running correctly,please press the button 1 time.");
  
  while(k == LOW){
      k = digitalRead(key);
      now_time = millis();
      
//      if(now_time-up_time > 10000 || n){//error test
//          error_flag++;
//      }
  }
  if(error_flag != 1){
    up_time = millis();
    while(k == HIGH){
        k = digitalRead(key);
    }
    down_time = millis();
    
//    pause = up_time;
    duration = down_time-up_time;
    Serial.print("\n");
    Serial.print("Start:");
  }
}
 
void loop() {
    if(morse_code[count-1] == 2 && morse_code[count-2] == 2){//do the translate
        Serial.print("\n");
        Serial.print("Translate:");
        decoded = morse_decode(morse_code);
        Serial.print(decoded);
    }else if(error_flag == 1){//something error
        Serial.print("Something are erroring,please check the hardware and the program.");
    }else{
      while(k == LOW){//test time
         k = digitalRead(key);
//         Serial.print(k);
      }
      up_time = millis();
      while(k == HIGH){
          k = digitalRead(key);
//          Serial.print(k);
      }
      down_time = millis();
//      Serial.print("\n");
//      pause = up_time;
      duration = down_time-up_time;
//      Serial.print("up_time");
      
      if(duration <= 300 && duration > 0){//<=300ms is a "."
          morse_code[++count] = ".";
          Serial.print(".");
      }else if(duration <= 800 && duration > 300){//<=1800ms is a "-"
          morse_code[++count] = "-";
          Serial.print("-");
      }else if(duration > 800){
          morse_code[++count] = ",";
          Serial.print(",");
      }else{
          Serial.print("error!");
//          error_flag++;//stop program
      }
//      Serial.print("\n");
    }
}
