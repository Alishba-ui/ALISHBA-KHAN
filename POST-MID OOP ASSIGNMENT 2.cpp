#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ================= BASE CLASS =================
class LibraryResource {
protected:
    int resourceID;
    string title;
    string author;
    bool isAvailable;
    int type; 

public:
    

    LibraryResource(int id, string t, string a, int type) {
        this->resourceID = id;
        this->title = t;
        this->author = a;
        this->type = type;
        this->isAvailable = true;
    }

    void setTitle(string title) {
        this->title = title; // this pointer 
    }

    void setAvailability(bool isAvailable) {
        this->isAvailable = isAvailable;
    }

    int getID() const { return resourceID; }
    bool getAvailability() const { return isAvailable; }
    int getType() const { return type; }

    void displayDetails() const {
        cout << "ID: " << resourceID
             << ", Title: " << title
             << ", Author: " << author;

        if (type == 1) cout << " (Book)";
        else if (type == 2) cout << " (Magazine)";
        else if (type == 3) cout << " (DVD)";

        cout << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    int calculateLateFee(int daysLate) {
        if (type == 1) return daysLate * 5;
        else if (type == 2) return daysLate * 3;
        else if (type == 3) return daysLate * 10;
        return 0;
    }
};

// ================= DERIVED CLASSES =================
class Book : public LibraryResource {
    string ISBN;
    int pageCount;

public:
    Book(int id, string t, string a, string isbn, int pages)
        : LibraryResource(id, t, a, 1) {
        ISBN = isbn;
        pageCount = pages;
    }
};

class Magazine : public LibraryResource {
    int issueNumber;

public:
    Magazine(int id, string t, string a, int issue)
        : LibraryResource(id, t, a, 2) {
        issueNumber = issue;
    }
};

class DVD : public LibraryResource {
    int duration;

public:
    DVD(int id, string t, string a, int dur)
        : LibraryResource(id, t, a, 3) {
        duration = dur;
    }
};

// ================= MEMBER CLASS =================
class LibraryMember {
    int memberID;
    string name;
    vector<LibraryResource> borrowedItems;

public:
    LibraryMember(int id, string n) {
        memberID = id;
        name = n;
    }

    int getID() const { return memberID; }

    void borrowResource(LibraryResource res) {
        borrowedItems.push_back(res);
    }

    void returnResource(int resourceID) {
        for (int i = 0; i < borrowedItems.size(); i++) {
            if (borrowedItems[i].getID() == resourceID) {
                borrowedItems.erase(borrowedItems.begin() + i);
                cout << "Returned successfully.\n";
                return;
            }
        }
        cout << "Resource not found.\n";
    }

    void displayBorrowedItems() {
        for (int i = 0; i < borrowedItems.size(); i++) {
            borrowedItems[i].displayDetails();
        }
    }

    int calculateTotalLateFee(int daysLate) {
        int total = 0;
        for (int i = 0; i < borrowedItems.size(); i++) {
            total += borrowedItems[i].calculateLateFee(daysLate);
        }
        return total;
    }

    friend void adminView(vector<LibraryResource>&, vector<LibraryMember>&);
};

// ================= FRIEND FUNCTION =================
void adminView(vector<LibraryResource>& resources, vector<LibraryMember>& members) {
    cout << "\n--- ALL RESOURCES ---\n";
    for (int i = 0; i < resources.size(); i++) {
        resources[i].displayDetails();
    }

    cout << "\n--- ALL MEMBERS ---\n";
    for (int i = 0; i < members.size(); i++) {
        cout << "Member ID: " << members[i].memberID
             << ", Name: " << members[i].name << endl;

        members[i].displayBorrowedItems();
    }
}

// ================= MAIN =================
int main() {
    vector<LibraryResource> resources;
    vector<LibraryMember> members;

    int choice;

    do {
        cout << "\n1. Add Resource\n2. Add Member\n3. Borrow\n4. Return\n"
             << "5. Show Resources\n6. Show Member Items\n"
             << "7. Late Fee\n8. Admin View\n9. Exit\n";

        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            int type, id;
            string title, author;

            cout << "1.Book 2.Magazine 3.DVD: ";
            cin >> type;
            cin.ignore();

            cout << "Enter ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Title: ";
            getline(cin, title);

            cout << "Enter Author: ";
            getline(cin, author);

            if (type == 1) {
                string isbn;
                int pages;

                cout << "ISBN: ";
                getline(cin, isbn);

                cout << "Pages: ";
                cin >> pages;

                Book b(id, title, author, isbn, pages);
                resources.push_back(b);
            }
            else if (type == 2) {
                int issue;
                cout << "Issue: ";
                cin >> issue;

                Magazine m(id, title, author, issue);
                resources.push_back(m);
            }
            else {
                int duration;
                cout << "Duration: ";
                cin >> duration;

                DVD d(id, title, author, duration);
                resources.push_back(d);
            }
        }

        else if (choice == 2) {
            int id;
            string name;

            cout << "Member ID: ";
            cin >> id;
            cin.ignore();

            cout << "Name: ";
            getline(cin, name);

            members.push_back(LibraryMember(id, name));
        }

        else if (choice == 3) {
            int mid, rid;
            bool memberFound = false;
            bool resourceFound = false;

            cout << "Member ID: ";
            cin >> mid;
            cout << "Resource ID: ";
            cin >> rid;

            for (int i = 0; i < members.size(); i++) {
                if (members[i].getID() == mid) {
                    memberFound = true;

                    for (int j = 0; j < resources.size(); j++) {
                        if (resources[j].getID() == rid) {
                            resourceFound = true;

                            if (!resources[j].getAvailability()) {
                                cout << "Resource already borrowed.\n";
                            } else {
                                members[i].borrowResource(resources[j]);
                                resources[j].setAvailability(false);
                                cout << "Borrowed successfully.\n";
                            }
                            break;
                        }
                    }
                }
            }

            if (!memberFound) cout << "Member not found.\n";
            else if (!resourceFound) cout << "Resource not found.\n";
        }

        else if (choice == 4) {
            int mid, rid;

            cout << "Member ID: ";
            cin >> mid;
            cout << "Resource ID: ";
            cin >> rid;

            for (int i = 0; i < members.size(); i++) {
                if (members[i].getID() == mid) {
                    members[i].returnResource(rid);

                    for (int j = 0; j < resources.size(); j++) {
                        if (resources[j].getID() == rid) {
                            resources[j].setAvailability(true);
                        }
                    }
                }
            }
        }

        else if (choice == 5) {
            for (int i = 0; i < resources.size(); i++) {
                resources[i].displayDetails();
            }
        }

        else if (choice == 6) {
            int id;
            cout << "Member ID: ";
            cin >> id;

            for (int i = 0; i < members.size(); i++) {
                if (members[i].getID() == id) {
                    members[i].displayBorrowedItems();
                }
            }
        }

        else if (choice == 7) {
            int id, days;
            cout << "Member ID: ";
            cin >> id;
            cout << "Days Late: ";
            cin >> days;

            for (int i = 0; i < members.size(); i++) {
                if (members[i].getID() == id) {
                    cout << "Total Fee: "
                         << members[i].calculateTotalLateFee(days)
                         << endl;
                }
            }
        }

        else if (choice == 8) {
            adminView(resources, members);
        }

    } while (choice != 9);

    return 0;
}