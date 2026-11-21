#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
    string address;
};

vector<Contact> contacts;

// Save contacts to file
void saveContacts() {
    ofstream file("contacts.txt");

    for (const Contact &c : contacts) {
        file << c.name << "|" << c.phone << "|"
             << c.email << "|" << c.address << endl;
    }

    file.close();
}

// Load contacts from file
void loadContacts() {
    ifstream file("contacts.txt");
    string line;

    while (getline(file, line)) {
        Contact c;

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        if (p1 != string::npos &&
            p2 != string::npos &&
            p3 != string::npos) {

            c.name = line.substr(0, p1);
            c.phone = line.substr(p1 + 1, p2 - p1 - 1);
            c.email = line.substr(p2 + 1, p3 - p2 - 1);
            c.address = line.substr(p3 + 1);

            contacts.push_back(c);
        }
    }

    file.close();
}

// Add contact
void addContact() {
    Contact c;

    cout << "\nEnter Name: ";
    getline(cin, c.name);

    cout << "Enter Phone: ";
    getline(cin, c.phone);

    cout << "Enter Email: ";
    getline(cin, c.email);

    cout << "Enter Address: ";
    getline(cin, c.address);

    contacts.push_back(c);

    saveContacts();

    cout << "\nContact added successfully!\n";
}

// Display all contacts
void viewContacts() {
    if (contacts.empty()) {
        cout << "\nNo contacts available.\n";
        return;
    }

    cout << "\n===== CONTACT LIST =====\n";

    for (int i = 0; i < contacts.size(); i++) {
        cout << "\nContact " << i + 1 << endl;
        cout << "Name: " << contacts[i].name << endl;
        cout << "Phone: " << contacts[i].phone << endl;
        cout << "Email: " << contacts[i].email << endl;
        cout << "Address: " << contacts[i].address << endl;
    }
}

// Search contact
void searchContact() {
    string search;
    bool found = false;

    cout << "\nEnter name or phone to search: ";
    getline(cin, search);

    for (const Contact &c : contacts) {
        if (c.name.find(search) != string::npos ||
            c.phone.find(search) != string::npos) {

            cout << "\nContact Found!\n";
            cout << "Name: " << c.name << endl;
            cout << "Phone: " << c.phone << endl;
            cout << "Email: " << c.email << endl;
            cout << "Address: " << c.address << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "\nContact not found.\n";
    }
}

// Edit contact
void editContact() {
    string phone;
    bool found = false;

    cout << "\nEnter phone number of contact to edit: ";
    getline(cin, phone);

    for (Contact &c : contacts) {
        if (c.phone == phone) {
            cout << "\nEnter new details:\n";

            cout << "New Name: ";
            getline(cin, c.name);

            cout << "New Phone: ";
            getline(cin, c.phone);

            cout << "New Email: ";
            getline(cin, c.email);

            cout << "New Address: ";
            getline(cin, c.address);

            saveContacts();

            cout << "\nContact updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nContact not found.\n";
    }
}

// Delete contact
void deleteContact() {
    string phone;
    bool found = false;

    cout << "\nEnter phone number of contact to delete: ";
    getline(cin, phone);

    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].phone == phone) {
            contacts.erase(contacts.begin() + i);

            saveContacts();

            cout << "\nContact deleted successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nContact not found.\n";
    }
}

// Main function
int main() {
    loadContacts();

    int choice;
    string input;

    do {
        cout << "\n===== CONTACT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Contact\n";
        cout << "2. View All Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Edit Contact\n";
        cout << "5. Delete Contact\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        getline(cin, input);

        try {
            choice = stoi(input);
        } catch (...) {
            choice = 0;
        }

        switch (choice) {
            case 1:
                addContact();
                break;

            case 2:
                viewContacts();
                break;

            case 3:
                searchContact();
                break;

            case 4:
                editContact();
                break;

            case 5:
                deleteContact();
                break;

            case 6:
                saveContacts();
                cout << "\nContacts saved. Exiting program.\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}