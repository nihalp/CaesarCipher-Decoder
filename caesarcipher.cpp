
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <cmath>
using namespace std;

static float default_freq[26] = {
	.080,
	.015,
	.030,
	.040,
	.130,
	.020,
	.015,
	.060,
	.065,
	.005,
	.005,
	.035,
	.030,
	.070,
	.080,
	.020,
	.002,
	.065,
	.060,
	.090,
	.030,
	.010,
	.015,
	.005,
	.020,
	.002
};

struct sort_pair {
	    bool operator()(const pair<int,float> &left, const pair<int,float> &right) {
	        return left.second > right.second;
	    }
	};

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
		cout << message << endl;

		vector<float> char_freq(26, 0.0);
		vector< pair<int, float> > analysis(26, make_pair(0, 0));
		int totalchars = 0;

		//cout << line << endl;
		for (unsigned int i = 0; i < message.length(); i++) {
			char c = message[i];
			if (c >= 'A' && c <= 'Z') {
				totalchars++;
				char_freq[c-'A'] += 1;
			}
		}
		cout << endl << "=====================" << endl;
		cout << "CHARACTER FREQUENCIES" << endl;
		cout << "=====================" << endl << endl;
		for (int i = 0; i < 26; i++) {
			char_freq[i] /= totalchars;
			cout << (char) (i+'A') << ": " << char_freq[i] << endl;
		}

		cout << endl << "=========================" << endl;
		cout << "PHI(i) FOR SHIFT LENGTH i" << endl;
		cout << "=========================" << endl << endl;

		for (int i = 0; i < 26; i++) {
			analysis[i].first = i;
			for (int j = 0; j < 26; j++) {
				analysis[i].second += char_freq[j] * default_freq[(26 + j - i) % 26];
			}
			cout << "i=" << i << ": " << analysis[i].second << endl;
		}

		sort(analysis.begin(), analysis.end(), sort_pair());

		cout << endl << "=================================" << endl;
		cout << "TOP 5 MOST PROBABLE SHIFT LENGTHS" << endl;
		cout << "=================================" << endl << endl;
		for (int i = 0; i < 5; i++) {
			cout << "i=" << analysis[i].first << ": " << analysis[i].second << endl;
		}

		for (int i = 0; i < 5; i++) {
			cout << endl << "==============================" << endl;
			cout << "DECODE USING SHIFT LENGTH i=" << analysis[i].first << endl;
			cout << "==============================" << endl << endl;

			for (unsigned int j = 0; j < message.length(); j++) {
				char c = message[j];
				if (c >= 'A' && c <= 'Z') {
					char shifted = c - analysis[i].first;
					if (shifted < 'A') {
						shifted = 'Z' - ('A' - shifted - 1);
					}
					cout << shifted;
				} else {
					cout << c;
				}
			}
			cout << endl;
		}
	}

	return 0;
}