/*
Write an application for booking railway ticket reservation system. The application should
have four functionalities.
1. Book
2. Cancel
3. Print booked tickets (details with summary)
4. Print available tickets (details with summary)
*/
#include <iostream>
#include <queue>
#include<map>
#include <string>
#include<limits>
using namespace std;
short confirmedBerths = 63;
short upperBerths = 21;
short middleBerths = 21;
short lowerBerths = 21;
short racCounts = 18;
short waitingCounts = 10;
queue<int>RacIdvec;
queue<int>WaitingIDvec;
class Passenger
{
public:
    short passengerId;
    short age;
    string name;
    char gender, berth;
    bool seatAllotted;
    string status;
    Passenger(string name = "", short age = 0, char gender = ' ', char berth = ' ', bool seatAllotted = false, short passengerId = 0, string status = "")
    {
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->berth = berth;
        this->seatAllotted = seatAllotted;
        this->passengerId = passengerId;
        this->status = status;
    }
};
class TicketReservation
{
    static short passengerId;
public:
    void Booking(map<int,Passenger> &storage,char type)
    {
        string name;
        bool seatAllotted = false,isChild = false;
        string status;
        short age;
        char gender, berth = 'N';
        cout << "Enter your name:";
        cin >> name;
        cout << "Enter your age:";
        cin >> age;
        if(age<5)
            isChild = true;
        cout << "Enter your gender(M/F):";
        cin >> gender;
        while (gender != 'M' && gender != 'F' && gender != 'm' && gender != 'f')
        {
            cout << "Enter your gender in this format(M/F)!" << endl;
            cout << "Enter your gender(M/F):";
            cin >> gender;
        }
        if(type == 'c')
        {
            cout << "Enter your Berth preference(U/M/L):";
            cin >> berth;
            while (toupper(berth) != 'U' && toupper(berth) != 'M' && toupper(berth) != 'L')
            {
                cout << "Enter your berth in this format(U/M/L)!" << endl;
                cout << "Enter your berth(U/M/L):";
                cin >> berth;
            }
            if ( toupper(berth) == 'U')
            {
                if(upperBerths)
                {
                    upperBerths--;
                    berth = 'U';
                }
                else 
                {
                    cout << "upper berths are occupied!" << endl;
                    if (middleBerths)
                    {
                        berth = 'M';
                        cout << "middle berth is given" << endl;
                        middleBerths--;
                    }
                    else if (lowerBerths)
                    {
                        berth = 'L';
                        cout << "lower berth is given" << endl;
                        lowerBerths--;
                    }
                }
            }
            else if ( toupper(berth) == 'M')
            {
                if(middleBerths)
                {
                    middleBerths--;
                    berth = 'M';
                }
                else 
                {
                    cout << "middle berths are occupied!" << endl;
                    if (upperBerths)
                    {
                        berth = 'U';
                        cout << "upper berth is given" << endl;
                        upperBerths--;
                    }
                    else if (lowerBerths)
                    {
                        berth = 'L';
                        cout << "lower berth is given" << endl;
                        lowerBerths--;
                    }
                }
            }
            else if ( toupper(berth) == 'L')
            {
                if(lowerBerths)
                {
                    lowerBerths--;
                    berth = 'L';
                }
                else
                {
                    cout << "lower berths are occupied!" << endl;
                    if (upperBerths)
                    {
                        berth = 'U';
                        cout << "upper berth is given" << endl;
                        upperBerths--;
                    }
                    else if (middleBerths)
                    {
                        berth = 'M';
                        cout << "middle berth is given" << endl;
                        middleBerths--;
                    }
                }
            }
            confirmedBerths--;
            seatAllotted = true;
            status = "confirmed";
        }
        else if(type == 'r')
        {
            status = "RAC";
            RacIdvec.push(passengerId);
            racCounts--;
        }  
        else
        {
            status = "WaitingTickets";
            WaitingIDvec.push(passengerId);
            waitingCounts--;
        }
        Passenger passenger(name, age, toupper(gender), toupper(berth), seatAllotted, passengerId,status);
        storage[passengerId++] = passenger; 
        cout << "Ticket booked successfully!" << endl;
        
    }
    void Cancel(map<int,Passenger> &storage)
    {
        int cId;
        while (true)
            {
                cout << "Enter the Passenger ID to be cancelled: ";
                cin >> cId;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Input is not an integer. Please try again.\n";
                }
                else
                {
                    break;
                }
            }
        if(storage.find(cId) == storage.end())
        {
            cout<<"Invalid Passenger Id!"<<endl;
        }
        else
        {
            for (auto it = storage.begin(); it != storage.end(); it++)
            {
                if (it->first == cId)
                {
                    if ((it->second.berth) == 'L')
                    {
                        lowerBerths++;
                        confirmedBerths++;
                    }
                    else if (it->second.berth == 'M')
                    {
                        middleBerths++;
                        confirmedBerths++;
                    }
                    else if (it->second.berth == 'U')
                    {
                        upperBerths++;
                        confirmedBerths++;
                    }
                    else if (it->second.status == "RAC")
                    {
                        racCounts++;
                        RacIdvec.pop();
                    }
                    else if (it->second.status == "WaitingTickets")
                    {
                        waitingCounts++;
                        WaitingIDvec.pop();
                    }
                    storage.erase(it->first);
                    break;
                }
            }
        }
        if (RacIdvec.size() > 0 && (lowerBerths > 0 || upperBerths > 0 || middleBerths > 0))
        {
            int id = RacIdvec.front();
            Passenger p = storage[id];
            if (lowerBerths > 0)
            {
                storage[id].berth = 'L';
                lowerBerths--;
                confirmedBerths--;
            }
            else if (middleBerths > 0)
            {
                storage[id].berth = 'M';
                middleBerths--;
                confirmedBerths--;
            }
            else if (upperBerths > 0)
            {
                storage[id].berth = 'U';
                upperBerths--;
                confirmedBerths--;
            }
            RacIdvec.pop();
            racCounts++;
            storage[id].status = "confirmed";
        }
        if (WaitingIDvec.size() > 0 && racCounts > 0)
        {
            int id = WaitingIDvec.front();
            Passenger p = storage[id];
            storage[id].status = "RAC";
            RacIdvec.push(id);
            WaitingIDvec.pop();
            waitingCounts++;
            racCounts--;
        }
        
    }
    void availableTickets()
    {
        cout << "---------------------------------------------------" << endl;
        cout << upperBerths << " upper berths are available" << endl;
        cout << middleBerths << " middle berths are available" << endl;
        cout << lowerBerths << " lower berths are available" << endl;
        cout << racCounts << " RAC Tickets are available" << endl;
        cout << waitingCounts << " Waiting Tickets are available" << endl;
        cout << "---------------------------------------------------" << endl;
    }
    void bookedTickets(map<int,Passenger>storage)
    {
        bool flag = true;
        for (auto it : storage)
        {
              
            flag = false;
            cout << "---------------------------------------------------" << endl;
            cout << "Passenger Id:" << it.second.passengerId<< endl;
            cout << "Name: " << it.second.name << endl;
            cout << "Age : " << it.second.age << endl;
            cout << "Gender :" << it.second.gender << endl;
            cout << "Ticket Status : " << it.second.status << endl;
            if(it.second.status == "confirmed")
                cout << "Berth :" << it.second.berth << endl;
            cout << "---------------------------------------------------" << endl;
        }
        if (flag)
        {
            cout << "No tickets are booked!" << endl;
            return;
        }
    }
};
short TicketReservation ::passengerId = 1;
int main()
{
    TicketReservation ticketReservation;
    map<int,Passenger>storage;
    while (true)
    {
        short choice;
        cout<<"******************************************"<<endl;
        cout << "1.Book" << endl;
        cout << "2.Cancel" << endl;
        cout << "3.Print booked Tickets" << endl;
        cout << "4.Print available Tickets" << endl;
        cout << "5.Exit" << endl;
        cout<<"******************************************"<<endl;
        cout << "Enter your choice:";
        cin >> choice;
        if (choice == 1)
        {
            if (!waitingCounts)
            {
                cout << "Sorry, No Tickets are available!" << endl;
            }
            else
            {
                if (confirmedBerths)
                    ticketReservation.Booking(storage,'c');
                else if (racCounts)
                {
                    char op;
                    cout << "confirmed tickets are occupied" << endl;
                    cout << "Do you want to fill in RAC?(y/n):";
                    cin >> op;
                    if (toupper(op) == 'Y')
                        ticketReservation.Booking(storage,'r');
                }
                else if (waitingCounts)
                {
                    char op;
                    cout << "confirmed tickets are occupied" << endl;
                    cout << "RAC tickets are occupied" << endl;
                    cout << "Do you want to fill in waiting tickets?(y/n):";
                    cin >> op;
                    if (toupper(op) == 'Y')
                        ticketReservation.Booking(storage,'w');
                }
            }
        }
        else if (choice == 2)
        {
            if (confirmedBerths == 3)
            {
                cout << "No tickets are available to cancel!" << endl;
            }
            else
            {
                ticketReservation.Cancel(storage);
            }
        }
        else if (choice == 3)
        {
            ticketReservation.bookedTickets(storage);
        }
        else if (choice == 4)
        {
            if (!waitingCounts)
                cout << "No Tickets are available!" << endl;
            else
                ticketReservation.availableTickets();
        }
        else if (choice == 5)
        {
            return 0;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
}
