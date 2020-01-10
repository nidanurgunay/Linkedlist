#include <iostream>
#include<sstream>
#include <fstream>
 
using namespace std;

/************** creation of a struct node***********/
struct node
{ string name;// for the programme i need to store name and laptime
  int laptime;
  node * next;
  //default constructor
	node::node ()
		:name(""),laptime(0), next(NULL)
	{}

	//constructor
	node::node (string name ,int lap,node *n)
		:name(name),laptime(lap), next(n)
	{}	
		
  
};

/***** Begin: the code taken from linkedlist.cpp******/
void ClearList(node *head)
{
	node *ptr;
	while(head!=NULL)
	{
		ptr=head;
		head=head->next;
		delete ptr;
	}
}
/***Emd: the code taken from linkedlist.cpp*******/

/********this function will place the new list as sorted******/
node * SortGeneral(int lapt, node* mylist, node* & head)
{
	node *ptr=head;
	if((head->next==NULL) && lapt < ptr->laptime)// if the new node will place to the beginning of the list and it is the first node
	{  
		head=mylist;
		return ptr;
	}

	if((ptr->laptime) > lapt)// if the new node will place to the beginning of the list 
	{	
		head=mylist;
		return ptr;
	}

	node* prev=ptr; 
	while((ptr->next!=NULL) && (ptr->laptime <= lapt))//if newnode between other nodes
	{
		prev=ptr;
		ptr=ptr-> next;
	
		if((prev->laptime <= lapt) && (lapt < ptr->laptime) )//if the newnode between prev and ptr or equals to ptr then sort it between them
		{
			prev->next=mylist;
			return ptr;
		}
		prev= prev-> next;
	}

	if ((ptr->next==NULL )&& (ptr->laptime < lapt))// if the newnode will be sorted to the end
	{
		ptr->next=mylist;
		return NULL;
	}


}

/********this function will return the best laptime number of newnodes driver **********/
int personaldegreelaptime (node* head,  string name)
{
	if(head->name==name )// if the newnodes driver has the first place 
		return head->laptime;
	
	int degree=0;
	node *temp=head;
	
	while(temp->next!= NULL )// find the place of the newnodes driver
	{
		if( name==temp->name)
			return temp->laptime;

	  temp = temp->next;
	}
	if(temp->next == NULL)// if the ewnodes driver would be the last
		return temp->laptime;
}

/********this function will return the the newnodes drivers degree*********/
int currentposition(node*head,  string name)
{
	if(head->name==name )// if the newnodes driver would be the first
		return 1;
	
	node*temp=head;
	int degree=0;
	while(temp->next!= NULL)// to find the degree of the newnodes drivers current position
	{
		degree ++;
		if(name==temp->name)
			return degree;

		temp=temp->next;

	}
	if(temp->next==NULL)
	{	
		degree++;
		return degree;
	}
}

/********** this function will check if the newnodes driver has been exist in the list before**********/ 
bool exist(node* &temp, node*mylist, node* head)
{
	
	int count = 0;
	string name=mylist->name;
	while(temp->next!=NULL)
	{
		if(temp->name==name)
		{
			head=temp;
			count++;
		}
		if (count==2)
			return true;
		temp=temp->next;
	}
	if(temp->next==NULL && temp->name==name && count==1)
	 return true;

		return false;
}

/* Begin: code taken from linkedlist.cpp */
void DeleteOneNode (node * mylist, node * & head)
	
{
	node * ptr;
	if (mylist == head)  //if the node to be deleted is the first node
	{     head = head->next;
		delete mylist;
	}
	else  //if the node to be deleted is in the middle or at the end
	{     ptr = head;
		while (ptr->next != mylist)
			ptr = ptr->next;
		
		ptr->next = mylist->next;
		delete mylist;
	}
}
/* End: code taken from ptrfunc.cpp */
	


 int main ()
 {
	 ifstream textfile;
	 string filename;
	  
	 cout<< "Please enter a file name. ";
	 cin>> filename;
	 textfile.open(filename.c_str());
		
	 while (textfile.fail())
	 { 
		 cout<<"Unable to open file "<< filename<< endl<< "Please enter a different file name. ";
		 cin>>filename;    
		 textfile.open(filename.c_str());	
	 }

	 cout<<"Successfully opened file "<<filename << endl<< endl;
	 cout<< "############################### "<< endl<< "Qualifying Laps:"<< endl << "###############################"<< endl;
	string line;
		
	node * mylist=NULL;
	node *p=NULL;
	//i created my fisrt node to initialize the head pointer
	getline(textfile,line);
	istringstream iss(line);
	string name1; int lap1;
	iss>> name1>> lap1;

	mylist= new node(name1,lap1,NULL);
						
	node*head=mylist;// i create my head pointer
	int count=1;
	cout<< name1 << " completed the lap in " << lap1<< " milliseconds " << endl;
	cout<< name1<< ": current personal best is" << lap1 << "; current position is "<< count <<endl;
	
	// the other par will be looped beacuse each line list is sorted again and again
		while (getline(textfile,line))
		{   
			istringstream iss(line);
			string name; int lap;
			iss>> name>> lap;
					

			mylist= new node(name,lap,NULL);// icreate a new node with name and laptime that read from file
			p=SortGeneral(lap,mylist, head);// i sorted mu newnode and put it to proper place
			mylist->next=p;// i linked my newnode to proper place 


			node*temp=head;
			cout<< name << " completed the lap in " << lap<< " milliseconds " << endl;
		
				if(exist(temp, mylist,head))// i checked if it is exist or not previously
					{// if it is exist the i checked  which node will delete
						if(mylist->laptime<temp->laptime)
							mylist=temp;//if my newnode wont bedeleted then the pointer that will points to deleted will cange 
			
						DeleteOneNode(mylist, head);	// delete the proper node	
					}

			cout<< name<< ": current personal best is " << personaldegreelaptime(head, name)<< "; current position is "<< currentposition(head, name)<<endl;
					
		}
	
		cout<< "###############################" << endl<< "Results:" <<endl<< "###############################"<< endl;
		int k=1;
		node*temp=head;
			while(temp->next!=NULL)// i willdisplat the sorted linked list to the screen except the last one
			{
				cout<< k<< "." << temp->name << " " << temp->laptime<<endl;
				temp=temp->next;
				k++;
			}
		
			cout<< k<< "." << temp->name << " " << temp->laptime<<endl;// i displayed the last one
	
			ClearList(head);

	 return 0;
 }