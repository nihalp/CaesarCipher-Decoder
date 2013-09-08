
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <cmath>
using namespace std;

int main(int argc, char const *argv[])
{
	ifstream file;
	if (argc <= 1) {
		cout << "Specify a file to decode" << endl;
		return 0;
	} else {
		file.open(argv[1]);	
	}

	// check if file is open
	if (file.is_open()) {
		// read file into string
		stringstream buffer;
		buffer << file.rdbuf();
		string message(buffer.str());

		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				for (int m = 0; m < 26; m++) {
					for (int n = 0; n < 26; n++) {
						string key = "AAAA";
						key[0] = (char)(n+'A');
						key[1] = (char)(m+'A');
						key[2] = (char)(j+'A');
						key[3] = (char)(i+'A');
						
						string decoded_string = "";
						int count = 0;
						for (unsigned int x = 0; x < message.length(); x++) {
							if (message[x] >= 'A' && message[x] <= 'Z') {
								int shift = key[(count%4)] - 'A';
								count++;
								char shifted = message[x] - shift;
								if (shifted < 'A') {
									shifted = 'Z' - ('A' - shifted - 1);
								}
								decoded_string += shifted;
							} else {
								decoded_string += message[x];
							}
						}

						if (decoded_string.find("BLITZKRIEG") != string::npos) {
							cout << endl << "DECODED STRING WITH KEY: " << key << endl << "=============================" << endl << decoded_string << endl;
							return 0;
						}
					}			
				}		
			}			
		}
		cout << "Can't decode" << endl;
	}

	return 0;
}