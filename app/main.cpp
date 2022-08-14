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

int main(){

    int choice;

    cout << "1: Register\n2: Login\n3: Your choice: "; cin >> choice;
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
    cout << "Succesfully logged in! Admin" << endl;
    system("PAUSE");
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