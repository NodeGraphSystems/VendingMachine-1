#ifndef VENDING_H
#define VENDING_H
#include <string>
#include <vector>
class Vending {
public:
	void setItem(std::string itemName);
	void setCost(double costName);
	void setQuantity(int quantityName);
	std::string getItem();
	double getCost();
	int getQuantity();
	void appendItem(std::vector<Vending>& machineVector);
	bool readItem(std::ifstream &);
	void printVector(const Vending);
	void printEndReport(std::ofstream& oFS);
	Vending();
private:
	std::string item;
	double cost;
	int quantity;
};

#endif