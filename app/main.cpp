#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

string email, password, em, pw, status;
void logIn();
void isCustomer();
void isEmployee();
void addCustomer();


// admin related functions
void isAdmin();
void adminMenu();
void displayComplaints();
void displayLostItemReports();
void logOut();
void displayDriverContactInfo();
void displayCustomerContactInfo();
// end admin related functions

// complaints
struct ComplaintsRecord {
public:
    ComplaintsRecord(
        int complaintNo,
        string name,
        string role,
        string date,
        string complaintDesc,
        string status
    ) {
        ComplaintNo = complaintNo;
        Name = name;
        Role = role;
        Date = date;
        ComplaintDesc = complaintDesc;
        Status = status;
    }

    void complaintDisplay() {
        cout << "\nCOMPLAINT NO:  " << ComplaintNo << "\n";
        cout << "Name:          " << Name << endl;
        cout << "Role:         " << Role << endl;
        cout << "Date of ride: " << Date << endl;
        cout << "Complaint:    " << ComplaintDesc << endl;
        cout << "Status:       " << Status << "\n\n";
    }

    int ComplaintNo;
    string Name, Role, Date, ComplaintDesc, Status;

};



int main(){

    int choice;

    cout << "1: Register\n2: Login\n\nYour choice: "; cin >> choice;
    cout << "\n";
    if (choice == 1){
        addCustomer();
        main();
    }
    else if (choice == 2){
        logIn();
    }
}

void logIn(){
    cout << "Enter email: "; cin >> email;
    cout << "Enter password: "; cin >> password;
    cout << "\n\n";

    ifstream read("users/" + email + ".txt");
    getline(read, em);
    getline(read, pw);
    getline(read, status);

    if (em == email && pw == password && status == "customer"){
        isCustomer();
    }
    else if (em == email && pw == password && status == "admin"){
        isAdmin();
    }
    else if (em == email && pw == password && status == "employee"){
        isEmployee();
    }
    else {
        cout << "Failed! User doesn't exist." << endl;
        main();
    }
    
}

void isCustomer() {
    cout << "Succesfully logged in! Customer" << endl;
    system("PAUSE");
}

void isAdmin() {

    system("cls"); // clearing so login password is cleared from screen

    cout << "***************************************\n";
    cout << "             WELCOME ADMIN!            \n";
    cout << "***************************************\n";

    adminMenu();
}

void isEmployee() {
    cout << "Succesfully logged in! Employee" << endl;
    system("PAUSE");
}

void addCustomer() {
    string customerName, email, password, address, phoneNo, creditCardNo;
        cout << "Enter your name: "; getline(cin >> ws, customerName);
        cout << "Enter your email: "; cin >> email;
        cout << "Enter your password: "; cin >> password;
        cout << "Enter your address: "; getline(cin >> ws, address);
        cout << "Enter your phone number: "; cin >> phoneNo;
        cout << "Enter your credit card number: "; cin >> creditCardNo;

        ofstream file;
        file.open("users/" + email + ".txt");
        file << email << endl << password << endl << "customer" << endl << customerName << endl << address << endl << phoneNo << endl << creditCardNo;
        file.close();
}

////////////////////////// ADMIN FUNCTIONS ////////////////////////// 
void adminMenu() {
    bool choiceInvalid = false;
    int choice;

    do {
        cout << "\nADMIN MENU \n\n1: View complaints \n2: View lost item reports \n3: Log Out \n\nYour choice: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
        case 1: displayComplaints(); break;
        case 2: displayLostItemReports(); break;
        case 3: logOut(); break;
        default:
            cout << "Invalid choice\n\n";
            choiceInvalid = true;
        }
    } while (choiceInvalid == true);
}

void listComplaints(vector<ComplaintsRecord>& complaints) {

    for (auto complaint : complaints) {
        complaint.complaintDisplay();
    }
}

void displayComplaints() {

    cout << "***************************************\n";
    cout << "               COMPLAINTS              \n";
    cout << "***************************************\n\n";

    int complaintNo = 0;
    string name, role, date, complaintDesc, status, tempString;


    // PARSING CSV tutorial link https://www.youtube.com/watch?v=NFvxA-57LLA

    ifstream inputFile;
    inputFile.open("complaints.csv");
    string line = "";

    vector<ComplaintsRecord> complaints;
    while (getline(inputFile, line)) {

        stringstream inputString(line);

        getline(inputString, tempString, ',');
        complaintNo = atoi(tempString.c_str());
        getline(inputString, name, ',');
        getline(inputString, role, ',');
        getline(inputString, date, ',');
        getline(inputString, complaintDesc, ',');
        getline(inputString, status, ',');

        ComplaintsRecord complaint(complaintNo, name, role, date, complaintDesc, status);
        complaints.push_back(complaint);
        line = "";
    }

    // display complaints
    listComplaints(complaints);

    // ask admin to choose a complaint from the list
    int complaintNumInput;
    bool complaintDoesNotExist = false;

    cout << "\nPlease choose the Complaint no. from the above that you'd like to action: ";

    do {
        cin >> complaintNumInput;
 
            for (ComplaintsRecord c : complaints) { // loop through complaints

                if (complaintNumInput == c.ComplaintNo) {
                    
                    cout << "\nYou have chosen complaint no. " << c.ComplaintNo << "\n\n";
                    // display complaint info
                    c.complaintDisplay();
                    
                    // ask what the'yd like to do with the complaint (1) contact driver / customer (2) change status to resolved  
                    bool choiceInvalid = false;
                    int choice;

                    do {
                        cout << "\nWhat would you like to do about this complaint? \n\n1: Contact the driver and customer \n2: Mark as Resolved \n3: Go back to Complaints list \n4: Go back to Admin Menu \n\nYour choice: ";
                        cin >> choice;
                        cout << "\n\n";
   
                        switch (choice) {
                        case 1: 
                                displayDriverContactInfo();
                                displayCustomerContactInfo(); break;
                        case 2: 
                                c.Status = "Resolved";
                            //    udateComplaints(vector<ComplaintsRecord>&complaints);
                                break;
                        case 3: 
                                displayComplaints(); break;
                        case 4:
                                adminMenu(); break;
                        default:
                                cout << "Invalid choice\n\n";
                                choiceInvalid = true;
                        }
                    } while (choiceInvalid == true);
                    
                    cout << "\nWhat would you like to do next? \n\n1: Go back to complaints list \n2: Go back to Admin Menu \n\nYour choice: ";
                    cin >> choice;
                    cout << "\n\n";

                    switch (choice) {
                    case 1:
                        displayComplaints();
                    case 2:
                        adminMenu(); break;
                    default:
                        cout << "Invalid choice\n\n";
                        choiceInvalid = true;
                    }

                }
                else { 
                    cout << "Complaint no. " << complaintNumInput << " does not exist. Please choose a valid Complaint no. : ";
                        complaintDoesNotExist = true;
                }
            }

    } while (complaintDoesNotExist == true);
    
    system("pause");

}



void updateComplaints(vector<ComplaintsRecord>& complaints) {

}


void displayDriverContactInfo() {

    // change later
    string name, email;
    int phone = 0211234567; // change later
    cout << "Here are the driver's contact details\n";
    cout << "Name: " << name << endl;
    cout << "Phone no: " << phone << endl;
    cout << "Email: " << email << "\n\n";

}

void displayCustomerContactInfo() {

    // change later
    string name, email;
    int phone = 0221234567; // change later
    cout << "Here are the customer's contact details\n";
    cout << "Name: " << name << endl;
    cout << "Phone no: " << phone << endl;
    cout << "Email: " << email << "\n\n";
};


void displayLostItemReports() {

    cout << "***************************************\n";
    cout << "               LOST ITEMS              \n";
    cout << "***************************************\n\n";


}

void logOut() {

    system("cls");
    cout << "\nYou've logged out. Bye!\n\n";
    main();

}

////////////////////////// END ADMIN FUNCTIONS ////////////////////////// 