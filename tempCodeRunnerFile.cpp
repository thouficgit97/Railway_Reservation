/*
Write an application for booking railway ticket reservation system. The application should
have four functionalities.
1. Book
2. Cancel
3. Print booked tickets (details with summary)
4. Print available tickets (details with summary)
*/
#include <iostream>
#include <vector>
#include<map>
#include <string>
using namespace std;
short confirmedBerths = 3;
short upperBerths = 1;
short middleBerths = 1;
short lowerBerths = 1;
short racCounts = 1;
short waitingCounts = 1;
vector<int>RacIdvec(racCounts);
vector<int>WaitingIDvec(waitingCounts);
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
public:
    static short passengerId;
    static short racId;
    static short waitingId;
    void Booking(map<int,Passenger> &storage,char type)
    {
        string name;
        bool seatAllotted = false;
        string status;
        short age;
        char gender, berth = 'N', hasChild;
        cout << "Enter your name:";
        cin >> name;
        cout << "Enter your age:";
        cin >> age;
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
            while (berth != 'U' && berth != 'M' && berth != 'L' && berth != 'u' && berth != 'm' && berth != 'l')
            {
                cout << "Enter your berth in this format(U/M/L)!" << endl;
                cout << "Enter your berth(U/M/L):";
                cin >> berth;
            }
            if ( toupper(berth) == 'U')
            {
                if(upperBerths)
                    upperBerths--;
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
                    middleBerths--;
                else 
                {
                    cout << "middle berths are occupied!" << endl;
                    if (upperBerths)
                    {
                        berth = 'U';
                        cout << "upper berth is given" << endl;
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
            else if ( toupper(berth) == 'L')
            {
                if(lowerBerths)
                    lowerBerths--;
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
            RacIdvec[racId++] = passengerId;
            racCounts--;
        }  
        else
        {
            status = "WaitingTickets";
            WaitingIDvec[waitingId++] = passengerId;
            waitingCounts--;
        }
        Passenger passenger(name, age, toupper(gender), toupper(berth), seatAllotted, passengerId,status);
        storage[passengerId++] = passenger; 
        cout << "Ticket booked successfully!" << endl;
        
    }
    void Cancel(map<int,Passenger> &storage)
    {
        int cancelId;
        cout<<"Enter your passenger Id:";
        cin>>cancelId;
        if(storage.find(cancelId)!=storage.end())
        {
            Passenger passenger = storage[cancelId];
            storage.erase(cancelId);
            if(passenger.status == "confirmed")
            {
                confirmedBerths++;
                if(passenger.berth == 'L')
                    lowerBerths++;
                else if(passenger.berth == 'M')
                    middleBerths++;
                else if(passenger.berth == 'U')
                    upperBerths++;
                if(racId)
                {
                    int racPasId = RacIdvec.front();
                    RacIdvec.erase(RacIdvec.begin());
                    racCounts++;
                    racId--;
                    storage[racPasId].status = "confirmed";
                    storage[racPasId].berth = passenger.berth;
                    storage[racPasId].seatAllotted = true;
                    confirmedBerths--;
                    if(passenger.berth == 'L')
                    lowerBerths++;
                    else if(passenger.berth == 'M')
                        middleBerths++;
                    else if(passenger.berth == 'U')
                        upperBerths++;
                    if(waitingId)
                    {
                        int waitingPasId = WaitingIDvec.front();
                        WaitingIDvec.erase(WaitingIDvec.begin());
                        waitingCounts++;
                        waitingId--;
                        storage[waitingPasId].status = "RAC";
                        racCounts--;
                        racId++;
                        RacIdvec.push_back(waitingPasId);
                    }
                }
            }
            else if(passenger.status == "RAC")
            {
                racCounts++;
                racId--;
                if(waitingId)
                {
                    int waitingPasId = WaitingIDvec.front();
                    WaitingIDvec.erase(WaitingIDvec.begin());
                    waitingCounts++;
                    waitingId--;
                    storage[waitingPasId].status = "RAC";
                    racCounts--;
                    racId++;
                    RacIdvec.push_back(waitingPasId);
                }
            }
            else if(passenger.status == "waitingTickets")
            {
                waitingCounts++;
                waitingId--;
                WaitingIDvec.erase(WaitingIDvec.begin());
            }
        }
        else
        {
            cout<<"Invalid Passenger Id!"<<endl;
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
            Passenger passenger = it.second;  
            flag = false;
            cout << "---------------------------------------------------" << endl;
            cout << "Passenger Id:" << passenger.passengerId + 1 << endl;
            cout << "Name: " << passenger.name << endl;
            cout << "Age : " << passenger.age << endl;
            cout << "Gender :" << passenger.gender << endl;
            cout << "Berth :" << passenger.berth << endl;
            cout << "Ticket Status : " << passenger.status << endl;
            cout << "---------------------------------------------------" << endl;
        }
        if (flag)
        {
            cout << "No tickets are booked!" << endl;
            return;
        }
    }
};
short TicketReservation ::passengerId = 0;
short TicketReservation ::racId = 0;
short TicketReservation ::waitingId = 0;
int main()
{
    TicketReservation ticketReservation;
    map<int,Passenger>storage;
    vector<int> RAC;
    vector<int> waitingTickets;
    while (true)
    {
        short choice;
        cout << "1.Book" << endl;
        cout << "2.Cancel" << endl;
        cout << "3.Print booked Tickets" << endl;
        cout << "4.Print available Tickets" << endl;
        cout << "5.Exit" << endl;
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
