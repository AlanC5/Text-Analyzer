/*
 * Text Analyzer.cpp
 *
 *  Created on: Sep 26, 2014
 *	Author: Alan Chen
 */


#include <iostream>
#include <vector>
using namespace std;

struct Character {
	char letter;
	int l_count;
};

struct Word {
	string wrd;
	int w_count;
};


void sort (vector<Word>& wom) {
	bool swap;
	do {
		swap = false;
	for (int i = 0, lens = wom.size() - 1; i < lens; ++i) {

		for (int k = 0, sens = wom[i].wrd.length(); k < sens; ++k) {

			if (wom[i+1].wrd[k] < wom[i].wrd[k]) {
				Word temp;
				temp = wom[i];
				wom[i] = wom[i+1];
				wom[i+1] = temp;
				swap = true;
				break;
			}

			if (wom[i+1].wrd[k] > wom[i].wrd[k]) {
				break;
			}
		}
	}
	} while (swap == true);
}

int main () {
	vector<Character>letter_counter(26);
	vector<Word>word_counter;
	string sentence;


	cout << "Greetings, user!" << endl;
	cout << "This is a text analyzer. Please write some text to analyze." << endl;
	cout << "Please note that words must be separated by some kind of whitespace." << endl;
	cout << "When you want to stop inserting text, please press 'q' or 'Q' . \n" << endl;
	
	// places letter in vector incase not every letter is typed
	for (int i = 97; i <= 122; ++i) {
		int place = i - 97;
		letter_counter[place].letter = i;
	}
	while(getline(cin,sentence)) {
		sentence += ' ';
		Word storeword;
		storeword.w_count = 0;
	    //For break
	    int Detectq = 0;
	    //Scans all the letters
		for (int j = 0, len = sentence.length(); j < len; ++j) {

			sentence[j] = tolower(sentence[j]); //Covert all letters to lower-case
			if (sentence[j] == 113 && sentence[j-1] == ' ' && sentence[j+1] == ' ') {
				Detectq = 5;
				break;
				}
			for (int i = 97; i <= 122; ++i) {
				if (sentence[j] == i) {  // stores letters 
					int hold = i - 97;
					letter_counter[hold].l_count += 1;
				}
			}
			if (isalpha(sentence[j])) {
				storeword.wrd += sentence[j];	
			}


			if (sentence[j] == ' ') {
				if (storeword.wrd.length() == 1) {
					storeword.wrd.clear();
					break;
				}
				if (word_counter.size() > 0) {
					for (int i = 0, den = word_counter.size(); i < den; ++i) {
				 
						if (word_counter[i].wrd == storeword.wrd) {
							word_counter[i].w_count += 1;
							storeword.wrd.clear();
							storeword.w_count = 0;
							break;						

						}
						if ((word_counter[i].wrd != storeword.wrd) && (i == den -1) ) {	
							storeword.w_count += 1;
							word_counter.push_back(storeword);
							storeword.wrd.clear();
							storeword.w_count = 0;
						}
					}
				}

				if (word_counter.size() == 0) {  //first word					
					storeword.w_count += 1;
					word_counter.push_back(storeword);
					storeword.wrd.clear();
					storeword.w_count = 0;				
				}
			}
		}
	
	if (Detectq == 5) break;
	}

	cout << endl << "Analysis of text: \n" << endl;
	cout << "Counting characters: \n" << endl;
	for (int i = 0; i < 26; ++i) {
		char capital;
		capital = letter_counter[i].letter - 32;
		cout << letter_counter[i].letter << " or " << capital << " appears exactly " << letter_counter[i].l_count << " times." << endl;
	}
	sort(word_counter);
	cout << endl << "Counting words (appearing in alphabetical order): \n" << endl;
	for (int i = 0, len = word_counter.size(); i < len; ++i) {
		
		cout << word_counter[i].wrd << " appears " << word_counter[i].w_count << " times." << endl;
		
	}

	return 0;
}
