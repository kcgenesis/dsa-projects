#include "hash.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <locale>
using namespace std;


//uses an ascii range to denote valid characters
vector<string> &split(const string &s, vector<int*> &range, vector<string> &elems) {
	string r = s;
	char delim = ' ';
	int* ptr;
	bool valid;
	for(int i=0;i<r.size();i++){
		valid = true;
		for(int j=0;j<range.size();j++){
			ptr = range[j];
			if ((ptr[0] <= (int)r[i])&&((int)r[i] <= ptr[1])) {
				valid = true;
				break;
			}
			else{
				valid = false;
			}
		}
		if (!valid) {
			r[i] = delim;
		}
	}
	stringstream ss(r);
	string item;
	while (getline(ss, item, delim)) {
		if(item.size()!=0){
			elems.push_back(item);
		}
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
		vector<int*> valid;
		
		//valid ascii ranges
		int range[5][2];
		range[0][0] = 'A';
		range[0][1] = 'Z';
		valid.push_back(range[0]);
		range[1][0] = 'a';
		range[1][1] = 'z';
		valid.push_back(range[1]);
		range[2][0] = '0';
		range[2][1] = '9';
		valid.push_back(range[2]);
		range[3][0] = '-';
		range[3][1] = '-';
		valid.push_back(range[3]);
		range[4][0] = '\'';
		range[4][1] = '\'';
		valid.push_back(range[4]);

		string line;
		int n = 1;
		while(getline(file2,line)){
			words = split(line,valid,words);
			for(int i=0;i<words.size();i++){
				for(int j=0;j<words[i].size();j++){
						if(('A'<=words[i][j])&&(words[i][j]<='Z')){
							words[i][j] = words[i][j] + ('a' - 'A');
						}
				}
				if(words[i].size()>20){
					file3<<"Long word at line "<< n <<", ";
					file3<<"starts: "<<words[i].substr(0,20)<<endl;
				}
				else{
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


