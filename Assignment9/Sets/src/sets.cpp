//============================================================================
// Name        : sets.cpp
// Author      : Anish Dhage
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <vector>

class Set{
	vector <int> setlist;
public:
	void insert();//
	void remove(int);//
	int search(int );//
	void size();//
	void intersection(Set );
	void unions(Set );
	void difference(Set );
	void subset(Set );
	void display();//
};

void Set::insert(){
	int ele;
	cout<<"\nEnter element to insert into set : ";
	cin>>ele;
	if(search(ele) != -1){
		cout<<"Element already exists !\n";
		return;
	}
	else{
		setlist.push_back(ele);
	}
}

int Set::search(int sele){
	int i = 0;
	vector <int> :: iterator it;
	for(it = setlist.begin(); it != setlist.end() ; it++){
		if(*it == sele){
			return i;
		}
		i++;
	}
	return -1;
}

void Set::display(){
	vector <int> :: iterator it;
	cout<<endl;
	for(it = setlist.begin(); it != setlist.end() ; it++){
		cout<< *it<<"\t";
	}
}

void Set::size(){
	cout<<"Size : "<<setlist.size()<<endl;
}

void Set::remove(int rem){
	int i = search(rem);
	if(i == -1){
		cout<<"\nElement does not exist!";
		return;
	}
	setlist.erase(setlist.begin() + i);
	cout<<"\nDeleted!";
}

void Set::intersection(Set X){
	vector <int> :: iterator it1,it2;
	for(it1 = setlist.begin(); it1 != setlist.end() ; it1++){
		for(it2 = X.setlist.begin(); it2 != X.setlist.end() ; it2++){
			if(*it1 == *it2){
				cout<<*it1<<"\t";
			}
		}
	}
	cout<<endl;
}
void Set::unions(Set X){
	vector <int> unionl = setlist;
	vector <int> :: iterator it1;
	int i;
	for(it1 = X.setlist.begin(); it1 != X.setlist.end() ; it1++){
		i = (int)*it1;
		if(search(i) == -1){
			unionl.push_back(i);
		}
	}

	vector <int> :: iterator it;
	cout<<endl;
	for(it = unionl.begin(); it != unionl.end() ; it++){
		cout<< *it<<"\t";
	}

}

void Set::subset(Set X){
	vector <int> :: iterator it2;
	int i;
	for(it2 = X.setlist.begin(); it2 != X.setlist.end() ; it2++){
		i = (int)*it2;
		if(search(i) == -1){
			cout<<"\nIt is not a subset !";
			return;
		}
	}
	cout<<"\nIt is a subset";
}

void Set::difference(Set X){
	vector <int> unionl = setlist;
	vector <int> union2;
	vector <int> :: iterator it1;
	int i;
	for(it1 = X.setlist.begin(); it1 != X.setlist.end() ; it1++){
		i = (int)*it1;
		if(search(i) != -1){
			remove(i);
		}
	}
	display();
	setlist = unionl;
	return;
}

int main(){
	Set A,B;
	int ch,ch1 = 0;
	while (ch1 != 3){
		cout<<"\n1.Set A\n2.Set B\n3.Exit\n";
		cin>>ch1;
		switch(ch1){

		case 1: ch = 0;
				while (ch != 10){
				cout<<"\n\nEnter your Choice : \n1.Insert\n2.Search\n3.Delete\n4.Size\n5.Display\n6.Subset\n7.Union\n8.Intersection\n9.Difference\n10.Exit\n";
				cin>>ch;
				switch(ch){

				case 1: cin.ignore();
						A.insert();
						break;

				case 2: int sele,exist;
						cout<<"\nEnter Element to be Searched : ";
						cin>>sele;
						exist = A.search(sele);
						if(exist != -1){
							cout<<"\nFound!";
						}
						else{
							cout<<"\nNot Found!";
						}
						break;

				case 3: int rem;
						cout<<"\nEnter element to be removed : ";
						cin>>rem;
						A.remove(rem);
						break;

				case 4: A.size();
						break;

				case 5: A.display();
						break;

				case 6: A.subset(B);
						break;

				case 7:	A.unions(B);
						break;

				case 8:	A.intersection(B);
						break;

				case 9:	A.difference(B);
						break;

				case 10: break;

				default:cout<<"\nTry Again!\n";
						break;
				}
				}
				break;

		case 2: ch = 0;
				while (ch != 10){
				cout<<"\n\nEnter your Choice : \n1.Insert\n2.Search\n3.Delete\n4.Size\n5.Display\n6.Subset\n7.Union\n8.Intersection\n9.Difference\n10.Exit\n";
				cin>>ch;
				switch(ch){

				case 1: cin.ignore();
						B.insert();
						break;

				case 2: int sele,exist;
						cout<<"\nEnter Element to be Searched : ";
						cin>>sele;
						exist = B.search(sele);
						if(exist != -1){
							cout<<"\nFound!";
						}
						else{
							cout<<"\nNot Found!";
						}
						break;

				case 3: int rem;
						cout<<"\nEnter element to be removed : ";
						cin>>rem;
						B.remove(rem);
						break;

				case 4: B.size();
						break;

				case 5: B.display();
						break;

				case 6: B.subset(A);
						break;

				case 7:	B.unions(A);
						break;

				case 8:	B.intersection(A);
						break;

				case 9:	B.difference(A);
						break;

				case 10: break;

				default:cout<<"\nTry Again!\n";
						break;
				}
				}
				break;

		case 3 : break;

		default : cout<<"Try Again!";
				  break;
		}
	}
	return 0;
}
