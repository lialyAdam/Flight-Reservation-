#include <iostream>
using namespace std;
class Seat {
private:
    int No;
    bool reserved;

public:
    Seat() {
        No = 0;
        reserved = false;
    }
    Seat(int N, bool rs) {
        No = N;
        reserved = rs;
    }

    void setSeatNo(int SN) {
        No = SN;
    }

    void setReserved(bool r) {
        reserved = r;
    }

    int getSeatNo() const {
        return No;
    }

    bool isReserved() const {
        return reserved;
    }

    void reserve() {
        reserved = true;
    }

    void unreserve() {
        reserved = false;
    }

    void printInfo() const {
        cout << "Seat Information (Seat Number: " << No << ", " << (reserved ? "Reserved" : "Not Reserved") << ")" << endl;
    }
};

class Flight {
private:
    Seat** s;
    int nR;
    int* seatsPerRow;

public:
    Flight(int nR, const int* seatsPerRow) : nR(nR), seatsPerRow(new int[nR]) {

        for (int i = 0; i < nR; i++) {
            this->seatsPerRow[i] = seatsPerRow[i];
        }

        s = new Seat * [nR];
        for (int i = 0; i < nR; i++) {
            s[i] = new Seat[seatsPerRow[i]];
            for (int j = 0; j < seatsPerRow[i]; j++) {
                s[i][j] = Seat(i * seatsPerRow[i] + j + 1, false);
            }
        }
    }



    bool isValid(int sNo) const {
        int sumofseats = 0;
        for (int i = 0; i < nR; i++) {
            sumofseats += seatsPerRow[i];
        }
        return (sNo >= 1 && sNo <= sumofseats);
    }

    void reserveSeat(int sNo) {
        if (!isValid(sNo)) {
            cout << "Invalid seat number. Please re-enter it again." << endl;
            return;
        }

        int r = 0;
        int c = sNo - 1;

        for (int i = 0; i < nR; i++) {
            if (c >= seatsPerRow[i]) {
                c -= seatsPerRow[i];
                r++;
            }
            else {
                break;
            }
        }

        if (!s[r][c].isReserved()) {
            s[r][c].reserve();
            cout << "Seat " << sNo << " has been reserved" << endl;
        }
        else {
            cout << "Seat :" << sNo << " is already reserved" << endl;
        }
    }

    void deleteSeat(int sNo) {
        if (!isValid(sNo)) {
            cout << "invalid seat number, try again" << endl;
            return;
        }

        int r = 0;
        int c = sNo - 1;

        for (int i = 0; i < nR; i++) {
            if (c >= seatsPerRow[i]) {
                c -= seatsPerRow[i];
                r++;
            }
            else {
                break;
            }
        }

        if (s[r][c].isReserved()) {
            s[r][c].unreserve();
            cout << "Seat " << sNo << " has been deleted " << endl;
        }
        else {
            cout << "Seat " << sNo << " is already empty.=" << endl;
        }
    }

    void deleteAllReservedSeats() {
        for (int i = 0; i < nR; i++) {
            for (int j = 0; j < seatsPerRow[i]; j++) {
                s[i][j].unreserve();
            }
        }
        cout << " its  deleted , now all the seats as not reserved." << endl;
    }

    void printSeatMap() const {
        for (int i = 0; i < nR; i++) {
            for (int j = 0; j < seatsPerRow[i]; j++) {
                s[i][j].printInfo();
            }
        }
    }
    ~Flight() {
        delete[] seatsPerRow;
        for (int i = 0; i < nR; i++) {
            delete[] s[i];
        }
        delete[] s;
    }
};

int main() {
    int numRows = 3;
    int seatsPerRow[] = { 4,5,7 };

    Flight f(numRows, seatsPerRow);

    while (true) {
        cout << "*******************Menu*******************" << endl;
        cout << "1. Reserve a newly empty seat." << endl;
        cout << "2. Delete a reserved seat." << endl;
        cout << "3. Delete all reserved seats." << endl;
        cout << "4. Print out flight seats map." << endl;
        cout << "5. Quit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the seat number to reserve: ";
            int reserveSeatNumber;
            cin >> reserveSeatNumber;
            f.reserveSeat(reserveSeatNumber);
        }
        else if (choice == 2) {
            cout << "Enter the seat number to delete: ";
            int deleteSeatNumber;
            cin >> deleteSeatNumber;
            f.deleteSeat(deleteSeatNumber);
        }
        else if (choice == 3) {
            f.deleteAllReservedSeats();
        }
        else if (choice == 4) {
            f.printSeatMap();
        }
        else if (choice == 5) {
            cout << "Exiting the program." << endl;
            return 0;
        }
        else {
            cout << "Invalid choice. Please enter a valid option (1-5) " << endl;
        }
    }

    return 0;
}
