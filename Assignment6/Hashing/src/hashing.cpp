//============================================================================
// Name        : hashing.cpp
// Author      : Anish Dhage
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

class Hashing;

class Dict{
	string key;
	string meaning;
public:
	Dict(){
		key = " ";
		meaning = " ";
	}

	friend class Hashing;
};

class Hashing{
	vector <Dict *> hashtable {26,NULL};
public:

	void search();
	void insert();
	void deletekey();
};

void Hashing::insert(){
	Dict *new1 = new Dict;
	cout<<"\nEnter the key : ";
	getline(cin,new1->key);
	cout<<"\nEnter the meaning : ";
	getline(cin,new1->meaning);

	int index;
	index = new1->key[0] % 26;

	if(hashtable[index] == NULL){
		hashtable[index] = new1;
	}

	else if(hashtable[index]->key[0] % 26 == index){
		int i = 0;
		while(hashtable[i] != NULL){
			if(i == 25){
				cout<<"\nOverflow!\n";
				return;
			}
			i++;
		}
		hashtable[i] = new1;
	}

	else{
	int i = 0;
	Dict *curr = hashtable[index];
	hashtable[index] = new1;
		while(hashtable[i] != NULL){
			i++;
		}
	hashtable[i] = curr;
	}
}

void Hashing::search(){
	cout<<"Enter the key to be searched : ";
	string skey;
	getline(cin,skey);
	int index = skey[0]%26;
	if(hashtable[index]->key == skey){
		cout<<"Meaning is : "<<hashtable[index]->meaning<<endl;
		cout<<"Index is "<<index<<endl;
	}

	else{
		int i = 0;
		while(hashtable[i]->key != skey){
			if(i==25){
				cout<<"\nNot Found!\n";
				return;
			}
			i++;
		}
		cout<<"Meaning is : "<<hashtable[i]->meaning<<endl;
		cout<<"Index is "<<i<<endl;
	}

}

void Hashing::deletekey(){
	cout<<"Enter the key to be deleted : ";
	string dkey;
	getline(cin,dkey);
	int index = dkey[0]%26;
	if(hashtable[index]->key == dkey){

		hashtable[index] = NULL;
		cout<<"\nDeleted!\n";
	}
	else{
		int i = 0;
		while(hashtable[i]->key != dkey){
			if(i==25){
				cout<<"\nNot Found!\n";
				return;
			}
			i++;
		}
		cout<<"\nDeleted!\n";
		hashtable[index] = NULL;
	}
}

int main(){
	Hashing A;
	int ch = 0;
	while (ch != 4){
		cout<<"\n\nEnter your Choice : \n1.Insert\n2.Search\n3.Delete\n4.Exit\n";
		cin>>ch;
		switch(ch){

		case 1: cin.ignore();
				A.insert();
				break;

		case 2: cin.ignore();
				A.search();
				break;

		case 3:	cin.ignore();
				A.deletekey();
				break;

		case 4: break;

		default:cout<<"\nTry Again!\n";
				break;
		}
	}
	return 0;
}
