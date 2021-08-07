#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <conio.h>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************* CLASSES ******************************************************/
class Cars
{
	protected:
		char name[30];
		int ID;  //format 4 digit
		bool booked; // 1 or 0
	public:
		void getdata();
		void putdata();
		void modify();
		bool booked_status(){
			return booked;
		}
		int get_ID(){
			return ID;
		}
		char* get_name(){
			return name;
		}
		void bookit(){
			this->booked = 1;
		}
		void unbookit(){
			this->booked = 0;			
		}
}c;
class Login{
	protected:
		char username[100];
		char password[50];
};
class Login_user:public Login{
	public:
		void Register();
		int check_user_existence(char[]);
		void login(char user_n[], char pass[]);
		//display available cars
		int show_hatchback();
		int show_sedan();
		int show_suv();
		int show_luxury();
		//book the available cars
		void book_hatchback();
		void book_sedan();
		void book_suv();
		void book_luxury();
		//invoices
		//void invoice(int);
		void bill(int);   //void bill(float,int,char*);
		//do work function
		void do_user_work();
		void unbook();
		int search_car_hatchback(int);
		int search_car_sedan(int);
		int search_car_suv(int);
		int search_car_luxury(int);
};
class Login_admin:public Login{
	public:
		void login_admin(char user_n[],char pass[]);
		//void register_admin();
		void Export_user_data(); //exporting user data to csv
		void Read_user_data();
		//this is file class in original code
		void search_car();
		void delete_c();
		void Export();
		void modify_car();
		void add_car_hatchback();
		void add_car_luxury();
		void add_car_sedan();
		void add_car_suv();
		//display versions
		void display_car_hatchback();
		void display_car_luxury();
		void display_car_sedan();
		void display_car_suv();
		//do work function
		void do_work();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************* STRING OPERATIONS ********************************************/
int str_len(char c[])
{
	int length=0;
	while(c[length]!='\0')
	{
		length++;
	}
	return length;
}
string conv_to_str(char* a,int size)
{
	int i;
	string s = "";
	for(i=0;i<size;i++)
	{
		s = s + a[i];
	}
	return s;
}
int isSubstring(string s1, string s2) 
{ 
    int M = s1.length(); 
    int N = s2.length(); 
    for (int i = 0; i <= N - M; i++) { // A loop to slide pat[] one by one
        int j; 
        for (j = 0; j < M; j++) //For current index i, check for pattern match
            if (s2[i + j] != s1[j]) 
                break; 
        if (j == M) 
            return i; 
    } 
    return -1;
} 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************CAR CLASS FUNCTIONS****************************************************/
void Cars::getdata()
{
	cout<<"Enter name of car: ";
	scanf(" %[^\n]s",name);
	while(1)
	{
		cout<<"Enter ID of the car: ";
		cin>>ID;
		if(ID/10000 == 0 && ID/1000!=0)
			break;
		else
			cout<<"4 Digit please"<<endl;
	}
	while(1)
	{
		cout<<"Booked status(1 for yes/0 for no): ";
		cin>>booked;
		if(booked==1||booked==0)
			break;
		else
			cout<<"Enter (1 for yes/0 for no)"<<endl;
	}
}
void Cars::putdata()
{
	if(booked==1)
		cout<<"\t"<<"|"<<setw(20)<<name<<" |"<<setw(5)<<ID<<" |"<<setw(4)<<"Yes"<<" |"<<endl;
	else
		cout<<"\t"<<"|"<<setw(20)<<name<<" |"<<setw(5)<<ID<<" |"<<setw(4)<<"No"<<" |"<<endl;
}
void Cars::modify() //function to modify the records
{
	int ch;
	cout<<"Current details are"<<endl;
	putdata();
	cout<<"Modify:\n 1.Name\n 2.ID\n 3.Booked?\n 4.All\n Your choie: ";
	cin>>ch;
	switch(ch)
	{
		case 1:
			cout<<"Enter new name of the Car: ";
			cin>>name;
			break;
		case 2:
			cout<<"Enter new ID: ";
			cin>>ID;
			break;
		case 3:
			cout<<"Booking status?(1 for yes/0 for no): ";
			cin>>booked;
			break;
		case 4:
			getdata();
			break;
		default:
			cout<<"Wrong option selected, refer menu"<<endl;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************LOGIN ADMIN CODES****************************************************/
void Login_admin::login_admin(char user_n[], char pass[])
{
	string name;
	int ch = 0,round = 0;
	ifstream fin("admin_data.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No admin Data Available!"<<endl;
		fin.close();
		return;
	}
	else{
		while(fin>>username>>password)
		{
			if(strcmp(user_n,username)==0 && strcmp(pass,password)==0)
			{
				name = conv_to_str(user_n,str_len(user_n));
				size_t found = name.find("@cadmin.ac.in"); 
				cout<<"Hello "<<name.substr(0,found)<<endl;
				round = 1;
				do_work();
			}
			else if(strcmp(user_n,username)==0)
			{
				cout<<"Entered password is incorrect"<<endl;
				round = 1;
				/*cout<<"You might want to consider registering(y/n): ";
				cin>>ans;
				if(ans=='y'||ans=='Y'){
					this->register_admin();
				}
				else{
					cout<<"Allright see ya!"<<endl;
				}*/
			}
		}
		fin.close();
		if(round==0)
		{
			cout<<"This User does not exist!"<<endl;
		}
	}
}
/*void Login_admin :: register_admin()
{
	ofstream fout("admin_data.txt",ios::app);
	cout<<"Enter username(mail): ";
	cin>>username;
	cout<<"Enter your preferred password: ";
	cin>>password;
	fout<<username<<" "<<password<<endl;
	fout.close();
}*/
void Login_admin::Read_user_data()
{
	ifstream fin("login_data.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No User Data Available!"<<endl;
		fin.close();
		return;
	}
	while(fin>>username>>password)
	{
		cout<<"|"<<setw(20)<<username<<"|"<<setw(10)<<password<<"|"<<endl;
	}
	fin.close();
}
void Login_admin::Export_user_data()
{
	ifstream fin("login_data.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No User Data Available!"<<endl;
		fin.close();
		return;
	}
	ofstream fout("Login_data.csv",ios::out);
	fout<<"USERNAME"<<","<<"PASSWORD"<<endl;
	while(fin>>username>>password)
	{
		fout<<username<<","<<password<<endl;
	}
	fin.close();
	fout.close();
}
void Login_admin::add_car_hatchback(){
	char ch='y';
	ofstream fout("HATCHBACK.txt",ios::out|ios::app);
	while(ch=='y'|ch=='Y')
	{
		c.getdata();
		fout.write((char*)&c,sizeof(c));
		cout<<"\nDo you wish to add more(y/n): ";
		cin>>ch;
	}
	cout<<"\nData added to file\n"<<endl;
	fout.close();
}
void Login_admin::add_car_luxury(){
	char ch='y';
	ofstream fout("LUXURY.txt",ios::out|ios::app);
	while(ch=='y'|ch=='Y')
	{
		c.getdata();
		fout.write((char*)&c,sizeof(c));
		cout<<"\nDo you wish to add more(y/n): ";
		cin>>ch;
	}
	cout<<"\nData added to file\n"<<endl;
	fout.close();
}
void Login_admin::add_car_sedan(){
	char ch='y';
	ofstream fout("SEDAN.txt",ios::out|ios::app);
	while(ch=='y'|ch=='Y')
	{
		c.getdata();
		fout.write((char*)&c,sizeof(c));
		cout<<"\nDo you wish to add more(y/n): ";
		cin>>ch;
	}
	cout<<"\nData added to file\n"<<endl;
	fout.close();
}
void Login_admin::add_car_suv(){
	char ch='y';
	ofstream fout("SUV.txt",ios::out|ios::app);
	while(ch=='y'|ch=='Y')
	{
		c.getdata();
		fout.write((char*)&c,sizeof(c));
		cout<<"\nDo you wish to add more(y/n): ";
		cin>>ch;
	}
	cout<<"\nData added to file\n"<<endl;
	fout.close();
}
void Login_admin::display_car_hatchback()
{
	ifstream fin("HATCHBACK.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No HATCHBACK Data Available!"<<endl;
		fin.close();
		return;
	}
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		c.putdata();
		cout<<endl; 
	}
	fin.close();
}
void Login_admin::display_car_luxury()
{
	ifstream fin("LUXURY.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No LUXURY Data Available!"<<endl;
		fin.close();
		return;
	}
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		c.putdata();
		cout<<endl; 
	}
	fin.close();
}
void Login_admin::display_car_sedan()
{
	ifstream fin("SEDAN.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No SEDAN Data Available!"<<endl;
		fin.close();
		return;
	}
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		c.putdata();
		cout<<endl; 
	}
	fin.close();
}
void Login_admin::display_car_suv()
{
	ifstream fin("SUV.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No SUV Data Available!"<<endl;
		fin.close();
		return;
	}
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		c.putdata();
		cout<<endl; 
	}
	fin.close();
}
void Login_admin::Export()
{	
	ofstream fout("cars.csv");
	//writing hatchback file to excel cars file
	ifstream fin1("HATCHBACK.txt",ios::in); //open hatchback
	fout<<"HATCHBACK"<<endl;
	while(fin1.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==0)
			fout<<c.get_name()<<","<<c.get_ID()<<","<<"Yes"<<endl;
		else
			fout<<c.get_name()<<","<<c.get_ID()<<","<<"No"<<endl;
	}
	fout<<endl;
	fin1.close();//close hatchback
	
	//writing Sedan file to excel cars file
	ifstream fin2("SEDAN.txt",ios::in); //open hatchback
	fout<<"SEDAN"<<endl;
	while(fin2.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==0)
			fout<<c.get_name()<<","<<c.get_ID()<<","<<"Yes"<<endl;
		else
			fout<<c.get_name()<<","<<c.get_ID()<<","<<"No"<<endl;
	}
	fout<<endl;
	fin2.close();//close Sedan
	
	//writing Suv file to excel cars file
	ifstream fin3("SUV.txt",ios::in); //open hatchback
	fout<<"SUV"<<endl;
	while(fin3.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==0)
			fout<<c.get_name()<<","<<c.get_ID()<<","<<"Yes"<<endl;
		else
			fout<<c.get_name()<<","<<c.get_ID()<<","<<"No"<<endl;
	}
	fout<<endl;
	fin3.close();//close Suv
	
	//writing luxury file to excel cars file
	ifstream fin4("LUXURY.txt",ios::in); //open hatchback
	fout<<"LUXURY"<<endl;
	while(fin4.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==0)
			fout<<c.get_name()<<","<<c.get_ID()<<","<<"Yes"<<endl;
		else
			fout<<c.get_name()<<","<<c.get_ID()<<","<<"No"<<endl;
	}
	fout<<endl;
	fin4.close();//close luxury
	fout.close();//close the excel file
}
void Login_admin::search_car()
{
	int entered_id;
	char found  = 'n';
	cout<<"\nEnter the ID to be searched: ";
	cin>>entered_id;
	//searching the hatchback file
	ifstream fin1("HATCHBACK.txt",ios::in);
	while(fin1.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			c.putdata();
			found = 'y';
		}
	}
	fin1.close();
	if(found =='y'){return;}

	//searching the sedan file
	ifstream fin2("SEDAN.txt",ios::in);
	while(fin2.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			c.putdata();
			found = 'y';
		}
	}
	fin2.close();
	if(found =='y'){return;}
	
	//searching the suv file
	ifstream fin3("SUV.txt",ios::in);
	while(fin3.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			c.putdata();
			found = 'y';
		}
	}
	fin3.close();
	if(found =='y'){return;}
	
	//searching the luxury file
	ifstream fin4("LUXURY.txt",ios::in);
	while(fin4.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			c.putdata();
			found = 'y';
		}
	}
	fin4.close();
	if(found =='n'){cout<<"\nCar of ID "<<entered_id<<"is not in the file.\n";}
	return;
}
void Login_admin::modify_car() //fuction to modify the records of file
{
	int entered_id;
	char found  = 'n';
	cout<<"\nEnter the ID to be searched: ";
	cin>>entered_id;
	
	//searching and modifying the hatchback file
	fstream fio1("HATCHBACK.txt",ios::in|ios::out);
	fio1.seekg(0);
	while(!fio1.eof())
	{
		int loc = fio1.tellg(); //storing the current location in loc
		fio1.read((char*)&c,sizeof(c));
		if(c.get_ID()==entered_id)
		{
			c.modify();
			found = 'y';
			fio1.seekg(loc); //moving the pointer to current location
			fio1.write((char*)&c,sizeof(c));
			cout<<"\nYour record of ID "<<entered_id<<" has been updated"<<endl;
			break;
		}
	}
	fio1.close();
	if(found =='y'){return;}
	
	//searching and modifying the sedan file
	fstream fio2("SEDAN.txt",ios::in|ios::out);
	fio2.seekg(0);
	while(!fio2.eof())
	{
		int loc = fio2.tellg(); //storing the current location in loc
		fio2.read((char*)&c,sizeof(c));
		if(c.get_ID()==entered_id)
		{
			c.modify();
			found = 'y';
			fio2.seekg(loc); //moving the pointer to current location
			fio2.write((char*)&c,sizeof(c));
			cout<<"\nYour record of ID "<<entered_id<<" has been updated"<<endl;
		}
	}
	fio2.close();
	if(found =='y'){return;}
	
	//searching and modifying the suv file
	fstream fio3("SUV.txt",ios::in|ios::out);
	fio3.seekg(0);
	while(!fio3.eof())
	{
		int loc = fio3.tellg(); //storing the current location in loc
		fio3.read((char*)&c,sizeof(c));
		if(c.get_ID()==entered_id)
		{
			c.modify();
			found = 'y';
			fio3.seekg(loc); //moving the pointer to current location
			fio3.write((char*)&c,sizeof(c));
			cout<<"\nYour record of ID "<<entered_id<<" has been updated"<<endl;
		}
	}
	fio3.close();
	if(found =='y'){return;}
	
	//searching and modifying the hatchback file
	fstream fio4("LUXURY.txt",ios::in|ios::out);
	fio4.seekg(0);
	while(!fio4.eof())
	{
		int loc = fio4.tellg(); //storing the current location in loc
		fio4.read((char*)&c,sizeof(c));
		if(c.get_ID()==entered_id)
		{
			c.modify();
			found = 'y';
			fio4.seekg(loc); //moving the pointer to current location
			fio4.write((char*)&c,sizeof(c));
			cout<<"\nYour record of ID "<<entered_id<<" has been updated"<<endl;
		}
	}
	fio4.close();
	if(found =='n'){cout<<"\nCar of ID "<<entered_id<<"is not in the file.\n";}
	return;
}
void Login_admin::delete_c() //function to delete the records of file
{	
	int entered_id;
	char found  = 'n';
	cout<<"\nEnter the ID to be deleted: ";
	cin>>entered_id;
	
	//fstream fio1("HATCHBACK.txt",ios::in|ios::out|ios::app);
	ifstream fin1("HATCHBACK.txt",ios::in);
	ofstream fout1("temp1.txt",ios::out|ios::app);
	while(fin1.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			found = 'y';
		}
		else{
			fout1.write((char*)&c,sizeof(c)); //writing to temp file
		}
	}
	fin1.close();
	fout1.close();
	remove("HATCHBACK.txt");
	rename("temp1.txt","HATCHBACK.txt");
	if(found=='y'){
		cout<<"Record successfully deleted"<<endl;
		return;
	}
	
	
	//fstream fio2("SEDAN.txt",ios::in|ios::out|ios::app);
	ifstream fin2("SEDAN.txt",ios::in);
	ofstream fout2("temp2.txt",ios::out|ios::app);
	while(fin2.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			found = 'y';
		}
		else{
			fout2.write((char*)&c,sizeof(c)); //writing to temp file
		}
	}	
	fin2.close();
	fout2.close();
	remove("SEDAN.txt");
	rename("temp2.txt","SEDAN.txt");
	if(found=='y'){
		cout<<"Record successfully deleted"<<endl;
		return;
	}
	
	//fstream fio3("SUV.txt",ios::in|ios::out|ios::app);
	ifstream fin3("SUV.txt",ios::in);
	ofstream fout3("temp3.txt",ios::out|ios::app);
	while(fin3.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			found = 'y';
		}
		else{
			fout3.write((char*)&c,sizeof(c)); //writing to temp file
		}
	}
	fin3.close();
	fout3.close();
	remove("SUV.txt");
	rename("temp3.txt","SUV.txt");
	if(found=='y'){
		cout<<"Record successfully deleted"<<endl;
		return;
	}
	
	ifstream fin4("LUXURY.txt",ios::in);
	ofstream fout4("temp4.txt",ios::out|ios::app);
	while(fin4.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			found = 'y';
		}
		else{
			fout4.write((char*)&c,sizeof(c)); //writing to temp file
		}
	}
	fin4.close();
	fout4.close();
	remove("LUXURY.txt");
	rename("temp4.txt","LUXURY.txt");
	if(found=='y'){
		cout<<"Record successfully deleted"<<endl;
		return;
	}
	else{
		cout<<"Record not found"<<endl;
	}
}
void Login_admin::do_work()
{
	int ch,op;
	int choose;
	do{
		cout<<"\nChoose option \n 1.Add Data \n 2.Display Data \n 3.Search Data \n 4.Modify Data \n 5.Delete Data\n 6.Export Car data\n 7.To see all the users\n 8.Export user data\n 9.Exit"<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				cout<<"Add Car Data\n";
				cout<<"Enter\n 1.Hatchback\n 2.Sedan\n 3.SUV\n 4.Luxury\n Your choice: ";
				cin>>choose;
				switch(choose)
				{
					case 1:
						add_car_hatchback();
						break;
					case 2:
						add_car_sedan();
						break;
					case 3:
						add_car_suv();
						break;
					case 4:
						add_car_luxury();
						break;
					default:
						cout<<"Wrong option selected"<<endl;
				}
				break;
			case 2:
				choose = 0;
				cout<<"Display Record\n";
				cout<<"Enter\n 1.Hatchback\n 2.Sedan\n 3.SUV\n 4.Luxury\n 5.All\n Your choice: ";
				cin>>choose;
				switch(choose)
				{
					case 1:
						display_car_hatchback();
						break;
					case 2:
						display_car_sedan();
						break;
					case 3:
						display_car_suv();
						break;
					case 4:
						display_car_luxury();
						break;
					case 5:
						display_car_hatchback();
						display_car_sedan();
						display_car_suv();
						display_car_luxury();
						break;
					default:
						cout<<"Wrong option selected"<<endl;
				}
				break;
			case 3:
				cout<<"Search Record\n";
				search_car();
				break;
			case 4:
				cout<<"Modify Record\n";
				modify_car();
				break;
			case 5:
				cout<<"Delete Record\n";
				delete_c();
				break;
			case 6:
				cout<<"Export car data in process"<<endl;
				Export();
				break;
			case 7:
				cout<<"User Data"<<endl;
				Read_user_data();
				break;
			case 8:
				cout<<"Export file in process"<<endl;
				Export_user_data();
				break;
			case 9:
				cout<<"Thank You for using the program :)"<<endl;
				break;
			default:
				cout<<"Wrong choice\n";
		}
	}while(ch!=9);
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/****************************************** LOGIN USER CODES **************************************************/
int Login_user::check_user_existence(char uname[] )
{
	int flag = 0;
	ifstream fin("login_data.txt",ios::in);
	while(fin>>username>>password)
	{
		if(strcmp(uname,username)==0){
			flag = 1;
		}
	}
	fin.close();
	if(flag==1)
	{
		return 1;
	}
	return 0;
}
void Login_user :: Register()
{
	char new_name[100];
	char pass[50];
	int val;
	ofstream fout("login_data.txt",ios::app);
	do{
		cout<<"Enter username(mail): ";
		cin>>new_name;
		//check username exists or not
		val = check_user_existence(new_name);
		if(val==1){cout<<"Username already exists use another one "<<endl;}
	}while(val==1);
	cout<<"Enter your preferred password: ";
	cin>>pass;
	fout<<new_name<<" "<<pass<<endl;
	fout.close();
}
int Login_user :: show_hatchback()
{
	ifstream fin("HATCHBACK.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No HATCHBACK Data Available!"<<endl;
		fin.close();
		return 1;
	}
	cout<<"\tFORMAT"<<endl;
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |"<<endl;
	cout<<"\n\tAvailable hatchback cars are\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==0){
			c.putdata();
		}
	}
	fin.close();
	fin.open("HATCHBACK.txt",ios::in);
	cout<<"\n\tUnvailable hatchback cars are\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==1){
			c.putdata();
		}
	}
	fin.close();
	return 0;
}
int Login_user :: show_sedan()
{
	ifstream fin("SEDAN.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No SEDAN Data Available!"<<endl;
		fin.close();
		return 1;
	}
	cout<<"FORMAT"<<endl;
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |"<<endl;
	cout<<"Available SEDAN cars are"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==0){
			c.putdata();
		}
	}
	fin.close();
	fin.open("SEDAN.txt",ios::in);
	cout<<"\nUnvailable SEDAN cars are"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==1){
			c.putdata();
		}
	}
	fin.close();
	return 0;
}
int Login_user :: show_suv()
{
	ifstream fin("SUV.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No SUV Data Available!"<<endl;
		fin.close();
		return 1;
	}
	cout<<"FORMAT"<<endl;
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |"<<endl;
	cout<<"Available SUV cars are"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==0){
			c.putdata();
		}
	}
	fin.close();
	fin.open("SUV.txt",ios::in);
	cout<<"\nUnvailable SUV cars are"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==1){
			c.putdata();
		}
	}
	fin.close();
	return 0;
}
int Login_user :: show_luxury()
{
	ifstream fin("LUXURY.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No LUXURY Data Available!"<<endl;
		fin.close();
		return 1;
	}
	cout<<"FORMAT"<<endl;
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |"<<endl;
	cout<<"Available LUXURY cars are"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==0){
			c.putdata();
		}
	}
	fin.close();
	fin.open("LUXURY.txt",ios::in);
	cout<<"\nUnvailable LUXURY cars are"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==1){
			c.putdata();
		}
	}
	fin.close();
	return 0;
}
void Login_user :: book_hatchback()
{
	int car_to_book;
	char found = 'n';
	int check;
	do{
		cout<<"Enter the ID of car to book: ";
		cin>>car_to_book;
		check = search_car_hatchback(car_to_book);
		if(check == 0){
			cout<<"ID is wrong :( refer menu"<<endl;
		}
	}while(check==0);
	fstream fio("HATCHBACK.txt",ios::in|ios::out);
	//check valid id
	fio.seekg(0);
	while(!fio.eof())
	{
		int loc = fio.tellg(); 
		fio.read((char*)&c,sizeof(c));
		if(c.get_ID() == car_to_book && c.booked_status() == 0){
			c.bookit();
			found = 'y';
			fio.seekg(loc);
			fio.write((char*)&c,sizeof(c));
		}
		else if(c.get_ID() == car_to_book && c.booked_status() == 1)
		{
			cout<<"Sorry its Already booked"<<endl;
			found = 'y';
		}
	}
	fio.close();
	if(found=='n'){
		cout<<"Not Available!"<<endl;
		return;
	}
	else if(found == 'y'){
		//invoice function
		cout<<"You've chosen a hatchback car"<<endl;
		bill(car_to_book); //this->invoice(car_to_book,name_of_car);
		//cout<<"Thank You for Booking!"<<endl;
		return;
	}
}
void Login_user :: book_sedan()
{
	int car_to_book;
	char found = 'n';
	int check;
	do{
		cout<<"Enter the ID of car to book: ";
		cin>>car_to_book;
		check = search_car_sedan(car_to_book);
		if(check == 0){
			cout<<"ID is wrong :( refer menu"<<endl;
		}
	}while(check==0);
	fstream fio("SEDAN.txt",ios::in|ios::out);
	fio.seekg(0);
	while(!fio.eof())
	{
		int loc = fio.tellg(); 
		fio.read((char*)&c,sizeof(c));
		if(c.get_ID() == car_to_book && c.booked_status() == 0){
			c.bookit();
			found = 'y';
			fio.seekg(loc);
			fio.write((char*)&c,sizeof(c));
		}
		else if(c.get_ID() == car_to_book && c.booked_status() == 1)
		{
			cout<<"Sorry its Already booked"<<endl;
			found = 'y';
		}
	}
	fio.close();
	if(found=='n'){
		cout<<"Not Available!"<<endl;
		return;
	}
	else if(found == 'y'){
		//invoice function
		cout<<"You've chosen a sedan car"<<endl;
		bill(car_to_book);
		//cout<<"Thank You for Booking!"<<endl;
		return;
	}
}
void Login_user :: book_suv()
{
	int car_to_book;
	char found = 'n';
	int check;
	do{
		cout<<"Enter the ID of car to book: ";
		cin>>car_to_book;
		check = search_car_suv(car_to_book);
		if(check == 0){
			cout<<"ID is wrong :( refer menu"<<endl;
		}
	}while(check==0);
	fstream fio("SUV.txt",ios::in|ios::out);
	fio.seekg(0);
	while(!fio.eof())
	{
		int loc = fio.tellg(); 
		fio.read((char*)&c,sizeof(c));
		if(c.get_ID() == car_to_book && c.booked_status() == 0){
			c.bookit();
			found = 'y';
			fio.seekg(loc);
			fio.write((char*)&c,sizeof(c));
		}
		else if(c.get_ID() == car_to_book && c.booked_status() == 1)
		{
			cout<<"Sorry its Already booked"<<endl;
			found = 'y';
		}
	}
	fio.close();
	if(found=='n'){
		cout<<"Not Available!"<<endl;
		return;
	}
	else if(found == 'y'){
		//invoice function
		cout<<"You've chosen a SUV car"<<endl;
		bill(car_to_book);
		return;
	}
}
void Login_user :: book_luxury()
{
	int car_to_book;
	char found = 'n';
	int check;
	do{
		cout<<"Enter the ID of car to book: ";
		cin>>car_to_book;
		check = search_car_luxury(car_to_book);
		if(check == 0){
			cout<<"ID is wrong :( refer menu"<<endl;
		}
	}while(check==0);
	fstream fio("LUXURY.txt",ios::in|ios::out);
	fio.seekg(0);
	while(!fio.eof())
	{
		int loc = fio.tellg(); 
		fio.read((char*)&c,sizeof(c));
		if(c.get_ID() == car_to_book && c.booked_status() == 0){
			c.bookit();
			found = 'y';
			fio.seekg(loc);
			fio.write((char*)&c,sizeof(c));
		}
		else if(c.get_ID() == car_to_book && c.booked_status() == 1)
		{
			cout<<"Sorry its Already booked"<<endl;
			found = 'y';
		}
	}
	fio.close();
	if(found=='n'){
		cout<<"Not Available!"<<endl;
		return;
	}
	else if(found == 'y'){
		//invoice function
		cout<<"You've chosen a Luxury car"<<endl;
		bill(car_to_book);
		return;
	}
}
void Login_user::unbook()
{
	char* name_of_car;
	int id_car;
	do{
	cout<<"Enter the ID of car you want to submit: ";
	cin>>id_car;
	if(id_car/10000!=0 && id_car/1000==0){cout<<"ID is of 4 digit please check your bill"<<endl;}
	}while(id_car/10000!=0 && id_car/1000==0);
	char found = 'n';
	fstream fio1("HATCHBACK.txt",ios::in|ios::out);
	fio1.seekg(0);
	while(!fio1.eof())
	{
		int loc = fio1.tellg(); 
		fio1.read((char*)&c,sizeof(c));
		if(c.get_ID() == id_car && c.booked_status()==1){
			c.unbookit();
			name_of_car = c.get_name();
			found = 'y';
			fio1.seekg(loc);
			fio1.write((char*)&c,sizeof(c));
		}
		else if(c.get_ID() == id_car && c.booked_status()==0){
			name_of_car = c.get_name();
			cout<<"This ID is of "<<name_of_car<<"\nPlease enter the correct ID of Your car"<<endl;
			found = 'j';
		}
	}
	fio1.close();
	if(found == 'j'){return;}
	if(found == 'y'){
		cout<<"Hope You liked Our Hatchback Car - "<<name_of_car<<" :)"<<endl;
		cout<<"Thank You for using our services!!"<<endl;
		return;
	}
	
	fstream fio2("SEDAN.txt",ios::in|ios::out);
	fio2.seekg(0);
	while(!fio2.eof())
	{
		int loc = fio2.tellg(); 
		fio2.read((char*)&c,sizeof(c));
		if(c.get_ID() == id_car && c.booked_status()==1){
			c.unbookit();
			name_of_car = c.get_name();
			found = 'y';
			fio2.seekg(loc);
			fio2.write((char*)&c,sizeof(c));
		}
		else if(c.get_ID() == id_car && c.booked_status()==0){
			name_of_car = c.get_name();
			cout<<"This ID is of "<<name_of_car<<"\nPlease enter the correct ID of Your car"<<endl;
			found = 'j';
		}
	}
	fio2.close();
	if(found == 'j'){return;}
	if(found == 'y'){
		cout<<"Hope You liked Our Sedan Car - "<<name_of_car<<" :)"<<endl;
		cout<<"Thank You for using our services!!"<<endl;
		return;
	}
	
	fstream fio3("SUV.txt",ios::in|ios::out);
	fio3.seekg(0);
	while(!fio3.eof())
	{
		int loc = fio3.tellg(); 
		fio3.read((char*)&c,sizeof(c));
		if(c.get_ID() == id_car){
			c.unbookit();
			name_of_car = c.get_name();
			found = 'y';
			fio3.seekg(loc);
			fio3.write((char*)&c,sizeof(c));
		}
		else if(c.get_ID() == id_car && c.booked_status()==0){
			name_of_car = c.get_name();
			cout<<"This ID is of "<<name_of_car<<"\nPlease enter the correct ID of Your car"<<endl;
			found = 'j';
		}
	}
	fio3.close();
	if(found == 'j'){return;}
	if(found == 'y'){
		cout<<"Hope You liked Our SUV Car - "<<name_of_car<<" :)"<<endl;
		cout<<"Thank You for using our services!!"<<endl;
		return;
	}
	
	fstream fio4("HATCHBACK.txt",ios::in|ios::out);
	fio4.seekg(0);
	while(!fio4.eof())
	{
		int loc = fio4.tellg(); 
		fio4.read((char*)&c,sizeof(c));
		if(c.get_ID() == id_car){
			c.unbookit();
			name_of_car = c.get_name();
			found = 'y';
			fio4.seekg(loc);
			fio4.write((char*)&c,sizeof(c));
		}
		else if(c.get_ID() == id_car && c.booked_status()==0){
			name_of_car = c.get_name();
			cout<<"This ID is of "<<name_of_car<<"\nPlease enter the correct ID of Your car"<<endl;
			found = 'j';
		}
	}
	fio4.close();
	if(found == 'j'){return;}
	if(found == 'y'){
		cout<<"Hope You liked Our Luxury Car -  "<<name_of_car<<" :)"<<endl;
		cout<<"Thank You for using our services!!"<<endl;
		return;
	}
	else if(found == 'n')
	{
		cout<<"OOPS! The Car you are submitting does not belong to us!!"<<endl;
	}
}
int Login_user::search_car_hatchback(int id_car)
{
	char found = 'n';
	ifstream fio1("HATCHBACK.txt",ios::in);
	while(fio1.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID() == id_car){
			found = 'y';
		}
	}
	fio1.close();
	if(found == 'y'){
		return 1;
	}
	return 0;
}
int Login_user::search_car_sedan(int id_car)
{
	char found = 'n';
	ifstream fio2("SEDAN.txt",ios::in);
	while(fio2.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID() == id_car){
			found = 'y';
		}
	}
	fio2.close();
	if(found == 'y'){
		return 1;
	}
	return 0;
}
int Login_user::search_car_suv(int id_car)
{
	char found = 'n';
	ifstream fio3("SUV.txt",ios::in);
	while(fio3.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID() == id_car){
			found = 'y';
		}
	}
	fio3.close();
	if(found == 'y'){
		return 1;
	}
	return 0;
}
int Login_user::search_car_luxury(int id_car)
{
	char found = 'n';
	ifstream fio4("LUXURY.txt",ios::in);
	while(fio4.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID() == id_car){
			found = 'y';
		}
	}
	fio4.close();
	if(found == 'y'){
		return 1;
	}
	return 0;
}
void Login_user::bill(int carid)  //(float rate,int carid,char* name_of_car)
{
	int see_car,rate;
	string namethecar;
	int choice,n,bill_id;
	float pay,min_pay,penalty_rate;
	see_car = search_car_hatchback(carid);
	if(see_car==1)
	{
		rate = 50;
		ifstream fin("HATCHBACK.txt",ios::in);
		while(fin.read((char*)&c,sizeof(c)))
		{
			if(c.get_ID() == carid)
			{
				namethecar = c.get_name();
			}
		}
		fin.close();
	}
	see_car = search_car_sedan(carid);
	if(see_car==1)
	{
		rate = 75;
		ifstream fin("SEDAN.txt",ios::in);
		while(fin.read((char*)&c,sizeof(c)))
		{
			if(c.get_ID() == carid)
			{
				namethecar = c.get_name();
			}
		}
		fin.close();
	}
	see_car = search_car_suv(carid);
	if(see_car==1)
	{
		rate = 85;
		ifstream fin("SUV.txt",ios::in);
		while(fin.read((char*)&c,sizeof(c)))
		{
			if(c.get_ID() == carid)
			{
				namethecar = c.get_name();
			}
		}
		fin.close();
	}
	see_car = search_car_luxury(carid);
	if(see_car==1)
	{
		rate = 220;
		ifstream fin("LUXURY.txt",ios::in);
		while(fin.read((char*)&c,sizeof(c)))
		{
			if(c.get_ID() == carid)
			{
				namethecar = c.get_name();
			}
		}
		fin.close();
	}
	system("cls");
	cout<<"Thank You for Booking! Please enter following info"<<endl;
	cout<<"Enter Time for which you want the car for rent"<<endl;
    cout<<" (1)Less than a day\n (2)Min 1 whole day\n Your choice: ";
    cin>>choice;
    fstream file1("Invoice.txt",ios::in);
	file1>>bill_id;
	bill_id=bill_id+1;
	file1.seekg(0);
	file1<<bill_id;
	file1.close();
	switch(choice)
	{
		case 1:
			//while(1)
			//{
				cout<<"Enter number of hours for which u want to get car on rent: ";
            	cin>>n;
				//if(n>0&&n<25){break;}
				//else{cout<<"Hrs between [1,24]"<<endl;}
			//}
			pay = n * rate;
			min_pay = 0.3 * pay;
			penalty_rate = 0.1 * rate + rate;
			cout<<endl;
			system("cls");
			cout<<"************************ BILL ********************************"<<endl;
			cout<<"|"<<setw(30)<<"Invoice Number"<<"|"<<setw(30)<<bill_id<<endl;
			cout<<"|"<<setw(30)<<"Customer Name"<<"|"<<setw(30)<<username<<endl;
			cout<<"|"<<setw(30)<<"Car Name"<<"|"<<setw(30)<<namethecar<<endl;
			cout<<"|"<<setw(30)<<"Car ID"<<"|"<<setw(30)<<carid<<endl;
			cout<<"|"<<setw(30)<<"Numbers of Hours"<<"|"<<setw(30)<<n<<endl;
			cout<<"|"<<setw(30)<<"Total Pay"<<"|"<<setw(30)<<pay<<endl;
			cout<<"|"<<setw(30)<<"Advance Pay "<<"|"<<setw(30)<<min_pay<<endl;
			cout<<"|"<<setw(30)<<"After use Pay"<<"|"<<setw(30)<<pay-min_pay<<endl;
			cout<<"|"<<setw(30)<<"Penalty per hour"<<"|"<<setw(30)<<penalty_rate<<endl;
			cout<<"***************************************************************"<<endl;
			break;
		case 2:
			//while(1)
			//{
				cout<<"Enter number of days for which u want to get car on rent(max a month): ";
           		cin>>n;
				//if(n>0&&n<32){break;}
				//else{cout<<"Days between [1,31]"<<endl;}
			//}
			pay = n * rate * 18; //18 = hours driven per day
			min_pay = 0.3 * pay;
			penalty_rate = 0.1 * rate + rate;
			cout<<endl;
			system("cls");
			cout<<"************************** BILL ******************************"<<endl;
			cout<<"|"<<setw(30)<<"Invoice Number"<<"|"<<setw(30)<<bill_id<<endl;
			cout<<"|"<<setw(30)<<"Customer Name"<<"|"<<setw(30)<<username<<endl;
			cout<<"|"<<setw(30)<<"Car Name"<<"|"<<setw(30)<<namethecar<<endl;
			cout<<"|"<<setw(30)<<"Car ID"<<"|"<<setw(30)<<carid<<endl;
			cout<<"|"<<setw(30)<<"Numbers of Hours"<<"|"<<setw(30)<<n<<endl;
			cout<<"|"<<setw(30)<<"Total Pay"<<"|"<<setw(30)<<pay<<endl;
			cout<<"|"<<setw(30)<<"Advance Pay "<<"|"<<setw(30)<<min_pay<<endl;
			cout<<"|"<<setw(30)<<"After use Pay"<<"|"<<setw(30)<<pay-min_pay<<endl;
			cout<<"|"<<setw(30)<<"Penalty per hour"<<"|"<<setw(30)<<penalty_rate<<endl;
			cout<<"**************************************************************"<<endl;
			break;
		default:
			cout<<"Wrong option selected"<<endl;
	}
}
void Login_user :: do_user_work()
{
	int choice;
	cout<<"Menu\n 1.Book a car\n 2.Submit the car\n Your choice: ";
	cin>>choice;
	switch(choice)
	{
		case 1:
			int ch;
			int collect;
			cout<<setw(30)<<"QUICK INFO"<<endl;
			cout<<"|"<<setw(10)<<"TYPE"<<" |"<<setw(15)<<"RATE(per hr)"<<" |"<<setw(20)<<"PENALTY RATE(per hr)"<<" |"<<endl;
			cout<<"|"<<setw(10)<<"HATCHBACK"<<" |"<<setw(15)<<50<<" |"<<setw(20)<<50*(0.1) + 50<<" |"<<endl;
			cout<<"|"<<setw(10)<<"SEDAN"<<" |"<<setw(15)<<75<<" |"<<setw(20)<<75*(0.1) + 75<<" |"<<endl;
			cout<<"|"<<setw(10)<<"SUV"<<" |"<<setw(15)<<85<<" |"<<setw(20)<<85*(0.1) + 85<<" |"<<endl;
			cout<<"|"<<setw(10)<<"LUXURY"<<" |"<<setw(15)<<220<<" |"<<setw(20)<<220*(0.1) + 220<<" |"<<endl;
			cout<<"\nBooking Point\n 1.Hatchback\n 2.Sedan\n 3.Suv\n 4.Luxury\n Your Choice: ";
			cin>>ch;
			switch(ch)
			{
				case 1:
					collect = show_hatchback();
					if(collect == 0)
						book_hatchback();	
					break;
				case 2:
					collect = show_sedan();
					if(collect == 0)
						book_sedan();
					break;
				case 3:
					collect = show_suv();
					if(collect == 0)
						book_suv();
					break;
				case 4:
					collect = show_luxury();
					if(collect == 0)
						book_suv();
					break;
				default:
					cout<<"Seems You selected wrong option"<<endl;
			}
			break;
		case 2:
			unbook();
			break;
	}
	
}
void Login_user :: login(char user_n[], char pass[])
{
	string name;
	int round = 0;
	ifstream fin("login_data.txt",ios::in);
	while(fin>>username>>password)
	{
		if(strcmp(user_n,this->username)==0 && strcmp(pass,this->password)==0)
		{
			name = conv_to_str(user_n,str_len(user_n));
			size_t found = name.find("@");
			cout<<"Welcome back "<<name.substr(0,found)<<endl;
			round = 1;
			do_user_work();
		}
		else if(strcmp(user_n,this->username)==0)
		{
			cout<<"Entered Password is incorret"<<endl;
			round =1;
		}
	}
	fin.close();
	if(round == 0)
	{
		char ans;
		cout<<"You might want to consider registering(y/n): ";
			cin>>ans;
			if(ans=='y'||ans=='Y'){
				this->Register();
			}
			else{
				cout<<"Allright see ya!"<<endl;
			}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////
/******************************** MAIN PROGRAM ***********************************************/
int main()
{
	Login_user l;
	Login_admin la;
	char username[100],password[50];
	int choosing;
	string user;
	string line;
	ifstream fin("decorate.txt");
	while(getline(fin,line))
	{
		cout<<line<<endl;
	}
	do{
		cout<<"\n\t\t\tEnter:\n \t\t\t[1]Login\n \t\t\t[2]User Registeration\n \t\t\t[3]Exit Program\n \t\t\tYour Choice: ";
		cin>>choosing;
		switch(choosing)
	{
		case 1: //login function will seperate the user and admin.
			system("cls");
			cout<<"------------------------------------------------------------"<<endl;
			cout<<"\t\t\tLogin"<<endl;
			cout<<"------------------------------------------------------------"<<endl;
			cout<<"\n\tUsername - ";
			cin>>username;
			cout<<"\tPassword - ";
			cin>>password;
			user = conv_to_str(username,str_len(username));
			if(isSubstring("@cadmin.ac.in",user)!=-1)
			{
				la.login_admin(username,password);
				choosing = 3;
			}
			else{
				l.login(username,password);
				choosing = 3;
			}
			break;
		case 2: //user registeration
			l.Register();
			cout<<"Thank You For Registering, We won't let you down!"<<endl;
			break;
		case 3:
			cout<<"Thank You for checking in, Have an Awesome Day!"<<endl;
			break;
		default:
			cout<<"Wrong option selected please refer menu"<<endl;
			exit(1);
	}
	}while(choosing!=3);
	return 0;
}
