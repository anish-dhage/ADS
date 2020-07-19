//============================================================================
// Name        : Prims.cpp
// Author      : Anish Dhage
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include <queue>
using namespace std;

class OGraph;

class City{
	int name;
	list <int> undir ;
public:
	friend class OGraph;
	void display_undir(){
		list<int> :: iterator it;
		for(it = undir.begin() ; it!= undir.end() ; it++){
			cout<<*it<<"\t";
		}
	}
};

class OGraph{
	int city_num;
	list <City*> cities;
	int cost[10][10];
public:
	OGraph(){
		city_num = 0;
	}
	City* searchret(int);
	void addcity();
	void delcity();
	void addpath();
	void delpath();
	void init();
	void display();
	void prims();
};

void OGraph::init(){
	int i,j;
	for(i = 0; i<10 ; i++){
		for(j = 0; j<10 ; j++){
			cost[i][j] = 1000;
		}
	}
}

City* OGraph::searchret(int x){
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

void OGraph::display(){
	int i,j;
	list <City*> cities1 = cities;
	for(i = 0; i<city_num ;i++){
		City *curr = cities1.front();
		cout <<"\n\n"<< curr->name;
		cout<<"\nUndirected : ";
		curr->display_undir();
		cities1.pop_front();
	}
	for(i = 0; i<10 ;i++){
		for(j = 0; j<10 ;j++){
			if(cost[i][j] != 1000){
				cout<<"\n"<< i <<"---"<<j<<": "<<cost[i][j]<<endl;
			}
		}
	}
}

void OGraph::addcity(){
	City *new1 = new City;
	cout<<"Enter name of city : ";
	cin>>new1->name;
	cities.push_back(new1);
	city_num ++;
}

void OGraph::delcity(){
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
		cities1.pop_front();
	}

	for(i = 0; i<10 ; i++){
		cost[i][del] = 0;
		cost[del][i] = 0;
	}

}

void OGraph::addpath(){
	int cost1;

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

void OGraph::delpath(){

		cout<<"\nWhich Two Cities are supposed to be disconnected?\n";
		int city1,city2;
		cin>>city1;
		cin>>city2;
		City *city1p = searchret(city1);
		City *city2p = searchret(city2);
		city1p->undir.remove(city2);
		city2p->undir.remove(city1);
		cost[city1][city2] = 1000;
		cost[city2][city1] = 1000;

}

void OGraph::prims(){
	int visited[10] = {0};
	int set[10] = {0};
	int from[10] = {0};
	int to[10] = {0};
	int mincost = 0;
	int min;
	int j,m;
	City *curr = cities.front();
	int i = curr->name;
	int edges = 0;
	set[edges] = i;
	visited[i] = 1;
	while(edges < city_num-1){
		int k,l;
		min = 1000;
		for(k=0; k<=edges ;k++){
			for(l=0 ; l<=city_num ; l++){
				if(cost[set[k]][l] < min){
					if(visited[l] != 1){
						min = cost[set[k]][l];
						j = l;
						m = set[k];
					}
				}
			}
		}
		from[edges] = m;
		to[edges] = j;
		edges++;
		set[edges] = j;
		visited[j] = 1;

		if(min != 1000){
			mincost += min;
		}
	}
	cout<<"\nMincost = "<<mincost<<endl;
	for(i = 0; i<edges ; i++){
		cout<<from[i]<<"---"<<to[i]<<"\n";
	}
	cout<<endl;
}


int main(){
	OGraph A;
	A.init();
	int ch = 0;
	while (ch != 7){
		cout<<"\n\nEnter your Choice : \n1.Add City\n2.Delete City\n3.Add Path\n4.Delete Path\n5.Display\n6.Prims\n7.Exit\n";
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

		case 6: A.prims();
				break;

		case 7: break;

		default:cout<<"\nTry Again!\n";
				break;

		}
	}
	return 0;
}
