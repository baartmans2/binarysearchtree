/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

//binary search tree
//raymond baartmans
//3/9/2020

#include <iostream>

using namespace std;


struct treenode
{
    int num;
    treenode * left;
    treenode * right;
};

void add(treenode* head);
void rem(treenode* head);
bool search(treenode* head);
int getNum();
int findclosest(treenode* curr);

void vis(treenode* head);

int main()
{
    cout<<"Binary Search Tree" << endl;
    bool done = false;
    char input [4];
    treenode * start = new treenode();
    
    while (!done)
    {
        cout << "Type 'a' to add a number, 'r' to remove a number, 'v' to visualize the tree, 's' to search for a number, or 'e' to exit." << endl;
        cin >> input;
        if(input[0] == 'a')
        {
            add(start);
        }
        else if(input[0] == 'r')
        {
            rem(start);
        }
	else if(input[0] == 'v')
        {
	  vis(start);
	}
        else if(input[0] == 's')
        {
            if (search(start))
            {
                cout << "This number is in the tree." << endl;
            }
            else
            {
                cout << "This number is not in the tree." << endl;
            }
        }
        else if(input[0] == 'e')
        {
            done = true;
        }
        else
        {
            cout << "Invalid input, try again." << endl;
        }
    }
    
    return 0;
}

void vis(treenode* head)
{
  treenode* curr = new treenode();
  treenode* prev = new treenode();

  
  
}

void print(treenode* c)
{

}

void add(treenode* head)
{
    int num1 = getNum();
    bool numplaced = false;
    
    if (head->num == NULL)//start node
    {
        head->num = num1;
        //cout << head->num << endl;
    }
    else
    {
        treenode* current = new treenode();
        current  = head;
        treenode* node_to_place = new treenode();
        node_to_place->num = num1;
        
        while (!numplaced)
        {
	  //cout << current->num << endl;
            if ( (num1 > current->num) && (current->right == NULL) )
            {
                current->right = node_to_place;
                numplaced = true;
            }
            else if ( (num1 < current->num) && (current->left == NULL) )
            {
                current->left = node_to_place;
                numplaced = true;
            }
            else if (num1 == current->num)
            {
                numplaced = true;
            }
            else
            {
                 if (num1 > current->num)
                 {
                     current = current->right;
                 }
                 else if (num1 < current->num)
                 {
                     current = current->left;
                 }
            }
        }
    }
}

void rem(treenode* head)
{
    int num2 = getNum();
    
    bool located = false;
    treenode* current = new treenode();
    current = head;
    
    while (!located)
        {
            if (current->right == NULL && current->left == NULL)
            {
                
                if (num2 == current->num)
                {
                    located = true;
                }
                else
                {
                    break;
                }
                
            }
            
            if (num2 == current->num)
            {
                located = true;
            }
            else
            {
                 if (num2 > current->num)
                 {
                     current = current->right;
                 }
                 else if (num2 < current->num)
                 {
                     current = current->left;
                 }
            }
        }
        
        if (!located)
        {
            cout << "Number not found." << endl;
        }
        else
        {
            if (current-> left != NULL && current->right != NULL)//two children
            {
                if (findclosest(current) == 1)//we need to go right.NOTWORKING
                {
                    treenode* original = new treenode();
                    original = current;
                    
                    current = current->right;
                    while (current->left !=NULL)
                    {
                        current = current->left;
                    }

                    original->num = current->num;
		    delete current;
                    
                   
                }
                else if (findclosest(current) == 2)//we need to go left.NOTWORKING
                {
                    treenode* original = new treenode();
                    original = current;
                    
                    current = current->left;
                    while (current->right !=NULL)
                    {
                        current = current->right;
                    }
                    
                    original->num = current->num;
		    delete current;
                    
                }
                else if (findclosest(current) == 3)//the things are equal. NOT WORKING
                {
                    treenode* original = new treenode();
                    original = current;
                    
                    //create temp holder for left children, set right child equal to original, attach temp to left most child or new original. edit: This comment is stupid
                    current = current->right;

		    //cout << "HELP ME!!!" << endl;
                    while (current->left !=NULL)
                    {
                        current = current->left;
                    }
		    original->num = current->num;
		    delete current;
                }
            }
            else if (current->left == NULL && current-> right != NULL)//only a child on the right
            {
	      treenode* original = current;
	      current = current->right;
	      while (current->left != NULL)
		{
		  current = current->left;
		}
	      original->num = current->num;
	      delete current;
            }
            else if (current->left != NULL && current-> right == NULL)//only a child on the left
            {
	      treenode* original = current;
	      current = current->left;
	      while (current->right != NULL)
		{
		  current = current->right;
		}

	      original->num = current->num;
	      delete current;
            }
            else//both children dont exist
            {
                delete current;
            }
        }
}

int findclosest(treenode* curr)//determines whether to go right (1) or left(2) or the diff is equal(3)
{
    int orig; 
    int diff1; //diff going to the right 
    int diff2; //diff going to the left
    orig = curr->num;
    treenode* curr2 = new treenode();
    curr2 = curr;
    
    curr = curr->right;
    while (curr->left != NULL)
    {
        curr = curr->left;
    }
    
    diff1 = curr->num - orig;//calc how far this number was from the original
    
    curr2 = curr2->left;
    while (curr2->right != NULL)
    {
        curr2 = curr2->right;
    }
    
    diff2 = orig - curr2->num;//calc how far this number was from orig

    if (diff1 < diff2)//we should go right
    {
        orig = 1;//orig is repurposed here
    }
    else if (diff2 < diff1)//we should go left
    {
        orig = 2;
    }
    else if (diff2 == diff1)//if differences are equal
    {
        orig = 3;
    }
    
    return orig;
}


bool search(treenode* head)
{
    bool success = false;
    int num3 = getNum();
    
    treenode* current = new treenode();
    current  = head;
    
    while (!success)
        {
            if (current->right == NULL && current->left == NULL)
            {
                
                if (num3 == current->num)
                {
                    success = true;
                }
                else
                {
                    break;
                }
                
            }
            
            if (num3 == current->num)
            {
                success = true;
            }
            else
            {
                 if (num3 > current->num)
                 {
                     current = current->right;
                 }
                 else if (num3 < current->num)
                 {
                     current = current->left;
                 }
            }
        }
    
    cout << num3;
    cout << " ";
    
    return success;
}

int getNum()
{
    int num4;
    cout << "Enter the number you would like to add/remove/search for." << endl;
    cin >> num4;
    return num4;
}

