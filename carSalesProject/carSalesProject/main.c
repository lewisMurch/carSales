#include <stdio.h> //Allow for printf and scanf
#include <math.h> //Allow for maths functions
#include <ctype.h> 
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include<sys/stat.h> //check if file exists
#pragma warning(disable:4996) //_CRT_SECURE_NO_WARNINGS

//defined functions to save time
#define clear				system("cls"); //clears the system when called
#define pass				printf(""); //helps me debug functions more quickly
#define nLine				printf("\n"); //creates a new line when called
#define bigGap				printf("\n \n \n \n \n"); //creates a big gap when called - good for debug
#define longLine			printf("----------------------------------\n"); //creates a standardised line when called
#define p(a)				printf(a); //forshortnes print when called
#define POUND_SIGN          156 //ASCII for the pound sign
#define PERCENT_SIGN        37 //ASCII for the pound sign
#define accurateInput 	    while ((getchar()) != '\n'); option = getchar();//Makes sure it accurately reads the users input, instead of reading all the characters after it should have stopped
#define pressAnyKeyToClose  while ((getchar()) != '\n'); if (getchar()); menuChoice();

//Global Variables 
int user_age; char username_global[33] = ""; char password_global[33] = "";
const char* car_model_list[9] = { "Lamborghini","Ferrari","Bugatti", "Mercedes", "BMW", "Tesla", "Range Rover", "Saab", "Ford" };
float car_price_list[9] = { 360000.00, 290000.00, 3800000.00, 65750.00, 40000.00, 40000.00, 80000.00, 25000.00, 12000.00 };
const int* car_stock_list[9] = { 0 };
float sales_figure_total[9] = { 0 };

int car_model_list_highest_first[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int car_model_list_highest_first2[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
float sales_figure_total_highest_first[9] = { 0 };

int car_stock_list_highest_first[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

//Sends a goodbye message when called
void goodByeMessage() {
	clear; p("Thank you for your visit, enjoy the rest of your day\n\n");
}

//Saves the current stock array to the file. This is called after a purchase is made
int saveStockToFile() {
	char str[2];
	FILE* f = fopen("carStockList.txt", "w+"); ifNullFile(f); //Opens the list of car models, then checks if it has opened properly
	for (int i = 0; i < 9; i++) {
		sprintf(str, "%d", car_stock_list[i]);
		fprintf(f, str); fprintf(f, "\n"); //writes each element one by one to the file
	}
	fclose(f); //Close the file
}

//Saves the users purchase information to a file named after them
int saveInvoice(car_element, price, amount) {
	char age_string[128]; char discount_string[128] = "0"; 	char amount_string[128]; char car_element_string[128]; float* price_pointer = price; //set a pointer to hold the data passed into it by the price calculator function
	char file_name[45] = "invoice-"; 
	strcat(file_name, username_global); strcat(file_name, ".txt"); //Creates the file name by adding ".txt" to the end of the username given
	FILE* f = fopen(file_name, "a"); ifNullFile(f);

	if (user_age >= 65) {
		strcpy(discount_string, "25"); //sets the percentage removed as a string if the user is 65 or over so we can write it to the file
	}
	sprintf(age_string, "%d", user_age); sprintf(car_element_string, "%d", car_element); sprintf(amount_string, "%d", amount);
	fprintf(f, "%s\n%s\n%.2f\n%s\n", car_element_string, discount_string, *price_pointer, amount_string);
	fclose(f);

	char temp_string[64];
	FILE* f2 = fopen("salesFigure.txt", "w+"); ifNullFile(f2);
	for (int i = 0; i < 9; i++) {
		fprintf(f2, "%.2f\n", sales_figure_total[i]);
	}
	fclose(f2);
}

int loadSalesFigure() {
	char temp_string[24] = ""; float temp_float;
	FILE* f = fopen("salesFigure.txt", "r"); ifNullFile(f);
	for (int i = 0; i < 9; i++) {
		fgets(temp_string, 12, f); temp_string[strcspn(temp_string, "\n")] = 0; //Gets the price as a string, removes newline character
		temp_float = atof(temp_string); //Typecasts the string from the file, turning it into a float
		sales_figure_total[i] = temp_float;
	}
	fclose(f);
}

int loadStock() {
	char temp_string[3] = ""; int temp_int;
	FILE* f = fopen("carStockList.txt", "r"); ifNullFile(f);
	for (int i = 0; i < 9; i++) {
		fgets(temp_string, 12, f); temp_string[strcspn(temp_string, "\n")] = 0; //Gets the stock value as a string, removes newline character
		temp_int = atof(temp_string); //Typecasts the string from the file, turning it into an intiger
		car_stock_list[i] = temp_int;
	}
	fclose(f);
}

int viewAdminSales() {
	loadSalesFigure();
	char temp_string[24] = ""; float temp_float;
	FILE* f = fopen("salesFigure.txt", "r"); ifNullFile(f);

	for (int i = 0; i < 9; i++) { //Makes sure the "highest first" list is up-to-date
		fgets(temp_string, 12, f); temp_string[strcspn(temp_string, "\n")] = 0; //Gets the price as a string, removes newline character
		temp_float = atof(temp_string); //Typecasts the string from the file, turning it into a float
		sales_figure_total_highest_first[i] = temp_float;
	}

	int check_var = 0;
	while (check_var < 9) { //While NOT all 9 items are in order, do the following:
		for (int i = 0; i < 9; i++) { //for the entire list
			if (sales_figure_total_highest_first[i] < sales_figure_total_highest_first[i + 1]) { //if the element infront is smaller

				float temp_float = sales_figure_total_highest_first[i]; //save its value to a temporary value
				sales_figure_total_highest_first[i] = sales_figure_total_highest_first[i + 1]; //set the prior elements value to the latter elements value
				sales_figure_total_highest_first[i + 1] = temp_float; //Set the latter elements value to the temp variable (previously the prior value)

				//The below three lines of code are for keeping track of the car names, same as above with prices, so we can print which car has which price later on
				int temp_int = car_model_list_highest_first[i];
				car_model_list_highest_first[i] = car_model_list_highest_first[i + 1];
				car_model_list_highest_first[i + 1] = temp_int;

				check_var = 0; //Set the "item in a row" count to 0, as we just broke the chain
			}
			else {
				check_var++; //add 1 to the "another item in a row" value tracker
			}
		}
	}
	p("Lifetime car sales\n"); longLine;
	for (int i = 0; i < 9; i++) { //For each car model in the list
		if (sales_figure_total_highest_first[i] > 1) { //Only prints cars that have sold, meaning there is less clutter 
			printf("%c%.2f - %s\n", POUND_SIGN, sales_figure_total_highest_first[i], car_model_list[car_model_list_highest_first[i]]);
		}
	}
	fclose(f); pressAnyKeyToClose;
}

int menuChoice(username) {
	char option;
	if (strcmp(username_global, "admin") == 1) { //If they are NOT logged in as an admin
		clear; p("Lewis's car dealership!\n"); longLine;
		p("A: View available cars\nB: Purchase a car\nC: View Sales\nX: Back\n"); accurateInput;
		switch (option)
		{
		case 'a': case 'A':
			clear; viewCarFunction(); break;
		case 'b': case 'B':
			clear; buyCarFunction(); break;
		case 'c': case 'C':
			clear; viewSaleFunction(); break;
		case 'x': case 'X':
			clear; authenticationPage(); break;
		default:
			clear; p("Not a valid input\n"); longLine;
			authenticationPage(); break;
		}
	}
	else {
		clear; p("A: View sales figures for all cars\nX: Back\n"); accurateInput;
		switch (option)
		{
		case 'a': case 'A':
			clear; viewAdminSales(); break;
		case 'x': case 'X':
			clear; authenticationPage(); break;
		default:
			clear; p("Not a valid input\n"); longLine;
			authenticationPage(); break;
		}
	}
}

int viewCarFunction() {
	clear;	char temp_string[3] = ""; int temp_int;
	FILE* f = fopen("carStockList.txt", "r"); ifNullFile(f);

	loadStock(); //Makes sure the normal stock array is up to date

	for (int i = 0; i < 9; i++) { //Makes sure the "highest first" stock array is up-to-date
		fgets(temp_string, 12, f); temp_string[strcspn(temp_string, "\n")] = 0; //Gets the stock value as a string, removes newline character
		temp_int = atof(temp_string); //Typecasts the string from the file, turning it into an intiger
		car_stock_list_highest_first[i] = temp_int;
	}

	int check_var = 0;
	while (check_var < 9) { //While NOT all 9 items are in order, do the following:
		for (int i = 0; i < 9; i++) { //for the entire list
			if (car_stock_list_highest_first[i] < car_stock_list_highest_first[i + 1]) { //if the element infront is smaller

				int temp_int = car_stock_list_highest_first[i]; //save its value to a temporary value
				car_stock_list_highest_first[i] = car_stock_list_highest_first[i + 1]; //set the prior elements value to the latter elements value
				car_stock_list_highest_first[i + 1] = temp_int; //Set the latter elements value to the temp variable (previously the prior value)

				//The below three lines of code are for keeping track of the car names, same as above with prices, so we can print which car has which price later on
				int temp_int2 = car_model_list_highest_first2[i];
				car_model_list_highest_first2[i] = car_model_list_highest_first2[i + 1];
				car_model_list_highest_first2[i + 1] = temp_int2;

				check_var = 0; //Set the "item in a row" count to 0, as we just broke the chain
			}
			else {
				check_var++; //add 1 to the "another item in a row" value tracker
			}
		}
	}

	p("Stock list\n"); longLine;
	for (int i = 0; i < 9; i++) { //For each car model in the list
		if (car_stock_list_highest_first[i] > 1) { //Only prints cars that have sold, meaning there is less clutter 
			printf("%d - %s\n", car_stock_list_highest_first[i], car_model_list[car_model_list_highest_first2[i]]);
		}
	}
	fclose(f); pressAnyKeyToClose;
}

int priceCalculator(int* choice) {
	float price = car_price_list[*choice - 1]; int amount = 0; int stock_check_amount; int discount_used = 0;
	if (user_age >= 65) {
		printf("As you are %d, you qualify for a 25%c reduction of the final price!\n", user_age, PERCENT_SIGN);
		price *= 0.75; discount_used = 25;//reduce the price by 25% if the user is over 65
	}

	stock_check_amount = car_stock_list[*choice - 1];

	while (amount > stock_check_amount || amount < 1) {
		clear; printf("Selected: %s - %c%.2f\nHow many would you like to purchase? There are %d in stock currently\n", car_model_list[*choice - 1], POUND_SIGN, price, car_stock_list[*choice - 1]);
		int option; accurateInput; option = option - '0'; /*Allows the user to select how many of that type of car they want*/ amount = option;
	}
	price *= amount; 
	clear;
	printf("Continue with purchase? %d %s for a total of %c%.2f\nA: Yes\nB: No\n\n", amount, car_model_list[*choice - 1], POUND_SIGN, price); char option2; while ((getchar()) != '\n'); option2 = getchar();//Makes sure it accurately reads the users input, instead of reading all the characters after it should have stopped
	switch (option2)
	{
	case 'a': case 'A':
		clear; p("Thank you for purchasing from us!\n");
		int chosen_stock = car_stock_list[*choice - 1]; 
		chosen_stock -= amount; 
		car_stock_list[*choice - 1] = chosen_stock;//Edits the array by creating a temp int variable that is used to replace the value of the stock array
		float chosen_price = sales_figure_total[*choice - 1]; 
		chosen_price += price; 
		sales_figure_total[*choice - 1] = chosen_price; //Updates the total revenue per car model
		saveStockToFile(); //Writes the new array to a file right after it is edited
		saveInvoice(*choice - 1, &price, amount); //pass price as a pointer so it isn't lost when the function closes
		authenticationPage;

	case 'b': case 'B':
		clear; buyCarFunction(); break;
	default:
		clear; p("Not a valid input\n"); longLine;
		priceCalculator(&choice); break;
	}
}

int buyCarFunction() {
	clear; p("Please choose a vehical, or press 0 to go back\n"); longLine; int option; float price;
	p("1: Lamborghini		2: Ferrari	3: Bugatti\n4: Mercedes		5: BMW		6: Tesla\n7: Range Rover		8: Saab		9: Ford\n\n"); accurateInput; option = option - '0'; //Makes the 'option' value an int, not a char
	switch (option)
	{
	case 1:	case 2:	case 3:	case 4:	case 5:	case 6:	case 7:	case 8:	case 9:
		clear; priceCalculator(&option); break;
	case 0:
		clear; menuChoice(); break;
	default:
		buyCarFunction(); break;
	}
}

int viewSaleFunction() {
	loadStock();
	clear; p("Previous sales on this account:\n"); p("===============================\n"); 
	char file_name[64] = ""; char temp_car_element[4]; char temp_discount[4]; char temp_price[24]; char temp_amount[3];
	strcat(file_name, "invoice-"); strcat(file_name, username_global); strcat(file_name, ".txt");

	//Reads the amount of lines in the file, allowing us to iterate throught the file an apporpraite number of times
	FILE* fi = fopen(file_name, "r"); ifNullFile();
	int line_count = 0; char temp_char = "";
	while (temp_char != EOF){
		temp_char = fgetc(fi);
		if (temp_char == '\n') {
			line_count++;
		}
	}
	fclose(fi);

	FILE* f = fopen(file_name, "r"); ifNullFile();
	line_count /= 4; //divied by 3 as we need to run the code below every three lines
	for (int i = 0; i < line_count; i++) {

		fgets(temp_car_element, 4, f); temp_car_element[strcspn(temp_car_element, "\n")] = 0;
		fgets(temp_discount, 4, f); temp_discount[strcspn(temp_discount, "\n")] = 0;
		fgets(temp_price, 24, f); temp_price[strcspn(temp_price, "\n")] = 0;
		fgets(temp_amount, 3, f); temp_amount[strcspn(temp_amount, "\n")] = 0;

		if (atof(temp_amount) == 1) { //Uses correct grammar depending on if they bought a plural amount of cars
			printf("You bought 1 %s with a discount of %s%c for a total of %c%s\n", car_model_list[atoi(temp_car_element)], temp_discount, PERCENT_SIGN, POUND_SIGN, temp_price);
		}
		else {
			printf("You bought %s %s's with a discount of %s%c for a total of %c%s\n", temp_amount, car_model_list[atoi(temp_car_element)], temp_discount, PERCENT_SIGN, POUND_SIGN, temp_price);
		}
	}
	fclose(f);
	p("\n\nEnter X to go back: ");
	pressAnyKeyToClose;
}

int carModelListRead() {
	char temp_string[4] = ""; int temp_int = 0; //Initialise some temporary variables that will only be used in this function
	FILE* f = fopen("carStockList.txt", "r"); ifNullFile(f); //Opens the list of car models, then checks if it has opened properly
	for (int i = 0; i < 9; i++) {
		fgets(temp_string, 3, f);  //Gets the stock as a string, removes newline character
		temp_int = atoi(temp_string); //Typecasts the string from the file, turning it into a intiger
		car_stock_list[i] = temp_int;
	}
	fclose(f);//Close the file
}

int ifNullFile(f) {
	if (f == NULL) {  // Checks if the file can be opened or not (If it was succesfully created)
		perror("Unable to access file.\n"); return 1;//Prints an error message to console
	}
}

int lowerCaseFunc(upperString) {
	char* str = upperString; size_t len = strlen(str);
	char* lower = calloc(len + 1, sizeof(char)); //creates room in memory for the lower case version of the text
	for (size_t i = 0; i < len; ++i) { //for each character in the string
		lower[i] = tolower((unsigned char)str[i]); //append a lowercase version of the character to a list, overtime recreating a lowercase string
	}
	return lower; free(lower); //Returns the string (lower case), then frees the memory as we no longer need it to store the lower case version of the text
}

int fileExistsCheck(const char* filename) {
	struct stat buffer; //A system structure that stores infomation about files. Holds info like file permissions/ recent access dates etc
	int exist = stat(filename, &buffer);
	if (exist == 0) //If exist is 0, the file exists. If it is -1, it does not exist
		return 1; //Return a value of 1 if the file exists
	else
		return 0; //Return 0 if the file does not exist
}

int signUpFunction() {
	char entered_username[33] = ""; char entered_password[33] = ""; int entered_age = 0; char file_name[37] = ""; //Creates variables that holds the username, password, and age that the person wants to enter. Creats a string that will act as a filename.

	p("Please enter a username that is 4 to 32 characters long (Not case sensetive)\nEnter Here: "); scanf("%s", entered_username, 32);
	int username_length = strlen(entered_username);
	if (username_length > 32 || username_length < 4) { //If the entered usernmae is too short or too long
		clear; p("Please enter a username between 4 and 32 characters\n"); longLine;
		signUpFunction();
	} nLine;

	if (strcmp(lowerCaseFunc(entered_username), "admin") == 0) { //Doesn't allow the user to enter the username "admin" as this is reserved
		clear; p("Please enter a different username\n"); longLine;
		signUpFunction();
	} nLine;

	strcpy(entered_username, lowerCaseFunc(entered_username)); //Makes the entered username lowercase
	strcat(file_name, entered_username); strcat(file_name, ".txt"); //Creates the file name by adding ".txt" to the end of the username given

	if (fileExistsCheck(file_name)) { //if the file exists (returns 1 from the 'fileExistsCheck' function)
		clear; p("That username already exists\n"); longLine;
		signUpFunction();
	}

	p("Please enter a password that is 8 to 32 characters long (Case sensetive)\nEnter Here: "); scanf("%s", entered_password, 32);
	int password_length = strlen(entered_password);
	if (password_length > 32 || password_length < 8) {
		clear; p("Please enter a password between 8 and 32 characters\n"); longLine;
		signUpFunction();
	} nLine;

	p("Please enter your age: "); scanf("%d", &entered_age);
	char entered_age_string[4]; sprintf(entered_age_string, "%d", entered_age); //creates a second variable that holds the age as a string. This allows it to be written to the file. We then typecast the int to a string version.
	if (entered_age > 130 || entered_age < 17) {
		clear; p("Please enter an age between 17 and 130\n"); longLine;
		signUpFunction();
	} nLine;

	FILE* f = fopen(file_name, "w+"); //Create file variable and create the file with the ability to write
	ifNullFile(f);
	fprintf(f, "%s\n%s\n%s\n", entered_password, entered_age_string, entered_username); //Write the users infomation
	fclose(f); //Close the file
	clear; loginFunction(); //Allows the user to login
}

int loginFunction() {
	p("Please login below\n"); longLine;
	char entered_username[33] = ""; char entered_password[33] = ""; char file_name[37] = ""; char password_from_file[33] = ""; char age_from_file[4] = "";
	p("Please enter your username: "); scanf("%s", entered_username, 32);
	int username_length = strlen(entered_username);
	if (username_length > 32) {
		clear; p("Please enter a smaller username\n"); longLine;
		loginFunction();
	} nLine;

	strcpy(entered_username, lowerCaseFunc(entered_username)); //Makes the entered username lowercase
	strcat(file_name, entered_username); strcat(file_name, ".txt"); //Creates the file name by adding ".txt" to the end of the username given

	if (fileExistsCheck(file_name)) { //if the file exists (They have an account)

		FILE* f = fopen(file_name, "r"); fgets(password_from_file, 32, f); //Open the file that is named after there username, get the password from the first line

		p("Please enter your password: "); scanf("%s", entered_password, 32);
		int password_length = strlen(entered_password);
		if (password_length > 32) { //If the password is too long
			clear; p("Please enter a smaller password\n"); longLine;
			loginFunction();
		} nLine;

		password_from_file[strcspn(password_from_file, "\n")] = 0; //Removes the endline character from the password saved in the file, allowing us to compare them

		if (strcmp(entered_password, password_from_file) == 0) { //If the entered password and the password saved for that username are the same, then proceed
			clear; //User has succsefully logged in if this code is ran
			strcpy(username_global, entered_username); strcpy(password_global, entered_password);
			fgets(age_from_file, 4, f); age_from_file[strcspn(age_from_file, "\n")] = 0; //Removes the endline character from the age string
			user_age = atoi(age_from_file);
			fclose(f); // close the file
			menuChoice(entered_username);//pass the username into the next function
		}

		else {
			clear; p("Wrong password, please try again\n"); fclose(f); loginFunction();
		}
	}
	else {
		clear; p("You don't have an account with that username, please try again\n"); longLine; loginFunction();
	}
}

int authenticationPage() {
	clear; p("Welcome to Lewis's car dealership!\n"); longLine; char option;
	p("A: Sign up\nB: Login\nX: Exit\n"); option = getchar();

	switch (option)
	{
	case 'a': case 'A':
		clear; signUpFunction(); break;
	case 'b': case 'B':
		clear; loginFunction();  break;
	case 'x': case 'X':
		clear; goodByeMessage(); break;
	default:
		clear; p("Not a valid input\n"); longLine;
		authenticationPage(); break;
	}
}

void main() {
	carModelListRead(); loadSalesFigure(); //Functions used for pre-loading
	authenticationPage();
	goodByeMessage();
	nLine; nLine;
}
