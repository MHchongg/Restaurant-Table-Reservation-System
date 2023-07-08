#include <iostream>
#include <fstream>
#include <windows.h>
#include <cctype>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

string opt = "0";
string opt2;
string line;
string checkName;
int age2;
string gender2;
string phoneNum2;
const int table_count = 15;

struct HTableforTables {
  bool reserved;
  string status;
};

//Linked list
class Node{

    public:
    int bookingnum;
    string name;
    int age;
    string gender;
    string phonenum;
    int tablenum;
    Node *next;  //pointer to next node in singly linked list
};

//swap function
Node* swap(Node* ptr1, Node* ptr2){

    Node* tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}

//Bubble sort function
int BubbleSort(Node** head, int count){

    Node** h;
    int i, j, swapped;

    for (i = 0 ; i < count ; i++){

        h = head;
        swapped = 0;
        for (j = 0 ; j < count  - i -1 ; j++){

            Node* p1 = *h;
            Node* p2 = p1->next;
            if (p1->tablenum > p2->tablenum){

                *h = swap(p1, p2);
                swapped = 1;
            }

            h = &(*h)->next;
        }

        if (swapped == 0){
            break;
        }
    }
}

void printList(Node* n){

    while (n != NULL){

        cout << endl << setw(9) << n->bookingnum << setw(18) << n->tablenum << setw(24) << n->name << setw(18) << n->age << setw(15) << n->gender << setw(24) << n->phonenum << endl;
        n = n->next;
    }
    cout << endl;
}

void add(Node** head, int bookingnum,string name, int age, string gender, string phonenum, int tablenum){

    Node* ptr1 = new Node;

    ptr1->bookingnum = bookingnum;
    ptr1->name = name;
    ptr1->age = age;
    ptr1->gender = gender;
    ptr1->phonenum = phonenum;
    ptr1->tablenum = tablenum;
    ptr1->next = *head;
    *head = ptr1;
}

class User{

    public:
        int bookingNum;
        int tableNum;
        string name;
        string phoneNum;
        string gender;
        int age;
        string password;
        void View();
        void Book();
        void Edit();
        void Cancel();
        void Logout();
        void Menu();
        void Login();
        void Register();
        int GenerateUniqueNum();
};

void User :: Register(){

    system("cls");

    fstream file;
    file.open("Authentication.txt", ios::app | ios::out);

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
        file.close();
    }
    else{

        cout << "\t\t-----Register-----" << endl;
        cout << endl << "\tPlease enter your name: ";
        cin >> name;
        cout << endl << "\tPlease enter your password: ";
        cin >> password;
        cout << endl << "\tPlease enter your age: ";
        cin >> age;

        gender = "A";
        while(gender != "M" && gender != "F"){
            cout << endl << "\tPlease enter your gender (M/F): ";
            cin >> gender;
            transform(gender.begin(), gender.end(), gender.begin(), ::toupper);

            if(gender != "M" && gender != "F"){
                cout << "\tInvalid input. Please try again";
            }
        }

        phoneNum = "1";
        while(phoneNum.length() > 10 || phoneNum.length() <= 9){
            cout << endl << "\tPlease enter your phone number: ";
            cin >> phoneNum;

            if(phoneNum.length() > 10 || phoneNum.length() <= 9){
                cout << "\tInvalid input. Please try again";
            }
        }

        file << name << " " << password << " " << age << " " << gender << " " << phoneNum << endl;

        file.close();

        cout << "\n\tYour information is saved successfully.";
        Sleep(1000);

    }
    opt = "0";
}

void User :: View(){

    system("cls");
    bool check = false;
    fstream file;
    file.open("Booking.txt");

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
        file.close();
    }
    else{
        int i = 1;
        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        while(getline(file, line)){
            if(checkName == name){
                check = true;
                if(i == 1){
                    cout << "\n\t\t\t\t\t\t  Booking Details " << endl;
                    cout << "\n -------------------------------------------------------------------------------------------------------------";
                    cout << "\n ||  Booking No  ||       Name        ||    Age    ||    Gender    ||    Phone Number    ||    Table Num    ||";
                    cout << "\n -------------------------------------------------------------------------------------------------------------";
                }

                cout << endl << i << setw(9) << bookingNum << setw(20) << name << setw(16) << age << setw(13) << gender << setw(25) << phoneNum << setw(15) << tableNum << endl;
                i++;
            }
            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        }
        if(!check){
            cout << "\n\n\t\tNo order yet";
        }
        file.close();
    }

    cout << endl << "\n\n\t\tDo you want back to Menu (Y/n) : ";
    cin >> opt2;
    transform(opt2.begin(), opt2.end(), opt2.begin(), ::tolower);

    if(opt2 == "y"){
        cout << "\nReturning to Menu.....";
        Menu();
    }
    else{
        View();
    }
}

void User :: Book(){

    system("cls");
    unordered_map<int, HTableforTables> tables;
    int option;
    int n = 100;

    fstream file;

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
        file.close();
    }
    else{
        file.open("Booking.txt");
        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;

        while(getline(file,line)){

            for(int i = 1 ; i <= table_count ; i++){
                if(i == tableNum){
                    tables[i].reserved = true;
                    tables[i].status = "No available";
                }
            }

            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        }
        file.close();

        cout << "------Select your wanted table and book a new table------" << endl << endl;
        for(int i = 1 ; i <= table_count ; i++){
            cout << "Table [" << i << "] : ";
            if(tables[i].reserved){
                cout << tables[i].status << endl;
            }
            else{
                cout << "Available" << endl;
            }
        }
        cout << endl << endl << "Your option :";
        cin >> option;

        cout << endl << "Are you confirm to book the table? (y/n) :";
        cin >> opt2;
        transform(opt2.begin(), opt2.end(), opt2.begin(), ::tolower);

        if(opt2 == "y"){
            if(tables[option].reserved || option > table_count){
                cout << "The table is unavailable or input is larger than total number of tables";
                cout << endl << "Please try again";
                Sleep(2000);
            }
            else{

                file.open("Booking.txt", ios::app | ios::out);

                file << GenerateUniqueNum() << " " << checkName << " " << age2 << " " << gender2 << " " << phoneNum2 << " " << option << endl;
                file.close();

                cout << "The booking is added successfully...";
                Sleep(1000);
            }
        }
        else{
            Book();
        }
    }
    Menu();
}

void User :: Edit(){

    system("cls");

    unordered_map<int, HTableforTables> tables;
    int tableNum2;
    bool check;
    int bookingNum2;
    fstream file,file2;

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
        file.close();
    }
    else{
        int i = 1;
        file.open("Booking.txt", ios::in);
        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        while(getline(file, line)){
            if(checkName == name){
                check = true;
                if(i == 1){
                    cout << "\n\t\t\t\t   Booking Details " << endl;
                    cout << "\n\t\t ----------------------------------------------------------";
                    cout << "\n\t\t ||  Booking No  ||       Name        ||    Table Num    ||";
                    cout << "\n\t\t ----------------------------------------------------------";
                }

                cout << endl << "\t\t" << i << "." << setw(9) << bookingNum << setw(20) << name << setw(17) << tableNum << endl;
                i++;
            }
            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        }
        file.close();

        if(!check){
            cout << "\n\n\t\tNo order yet";
            cout << "\n\n\t\tBack to Menu...";
            Sleep(1000);
        }
        else{

            bool check2 = false;

            cout << "\n\t\tPlease enter the booking number you want to edit :";
            cin >> bookingNum2;

            file.open("Booking.txt",ios::in);
            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;

            while(getline(file,line)){

                if(checkName == name && bookingNum2 == bookingNum){
                    check2 = true;
                    tableNum2 = tableNum;
                }

                file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
            }
            file.close();

            if(!check2){
                cout << "\n\t\tInvalid booking number! Please try again.";
                Sleep(2000);
            }
            else{
                int tableNum3;

                file.open("Booking.txt", ios::in);
                file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;

                while(getline(file,line)){

                    for(int i = 1 ; i <= table_count ; i++){
                        if(i == tableNum){
                            tables[i].reserved = true;
                            tables[i].status = "No available";
                        }
                    }
                    file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
                }
                file.close();

                system("cls");
                cout << "\n\t\t------Tables status------" << endl;
                for(int i = 1 ; i <= table_count ; i++){
                    cout << "\t\tTable [" << i << "] : ";
                    if(tables[i].reserved){
                        cout << tables[i].status << endl;
                    }
                    else{
                        cout << "Available" << endl;
                    }
                }

                cout << "\n\t\tEnter the new table number :";
                cin >> tableNum3;
                if(tableNum3 > 15 || tableNum3 <= 0){
                    cout << "\t\tInvalid table number. Please try again.";
                    Sleep(1000);
                }
                else if(tables[tableNum3].reserved){
                    cout << "\t\tThe table is unavailable. Please try again. ";
                    Sleep(1000);
                }
                else{

                    cout << "\t\tTable Number " << tableNum2 << " change to Table Number " << tableNum3;

                    file.open("Booking.txt", ios::in);
                    file2.open("tmp.txt", ios::app | ios::out);
                    file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
                    while(getline(file,line)){

                        if(bookingNum2 != bookingNum){
                            file2 << bookingNum << " " << name << " " << age << " " << gender << " " << phoneNum << " " << tableNum << endl;
                        }
                        else if (bookingNum2 == bookingNum){
                            file2 << bookingNum << " " << name << " " << age << " " << gender << " " << phoneNum << " " << tableNum3 << endl;
                        }

                        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
                    }

                    cout << "\n\t\t Edit successfully...";

                    file.close();
                    file2.close();

                    remove("Booking.txt");
                    rename("tmp.txt","Booking.txt");

                    cout << "\n\t\t Back to Menu...";
                    Sleep(2500);
                }
            }
        }
    }
    Menu();
}

void User :: Cancel(){

    system("cls");
    int bookingNum2;
    bool check = false;
    bool check2 = false;

    fstream file,file2;

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
        file.close();
    }
    else{
        int i = 1;
        file.open("Booking.txt", ios::in);
        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        while(getline(file, line)){
            if(checkName == name){
                check = true;
                if(i == 1){
                    cout << "\n\t\t\t\t\t\t   Booking Details " << endl;
                    cout << "\n -------------------------------------------------------------------------------------------------------------";
                    cout << "\n ||  Booking No  ||       Name        ||    Age    ||    Gender    ||    Phone Number    ||    Table Num    ||";
                    cout << "\n -------------------------------------------------------------------------------------------------------------";
                }

                cout << endl << i << setw(9) << bookingNum << setw(20) << name << setw(17) << age << setw(13) << gender << setw(25) << phoneNum << setw(15) << tableNum << endl;
                i++;
            }
                file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        }
        file.close();
        if(!check){
            cout << "\n\n\t\tNo order yet";
            cout << "\n\n\t\t Go back to Menu...";
            Sleep(1000);
        }
        else{

            cout << "\n\n\tPlease enter the booking number you want to cancel :";
            cin >> bookingNum2;

            file.open("Booking.txt",ios::in);
            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;

            while(getline(file,line)){

                if(checkName == name && bookingNum2 == bookingNum){
                    check2 = true;
                }

                file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
            }
            file.close();

            if(!check2){
                file2.close();
                cout << "\n\tInvalid booking number! Please try again.";
                Sleep(2000);
            }
            else{

                file.open("Booking.txt", ios::in);
                file2.open("tmp.txt",ios::app | ios::out);
                file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
                while(getline(file,line)){

                    if(bookingNum2 != bookingNum){
                        file2 << bookingNum << " " << name << " " << age << " " << gender << " " << phoneNum << " " << tableNum << endl;
                    }

                    file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
                }

                cout << "\n\tCancel successfully";

                file.close();
                file2.close();

                remove("Booking.txt");
                rename("tmp.txt","Booking.txt");

                cout << "\n\tBack to Menu.....";
                Sleep(1000);
            }
        }
        Menu();
    }
}

void User :: Logout(){

    system("cls");
    cout << "\n\t\t Are you sure you want to log out? (Y/Press any key to back to Menu) :";
    cin >> opt2;
    transform(opt2.begin(), opt2.end(), opt2.begin(), ::tolower);
    if(opt2 == "y"){
        opt = "0";
        cout << "\n\t\t Log out successfully.....";
        Sleep(1000);
    }
    else{
        Menu();
    }
}

void User :: Menu(){

    string selection;

    system("cls");
    cout << "\n\t\t Menu" << "\n-----------------------------------------";
    cout << "\n\t[1] View \n\t[2] Book \n\t[3] Edit \n\t[4] Cancel \n\t[5] Log out";
    cout << "\n---------------------------------------------";
    cout << "\n\t Please enter your choice : ";
    cin >> selection;

    if(selection == "1"){
        View();
    }
    else if(selection == "2"){
        Book();
    }
    else if(selection == "3"){
        Edit();
    }
    else if(selection == "4"){
        Cancel();
    }
    else if(selection == "5"){
        Logout();
    }
    else{
        cout << "\n\t Invalid input, please try again ";
        Sleep(1500);
        Menu();
    }
}

void User :: Login(){

    system("cls");
    fstream file;
    file.open("Authentication.txt");
    string name2;
    string password2;
    bool check = false;

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
        file.close();
    }
    else{
        cout << "\n\t\t Please enter your username : ";
        cin >> name2;
        cout << "\n\t\t Please enter your password : ";
        cin >> password2;

        if(!file){
            cout << "Error: file could not be opened!";
            Sleep(1000);
            file.close();
        }
        else{

            file >> name >> password >> age >> gender >> phoneNum;
            while(getline(file,line)){
                if(name2 == name){
                    age2 = age;
                    gender2 = gender;
                    phoneNum2 = phoneNum;
                }
                file >> name >> password >> age >> gender >> phoneNum;
            }
            file.close();
        }

        file.open("Authentication.txt");

        file >> name >> password >> age >> gender >> phoneNum;
        while(getline(file,line)){
            if(name2 == name && password2 == password){
                checkName = name2;
                cout << "\n\n\t\t\tLogin successfully...";
                Sleep(1000);
                Menu();
                check = true;
            }
            file >> name >> password >> age >> gender >> phoneNum;
        }
        file.close();
        if(!check){
            cout << "\n\t\tNo matching record. Please try again." << endl;
            Sleep(1000);
            cout << "\n\t\tDo you want to back to previous page? (y/n) :";
            cin >> opt2;
            transform(opt2.begin(), opt2.end(), opt2.begin(), ::tolower);
            if(opt2 == "y"){
                opt = "0";
            }
            else{
                Login();
            }
        }
    }
}

//Recursive function to generate an unique booking number
int User :: GenerateUniqueNum(){

    vector<int> bookingNumbers;
    vector<int>::iterator test;
    fstream file;
    int num;

    file.open("Booking.txt",ios::in);

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
    }
    else{

        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        while(getline(file,line)){

            bookingNumbers.push_back(bookingNum);

            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        }
        file.close();

        num = (rand() % 100)+1;

        test = find (bookingNumbers.begin(), bookingNumbers.end(), num);

        if(test != bookingNumbers.end()){
            bookingNumbers.clear();
            return GenerateUniqueNum();
        }
        else{
            return num;
        }
    }
}

class Admin : public User{

    private:
        string password;
    public:
        void ViewCusInfo();
        void Search();
        void Login();
        void Menu();
        void Edit();
        void ViewTableStatus();
        void Cancel();
};

void Admin :: ViewCusInfo(){

    system("cls");
    int num = 1;
    int sizeoflist = 0;
    Node* head = NULL;

    fstream file;

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
        file.close();
    }
    else{
        file.open("Booking.txt", ios::in);
        cout << "\n\t\t\t\t\t   Booking Details " << endl;
        cout << "\n --------------------------------------------------------------------------------------------------------------";
        cout << "\n ||  Booking No  ||    Table Num    ||  ||       Name        ||    Age    ||    Gender    ||    Phone Number ||";
        cout << "\n --------------------------------------------------------------------------------------------------------------";

        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        while(getline(file, line)){
            sizeoflist++;
            add(&head, bookingNum, name, age, gender, phoneNum, tableNum);
            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        }
        file.close();

        BubbleSort(&head,sizeoflist);
        printList(head);
    }

    cout << "\n\nPress 'y' to return to menu : ";
    cin >> opt2;
    transform(opt2.begin(), opt2.end(), opt2.begin(), ::tolower);

    if(opt2 == "y"){
        cout << "\nReturning to Menu.....";
        Menu();
    }
    else{
        cout << "Invalid input!";
        Sleep(350);
        ViewCusInfo();
    }
}

void Admin :: ViewTableStatus(){
    system("cls");
    unordered_map<int, HTableforTables> tables;

    fstream file;

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
        file.close();
    }
    else{
        file.open("Booking.txt");
        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;

        while(getline(file,line)){

            for(int i = 1 ; i <= table_count ; i++){
                if(i == tableNum){
                    tables[i].reserved = true;
                    tables[i].status = "No available";
                }
            }
            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        }
        file.close();

        cout << "\n\n\t------Tables Staus------" << endl;
        for(int i = 1 ; i <= table_count ; i++){
            cout << "\tTable [" << i << "] : ";
            if(tables[i].reserved){
                cout << tables[i].status << endl;
            }
            else{
                cout << "Available" << endl;
            }
        }
    }

    cout << endl << "\n\n\tPress y to back to menu :";
    cin >> opt2;
    transform(opt2.begin(), opt2.end(), opt2.begin(), ::tolower);

    if(opt2 == "y"){
        Menu();
    }
    else{
        ViewTableStatus();
    }
}

void Admin :: Search(){

    system("cls");

    bool check = false;
    fstream file;
    file.open("Booking.txt", ios::in);

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
        file.close();
    }
    else{

        string searchname;
        cout << "\n\n\t\tEnter the user's name to display the information of designated user :";
        cin >> searchname;

        cout << "\n\t\t\t\t   Booking Details " << endl;
        cout << "\n -------------------------------------------------------------------------------------------------------------";
        cout << "\n ||  Booking No  ||       Name        ||    Age    ||    Gender    ||    Phone Number    ||    Table Num    ||";
        cout << "\n -------------------------------------------------------------------------------------------------------------";

        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        while(getline(file,line)){

            if(searchname == name){
                int num = 1;
                cout << endl << num << ". " << setw(9) << bookingNum << setw(14) << setw(17) << name << setw(17) << age << setw(13) << gender << setw(25) << phoneNum << setw(15) << tableNum << endl;
                num++;
                check = true;
            }

            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        }
        file.close();
    }

    if(!check){
        cout << "\n\n\t\t The user does not exist, or the user has not booked any tables yet.";
        cout << endl << "\t\t Please try again.";
        Sleep(4000);
    }
    else{

        cout << "\n\t\t Do you want to back to Menu? (y/n) :";
        cin >> opt2;
        transform(opt2.begin(), opt2.end(), opt2.begin(), ::tolower);

        if(opt2 != "y"){
            Search();
        }
    }
    Menu();
}

void Admin :: Edit(){

    system("cls");

    unordered_map<int, HTableforTables> tables;
    int tableNum2;
    fstream file,file2;
    file.open("Booking.txt", ios::in);

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
        file.close();
    }
    else{
        int num = 1;
        int bookingNum2;
        cout << "\n\t\t\t\t\t   Booking Details " << endl;
        cout << "\n\t\t\t ----------------------------------------------------------";
        cout << "\n\t\t\t ||  Booking No  ||       Name        ||    Table Num    ||";
        cout << "\n\t\t\t ----------------------------------------------------------";

        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        while(getline(file, line)){
            cout << endl;
            cout << endl << "\t\t\t" << num << ". " << setw(9) << bookingNum << setw(19) << name << setw(16) << tableNum << endl;
            num++;
            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        }
        file.close();

        cout << "\n\t\t\tEnter booking number you want to edit :";
        cin >> bookingNum2;

        file.open("Booking.txt", ios::in);
        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;

        bool check = false;
        while(getline(file, line)){

            if(bookingNum2 == bookingNum){
                check = true;
                tableNum2 = tableNum;
            }

            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        }
        file.close();

        if(!check){
            cout << "\t\t\t Invalid booking number. Please try again.";
            Sleep(1000);
        }
        else{
            int tableNum3;

            file.open("Booking.txt", ios::in);
            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;

            while(getline(file,line)){

                for(int i = 1 ; i <= table_count ; i++){
                    if(i == tableNum){
                        tables[i].reserved = true;
                        tables[i].status = "No available";
                    }
                }
                file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
            }
            file.close();

            system("cls");
            cout << "\n\n\t\t------Tables Staus------" << endl;
            for(int i = 1 ; i <= table_count ; i++){
                cout << "\t\tTable [" << i << "] : ";
                if(tables[i].reserved){
                    cout << tables[i].status << endl;
                }
                else{
                    cout << "Available" << endl;
                }
            }

            cout << "\n\t\tEnter the new table number :";
            cin >> tableNum3;
            if(tableNum3 > 15 || tableNum3 <= 0){
                cout << "\t\tInvalid table number. Please try again.";
                Sleep(1000);
            }
            else if(tables[tableNum3].reserved){
                cout << "\t\tThe table is unavailable. Please try again. ";
                Sleep(1000);
            }
            else{
                cout << "\t\tTable Number " << tableNum2 << " change to Table Number " << tableNum3;

                file.open("Booking.txt", ios::in);
                file2.open("tmp.txt", ios::app | ios::out);

                file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
                while(getline(file,line)){

                    if(bookingNum2 != bookingNum){
                        file2 << bookingNum << " " << name << " " << age << " " << gender << " " << phoneNum << " " << tableNum << endl;
                    }
                    else if (bookingNum2 == bookingNum){
                        file2 << bookingNum << " " << name << " " << age << " " << gender << " " << phoneNum << " " << tableNum3 << endl;
                    }

                    file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
                }

                cout << "\n\t\t Edit successfully...";

                file.close();
                file2.close();

                remove("Booking.txt");
                rename("tmp.txt","Booking.txt");

                cout << "\n\t\tBack to Menu...";
                Sleep(2000);

            }
        }
    }
    Menu();
}

void Admin :: Cancel(){

    system("cls");
    int num = 1;
    int bookingNum2;
    bool check = false;

    fstream file,file2;
    file.open("Booking.txt", ios::in);

    if(!file){
        cout << "Error: file could not be opened!";
        Sleep(1000);
        file.close();
    }
    else{
        cout << "\n\t\t\t\t\t\t   Booking Details " << endl;
        cout << "\n -------------------------------------------------------------------------------------------------------------";
        cout << "\n ||  Booking No  ||       Name        ||    Age    ||    Gender    ||    Phone Number    ||    Table Num    ||";
        cout << "\n -------------------------------------------------------------------------------------------------------------";

        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        while(getline(file, line)){
            cout << endl;
            cout << endl << num << ". " << setw(9) << bookingNum << setw(14) << setw(17) << name << setw(17) << age << setw(13) << gender << setw(25) << phoneNum << setw(15) << tableNum << endl;
            num++;
            file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
        }
        file.close();
    }

    cout << "\n\t Enter the booking number to delete the reservation: ";
    cin >> bookingNum2;

    file.open("Booking.txt",ios::in);
    file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
    while(getline(file, line)){

        if(bookingNum2 == bookingNum){
            check = true;
        }

        file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
    }

    file.close();

    if(!check){
        cout << "\n\t Invalid booking number! Please try again.";
        Sleep(1000);
    }
    else{

        cout << "\n\t Are you sure you want to delete? (y/n) : ";
        cin >> opt2;
        transform(opt2.begin(), opt2.end(), opt2.begin(), ::tolower);

        if(opt2 == "y"){
            file.open("Booking.txt", ios::in);
            file2.open("tmp.txt", ios::app | ios::out);

            if(!file){
                cout << "Error: file could not be openend!";
                Sleep(1000);
                file.close();
            }
            else{
                file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;

                while(getline(file,line)){

                    if(bookingNum2 != bookingNum){
                        file2 << bookingNum << " " << name << " " << age << " " << gender << " " << phoneNum << " " << tableNum << endl;
                    }

                    file >> bookingNum >> name >> age >> gender >> phoneNum >> tableNum;
                }

                cout << "\n\tCancel successfully...";

                file.close();
                file2.close();

                remove("Booking.txt");
                rename("tmp.txt","Booking.txt");

                cout << "\n\tBack to Menu...";
                Sleep(1000);
            }
        }
        else{
            cout << "\n\tBack to Menu...";
            Sleep(1000);
        }
    }
    Menu();
}

void Admin :: Login(){

    system("cls");
    cout << "\n\t\t Please enter password : ";
    cin >> password;

    if (password == "admin"){
        cout << "\n\t\t Login successfully.....";
        Sleep(1500);
        Menu();
    }
    else{
        cout << "\n\t\t Incorrect password, please try again";
        cout << "\n\n\t\t Or you want to back to previous step (Y/Press any key to log in) : ";
        cin >> opt2;
        transform(opt2.begin(), opt2.end(), opt2.begin(), ::tolower);
        if(opt2 == "y"){
            opt = "0";
        }
        else{
            Login();
        }
    }
}

void Admin :: Menu(){

    string selection;

    system("cls");
    cout << "\n\t\t Menu" << endl << "-----------------------------------------";
    cout << "\n\t[1] View Customer information \n\t[2] Search \n\t[3] Edit \n\t[4] Cancel \n\t[5] View Tables status \n\t[6] Log out";
    cout << endl << "-----------------------------------------";
    cout << endl << "\t Please enter your choice : ";
    cin >> selection;

    if(selection == "1"){
        ViewCusInfo();
    }
    else if(selection == "2"){
        Search();
    }
    else if(selection == "3"){
        Edit();
    }
    else if(selection == "4"){
        Cancel();
    }
    else if(selection == "5"){
        ViewTableStatus();
    }
    else if(selection == "6"){
        Logout();
    }
    else{
        cout << "\n\t Invalid input, please try again";
        Sleep(1500);
        Menu();
    }
}

int main(){

    string choice;
    User u1;
    Admin a1;

    do{
        system("cls");

        cout << "\t\t ------------------------------------------";
        cout << "\n\t\t |  Restaurant Tables Reservation System  |" << endl;
        cout << "\t\t ------------------------------------------";
        cout << "\n\t\t   Please choose your user type or exit " << endl;
        cout << "\n\t\t [1] Normal User [2] Admin  [3] Register [4] Exit: ";
        cin >> choice;

        if(choice == "1"){
            opt = "-1";
            u1.Login();
        }
        else if(choice == "2"){
            opt = "-1";
            a1.Login();
        }
        else if(choice == "3"){
            opt = "-1";
            u1.Register();
        }
        else if(choice == "4"){
            opt = "-1";
            system("cls");
            cout << "\n\t\t ----------------------------------";
            cout << "\n\t\t |  Thanks for using this system  | ";
            cout << "\n\t\t ----------------------------------\n";
            Sleep(200);
        }
        else{
            cout << "\n\t\t Invalid input, please try again";
            Sleep(1500);
        }

    } while(opt == "0");

    return 0;
}
