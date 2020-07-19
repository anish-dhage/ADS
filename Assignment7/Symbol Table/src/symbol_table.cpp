//============================================================================
// Name        : symbol_table.cpp
// Author      : Anish Dhage
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Symbol_Table{
	string symbol[26];
	string meaning[26];
	bool correct[26];
	int chain[26];

public:
	void init();
	void insert();
	int get_key(int);
	void del_ele();
	void search();
	void display();
	void modify();
};

void Symbol_Table::init(){
	for(int i=0 ; i<26 ; i++){
		symbol[i] = " ";
		correct[i] = 0;
		chain[i] = -1;
	}
}

void Symbol_Table::insert(){
	string input;
	string value;
	cout<<"\nEnter String to Insert : \n";
	getline(cin,input);
	cout<<"\nEnter Meaning : \n";
	getline(cin,value);

	int i = get_key(input[0]);
	if(i == -1){
		cout<<"\nTable Full! Not Inserted\n";
		return;
	}

	symbol[i] = input;
	meaning[i] = value;
}

int Symbol_Table::get_key(int ch){
	cout<<"\n1.With Replacement\n2.Without Replacement\n";
	int op;
	cin>>op;
	int index = ch % 26;
	if(op == 1){
		if(symbol[index] == " "){
			correct[index] = 1;
			return index;
		}
		else if(symbol[index][0] % 26 == index){
			int i = 0;
			while(chain[index] != -1){
				index = chain[index];
			}
			while(symbol[i] != " " ){
				if(i == 26){
					return -1;
				}
				i++;
			}
			chain[index] = i;
			return i;
		}

		else{
			int  i = 0;
			while(chain[i] != index){
				i++;
			}
			correct[index] = 1;
			int j = 0;
			string key = symbol[index];
			string value = meaning [index];

			while(symbol[j] != " " ){
				if(j == 26){
					return -1;
				}
				j++;
			}
			symbol[j] = key;
			meaning [j] = value;
			chain[i] = j;

			return index;
		}
	}

	else{
		if(symbol[index] == " "){
			correct[index] = 1;
			return index;
		}
		else{
			while(chain[index] != -1){
				index = chain[index];
			}
			int i = 0;
			while(symbol[i] != " " ){
				if(i == 26){
					return -1;
				}
				i++;
			}
			chain[index] = i;
			return i;
		}
	}
	return -1;
}

void Symbol_Table::display(){
	for(int i = 0;i<26 ;i++){
		cout<<i<<"\t"<<symbol[i]<<"\t"<<meaning[i]<<"\t"<<chain[i]<<"\n";
	}
}

void Symbol_Table::search(){
	string input;
	cout<<"\nEnter String to Search : \n";
	getline(cin,input);
	int index = input[0]%26;
	if(symbol[index] == input){
		cout<<"\nFound!\nMeaning : "<<meaning[index];
		return;
	}
	else{
		while(chain[index] != -1){
			index = chain[index];
            if(symbol[index] == input){
            	cout<<"\nFound!\nMeaning : "<<meaning[index];
           		return;
		    }
		}
	}

	cout<<"\nNot Found!\n";
}

int main(){
	Symbol_Table A;
	A.init();
	int ch = 0;
	while (ch != 6){
		cout<<"\n\nEnter your Choice : \n1.Insert\n2.Search\n3.Delete\n4.Modify\n5.Display\n6.Exit\n";
		cin>>ch;
		switch(ch){

		case 1: cin.ignore();
				A.insert();
				break;

		case 2: cin.ignore();
				A.search();
				break;

		case 3:	cin.ignore();
			//	A.del_ele();
				break;

		case 4: cin.ignore();
			//	A.modify();
				break;

		case 5: A.display();
				break;

		case 6: break;

		default:cout<<"\nTry Again!\n";
				break;
		}
	}
	return 0;
}
