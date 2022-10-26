#include<iostream>
using namespace std;
#define MAX_PARKING 3
#define PER_TIME_MONEY 2    
struct Node
{
    double in_time_hour=0;
    double in_time_min=0;
    double out_time_hour=0;
    double out_time_min=0;
    string number;
    Node *next;
    Node() : in_time_hour(0), in_time_min(0), out_time_hour(0), out_time_min(0), next(NULL){};
};
class stack
{
    private:
        Node *top;
    public:
        stack();
        void stack_push(Node *node);
        void stack_pop();
        bool stack_empty();
        void print_stack();
        Node *get_head();
};
class queue
{
    private:
        Node *front;
        Node *rear;
    public:
        queue();
        void queue_push(Node *node);
        void queue_pop();
        bool queue_empty();
        Node *get_queue_head();
        void print_queue();
};
class administrator
{
    private :
        queue *Queue;
        stack *Stack;
        stack *Stack_temp;
        int Capacity = 0;
    public:
        administrator();
        void arrive();
        void menu();
        void leave();
        void print_parking() { Stack->print_stack(); }
        void print_sidewalk() { Queue->print_queue(); }
        void inquire();
        double money(double in_time_hour, double in_time_min, double out_time_hour, double out_time_min);
};
stack::stack()
{
    top = NULL;
}
void stack::stack_push(Node* temp)
{
    Node *node = new Node;
    node = temp;
    node->next = top;
    top = node;
}
void  stack::stack_pop()
{
    Node *node;
    if(stack_empty())
        cout << "停车场内暂无车辆" << endl;
    node = top;
    top = top->next;
    delete node;
}
void stack::print_stack()
{
    Node *node = top;
    if(node==NULL)
    {
        cout << "停车场内无车辆" << endl;
        return;
    }
    while(node)
    {
        cout << "车牌号" << node->number << endl;
        cout << "车辆进入的时间" << node->in_time_hour << "时";
        cout << node->in_time_min << "分" << endl;
        node = node->next;
        cout << "************************" << endl;
    }
}
bool stack::stack_empty()
{
    if(top==NULL)
        return 1;
    else
        return 0;
}
Node* stack::get_head()
{
    Node *node = new Node;
    node->in_time_hour = top->in_time_hour;
    node->in_time_min = top->in_time_min;
    node->number = top->number;
    node->out_time_hour = top->out_time_hour;
    node->out_time_min = top->out_time_min;
    return node;
}
queue::queue()
{
    Node *node = new Node;
    node->next = NULL;
    front = node;
    rear = node;
}
void queue::queue_push(Node* temp)
{
    Node *node = new Node;
    node = temp;
    node->next = NULL;
    rear->next = node;
    rear = node;
}
void queue::queue_pop()
{
    Node *node = NULL;
    node = front->next;
    if(rear==NULL)
        cout << "便道无车辆输出" << endl;
    front->next = node->next;
    if(node->next==NULL)
        rear = front;
    delete node;
}
Node* queue::get_queue_head()
{
    Node *node = new Node;
    node->in_time_hour = rear->in_time_hour;
    node->in_time_min = rear->in_time_min;
    node->number = rear->number;
    node->out_time_hour = rear->out_time_hour;
    node->out_time_min = rear->out_time_min;
    return node;
}
bool queue::queue_empty()
{
    if(rear==front)
        return 1;
    else
        return 0;
}
void queue::print_queue()
{
    Node *node = rear;
    if(node==front)
    {
        cout << "便道无车辆" << endl;
        return;
    }
    while(node)
    {
        cout << "车牌号" << node->number << endl;
        node = node->next;
        cout << "************************" << endl; 
    }
}
administrator::administrator()
{
    Capacity = 0;
    Queue=new queue;
    Stack=new stack;
    Stack_temp=new stack;
}
void administrator::inquire()
{
    cout << "输入便道中离开车辆的车牌号" << endl;
    string inq;
    while(!Queue->queue_empty())
    {
        if(inq==Queue->get_queue_head()->number)
        {
            Queue->queue_pop();
        }
        Queue->queue_push(Queue->get_queue_head());
        Queue->queue_pop();
    }
}
void administrator::arrive()
{
    Node *node = new Node;
    cout << "请输入车牌号:" << endl;
    cin >> node->number;
    if(Capacity==MAX_PARKING) //停车场满，车辆进入便道等待
    {
        cout << "停车场已满，请到便道等待" << endl; 
        Queue->queue_push(node);
    }
    else
    {
        cout << "请输入车辆进入停车场的时间" << endl;
        cout << "小时:";
        cin >> node->in_time_hour;
        cout << endl;
        cout << "分钟:";
        cin >> node->in_time_min;
        Stack->stack_push(node);
        Capacity++;
    }
}
void administrator::leave()
{
    string leave_number;
    Node *node = new Node;
    int pos = 1;
    bool flag = false;
    cout << "请输入离开的车辆的车牌号" << endl;
    cin >> node->number;
    cout << endl;
    while(!Stack->stack_empty())
    {
        if(node->number==Stack->get_head()->number)
        {
            cout << "离开车辆的位置:" << endl;
            cout << pos << endl;
            flag = true;
            node = Stack->get_head();
            Stack->stack_pop();
        }
        Stack_temp->stack_push(Stack->get_head());
        Stack->stack_pop();
        pos++;
    }
    if(!flag)
    {
        cout << "车牌号有误!" << endl;
        return;
    }
    while(!Stack_temp->stack_empty())
    {
        Stack->stack_push(Stack_temp->get_head());
        Stack_temp->stack_pop();
    }
    cout << "输入车辆离开时间" << endl;
    cout << "小时:";
    cin >> node->out_time_hour;
    cout << endl;
    cout << "分钟:";
    cin >> node->out_time_min;
    cout << "需要收取的费用:";
    cout << money(node->in_time_hour, node->in_time_min, node->out_time_hour, node->out_time_min);
    cout << endl;
    Capacity--;
    if(!Queue->queue_empty())
    {
        cout << "请输入车牌号为:" << Queue->get_queue_head()->number << "的车进入停车场的时间" << endl;
        cout << "小时:" ;
        Node *temp = new Node;
        temp = Queue->get_queue_head();
        cin >> temp->in_time_hour;
        cout << "分钟:";
        cin >> temp->in_time_min;
        Stack->stack_push(temp);
        Queue->queue_pop();
    }
}
double administrator::money(double in_hour,double in_min,double out_hour,double out_min)
{
    double hour, min;
    double sum = 0;
    if(in_hour<=out_hour)
    {
        hour = out_hour - in_hour;

    }
    else
    {
        hour = 24 - in_hour + out_hour;
    }
    if(in_min<=out_min)
    {
        min = out_min - in_min;
    }
    else
    {
        min = 60 - in_min + out_min;
    }
    sum = hour  + min/60;
    sum = sum * PER_TIME_MONEY;
    
    return sum;
}
void administrator::menu()
{
    cout << "**************************************************\n";
    cout << "*                    菜单                         *\n";
    cout << "*                 1.车辆到达                      *\n";
    cout << "*                 2.车辆离开                      *\n";
    cout << "*                 3.输出停车场车辆信息             *" << endl;
    cout << "*                 4.输出便道车辆信息               *\n";
    cout << "*                 5.询问便道车辆                  *\n";
    cout << "*                 0.退出                         *\n";
    cout << "**************************************************\n";
}
int main()
{
    administrator *user= new administrator;
    char choice;
    do
    {
        user->menu();
        cout << "输入你的选择" << endl;
        cin >> choice;
        switch(choice)
        {
            case '1':
                user->arrive();
                break;
            case '2':
                user->leave();
                break;
            case '3':
                user->print_parking();
                break;
            case '4':
                user->print_sidewalk();
                break;
            default:
            {
                cout << "输入错误" << endl;
                break;
            }
                
        }
    } while (choice != '0');
}