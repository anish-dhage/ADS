#include <iostream>
#include <stdlib.h>
using namespace std;

class node
{
	int key;
	node *left;
	node *right;
	int height;
public:
	node()
	{
		key=0;
		height = 0;
		left = NULL;
		right = NULL;
	}
	friend class avl;
};

class avl
{
	node *root;
public:
	avl()
	{
		root = NULL;
	}
	node* insert(node* ,int);
	int get_bal(node*);
	int max(int ,int);
	int height(node *);
	node *left_rotate(node *);
	node *right_rotate(node *);
	node* newNode(int);
	void input();
	void inorder(node *);
	void call_asc();
	void call_des();
	void in_des(node *);
	node* delete_node(node* ,int);
	node* min_val(node* );
	void del();
	node* changeKey(node *);
	void call_change();
}; 
void avl :: call_change()
{
	root = changeKey(root);
}
node* avl ::changeKey(node *root)  
{  
	int x,y;
	cout<<"Enter the element you want to search\n";
	cin>>x;
    root = delete_node(root, x);  
    cout<<"Enter the updated value\n";
    cin>>y;
    root = insert(root, y);  
    
    return root;  
}  
void avl :: del()
{
	int x;
	cout<<"Enter the value you want to delete\n";
	cin>>x;
	root = delete_node(root,x);
}
node* avl :: min_val(node* n)
{
  node* current = n;   
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 

node* avl :: delete_node(node* r,int key)
{

	if(r == NULL)
	{	cout<<"Empty\n";
		return r;
	}

	if(key < r->key)
	{	
		r->left = delete_node(r->left,key);
	}

	else if(key > r->key)
	{
	
		r->right = delete_node(r->right,key);
	}
	else
	{
	
		if((r->left == NULL) || (r->right==NULL))
		{
			node *temp = new node; 
				 temp = r->left ? r->left:r->right;
				
			if(temp == NULL)
			{
				temp = r;
				r = NULL;
			}
			else
				r = temp;

			delete temp;
		}
		else
		{
		
			node *temp = min_val(r->right);

			r->key = temp->key;

			r->right = delete_node(r->right,temp->key);
		}
	}
	if (r == NULL) 
      return r; 
  
    r->height = 1 + max(height(r->left), 
                           height(r->right)); 
  
    int balance = get_bal(r); 
  
   
    if (balance > 1 && get_bal(r->left) >= 0) 
        return right_rotate(r); 
  
    if (balance > 1 && get_bal(r->left) < 0) 
    { 
        r->left =  left_rotate(r->left); 
        return right_rotate(r); 
    } 
  
    if (balance < -1 && get_bal(r->right) <= 0) 
        return left_rotate(r); 
  
    if (balance < -1 && get_bal(r->right) > 0) 
    { 
        r->right = right_rotate(r->right); 
        return left_rotate(r); 
    } 
    return r; 
}
void avl :: in_des(node *r)
{

	if(r!=NULL)
	{
		in_des(r->right);
		cout<<r->key<<" ";
		in_des(r->left);
	}
}
void avl :: call_des()
{
	if(root==NULL)
	{	cout<<"Empty\n";
		return;
	}	
	in_des(root);
	cout<<"\n";
	return;
}
void avl :: inorder(node *r)
{
	if(r != NULL)
	{
		inorder(r->left);
		cout<<r->key<<" ";
		inorder(r->right);
	}
}
void avl :: call_asc()
{
	if(root==NULL)
	{
		cout<<"Empty\n";
		return;
	}
	inorder(root);
	cout<<"\n";
	return;
}
node* avl :: right_rotate(node *y)
{
	node *x = y->left;
	node *t2 = x->right;

	x->right = y;
	y->left = t2;

	y->height = max(height(y->left),height(y->right))+1;

	x->height = max(height(x->left),height(x->right))+1;

	return x;
}
node* avl :: left_rotate(node *x)
{
	node *y = x->right;
	node *t2 = y->left;

	y->left = x;
	x->right = t2;

	x->height = max(height(x->left),height(x->right))+1;
	y->height = max(height(y->left),height(y->right))+1;

	return y;
}
int avl :: get_bal(node* n)
{
	if(n==NULL)
		return 0;
	return height(n->left) - height(n->right);
}

int avl :: height(node *n)
{
	if(n==NULL)
		return 0;
	return n->height;
}

int avl :: max(int a,int b)
{
	return (a>b)? a:b;
}
node* avl :: newNode(int key)
{
	 node* Node = new node(); 
    Node->key = key;  
    Node->left = NULL;  
    Node->right = NULL;  
    Node->height = 1;  
    return(Node); 
}
void avl :: input()
{
	int x;
	cout<<"Enter the number \n";
	cin>>x;
	root = insert(root,x);

}
node* avl :: insert(node* node,int key)
{
	if(node==NULL)
		return(newNode(key));

	if(key<node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right,key);
	else
		return node;

	node->height = 1 + max(height(node->left),height(node->right));


	int balance = get_bal(node);

	if(balance > 1 && key< node->left->key)
		return right_rotate(node);
	if(balance <-1 && key> node->right->key)
		return left_rotate(node);

	if(balance > 1 && key > node->left->key)
	{
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	if(balance < -1 && key < node->right->key)
	{
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}

	return node;
	
}

int main()
{
	avl ob;
	int ch;
	while(1)
	{
		cout<<"1)Insert the element\n2)Ascending order\n3)Descending order\n4)Delete the element\n5)Update the value\nExit\n";
		cin>>ch;
		switch(ch)
		{
			case 1:ob.input();
				break;	
			case 2:ob.call_asc();
				break;
				case 3:ob.call_des();
				break;
				case 4:ob.del();
				break;
				case 5: ob.call_change();
					break;
			default: exit(1);
				break;
		}
	}
	return 0;
}