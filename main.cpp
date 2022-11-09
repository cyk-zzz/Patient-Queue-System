// Cheah Yau Khin
// Liu Jia Hwee

// PATIENT SEE!
// Your Number :
// Now Serving In Room:
// Now Serving Counter:

// 1.Patient Get Queue
// 2.Patient Gets Called And Enter Doctor Room
// 3.Patient Comes Outside And Wait To Be Called To Counter
// 4.Patient Gets Called Again and Go To Counter
// Queue 1 : Patient Go To Room
// Queue 2 : Patient Go To Counter

// Queue ID is assigned automatically by system
// PatientName, PhoneNo, IC is typed by patient

// -------------------
// Select Your Role:
// [1] Patient
// [2] Admin
// [3]: Exit
// Input(1-3): 
// -------------------

// -------------------
// Patient Menu:
// [1] Add Appointment
// [2] View Queue     (Only Current Serving)
// [3]: Exit
// Input(1-3):
// -------------------

// -------------------
// Admin Login:
// Username: admin
// Password: admin
// -------------------

// -------------------
// Admin Menu:
// [1]: NEXT RoomQueue To CounterQueue
// [2]: NEXT CounterQueue
// [3]: View Queue		(Current + Upcoming)
// [4]: Search Patient By IC
// [5]: Search Patient By Phone Number
// [6]: Exit
// Input(1-6): 
// -------------------


#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <string>
using namespace std;

void PrintToday(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	string timestat;
	int hour1 = ltm->tm_hour;
	int hour2 = ltm->tm_hour-12;
	int minute;
	
	cout << "Today's Date: "
		<< ltm->tm_mday << "-"
		<< 1 + ltm->tm_mon << "-"
		<< 1900 + ltm->tm_year << endl;
	
	if((5+ltm->tm_hour)>12){
		cout << "Current Time: "
		<< setfill('0') << setw(2) << hour2 << ":"
		<< setfill('0') << setw(2) << ltm->tm_min 
		<< " PM" << endl;
	}
	else{
		cout << "Current Time: "
		<< setfill('0') << setw(2) << hour1 << ":"
		<< setfill('0') << setw(2) << ltm->tm_min 
		<< " AM" << endl;
	}
	
}

class Queue {
public:
	int QueueID;
	string PatientName;
	string PhoneNo;
	string IC;
	Queue *Next = NULL;
	
};

class QueueList {
private:
	int count;
	Queue* CurrentRoom;
	Queue* CurrentCounter;
	
public:
	// Head = Now Serving
	QueueList(){
		CurrentRoom	= NULL;
		CurrentCounter = NULL;
	};
	
	void InsertQueue(string PatientName,string PhoneNo,string IC);
	void RoomToCounter();
	void CounterNext();
	void AdminDisplay();
	void PatientDisplay();
	void SearchByIC(string IC);
	void SearchByPhone(string PhoneNo);
};

void QueueList::InsertQueue(string PatientName,string PhoneNo,string IC){
	count++;
	Queue* temp = CurrentRoom;
	Queue* prev = NULL;
	Queue* P = new Queue;
	P->QueueID = count;
	P->PatientName = PatientName;
	P->PhoneNo = PhoneNo;
	P->IC = IC;
	
	if (CurrentRoom == NULL) CurrentRoom = P;
	else{
		while(temp){
			cout << "x";
			prev = temp;
			temp = temp ->Next;
			}
			
		prev->Next = P;
	}
}

void QueueList::RoomToCounter(){
	system("CLS");
	Queue* currCounter = CurrentCounter;
    Queue* prevCounter = NULL;
    Queue* currRoom = CurrentRoom;

    CurrentRoom = CurrentRoom->Next;
    currRoom->Next = NULL;

    if(CurrentCounter == NULL){
            CurrentCounter = currRoom;
    }
    else{
        while(currCounter){
            prevCounter = currCounter;
            currCounter = currCounter ->Next;
            }

        prevCounter->Next = currRoom;
    }
	
	cout<<"Success...\n";
	cout<<"Press Any Key to Back to Admin Menu...\n";
	getch();

}

void QueueList::CounterNext(){
	system("CLS");
	Queue* temp = CurrentCounter;
	Queue* prev = NULL;
	
	if(CurrentCounter != NULL)
	CurrentCounter = CurrentCounter -> Next;
	
	cout<<"Success...\n";
	cout<<"Press Any Key to Back to Admin Menu...\n";
	getch();
}

void QueueList::AdminDisplay(){
	system("CLS");
	PrintToday();
	if(CurrentRoom==NULL)
		cout<<"Now Serving For Room: NONE";
	else
		cout<<"Now Serving For Room: "<<CurrentRoom->QueueID;
	
	if(CurrentCounter==NULL)
		cout<<"\nNow Serving For Counter: NONE";
	else
		cout<<"\nNow Serving For Counter: "<<CurrentCounter->QueueID;
	
	//Room Queue
	cout<<"\n\nDisplay Room Queue";
	Queue *currRoomQueue = CurrentRoom;
	cout<<"\n------------------------------";
	cout<<setfill(' ')<<setw(8)<<"\nQueue ID"<<setw(20)<<"Name"<<setw(12)<<"Phone No"<<setw(15)<<"IC";
	cout<<"\n------------------------------\n";
	while (currRoomQueue){
		cout<<setw(8)<<currRoomQueue->QueueID
			<<setw(20)<<currRoomQueue->PatientName
			<<setw(12)<<currRoomQueue->PhoneNo
			<<setw(15)<<currRoomQueue->IC<<"\n";
		currRoomQueue = currRoomQueue->Next;
	}
	//Counter Queue
	cout<<"\n\nDisplay Counter Queue";
	Queue *currCounterQueue = CurrentCounter;
	cout<<"\n------------------------------";
	cout<<setw(8)<<"\nQueue ID"<<setw(20)<<"Name"<<setw(12)<<"Phone No"<<setw(15)<<"IC";
	cout<<"\n------------------------------\n";
	while (currCounterQueue){
		cout<<setw(8)<<currCounterQueue->QueueID
			<<setw(20)<<currCounterQueue->PatientName
			<<setw(12)<<currCounterQueue->PhoneNo
			<<setw(15)<<currCounterQueue->IC<<"\n";
		currCounterQueue = currCounterQueue->Next;
	}
	cout<<"Press Any Key to Back to Admin Menu...\n";
	getch();
	system("CLS");
}

void QueueList::PatientDisplay(){
	system("CLS");
	PrintToday();
	
	if(CurrentRoom==NULL)
		cout<<"\nNow Serving For Room: NONE";
	else
		cout<<"\nNow Serving For Room: "<<CurrentRoom->QueueID;
	
	if(CurrentCounter==NULL)
		cout<<"\nNow Serving For Counter: NONE";
	else
		cout<<"\nNow Serving For Counter: "<<CurrentCounter->QueueID;
	
	cout<<"\n\nPress Any Key to Back to Patient Menu...\n";
	getch();
	system("CLS");
}

void QueueList::SearchByIC(string ICNo){
	Queue *currRoom = CurrentRoom;
	Queue *currCounter = CurrentCounter;
	bool found=0;
	system("CLS");
	cout<<"Searching for Record with IC Number: "<<ICNo<<"...\n\n";
	while(currRoom&&found==0){
		if(currRoom->IC==ICNo){
			cout<<"Found In Room Queue\n\n";
			cout<<"Queue ID: "<<currRoom->QueueID
				<<"\nPatient Name: "<<currRoom->PatientName
				<<"\nPhone Number: "<<currRoom->PhoneNo
				<<"\nIC Number: "<<currRoom->IC;
			found=1;
			break;
		}
		currRoom = currRoom->Next;
	}
	while(currCounter&&found==0){
		if(currCounter->IC==ICNo){
			cout<<"Found In Counter Queue\n\n";
			cout<<"Queue ID: "<<currCounter->QueueID
				<<"\nPatient Name: "<<currCounter->PatientName
				<<"\nPhone Number: "<<currCounter->PhoneNo
				<<"\nIC Number: "<<currCounter->IC;
			found=1;
			break;
		}
		currCounter = currCounter->Next;
	}
	
	if (found==0){
		cout<<"No Record Found!\n";
	}
	cout<<"\n\nPress Any Key to Back to Admin Menu...\n";
	getch();
	system("CLS");
}

void QueueList::SearchByPhone(string Phone){
	Queue *currRoom = CurrentRoom;
	Queue *currCounter = CurrentCounter;
	bool found=0;
	system("CLS");
	cout<<"Searching for Record with Phone Number: "<<Phone<<"...\n\n";
	while(currRoom&&found==0){
		if(currRoom->PhoneNo==Phone){
			cout<<"Found In Room Queue\n";
			cout<<"Queue ID: "<<currRoom->QueueID
				<<"\nPatient Name: "<<currRoom->PatientName
				<<"\nPhone Number: "<<currRoom->PhoneNo
				<<"\nIC Number: "<<currRoom->IC;
			found=1;
			break;
		}
		currRoom = currRoom->Next;
	}
	while(currCounter&&found==0){
		if(currCounter->PhoneNo==Phone){
			cout<<"Found In Counter Queue\n";
			cout<<"Queue ID: "<<currCounter->QueueID
				<<"\nPatient Name: "<<currCounter->PatientName
				<<"\nPhone Number: "<<currCounter->PhoneNo
				<<"\nIC Number: "<<currCounter->IC;
			found=1;
			break;
		}
		currCounter = currCounter->Next;
	}
	
	if (found==0){
		cout<<"No Record Found!\n";
	}
	cout<<"\n\nPress Any Key to Back to Admin Menu...\n";
	getch();
	system("CLS");
}

//void MainMenu(QueueList &);
void AdminMenu(QueueList &P) {
	int input;
	string IC, phoneNo;
	string username, pw;
	
	do{
		system("CLS");
		cout<<"-------------------\n";
		cout<<"Admin Login:\n";
		cout<<"Username: ";//admin
		cin>>username;
		cout<<"Password: ";//admin
		cin>>pw;
		
		if((username=="admin")&&(pw=="admin")){
			cout<<"\nValid login...\n";
			Sleep(500);
			//system("CLS");
			break;
		}
		else {
			system("CLS");
			cout<<"Invalid Username or Password!!\n";
			cout<<"Please try again!!\n";
			Sleep(500);
			return;
		}
	}while ((username!="admin")||(pw!="admin"));
	

	
	do{
		system("CLS");
		cout<<"-------------------\n"
		<<"Admin Menu\n"
		<<"-------------------\n"
		<<"[1]: NEXT RoomQueue To CounterQueue \n"
		<<"[2]: NEXT CounterQueue \n"
		<<"[3]: View Queue \n" //(Current + Upcoming)
		<<"[4]: Search Patient By IC \n"
		<<"[5]: Search Patient By Phone Number \n"
		<<"[6]: Back to Main Menu \n"
		<<"Input(1-6): "; 
		cin>>input;
	
		switch (input){
			case 1: 
				P.RoomToCounter();
				break;
			case 2:
				P.CounterNext();
				break;
			case 3:
				P.AdminDisplay();
				break;
			case 4:
				system("CLS");
				cout<<"Search Patient By IC \n";
				cout<<"Input: ";
				cin>>IC;
				P.SearchByIC(IC);
				break;
			case 5:
				system("CLS");
				cout<<"Search Patient By Phone Number \n";
				cout<<"Input: ";
				cin>>phoneNo;
				P.SearchByPhone(phoneNo);
				break;
			case 6:
				break;
			default: 
				cout<<"Invalid input!";
				break;	
		}
		
	}while(input!=6);

};

void PatientMenu(QueueList &P){
	int choice;
	string name, pNo, ICNo;
	do{
		system("CLS");
		cout<<"-------------------\n"
			<<"Patient Menu\n"
			<<"-------------------\n"
			<<"[1] Add Appointment\n"
			<<"[2] View Queue\n"
			<<"[3] Back to Main Menu\n"
			<<"Input(1-3): ";
		cin>>choice;
		
		switch(choice){
			case 1:
				system("CLS");
				cout<<"-------------------\n"
					<<"Add Appointment\n"
					<<"-------------------\n"
					<<"Name: ";
				cin.ignore();
				getline(cin,name);
				cout<<"Phone Number: ";
				cin>>pNo;
				cout<<"IC Number: ";
				cin>>ICNo;
				P.InsertQueue(name,pNo,ICNo);
				break;
			case 2:
				P.PatientDisplay();
				break;
			case 3:
				break;
			default:
				cout<<"Invalid Input!";
				break;
		}	
		
	}while(choice!=3);
};

void MainMenu(QueueList &P) {
 	int input;

    do{
        system("CLS");
        cout<<"-------------------\n"
        <<"Select Your Role\n"
        <<"-------------------\n"
        <<"[1]: Patient \n"
        <<"[2]: Admin \n"
        <<"[3]: Exit \n"
        <<"Input(1-3): "; 
        cin>>input;

        switch (input){
            case 1: 
                PatientMenu(P);
                break;
            case 2:
                AdminMenu(P);
                break;
            case 3:
                cout<<"\nSayonara, have a nice day <3";
                break;
            default: 
                cout<<"Invalid input!";
                break;
        }

    }while(input!=3);
};

int main() {
	PrintToday();
	QueueList P;
	MainMenu(P);
}
