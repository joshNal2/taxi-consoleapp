#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>

using namespace std;

string email, password, em, pw, status;
void taxiAppHeader();
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
        cout << "\nCOMPLAINT NO: " << ComplaintNo << "\n";
        cout << "Name:         " << Name << endl;
        cout << "Role:         " << Role << endl;
        cout << "Date of ride: " << Date << endl;
        cout << "Complaint:    " << ComplaintDesc << endl;
        cout << "Status:       " << Status << "\n\n";
    }

    int ComplaintNo;
    string Name, Role, Date, ComplaintDesc, Status;

};

void resolveComplaint(ComplaintsRecord c);

// lost items

struct LostItemsReport {
public:
    LostItemsReport(
        int lostItemReportNo,
        string name,
        string date,
        string lostItemDesc,
        string status
    ) {
        LostItemReportNo = lostItemReportNo;
        Name = name;
        Date = date;
        LostItemDesc = lostItemDesc;
        Status = status;
    }

    void lostItemDisplay() {
        cout << "\nLOST ITEM REPORT NO:  " << LostItemReportNo << "\n";
        cout << "Name:          " << Name << endl;
        cout << "Date of ride: " << Date << endl;
        cout << "Complaint:    " << LostItemDesc << endl;
        cout << "Status:        " << Status << "\n\n";
    }

    int LostItemReportNo;
    string Name, Date, LostItemDesc, Status;

};

void resolveLostItemsReport(LostItemsReport l);



int main(){

    taxiAppHeader();

    cout << "Welcome to Taxi! Booking System where \nyou can securely book a taxi whenever \nand wherever you need it. We pride \nourselves in using only electric \nvehicles, enabling us to provide you \nwith cheaper fares while at the same \ntime being nice to planet! Customer \nsafety is very important to us, all our \ndrivers go through a thorough security \ncheck so rest assured you are in safe \nhands! \n\nPrefer calling? Phone 0800 777 \nto talk to one of our friendly customer \nservice!\n\n";

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

void taxiAppHeader() {
    cout << "***************************************\n";
    cout << "          TAXI! BOOKING SYSTEM         \n";
    cout << "***************************************\n\n";
}

void isCustomer() {
    cout << "Succesfully logged in! Customer" << endl;
    system("PAUSE");
}

void isAdmin() {

    system("cls"); // clearing so login password is cleared from screen

    taxiAppHeader();

    cout << "Welcome Admin!\n\n";

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
        cout << "***************************************\n";
        cout << "               ADMIN MENU              \n";
        cout << "***************************************\n";
            
        cout <<"\n1: View complaints \n2: View lost item reports \n3: Log Out \n\nYour choice : ";
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

    int complaintNo;
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

    inputFile.close();

    // ask admin to choose a complaint from the list
    int complaintNumInput;
    bool complaintDoesNotExist = false;

    cout << "\nPlease choose the Complaint no. from the above that you'd like to action: ";

    do {
        cin >> complaintNumInput;
 
            
            for (ComplaintsRecord c : complaints) { // loop through complaints

                if (complaintNumInput == c.ComplaintNo) {
                    
                    cout << "\nYou have chosen Complaint no. " << c.ComplaintNo <<". ";
                    // display complaint info
                    // c.complaintDisplay();
                    
                    // ask what the'yd like to do with the complaint (1) contact driver / customer (2) change status to resolved  
                    bool choiceInvalid = false;
                    int choice;

                    do {
                        cout << "What would you like to do about this complaint? \n\n1: Contact the driver and customer \n2: Mark as Resolved \n3: Go back to Complaints list \n4: Go back to Admin Menu \n\nYour choice: ";
                        cin >> choice;
                        cout << "\n";
   
                        switch (choice) {
                        case 1: 
                                displayDriverContactInfo();
                                displayCustomerContactInfo(); break;
                        case 2: 
                               resolveComplaint(c);
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
                    
                    cout << "What would you like to do next? \n\n1: Go back to complaints list \n2: Go back to Admin Menu \n\nYour choice: ";
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
                        complaintDoesNotExist = true;
                }
            }

            if (complaintDoesNotExist == true) {
                cout << "\nComplaint no. " << complaintNumInput << " does not exist. Please choose a valid Complaint no. : ";
            }

    } while (complaintDoesNotExist == true);


    system("pause");

}

void resolveComplaint(ComplaintsRecord complaint) {
    fstream iF, oF;
    iF.open("complaints.csv", ios::in);
    oF.open("complaintsNew.csv", ios::out);

    vector<string> row;
    string cell, line;

    int count = 0;

    while (!iF.eof()) {
        count++;
        row.clear();
        getline(iF, line);
        stringstream iF(line);

        while (getline(iF, cell, ',')) {
            row.push_back(cell);
        }
        //Only prepend newline if count is greater than 1
        int complaintNo = stoi(row[0]); //This will error if we have a blank line. I.e., we cannot have an endl in the beginning or the end of the file.
        int rowSize = row.size();

        if (stoi(row[0]) == complaint.ComplaintNo) {
            row[5] = "Resolved";
            cout << "Complaint No. " << complaint.ComplaintNo << " has been marked as resolved.\n\n";
        }
        if (count > 1) {
            oF << endl;         //Add an endl if we are not in the first row of the output file (oF)
        }
        //Write everything to oF output file to overwrite complaints.txt
        for (int i = 0; i < rowSize - 1; i++) {
            oF << row[i] + ',';     //Append a comma between each cell for the csv format.
        }
        oF << row[rowSize - 1];     //Exclude having a comma at the last item of the line.
    }

    iF.close();
    oF.close();
    remove("complaints.csv");
    rename("complaintsNew.csv", "complaints.csv");

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

void listLostItems(vector<LostItemsReport>& lostItems) {

    for (auto lostItem : lostItems) {
        lostItem.lostItemDisplay();
    }
}

void displayLostItemReports() {

    cout << "***************************************\n";
    cout << "               LOST ITEMS              \n";
    cout << "***************************************\n\n";

    int lostItemReportNo;
    string name, date, lostitemDesc, status, tempString;


    // PARSING CSV tutorial link https://www.youtube.com/watch?v=NFvxA-57LLA

    ifstream inputFile;
    inputFile.open("lostitems.csv");
    string line = "";

    vector<LostItemsReport> lostItems;
    while (getline(inputFile, line)) {

        stringstream inputString(line);

        getline(inputString, tempString, ',');
        lostItemReportNo = atoi(tempString.c_str());
        getline(inputString, name, ',');
        getline(inputString, date, ',');
        getline(inputString, lostitemDesc, ',');
        getline(inputString, status, ',');

        LostItemsReport lostItem(lostItemReportNo, name, date, lostitemDesc, status);
        lostItems.push_back(lostItem);
        line = "";
    }

    // display lost Items
    listLostItems(lostItems);

    inputFile.close();

    // ask admin to choose a report from the list
    int lostItemNumInput;
    bool reportDoesNotExist = false;

    cout << "\nPlease choose the Lost Item Report no. from the above that you'd like to action: ";

    do {
        cin >> lostItemNumInput;

        for (LostItemsReport l : lostItems) { // loop through lost Items

            if (lostItemNumInput == l.LostItemReportNo) {

                cout << "\nYou have chosen Lost Item Report no. " << l.LostItemReportNo << "\n\n";
                // display info
                // l.lostItemDisplay();

                // ask what the'yd like to do with the lost item report  
                bool choiceInvalid = false;
                int choice;

                do {
                    cout << "What would you like to do about this lost item report? \n\n1: Contact the driver and customer \n2: Mark as Resolved \n3: Go back to Lost Items list \n4: Go back to Admin Menu \n\nYour choice: ";
                    cin >> choice;
                    cout << "\n";

                    switch (choice) {
                    case 1:
                        displayDriverContactInfo();
                        displayCustomerContactInfo();
                        break;
                    case 2:
                        resolveLostItemsReport(l);
                        break;
                    case 3:
                        displayLostItemReports(); break;
                    case 4:
                        adminMenu(); break;
                    default:
                        cout << "Invalid choice\n\n";
                        choiceInvalid = true;
                    }
                } while (choiceInvalid == true);

                cout << "What would you like to do next? \n\n1: Go back to Lost Items list \n2: Go back to Admin Menu \n\nYour choice: ";
                cin >> choice;
                cout << "\n\n";

                switch (choice) {
                case 1:
                    displayLostItemReports();;
                case 2:
                    adminMenu(); break;
                default:
                    cout << "Invalid choice\n\n";
                    choiceInvalid = true;
                }

            }
            else {
                reportDoesNotExist = true;
            }
        }

        if (reportDoesNotExist == true) {
        cout << "\nLost Item Report no. " << lostItemNumInput << " does not exist. Please choose a valid Lost Item Report no. : ";
        }

    } while (reportDoesNotExist == true);

    system("pause");

}

void resolveLostItemsReport(LostItemsReport lostitem) {
    fstream iF, oF;
    iF.open("lostitems.csv", ios::in);
    oF.open("lostitemsNew.csv", ios::out);

    vector<string> row;
    string cell, line;

    int count = 0;

    while (!iF.eof()) {
        count++;
        row.clear();
        getline(iF, line);
        stringstream iF(line);

        while (getline(iF, cell, ',')) {
            row.push_back(cell);
        }
        //Only prepend newline if count is greater than 1
        int lostItemReportNo = stoi(row[0]); //This will error if we have a blank line. I.e., we cannot have an endl in the beginning or the end of the file.
        int rowSize = row.size();

        if (stoi(row[0]) == lostitem.LostItemReportNo) {
            row[4] = "Resolved";
            cout << "Lost Item Report No. " << lostitem.LostItemReportNo << " has been marked as resolved.\n\n";
        }
        if (count > 1) {
            oF << endl;         //Add an endl if we are not in the first row of the output file (oF)
        }
        //Write everything to oF output file to overwrite lostitems.csv
        for (int i = 0; i < rowSize - 1; i++) {
            oF << row[i] + ',';     //Append a comma between each cell for the csv format.
        }
        oF << row[rowSize - 1];     //Exclude having a comma at the last item of the line.
    }

    iF.close();
    oF.close();
    remove("lostitems.csv");
    rename("lostitemsNew.csv", "lostitems.csv");
}

void logOut() {

    system("cls");
    taxiAppHeader();
    cout << "You've logged out. Bye!\n\n";
    system("pause");
    system("cls");
    main();

}




////////////////////////// END ADMIN FUNCTIONS ////////////////////////// 