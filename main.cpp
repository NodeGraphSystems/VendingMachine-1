#include <iostream>
#include <ios>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

#include "vending.h"
#include "register.h"

using namespace std;

int main()
{
	//--------------------------ANDY-------------------
	ifstream inFS;
	ofstream oFS;
	Vending temp;
	vector<Vending> machineVector;
	int i;
	int j;
	string filename;
	cout << "Please enter the name of the file you would like to enter. (be sure to include the file extention)" << endl;
	cin >> filename;
	inFS.open(filename);
	if (inFS.fail())
	{
		cout << "Input file can not be found, exiting file." << endl;
		exit(1);
	}

	while (temp.readItem(inFS))
	{
		//the machine itself cannot hold more than 36 different items, (6 rows 6 cols)
		if (machineVector.size() > 35)
		{
			cout << "Too many items, max size of the machine is 6 rows of 6" << endl;
		}
		else
		{
			temp.appendItem(machineVector);
		}
	}

	for (i = 0; i < machineVector.size(); i++)
	{
		cout<<"[" << i<< "]" << ": ";
		machineVector.at(i).printVector(machineVector.at(i));
	}
	
	oFS.open("endReport.txt");
	for (j = 0; j < machineVector.size(); j++)
	{
		machineVector.at(j).printEndReport(oFS);
		//TODO: total counts for coins
	}

	//---------------------------John-George---------------------
	//

	Register transaction;
		int userChoice = 0;
		double userTotal = 0;
		double price = 0;
		double change = 0;
		int fcounter = 0;
		int dbcounter = 0;
		int qcounter = 0;
		int dcounter = 0;
		int ncounter = 0;
		int machineTotal = 0;
		int tempFive = 0;
		int tempOne = 0;
		int intUserTotal;
		int intPrice;
		int intChange;
		int userItemChoice;
		
		machineTotal = ((transaction.GetTotalFives() * 500) + (transaction.GetTotalOnes() * 100) + (transaction.GetTotalQuarters() * .25) + (transaction.GetTotalDimes() * .10) + (transaction.GetTotalNickels() * .05));
		
		 while(userItemChoice>=machineVector.size()+1 && userItemChoice>=1)
		{
			cout<<"What item do you want to chose?"<<endl;
			cin>>userItemChoice;
		
			if(userItemChoice>machineVector.size()||userItemChoice<=-1)
			{
				cout<<"please enter a number thats on the machine"<<endl;
			}
		}
		
		price = machineVector.at((userItemChoice)).getCost();
		while(userChoice != 6) {
			cout << "Enter an amount of money" << endl;
			cout << "[1] $5" << endl;
			cout << "[2] $1" << endl;
			cout << "[3] 1 Quarter" << endl;
			cout << "[4] 1 Dime" << endl;
			cout << "[5] 1 Nickel" << endl;
			cout << "[6] Stop entering money" << endl;
			cout << "You have $" << userTotal << " in credits" << endl;
			if (price-userTotal > 0) {
				cout << "You still need $" << (price - userTotal) << endl;
			}
			
			else if(price-userTotal < 0) {
				cout << "Machine owes you $" << userTotal - price << endl;
				cout << "(enter 6 to stop entering money)" << endl;
			}
		
			cin >> userChoice;
			
			if(userChoice == 1) {
				userTotal += 5;
				transaction.SetTotalFives(1); //Adds one to the total count of 5 dollar bills in machine
				fcounter++;
			}
			
			else if(userChoice == 2) {
				userTotal += 1;
				transaction.SetTotalOnes(1); //Adds one to the total count of 1 dollar bills in machine
				dbcounter++;
			}
			
			else if(userChoice == 3) {
				userTotal += 0.25;
				transaction.SetTotalQuarters(1); //Adds one to the total count of quarters in machine
				qcounter++;
			}
			
			else if(userChoice == 4) {
				userTotal += 0.10;
				transaction.SetTotalDimes(1); //Adds one to the total count of dimes in machine
				dcounter++;
			}
			
			else if(userChoice == 5) {
				userTotal += 0.05;
				transaction.SetTotalNickels(1); //Adds one to the total count of nickels in machine
				ncounter++;
			}
			else if(userChoice == 6) { 
				userTotal = userTotal; //Stop entering money and exit the loop 
			}
		}
		
		
		change = userTotal - price;
		change *= 100.00; //remove decimal place
		change = ceil(change+0.005); //round up to cloest whole number
		intChange = change; //swtich change to an int to allow for math
		intChange -=1; //subtract 1 to recieve change
		
	if(userTotal < price) { 
			change = userTotal;
			if(machineTotal > userTotal) {
				if(fcounter > 0) {
					tempFive = transaction.GetTotalFives() * 500;
					while(tempFive !=0) {				
						if(tempFive - 25 >= 0) { 
							tempFive = tempFive - 25; //if a quarter can be subtracted, do so
							qcounter++; //keep track of quarters that will be returned
						}
						
						else if(tempFive - 10 >= 0) {
							tempFive = tempFive - 10; //if a dime can be subtracted, do so
							dcounter++; //keep track of dimes that will be returne
						}
						
						else if(tempFive - 5 >= 0) {
							tempFive = tempFive - 5; //if a nickel can be subtracted, do so
							ncounter++; //keep track of nickels that will be returne
						}
					}
				}
				
				if(dbcounter > 0) {
					tempOne = transaction.GetTotalOnes() * 100;
					while(tempOne !=0) {				
						if(tempOne - 25 >= 0) { 
							tempOne = tempOne - 25; //if a quarter can be subtracted, do so
							qcounter++; //keep track of quarters that will be returned
						}
						
						else if(tempOne - 10 >= 0) {
							tempOne = tempOne - 10; //if a dime can be subtracted, do so
							dcounter++; //keep track of dimes that will be returne
						}
						
						else if(tempOne - 5 >= 0) {
							tempOne = tempOne - 5; //if a nickel can be subtracted, do so
							ncounter++; //keep track of nickels that will be returne
						}
					}
				}
	
			}
			
			cout << "Error: You did not enter enough money to buy item, giving money back" << endl;
			cout << "" << endl; //I have no idea why, but deleting this line breaks the program

			cout << "You got back " << qcounter <<  " quarters" << endl;
			cout << "You got back " << dcounter << " dimes" << endl;
			cout << "You got back " << ncounter << " nickels" << endl;

			transaction.SetTotalQuarters(-qcounter); //remove quarters enetered by user from total
			transaction.SetTotalDimes(-dcounter); //remove dimes enetered by user from total
			transaction.SetTotalNickels(-ncounter); //remove nickels enetered by user from total
		}

		else if(machineTotal < userTotal) {
			cout << "ERROR: There is not enough money in the machine to make change. Contact vendor company to get your money back." << endl;
					exit(EXIT_SUCCESS); //Terminate the program if machine cannot make change
		}

		
		else if(userTotal > price) {
			fcounter = 0;
			dbcounter = 0;
			qcounter = 0;
			dcounter = 0;
			ncounter = 0;
			cout << "Change is " << intChange << " cents" << endl;
			while(intChange !=0) {				
				if(intChange - 25 >= 0) { 
					intChange = intChange - 25; //if a quarter can be subtracted, do so
					qcounter++; //keep track of quarters that will be returned
				}
				
				else if(intChange - 10 >= 0) {
					intChange = intChange - 10; //if a dime can be subtracted, do so
					dcounter++; //keep track of dimes that will be returne
				}
				
				else if(intChange - 5 >= 0) {
					intChange = intChange - 5; //if a nickel can be subtracted, do so
					ncounter++; //keep track of nickels that will be returne
				}
			}
			cout << "You got back " << qcounter <<  " quarters" << endl;
			cout << "You got back " << dcounter << " dimes" << endl;
			cout << "You got back " << ncounter << " nickels" << endl;
			
			transaction.SetTotalQuarters(-qcounter); //Subtracts ammount of quarters given to user as change from total quarter count
			transaction.SetTotalDimes(-dcounter); //Subtracts ammount of dimes given to user as change from total dime count
			transaction.SetTotalNickels(-ncounter); //Subtracts ammount of nickels given to user as change from total nickel count
		}


	return 0;
}
