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
void logOut();
int exit();

// admin related functions
void isAdmin();
void adminMenu();
void displayComplaints();
void complaintsSubmenu();
void displayLostItemReports();
void lostItemsReportSubmenu();
void suspendAccount(string email);
void unsuspendAccount();

// complaints
struct ComplaintsRecord {
public:
    ComplaintsRecord(
        int complaintNo,
        string name,
        string role,
        string date,
        string complaintDesc,
        string status,
        string drivername,
        string driveremail,
        string driverphone,
        string customername,
        string customeremail,
        string customerphone
    ) {
        ComplaintNo = complaintNo;
        Name = name;
        Role = role;
        Date = date;
        ComplaintDesc = complaintDesc;
        Status = status;
        DriverName = drivername;
        DriverEmail = driveremail;
        DriverPhone = driverphone;
        CustomerName = customername;
        CustomerEmail = customeremail;
        CustomerPhone = customerphone;
    }

    void complaintDisplay() {
        cout << "\nCOMPLAINT NO: " << ComplaintNo << "\n";
        cout << "Name:         " << Name << endl;
        cout << "Role:         " << Role << endl;
        cout << "Date of ride: " << Date << endl;
        cout << "Complaint:    " << ComplaintDesc << endl;
        cout << "Status:       " << Status << "\n\n";
    }

    void driverDetailsDisplay() {
        cout << "Driver Name:       " << DriverName << endl;
        cout << "Driver Email:      " << DriverEmail << endl;
        cout << "Drive Phone No:    " << DriverPhone << "\n\n";
    }

    void customerDetailsDisplay() {
        cout << "Customer Name:     " << CustomerName << endl;
        cout << "Customer Email:    " << CustomerEmail << endl;
        cout << "Customer Phone No: " << CustomerPhone << "\n\n";
    }
    
    
    int ComplaintNo;
    string Name, Role, Date, ComplaintDesc, Status, DriverName, DriverEmail, DriverPhone, CustomerName, CustomerEmail, CustomerPhone;

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
        string status,
        string drivername,
        string driveremail,
        string driverphone,
        string customername,
        string customeremail,
        string customerphone
    ) {
        LostItemReportNo = lostItemReportNo;
        Name = name;
        Date = date;
        LostItemDesc = lostItemDesc;
        Status = status;
        DriverName = drivername;
        DriverEmail = driveremail;
        DriverPhone = driverphone;
        CustomerName = customername;
        CustomerEmail = customeremail;
        CustomerPhone = customerphone;
    }

    void lostItemDisplay() {
        cout << "\nLOST ITEM REPORT NO:  " << LostItemReportNo << "\n";
        cout << "Name:          " << Name << endl;
        cout << "Date of ride: " << Date << endl;
        cout << "Complaint:    " << LostItemDesc << endl;
        cout << "Status:        " << Status << "\n\n";
    }

    void driverDetailsDisplay() {
        cout << "Driver Name:       " << DriverName << endl;
        cout << "Driver Email:      " << DriverEmail << endl;
        cout << "Drive Phone No:    " << DriverPhone << "\n\n";
    }

    void customerDetailsDisplay() {
        cout << "Customer Name:     " << CustomerName << endl;
        cout << "Customer Email:    " << CustomerEmail << endl;
        cout << "Customer Phone No: " << CustomerPhone << "\n\n";
    }

    int LostItemReportNo;
    string Name, Date, LostItemDesc, Status, DriverName, DriverEmail, DriverPhone, CustomerName, CustomerEmail, CustomerPhone;

};

void resolveLostItemsReport(LostItemsReport l);


int main(){

    system("cls"); 

    taxiAppHeader();

    cout << "Welcome to Taxi! Booking System where \nyou can securely book a taxi whenever \nand wherever you need it. We pride \nourselves in using only electric \nvehicles, enabling us to provide you \nwith cheaper fares while at the same \ntime being nice to planet! Customer \nsafety is very important to us, all our \ndrivers go through a thorough security \ncheck so rest assured you are in safe \nhands! \n\nPrefer calling? Phone 0800 777 \nto talk to one of our friendly customer \nservice!\n\n";

    bool choiceInvalid = false;
    int choice;

    do {
        cout << "1: Register\n2: Login\n\nYour choice: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
        case 1:
            addCustomer();
            main(); 
            break;
        case 2:
            logIn();
            break;
        default:
            cout << "Invalid choice\n\n";
            choiceInvalid = true;
        }
    } while (choiceInvalid == true);



}

void taxiAppHeader() {
    cout << "***************************************\n";
    cout << "          TAXI! BOOKING SYSTEM         \n";
    cout << "***************************************\n\n";
}

void logIn(){

    cout << "***************************************\n";
    cout << "                 LOG IN               \n";
    cout << "***************************************\n\n";

    string accountStatus;


    cout << "Enter email: "; cin >> email;
    cout << "Enter password: "; cin >> password;
    cout << "\n";

    ifstream read("users/" + email + ".txt");
    getline(read, em);
    getline(read, pw);
    getline(read, status);
    getline(read, accountStatus);
  
    if (em == email && pw == password && accountStatus == "Suspended") {
        cout << "Your account has been suspended. Please contact customer service at 0800 777 to resolve this issue.\n\n";
        system("pause");
        main();
    }

    else {

        if (em == email && pw == password && status == "customer") {
            isCustomer();
        }
        else if (em == email && pw == password && status == "admin") {
            isAdmin();
        }
        else if (em == email && pw == password && status == "employee") {
            isEmployee();
        }
        else {
            cout << "Failed! Username & password does not match or user doesn't exist.\n\n" << endl;
            system("pause");
            main();
        }
    }

    read.close();
    
}

void isCustomer() {

    system("cls"); // clearing so login password is cleared from screen

    taxiAppHeader();

    cout << "Welcome Customer!\n\n";

    cout << "Lucy to create Customer dashboard.\n\n";

    system("pause");
    main();
}

void isAdmin() {

    system("cls"); // clearing so login password is cleared from screen

    taxiAppHeader();

    cout << "Welcome Admin!\n\n";

    adminMenu();
}

void isEmployee() {

    system("cls"); // clearing so login password is cleared from screen

    taxiAppHeader();

    cout << "Welcome Employee!\n\n";

    cout << "Josh to create Employee dashboard.\n\n";

    system("pause");
    main();
}

void addCustomer() {

    cout << "***************************************\n";
    cout << "                REGISTER               \n";
    cout << "***************************************\n\n";

    string customerName, email, password, address, phoneNo, creditCardNo;
        cout << "Enter your name: "; getline(cin >> ws, customerName);
        cout << "Enter your email: "; cin >> email;
        cout << "Enter your password: "; cin >> password;
        cout << "Enter your address: "; getline(cin >> ws, address);
        cout << "Enter your phone number: "; cin >> phoneNo;
        cout << "Enter your credit card number: "; cin >> creditCardNo;

        ofstream file;
        file.open("users/" + email + ".txt");
        file << email << endl << password << endl << "customer" << endl << "Active" << endl << customerName << endl << address << endl << phoneNo << endl << creditCardNo;
        file.close();

        cout << "\nRegistration successful!\n\n";
        system("pause");
        main();
}

////////////////////////// ADMIN FUNCTIONS ////////////////////////// 
void adminMenu() {
    bool choiceInvalid = false;
    int choice;

    do {
        cout << "***************************************\n";
        cout << "               ADMIN MENU              \n";
        cout << "***************************************\n";
            
        cout <<"\n1: View complaints \n2: View lost item reports \n3: Unsuspend account \n4: Log Out \n\nYour choice : ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
        case 1: displayComplaints(); break;
        case 2: displayLostItemReports(); break;
        case 3: unsuspendAccount(); break;
        case 4: logOut(); break;
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
    string name, role, date, complaintDesc, status, drivername, driveremail, driverphone, customername, customeremail, customerphone, tempString;


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
        getline(inputString, drivername, ',');
        getline(inputString, driveremail, ',');
        getline(inputString, driverphone, ',');
        getline(inputString, customername, ',');
        getline(inputString, customeremail, ',');
        getline(inputString, customerphone, ',');

        ComplaintsRecord complaint(complaintNo, name, role, date, complaintDesc, status, drivername, driveremail, driverphone, customername, customeremail, customerphone);
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
                        cout << "What would you like to do about this complaint? \n\n1: Contact the driver and customer \n2: Suspend the driver \n3: Suspend the customer  \n4: Mark as Resolved \n5: Go back to Complaints list \n6: Go back to Admin Menu \n\nYour choice: ";
                        cin >> choice;
                        cout << "\n";
   
                        switch (choice) {
                        case 1: 
                                c.driverDetailsDisplay();
                                c.customerDetailsDisplay(); 
                                complaintsSubmenu();
                                break;
                        case 2:
                                suspendAccount(c.DriverEmail);
                                complaintsSubmenu();
                                break;
                        case 3:
                                suspendAccount(c.CustomerEmail);
                                complaintsSubmenu();
                                break;
                        case 4: 
                               resolveComplaint(c);
                               complaintsSubmenu();
                               break;
                        case 5: 
                                displayComplaints(); break;
                        case 6:
                                adminMenu(); break;
                        default:
                                cout << "Invalid choice\n\n";
                                choiceInvalid = true;
                        }
                    } while (choiceInvalid == true);

                }
                else { 
                        complaintDoesNotExist = true;
                }
            }

            if (complaintDoesNotExist == true) {
                cout << "\nComplaint no. " << complaintNumInput << " does not exist. Please choose a valid Complaint no. : ";
            }

    } while (complaintDoesNotExist == true);


}

void complaintsSubmenu() {

    bool choiceInvalid = false;
    int choice;

    do {
        cout << "What would you like to do next? \n\n1: Go back to complaints list \n2: Go back to Admin Menu \n\nYour choice: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
        case 1:
            displayComplaints(); break;
        case 2:
            adminMenu(); break;
        default:
            cout << "Invalid choice\n\n";
            choiceInvalid = true;
        }
    } while (choiceInvalid == true);
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
    if (rename("complaintsNew.csv", "complaints.csv") != 0) {
    }

}

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
    string name, date, lostitemDesc, status, drivername, driveremail, driverphone, customername, customeremail, customerphone, tempString;


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
        getline(inputString, drivername, ',');
        getline(inputString, driveremail, ',');
        getline(inputString, driverphone, ',');
        getline(inputString, customername, ',');
        getline(inputString, customeremail, ',');
        getline(inputString, customerphone, ',');

        LostItemsReport lostItem(lostItemReportNo, name, date, lostitemDesc, status, drivername, driveremail, driverphone, customername, customeremail, customerphone);
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
                        l.driverDetailsDisplay();
                        l.customerDetailsDisplay();
                        lostItemsReportSubmenu();
                        break;
                    case 2:
                        resolveLostItemsReport(l);
                        lostItemsReportSubmenu();
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


            }
            else {
                reportDoesNotExist = true;
            }
        }

        if (reportDoesNotExist == true) {
        cout << "\nLost Item Report no. " << lostItemNumInput << " does not exist. Please choose a valid Lost Item Report no. : ";
        }

    } while (reportDoesNotExist == true);



}

void lostItemsReportSubmenu() {

    bool choiceInvalid = false;
    int choice;

    do {
        cout << "What would you like to do next? \n\n1: Go back to Lost Items list \n2: Go back to Admin Menu \n\nYour choice: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
        case 1:
            displayLostItemReports(); break;
        case 2:
            adminMenu(); break;
        default:
            cout << "Invalid choice\n\n";
            choiceInvalid = true;
        }
    } while (choiceInvalid == true);
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
    if (rename("lostitemsNew.csv", "lostitems.csv") != 0) {
    }
}

void suspendAccount(string email) {

    // source: https://stackoverflow.com/questions/9505085/replace-a-line-in-text-file

        string strReplace = "Active";
        string strNew = "Suspended";
        ifstream filein("users/" + email + ".txt"); //File to read from
        ofstream fileout("users/" + email + "New.txt"); //Temporary file
        if (!filein || !fileout)
        {
            cout << "\nAccount does not exist!\n" << endl;
        }

        string strTemp;
        //bool found = false;
        while (filein >> strTemp)
        {
            if (strTemp == strReplace) {
                strTemp = strNew;
                
                //found = true;
            }
            strTemp += "\n";
            fileout << strTemp;
            //if(found) break;
        }

        filein.close();
        fileout.close();

        string oldFile = "users/"+email + ".txt";
        string newFile = "users/"+email + "New.txt";

        //have to use .c_str() here because the remove and rename functions appear to only accept char arrays.
        //However, the way we concatenate strings above means they are just strings.
        remove(oldFile.c_str());
        if (rename(newFile.c_str(), oldFile.c_str()) != 0) {
        }

        cout << email << " has been suspended.\n\n";




}

void unsuspendAccount() {

    cout << "***************************************\n";
    cout << "           UNSUSPEND ACCOUNT           \n";
    cout << "***************************************\n\n";

    string email;

    cout << "Enter email to reactivate: ";
    cin >> email;

    // source: https://stackoverflow.com/questions/9505085/replace-a-line-in-text-file

    string strReplace = "Suspended";
    string strNew = "Active";
    ifstream filein("users/" + email + ".txt"); //File to read from
    ofstream fileout("users/" + email + "New.txt"); //Temporary file
    if (!filein || !fileout)
    {
        cout << "\nAccount does not exist!\n" << endl;
    }

    string strTemp;
    //bool found = false;
    while (filein >> strTemp)
    {
        if (strTemp == strReplace) {
            strTemp = strNew;
            //found = true;

        }
        strTemp += "\n";
        fileout << strTemp;
        //if(found) break;
    }

    filein.close();
    fileout.close();

    string oldFile = "users/" + email + ".txt";
    string newFile = "users/" + email + "New.txt";

    //have to use .c_str() here because the remove and rename functions appear to only accept char arrays.
    //However, the way we concatenate strings above means they are just strings.
    remove(oldFile.c_str());
    if (rename(newFile.c_str(), oldFile.c_str()) != 0) {
    }
   

    cout << "\n" << email << " has been reactivated.\n\n";


    bool choiceInvalid = false;
    int choice;

    do {
        cout << "What would you like to do next? \n\n1: Unsuspend another account \n2: Go back to Admin Menu \n\nYour choice: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
        case 1:
            unsuspendAccount(); break;
        case 2:
            adminMenu(); break;
        default:
        cout << "Invalid choice\n\n";
        choiceInvalid = true;
        }
    } while (choiceInvalid == true);

 

    

}

////////////////////////// END ADMIN FUNCTIONS ////////////////////////// 

////////////////////////// LOG OUT ////////////////////////// 

void logOut() {

    system("cls");
    taxiAppHeader();
    cout << "You've logged out. Bye!\n\n";
    system("pause");
    main();



}




////////////////////////// END LOG OUT ////////////////////////// 