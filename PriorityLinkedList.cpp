#include <iostream>
using namespace std;
/*
highest num-high priority
tasks object.push() to input
tasks object.display() to display
tasks object.peek() to display task with highest priority
tasks object.pop() to pop the element with highest priority
*/
class TaskNode{
    public:
        string task;
        int priority;
        TaskNode* next;
        TaskNode(){
            task='x';
            priority=0;
            next=NULL;
        }
        TaskNode(string Task,int Priority){
            task=Task;
            priority=Priority;
            next=NULL;
        }
        friend istream& operator>>(istream &in , TaskNode &p);
        friend ostream& operator<<(ostream &out, const TaskNode &p);
};

class Tasks:public TaskNode
{
    public:
        TaskNode *head;
        string peek();
        void pop();
        void push();
        void display();
        Tasks()
        {
            head=NULL;
        }

};

ostream& operator<<(ostream &out, const TaskNode &p)
{
    out<<"Task :"<<p.task<<endl;
    out<<"Priority :"<<p.priority<<endl;
    return out;
}

istream& operator>>(istream &in,TaskNode &p){
    cout<<"Enter task To be assigned :"<<endl;
    getchar();
    getline(in,p.task);
    cout<<"Press Enter to confirm !"<<endl;
    getchar();
    cout<<"Enter priority of the task :"<<endl;
    in>>p.priority;
    cout<<"Press Enter to confirm !"<<endl;
    getchar();
    return in;
}

string Tasks::peek(){
    if(head->next!=NULL)
    {
        return head->task;
    }
}

void Tasks::pop()
{
    if(head->next!=NULL)
    {
        TaskNode* temp = head;
        head=head->next;
        delete temp;
    }
}

void Tasks::push(){
    TaskNode *node = new TaskNode();
    cin>>*node;

    // If head is null, this is the first TaskNode to be added
    // so make head = newTaskNode
    if (head == NULL) {
        head = node;
        return;
    }

    TaskNode *temp = head;
    TaskNode *prev = NULL;

    // search for first node having priority less than p
    while (temp != NULL && temp->priority >node->priority ) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        // no TaskNode with priority less than this node (Case 1)
        prev->next = node;
    }
    else {
        if (prev == NULL) {
            // all the nodes have priority less than p (Case 2)
            // add this node at the starting
            node->next = head;
            head = node;
        }
        else {
            // Case 3
            // add this node before the node with priority less than p
            node->next = temp;
            prev->next = node;
        }
    }

}
void Tasks::display(){
    TaskNode *curr=new TaskNode();
    curr=head;
    while(curr!=NULL ){
        cout<<*curr<<endl;
        curr=curr->next;
    }
}
