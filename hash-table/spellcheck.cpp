#include "hash.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <locale>
using namespace std;


//fix delimiter
vector<string> &split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
	    elems.push_back(item);
	}
	return elems;
}

int main(){
	hashTable d;
	ifstream file1;
	clock_t t = clock();
	file1.open("wordlist_small.txt");
	if (file1.is_open()){
		string word;
		while(getline(file1,word)){
			d.insert(word);
		}
		file1.close();
	}
	else cout << "unable to open file1"<<endl;
	t = clock() -t;
	cout<<"Total time (in seconds) to load dictionary: "<< ((float)t)/CLOCKS_PER_SEC <<endl;
	
	ifstream file2;
	ofstream file3;
	file2.open("lyrics.txt");
	file3.open("output.txt");
	t = clock();
	if(file2.is_open()&&file3.is_open()){
		vector<string> words;
		//locale loc;
		string line;
		int n = 1;
		while(getline(file2,line)){
			words = split(line,' ',words);
			for(int i=0;i<words.size();i++){
				if(words[i].size()>20){
					file3<<"Long word at line "<< n <<", ";
					file3<<"starts: "<<words[i].substr(0,20)<<endl;
				}
				else{
					for(int j=0;j<words[i].size();j++){
						//words[i][j] = tolower(words[i][j],loc);
						words[i][j] = tolower(words[i][j]);
					}
					if(!d.contains(words[i])){
						file3<<"Unknown word at line "<< n <<": ";
						file3<< words[i] <<endl;
					}
				}
				
			}
			n++;
			words.erase(words.begin(), words.end());
		}
		file2.close();
		file3.close();
	}	
	else cout << "unable to open file2"<<endl;
	t = clock() -t;
	cout<<"Total time (in seconds) to check document: "<< ((float)t)/CLOCKS_PER_SEC <<endl;
	return 0;
}


