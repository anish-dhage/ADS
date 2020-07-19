//============================================================================
// Name        : CityGraph.cpp
// Author      : Anish Dhage
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include <queue>
using namespace std;

class CGraph;

class City{
	int name;
	list <int> undir ;
	list <int> dir ;
public:
	friend class CGraph;
	void display_undir(){
		list<int> :: iterator it;
		for(it = undir.begin() ; it!= undir.end() ; it++){
			cout<<*it<<"\t";
		}
	}
	void display_dir(){
		list<int> :: iterator it;
		for(it = dir.begin() ; it!= dir.end() ; it++){
			cout<<*it<<"\t";
		}
	}
};

class CGraph{
	int city_num;
	list <City*> cities;
	int cost[10][10];
public:
	CGraph(){
		city_num = 0;
		for(int i = 0; i<10 ; i++){
				for(int j = 0; j<10 ; j++){
				cost[i][j] = 0;
			}
		}
	}
	City* searchret(int);
	void addcity();
	void delcity();
	void addpath();
	void delpath();
	void display();
	void degree();
	void init();
	void bfs();
};

void CGraph::init(){
	int i,j;
	for(i = 0; i<10 ; i++){
		for(j = 0; j<10 ; j++){
			cost[i][j] = 0;
		}
	}
}

City* CGraph::searchret(int x){
	int i;
	list <City*> cities1 = cities;
	for(i = 0; i<city_num ;i++){
		City *curr = cities1.front();
		if(curr->name == x){
			return curr;
		}
		cities1.pop_front();
	}
	return NULL;
}

void CGraph::display(){
	int i,j;
	list <City*> cities1 = cities;
	for(i = 0; i<city_num ;i++){
		City *curr = cities1.front();
		cout <<"\n\n"<< curr->name;
		cout<<"\nDirected : ";
		curr->display_dir();
		cout<<"\nUndirected : ";
		curr->display_undir();
		cities1.pop_front();
	}
	for(i = 0; i<10 ;i++){
		for(j = 0; j<10 ;j++){
			if(cost[i][j] != 0){
				cout<<"\n"<< i <<"---"<<j<<": "<<cost[i][j]<<endl;
			}
		}
	}
}

void CGraph::addcity(){
	City *new1 = new City;
	cout<<"Enter name of city : ";
	cin>>new1->name;
	cities.push_back(new1);
	city_num ++;
}

void CGraph::delcity(){
	int del;
	cout<<"Enter name of city to remove: ";
	cin>>del;
	City *new1 = searchret(del);
	cities.remove(new1);
	city_num --;

	int i;
	list <City*> cities1 = cities;
	for(i = 0; i<city_num ;i++){
		City *curr = cities1.front();
		curr->undir.remove(del);
		curr->dir.remove(del);
		cities1.pop_front();
	}

	for(i = 0; i<10 ; i++){
		cost[i][del] = 0;
		cost[del][i] = 0;
	}

}

void CGraph::addpath(){
	cout<<"\n1.Undirected\n2.Directed\n";
	int op;
	int cost1;
	cin>>op;
	if(op == 1){
		cout<<"\nWhich Two Cities are supposed to be connected?\n";
		int city1,city2;
		cin>>city1;
		City *city1p = searchret(city1);
		cin>>city2;
		City *city2p = searchret(city2);
		city1p->undir.push_back(city2);
		city2p->undir.push_back(city1);
		cout<<"Input Cost: ";
		cin>>cost1;
		cost[city1][city2] = cost1;
		cost[city2][city1] = cost1;
	}
	else if(op == 2){
		cout<<"\nEnter Start :\n";
		int city1,city2;
		cin>>city1;
		cout<<"\nEnter Destination :\n";
		cin>>city2;
		City *city1p = searchret(city1);
		city1p->dir.push_back(city2);
		cout<<"Input Cost: ";
		cin>>cost1;
		cost[city1][city2] = cost1;
	}
}

void CGraph::delpath(){
	cout<<"\n1.Undirected\n2.Directed\n";
	int op;
	cin>>op;
	if(op == 1){
		cout<<"\nWhich Two Cities are supposed to be disconnected?\n";
		int city1,city2;
		cin>>city1;
		cin>>city2;
		City *city1p = searchret(city1);
		City *city2p = searchret(city2);
		city1p->undir.remove(city2);
		city2p->undir.remove(city1);
		cost[city1][city2] = 0;
		cost[city2][city1] = 0;
	}
	else if(op == 2){
		cout<<"\nEnter Start :\n";
		int city1,city2;
		cin>>city1;
		cout<<"\nEnter Destination :\n";
		cin>>city2;
		City *city1p = searchret(city1);
		city1p->dir.remove(city2);
		cost[city1][city2] = 0;
	}
}

void CGraph::degree(){
	int i;
	list <City*> cities1 = cities;
	for(i = 0; i<city_num ;i++){
		City *curr = cities1.front();
		cout<<"\nDegree of Undirected Graph "<<curr->name<<" : \n";
		cout<<curr->undir.size();
		cout<<"\nDegree of Directed Graph "<<curr->name<<" : \n";
		cout<<curr->dir.size();
		cities1.pop_front();
	}
}

void CGraph::bfs(){
	int flag[10] = {0};
	queue <City*> A;
	City *curr = cities.front();
	City *pt;
	int num;
	A.push(curr);
	flag[curr->name] = 1;
	cout<<"\nUndirected : \n";
	while(!A.empty()){
		curr = A.front();
		cout<<curr->name<<"\t";
		list <int> it = curr->undir;
		while(!it.empty()){
			num = it.front();
			pt = searchret(num);
			if(flag[pt->name] != 1){
				A.push(pt);
				flag[pt->name] = 1;
			}
			it.pop_front();
		}
		A.pop();
	}
	cout<<endl;

	A.push(cities.front());
	for(int i = 0; i<10;i++){
		flag[i] = 0;
	}
	cout<<"\nDirected : \n";
	while(!A.empty()){
		curr = A.front();
		cout<<curr->name<<"\t";
		flag[curr->name] = 1;
		list <int> it = curr->dir;
		while(!it.empty()){
			num = it.front();
			pt = searchret(num);
			if(flag[pt->name] != 1){
				A.push(pt);
			}
			it.pop_front();
		}
		A.pop();
	}


}

int main(){
	CGraph A;
	A.init();
	int ch = 0;
	while (ch != 8){
		cout<<"\n\nEnter your Choice : \n1.Add City\n2.Delete City\n3.Add Path\n4.Delete Path\n5.Display\n6.Degree\n7.BFS Traversal\n8.Exit\n";
		cin>>ch;
		switch(ch){

		case 1: A.addcity();
				break;

		case 2: A.delcity();
				break;

		case 3:	A.addpath();
				break;

		case 4: A.delpath();
				break;

		case 5: A.display();
				break;

		case 6: A.degree();
				break;

		case 7: A.bfs();
				break;

		case 8: break;

		default:cout<<"\nTry Again!\n";
				break;

		}
	}
	return 0;
}
