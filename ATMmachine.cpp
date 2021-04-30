// Program that simulates an ATM machine
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
// prototype all functions
void menu();
void balance();
void deposit();
void withdraw();
void tooMany();
void exit();

// make a loop that keeps the menu up while the user is logged in
bool token;
int a;
int count = 0;
const int accounts = 10;
string user[10] = { "Jason", "Brittnee" , "Elijah" , "Keith", "Sharon" , "Jessica",
	"Sarah", "Laura" , "Mike" , "Dorothy" };

double accbal[accounts];
void main()
{
	bool token = false; // sets log in to NOT logged in
	int count = 0;

	for (int i = 0; i < accounts; i++) // sets all account balances to $1000
		accbal[i] = 1000;
	do // Loop for log in attempts
	{
		if (token == false && count < 2)// gives user 2 tries to verify their account
		{
			cout << "\nEnter Account Number to Begin ===> ";
			cin >> a;
			cout << "Hello " << user[a] 
				<< ", welcome to CSC Bank.\nIf this is your account press 1\nIf this is not your account press 0" << endl;
			int verify;
			cin >> verify;
			if (verify == 1) // if user verifies their account the token
			{
				token = true;
			}
			if (verify == 0 && count < 1)
				cout << "\n***Entering wrong account number again will end session***\n";

			count++;

			if (token == false && count == 2)
			{
				tooMany(); // if user does not verify account in 2 attempts they have to start over
			}
			    
		}
	} 	
	while (token == false);
	menu(); // once token = true user goes to main menu
}
	
void menu() // Menu that has a list of the options and switches to the different functions
{
	do
	{
		cout << "\nHow may I help you today " << user[a] << endl;// menu options
		cout << "1. Check Balance\n" << "2. Make a Deposit\n" << "3. Withdraw Money\n"
			<< "4. Exit\n";
		int select;
		cin >> select;
		switch (select) // based on user input the correct case will be selected 
		{
		case 1: balance();
			break;
		case 2: deposit();
			break;
		case 3: withdraw();
			break;
		case 4: 
			token = false;
			exit();
			break;
        }
    } 	
	while (token);// while the user is signed in the token is true so they can access the menu several times

}
		

void balance() // function to allow user to check account balance
{   
		if (accbal[a] < 100)// warns user of low balance
		{
			cout << "Your Balance Is Low!! Your current balance is $ " << accbal[a];
			menu();
		}
		cout << "Your account has a balance of : $" << accbal[a] << endl;
		menu();
}
	
void deposit() // function that allows user to deposit money
{
	bool again = true;
	do // loop to make multiple deposits without going back to menu
	{
		cout << "\nEnter the amount you would like to deposit : $ ";
		double d;
		cin >> d;
		if (d <= 0) // checks that deposit is positive
		{
			for (int i = 0; i < 2; i++) // loop to limit number of failed attempts
			{ 
				if (d <= 0)
				{
					cout << "\n            *** Invalid Amount ***" << endl;
					cout << "Enter a POSITIVE amount you would like to deposit : $ ";
					cin >> d;
				}
				if (i > 0)
					again = false;
				if (d >= 0)
					break;
			}
			
		}
		if (d >= 0)// if positive value entered adds amount to user account and displays result
		{
			accbal[a] += d;
			cout << "Youre new account balance is $ " << accbal[a] << endl;
			cout << "Would you like to make another deposit?"
				<< "\nPress 1 for YES and 2 to go back to Menu" << endl;
			int d2;
			cin >> d2;
			if (d2 != 1)
				again = false;// if user choose main menu bool is set to false and loop terminates
		}
	} 	
	while (again);// 
	menu();
}

void withdraw()// Function for withdraw
{
	    cout << endl << "Your current available balance is $ " << accbal[a] << endl
			<< "\nHow much money would you like to withdraw?  $  ";
		double w;
		cin >> w;
		if (accbal[a] >= w) // Checks to make sure user has enough money to make withraw
		{
			accbal[a] = accbal[a] - w;
			cout << "\nYour new balance is $ " << accbal[a] << endl;
		}
		else // If user does not have enough money they are asked to try again
		{
			cout << "****You do not have sufficient funds avalable****\n";
			cout << endl << "Your current available balance is $ " << accbal[a] << endl
				<< "\nHow much money would you like to withdraw?  $  ";
			cin >> w;
			if (accbal[a] >= w)
			{
				accbal[a] = accbal[a] - w;
				cout << "\nYour new balance is $ " << accbal[a] << endl;
				menu();
			}
			else menu();// after second failed attempt user is sent back to menu 
			
		}
        menu();
}
	
void tooMany() // funtion to notify user they had too many failed attempts verifying account
{
	cout << "****You have exceeded account number attempts****"
		    "\nFor assistance contact your local CSC Branch"
		    "\n                 Goodbye\n";
	main();
}
void exit()  // Exit function that sends user back to main and logs them out as main token = false
{
	cout << "Thank you " << user[a] << " for chosing CSC Bank" << endl;
	cout << "      Have a great day!! Goodbye" << endl;
	main();
}