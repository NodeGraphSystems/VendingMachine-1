#include <iostream>
#include <ios>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

class Vending {
public:
	void setItem(string itemName);
	void setCost(double costName);
	void setQuantity(int quantityName);
	string getItem();
	double getCost();
	int getQuantity();
	void appendItem(vector<Vending>& machineVector);
	bool readItem(ifstream &);
	void printVector(const Vending);
	void printEndReport(ofstream& oFS);
	Vending();
private:
	string item;
	double cost;
	int quantity;
};

Vending::Vending()
{
	item = "*Null*";
	cost = 999.95;
	quantity = 12;
}
//Mutator for the Item variable
void Vending::setItem(string itemName)
{
	item = itemName;
}
//Mutator for the cost variable
void Vending::setCost(double costName)
{
	cost = costName;
}
//Mutator for the quantity variable
void Vending::setQuantity(int quantityName)
{
	quantity = quantityName;
}
//getter for the variable item
string Vending::getItem()
{
	return item;
}
//getter for the variable cost
double Vending::getCost()
{
	return cost;
}
//getter for the variable quantity
int Vending::getQuantity()
{
	return quantity;
}
//This method will have the Vending object passed into it and have the variables loaded into it.  
void Vending::appendItem(vector<Vending>& machineVector)
{
	Vending temp;
	temp.setCost(this->cost);
	temp.setItem(this->item);
	temp.setQuantity(this->quantity);
	machineVector.push_back(temp);
}
//This method will check that the file still has items in it, and will check to make sure its in the correct format.
bool Vending::readItem(ifstream &inFS)
{
	//cout << "DEBUG:entered read file" << endl;
	bool isMore = true;
	string junk;
	string holdingString;
	int i = 0;
	int j = 0;
	int counter = 0;
	int pos = 0;
	double numholder;
	bool breakFlag = false;
	bool flag2 = false;
	//Check to make sure that the file is not over
	if (!inFS.eof())
	{
		getline(inFS, holdingString);
		for (i = 0; i < holdingString.length(); i++)
		{
			//makes sure that file is the correct format
			if (holdingString.at(i) == ',')
			{
				counter += 1;
			}
		}
		//when the files the correct format it will add then to the object
		if (counter == 2)
		{
			pos = holdingString.find(',');
			this->item = holdingString.substr(0, pos);
			holdingString = holdingString.erase(0, (pos+1));
			pos = holdingString.find(',');
			this->cost = stod(holdingString.substr(0, pos));
			holdingString = holdingString.erase(0, pos+1);
			this->quantity = stoi(holdingString.substr(0, pos));
			counter = 0;
			//cout << "Debug: Entered correctly" << this->item << " " << this->cost << this->quantity << endl;
		}
		else
		{
			breakFlag = true;
		}
		numholder = (this->cost);
		numholder = numholder * 100;
		numholder = round(numholder);
		//makes sure that the cost of the item can be divisable by 5, because our machine doesnt take pennies
		if (fmod(numholder,5) != 0)
		{
			breakFlag = true;
			cout << "Error: Price cannot be met without pennies" << endl;
		}
		//the vending machine cannot have a quantity of more than 12
		if (this->quantity > 12)
		{
			breakFlag = true;
			cout << "Error: Machine cannot hold more than 12 items" << endl;
		}
		//Sets easy to see values if the line was thrown away
		if(breakFlag)
		{
			cout << "Error on line, line skipped"<<endl;
			this->item = "*Error*";
			this-> cost = 0.00;
			this->quantity = 0;
		}
		
		//cout << "DEBUG:returned true"<<endl;
	}
	else if (inFS.eof())
	{
		isMore = false;
		//cout << "DEBUG:returned false" << endl;
	}
	breakFlag = true;
	return isMore;
}
//This method will print out all of the contents of the vector to the screen
void Vending::printVector(Vending temp)
{
	//cout << "DEBUG:entering printVector" << endl;
	cout << temp.getItem() << " ";
	cout << temp.getCost()<<" ";
	cout << temp.getQuantity()<<endl;
}
//This method will print all of the contencts of the vector to an end report text file
void Vending::printEndReport(ofstream& oFS)
{
	oFS << this->item << "," << this->cost << "," << this->quantity << endl;
}

class Register {
	public:
		void SetTotalFives(int fives);
		void SetTotalOnes(int ones);
		void SetTotalQuarters(int quarters);
		void SetTotalDimes(int dimes);
		void SetTotalNickels(int nickels);
		void SetChange(double price, double userTotal);
		
		int GetTotalFives();
		int GetTotalOnes();
		int GetTotalQuarters();
		int GetTotalDimes();
		int GetTotalNickels();
		double GetChange();
		
	private:
		int TotalFives = 0;
		int TotalOnes = 0;
		int TotalQuarters = 40;
		int TotalDimes = 50;
		int TotalNickels = 40;
		double change = 0;
	};

	//Sets
	void Register::SetTotalFives(int fives) {
		TotalFives += fives;
	}
	
	void Register::SetTotalOnes(int ones) {
		TotalOnes += ones;
	}
	
	void Register::SetTotalQuarters(int quarters) {
		TotalQuarters += quarters;
	}

	void Register::SetTotalDimes(int dimes) {
		TotalDimes += dimes;
	}

	void Register::SetTotalNickels(int nickels) {
		TotalNickels += nickels;
	}


	void Register::SetChange(double price, double userTotal) {
		change = userTotal - price;
	}

	//Gets
	int Register::GetTotalFives() {
		return TotalFives;
	}
	
	int Register::GetTotalOnes() {
		return TotalOnes;
	}
	
	int Register::GetTotalQuarters() {
		return TotalQuarters;
	}

	int Register::GetTotalDimes() {
		return TotalDimes;
	}

	int Register::GetTotalNickels() {
		return TotalNickels;
	}


	double Register::GetChange() {
		return change;
	}

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
		int fives = 0;
		int ones = 0;
		int quarters = 0;
		int dimes = 0;
		int nickels = 0;
		int userChoice = 0; //used for menu
		double userTotal = 0; //ammount of money entered by user
		double price = 2.70; //this is only here to fill in for pricedisp | cost of item
		double change = 0; //(userTotal - price)
		int fcounter = 0;
		int dbcounter = 0;
		int qcounter = 0;
		int dcounter = 0;
		int ncounter = 0;
		
		int intUserTotal;
		int intPrice;
		int intChange;
		
		
		while(userChoice != 6) {
			cout << "Enter an ammount of money" << endl;
			cout << "[1] $5" << endl;
			cout << "[2] $1" << endl;
			cout << "[3] 1 Quarter" << endl;
			cout << "[4] 1 Dime" << endl;
			cout << "[5] 1 Nickel" << endl;
			cout << "[6] Stop entering money" << endl;
			cout << "You have $" << userTotal << " in credits" << endl;
			if (price-userTotal != 0) {
				cout << "You need " << (price - userTotal) << " more dollars" << endl;
			}
			
			cin >> userChoice;
			
			 if(userChoice == 1) {
				userTotal += 5;
				transaction.SetTotalFives(1); //Adds one to the total count of 5 dollar bills in machine
			}
			
			else if(userChoice == 2) {
				userTotal += 1;
				transaction.SetTotalOnes(1); //Adds one to the total count of 1 dollar bills in machine
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
		
		
		if(userTotal < price) { //if the user doesn't have enough money, give back all their money
			change = userTotal;
			cout << "Error: not enough money" << endl;
			cout << "Change is " << userTotal << endl; //TODO: Convert 5s and 1s into coins before returning

			cout << "You got back " << qcounter <<  " quarters" << endl;
			cout << "You got back " << dcounter << " dimes" << endl;
			cout << "You got back " << ncounter << " nickels" << endl;

			transaction.SetTotalQuarters(-qcounter); //remove quarters enetered by user from total
			transaction.SetTotalDimes(-dcounter); //remove dimes enetered by user from total
			transaction.SetTotalNickels(-ncounter); //remove nickels enetered by user from total
			
		}
	/*	
		else if (machineTotal < change) {
			change = userTotal;
			transaction.SetTotalQuarters(-qcounter); 
			transaction.SetTotalDimes(-dcounter);
			transaction.SetTotalNickels(-ncounter); 
		}
	*/
		
		else if(userTotal > price) {
			qcounter = 0;
			dcounter = 0;
			ncounter = 0;
			cout << "Change is " << intChange << endl;
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
