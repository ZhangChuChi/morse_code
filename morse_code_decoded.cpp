#include <iostream>
#include <string>
#include <map> // For mapping Morse code to letters

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
/*
{".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'},
{"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'},
{"-.-", 'K'}, {".-..", 'L'}, {"--", 'M'}, {"-.", 'N'}, {"---", 'O'},
{".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'},
{"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'}, {"-.--", 'Y'},
{"--..", 'Z'}, {"-----", '0'}, {".----", '1'}, {"..---", '2'},
{"...--", '3'}, {"....-", '4'}, {".....", '5'}, {"-....", '6'},
{"--...", '7'}, {"---..", '8'}, {"----.", '9'}, {".-.-.-", '.'},
{"---...", ':'}, {"--..--", ','}, {"-.-.-.", ';'}, {"..--..", '?'},
{"-...-", '='}, {".----.", '\''}, {"-..-.", '/'}, {"-.-.--", '!'},
{"....", ' '}, {"..--.-", '_'}, {".-..-.", '\"'}, {"-.--.", '('},
{"-.--.-", ')'}, {"...-..-", '$'}, {"....", '&'}, {".--.-.", '@'}
*/

int main() {
	std::string morseCode;
	std::cout << "Enter a coded Morse message (e.g., .- -... -.-.): ";
	std::getline(std::cin, morseCode);
	
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
	
	std::cout << "Decoded message: " << decodedMessage << std::endl;
	return 0;
}

