//============================================================================
// Name        : Trees.cpp
// Author      : Anish Dhage
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Tree;

class Node{
	int data;
	Node *right;
	Node *left;

public:
	Node(){
		data = 0;
		left = NULL;
		right = NULL;
	}

	friend class Tree;
};

class Tree{
	Node *root;
	char op;
	int hgh;
	int tot_ele;

public:
	Tree(){
		op = 'L';
		root = NULL;
		hgh = 0;
		tot_ele = 0;
	}

	Node* retroot(){
		return root;
	}

	void insert(){
		tot_ele++;
		Node *new1 = new Node;
		cout<<"\nEnter Data of Node : ";
		cin>>new1->data;
		cout<<endl;

		if(root == NULL){
			root = new1;
		}

		else{
			Node *curr = root;
			start:
			cout<<"\nWhere do you want to insert the Node (L/R) : ";
			cin>>op;
			cout<<endl;

			if(op == 'L' || op =='l'){
				if(curr->left == NULL){
					curr->left = new1;
				}
				else{
					curr = curr->left;
					cout<<"Node is not Empty, choose left or right for this Node\n";
					goto start;
				}
			}

			else if(op == 'R' || op =='r'){
				if(curr->right == NULL){
						curr->right = new1;
				}
				else{
					curr = curr->right;
					cout<<"Node is not Empty, choose left or right of this Node\n";
					goto start;
				}
			}

			else{
				cout<<"\nTry again!\n";
				goto start;
			}
		}


	}

	void display(){
		if (root == NULL){
			cout<<"\nQueue is Empty!\n";
			return;
		}

		queue <Node*> disq;
		Node *curr ;
		cout<<endl;

		disq.push(root);

		while(!disq.empty()){
			curr = disq.front();

			cout<<curr->data<<"\t";

			if(curr->left != NULL){
				disq.push(curr->left);
			}
			if(curr->right != NULL){
				disq.push(curr->right);
			}
			disq.pop();

		}
		cout<<endl;
		hgh = height(root,0);
		cout<<"\nHeight is : "<<hgh<<"\n" ;
		count_leaves();
		cout<<endl;
	}

	void count_leaves(){
		int leaves = 0;
		int int_nodes = 0;
		queue <Node*> disq;
		Node *curr ;
		cout<<endl;

		disq.push(root);

		while(!disq.empty()){
			curr = disq.front();

			if(curr->left != NULL){
				disq.push(curr->left);
			}
			if(curr->right != NULL){
				disq.push(curr->right);
			}
			if(curr->right == NULL && curr->left == NULL){
				leaves++;
			}
			disq.pop();
		}

		int_nodes = tot_ele - leaves;
		cout<<"No of Leaves are : "<<leaves;
		cout<<"\nNo of intermediate nodes are : "<<int_nodes;
		cout<<endl;
	}


	int height(Node *rt, int h){
		Node *rsub;
		Node *lsub;
		int rh ;
		int lh ;
		if(rt->left == NULL && rt->right == NULL){
			return h;
		}
		if(rt->left != NULL){
			lsub = rt->left;
			lh = height(lsub, h+1);
			if(rt->right == NULL){
				return lh;
			}
		}
		if(rt->right != NULL){
			rsub = rt->right;
			rh = height(rsub, h+1);
			if(rt->left == NULL){
				return rh;
			}
		}

		if(lh > rh){
			return lh;
		}
		else{
			return rh;
		}
	}

	void recur_inorder(Node* curr){
		if(curr->left!= NULL){
			recur_inorder(curr->left);
		}
		cout<<curr->data<<"\t";
		if(curr->right!= NULL){
			recur_inorder(curr->right);
		}
	}

	void inorder_traversal(){
		if(root == NULL){
			cout<<"\nTree is empty!\n";
		}
		stack <Node*> inorder;
		Node *curr = root;

		do{
			while(curr!= NULL){
				inorder.push(curr);
				curr = curr->left;
			}

			curr = inorder.top();
			inorder.pop();

			while(curr!= NULL){
				cout<<curr->data<<"\t";
				if (curr->right!=NULL){
					curr = curr->right;
					break;
				}
				curr = inorder.top();
				inorder.pop();

			}
		}while(!inorder.empty());
		cout<<endl;
	}

	void recur_preorder(Node* curr){
		cout<<curr->data<<"\t";
		if(curr->left!= NULL){
			recur_preorder(curr->left);
		}
		if(curr->right!= NULL){
			recur_preorder(curr->right);
		}
	}

	void preorder_traversal(){
		if(root == NULL){
			cout<<"\nTree is Empty!\n";
		}
		stack <Node*> predis;
		Node* curr;
		predis.push(root);

		while(!predis.empty()){
			curr = predis.top();
			cout<<curr->data<<"\t";
			predis.pop();
			if(curr->right != NULL){
				predis.push(curr->right);
			}
			if(curr->left != NULL){
				predis.push(curr->left);
			}
		}
		cout<<endl;
	}

	void recur_postorder(Node* curr){
		if(curr->left!= NULL){
			recur_postorder(curr->left);
		}
		if(curr->right!= NULL){
			recur_postorder(curr->right);
		}
		cout<<curr->data<<"\t";
	}

	void postorder_traversal(){
		if(root == NULL){
			cout<<"\nTree is Empty!\n";
		}
		stack <Node*> postone;
		stack <Node*> posttwo;
		Node* curr;
		postone.push(root);

		while(!postone.empty()){
			curr = postone.top();
			postone.pop();
			if(curr->left != NULL){
				postone.push(curr->left);
			}
			if(curr->right != NULL){
				postone.push(curr->right);
			}
			posttwo.push(curr);
		}

		while(!posttwo.empty()){
			curr = posttwo.top();
			cout<<curr->data<<"\t";
			posttwo.pop();
		}
		cout<<endl;
	}

	void mirror_tree(Tree t){
		Node* new1 = new Node;
		new1->data = t.root->data;
		root = new1;
		queue <Node*> q1,q2;
		q1.push(t.root);
        q2.push(root);
        Node *copy,*org;

        while(!q1.empty())
        {
           Node *n1 = new Node;
           Node *n2 = new Node;
           org = q1.front();
           q1.pop();
           copy = q2.front();
           q2.pop();
           if(org->left!=NULL)
            {
                n1->data = org->left->data;
                copy->right = n1;
                q1.push(org->left);
                q2.push(copy->right);
            }
            if(org->right!=NULL)
            {
                n2->data = org->right->data;
                copy->left = n2;
                q1.push(org->right);
                q2.push(copy->left);
            }
        }
	}

	void rec_mirror(Node *ptr1 , Node* ptr2){
		Node* n1 = new Node;
		n1->data = ptr1->data;
		ptr2 = n1;
		if(ptr1->left != NULL){
			rec_mirror(ptr1->left , ptr2->right);
		}
		if(ptr1->right != NULL){
			rec_mirror(ptr1->right , ptr2->left);
		}
		root = ptr2;

	}

    void operator = (Tree const &t){
        Node* new1 = new Node;
        new1->data = t.root->data;
        root = new1;
        queue <Node*> q1,q2;
        q1.push(t.root);
        q2.push(root);
        Node *copy,*org;
        while(!q2.empty())
        {
        	Node *n1 = new Node;
            Node *n2 = new Node;
            org = q1.front();
            q1.pop();
            copy = q2.front();
            q2.pop();
            if(org->left!=NULL)
            {
                n1->data = org->left->data;
                copy->left = n1;
                q1.push(org->left);
                q2.push(copy->left);
            }
            if(org->right!=NULL)
            {
                n2->data = org->right->data;
                copy->right = n2;
                q1.push(org->right);
                q2.push(copy->right);
            }
        }

    }

    void erase_tree(){
    	queue <Node*> q1;
    	q1.push(root);
    	while(!q1.empty()){
    		Node *curr;
    		curr = q1.front();
    		q1.pop();
    		if(curr->left != NULL){
    			q1.push(curr->left);
    		}
    		if(curr->right != NULL){
    		    q1.push(curr->right);
    		}
    		curr->left = NULL;
    		curr->right = NULL;
    		curr = NULL;
    		delete curr;
    	}
    	tot_ele = 0;
    }

    void rec_erase(Node* curr){
    	if(curr->left != NULL){
        	rec_erase(curr->left);
    	}
    	if(curr->right != NULL){
    	    rec_erase(curr->right);
    	}
    	curr->left = NULL;
    	curr->right = NULL;
    	curr = NULL;
    	delete curr;
    }



};

int main() {
	Tree A,B;
	int ch = 0;

	while (ch != 9){
		cout<<"Enter your Choice : \n1.Insert\n2.Display\n3.Inorder Traversal\n4.Preorder Traversal\n5.Postorder Traversal\n6.Mirror\n7.Copy\n8.Erase\n9.Exit\n";
		cin>>ch;
		switch(ch){

		case 1: A.insert();
				break;

		case 2: A.display();
				break;

		case 3: A.inorder_traversal();
				A.recur_inorder(A.retroot());
				break;

		case 4: A.preorder_traversal();
				A.recur_preorder(A.retroot());
				break;

		case 5: A.postorder_traversal();
				A.recur_postorder(A.retroot());
				break;

		case 6: B.mirror_tree(A);
				//B.rec_mirror(A.retroot(),B.retroot());
				B.display();
				break;

		case 7: B = A;
			    B.display();
                break;

		case 8:	A.erase_tree();
				A.rec_erase(A.retroot());
				cout<<"Tree Erased\n";
				break;

		case 9: break;

		default:cout<<"\nTry Again!\n";
				break;

		}
	}
	return 0;
}
