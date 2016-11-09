#include <iostream>
#include <ios>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

#include "vending.h"

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
	cout <<"Item: "<< temp.getItem() << " ";
	cout <<"$"<< temp.getCost()<<" ";
	cout <<"Quantity: " << temp.getQuantity()<<endl;
}
//This method will print all of the contencts of the vector to an end report text file
void Vending::printEndReport(ofstream& oFS)
{
	oFS << this->item << "," << this->cost << "," << this->quantity << endl;
}
