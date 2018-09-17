#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

string makeCharString(char useSymbols, char useNumbers, char useLower, char useUpper);
void generatePassword(string charstr, int genAmount, int passLength, char savePass);
int getRandom(int lowPoint, int highPoint);

int main() 
{
	// Sets the title
	SetConsoleTitle("Password Generator");
	
	// Initializes the seed
	srand(time(NULL));

	int retry = 0, genAmount, passLength;
	char useSymbols, useNumbers, useLower, useUpper, savePass;

	// Prompts the user to input the amount of generated passwords
	cout << "How many passwords should be generated: ";
	cin >> genAmount;

	// Prompts the user to input the length of the generated password
	cout << "Desired password length: ";
	cin >> passLength;

	cout << "Answer the following with 'n' for NO and 'y' for YES." << endl;
	cout << "-----------------------------------" << endl;

	cout << "Use symbols (e.g. @#$%): ";
	cin >> useSymbols;

	cout << "Use numbers (e.g. 123456): ";
	cin >> useNumbers;

	cout << "Use lower-case characters (e.g. abcdef): ";
	cin >> useLower;

	cout << "Use upper-case characters (e.g. ABCDEF): ";
	cin >> useUpper;

	cout << "Save passwords to a file: ";
	cin >> savePass;

	// Outputs the current settings.
	cout << "-----------------------------------" << endl;
	cout << "Executing with these settings: " << endl;
	cout << "-----------------------------------" << endl;
	cout << "- Number of passwords: " << genAmount << endl;
	cout << "- Length of password: " << passLength << endl;
	cout << "- Use symbols: " << ((useSymbols == 'y') ? "yes" : "no") << endl;
	cout << "- Use numbers: " << ((useNumbers == 'y') ? "yes" : "no") << endl;
	cout << "- Use lower-case characters: " << ((useLower == 'y') ? "yes" : "no") << endl;
	cout << "- Use upper-case characters: " << ((useUpper == 'y') ? "yes" : "no") << endl;
	cout << "- " << ((savePass == 'y') ? "Passwords will be saved" : "Passwords will not be saved") << endl;
	cout << "-----------------------------------" << endl;
	cout << endl;

	// Create the characters based on user info
	string charstr = makeCharString(useSymbols, useNumbers, useLower, useUpper);

	// Calls the function that generates the password and outputs it to the console
	generatePassword(charstr, genAmount, passLength, savePass);

	// Pauses the program so it doesn't close immediately upon generation
	system("pause");
	return 0;
}

string makeCharString(char useSymbols, char useNumbers, char useLower, char useUpper)
{
	string charstr = "";

	// Define presets
	const char *symbols = "!#$%&'()*+,-./:;<=>?@[\]^_{|}~";
	const char *numbers = "0123456789";
	const char *lowercase = "abcdefghijklmnopqrstuvwyz";
	const char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// Check and concatenate
	if (useSymbols == 'y')
		charstr += symbols;
	if (useNumbers == 'y')
		charstr += numbers;
	if (useLower == 'y')
		charstr += lowercase;
	if (useUpper == 'y')
		charstr += uppercase;

	// Return concatenated string
	return charstr;
}

void generatePassword(string charstr, int genAmount, int passLength, char savePass)
{
	string pass;

	// Opens the password.txt file
	ofstream passfile;
	passfile.open("passwords.txt");

	// Checks if the user chose no for every option
	if (charstr != "")
	{
		// Loops through the provided amount of generations
		for (int i = 0; i < genAmount; i++)
		{
			// Resets the password string so a new one can be generated
			pass = "";
			// Loops as many times as is the length of the password
			for (int j = 0; j < passLength; j++)
			{
				// Adds a random character from the array to the password string
				pass += charstr[getRandom(0, charstr.length() - 1)];
			}
			// Outputs the generated password
			cout << i+1 << ". " << pass << endl;
			if(savePass == 'y')
				passfile << pass << "\n";
		}
	}

	// If the user chose no for every option
	else
		cout << "No usable characters." << endl;

	// Closes the file
	if(passfile.is_open()) passfile.close();
}

int getRandom(int lowPoint, int highPoint)
{
	// Returns a random integer between two given numbers
	return rand() % (highPoint - lowPoint + 1) + lowPoint;
}