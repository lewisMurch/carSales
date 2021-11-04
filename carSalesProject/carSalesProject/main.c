#include <stdio.h> //Allow for printf and scanf
#include <math.h> //Allow for maths functions
#include <ctype.h> 
#include <windows.h>
#include <stdlib.h>
#pragma warning(disable:4996) //_CRT_SECURE_NO_WARNINGS

//defined functions to save time
#define clear				system("cls"); //clears the system when called
#define pass				printf(""); //helps me debug functions
#define nLine				printf("\n"); //creates a new line when called
#define bigGap				printf("\n \n \n \n \n"); //creates a big gap when called - good for debug
#define longLine			printf("--------------------------\n"); //creates a standardised line when called
#define p(a)				printf(a); //forshortnes print when called
#define elementCount(list)	sizeof(list) / sizeof(list[0]); //finds the length of a list when called
#define intInput(a, b)		scanf_s(a, &b); //forshortens numeric input when called
#define input(a, b)			scanf_s(a, b); //forshortens normal input when called
#define ps(a, b)			printf(a, b) //allows me to print a string

//temp user login details
//char* acceptedLogin[][2][128] = { {"", "" } }; //Creates an maricies with un-defined rows, 2 columns (element 0 for username, element 1 for pass), and each using 128 space to store each sring

char enteredUsername[128];
char enteredPassword[128];

char usernameFromFile[128];
char passwordFromFile[128];

int accountCount;
char accountCountString[4];
int currentUserAccountNumber;

//declare variables
float finalPrice = 1000;
float priceMultiplier = 1;
float lowestPreviewPrice;
char methodOfPurchase;

short monthsToRent;
float monthlyPrice;

short yearsToFinance;
float yearlyCost;

float RENT_INTEREST = 0.98f; //The longer you rent for, the less per month
float FINANCE_YEARLY_INTEREST = 1.04f;

char modelSelector;
char carClass;
int carNameElementNumber;
int carAmountRequired;

int pistonCount[] = { 0, 2, 4, 6, 8, 10, 12 }; //0 for electric motors instead of an engine
int accesablePistonAmount[] = { 0 };
int pistonChoice;

int engineLiters;
int topSpeed;

int continueYesOrNo;
int stockValue;

const char* CAR_MODEL_LIST[] = { "Lamborghini","Ferrari","Bugatti", "Mercedes", "BMW", "Tesla", "Range Rover", "Saab", "Ford", "Kia", "VW" };
int stock_array[11] = { 1, 2, 1, 3, 4, 2, 3, 5, 8, 7, 9 };

const char* A[] = { "Lamborghini", "Ferrari", "Bugatti" };
const char* B[] = { "Mercedes","BMW", "Telsa" };
const char* C[] = { "Range Rover","Saab" };
const char* D[] = { "Ford","Kia","VW" };

//Assigns a class and price multiplier depending on the car selected
int modelClassAndPriceMultiplierFunc() {
	switch (modelSelector) {
	case 1:
	case 2:
	case 3:
		carClass = 'A'; //sets the car class to A for later use
		priceMultiplier = 300;
		break;

	case 4:
	case 5:
	case 6:
		carClass = 'B'; //sets the car class to B for later use
		priceMultiplier = 35;
		break;

	case 7:
	case 8:
		carClass = 'C'; //sets the car class to C for later use
		priceMultiplier = 5;
		break;

	case 9:
	case 10:
	case 11:
		carClass = 'D'; //sets the car class to D for later use
		priceMultiplier = 1.8f;
		break;

	default:
		printf("Error with model selection, please try again\n");
		modelClassPriceCalculator();
		break;
	}
}

//Shows the user the stats for all available cars
void viewStats() {
	size_t n = elementCount(CAR_MODEL_LIST);
	for (int i = 0; i < n; i++) {
		switch (i)
		{
		case 0:
		case 1:
		case 2:
			lowestPreviewPrice = 240000;
			break;

		case 3:
			nLine;
		case 4:
		case 5:
			lowestPreviewPrice = 35000;
			break;

		case 6:
			nLine;
		case 7:
			lowestPreviewPrice = 5000;
			break;

		case 8:
			nLine;
		case 9:
		case 10:
			lowestPreviewPrice = 900;
			break;

		default:
			break;
		}

		printf("%d: %s - starting at %.2f - %d in stock\n", i + 1, CAR_MODEL_LIST[i], lowestPreviewPrice, stock_array[i]);

	}
	nLine;
	goBack();
}

int goBack() {
	p("press 1 to go back\n");
	int goBackVar = 0;
	intInput("%d", goBackVar);

	switch (goBackVar)
	{
	case 1:
		clear;
		mainMenu();
		break;
	default:
		clear;
		viewStats();
		break;
	}

}

//Set the element variable to find the car the user requested
void carChosenFunc() {
	carNameElementNumber = modelSelector - 1;
}

int getStock() {
	carChosenFunc();
	stockValue = stock_array[carNameElementNumber];
}

int modelClassPriceCalculator() {
	printf("A:\n--\n1.Lamborghini   2.Ferrari   3.Bugatti\n\n");
	printf("B:\n--\n4.Mercedes   5.BMW   6.Tesla\n\n");
	printf("C:\n--\n7.Range Rover   8.Saab\n\n");
	printf("D:\n--\n9.Ford   10.Kia   11.VW\n");
	longLine;
	printf("Please choose a car brand: ");
	scanf_s("%d", &modelSelector);
	nLine;
	clear;
	modelClassAndPriceMultiplierFunc(); //assigns a class and price multipler
	carChosenFunc();
	getStock();
	clear;
	multiCarChooser();
	priceFunction();
}

//This function displays a menu and allows the user to select there desired amount of pistons
int pistonChoose(int levelOfBasePower, int range) {
	for (int i = levelOfBasePower; i < range + levelOfBasePower; i++) {
		printf("%d: %d pistons\n", i - levelOfBasePower + 1, pistonCount[i]);
		accesablePistonAmount[i - levelOfBasePower] = pistonCount[i];
	}
	scanf_s("%d", &pistonChoice);
	clear;
	switch (pistonChoice)
	{
	case 1:
		pistonChoice = accesablePistonAmount[0];
		printf("You chose %d pistons\n", pistonChoice);
		break;
	case 2:
		pistonChoice = accesablePistonAmount[1];
		printf("You chose %d pistons\n", pistonChoice);
		break;
	case 3:
		if (range == 3) {
			pistonChoice = accesablePistonAmount[2];
			printf("You chose %d pistons\n", pistonChoice);
			break;
		}
		else {
			system("cls");
			printf("Invalid selection\n");
			modelClassPriceCalculator();
			break;
		}
	default:
		system("cls");
		printf("Invalid selection\n");
		modelClassPriceCalculator();
		break;
	}
	//for (int x = 0; x < range; x++) {
	//	printf("VIABLE PISTONS %d\n", accesablePistonAmount[x]);
	//}
}

//allows user to choose a piston amount from available options
int pistonSwitch() {
	switch (carClass)
	{
	case 'A':
		pistonChoose(4, 3);
		break;
	case 'B':
		pistonChoose(3, 3);
		break;
	case 'C':
		pistonChoose(2, 2);
		break;
	case 'D':
		pistonChoose(1, 2);
		break;
	default:
		printf("Error choosing pistons!\n");
		break;
	}
}

//Calculates the price of the car based off of specs
int priceFunction() {
	finalPrice *= priceMultiplier; //multiply the final price by the multiplier

	//outputs & menus for the user to select from
	if (CAR_MODEL_LIST[modelSelector - 1] != "Tesla") { //if the car is NOT a Tesla
		printf("Please choose an amount of pistons in your engine: \n");
		printf("-------------------------------------------------- \n");
		pistonSwitch();

		//Adjusts prices based on piston count
		finalPrice *= pistonChoice;
		if (pistonChoice > 7) {
			finalPrice /= 10;
		}
		else if (pistonChoice < 7 && pistonChoice > 0) {
			finalPrice /= 4;
		}
	}

	else if (CAR_MODEL_LIST[modelSelector - 1] == "Tesla") { //If the car IS a Telsa
		pistonCount == 0;
		engineLiters == 0;
		system("cls");
		printf("What top speed do you require? (Maximum of 200 mph, Minimum of 100): \n");
		printf("---------------------------------------------------- \n");
		scanf_s("%d", &topSpeed);

		if (topSpeed > 200) { //lets them re-enter if there top speed is over 200 
			topSpeed = 0;
			priceFunction();
		}
		else if (topSpeed < 100) { //lets them re-enter if there top speed is below 100
			topSpeed = 0;
			priceFunction();
		}
		finalPrice *= topSpeed;
		finalPrice /= 100;
	}
	//printf("xxxx: \n");
	//printf("---------------------------------------------------- \n");
	//printf("1.Finance \n");
	//printf("2.Rent \n");
	//printf("3.buy \n");
	//scanf_s("%d", &methodOfPurchase);
	paymentTypeFunction();
}

int rentMethodFunc() {
	methodOfPurchase = 'R';
	system("cls");
	printf("How many months would you like to rent your car for?: \n");
	printf("---------------------------------------------- \n");
	scanf_s("%d", &monthsToRent);
	system("cls");//clears console output
	monthlyPrice = finalPrice / 12;
	int finalPriceIncaseOverMonthLimit = finalPrice;
	finalPrice = monthlyPrice * monthsToRent * pow(RENT_INTEREST, monthsToRent); //works out the final price (including price reduction)
	switch (monthsToRent)
	{
	case 0:
		system("cls");//clears console output
		paymentTypeFunction(); //lets the user re-enter there data
		break;
	case 1:
		printf("You will be renting the car for one month, costing %.2f pounds. \n\n", monthlyPrice); //prints a grammatically correct statment (as it's only one month), displaying costs to the user
		break;
	default:
		if (monthsToRent <= 72) {
			printf("You will be renting the car for %d months costing %.2f pounds for the first month. After this initial month, a reduction of 2 percent will be applied each month. This will amount to a total of %.2f pounds\n\n", monthsToRent, monthlyPrice, finalPrice); //prints a grammatically correct statment (as it's multiple months), displaying costs to the user
			break;
		}

		//This statment re-calculates the price using 72 weeks as a maximum
		else {
			printf("The longest amount of time you can rent a car for is 72 months\n");
			monthsToRent = 72;
			monthlyPrice = finalPriceIncaseOverMonthLimit / 12;
			finalPriceIncaseOverMonthLimit = monthlyPrice * monthsToRent * pow(RENT_INTEREST, monthsToRent);
			printf("You will be renting the car for %d months costing %.2f pounds for the first month. After this initial month, a reduction of 2 percent will be applied each month. This will amount to a total of %.2f pounds\n\n", monthsToRent, monthlyPrice, finalPrice); //prints a grammatically correct statment (as it's multiple months), displaying costs to the user
			break;
		}
	}
}

int financeMethodFunc() {
	methodOfPurchase = 'F';
	clear;
	printf("How many years do you want to finance your car for?: \n");
	printf("---------------------------------------------- \n");
	scanf_s("%d", &yearsToFinance);
	clear;

	switch (yearsToFinance)
	{
	case 0:
		system("cls");//clears console output
		paymentTypeFunction(); //lets the user re-enter there data
		break;

	default:
		yearlyCost = finalPrice / yearsToFinance;
		finalPrice = yearlyCost * yearsToFinance * pow(FINANCE_YEARLY_INTEREST, yearsToFinance);
		printf("You will be financing the car for %d years costing %.2f pounds for the first year. After this initial year, an increase of 4 percent will be applied each month. This will amount to a total of %.2f pounds\n\n", yearsToFinance, yearlyCost, finalPrice);
	}
}

int paymentTypeFunction() {
	//outputs & menus for the user to select from
	printf("Would you like to finance, rent or buy your car?: \n");
	printf("------------------------------------------------- \n");
	printf("1.Finance \n");
	printf("2.Rent \n");
	printf("3.buy \n");
	scanf_s("%d", &methodOfPurchase);

	//sets the mode of payment based of what the user selects
	switch (methodOfPurchase)
	{
	case 1: //for financing cars
		financeMethodFunc();
		break;

	case 2: //for renting cars
		rentMethodFunc();
		break;

	case 3: //For outright buying cars
		methodOfPurchase = 'B';
		clear;
		switch (carAmountRequired) //checks how many cars the user is trying to buy, and displays an appropriate message.
		{
		case 1:
			printf("You are about to purchase one %s \n", CAR_MODEL_LIST[carNameElementNumber]);
			printf("The final price is: %.2f\n ", finalPrice);
			confirmPurchase();
			break;

		default:
			printf("You are about to purchase %d %s's \neach %s costs %.2f\n\n", carAmountRequired, CAR_MODEL_LIST[carNameElementNumber], CAR_MODEL_LIST[carNameElementNumber], finalPrice / carAmountRequired);
			printf("The final price is: %.2f\n", finalPrice);
			confirmPurchase();
			break;
		}
		break;

	default:
		printf("Error with method of purchase selection"); //shows an error if the user selects somthing other than the acceptable values
		break;
	}
	//peforms equations to determin the overall price of the vechical
}

int confirmPurchase() {
	printf("Do you want to continue?\n1: yes\n2: no\n");
	scanf_s("%d", &continueYesOrNo);
	clear;
	switch (continueYesOrNo)
	{
	case 1:
		clear;
		p("Thank you for purchasing!\n\n");
		loginMenu();
		break;

	case 2:
		printf("Returning to the start...\n");
		modelClassPriceCalculator();
		break;

	default:
		clear;
		confirmPurchase;
		break;
	}
}

int multiCarChooser() {
	printf("There are %d %s's in stock. How many do you require? \n", stockValue, CAR_MODEL_LIST[carNameElementNumber]);
	scanf_s("%d", &carAmountRequired);

	if (carAmountRequired > stockValue) {
		clear;
		printf("There are not enough cars in stock. Please choose %d or less\n", stockValue);
		multiCarChooser();
	}
	else if (carAmountRequired < 1) {
		clear;
		printf("Please choose at least one car\n");
		multiCarChooser();
	}
	else {
		priceMultiplier *= carAmountRequired;
		stock_array[carNameElementNumber] -= carAmountRequired;
		clear;
	}
}

//main menu function
int mainMenu() {
	printf("1: View available cars prices and availability\n");
	printf("2: Purchase cars\n");
	int userMenuChoice = 0;
	scanf_s("%d", &userMenuChoice);
	switch (userMenuChoice)
	{
	case 1:
		clear;
		viewStats();
		break;

	case 2:
		clear;
		modelClassPriceCalculator();
		break;

	default:
		clear;
		p("Please try again\n");
		mainMenu();
		break;
	}
}

int loginMenu() {
	int loginChoice = 0;
	p("1: Login\n2: Sign up\n");
	intInput("%d", loginChoice);


	switch (loginChoice)
	{
	case 1:
		clear;
		p("Your logging in\n");
		loginFunc();
		mainMenu();
		break;

	case 2:
		clear;
		p("Your siging up\n");
		signupFunc();
		loginFunc();
		break;

	default:
		clear;
		p("Please try again\n");
		loginMenu();
		break;
	}
}

int loginFunc() {


	p("Please Login\n");
	longLine;
	p("What is your username? (Not case sensetive): ");
	scanf_s("%s", enteredUsername, 9);

	nLine;
	p("What is your password? (Case sensetive): ");
	scanf_s("%s", enteredPassword, 9);

	for (int i = 0; i >= accountCount; i++) {
		char stringI[4];

		sprintf(stringI, "%d", i+1);

		readUsernameFromFile(stringI);
		readPasswordFromFile(stringI);

		//DEBUG INCASE BROKEN:
			//p("check ");
			//printf("%d", i);
			//nLine;

		if (strcmp(lowerCaseFunc(enteredUsername), lowerCaseFunc(usernameFromFile)) == 0 && strcmp(enteredPassword, passwordFromFile) == 0) { //compares the users inputs (for username and pasword) to acceptible pairs
			clear;
			printf("Logging you in now...\n\n");
			mainMenu();
		}
	}

	//run the three lines of code below if the password isn't found within the list of accaptable values. It will only run if the above "if" statment isn't ran.
	clear;
	p("incorrect username or password, please try again\n\n");
	loginFunc();
}

int signupFunc() {
	accountCountReader();
	printf("There are: %d accounts\n", accountCount);

	p("Please enter a username (Not case sensetive): ");
	scanf_s("%s", enteredUsername, 9);

	sprintf(accountCountString, "%d", accountCount+1); //converts a number into a string to pass into the file-loading function
	fileLoaderUsername(enteredUsername, accountCountString);
	nLine;

	p("Please enter a password (Case sensetive): ");
	scanf_s("%s", enteredPassword, 9); 

	fileLoaderPassword(enteredPassword, accountCountString);
	clear;
	accountCount++;

	accountCountWriter(accountCountString);
}

int lowerCaseFunc(upperString) {
	char* str = upperString;
	size_t len = strlen(str);
	char* lower = calloc(len + 1, sizeof(char)); //creates room in memory for the lower case version of the text

	for (size_t i = 0; i < len; ++i) { //for each character in the string
		lower[i] = tolower((unsigned char)str[i]); //append a lowercase version of the character to a list, over time recreating a lowercase string
	}
	return lower;
	free(lower); //frees the memory as we no longer need it to store the lower case version of the text
}

int fileLoaderUsername(username, userNumber) { //userNumber e.g. "user1.txt"
	//https://www.programiz.com/c-programming/c-file-input-output
	char userFileName[32] = "username";
	char textExtension[7] = ".text";
	FILE* f; //Declear pointer with a type of "file"

	strcat(userFileName, userNumber);
	strcat(userFileName, textExtension);

	f = fopen(userFileName, "a+"); //opens a read/write version of the file.

	ifNullFile(f); //checks if the file is accessible

	fprintf(f, "%s", username, 36); //appends a newline to the file
	fprintf(f, "%s", "\n", 36); //appends a newline to the file

	fclose(f); //closes the file
}

int fileLoaderPassword(password, passNumber) { //passNumber e.g. "pass1.txt"
	//https://www.programiz.com/c-programming/c-file-input-output
	//https://www.programiz.com/c-programming/c-file-input-output
	char passFileName[32] = "password";
	char textExtension[7] = ".text";
	FILE* f; //Declear pointer with a type of "file"

	strcat(passFileName, passNumber);
	strcat(passFileName, textExtension);

	f = fopen(passFileName, "a+"); //opens a read/write version of the file.

	ifNullFile(f); //checks if the file is accessible

	fprintf(f, "%s", password, 36); //appends a newline to the file
	fprintf(f, "%s", "\n", 36); //appends a newline to the file

	fclose(f); //closes the file
}

int ifNullFile(fileName) {
	if (fileName == NULL) //if there is an error with the pointer, it will cancel the program and give an exit command
	{
		printf("Error opening file\n\n");
		exit(1);
	}
}

int lineCheck(filename) {
	int lineCount = 1; //Holds the value of how many lines are counted
	char character;

	for (character = getc(filename); character != EOF; character = getc(filename))
		if (character == '\n') // Increment the line counter by one for every new line
			lineCount++;

	fclose(filename); //closes the file
	return(lineCount);
}

int readUsernameFromFile(userNumberAsString) {//userNumber e.g. "user1.txt"
	char str[9];
	char userFileName[32] = "username";
	char textExtension[7] = ".text";

	strcat(userFileName, userNumberAsString);
	strcat(userFileName, textExtension);

	// open the file
	FILE* f = fopen(userFileName, "r");
	ifNullFile(f); //checks if the file is accessible

	fgets(str, 9, f); // read a line from the file, save to the var str

	strcpy(usernameFromFile, str);
	fclose(f); // close the file
}

int readPasswordFromFile(passNumberAsString) { //passNumber e.g. "pass1.txt"
	char str[9];
	char passFileName[32] = "password";
	char textExtension[7] = ".text";

	strcat(passFileName, passNumberAsString);
	strcat(passFileName, textExtension);

	// open the file
	FILE* f = fopen(passFileName, "r");
	ifNullFile(f); //checks if the file is accessible

	fgets(str, 9, f); // read a line from the file, save to the var str

	strcpy(passwordFromFile, str);
	fclose(f); // close the file

}

int accountCountReader() {
	char str[4];
	// open the file
	FILE* f = fopen("accountCount.txt", "r");

	ifNullFile(f); //checks if the file is accessible

	fgets(str, 4, f); // read a line from the file, save to the var str

	strcpy(accountCountString, str);
	accountCount = atoi(accountCountString);
	fclose(f); // close the file
}

int accountCountWriter(numberAsString) {
	FILE* f = fopen("accountCount.txt", "w");	// open the file
	ifNullFile(f); //checks if the file is accessible

	fprintf(f, "%s\n", numberAsString);
	fclose(f); // close the file
}

void main() {
	loginMenu();
}




