#include <iostream>
#include <vector>
#include <string>
using namespace std;

short confirmedBerths = 3;
short upperBerths = 1;
short middleBerths = 1;
short lowerBerths = 1;
short racCounts = 1;
short waitingCounts = 1; 

class Passenger {
public:
    short passengerId;
    short age;
    string name;
    char gender;
    char berth;
    bool seatAllotted;

    Passenger(string name, short age, char gender, char berth, bool seatAllotted, short passengerId) {
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->berth = berth;
        this->seatAllotted = seatAllotted;
        this->passengerId = passengerId;
    }
};

class TicketReservation {
public:
    static short passengerId;
    static short racId;
    static short waitingId;

    void Booking(vector<Passenger> &details, char type) {
        string name;
        bool seatAllotted = false;
        short age;
        char gender, berth = 'N';
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your age: ";
        cin >> age;
        cout << "Enter your gender (M/F): ";
        cin >> gender;
        while (gender != 'M' && gender != 'F' && gender != 'm' && gender != 'f') {
            cout << "Enter your gender in this format (M/F)!" << endl;
            cout << "Enter your gender (M/F): ";
            cin >> gender;
        }
        gender = toupper(gender);

        if (type == 'c') {
            cout << "Enter your Berth preference (U/M/L): ";
            cin >> berth;
            while (berth != 'U' && berth != 'M' && berth != 'L' && berth != 'u' && berth != 'm' && berth != 'l') {
                cout << "Enter your berth in this format (U/M/L)!" << endl;
                cout << "Enter your berth (U/M/L): ";
                cin >> berth;
            }
            berth = toupper(berth);
            if (!upperBerths && berth == 'U') {
                cout << "Upper berths are occupied!" << endl;
                if (middleBerths) {
                    berth = 'M';
                    cout << "Middle berth is given" << endl;
                } else if (lowerBerths) {
                    berth = 'L';
                    cout << "Lower berth is given" << endl;
                }
            } else if (!middleBerths && berth == 'M') {
                cout << "Middle berths are occupied!" << endl;
                if (upperBerths) {
                    berth = 'U';
                    cout << "Upper berth is given" << endl;
                } else if (lowerBerths) {
                    berth = 'L';
                    cout << "Lower berth is given" << endl;
                }
            } else if (!lowerBerths && berth == 'L') {
                cout << "Lower berths are occupied!" << endl;
                if (upperBerths) {
                    berth = 'U';
                    cout << "Upper berth is given" << endl;
                } else if (middleBerths) {
                    berth = 'M';
                    cout << "Middle berth is given" << endl;
                }
            }
            seatAllotted = true;
        }
        
        Passenger passenger(name, age, gender, berth, seatAllotted, passengerId);
        details.push_back(passenger);
        if (details[passengerId].seatAllotted) {
            if (details[passengerId].berth == 'U') {
                upperBerths--;
            } else if (details[passengerId].berth == 'M') {
                middleBerths--;
            } else if (details[passengerId].berth == 'L') {
                lowerBerths--;
            }
        }
        cout << "Ticket booked successfully!" << endl;
        if (type == 'c') {
            confirmedBerths--;
        } else if (type == 'r') {
            racId++;
            racCounts--;
        } else if (type == 'w') {
            waitingId++;
            waitingCounts--;
        }
        passengerId++;
    }

    void Cancel(vector<Passenger>& details, vector<Passenger>& RAC, vector<Passenger>& waitingTickets) {
        short cancelId;
        cout << "Enter your passenger Id: ";
        cin >> cancelId;
        if (cancelId <= 0 || cancelId > details.size()) {
            cout << "Invalid Passenger ID!" << endl;
            return;
        }
        cancelId--; // Adjust for 0-based indexing

        if (details[cancelId].seatAllotted) {
            if (details[cancelId].berth == 'U') {
                upperBerths++;
            } else if (details[cancelId].berth == 'M') {
                middleBerths++;
            } else if (details[cancelId].berth == 'L') {
                lowerBerths++;
            }
            confirmedBerths++;
            details.erase(details.begin() + cancelId);
        } else {
            cout << "Ticket not found or already cancelled!" << endl;
            return;
        }

        if (!RAC.empty()) {
            details.push_back(RAC.front());
            RAC.erase(RAC.begin());
            racCounts++;
            confirmedBerths--;
        }

        if (!waitingTickets.empty() && racCounts > 0) {
            RAC.push_back(waitingTickets.front());
            waitingTickets.erase(waitingTickets.begin());
            racCounts--;
            waitingCounts++;
        }

        cout << "Ticket cancelled successfully!" << endl;
    }

    void availableTickets() {
        cout << "---------------------------------------------------" << endl;
        cout << upperBerths << " upper berths are available" << endl;
        cout << middleBerths << " middle berths are available" << endl;
        cout << lowerBerths << " lower berths are available" << endl;
        cout << racCounts << " RAC Tickets are available" << endl;
        cout << waitingCounts << " Waiting Tickets are available" << endl;
        cout << "---------------------------------------------------" << endl;
    }

    void bookedTickets(const vector<Passenger>& details, const vector<Passenger>& RAC, const vector<Passenger>& waitingTickets) {
        if (details.empty() && RAC.empty() && waitingTickets.empty()) {
            cout << "No tickets are booked!" << endl;
            return;
        }
        
        for (const auto& it : details) {
            cout << "---------------------------------------------------" << endl;
            cout << "Passenger Id: " << it.passengerId + 1 << endl;
            cout << "Name: " << it.name << endl;
            cout << "Age: " << it.age << endl;
            cout << "Gender: " << it.gender << endl;
            cout << "Berth: " << it.berth << endl;
            cout << "Ticket Status: confirmed" << endl;
            cout << "---------------------------------------------------" << endl;
        }
        for (const auto& it : RAC) {
            cout << "---------------------------------------------------" << endl;
            cout << "Passenger Id: " << it.passengerId + 1 << endl;
            cout << "Name: " << it.name << endl;
            cout << "Age: " << it.age << endl;
            cout << "Gender: " << it.gender << endl;
            cout << "Ticket Status: RAC" << endl;
            cout << "---------------------------------------------------" << endl;
        }
        for (const auto& it : waitingTickets) {
            cout << "---------------------------------------------------" << endl;
            cout << "Passenger Id: " << it.passengerId + 1 << endl;
            cout << "Name: " << it.name << endl;
            cout << "Age: " << it.age << endl;
            cout << "Gender: " << it.gender << endl;
            cout << "Ticket Status: waiting list" << endl;
            cout << "---------------------------------------------------" << endl;
        }
    }
};

short TicketReservation::passengerId = 0;
short TicketReservation::racId = 0;
short TicketReservation::waitingId = 0;

int main() {
    TicketReservation ticketReservation;
    vector<Passenger> details;
    vector<Passenger> RAC;
    vector<Passenger> waitingTickets;
    
    while (true) {
        short choice;
        cout << "1. Book" << endl;
        cout << "2. Cancel" << endl;
        cout << "3. Print booked Tickets" << endl;
        cout << "4. Print available Tickets" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (choice == 1) {
            if (!waitingCounts) {
                cout << "Sorry, No Tickets are available!" << endl;
            } else {
                if (confirmedBerths) {
                    ticketReservation.Booking(details, 'c');
                } else if (racCounts) {
                    char op;
                    cout << "Confirmed tickets are occupied" << endl;
                    cout << "Do you want to fill in RAC? (y/n): ";
                    cin >> op;
                    if (toupper(op) == 'Y') {
                        ticketReservation.Booking(RAC, 'r');
                    }
                } else if (waitingCounts) {
                    char op;
                    cout << "Confirmed tickets are occupied" << endl;
                    cout << "RAC tickets are occupied" << endl;
                    cout << "Do you want to fill in waiting tickets? (y/n): ";
                    cin >> op;
                    if (toupper(op) == 'Y') {
                        ticketReservation.Booking(waitingTickets, 'w');
                    }
                }
            }
        } else if (choice == 2) {
            if (confirmedBerths == 3) {
                cout << "No tickets are available to cancel!" << endl;
            } else {
                ticketReservation.Cancel(details, RAC, waitingTickets);
            }
        } else if (choice == 3) {
            ticketReservation.bookedTickets(details, RAC, waitingTickets);
        } else if (choice == 4) {
            if (!waitingCounts) {
                cout << "No Tickets are available!" << endl;
            } else {
                ticketReservation.availableTickets();
            }
        } else if (choice == 5) {
            return 0;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
}
