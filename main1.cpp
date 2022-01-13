//Smart Traffic Management System
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;

#define pass 1234
int i, choice, dd=0, mm=0, yy=0, hr=0, mint=0;

void date_time();

class onlyDisplay{
  public:
    void authentication();
    void menu();    
};

class features{
  public:
    void record_veh();
    void helpline();
};

class vehData {
  private:
    unsigned long long int owner_no;
    int seater, generation, RTO_no;
    char veh_type[10], owner_name[50], des_pat[10], address[100], issued_date[20], veh_no[15];
  public:
    vehData(){strcpy(veh_no, "ABXXXXXXXX");}
    void read_data();
    int store_data();
    void view_data();
    void show_data();
    void header();
    void search_data(char *);
    void delete_data(char *);
    void update_data(char *);
};

void vehData::header() {
  cout << endl;
  cout<<setw(13)<<"Vehicle No"<<setw(15)<<"Vehicle Type"<<setw(18)<<"Owner Name"<<setw(18)<<"Phone Number"<<setw(10)<<"Seater"<<setw(15)<<"Generation"<<setw(10)<<"Fuel"<<setw(10)<<"RTO No"<<setw(20)<<"Issued Date"<<setw(35)<<"Address\n";
  int i;
  for(i=0; i<=170; i++)
    cout << "_";
  cout << endl;
}

void vehData::show_data() {
  cout<<"\n\n"<<setw(13)<<veh_no<<setw(15)<<veh_type<<setw(18)<<owner_name<<setw(18)<<owner_no<<setw(10)<<seater<<setw(15)<<generation<<setw(10)<<des_pat<<setw(10)<<RTO_no<<setw(20)<<issued_date<<setw(35)<<address;
}

int main() {
  onlyDisplay od;
  od.authentication();
  return 0;
}

void features::record_veh() {
  system("clear");
  onlyDisplay d; vehData vh;
  char get[15];
  cout << "\xB2\xB2\xB2\xB2  Choose Option  \xB2\xB2\xB2\xB2"; 
  cout << "\xB2  1. Add a Record"; 
  cout << "\xB2  2. Delete a Record";
  cout << "\xB2  3. Update a Record";
  cout << "\xB2  4. Back to Main Menu";
  while(choice != 4) {
    cout << " Enter your choice : ";
    cin >> choice;
    switch(choice) {
      case 1: {
        vh.read_data();
        vh.store_data();
        break;
      }
      case 2: {
        system("clear");
        cout << "\xB2\xB2 Delete Record \xB2\xB2\n\n";
        cout << "Enter the Vehicle No to delete : ";
        cin.ignore();
        cin.getline(get, 14);
        vh.delete_data(get);
        break;
      }
      case 3: {
        system("clear");
        cout << "\xB2\xB2 Update Record \xB2\xB2\n\n";
        cout << "Enter the Vehicle No to Update : ";
        cin.ignore();
        cin.getline(get, 14);
        vh.update_data(get);
        break;
      }
      case 4: d.menu();
    }
  }
}

int vehData::store_data() {
  features f;
  if(veh_no == 0) {
    cout<<"\nData Not intialized";
//    return 0;
  } else {
    ofstream fout;
    fout.open("file1.dat", ios::app|ios::binary);
    fout.write((char*)this, sizeof(*this));
    fout.close();
    cout << "\n\tData stored Successfully";
//    return 1;
  }
  cout << "\n\tPress any key to continue...\n";
  f.record_veh();
}

void vehData::read_data() {
  system("clear");
  cout << "\xB2\xB2 Please enter the details \xB2\xB2\n\n";
    int type;
  cout << "\n\tVehicle No : ";
    cin.ignore();
    cin.getline(veh_no, 14);
  cout << "\n\t1. Two Wheeler (eg. Bike)\t2. Three Wheeler (eg. Auto)\t3. Four Wheeler (eg. Car)\n\n\tVehicle Type : ";
  cin >> type;
  if(type==1) strcpy(veh_type, "2 Wheeler");
  else if(type==2) strcpy(veh_type, "3 Wheeler");
  else if(type==3) strcpy(veh_type, "4 Wheeler");
  else strcpy(veh_type, "None");
  
  cout << "\tOwner Name: ";
    cin.ignore();
    cin.getline(owner_name, 49);
    cout << "\tMobile No : ";
    cin >> owner_no;
    cout << "\tSeater : ";
    cin >> seater;
    cout << "\tGeneration : ";
    cin >> generation;
    cout << "\tDesiel / Petrol : ";
    cin.ignore();
    cin.getline(des_pat, 9);
    cout << "\tRTO No : ";
    cin >> RTO_no;
  cout << "\tAddress : ";
    cin.ignore();
    cin.getline(address, 99);
  //Date and Time
  date_time();
  sprintf(issued_date, "%d:%d %d/%d/%d", hr, mint, dd, mm, yy);
}

void vehData::delete_data(char *t) {
  features f;
  int counter=0;
  ifstream fin;
  ofstream fout;
  fin.open("file1.dat", ios::in|ios::binary);
  if(!fin)
    cout << "\nFile NOT Found";
  else {
    fout.open("tempFile.dat", ios::out|ios::binary);
    fin.read((char*)this, sizeof(*this));
    while(!fin.eof()) {
      if(strcmp(t, veh_no)) {
        fout.write((char*)this, sizeof(*this)); counter++;
      }fin.read((char*)this, sizeof(*this));
    }
    fin.close();
    fout.close();
    remove("file1.dat");
    rename("tempFile.dat", "file1.dat");
    if(counter==0) cout << "Unable to Delete";
    else cout << "\n\tDeleted Successfully";
  }
  cout << "\n\tPress any key to continue...\n";
  f.record_veh();
}

void vehData::view_data() {
  system("clear");
  onlyDisplay d;
  cout << "\xB2\xB2 Record of Challans Done \xB2\xB2\n\n";
  header();
  ifstream fin;
  fin.open("file1.dat", ios::in|ios::binary);
  if(!fin)
    cout << "\nFile Not Found !";
  else {
    fin.read((char*)this, sizeof(*this));
    while(!fin.eof()) {
      show_data();
      fin.read((char*)this, sizeof(*this));  
    }
    fin.close();
  }
  cout << "\n\n\n\nPress any key to continue...\n";
  d.menu();    
}

void vehData::search_data(char *t) {
  onlyDisplay d;
  cout << "\xB2\xB2 Search Record \xB2\xB2\n\n";
  header();
  int counter=0;
  ifstream fin;
  fin.open("file1.dat", ios::in|ios::binary);
  if(!fin)
    cout << "\nFile NOT Found !";
  else {
    fin.read((char*)this, sizeof(*this));
    while(!fin.eof()) {
      if(!strcmp(t, veh_no)) {
        show_data();
        counter++;
      }
      fin.read((char*)this, sizeof(*this));
    }
    if(counter==0)
      cout << "\nRecord NOT Found";
    fin.close();
  }
  cout << "\n\nPress any key to continue...\n";
  d.menu();
}

void vehData::update_data(char *t) {
  features f;
  int found=0;
  fstream file;
  file.open("file1.dat", ios::in|ios::out|ios::ate|ios::binary);
  file.seekg(0);
  file.read((char*)this, sizeof(*this));
  while(!file.eof()) {
    if(!strcmp(t, veh_no)){
      read_data();
      int pos = (int)file.tellg()-sizeof(*this);
      file.seekp(pos, ios::beg);
      file.write((char*)this, sizeof(*this));
      found++;
    }
    file.read((char*)this, sizeof(*this));
  }
  file.close();
  if(found==0)
    cout << "\n\tUnable to Update";
  else
    cout << "\n\tUpdated Successfully";
  cout << "\n\tPress any key to continue...\n";
  f.record_veh();
}

/*Helpline*/
void features::helpline() {
  onlyDisplay d;
  cout << "\xB2\xB2\xB2\xB2  Helpline and Hospital Services  \xB2\xB2\xB2\xB2\n\n\n"; 
  char ch;
  ifstream fin;
  fin.open("helpline.dat");
  while(!fin.eof()) {
    ch = fin.get();
    if(ch == '*') cout << "\xB2";
    else cout << ch;
  }
  fin.close();
  cout << "\n\n\n\t\tPress any key to continue...\n";
  d.menu();
}

/*AUTHENTICATION*/
void onlyDisplay::authentication() {
  features f;
  int pkey;
  for(i=0; i<25; i++)
    cout << "\xD2"; 
  cout << endl; 
  cout << "Authentication\n"; 
  for(i=0; i<25; i++)
    cout << "\xD2";
    
  cout << "\n\xB2\xB2 Enter the PIN : ";
  static int i=3;
  cin >> pkey;
  if(pkey == pass) {
    cout <<endl;
    menu();
  }
  else {
    cout << "Sorry, you are not authorised...";
    cout << "Attempts left " << i;i--; 
    if(i==-1) exit(0);
    authentication();
  }
}

/*MENU SCREEN*/
void onlyDisplay::menu() {
  char srch[15];
  features f; vehData vh;
  for(i=0; i<40; i++)
    cout << "\xB2"; 
  cout << endl;
  cout << "Smart Traffic Management System\n"; 
  for(i=0; i<40; i++)
    cout << "\xB2"; 
  cout << endl;  
  cout << "1. Keep the record of vehicles\n";   
  cout << "2. Keep the record of challan done\n"; 
  cout << "3. Search the record of vehicles\n";  
  cout << "4. Helpline information and nearby hospitals\n"; 
  cout << "5. Exit";  
  
  while(choice!=5) {
    cout << "\n\nEnter Your Choice : ";
    cin >> choice;
    switch(choice) {
      case 1:  f.record_veh(); break;
      case 2:  vh.view_data(); break;
      case 3:  {
        cout << "Enter the Vehicle No to search : ";
        cin.ignore();
          cin.getline(srch, 14);
        vh.search_data(srch);
        break;
      }
      case 4:  f.helpline(); break;
      case 5: {
        cout << "Thanks for using our Service, hope this helps you in your daily life";
        exit(0);break;
      }
    } 
  }
}

/*DATE and TIME*/
void date_time() {
  time_t t ;
  time(&t);
    struct tm tm = *localtime(&t);
    dd = tm.tm_mday; mm = tm.tm_mon + 1; yy = tm.tm_year + 1900-2000;
    hr = tm.tm_hour; mint = tm.tm_min;
}

/*MOVING CURSOR POSITION*/
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}