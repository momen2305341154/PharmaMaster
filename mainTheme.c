#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>

#define MAX_PASSWORD_LENGTH 20
#define LINE_SIZE 200
int i;

struct Medicine
{
	char name[100];
	char genericName[100];
	float price;
	int quantity;
	char expiry_date[20];
} med, baseMed;

struct Customer
{
	char name[100];
	char address[100];
	char phone_number[15];
} customer;

struct User
{
	char username[50];
	char password[50];
	enum
	{
		ADMIN,
		CUSTOMER
	} type;
} user, customerUser;
COORD coord = {0, 0};
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function prototypes
void adminPanel(char *username, char *password);
void customerInterface();
void loginAdmin();
void loginCustomer();
void registerCustomer();
void addMedicine();
void updateMedicine();
void deleteMedicine();
void viewMedicineList();
int searchMedicine();
void browseMedicines();
int addToCart();
void viewCart();
void removeFromCart();
// int checkout();
void storeUser();
int verifyLogin(char *username, char *password, int userType);
void entryPasswordHide(char *password);
void flush_input_buffer();
// void disable_echo();
void enable_echo();
void viewCustomerInfo();
int printCurrentDateTime(void);
void getTerminalSize(int *rows, int *cols);
void box();
void wbox();
void blinkText(int x, int y, const char *text, int blinkTimes, int delayMicroseconds);
void colorCycleText(int x, int y, const char *text, int cycles, int delayMicroseconds);
void typeText(int x, int y, const char *text, int delayMicroseconds);
void plot();
void updateStock(struct Medicine med);
int checkout();
void get_input_with_asterisks(char *buffer, int length);

// Main function
int main()
{
	typeText(10, 1, "Welcome to our pharma master..........", 100000);

	printf("\n");
	printf("\033[36m");

	typeText(0, 10,

			 "    ____   __                                  __  ___           __  \n"
			 "   / __ \\/ /_  ____ __________ ___  ____ _   /  |/  /___ ______/ /____  _____\n"
			 "  / /_/ / __ \\/ __ `/ ___/ __ `__ \\/ __ `/  / /|_/ / __ `/ ___/ __/ _ \\/ ___/\n"
			 " / ____/ / / / /_/ / /  / / / / / / /_/ /  / /  / / /_/ (__  ) /_/  __/ /    \n"
			 "/_/   /_/ /_/\\__,_/_/  /_/ /_/ /_/\\__,_/  /_/  /_/\\__,_/____/\\__/\\___/_/   \n",
			 10000);
	printf("\n");

	blinkText(55, 30, "Hello ....", 10, 10000);
	system("pause");
	system("cls");

	printCurrentDateTime();

	int choice;

	do
	{
		system("cls");
		plot();
		// gotoxy(5,5);
		// printf("\n \t \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\ MEDICALE STORE   \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\  ");
		colorCycleText(5, 5, " \t \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PHARMA MASTER   \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  ", 10, 200000);
		gotoxy(7, 9);
		printf("\033[36m");
		printf("1. Admin Panel\n");
		gotoxy(7, 12);
		printf("2. Customer Interface\n");
		gotoxy(7, 15);
		printf("3. Exit\n");
		gotoxy(7, 18);
		printf("Enter your choice: ");
		scanf("%d", &choice);
		// system("cls");

		switch (choice)
		{
		case 1:
			loginAdmin();
			break;
		case 2:
			customerInterface();
			break;
		case 3:
			gotoxy(7, 20);
			printf("Exiting...\n");
			break;
		default:
			gotoxy(7, 20);
			printf("\033[31m");
			printf("Invalid choice. Please enter a valid option.\n");
		}
	} while (choice != 3);

	return 0;
}
// Admin Panel functions
void adminPanel(char *username, char *password)
{
	int choice;
	if (verifyLogin(username, password, ADMIN))
	{
		do
		{
			system("cls");
			plot();
			printf("\033[36m");
			gotoxy(7, 5);
			printf("Admin Options\n");
			gotoxy(7, 7);
			printf("1. Add Medicine\n");
			gotoxy(7, 9);
			printf("2. Update Medicine\n");
			gotoxy(7, 11);
			printf("3. Delete Medicine\n");
			gotoxy(7, 13);
			printf("4. View Medicine List\n");
			gotoxy(7, 15);
			printf("5. Search Medicine\n");
			gotoxy(7, 17);
			printf("6. view customer details\n");
			gotoxy(7, 19);
			printf("7. Logout\n");
			gotoxy(7, 21);
			printf("Enter your choice: ");
			scanf("%d", &choice);

			switch (choice)
			{
			case 1:
				addMedicine();
				break;
			case 2:
				updateMedicine();
				break;
			case 3:
				deleteMedicine();
				break;
			case 4:
				viewMedicineList();
				break;
			case 5:
				searchMedicine();
				break;
			case 6:
				viewCustomerInfo();
				break;
			case 7:
				gotoxy(7, 24);
				printf("\033[31m");
				printf("Logging out...\n");
				break;
			default:
				printf("\033[31m");
				printf("Invalid choice. Please enter a valid option.\n");
			}
		} while (choice != 7);
		system("pause");
	}
	else
	{
		// system("cls");
		gotoxy(7, 20);
		printf("\033[31m");
		printf("Invalid username or password.\n");
	}
}

void loginAdmin()
{
	char username[50];
	char password[MAX_PASSWORD_LENGTH];
	system("cls");
	plot();
	gotoxy(10, 7);
	printf("\033[34m");
	printf("Admin Panel\n");
	gotoxy(10, 10);
	printf("Login\n");
	gotoxy(10, 11);
	printf("Username: ");
	scanf("%s", username);
	gotoxy(10, 13);
	printf("Password: ");
	// disable_echo(); // for hiding password
	// getchar();
	// fgets(password, MAX_PASSWORD_LENGTH, stdin);
	get_input_with_asterisks(password, sizeof(password));

	enable_echo(); // for unhiding password
	// entryPasswordHide();
	password[strcspn(password, "\n")] = '\0';
	if (password != NULL)
	{

		adminPanel(username, password);
	}
}

void addMedicine()
{
	system("cls");
	plot();
	FILE *fileMedicine = fopen("medicine.txt", "r"); // Open the file in append mode

	if (fileMedicine == NULL)
	{
		gotoxy(7, 10);
		printf("\033[31m");
		printf("Error opening file!\n");
		exit(1);
	}
	// fprintf(fileMedicine, "Medicne name\t\t Generic Name\t\t Price\t\t Quantity\t\t Expiry Date\n"); // have to fix this line
	fileMedicine = fopen("medicine.txt", "a");

	printf("\033[34m");
	gotoxy(7, 8);
	printf("Enter medicine name: ");
	scanf("%s", &med.name);
	gotoxy(7, 10);
	printf("Enter generic name: ");
	scanf("%s", &med.genericName);
	gotoxy(7, 12);
	printf("Enter medicine price: ");
	scanf("%f", &med.price);
	gotoxy(7, 14);
	printf("Enter medicine quantity: ");
	scanf("%d", &med.quantity);
	flush_input_buffer();
	gotoxy(7, 16);
	printf("Enter the expiry date of the medicine (MM YYYY): ");
	fgets(med.expiry_date, sizeof(med.expiry_date), stdin);
	med.expiry_date[strcspn(med.expiry_date, "\n")] = '\0'; // Remove the newline character
	fprintf(fileMedicine, "%s %s %.2f %d %s\n", med.name, med.genericName, med.price, med.quantity, med.expiry_date);
	gotoxy(7, 20);
	printf("\033[32m");
	printf("Medicine added successfully....\n");
	gotoxy(7, 25);
	system("pause");

	fclose(fileMedicine);
}
void updateMedicine()
{
	system("cls");
	plot();
	FILE *fileMedicine = fopen("medicine.txt", "r");
	FILE *tempFile = fopen("temp.txt", "w");

	if (fileMedicine == NULL || tempFile == NULL)
	{
		gotoxy(7, 10);
		printf("\033[31m");
		printf("Error opening file!\n");
		exit(1);
	}

	// struct Medicine med;
	char searchName[50];
	int found = 0;
	// system("cls");
	gotoxy(10, 5);
	printf("\033[34m");
	printf("Update medicine:");
	gotoxy(7, 8);
	printf("Enter the medicine name to update: ");
	scanf("%s", searchName);

	// Convert searchName to lowercase (or uppercase) for case-insensitivity
	// for (int i = 0; searchName[i]; i++)
	// {
	// 	searchName[i] = tolower(searchName[i]);
	// }

	// Search for the medicine by name (case-insensitive and partial match)
	while (fscanf(fileMedicine, "%s %s %f %d %[^\n]s", med.name, med.genericName, &med.price, &med.quantity, med.expiry_date) != EOF)
	{
		// char medNameLower[50];
		// strcpy(medNameLower, med.name);
		// for (int i = 0; medNameLower[i]; i++)
		// {
		// 	medNameLower[i] = tolower(medNameLower[i]);
		// }

		if (strcmp(med.name, searchName) != 0)
		{
			fprintf(tempFile, "%s %s %.2f %d %s\n", med.name, med.genericName, med.price, med.quantity, med.expiry_date);
		}
		else
		{
			found = 1;
			gotoxy(7, 10);
			printf("Enter the new medicine name: ");
			scanf("%s", &med.name);
			gotoxy(7, 12);
			printf("Enter the new generic name: ");
			scanf("%s", &med.genericName);
			gotoxy(7, 14);
			printf("Enter the new price: ");
			scanf("%f", &med.price);
			gotoxy(7, 16);
			printf("Enter the new quantity: ");
			scanf("%d", &med.quantity);
			flush_input_buffer();
			gotoxy(7, 18);
			printf("Enter the new expiry date: ");
			fgets(med.expiry_date, sizeof(med.expiry_date), stdin);
			med.expiry_date[strcspn(med.expiry_date, "\n")] = '\0';
			fprintf(tempFile, "%s %s %.2f %d %s\n", med.name, med.genericName, med.price, med.quantity, med.expiry_date);
		}
	}
	fclose(fileMedicine);
	fclose(tempFile);
	remove("medicine.txt");
	rename("temp.txt", "medicine.txt");

	if (found)
	{
		gotoxy(7, 20);
		printf("\033[32m");
		printf("Medicine updated successfully.\n");
	}
	else
	{
		gotoxy(7, 20);

		printf("\033[31m");
		printf("Medicine not found.\n");
	}
	system("pause");
}
void deleteMedicine()
{
	system("cls");
	plot();
	printf("\033[34m");
	FILE *file = fopen("medicine.txt", "r");
	FILE *tempFile = fopen("temp.txt", "w");
	char medicineName[100];
	int found = 0;
	if (file == NULL || tempFile == NULL)
	{
		printf("\033[31m");
		printf("Error opening file.\n");
		return;
	}
	gotoxy(7, 8);
	printf("Enter the mame of the medicine that you wanna delete: ");
	scanf("%s", medicineName);
	while (fscanf(file, "%s %s %f %d %[^\n]s", med.name, med.genericName, &med.price, &med.quantity, med.expiry_date) != EOF)
	{
		if (strcmp(med.name, medicineName) != 0)
		{
			fprintf(tempFile, "%s\n%s\n%.2f\n%d\n%s\n", med.name, med.genericName, med.price, med.quantity, med.expiry_date);
		}
		else
		{
			found = 1;
		}
	}
	fclose(file);
	fclose(tempFile);
	remove("medicine.txt");
	rename("temp.txt", "medicine.txt");
	if (found)
	{
		gotoxy(7, 12);
		printf("\033[31m");
		printf("Medicine deleted successfully.\n");
	}
	else
	{
		gotoxy(7, 12);
		printf("\033[31m");
		printf("Medicine not found.\n");
	}
	system("pause");
}
void viewMedicineList()
{
	system("cls");
	plot();
	printf("\033[34m");
	FILE *fileMedicine = fopen("medicine.txt", "r"); // Open the file in read mode

	if (fileMedicine == NULL)
	{
		printf("Error opening file!\\n");
		exit(1);
	}

	int y = 10;

	gotoxy(7, 5);
	printf("Medicine List:\n");
	gotoxy(7, 8);
	printf("Medicine name\t Generic Name\t Price\t Quantity\t Expiry Date\n");

	// printf("Medicine name\t Generic Name\t Price\t Quantity\t Expiry Date\n");

	// Assuming 'med' is a struct that has been defined elsewhere
	while (fscanf(fileMedicine, "%s %s %f %d %[^\n]s", med.name, med.genericName, &med.price, &med.quantity, med.expiry_date) != EOF)
	{
		gotoxy(7, y);
		printf("\033[35m");
		printf("%s\t\t %s\t  %.2f\t%d\t\t  %s\n", med.name, med.genericName, med.price, med.quantity, med.expiry_date);
		y++;
	}

	fclose(fileMedicine);
	system("pause");
}

int searchMedicine()
{
	system("cls");
	plot();
	printf("\033[34m");
	FILE *file = fopen("medicine.txt", "r"); // Open in binary mode
	if (file == NULL)
	{
		gotoxy(7, 10);
		printf("\033[31m");
		perror("Error opening file");
		return -1; // Indicate error
	}
	char searchName[100];

	gotoxy(7, 8);

	printf("Enter the name of the medicine to search for: ");
	fscanf(stdin, "%s", searchName);

	// struct Medicine med;
	// int found = 0;
	while (fscanf(file, "%s %s %f %d %[^\n]s", med.name, med.genericName, &med.price, &med.quantity, med.expiry_date) != EOF)
	{
		// Add null terminator to the strings before comparing
		med.name[sizeof(med.name) - 1] = '\0';
		med.genericName[sizeof(med.genericName) - 1] = '\0';

		if (strcmp(med.name, searchName) == 0)
		{
			// found = 1;
			printf("\033[35m");
			gotoxy(7, 11);
			printf("Medicine found!\n");
			gotoxy(7, 14);
			printf("Medicine name: %s\n", med.name);
			gotoxy(7, 16);
			printf("Generic name: %s\n", med.genericName);
			gotoxy(7, 18);
			printf("Price: %.2f\n", med.price);
			gotoxy(7, 20);
			printf("Quantity: %d\n", med.quantity);
			gotoxy(7, 22);
			printf("Expiry date: %s\n", med.expiry_date);
			break;
		}
		else
		{
			gotoxy(7, 10);
			printf("\033[31m");
			printf("Medicine not found.\n");
		}
	}
	system("pause");
	fclose(file);
}
void viewCustomerInfo()
{
	system("cls");
	plot();
	printf("\033[34m");
	FILE *file = fopen("user.txt", "r");
	if (file == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	int y = 10;
	gotoxy(7, 5);
	printf("Customer Information:\n");
	gotoxy(7, 9);
	printf("Customer name\t Phone number\t Address\n");
	while (fscanf(file, "%s %s %s", customer.name, customer.phone_number, customer.address) != EOF)
	{
		gotoxy(7, y);

		printf("%s\t\t %s\t  %s\n", customer.name, customer.phone_number, customer.address);
		y += 2;
	}
	system("pause");
	fclose(file);
}

// Customer Interface functions
void customerInterface()
{
	system("cls");
	plot();
	printf("\033[34m");

	int choice;
	do
	{

		system("cls");
		plot();

		gotoxy(8, 10);

		printf("\033[36m");
		printf("Customer options: \n");
		gotoxy(7, 14);
		printf("1. Login customer Interface, \n");
		gotoxy(7, 16);
		printf("2. Register as a customer\n");
		gotoxy(7, 18);
		printf("3. Exit to main home page.\n");
		gotoxy(7, 20);
		printf("Enter your choice: ");

		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			loginCustomer();
			break;
		case 2:
			registerCustomer();
			break;
		case 3:
			gotoxy(7, 24);
			printf("\033[31m");
			printf("Exitting.... \n");

		default:
			break;
		}
	} while (choice != 3);
	system("pause");
}
void loginCustomer()
{
	int choice;
	char usernameCustomer[50];
	char passwordCustomer[MAX_PASSWORD_LENGTH];
	system("cls");
	plot();
	printf("\033[34m");
	gotoxy(8, 10);
	printf("Customer Panel\n");
	gotoxy(7, 11);
	printf("Login\n");
	gotoxy(7, 14);
	printf("Username: ");
	scanf("%s", usernameCustomer);
	gotoxy(7, 16);
	printf("Password: ");
	// disable_echo(); // for hiding password
	// getchar();
	// fgets(passwordCustomer, MAX_PASSWORD_LENGTH, stdin);
	get_input_with_asterisks(passwordCustomer, sizeof(passwordCustomer));

	enable_echo(); // for unhiding password
	passwordCustomer[strcspn(passwordCustomer, "\n")] = '\0';
	if (passwordCustomer != NULL)
	{

		if (verifyLogin(usernameCustomer, passwordCustomer, CUSTOMER))
		{
			do
			{
				system("cls");
				plot();
				printf("\033[34m");
				gotoxy(7, 5);
				printf("Customer Options\n");
				gotoxy(7, 7);
				printf("1. Browse Medicine\n");
				gotoxy(7, 9);
				printf("2. Add to curt Medicine\n");
				gotoxy(7, 11);
				printf("3. View cart Medicine\n");
				gotoxy(7, 13);
				printf("4. Remove Medicine from cart\n");
				gotoxy(7, 15);
				printf("5. Checkout Medicine\n");
				gotoxy(7, 17);
				printf("6. View medicine list\n");
				gotoxy(7, 19);
				printf("7. Logout\n");
				gotoxy(7, 22);
				printf("Enter your choice: ");
				scanf("%d", &choice);

				switch (choice)
				{
				case 1:
					searchMedicine();
					break;
				case 2:
					addToCart();
					break;
				case 3:
					viewCart();
					break;
				case 4:
					removeFromCart();
					break;
				case 5:
					checkout();
					break;
				case 6:
					viewMedicineList();
					break;
				case 7:
					gotoxy(7, 24);
					printf("\033[31m");
					printf("Logging out...\n");
					break;
				default:
					gotoxy(7, 24);
					printf("\033[31m");
					printf("Invalid choice. Please enter a valid option.\n");
				}
			} while (choice != 7);
			system("pause");
		}
		else
		{
			gotoxy(7, 15);
			printf("\033[31m");
			printf("Invalid username or password.\n");
			system("pause");
		}
	}
}

void registerCustomer()
{
	system("cls");
	plot();
	printf("\033[34m");
	FILE *file = fopen("customer.txt", "a");
	if (file == NULL)
	{
		gotoxy(7, 14);
		printf("Error opening file.\n");
		return;
	}

	char username[30];
	char password[30];

	gotoxy(7, 10);
	printf("Register your username and password:\n");
	gotoxy(7, 14);
	printf("User name: ");
	scanf("%s", username);
	gotoxy(7, 16);
	printf("Password: ");
	scanf("%s", password);

	fprintf(file, "%s %s\n", username, password);
	typeText(10, 20, "Congratulations! User registered successfully.\n", 100000);
	system("pause");

	fclose(file);
}
int addToCart()
{ // updated number of quantity to add
	system("cls");
	plot();
	printf("\033[34m");
	FILE *fileMedicine = fopen("medicine.txt", "r");
	FILE *fileCart = fopen("cart.txt", "a");
	if (fileMedicine == NULL || fileCart == NULL)
	{
		fprintf(stderr, "Error opening file!\n");
		return 1; // return error code
	}

	char searchName[50];
	gotoxy(7, 8);
	printf("Enter the medicine name to add to cart: ");
	fscanf(stdin, "%s", searchName);

	searchName[strcspn(searchName, "\n")] = 0; // remove newline character

	int found = 0;
	// Medicine med;
	while (fscanf(fileMedicine, "%s %s %f %d %[^\n]s", med.name, med.genericName, &med.price, &med.quantity, med.expiry_date) != EOF)
	{
		if (strcmp(med.name, searchName) == 0)
		{
			int quantityToAdd;
			gotoxy(8, 10);
			printf("Enter the quantity of %s to add to cart: ", med.name);
			scanf("%d", &quantityToAdd);
			if (quantityToAdd <= med.quantity)
			{
				fprintf(fileCart, "%s\t%s\t%.2f\t%d\t%s\n", med.name, med.genericName, med.price, quantityToAdd, med.expiry_date);
				found = 1;
			}
			else
			{
				gotoxy(8, 15);
				printf("Not enough stock available.\n");
			}
		}
	}
	fclose(fileMedicine);
	fclose(fileCart);
	if (found)
	{
		gotoxy(8, 12);
		printf("Medicine added to cart successfully.\n");
	}
	else
	{
		gotoxy(8, 12);
		printf("Medicine not found.\n");
	}
	system("pause");
	return 0; // return success code
}
void viewCart()
{
	system("cls");
	plot();
	printf("\033[34m");
	FILE *fileCart = fopen("cart.txt", "r");
	if (fileCart == NULL)
	{
		gotoxy(7, 10);
		printf("\033[31m");
		printf("Error opening file!\n");
		exit(1);
	}
	int y = 8;
	gotoxy(7, 5);
	printf("Cart:\n");
	gotoxy(7, 7);
	printf("Medicine name\t Generic Name\t Price\t Quantity\t Expiry Date\n");
	while (fscanf(fileCart, "%s %s %f %d %[^\n]s", med.name, med.genericName, &med.price, &med.quantity, med.expiry_date) != EOF)
	{
		gotoxy(7, y);
		printf("%s\t\t %s\t  %.2f\t%d\t\t  %s\n", med.name, med.genericName, med.price, med.quantity, med.expiry_date);
		y++;
	}
	system("pause");
	fclose(fileCart);
}

void removeFromCart()
{
	system("cls");
	plot();
	printf("\033[34m");
	FILE *fileCart = fopen("cart.txt", "r");
	FILE *tempFile = fopen("temp.txt", "w");
	if (fileCart == NULL || tempFile == NULL)
	{
		gotoxy(7, 10);
		printf("\033[34m");
		printf("Error opening file!\n");
		exit(1);
	}
	char searchName[50];
	int found = 0;

	gotoxy(7, 5);
	printf("Enter the medicine name to remove from cart: ");
	scanf("%s", searchName);
	while (fscanf(fileCart, "%s %s %f %d %[^\n]s", med.name, med.genericName, &med.price, &med.quantity, med.expiry_date) != EOF)
	{
		if (strcmp(med.name, searchName) != 0)
		{
			fprintf(tempFile, "%s %s %.2f %d %s\n", med.name, med.genericName, med.price, med.quantity, med.expiry_date);
		}
		else
		{
			found = 1;
		}
	}
	fclose(fileCart);
	fclose(tempFile);
	remove("cart.txt");
	rename("temp.txt", "cart.txt");
	if (found)
	{
		gotoxy(7, 7);
		printf("\033[32m");
		printf("Medicine removed from cart successfully.\n");
	}
	else
	{
		gotoxy(7, 7);
		printf("\033[31m");
		printf("Medicine not found in cart.\n");
	}
	system("pause");
}
/*
int checkout()
{
	system("cls");
	plot();
	FILE *fileCart = fopen("cart.txt", "r");
	if (fileCart == NULL)
	{
		fprintf(stderr, "Error opening file: %s\n", strerror(errno));
		return 1; // return error code
	}

	float totalCost = 0.0;
	FILE *fileBase = fopen("medicine.txt", "r+");
	if (fileBase == NULL)
	{
		fprintf(stderr, "Error opening base file: %s\n", strerror(errno));
		fclose(fileCart);
		return 1; // return error code
	}
	storeUser();

	// Medicine med, baseMed;
	char line[100];
	while (fgets(line, sizeof(line), fileCart) != NULL)
	{
		if (sscanf(line, "%49s %49s %f %d %19[^\n]", med.name, med.genericName, &med.price, &med.quantity, med.expiry_date) == 5)
		{
			float itemCost = med.price * med.quantity;
			totalCost += itemCost;

			fseek(fileBase, 0, SEEK_SET);
			long int pos = ftell(fileBase);
			while (fgets(line, sizeof(line), fileBase) != NULL)
			{
				if (sscanf(line, "%49s %49s %f %d %19[^\n]", baseMed.name, baseMed.genericName, &baseMed.price, &baseMed.quantity, baseMed.expiry_date) == 5)
				{
					if (strcmp(med.name, baseMed.name) == 0)
					{
						baseMed.quantity -= med.quantity;
						fseek(fileBase, pos, SEEK_SET);
						fprintf(fileBase, "%-49s %-49s %7.2f %4d %-19s\n", baseMed.name, baseMed.genericName, baseMed.price, baseMed.quantity, baseMed.expiry_date);
						fflush(fileBase);
						break;
					}
				}
				pos = ftell(fileBase);
			}
		}
		else
		{
			fprintf(stderr, "Error parsing line: %s\n", line);
			fclose(fileCart);
			fclose(fileBase);
			return 1; // return error code
		}
	}

	fclose(fileCart);
	fclose(fileBase);
	remove("cart.txt"); // Remove the cart file after checkout

	gotoxy(10, 10);
	printf("Total cost: %.2f\n", totalCost);
	typeText(10, 15, "Thank you for shopping.....", 100000);
	system("pause");
	return 0; // success
}
*/

// Other helper functions
void storeUser()
{
	FILE *fileUser = fopen("user.txt", "a");
	if (fileUser == NULL)
	{
		gotoxy(7, 10);
		printf("\033[31m");
		fprintf(stderr, "Error opening file!\n");
		exit(EXIT_FAILURE); // return error code
	}
	gotoxy(7, 7);
	printf("\033[34m");
	printf("Enter customer name: ");
	scanf("%s", customer.name);
	gotoxy(7, 8);
	printf("Enter customer phone number: ");
	scanf("%s", customer.phone_number);
	gotoxy(7, 9);
	printf("Enter customer address: ");
	scanf("%s", customer.address);
	fprintf(fileUser, "%s %s %s\n", customer.name, customer.phone_number, customer.address);
	gotoxy(7, 10);
	printf("Customer Name: %s\n", customer.name);
	gotoxy(7, 11);
	printf(
		"Customer phone number: %s\n", customer.phone_number);
	gotoxy(7, 12);
	printf(
		"Customer address: %s\n", customer.address);
	fclose(fileUser);
	system("pause");

	// Implement functionality to store user
}

int verifyLogin(char *username, char *password, int userType)
{

	// Implement functionality to verify login
	if (userType == ADMIN)
	{
		FILE *file = fopen("admin.txt", "r");
		if (file == NULL)
		{
			printf("Error opening database. Admmin authentication failed.\n");
			return 0;
		}
		else
		{
			char storedUsernameAdmin[20];
			char storedPasswordAdmin[20];

			int authenticated = 0;
			while (fscanf(file, "%s %s", storedUsernameAdmin, storedPasswordAdmin) != EOF)
			{
				if (strcmp(username, storedUsernameAdmin) == 0 && strcmp(password, storedPasswordAdmin) == 0)
				{
					authenticated = 1;
					break;
				}
			}
			fclose(file);
			return authenticated;
		}
	}
	if (userType == CUSTOMER)
	{
		FILE *file = fopen("customer.txt", "r");
		if (file == NULL)
		{
			printf("Error opening database. user authentication failed.\n");
			return 0;
		}
		else
		{
			char storedUsername[20];
			char storedPassword[20];
			int authenticated = 0;
			while (fscanf(file, "%s %s", storedUsername, storedPassword) != EOF)
			{
				if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0)
				{
					authenticated = 1;
					break;
				}
			}
			fclose(file);
			return authenticated;
		}
	}
	return 0;
}

void entryPasswordHide(char *password)
{
	// char password[MAX_PASSWORD_LENGTH];

	// printf("Enter password: ");
	// disable_echo();
	getchar();
	fgets(password, MAX_PASSWORD_LENGTH, stdin);
	enable_echo();
	// Implement functionality to encrypt password
}

void flush_input_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

/*void disable_echo()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_ECHO_INPUT; // Disable echo input
	SetConsoleMode(hStdin, mode);
}

void enable_echo()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode |= ENABLE_ECHO_INPUT; // Enable echo input
	SetConsoleMode(hStdin, mode);
}
*/
void get_input_with_asterisks(char *buffer, int length)
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	DWORD oldMode = mode;

	mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT); // Disable echo and line input
	SetConsoleMode(hStdin, mode);

	int i = 0;
	while (i < length - 1)
	{
		char ch;
		DWORD read;
		ReadConsoleA(hStdin, &ch, 1, &read, NULL);
		if (ch == '\r')
		{ // Carriage return (Enter key)
			break;
		}
		else if (ch == '\b')
		{ // Backspace
			if (i > 0)
			{
				printf("\b \b"); // Erase the asterisk from console
				i--;
			}
		}
		else
		{
			buffer[i++] = ch;
			printf("*");
		}
	}
	buffer[i] = '\0';
	printf("\n");

	// Restore the original console mode
	SetConsoleMode(hStdin, oldMode);
}

// Function to enable echo input
void enable_echo()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode |= ENABLE_ECHO_INPUT; // Enable echo input
	SetConsoleMode(hStdin, mode);
}

int printCurrentDateTime(void)
{
	time_t now = time(0);					// get current time
	struct tm *localTime = localtime(&now); // convert to local time format

	// Format the date and time correctly
	int day = localTime->tm_mday;
	int month = localTime->tm_mon + 1;	  // tm_mon is 0-11, add 1 to get 1-12
	int year = localTime->tm_year + 1900; // tm_year is years since 1900

	int hour = localTime->tm_hour;
	int minute = localTime->tm_min;
	int second = localTime->tm_sec;

	// Move cursor to the desired positions and print date and time
	gotoxy(60, 2);
	printf("\033[36m"); // text color cyan
	printf("Date: %02d-%02d-%d\n", day, month, year);

	gotoxy(60, 4);

	printf("Time: %02d:%02d:%02d\n", hour, minute, second);
	printf("\033[0m"); // reset color
	return 0;
}

void box()
{
	int i;
	printf("\033[35m");

	// Draw the top and bottom borders
	for (i = 3; i <= 120; i++)
	{
		gotoxy(i, 3);
		printf("%c", 219); // Top border
		gotoxy(i, 45);
		printf("%c", 219); // Bottom border
	}

	// Draw the left and right borders
	for (i = 3; i <= 120; i++)
	{
		gotoxy(3, i);
		printf("%c", 219); // Left border
		gotoxy(125, i);
		printf("%c", 219); // Right border
	}

	// Draw corners
	gotoxy(3, 3);
	printf("%c", 219); // Top-left corner
	gotoxy(120, 3);
	printf("%c", 219); // Top-right corner
	gotoxy(3, 120);
	printf("%c", 219); // Bottom-left corner
	gotoxy(120, 120);
	printf("%c", 219); // Bottom-right corner
}
void wbox()
{
	int i;
	int left = 5, top = 5;
	int right = 110, bottom = 100;
	printf("\033[37m");
	// Draw top and bottom borders
	for (i = left; i <= right; i++)
	{
		gotoxy(i, top);
		printf("%c", 196); // Horizontal line (ASCII 196)
		gotoxy(i, bottom);
		printf("%c", 196); // Horizontal line (ASCII 196)
	}

	// Draw left and right borders
	for (i = top; i <= bottom; i++)
	{
		gotoxy(left, i);
		printf("%c", 179); // Vertical line (ASCII 179)
		gotoxy(right, i);
		printf("%c", 179); // Vertical line (ASCII 179)
	}

	// Draw corners
	gotoxy(left, top);
	printf("%c", 218); // Top-left corner (ASCII 218)
	gotoxy(right, top);
	printf("%c", 191); // Top-right corner (ASCII 191)
	gotoxy(left, bottom);
	printf("%c", 192); // Bottom-left corner (ASCII 192)
	gotoxy(right, bottom);
	printf("%c", 217); // Bottom-right corner (ASCII 217)
	printf("\033[0m");
}
void getTerminalSize(int *rows, int *cols)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	*cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	*rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void blinkText(int x, int y, const char *text, int blinkTimes, int delayMicroseconds)
{
	for (int i = 0; i < blinkTimes; i++)
	{
		gotoxy(x, y);
		// Print text in red
		printf("\033[31m%s\033[0m", text); // ANSI escape code for red text
		fflush(stdout);
		usleep(delayMicroseconds);

		gotoxy(x, y);
		// Clear the text (print spaces)
		printf("      "); // Adjust the number of spaces based on the text length
		fflush(stdout);
		usleep(delayMicroseconds);
	}
}
// Function to cycle through colors for a piece of text
void colorCycleText(int x, int y, const char *text, int cycles, int delayMicroseconds)
{
	const char *colors[] = {
		"\033[31m", // Red
		"\033[32m", // Green
		"\033[34m", // Blue
		"\033[35m", // Magenta
		"\033[36m", // Cyan
		"\033[37m", // White
	};
	int numColors = sizeof(colors) / sizeof(colors[0]);

	for (int i = 0; i < cycles; i++)
	{
		gotoxy(x, y);
		printf("%s%s\033[0m", colors[i % numColors], text);
		fflush(stdout);
		usleep(delayMicroseconds);
	}
}
void typeText(int x, int y, const char *text, int delayMicroseconds)
{
	gotoxy(x, y);

	while (*text)
	{
		putchar(*text++);
		fflush(stdout);
		usleep(delayMicroseconds);
	}
}
void plot()
{
	box();
	wbox();
	printCurrentDateTime();
}

void updateStock(struct Medicine med)
{
	FILE *fileBase = fopen("medicine.txt", "r+");
	FILE *tempFile = fopen("temp.txt", "w");

	if (fileBase == NULL || tempFile == NULL)
	{
		perror("Error opening files");
		return;
	}

	char line[LINE_SIZE];
	struct Medicine baseMed;
	int updated = 0;

	while (fgets(line, sizeof(line), fileBase) != NULL)
	{
		if (sscanf(line, "%99s %99s %f %d %19[^\n]", baseMed.name, baseMed.genericName, &baseMed.price, &baseMed.quantity, baseMed.expiry_date) == 5)
		{
			if (strcmp(med.name, baseMed.name) == 0)
			{
				baseMed.quantity -= med.quantity;
				updated = 1;
			}
			fprintf(tempFile, "%s %s %.2f %d %s\n", baseMed.name, baseMed.genericName, baseMed.price, baseMed.quantity, baseMed.expiry_date);
		}
		else
		{
			// Copy non-matching lines as-is
			fputs(line, tempFile);
		}
	}

	fclose(fileBase);
	fclose(tempFile);

	if (updated = 1)
	{
		// Replace the original file with the updated one
		remove("medicine.txt");
		rename("temp.txt", "medicine.txt");
		gotoxy(7, 15);
		printf("Stock updated successfully!\n");
	}
	else
	{
		gotoxy(7, 15);
		printf("Medicine not found in the stock.\n");
	}
}
// Function to handle the checkout process
int checkout()
{
	system("cls"); // Clear the console
	plot();

	FILE *fileCart, *fileBase;
	char line[LINE_SIZE];
	float totalCost = 0.0;

	// Open the cart and base files
	fileCart = fopen("cart.txt", "r");
	if (fileCart == NULL)
	{
		gotoxy(7, 10);
		printf("\033[31m");
		fprintf(stderr, "Could not open cart.txt\n");
		return 1;
	}

	fileBase = fopen("medicine.txt", "r+");
	if (fileBase == NULL)
	{
		gotoxy(7, 10);
		printf("\033[31m");
		fprintf(stderr, "Could not open medicine.txt\n");
		fclose(fileCart);
		return 1;
	}
	storeUser();

	// Read each line from the cart file
	while (fgets(line, sizeof(line), fileCart) != NULL)
	{
		// Parse the line from the cart file
		if (sscanf(line, "%99s %99s %f %d %19[^\n]", med.name, med.genericName, &med.price, &med.quantity, med.expiry_date) == 5)
		{
			float itemCost = med.price * med.quantity;
			totalCost += itemCost;

			// Update the stock in the base file
			updateStock(med);
		}
		else
		{
			fprintf(stderr, "Error parsing line: %s\n", line);
			fclose(fileCart);
			fclose(fileBase);
			return 1; // Return error code
		}
	}
	viewCart();

	fclose(fileCart);
	fclose(fileBase);
	remove("cart.txt"); // Remove the cart file after checkout

	gotoxy(7, 20);
	printf("Total cost: %.2f\n", totalCost);
	typeText(9, 24, "Thanks for shoping... See you again...\n", 100000);
	system("pause"); // Pause the system to view the total cost
	return 0;
}
