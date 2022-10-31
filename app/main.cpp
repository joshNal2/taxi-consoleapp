#include <iostream>

#include <fstream>

#include <string>

using namespace std;

string email, password, em, pw, status;
void logIn();
void isCustomer();
void isAdmin();
void isEmployee();
void addCustomer();
void employeeMenu();
void taxiAppHeader();
void displayTrips();
void logOut();
void acceptTrip();
void findTrip();
void completeTrip();
void cancelTrip();
void employeeComplaint();
void employeeTripComplete();
void complaintFiled();

int main(void) {

  int choice = 0;
  bool choiceInvalid = false;
  bool isNumeric;
  string stringValue;

  taxiAppHeader();
  cout << "Welcome to Taxi! Booking System where \nyou can securely book a taxi whenever \nand wherever you need it. We pride \nourselves in using only electric \nvehicles, enabling us to provide you \nwith cheaper fares while at the same \ntime being nice to planet! Customer \nsafety is very important to us, all our \ndrivers go through a thorough security \ncheck so rest assured you are in safe \nhands! \n\nPrefer calling? Phone 0800 777 \nto talk to one of our friendly customer \nservice!\n\n";
  do {
    cout << "1: Register\n2: Login\n3: Close Application\n\nYour choice: ";

    if (cin >> choice) {
      isNumeric = true;
    } else {
      isNumeric = false;
      cin.clear();
      if (!(cin >> stringValue)) {}
    }

    cout << "\n";

    switch (choice) {
    case 1:
      addCustomer();
      main();
      break;
    case 2:
      logIn();
      break;
    case 3:
      return 0;
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

//LOG IN

void logIn() {
  cout << "Enter email: ";
  cin >> email;
  cout << "Enter password: ";
  cin >> password;

  ifstream read("users/" + email + ".txt");
  getline(read, em);
  getline(read, pw);
  getline(read, status);

  if (em == email && pw == password && status == "customer") {
    isCustomer();
  } else if (em == email && pw == password && status == "admin") {
    isAdmin();
  } else if (em == email && pw == password && status == "employee") {
    isEmployee();
  } else {
    cout << "Failed! User doesn't exist." << endl;
    system("pause");
    main();
  }

}

//REGISTER

void addCustomer() {
  string customerName, email, password, address, phoneNo, creditCardNo;
  cout << "Enter your name: ";
  getline(cin >> ws, customerName);
  cout << "Enter your email: ";
  cin >> email;
  cout << "Enter your password: ";
  cin >> password;
  cout << "Enter your address: ";
  getline(cin >> ws, address);
  cout << "Enter your phone number: ";
  cin >> phoneNo;
  cout << "Enter your credit card number: ";
  cin >> creditCardNo;

  ofstream file;
  file.open("users/" + email + ".txt");
  file << email << endl << password << endl << "customer" << endl << customerName << endl << address << endl << phoneNo << endl << creditCardNo;
  file.close();
}

//CUSTOMER FUNCTIONS - Email: a Password: a

void isCustomer() {
  system("cls");
  cout << "Succesfully logged in! Customer" << endl;
}

//ADMIN FUNCTIONS - Email: a Password: a

void isAdmin() {
  system("cls");
  cout << "Succesfully logged in! Admin" << endl;

}

//EMPLOYEE FUNCTIONS - Email: e Password: e

void isEmployee() {
  system("cls");
  cout << "***************************************\n";
  cout << "           WELCOME EMPLOYEE!           \n";
  cout << "***************************************\n";
  employeeMenu();
}

void employeeMenu() {
  int choice;
  bool choiceInvalid = false;
  bool isNumeric;
  string stringValue;

  do {
    cout << "1: View nearby trip bookings.\n2: Log Out\n\nYour choice: ";

    if (cin >> choice) {
      isNumeric = true;
    } else {
      isNumeric = false;
      cin.clear();
      if (!(cin >> stringValue)) {}
    }

    cout << "\n";
    switch (choice) {
    case 1:
      displayTrips();
      break;

    case 2:
      logOut();
      break;

    default:
      cout << "Invalid choice\n\n";
      choiceInvalid = true;
    }
  } while (choiceInvalid == true);
}

void findTrips() {
  int choice;
  bool choiceInvalid = false;
  bool isNumeric;
  string stringValue;

  do {
    system("cls");
    cout << "Would you like to be notified of nearby trips?" << endl;
    cout << "1: Yes\n2: No\n3: Log Out\n\nYour choice: ";

    if (cin >> choice) {
      isNumeric = true;
    } else {
      isNumeric = false;
      cin.clear();
      if (!(cin >> stringValue)) {}
    }

    switch (choice) {
    case 1:
      displayTrips();
      break;
    case 2:
      employeeMenu();
      break;
    case 3:
      logOut();
      break;
    default:
      cout << "Invalid choice\n\n";
      choiceInvalid = true;
    }
  } while (choiceInvalid == true);
}

void displayTrips() {
  int choice;
  bool choiceInvalid = false;
  bool isNumeric;
  string stringValue;

  do {
    system("cls");
    cout << "***************************************\n";
    cout << "          Trip found nearby!             " << endl;
    cout << "***************************************\n";
    cout << "Customer name: John Doe" << endl;
    cout << "Pick Up Location: 23 Example Place" << endl;
    cout << "Drop Off Location: 42 Example Road" << endl;
    cout << "\nWould you like to take this trip?" << endl;
    cout << "1: Yes\n2: No\n\nYour choice: ";

    if (cin >> choice) {
      isNumeric = true;
    } else {
      isNumeric = false;
      cin.clear();
      if (!(cin >> stringValue)) {}
    }

    switch (choice) {
    case 1:
      acceptTrip();
      break;
    case 2:
      employeeMenu();
      break;
    default:
      cout << "Invalid choice\n\n";
      choiceInvalid = true;
    }
  } while (choiceInvalid == true);
}

void acceptTrip() {
  int choice;
  bool choiceInvalid = false;
  bool isNumeric;
  string stringValue;

  do {
    system("cls");
    cout << "***************************************\n";
    cout << "          Trip has started.             " << endl;
    cout << "***************************************\n";
    cout << "1: Complete Trip\n2: Cancel Trip\n\nYour choice: ";

    if (cin >> choice) {
      isNumeric = true;
    } else {
      isNumeric = false;
      cin.clear();
      if (!(cin >> stringValue)) {}
    }

    switch (choice) {
    case 1:
      completeTrip();
      break;
    case 2:
      cancelTrip();
      break;
    default:
      cout << "Invalid choice\n\n";
      choiceInvalid = true;
    }
  } while (choiceInvalid == true);
}

void completeTrip() {
  int choice;
  bool choiceInvalid = false;
  bool isNumeric;
  string stringValue;

  do {
    cout << "\n***************************************\n";
    cout << "             Trip complete!             " << endl;
    cout << "***************************************\n";
    cout << "\nWould you like to log a complaint?\n";
    cout << "1: Yes\n2: No\n\nYour choice: ";

    if (cin >> choice) {
      isNumeric = true;
    } else {
      isNumeric = false;
      cin.clear();
      if (!(cin >> stringValue)) {}
    }

    switch (choice) {
    case 1:
      employeeComplaint();
      break;
    case 2:
      employeeTripComplete();
      break;
    default:
      cout << "Invalid choice\n\n";
      choiceInvalid = true;
    }
  } while (choiceInvalid == true);
}

void cancelTrip() {
  int choice;
  bool choiceInvalid = false;
  bool isNumeric;
  string stringValue;

  do {
    cout << "\n***************************************\n";
    cout << "             Trip canceled.             " << endl;
    cout << "***************************************\n";
    cout << "\nWould you like to log a complaint?\n";
    cout << "1: Yes\n2: No\n\nYour choice: ";

    if (cin >> choice) {
      isNumeric = true;
    } else {
      isNumeric = false;
      cin.clear();
      if (!(cin >> stringValue)) {}
    }

    switch (choice) {
    case 1:
      employeeComplaint();
      break;
    case 2:
      employeeTripComplete();
      break;
    default:
      cout << "Invalid choice\n\n";
    }
  } while (choiceInvalid == true);
}

void employeeTripComplete() {
  system("cls");
  taxiAppHeader();
  cout << "Thank you for driving for Taxi!\nYou will be returned to the menu.\n\n";
  system("pause");
  isEmployee();
}

//COMPLAINT FUNCTIONS

void employeeComplaint() {
  string firstName, date, complaintDesc, lastName, role = "Employee";
  cout << "Enter your first name: ";
  cin >> firstName;
  cout << "Enter your last name: ";
  cin >> lastName;
  cout << "What date did the ride take place on? (dd-mm-yyyy): ";
  cin >> date;
  cout << "Complaint: ";
  getline(cin >> ws, complaintDesc);

  ofstream file;
  file.open("complaints/" + firstName + lastName + " " + date + ".txt");
  file << firstName << " " << lastName << endl << role << endl << date << endl << complaintDesc;
  file.close();

  complaintFiled();
}

void complaintFiled() {
  system("cls");
  taxiAppHeader();
  cout << "Complaint has been filed.\nYou will be returned to the menu.\n\n";
  system("pause");
  isEmployee();
}

//LOG OUT

void logOut() {

  system("cls");
  taxiAppHeader();
  cout << "You've logged out. Bye!\n\n";
  system("pause");
  main();
}