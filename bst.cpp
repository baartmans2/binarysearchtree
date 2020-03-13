#include <iostream>

using namespace std;


struct treenode
{
    int num;
    treenode * left;
    treenode * right;
};
//methods
void add(treenode* head);
void rem(treenode* head);
bool search(treenode* head);
int getNum();
int findclosest(treenode* curr);
void print(treenode* head, int thenum);
void vis(treenode* startn);

int main()
{
    cout<<"Binary Search Tree" << endl;
    bool done = false;
    char input [4];
    treenode * start = new treenode();
    
    while (!done)//running loop WORKING
    {
        cout << "Type 'a' to add a number, 'r' to remove a number, 'v' to visualize the tree, 's' to search for a number, or 'e' to exit." << endl;
        cin >> input;//get user input
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

void print(treenode* head, int thenum)//function to print out the nodes in tree form on console. WORKING 
{
    // Base case  
    if (head == NULL)  
    {
        return;  
    }
    //this is used to space out the tree. 
    if (head->num != 0)
    {
        thenum += 10;  
    }
  
    print(head->right, thenum);  
  
    cout<<endl;  
    
    if (head-> num != 0)
    {
        for (int i = 10; i < thenum; i++)  
        {
            cout<<" ";  
        }
    
        cout<<head->num <<"\n";  
    }
    

    print(head->left, thenum);  

}

void vis(treenode* startn)
{
    print(startn, 0);//print out the tree WORKING
}

void add(treenode* head)//add a node to the tree WORKING
{
    int num1 = getNum();
    bool numplaced = false;
    
    if (head->num == NULL)//if start node
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
                cout << "Number added." << endl;
            }
            else if ( (num1 < current->num) && (current->left == NULL) )
            {
                current->left = node_to_place;
                numplaced = true;
                cout << "Number added." << endl;
            }
            else if (num1 == current->num)
            {
                numplaced = true;
                cout << "This number is already in the tree." << endl;
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

void rem(treenode* head)//remove a number from the tree WORKING
{
  int num2 = getNum();
    
    bool located = false;
    treenode* current = new treenode();
    current = head;
    
    while (!located)//find number we need to remove in this loop
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
        
    if (!located)//if the loop runs and the number was not found
        {
            cout << "Number not found." << endl;
        }
    else//number was found
        {
            cout << "Delete complete." << endl; 
            if (current-> left != NULL && current->right != NULL)//two children
            {
                if (findclosest(current) == 1)//we need to go right.WORKING
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
                else if (findclosest(current) == 2)//we need to go left.WORKING
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
                else if (findclosest(current) == 3)//the things are equal. WORKING
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


bool search(treenode* head)//finds the number in the tree
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

int getNum()//get input
{
    int num4;
    cout << "Enter the number you would like to add/remove/search for. Range is 1-1000." << endl;
    cin >> num4;
    return num4;
}
