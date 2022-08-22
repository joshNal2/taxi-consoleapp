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
        cout << "Status:       " << Status << "\n\n";
    }

    int LostItemReportNo;
    string Name, Date, LostItemDesc, Status;

};

void resolveComplaint(ComplaintsRecord c);

int main(){

    taxiAppHeader();

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
    cout << "                TAXI APP               \n";
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
                        cout << "\n\n";
   
                        switch (choice) {
                        case 1: 
                                displayDriverContactInfo();
                                displayCustomerContactInfo(); break;
                        case 2: 
                              //  c.Status = "Resolved";
                              //  update_record();
                               resolveComplaint(c);
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

                cout << "\nYou have chosen complaint no. " << l.LostItemReportNo << "\n\n";
                // display info
                l.lostItemDisplay();

                // ask what the'yd like to do with the complaint (1) contact driver / customer (2) change status to resolved  
                bool choiceInvalid = false;
                int choice;

                do {
                    cout << "\nWhat would you like to do about this lost item report? \n\n1: Contact the driver \n2: Mark as Resolved \n3: Go back to Lost Items list \n4: Go back to Admin Menu \n\nYour choice: ";
                    cin >> choice;
                    cout << "\n\n";

                    switch (choice) {
                    case 1:
                        displayDriverContactInfo();
                        break;
                    case 2:
                        l.Status = "Resolved";
                        //    updateLostItems(vector<LostItemsReport>&lostItems);
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

                cout << "\nWhat would you like to do next? \n\n1: Go back to Lost Items list \n2: Go back to Admin Menu \n\nYour choice: ";
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

void updateLostItems(vector<LostItemsReport>& lostItems) {

}

void logOut() {

    system("cls");
    taxiAppHeader();
    cout << "You've logged out. Bye!\n\n";
    system("pause");
    system("cls");
    main();

}



void resolveComplaint(ComplaintsRecord complaint) {

    int complaintNo = complaint.ComplaintNo;
    fstream inputFile, outputFile;
    inputFile.open("complaints.csv", ios::in);
    outputFile.open("complaintsNew.csv", ios::out);

    vector<string> row;
    string cell;
    string line;

    int count = 0; //debugging remove later

    /*
    while (!inputFile.eof()) {

        count++;
        row.clear();
        getline(inputFile, line);
        stringstream inputFile(line);

        //Put each item into row vector
        while (getline(inputFile, cell, ',')) {
            row.push_back(cell);
        }

        cout << stoi(row[0]) << " " << complaint.ComplaintNo << " ";
        
        //Check if the input ComplaintNo matches the row's complaint ID
        if (stoi(row[0]) == complaint.ComplaintNo) {
            row[5] = " Resolved"; //Mark as resolved if it is
            cout << "Complaint no. " << row[0] << " is marked as resolved.\n";

            //write everything back to output
            int rowSize = row.size();

            //if (!inputFile.eof()) {

            for (int i = 0; i < rowSize - 1; i++) {
                outputFile << row[i] << ",";
                //cout << row[i] << ",";
            }

            outputFile << row[rowSize - 1] << "\n";
            cout << "inputFile.str() is " << inputFile.str() << " !\n";
            //cout << row[rowSize - 1] << "\n";


       // }

            cout << "Writing line for " << row[1] << "\n"; //debugging


        }

    }
    */

    


    // Traverse the file 
    // https://www.geeksforgeeks.org/csv-file-management-using-c/
    while (!inputFile.eof()) {

        row.clear();

        getline(inputFile, line);
        stringstream inputFile(line);

        while (getline(inputFile, cell, ',')) {
            row.push_back(cell);
        }

        complaintNo = stoi(row[0]);
        int rowSize = row.size();

       // cout << "test" << complaintNo << stoi(row[0]) << complaint.ComplaintNo << endl;

        if (stoi(row[0]) == complaint.ComplaintNo) {

         //   count = 1;
            count++;
            row[5] = " Resolved"; //Mark as resolved if it is
            cout << "Complaint no. " << row[0] << " is marked as resolved.\n";

        //    if (!inputFile.eof()) {
             //   for (int i = 0; i < rowSize - 1; i++) {

                    // write the updated data
                    // into a new file 
               //     outputFile << row[i] << ",";
                //}

                outputFile << row[rowSize - 1] << "\n";
          //      outputFile << "test" << "\n";
         //   }
        }
  //      else {
    //        if (!inputFile.eof()) {
                for (int i = 0; i < rowSize - 1; i++) {

                    // writing other existing records
                    // into the new file
                    outputFile << row[i] << ",";
                //    outputFile << "test" << "\n";
                }

                // the last column data ends with a '\n'
                outputFile << row[rowSize - 1] << "\n";
        //    }
        }
     //   if (inputFile.eof())
       //     break;
    



    inputFile.close(); 
    outputFile.close();


    remove("complaints.csv"); 
    rename("complaintsNew.csv", "complaints.csv");



}


////////////////////////// END ADMIN FUNCTIONS ////////////////////////// 