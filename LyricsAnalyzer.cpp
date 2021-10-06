// FileReader.cpp : Defines the entry point for the console application.
/* 
Input: a txt file with lyrics
output: frequency of each word inside text

1. Read file
2. put each word in array
3. count words
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

bool canReadFile(const ifstream& inputFile) {
	if(!inputFile){
		cerr<<"The file could not be opened.\n";
		return false;	
	}
	else{
		cout<<"The file has been loaded successfully.\n";
		return true;
	}
}

bool isLetter(char* c){
	return ( (*c>='A' && *c <= 'Z') || (*c >='a' && *c <= 'z') );
}

bool wordExistsInArray(const int& SIZE, string words[], string& readWordFromFile){
	bool wordExists = false;
	for (int i = 0; i< SIZE; i++){
		if (words[i] == readWordFromFile) wordExists = true;
	}
	return wordExists;
}

int positionOfExistingItem(const int& SIZE, string words[], string& readWordFromFile){
	for (int i = 0; i< SIZE; i++){
		if (words[i] == readWordFromFile) return i;
	}
}

void printResults(const int& SIZE, string words[], double frequency[], double& wordCounter){
	string readWordFromFile;
	float ratio;
	for(int i=0; i<SIZE; i++){
		readWordFromFile = words[i];
		if(i>0 && i%3 ==0)
			cout <<endl;
		cout << setw(16) << setiosflags(ios::right) << readWordFromFile.c_str() << ": " << setw(2) << (frequency[i]/wordCounter)*100 << "%";
	}
	cout << endl;
}

string decapitalize(string& word){
	//decapitalizes the first letter the word.
	if(word[0] >= 'A' && word[0] <= 'Z') word[0] = tolower(word[0]);
	return word;
}

string reduceWord(string& word){
//Ommits everything but the letters. Usually the ,-. etc. are at start and in the end of the word, so we search first and last position.
	if(!isLetter(&word.front())){
		while(!isLetter(&word.front()))
			word.erase(0,1);
	}
	if (!isLetter(&word.back())){
		while(!isLetter(&word.back()))
			word.erase(word.length()-1,1);
	}
	return word;
}

void countWordFrequencies(ifstream& inputFile){
	const int SIZE = 1000;
	string readWordFromFile, words[SIZE];
	int n = 0;
	double frequency[SIZE]={0.0}, wordCounter = 0.0;
	while(inputFile >> readWordFromFile){
		readWordFromFile = reduceWord(readWordFromFile);
		readWordFromFile = decapitalize(readWordFromFile);
		if(readWordFromFile.length() == 0) 
			continue;
		if (wordExistsInArray(SIZE, words, readWordFromFile))
			frequency[positionOfExistingItem(SIZE, words, readWordFromFile)]++;
		else{
			words[n] = readWordFromFile;
			wordCounter++;
			frequency[n++]++;
		}
	}

	printResults(SIZE, words, frequency, wordCounter);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inputFile("C:\\Users\\Gaming\\Documents\\Visual Studio 2010\\Projects\\fileReader\\midnightSky.txt");
	if (canReadFile(inputFile)) countWordFrequencies(inputFile);
	return 0;
}

