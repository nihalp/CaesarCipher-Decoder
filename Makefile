
all:
	g++ -Wall -o caesarcipher caesarcipher.cpp
	g++ -Wall -o vigeneredecoder vigeneredecoder.cpp

caesarcipher:
	g++ -Wall -o caesarcipher caesarcipher.cpp
vigenere:
	g++ -Wall -o vigeneredecoder vigeneredecoder.cpp


clean:
	rm caesarcipher vigeneredecoder