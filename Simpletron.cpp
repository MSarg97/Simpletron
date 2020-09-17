#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	cout << "*** Welcome to Simpletron! ***\n";
	cout << "*** Please enter your program's commands one by one. ***\n";
	cout << "*** I will print memory cell number and question mark. ***\n";
	cout << "*** Entered command will be stored in that memory cell. ***\n";
	cout << "*** Print -99999 after entering your program. ***\n";
	cout << "*** Attention!!! You can enter not more than 90 commands!***\n\n";

	int memory[100] = {};
	int operationNumber[11] = { 10, 11, 20, 21, 30, 31, 32, 33, 40, 41, 42 };
	string operationName[] = {"READ", "WRITE", "LOAD", "STORE", "ADD", "SUBSTRACT", "MULTIPLY", "DIVIDE",
								"BRANCH", "BRANCHNEG", "BRANCHZERO" };

	int instructionCounter, commandCounter, command, operand, accumulator, instructionRegister, operationCode;
	int size = sizeof(operationName) / sizeof(operationName[0]);
	bool operationFlag;
	instructionCounter = 0;
	commandCounter = 0;
	command = 0;
	operand = 0;
	accumulator = 0;
	instructionRegister = 0;
	operationCode = 0;

	while (command != -99999)
	{
		operationFlag = false;
		if (commandCounter >= 0 && commandCounter <= 9)
			cout << '0';
		cout << commandCounter << "    ?    ";
		cin >> command;

		if (command == -99999)
			continue;
		else
		{
			while (command > 9999 || command < 1000)
			{
				cout << endl << "*** Please enter valid command (4 digit value)! ***\n";
				if (commandCounter >= 0 && commandCounter <= 9)
					cout << '0';
				cout << commandCounter << "    ?    ";
				cin >> command;
			}

			while (!operationFlag)
			{
				for (int i = 0; i < 11; i++)
				{
					if (command / 100 == operationNumber[i])
					{
						operationFlag = true;
						break;
					}
				}
				if (!operationFlag)
				{
					cout << "\n*** You entered an invalid operation! ***\n\nHere are valid operations: \n";
					
					for (int i = 0; i < size; i++)
						cout << left << setw(15) << operationName[i] << setw(10) << operationNumber[i] << endl;
					cout << endl;
					
					if (commandCounter >= 0 && commandCounter <= 9)
						cout << '0';
					cout << commandCounter << "    ?    ";
					cin >> command;
				}
			}
		}

		memory[commandCounter] = command;
		commandCounter++;
	}

	cout << "\n*** Program loading is over! ***\n";
	cout << "*** Program execution begins! ***\n";

	while (instructionCounter < commandCounter)
	{
		instructionRegister = memory[instructionCounter];
		operationCode = instructionRegister / 100;
		operand = instructionRegister % 100;

		switch (operationCode)
		{
		case 10: cout << "\nEnter an integer to store in cell " << operand << ": ";
			cin >> memory[operand]; //READ
			break;
		case 11: cout << "\nPrinting data of cell " << operand << endl << memory[operand] << endl; //WRITE
			break;
		case 20: cout << "\nLoading cell " << operand << "'s data in accumulator from memory!\n";
			accumulator = memory[operand]; //LOAD
			break;
		case 21: cout << "\nStoring accumulator data in cell " << operand << " !\n";
			memory[operand] = accumulator; //STORE
			break;
		case 30: cout << "\nAdding cell " << operand << "'s data to accumulator!\n";
			accumulator += memory[operand]; //ADD
			break;
		case 31: cout << "\nSubstracting cell " << operand << "'s data from accumulator!\n";
			accumulator -= memory[operand]; //SUBSTRACT
			break;
		case 32: cout << "\nMultiplying cell " << operand << "'s data and accumulator data!\n";
			accumulator *= memory[operand]; //MULTIPLY
			break;
		case 33: cout << "\nDividing accumulator to cell " << operand << "'s data!\n";
			if (!memory[operand])
			{
				cout << "\n*** Trying to divide to 0! ***\n*** Execution of program is aborted ***\n";
				break;
			}
			else
				accumulator /= memory[operand]; //DIVIDE
			break;
		case 40: cout << "\nGiving control to cell " << operand << "!\n";
			instructionCounter = operand;//BRANCH
			break;
		case 41: cout << "\nGiving control to cell " << operand << ", because accumulator data is negative!\n";
			if (accumulator < 0) instructionCounter = operand; //BRANCHNEG
			break;
		case 42: cout <<"\nGiving control to cell " << operand << ", because accumulator data is zero!\n";
			if (accumulator == 0) instructionCounter = operand; //BRANCHZERO
			break;
		}

		if (operationCode == 33 && !memory[operand])
			break;
		if (accumulator <= -9999 || accumulator >= 9999)
			break;

		cout << "\n\nREGISTERS\n";
		cout << "\naccumulator: " << accumulator;
		cout << "\ninsructionCounter: " << instructionCounter;
		cout << "\ninstructionRegister: " << instructionRegister;
		cout << "\noperationCode: " << operationCode;
		cout << "\noperand: " << operand;

		cout << "\n\nMEMORY\n\n";

		for (int i = 0; i < 10; i++)
		{
			if (!i)
				cout << setw(12);
			else
				cout << setw(10);
			cout << '0' << i;
		}
		cout << endl;

		for (int i = 0; i < 100; i++)
		{
			if (!(i % 10))
			{
				cout << endl;
				if (!i)
					cout << "00";
				else
					cout << i;
			}
			cout << setw(11) << memory[i];
		}
		cout << endl;
		instructionCounter++;
	} 

	if (accumulator <= -9999 || accumulator >= 9999)
		cout << endl << "*** Accumulator overflow! ***\n*** Execution of program is aborted ***\n";
	return 0;
}
