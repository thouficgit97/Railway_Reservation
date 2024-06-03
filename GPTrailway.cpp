#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

short confirmedBerths = 3;
short upperBerths = 1;
short middleBerths = 1;
short lowerBerths = 1;
short racCounts = 2;
short waitingCounts = 2;

vector<int> RacIdvec;
vector<int> WaitingIDvec;

class Passenger {
public:
    short passengerId;
    short age;
    string name;
    char gender, berth;
    bool seatAllotted;
    string status;

    Passenger(string name, short age, char gender, char berth, bool seatAllotted, short passengerId, string status) {
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->berth = berth;
        this->seatAllotted = seatAllotted;
        this->passengerId = passengerId;
        this->status = status;
    }
};

class TicketReservation {
public:
    static short passengerId;
    static short racId;
    static short waitingId;

    void Booking(unordered_map<int, Passenger>& storage, char type) {
        string name;
        bool seatAllotted = false;
        string status;
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

        if (type == 'c') {
            cout << "Enter your Berth preference (U/M/L): ";
            cin >> berth;

            while (berth != 'U' && berth != 'M' && berth != 'L' && berth != 'u' && berth != 'm' && berth != 'l') {
                cout << "Enter your berth in this format (U/M/L)!" << endl;
                cout << "Enter your berth (U/M/L): ";
                cin >> berth;
            }

            if (!upperBerths && toupper(berth) == 'U') {
                cout << "Upper berths are occupied!" << endl;
                if (middleBerths) {
                    berth = 'M';
                    cout << "Middle berth is given" << endl;
                    middleBerths--;
                } else if (lowerBerths) {
                    berth = 'L';
                    cout << "Lower berth is given" << endl;
                    lowerBerths--;
                }
            } else if (!middleBerths && toupper(berth) == 'M') {
                cout << "Middle berths are occupied!" << endl;
                if (upperBerths) {
                    berth = 'U';
                    cout << "Upper berth is given" << endl;
                    upperBerths--;
                } else if (lowerBerths) {
                    berth = 'L';
                    cout << "Lower berth is given" << endl;
                    lowerBerths--;
                }
            } else if (!lowerBerths && toupper(berth) == 'L') {
                cout << "Lower berths are occupied!" << endl;
                if (upperBerths) {
                    berth = 'U';
                    cout << "Upper berth is given" << endl;
                    upperBerths--;
                } else if (middleBerths) {
                    berth = 'M';
                    cout << "Middle berth is given" << endl;
                    middleBerths--;
                }
            }
            seatAllotted = true;
            status = "confirmed";
        } else if (type == 'r') {
            status = "RAC";
            RacIdvec.push_back(passengerId);
            racCounts--;
        } else {
            status = "WaitingTickets";
            WaitingIDvec.push_back(passengerId);
            waitingCounts--;
        }

        Passenger passenger(name, age, toupper(gender), toupper(berth), seatAllotted, passengerId, status);
        storage[passengerId] = passenger; 
        passengerId++;

        cout << "Ticket booked successfully!" << endl;
    }

    void Cancel(unordered_map<int, Passenger>& storage) {
        short cancelId;
        cout << "Enter your passenger Id: ";
        cin >> cancelId;

        if (storage.find(cancelId) != storage.end()) {
            Passenger passenger = storage[cancelId];

            if (passenger.status == "confirmed") {
                confirmedBerths++;
                if (passenger.berth == 'U') upperBerths++;
                else if (passenger.berth == 'M') middleBerths++;
                else if (passenger.berth == 'L') lowerBerths++;

                if (!RacIdvec.empty()) {
                    int racpId = RacIdvec.front();
                    RacIdvec.erase(RacIdvec.begin());
                    Passenger& racPassenger = storage[racpId];
                    racPassenger.berth = passenger.berth;
                    racPassenger.status = passenger.status;
                    racCounts++;

                    if (!WaitingIDvec.empty()) {
                        int waitingpId = WaitingIDvec.front();
                        WaitingIDvec.erase(WaitingIDvec.begin());
                        Passenger& waitingPassenger = storage[waitingpId];
                        waitingPassenger.status = "RAC";
                        RacIdvec.push_back(waitingpId);
                        waitingCounts++;
                    }
                }
            } else if (passenger.status == "RAC") {
                racCounts++;
                if (!WaitingIDvec.empty()) {
                    int waitingpId = WaitingIDvec.front();
                    WaitingIDvec.erase(WaitingIDvec.begin());
                    Passenger& waitingPassenger = storage[waitingpId];
                    waitingPassenger.status = "RAC";
                    RacIdvec.push_back(waitingpId);
                    waitingCounts++;
                }
            }

            storage.erase(cancelId);
            cout << "Ticket Cancelled successfully!" << endl;
        } else {
            cout << "Invalid Passenger ID!" << endl;
        }
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

    void bookedTickets(unordered_map<int, Passenger> storage) {
        bool flag = true;
        for (auto it : storage) {
            Passenger passenger = it.second;
            flag = false;
            cout << "---------------------------------------------------" << endl;
            cout << "Passenger Id: " << passenger.passengerId << endl;
            cout << "Name: " << passenger.name << endl;
            cout << "Age: " << passenger.age << endl;
            cout << "Gender: " << passenger.gender << endl;
            cout << "Berth: " << passenger.berth << endl;
            cout << "Ticket Status: " << passenger.status << endl;
            cout << "---------------------------------------------------" << endl;
        }
        if (flag) {
            cout << "No tickets are booked!" << endl;
        }
    }
};

short TicketReservation::passengerId = 0;
short TicketReservation::racId = 0;
short TicketReservation::waitingId = 0;

int main() {
    TicketReservation ticketReservation;
    unordered_map<int, Passenger> storage;

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
                    ticketReservation.Booking(storage, 'c');
                } else if (racCounts) {
                    char op;
                    cout << "Confirmed tickets are occupied" << endl;
                    cout << "Do you want to fill in RAC? (y/n): ";
                    cin >> op;
                    if (toupper(op) == 'Y') {
                        ticketReservation.Booking(storage, 'r');
                    }
                } else if (waitingCounts) {
                    char op;
                    cout << "Confirmed tickets are occupied" << endl;
                    cout << "RAC tickets are occupied" << endl;
                    cout << "Do you want to fill in waiting tickets? (y/n): ";
                    cin >> op;
                    if (toupper(op) == 'Y') {
                        ticketReservation.Booking(storage, 'w');
                    }
                }
            }
        } else if (choice == 2) {
            if (confirmedBerths == 3) {
                cout << "No tickets are available to cancel!" << endl;
            } else {
                ticketReservation.Cancel(storage);
            }
        } else if (choice == 3) {
            ticketReservation.bookedTickets(storage);
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
