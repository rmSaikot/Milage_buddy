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
    const string dataFile = "fuel_data.txt";

public:
    FuelConsumptionApp() {
        if (!loadFromFile()) {
            cout << "No existing data found. Initializing default values.\n";
            odometer = 20000.0;
            mileage = 40.0;
            remainingFuel = 5.0;
        }
    }

    void addEntry(double amount, double distance) {
        double fuel = (amount <= 13.0) ? amount : amount / 130.0;
        entries.push_back({distance, fuel});
        updateData();
        saveToFile();
        cout << "Entry added successfully!\n";
    }

    double calculateAverageConsumption() const {
        if (entries.empty()) return 0.0;

        double totalDistance = 0.0;
        double totalFuel = 0.0;
        for (const auto& entry : entries) {
            totalDistance += entry.distance;
            totalFuel += entry.fuel;
        }
        return totalFuel / totalDistance;
    }

    void displayEntries() const {
        if (entries.empty()) {
            cout << "No entries available.\n";
            return;
        }

        cout << "\nFuel Entries:\n";
        cout << "---------------------------------\n";
        cout << setw(10) << left << "Distance"
             << setw(10) << left << "Fuel\n";
        cout << "---------------------------------\n";
        for (const auto& entry : entries) {
            cout << setw(10) << left << entry.distance
                 << setw(10) << left << entry.fuel << "\n";
        }
        cout << "---------------------------------\n";
    }

    void displayStatistics() const {
        cout << "\nStatistics:\n";
        cout << "---------------------------------\n";
        cout << setw(15) << left << "Odometer"
             << setw(15) << left << "Mileage (km/l)"
             << setw(15) << left << "Remaining Fuel (liters)\n";
        cout << "---------------------------------\n";
        cout << setw(15) << left << odometer
             << setw(15) << left << mileage
             << setw(15) << left << remainingFuel << "\n";
    }

    void inputOdometerReading(double newReading) {
        if (newReading < odometer) {
            cout << "Error: Odometer reading cannot be less than the current value.\n";
            return;
        }
        odometer = newReading;
        saveToFile();
        cout << "Odometer reading updated successfully!\n";
    }

    void displayEstimatedMileage() const {
        double estimatedMileage = calculateAverageConsumption();
        if (estimatedMileage == 0.0) {
            cout << "Not enough data to calculate mileage.\n";
        } else {
            cout << "Estimated Mileage: " << fixed << setprecision(2)
                 << estimatedMileage << " liters per kilometer\n";
        }
    }

    void resetData() {
        entries.clear();
        odometer = 20000.0;
        mileage = 40.0;
        remainingFuel = 5.0;
        saveToFile();
        cout << "All data has been reset to default values.\n";
    }

private:
    bool loadFromFile() {
        ifstream file(dataFile);
        if (!file.is_open()) return false;

        file >> odometer >> mileage >> remainingFuel;

        entries.clear();
        double distance, fuel;
        while (file >> distance >> fuel) {
            entries.push_back({distance, fuel});
        }
        file.close();
        return true;
    }

    void saveToFile() const {
        ofstream file(dataFile);
        if (!file.is_open()) {
            cerr << "Error saving data to file.\n";
            return;
        }

        file << odometer << " " << mileage << " " << remainingFuel << "\n";
        for (const auto& entry : entries) {
            file << entry.distance << " " << entry.fuel << "\n";
        }
        file.close();
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

void displayMenu() {
    cout << "\n--- Fuel Consumption App ---\n";
    cout << "1. Add Fuel Entry\n";
    cout << "2. Display All Entries\n";
    cout << "3. Display Statistics\n";
    cout << "4. Update Odometer Reading\n";
    cout << "5. Show Estimated Mileage\n";
    cout << "6. Reset All Data\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    FuelConsumptionApp app;
    char choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case '1': {
                double amount, distance;
                cout << "Enter fuel amount (liters or equivalent taka): ";
                cin >> amount;
                cout << "Enter distance traveled (kilometers): ";
                cin >> distance;
                app.addEntry(amount, distance);
                break;
            }
            case '2':
                app.displayEntries();
                break;
            case '3':
                app.displayStatistics();
                break;
            case '4': {
                double newReading;
                cout << "Enter new odometer reading: ";
                cin >> newReading;
                app.inputOdometerReading(newReading);
                break;
            }
            case '5':
                app.displayEstimatedMileage();
                break;
            case '6':
                app.resetData();
                break;
            case '7':
                cout << "Exiting the application. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '7');

    return 0;
}
