#include <bits/stdc++.h>
#include "PriorityLinkedList.cpp"
using namespace std;

class Employee
{
    public:
        string password;
        int score;
        string name;
        string Designation;
        Tasks tasks;
        Employee *left;
        Employee *right;
        public:
                Employee(){
                        score=0;
                        name='x';
                        Designation='y';
                        left=NULL;
                        right=NULL;
                }
                ~Employee(){
                        delete right,left;
                }
                friend istream& operator >>(istream &in , Employee &p);
                friend ostream& operator <<(ostream &out, const Employee &p);
};

istream& operator>>(istream &in, Employee &p){
        getchar();
        cout<<"Enter Name :"<<endl;
        getline(in,p.name);
        //cout<<"press any key to confirm"<<endl;
        //getchar();
        cout<<"Entered password:"<<endl;
        getline(in,p.password);
        cout<<"Enter Designation:"<<endl;
        getline(in,p.Designation);
        //cout<<"press any key to confirm"<<endl;
        //getchar();
        p.tasks.push();
        return in;
}

ostream & operator<<(ostream &out, Employee &p){
        out<<"Employee Name :"<<p.name<<endl;
        out<<"Designation :"<<p.Designation<<endl;
        out<<"Pending tasks :"<<endl;
        p.tasks.display();
        out<<"Score :"<<p.score<<endl;
}

class organisation:public Employee{
        public:
            Employee *Root,*temp;
                organisation(){
                        Root=NULL;
                        temp=NULL;
                }
                inline Employee* getsenior(){return Root;}
                Employee* insert(Employee*,Employee*);
                void display(Employee *);
                Employee* find_max(Employee *);
                void newEmp( int);
                int height(Employee *);
                int balance(Employee *);
                bool check(Employee*);
};

bool organisation ::check(Employee* root)
{
    if(root == NULL)
        return false;
    bool x = check(root->left);
    if(balance(root)){
        return true;
    }
    bool y = check(root->right);

    return x||y;
}

int organisation::height(Employee* root){
    if(root == NULL){
        return 0;
    }
    else{
        int lheight = height(root->left)+1;
        int rheight = height(root->right)+1;

        return (lheight > rheight) ? lheight : rheight;
    }
}

int max1=0;
Employee* organisation::find_max(Employee* root)
{
    Employee* temp=new Employee();
    if(root == NULL)
    {
        return NULL;
    }
    display(root->left);
    display(root->right);
    if(root->score >= max1)
    {
        max1=root->score;
        temp=root;
    }
    return temp;
}



void organisation::display(Employee* root)
{
        if(root == NULL)
        {
                  return;
        }
        display(root->left);
        display(root->right);
        cout<<*root;
}

int organisation::balance(Employee* root)
{
        if(root == NULL){
            return 0;
        }
        int lheight = height(root->left)+1;
        int rheight = height(root->right)+1;

        return (lheight - rheight);
}

Employee* organisation::insert(Employee* root,Employee* temp){
    if(root==NULL)
    {
        return temp;
    }
    else if(balance(root)==0 && check(root->right))
    {
        root->right=insert(root->right,temp);
    }
    else if(balance(root)==0)
    {
        root->left = insert(root->left,temp);
    }
    else if(balance(root)==1 && check(root->left))
    {
        root->left = insert(root->left,temp);
    }
    else if(balance(root)==1)
    {
        root->right = insert(root->right,temp);
    }
    return root;
}

void organisation::newEmp(int num)
{
    int i;
    for (i=0;i<num;i++)
    {
        temp=new Employee();
        temp->left=NULL;
        temp->right=NULL;
        cin>>*temp;
        Root=insert(Root,temp);
    }
}

void Delete(Employee* root,string name,string pass)
{
    if(root == NULL){
        return;
    }
    Delete(root->left,name,pass);
    Delete(root->right,name,pass);
    if (root->name==name && root->password==pass)
    {
        root->score+=1;
        cout<<"Successively Deleted"<<endl;
        root->tasks.pop();
    }
}

void Insert(Employee* root,string name,string pass)
{
    if(root == NULL){
        return;
    }
    Insert(root->left,name,pass);
    Insert(root->right,name,pass);
    if (root->name==name && root->password==pass)
    {
        root->tasks.push();
    }
}

int main()
{
    organisation tree;
    int choice,t;
    do
    {
        cout<<"\n\n\t| Organization |\n";
        cout<<"\n 1.Create Employee Details";
        cout<<"\n 2.Insert Employee Details";
        cout<<"\n 3.Insert Tasks";
        cout<<"\n 4.Delete Tasks";
        cout<<"\n 5.Display Employee Details";
        cout<<"\n 6.Display Best Employee Details";
        cout<<"\n 7.Exit";
        cout<<"\n";
        cout<<"Enter your choice:";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"\nEnter the total number of employees: ";
                cin>>t;
                tree.newEmp(t);
                break;
            case 2:
                tree.newEmp(1);
                break;
            case 3:
            {
                string name,pass;
                cout<<"Enter the name of employee:";
                cin>>name;
                cout<<"Enter the password:";
                cin>>pass;
                Insert(tree.Root,name,pass);
                break;
            }
            case 4:
            {
                string name,pass;
                cout<<"Enter the name of employee:";
                cin>>name;
                cout<<"Enter the password:";
                cin>>pass;
                Delete(tree.Root,name,pass);
                break;
            }

            case 5:
                if(tree.getsenior() == NULL)
                {
                    cout<<"\n\t**** Tree doesn't exist *****\n";
                    break;
                }
                cout<<"\n\t| Tree Elements |\n\n";
                tree.display(tree.getsenior());
                break;
            case 6:
                cout<<"Best Employee:- "<<endl;
                cout<<*tree.find_max(tree.Root);

                break;
            case 7:
                cout<<"\n\t**** EXIT ****\n";
                break;
            default:
                cout<<"\n\t**** Invalid Choice ****\n";
                break;
        }
    }while(choice!= 7);
    return 0;
}
