
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Vehicle {
public:
    string driverName;
    string vehicleNo;
    float hoursOfStay;
    string timeSlot;

    virtual float calculateCharges() = 0;
};

class Motorcycle : public Vehicle {
public:
    float calculateCharges() {
        return hoursOfStay * 15.0f;
    }
};

class Car : public Vehicle {
public:
    float calculateCharges() {
        return hoursOfStay * 25.0f;
    }
};

void addVehicle() {
    ofstream outFile("parking.txt", ios::app);

    cout << "\nAdd a Vehicle\n";
    cout << "Driver Name: ";
    string driverName;
    cin.ignore();
    getline(cin, driverName);

    cout << "Vehicle No: ";
    string vehicleNo;
    getline(cin, vehicleNo);

    cout << "Hours of Stay: ";
    float hoursOfStay;
    cin >> hoursOfStay;

    cout << "Time Slot: ";
    string timeSlot;
    cin.ignore();
    getline(cin, timeSlot);

    if (outFile.is_open()) {
        outFile << driverName << "|"; // Delimiter: ,
        outFile << vehicleNo << "|";
        outFile << hoursOfStay << "|";
        outFile << timeSlot << "\n";

        cout << "\nVehicle added successfully!\n";
    } else {
        cout << "\nFailed to open the file.\n";
    }

    outFile.close();
}

void viewVehicles() {
    ifstream inFile("parking.txt");
    if (!inFile.is_open()) {
        cout << "\nNo vehicles parked yet.\n";
        return;
    }

    cout << "\nView Parked Vehicles\n";

    string line;
    int vehicleCount = 0;

    string searchVehicleNo;
    cout << "Enter the Vehicle No to search: ";
    cin.ignore();
    getline(cin, searchVehicleNo);

    bool found = false;

    while (getline(inFile, line)) {
        size_t pos = 0;
        string delimiter = "|";
        string token;

        string driverName;
        string vehicleNo;
        string hoursOfStay;
        string timeSlot;

        // Extract driver name
        pos = line.find(delimiter);
        driverName = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        // Extract vehicle number
        pos = line.find(delimiter);
        vehicleNo = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        // Extract hours of stay
        pos = line.find(delimiter);
        hoursOfStay = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        // Extract time slot
        timeSlot = line;

        // Determine the type of vehicle
        string vehicleType;
        if (vehicleNo.length() <= 9) {
            vehicleType = "Motorcycle";
        } else {
            vehicleType = "Car";
        }

        if (vehicleNo == searchVehicleNo) {
            cout << "\nDriver Name: " << driverName << endl;
            cout << "Vehicle No: " << vehicleNo << endl;
            cout << "Hours of Stay: " << hoursOfStay << endl;
            cout << "Time Slot: " << timeSlot << endl;
            cout << "Vehicle Type: " << vehicleType << endl;

            found = true;
            vehicleCount++;
        }
    }

    inFile.close();

    if (vehicleCount == 0) {
        cout << "\nNo vehicles with the specified vehicle number.\n";
    } else {
        cout << "\nTotal vehicles found: " << vehicleCount << endl;
    }
}

void calculateCharges() {
    ifstream inFile("parking.txt");
    if (!inFile.is_open()) {
        cout << "\nNo vehicles parked yet.\n";
        return;
    }

    cout << "\nCalculate Charges\n";

    string line;
    int vehicleCount = 0;
    float totalCharges = 0.0f;

    string searchVehicleNo;
    cout << "Enter the Vehicle No to calculate charges: ";
    cin.ignore();
    getline(cin, searchVehicleNo);

    bool found = false;

    string driverName, vehicleNo, hoursOfStayStr, timeSlot;
    while (getline(inFile, driverName, '|') && getline(inFile, vehicleNo, '|') &&
           getline(inFile, hoursOfStayStr, '|') && getline(inFile, timeSlot)) {
        float hoursOfStay = stof(hoursOfStayStr); // Convert string to float

        if (vehicleNo == searchVehicleNo) {
            Vehicle* vehicle = nullptr;

            if (vehicleNo.length() <= 9) {
                vehicle = new Motorcycle();
            } else {
                vehicle = new Car();
            }

            if (vehicle) {
                vehicle->driverName = driverName;
                vehicle->vehicleNo = vehicleNo;
                vehicle->hoursOfStay = hoursOfStay;
                vehicle->timeSlot = timeSlot;

                float charges = vehicle->calculateCharges();
                totalCharges += charges;

                cout << "\nDriver Name: " << vehicle->driverName << endl;
                cout << "Vehicle No: " << vehicle->vehicleNo << endl;
                cout << "Hours of Stay: " << vehicle->hoursOfStay << endl;
                cout << "Time Slot: " << vehicle->timeSlot << endl;
                cout << "Charges: " << charges << endl;

                delete vehicle;
                vehicleCount++;

                found = true;
            }
        }
    }

    inFile.close();

    if (vehicleCount == 0) {
        cout << "\nNo vehicles with the specified vehicle number.\n";
    } else if (!found) {
        cout << "\nVehicle not found.\n";
    } else {
        cout << "\nTotal vehicles found: " << vehicleCount << endl;
        cout << "Total charges: " << totalCharges << endl;
    }
}
void generateBill() {
    ifstream inFile("parking.txt");
    if (!inFile.is_open()) {
        cout << "\nNo vehicles parked yet.\n";
        return;
    }

    cout << "\nGenerate Bill\n";

    string line;
    int vehicleCount = 0;

    string searchVehicleNo;
    cout << "Enter the Vehicle No to generate bill: ";
    cin.ignore();
    getline(cin, searchVehicleNo);

    bool found = false;

    ofstream billFile("bill.txt");  // Create and open the bill file

    while (getline(inFile, line)) {
        size_t pos = 0;
        string delimiter = "|";
        string token;

        string driverName;
        string vehicleNo;
        string hoursOfStayStr;
        string timeSlot;

        // Extract driver name
        pos = line.find(delimiter);
        driverName = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        // Extract vehicle number
        pos = line.find(delimiter);
        vehicleNo = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        // Extract hours of stay
        pos = line.find(delimiter);
        hoursOfStayStr = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        // Extract time slot
        timeSlot = line;

        if (vehicleNo == searchVehicleNo) {
            Vehicle* vehicle = nullptr;

            if (vehicleNo.length() <= 9) {
                vehicle = new Motorcycle();
            } else {
                vehicle = new Car();
            }

            if (vehicle) {
                vehicle->driverName = driverName;
                vehicle->vehicleNo = vehicleNo;
                vehicle->hoursOfStay = stof(hoursOfStayStr);
                vehicle->timeSlot = timeSlot;

                float charges = vehicle->calculateCharges();

                cout << "\nDriver Name: " << vehicle->driverName << endl;
                cout << "Vehicle No: " << vehicle->vehicleNo << endl;
                cout << "Hours of Stay: " << vehicle->hoursOfStay << endl;
                cout << "Time Slot: " << vehicle->timeSlot << endl;
                cout << "Charges: " << charges << endl;

                // Write the bill details to the bill file
                billFile << "\t|***Parking Bill****"<<"\t|"<<endl;
                billFile << "\t|\tDriver Name: " << vehicle->driverName <<"\t|"<< endl;
                billFile << "\t|\tVehicle No: " << vehicle->vehicleNo <<"\t|"<< endl;
                billFile << "\t|\tHours of Stay: " << vehicle->hoursOfStay<<"\t|" << endl;
                billFile << "\t|\tTime Slot: " << vehicle->timeSlot <<"\t\t|"<< endl;
                billFile << "\t|\tCharges: " << charges <<"\t\t|"<< endl;
              
                billFile << "\t|***********" << "|" << endl;
                billFile << endl;

                delete vehicle;
                vehicleCount++;

                found = true;
            }
        }
    }

    inFile.close();
    billFile.close();  // Close the bill file

    if (vehicleCount == 0) {
        cout << "\nNo vehicles with the specified vehicle number.\n";
    } else if (!found) {
        cout << "\nVehicle not found.\n";
    } else {
        cout << "\nBill generated successfully!\n";
    }

}


void removeVehicle() {
    ifstream inFile("parking.txt");
    if (!inFile.is_open()) {
        cout << "\nNo vehicles parked yet.\n";
        return;
    }

    cout << "\nRemove Vehicle\n";
    cout << "Enter the Vehicle No: ";
    string searchVehicleNo;
    cin.ignore();
    getline(cin, searchVehicleNo);

    string line;
    int vehicleCount = 0;
    bool found = false;

    ofstream tempFile("temp.txt");

    while (getline(inFile, line)) {
        string driverName = line;
        getline(inFile, line); // vehicleNo
        getline(inFile, line); // hoursOfStay
        getline(inFile, line); // timeSlot

        if (line == searchVehicleNo) {
            found = true;
            cout << "\nVehicle found and removed successfully!\n";
        } else {
            tempFile << driverName << "\n";
            tempFile << line << "\n";
            tempFile << line << "\n";
            tempFile << line << "\n";
        }

        vehicleCount++;
    }

    inFile.close();
    tempFile.close();

    remove("parking.txt");
    rename("temp.txt", "parking.txt");

    if (vehicleCount == 0) {
        cout << "\nNo vehicles parked yet.\n";
    } else if (!found) {
        cout << "\nVehicle found and removed successfully!";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n\n====== VEHICLE PARKING RESERVATION SYSTEM ======\n";
        cout << "1. Add a Vehicle\n";
        cout << "2. View Parked Vehicles\n";
        cout << "3. calculate charges\n";
        cout << "4. Generate Bill\n";
        cout << "5. Remove Vehicle\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addVehicle();
                break;
            case 2:
                viewVehicles();
                break;
            case 3:
                calculateCharges() ;
                break;
            case 4:
                generateBill();
                break;
            case 5:
                removeVehicle();
                break;
            case 6:
                exit(0);
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}