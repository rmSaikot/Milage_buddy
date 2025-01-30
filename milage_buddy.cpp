#include <bits/stdc++.h>
using namespace std;

struct Entry {
    double distance;
    double fuel;
};

class FuelConsumptionApp {
private:
    vector<Entry> entries;
    double odometer;
    double mileage;
    double remainingFuel;

public:
    FuelConsumptionApp() {
        loadFromFile();
    }

    void addEntry(double amount) {
        double distance = 1.0;
        double fuel = (amount <= 13.0) ? amount : amount / 130.0;

        entries.push_back({distance, fuel});
        updateData();
        saveToFile();
    }

    double calculateAverageConsumption() {
        if (entries.empty()) {
            cout << "No entries available.\n";
            return 0.0;
        }

        double totalDistance = 0.0;
        double totalFuel = 0.0;

        for (const auto& entry : entries) {
            totalDistance += entry.distance;
            totalFuel += entry.fuel;
        }

        return totalFuel / totalDistance;
    }

    void displayEntries() {
        if (entries.empty()) {
            cout << "No entries available.\n";
            return;
        }

        cout << "Fuel Entries:\n";
        cout << "---------------------------------\n";
        cout << setw(15) << left << "Distance"
             << setw(15) << left << "Fuel\n";
        cout << "---------------------------------\n";

        for (const auto& entry : entries) {
            cout << setw(15) << left << entry.distance
                 << setw(15) << left << entry.fuel << endl;
        }
    }

    void displayStatistics() {
        cout << "\nStatistics:\n";
        cout << "---------------------------------\n";
        cout << setw(15) << left << "Odometer"
             << setw(15) << left << "Mileage"
             << setw(15) << left << "Remaining Fuel\n";
        cout << "---------------------------------\n";
        cout << setw(15) << left << odometer
             << setw(15) << left << mileage
             << setw(15) << left << remainingFuel << endl;
    }

    void inputOdometerReading() {
        cout << "Enter Odometer Reading: ";
        if (!(cin >> odometer)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n";
        }
    }

    void displayEstimatedMileage() {
        double estimatedMileage = calculateAverageConsumption();
        cout << "Estimated Mileage: " << estimatedMileage << " liters per kilometer\n";
    }

private:
    void loadFromFile() {
        ifstream file("fuel_data.txt");
        if (file.is_open()) {
            file >> odometer >> mileage >> remainingFuel;
            file.close();
        } else {
            odometer = 20000.0;
            mileage = 40.0;
            remainingFuel = 1.0;
        }
    }

    void saveToFile() {
        ofstream file("fuel_data.txt");
        if (file.is_open()) {
            file << odometer << " " << mileage << " " << remainingFuel;
            file.close();
        } else {
            cout << "Error saving data to file.\n";
        }
    }

    void updateData() {
        if (!entries.empty()) {
            const Entry& lastEntry = entries.back();
            odometer += lastEntry.distance;
            mileage = calculateAverageConsumption();
            remainingFuel -= lastEntry.fuel;
        }
    }
};

int main() {
    FuelConsumptionApp app;

    char choice;
    do {
        cout << "\n1. Add Entry\n";
        cout << "2. Calculate Average Consumption\n";
        cout << "3. Display Entries\n";
        cout << "4. Display Statistics\n";
        cout << "5. Input Odometer Reading\n";
        cout << "6. Display Estimated Mileage\n";
        cout << "7. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                double amount;
                cout << "Enter the amount in liters or taka: ";
                cin >> amount;
                app.addEntry(amount);
                break;
            }
            case '2':
                cout << "Average Fuel Consumption: " << app.calculateAverageConsumption() << " liters per kilometer\n";
                break;
            case '3':
                app.displayEntries();
                break;
            case '4':
                app.displayStatistics();
                break;
            case '5':
                app.inputOdometerReading();
                break;
            case '6':
                app.displayEstimatedMileage();
                break;
            case '7':
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != '7');

    return 0;
}
