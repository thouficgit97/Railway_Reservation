#include <iostream>
#define SIZE 5
using namespace std;
short front = 0, back = 0;
int queue[SIZE];
void menu()
{
    cout << "1.Enqueue" << endl;
    cout << "2.Dequeue" << endl;
    cout << "3.Display" << endl;
    cout << "4.Exit" << endl;
}
void Dequeue()
{
    if (back == front)
    {
        cout << "*** Queue is Empty!...You cant\'t dequeue an empty queue***" << endl;
        return;
    }
    else
    {
        int dead = queue[front];
        for(int i=0;i<back;i++)
        {
            queue[i] = queue[i+1];
        }
        cout<<"Dequeued element is "<<dead<<endl;
        back--;
    }
}
void Enqueue()
{
    if (SIZE == back)
    {
        cout << "*** queue is already full!... ***" << endl;
        return;
    }
    int element;
    cout << "Enter a number to enqueue:";
    cin >> element;
    queue[back++] = element;
    cout<<element<<" has been enqueued!"<<endl;
}
void display()
{
    if(back == front )
    cout<<"*** Queue is Empty!...Nothing to Display ***"<<endl;
    else
    {
    for (int i = front; i < back; i++)
    {
        cout << queue[i] << endl;
    }
    }
}
int main()
{
    while(true)
    {
        short choice;
        menu();
        cout<<"Enter Your Choice:";
        cin >> choice;
        if (choice == 1)
        {
            Enqueue();
        }
        else if (choice == 2)
        {
            Dequeue();
        }
        else if (choice == 3)
        {
            display();
        }
        else if (choice == 4)
        {
            return 0;
        }
        else
        {
           continue;
        }
    }
}
