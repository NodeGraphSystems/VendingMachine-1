#ifndef REGISTER_H
#define REGISTER_H

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
		
		Register();
		
	private:
		int TotalFives;
		int TotalOnes;
		int TotalQuarters;
		int TotalDimes;
		int TotalNickels;
		double change;
		double MachineTotal;
	};
	
#endif