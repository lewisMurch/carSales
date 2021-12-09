#include <stdio.h> //Allow for printf and scanf
#include <math.h> //Allow for maths functions
#include <ctype.h> 
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include<sys/stat.h> //check if file exists
#include <time.h>
#include <locale.h>
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

//Global Variables 
int user_age; char username_global[33] = ""; char password_global[33] = "";
const char* car_model_list[9] = { "Lamborghini","Ferrari","Bugatti", "Mercedes", "BMW", "Tesla", "Range Rover", "Saab", "Ford" };
float car_price_list[9] = { 360000.00, 290000.00, 3800000.00, 65750.00, 40000.00, 40000.00, 80000.00, 25000.00, 12000.00 };
const int* car_stock_list[9] = { 0 };
float sales_figure_total[9] = { 0 };
int car_amount_sold[9] = { 0 };
int car_model_list_highest_first[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

float sales_figure_total_highest_first[9] = { 0 };

int car_stock_list_highest_first[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int car_amount_sold_highest_first[9] = { 0 };

//A list of font options that the user can choose from, allowing them to find the most appropriate option
void accessiblitySettings() {
	char option;
	fseek(stdin, 0, SEEK_END); //clears the input buffer
	p("\x1b[4;mFont Settings\n");
	p("\x1b[0;mA: Underline text   B: Italic text   C: Eye strain safety mode   D: No text effect\n");
	option = getchar();
	switch (option)
	{
	case 'a': case 'A':
		p("\x1b[4mx");
		break;

	case 'b': case 'B':
		p("\x1b[3mx"); 
		break;

	case 'c': case 'C':
		p("\x1b[2mx"); 
		break;

	case 'd': case 'D':
		pass;
		break;

	default:
		clear; p("Invalid Input\n"); nLine;
		break; accessiblitySettings();
	}
	accessiblitySettings2();
}

//A list of font colours that the user can choose from, allowing them to find the most appropriate option
int accessiblitySettings2() {
	fseek(stdin, 0, SEEK_END); //clears the input buffer
	char option; clear;
	p("Font colour settings\n");
	p("A: Red   B: Green   C: Yellow   D: Blue   E: Magenta   F: Cyan   G: White   H: Black\n");
	option = getchar();
	switch (option)
	{
	case 'a': case 'A':
		p("\x1b[31mx");
		accessiblitySettings3(); break;

	case 'b': case 'B':
		p("\x1b[32mx"); 
		accessiblitySettings3(); break;

	case 'c': case 'C':
		p("\x1b[33mx"); 
		accessiblitySettings3(); break;

	case 'd': case 'D':
		p("\x1b[34mx"); 
		accessiblitySettings3(); break;

	case 'e': case 'E':
		p("\x1b[35mx"); 
		accessiblitySettings3(); break;

	case 'f': case 'F':
		p("\x1b[36mx"); 
		accessiblitySettings3(); break;

	case 'g': case 'G':
		p("\x1b[37mx"); 
		accessiblitySettings3(); break;

	case 'h': case 'H':
		p("\x1b[30;47mx"); //Makes the text black as shown, but the background black so the user can acutally see the text of the next page
		accessiblitySettings3(); break;

	default:
		clear; p("Invalid Input"); nLine;
		accessiblitySettings2(); break;
	}
}

//A list of background colours that the user can choose from, allowing them to find the most appropriate option
int accessiblitySettings3() {
	fseek(stdin, 0, SEEK_END); //clears the input buffer
	char option; clear;
	p("background colour settings\n");
	p("A: Red   B: Green   C: Yellow   D: Blue   E: Magenta   F: Cyan   G: White   H: Black\n");
	option = getchar();
	switch (option){

	case 'a': case 'A':
		p("\x1b[41mx");
		authenticationPage(); break;

	case 'b': case 'B':
		p("\x1b[42mx");
		authenticationPage(); break;

	case 'c': case 'C':
		p("\x1b[43mx");
		authenticationPage(); break;

	case 'd': case 'D':
		p("\x1b[44mx");
		authenticationPage(); break;

	case 'e': case 'E':
		p("\x1b[45mx");
		authenticationPage(); break;

	case 'f': case 'F':
		p("\x1b[46mx");
		authenticationPage(); break;

	case 'g': case 'G':
		p("\x1b[47mx");
		authenticationPage(); break;

	case 'h': case 'H':
		p("\x1b[40mx"); //Makes the text black as shown, but the background black so the user can acutally see the text of the next page
		authenticationPage(); break;

	default:
		clear; p("Invalid Input"); nLine;
		accessiblitySettings2(); break;
	}
}

/*The three accessibility settings sections above are very important to users who stuggle to read text on a screen
They help with my dyslexia as I can select a colour way that creates more contrast*/

//A function to allow the user to go back to the menu selection 
void pressXToExit(void (*f)() ) { //This parameter allows us to pass a function as a parameter. This function is the function called when the users presses X
	fseek(stdin, 0, SEEK_END); //Clears the input to stop if from being read after the fact
	char ch;
	scanf("%c", &ch);
	if (ch == 'x' || ch == 'X') {
		clear;	f();
	}
	else {
		pressXToExit(f);
	}
}

//A simple function that swaps the two inputted value in an array (used for my bubble sort)
void swap(int* x, int* y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

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

//Saves the users purchase information to a file named after them. Also saves the sales figure information to file.
int saveInvoice(car_element, price, amount) {
	char age_string[128]; char discount_string[128] = "0"; 	char amount_string[128]; char car_element_string[128]; float* price_pointer = price; //set a pointer to hold the data passed into it by the price calculator function
	char file_name[45] = "invoice-"; 
	strcat(file_name, username_global); strcat(file_name, ".txt"); //Creates the file name by adding ".txt" to the end of the username given
	FILE* f = fopen(file_name, "a"); ifNullFile(f);

	time_t now = time(NULL); //gets the time in seconds 
	struct tm* ptm = localtime(&now); //provides a structure tm with all the differnt components of our time (like day months and year)

	if (user_age >= 65) {
		strcpy(discount_string, "25"); //sets the percentage removed as a string if the user is 65 or over so we can write it to the file
	}
	sprintf(age_string, "%d", user_age); sprintf(car_element_string, "%d", car_element); sprintf(amount_string, "%d", amount);
	fprintf(f, "%s\n%s\n%.2f\n%s\n%02d\n%02d\n%04d\n", car_element_string, discount_string, *price_pointer, amount_string, ptm->tm_mday, ptm->tm_mon, ptm->tm_year + 1900);

	fclose(f);

	char temp_string[64]; char str[20];
	FILE* f2 = fopen("salesFigure.txt", "w+"); ifNullFile(f2);
	for (int i = 0; i < 9; i++) {
		fprintf(f2, "%.2f\n", sales_figure_total[i]);
		sprintf(str, "%d", car_amount_sold[i]);
		fprintf(f, str); fprintf(f, "\n"); //writes each element one by one to the file
	}
	fclose(f2);
}

//Gets all the sales figues from the file and stores them in an array
int loadSalesFigure() {
	char temp_string[24] = ""; float temp_float; int temp_int;
	FILE* f = fopen("salesFigure.txt", "r"); ifNullFile(f);

	for (int i = 0; i < 9; i++) {
		fgets(temp_string, 30, f); temp_string[strcspn(temp_string, "\n")] = 0; //Gets the price as a string, removes newline character
		temp_float = atof(temp_string); //Typecasts the string from the file, turning it into a float
		sales_figure_total[i] = temp_float;

		fgets(temp_string, 30, f); temp_string[strcspn(temp_string, "\n")] = 0; //Gets the amount sold as a string, removes newline character
		temp_int = atoi(temp_string); //Typecasts the string from the file, turning it into a float
		car_amount_sold[i] = temp_int;
	}
	fclose(f);
}

//A function that loads the stock information from the file into the array
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

//A function that allows the ADMIN user to view total car sales, listed in either "amount sold" or "revenue earned" first
int viewAdminSales() {

	loadSalesFigure();
	char temp_string[30] = ""; float temp_float; int temp_amount;
	int check_var = 0;
	char option;

	FILE* f = fopen("salesFigure.txt", "r"); ifNullFile(f);

	loadSalesFigure();
	for (int i = 0; i < 9; i++) { //Makes sure the "highest first" list is up-to-date for each respective array
		sales_figure_total_highest_first[i] = sales_figure_total[i];
		car_amount_sold_highest_first[i] = car_amount_sold[i];
		car_model_list_highest_first[i] = i;
	}

	p("A: Sort by total revenue\nB: Sort by total amount sold\nX: Back\n"); accurateInput;
	switch (option){
	case 'a': case 'A':
		clear;
		//Bubble sort to sort the cars in order of most revenue first
		int i, j;
		for (i = 0; i < 8; i++) 
			for (j = 0; j < 8 - i; j++)
				if (sales_figure_total_highest_first[j] < sales_figure_total_highest_first[j + 1]) {
					swap(&sales_figure_total_highest_first[j], &sales_figure_total_highest_first[j + 1]);
					swap(&car_amount_sold_highest_first[j], &car_amount_sold_highest_first[j + 1]);
					swap(&car_model_list_highest_first[j], &car_model_list_highest_first[j + 1]);
				}
		break;
	case 'b': case 'B':
		clear;
		//Bubble sort to sort the cars in order of highest amount sold first
		int x, y;
		for (x = 0; x < 8; x++)
			for (y = 0; y < 8 - x; y++)
				if (car_amount_sold_highest_first[y] < car_amount_sold_highest_first[y + 1]) {
					swap(&sales_figure_total_highest_first[y], &sales_figure_total_highest_first[y + 1]);
					swap(&car_amount_sold_highest_first[y], &car_amount_sold_highest_first[y + 1]);
					swap(&car_model_list_highest_first[y], &car_model_list_highest_first[y + 1]);
				}
		break;

	case 'x': case 'X':
		pressXToExit(menuChoice());
		break;

	default:
		clear; p("Not a valid input\n"); longLine;
		viewAdminSales(); break;
	}

	p("Lifetime car sales\n"); longLine;
	for (int i = 0; i < 9; i++) { //For each car model in the list
		if (sales_figure_total_highest_first[i] > 0) { //Only prints cars that have sold, meaning there is less clutter 
			printf("%c%.2f - %s - %d sold\n", POUND_SIGN, sales_figure_total_highest_first[i], car_model_list[car_model_list_highest_first[i]], car_amount_sold_highest_first[i]);
		}
	}

	fclose(f); nLine; 
	p("Press X to go back"); nLine;
	pressXToExit(viewAdminSales);
}

//A function that allows the user to choose from 4 basic options. It checks if they are an admin or not. It takes a username as a parameter to check for admin status
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
			menuChoice(); break;
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
			menuChoice(); break;
		}
	}
}

//A function that allows a user to see what cars are in stock, sorted in desending order
int viewCarFunction() {
	clear;	char temp_string[3] = ""; int temp_int;
	FILE* f = fopen("carStockList.txt", "r"); ifNullFile(f);

	loadStock(); //Makes sure the normal stock array is up to date

	for (int i = 0; i < 9; i++) { //Makes sure the "highest first" list is up-to-date
		car_stock_list_highest_first[i] = car_stock_list[i];
	}

	//Bubble sort to sort the cars in order of most in-stock first
	int car_model_list_amount_ordered[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	int i, j;
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8 - i; j++)
			if (car_stock_list_highest_first[j] < car_stock_list_highest_first[j + 1]) {
				swap(&car_stock_list_highest_first[j], &car_stock_list_highest_first[j + 1]);
				swap(&car_stock_list_highest_first[j], &car_stock_list_highest_first[j + 1]);
				swap(&car_stock_list_highest_first[j], &car_stock_list_highest_first[j + 1]);

				swap(&car_model_list_amount_ordered[j], &car_model_list_amount_ordered[j + 1]);
				swap(&car_model_list_amount_ordered[j], &car_model_list_amount_ordered[j + 1]);
				swap(&car_model_list_amount_ordered[j], &car_model_list_amount_ordered[j + 1]);
			}

	p("Stock list\n"); longLine;
	for (int i = 0; i < 9; i++) { //For each car model in the list
		if (car_stock_list_highest_first[i] > 1) { //Only prints cars that have sold, meaning there is less clutter 
			printf("%d - %s\n", car_stock_list_highest_first[i], car_model_list[car_model_list_amount_ordered[i]]);
		}
	}
	p("Press X to exit");
	fclose(f); nLine; pressXToExit(menuChoice);
}

//A function for calculating the price of a purchase, taking into consideration user age as a way of offering a discount
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
	printf("Continue with purchase? %d %s for a total of %c%.2f\nA: Yes\nB: No\n", amount, car_model_list[*choice - 1], POUND_SIGN, price); char option2; while ((getchar()) != '\n'); option2 = getchar();//Makes sure it accurately reads the users input, instead of reading all the characters after it should have stopped
	switch (option2)
	{
	case 'a': case 'A':
		clear; p("Thank you for purchasing from us! You'll be redirected shortly\n");

		int chosen_stock = car_stock_list[*choice - 1]; 
		chosen_stock -= amount; 
		car_stock_list[*choice - 1] = chosen_stock;//Edits the array by creating a temp int variable that is used to replace the value of the stock array

		float chosen_price = sales_figure_total[*choice - 1]; 
		chosen_price += price; 
		sales_figure_total[*choice - 1] = chosen_price; //Updates the total revenue per car model

		int amount_sold = car_amount_sold[*choice - 1];
		amount_sold += amount;
		car_amount_sold[*choice - 1] = amount_sold;

		saveStockToFile(); //Writes the new array to a file right after it is edited
		saveInvoice(*choice - 1, &price, amount); //pass price as a pointer so it isn't lost when the function closes
		Sleep(3000);
		authenticationPage();

	case 'b': case 'B':
		clear; buyCarFunction(); break;
	default:
		clear; p("Not a valid input\n"); longLine;
		priceCalculator(&choice); break;
	}
}

//A function that allows the user to choose which car they want to buy
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

//A function that allows an individual user to see there car names, amounts, cost and dates of purchase.
int viewSaleFunction() {
	loadStock();
	clear; p("Previous sales on this account\n"); p("===============================\n\n"); 
	char file_name[64] = ""; char temp_car_element[4]; char temp_discount[4]; char temp_price[24]; char temp_amount[3];
	char day[3]; char month[3]; char year[5]; char months[12][12] = {"January", "Febuary", "March", "April", "May", "June", "July", "Agust", "September", "October", "November", "December"};
	strcat(file_name, "invoice-"); strcat(file_name, username_global); strcat(file_name, ".txt");

	//Reads the amount of lines in the file, allowing us to iterate throught the file an apporpraite number of times
	FILE* f = fopen(file_name, "r"); ifNullFile();
	int line_count = 0; char temp_char = "";
	while (temp_char != EOF){
		temp_char = fgetc(f);
		if (temp_char == '\n') {
			line_count++;
		}
	}
	fseek(f, 0, SEEK_SET);

	if (line_count < 2) {
		p("There are no previously bought cars on this account\n")
	}
	else {
		line_count /= 7; //divied by 3 as we need to run the code below every three lines
		for (int i = 0; i < line_count; i++) {

			fgets(temp_car_element, 4, f); temp_car_element[strcspn(temp_car_element, "\n")] = 0;
			fgets(temp_discount, 4, f); temp_discount[strcspn(temp_discount, "\n")] = 0;
			fgets(temp_price, 24, f); temp_price[strcspn(temp_price, "\n")] = 0;
			fgets(temp_amount, 3, f); temp_amount[strcspn(temp_amount, "\n")] = 0;

			fgets(day, 4, f);
			int int_day = atoi(day);
			fgets(month, 4, f);
			int int_month = atoi(month);
			fgets(year, 6, f); year[strcspn(year, "\n")] = 0;

			if (atof(temp_amount) == 1) { //Uses correct grammar depending on if they bought a plural amount of cars
				printf("* You bought 1 %s with a discount of %s%c for a total of %c%s\x1b[0m\n", car_model_list[atoi(temp_car_element)], temp_discount, PERCENT_SIGN, POUND_SIGN, temp_price); //Highlighted the prices in green so the user can more easily see them
			}
			else {
				printf("* You bought %s %s's with a discount of %s%c for a total of %c%s\x1b[0m\n", temp_amount, car_model_list[atoi(temp_car_element)], temp_discount, PERCENT_SIGN, POUND_SIGN, temp_price);
			}
			p("  Date of purchase: ");
			switch (int_day){
			case 1:
				printf("%dst " ,int_day);
				break;
			case 2:
				printf("%dnd ", int_day);
				break;
			case 3:
				printf("%drd ", int_day);
				break;
			default:
				printf("%dth ", int_day);
			}
			printf("%s %s\n\n", months[int_month], year);
		}	
	}

	fclose(f);
	p("\n\nEnter X to go back: ");
	nLine; pressXToExit(menuChoice);
}

//A function that updates the car stock array from the file
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

//A function that checks if a file is openable, accepts a file variable as a parameter
int ifNullFile(f) {
	if (f == NULL) {  // Checks if the file can be opened or not (If it was succesfully created)
		perror("Unable to access file.\n"); //Prints an error message to console
		return 1;
	}
}

//A function that takes an uppercase string and returns a lowercase one
int lowerCaseFunc(upperString) {
	char* str = upperString; size_t len = strlen(str);
	char* lower = calloc(len + 1, sizeof(char)); //creates room in memory for the lower case version of the text
	for (size_t i = 0; i < len; ++i) { //for each character in the string
		lower[i] = tolower((unsigned char)str[i]); //append a lowercase version of the character to a list, overtime recreating a lowercase string
	}
	return lower; free(lower); //Returns the string (lower case), then frees the memory as we no longer need it to store the lower case version of the text
}

//A function that checks if a file exists, takes a filename as a paramater
int fileExistsCheck(const char* filename) {
	struct stat buffer; //A system structure that stores infomation about files. Holds info like file permissions/ recent access dates etc
	int exist = stat(filename, &buffer);
	if (exist == 0) //If exist is 0, the file exists. If it is -1, it does not exist
		return 1; //Return a value of 1 if the file exists
	else
		return 0; //Return 0 if the file does not exist
}

//A function that allows the user to create a new account by entering in some details
//It creates a file that holds your information for later validation
int signUpFunction() {
	char entered_username[33] = ""; char entered_password[33] = ""; int entered_age = 0; char file_name[37] = ""; //Creates variables that holds the username, password, and age that the person wants to enter. Creats a string that will act as a filename.

	p("Please enter a username that is 4 to 32 characters long (Not case sensetive)\nEnter Here: "); scanf("%s", entered_username, 32);
	int username_length = strlen(entered_username);
	if (username_length > 32 || username_length < 4) { //If the entered usernmae is too short or too long
		clear;
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

//A function that allows you to login. It searches for a file based off of your username
//If it finds one, it will check the entered password off of the password in the file
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

//This is the main menu BEFORE you login. It allows you to select a variety of differnt core choices
//such as logging in, signing up and more
int authenticationPage() {
	_Bool valid = 0;
	while (valid == 0) {
		p("Welcome to Lewis's car dealership!\n"); char option; //prints the title
		p("A: Sign up\nB: Login\nC: Accessibility settings\nX: Exit\n");
		option = getchar();
		switch (option)
		{
		case 'a': case 'A':
			clear; signUpFunction(); valid = 1;
			fseek(stdin, 0, SEEK_END); //clears the input buffer
			break;

		case 'b': case 'B':
			clear; loginFunction(); valid = 1;
			fseek(stdin, 0, SEEK_END);
			break;

		case 'c': case 'C':
			clear; accessiblitySettings(); valid = 1;
			fseek(stdin, 0, SEEK_END);
			break;

		case 'x': case 'X':
			clear; goodByeMessage(); valid = 1;
			fseek(stdin, 0, SEEK_END);
			break;

		default:
			fseek(stdin, 0, SEEK_END); 
			clear;
		}
	}

}

//The main function where the pre-load functions are called and the authentication function is started. 
//At the end, the goodbye message is called when the user quits the application.

void main() {
	carModelListRead(); loadSalesFigure(); //Functions used for pre-loading
	authenticationPage();
	goodByeMessage();
	nLine; nLine;
}
