#include <iostream>
#include <ios>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

#include "register.h"

Register::Register() {
		TotalFives = 0;
		TotalOnes = 0;
		TotalQuarters = 40;
		TotalDimes = 50;
		TotalNickels = 40;
		change = 0;
	}

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
	
