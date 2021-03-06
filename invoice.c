#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

struct items{
	char item[30];
	float price;
	int qty;
};

struct orders {
	char customer[50];
	char date[50];
	int numOfItems;
	struct items itm[50];
};

// Functions to generate bills
void generateBillHeader(char name[50], char date[30]) {
	printf("\n\n");
	printf("\t    Cafe House Invoice");
	printf("\n\t    ------------------");
	printf("\nDate: %s",date);
	printf("\nInvoice To: %s",name);
	printf("\n");
	printf("-----------------------------------------------\n");
	printf("Items\t\t\t");
	printf("Quantity\t");
	printf("Total\t");
	printf("\n-----------------------------------------------");
	printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price) {
	printf("%s\t\t", item);
	printf("%d\t\t", qty);
	printf("%.2f\t\t", qty * price);
	printf("\n");
}

void generateBillFooter(float total) {
	printf("\n");
	float discount = 0.01 * total;
	float netTotal = total - discount;
	float tax = 0.01 * netTotal, grandTotal = round(netTotal + tax);
	printf("-----------------------------------------------\n");
	printf("Sub Total\t\t\t\t%.2f",total);
	printf("\nDiscount @10%s\t\t\t\t%.2f", "%", discount);
	printf("\n\t\t\t\t\t-------");
	printf("\nNet Total\t\t\t\t%.2f", netTotal);
	printf("\nTax @1%s\t\t\t\t\t%.2f", "%", tax);
	printf("\n-----------------------------------------------");
	printf("\nGrand Total\t\t\t\t%.2f", grandTotal);
	printf("\n-----------------------------------------------\n");
}

void addInvoice() {
	system("cls");
	struct orders ord;
	int num;
	float total;
	char saveBill;
	FILE *fp;

	printf("Enter Customer's Name:\t");
	fgets(ord.customer, 50, stdin);
	ord.customer[strlen(ord.customer) - 1] = 0; // Remove the \n from the fgets
	strcpy(ord.date, __DATE__); // Copy one string from one variable to another variable

	printf("Enter Number Of Items:\t");
	scanf("%d", &num);
	ord.numOfItems = num;

	for (int i = 0; i < num; i++) {
		fgetc(stdin);
		printf("\n\n");
		printf("Please enter the item %d:\t", i+1);
		fgets(ord.itm[i].item, 20, stdin);
		ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;

		printf("Please enter the quantity:\t");
		scanf("%d", &ord.itm[i].qty);

		printf("Please enter the unit price:\t");
		scanf("%f", &ord.itm[i].price);

		total += ord.itm[i].qty * ord.itm[i].price;
	}

	generateBillHeader(ord.customer, ord.date);
	for (int i = 0; i < ord.numOfItems; i++) {
		generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
	}
	generateBillFooter(total);

	printf("\nDo you want to save the invoice? [y/n]:\t");
	scanf("%s", &saveBill);

	if (saveBill == 'y' || saveBill == 'Y') {
		fp = fopen("Invoices.dat", "w");
		fwrite(&ord, sizeof(struct orders), 1, fp);

		if (fwrite != 0) {
			printf("\nInvoice Successfully Saved");
		} else {
			printf("\nError Saving Invoice");
		}
		fclose(fp);
	}
}

void appendInvoice() {
	system("cls");
	struct orders ord;
	int num;
	float total;
	char saveBill;
	FILE *fp;

	printf("Enter Customer's Name:\t");
	fgets(ord.customer, 50, stdin);
	ord.customer[strlen(ord.customer) - 1] = 0; // Remove the \n from the fgets
	strcpy(ord.date, __DATE__); // Copy one string from one variable to another variable

	printf("Enter Number Of Items:\t");
	scanf("%d", &num);
	ord.numOfItems = num;

	for (int i = 0; i < num; i++) {
		fgetc(stdin);
		printf("\n\n");
		printf("Please enter the item %d:\t", i+1);
		fgets(ord.itm[i].item, 20, stdin);
		ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;

		printf("Please enter the quantity:\t");
		scanf("%d", &ord.itm[i].qty);

		printf("Please enter the unit price:\t");
		scanf("%f", &ord.itm[i].price);

		total += ord.itm[i].qty * ord.itm[i].price;
	}

	generateBillHeader(ord.customer, ord.date);
	for (int i = 0; i < ord.numOfItems; i++) {
		generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
	}
	generateBillFooter(total);

	printf("\nDo you want to save the invoice? [y/n]:\t");
	scanf("%s", &saveBill);

	if (saveBill == 'y' || saveBill == 'Y') {
		fp = fopen("Invoices.dat", "a");
		fwrite(&ord, sizeof(struct orders), 1, fp);

		if (fwrite != 0) {
			printf("\nInvoice Successfully Saved");
		} else {
			printf("\nError Saving Invoice");
		}
		fclose(fp);
	}
}

void displayInvoices() {
	system("cls");
	struct orders orders;
	FILE *fp;

	fp = fopen("Invoices.dat", "r");
	printf("\n   ***** Previous Invoices *****\n");

	while(fread(&orders, sizeof(struct orders), 1, fp) > 0) {
		float ttl = 0;
		generateBillHeader(orders.customer, orders.date);
		for (int i = 0; i < orders.numOfItems; i++) {
			generateBillBody(orders.itm[i].item, orders.itm[i].qty, orders.itm[i].price);
			ttl += orders.itm[i].qty * orders.itm[i].price;
		}
		generateBillFooter(ttl);
	}
	fclose(fp);
}

void searchInvoice() {
	struct orders order;
	FILE *fp;
	char cName[50];
	int invoiceFound = 0;

	printf("\nEnter Customer's Name:\t");
	//fgetc(stdin);
	fgets(cName, 50, stdin);
	cName[strlen(cName)-1] = 0;

	system("cls");

	fp = fopen("Invoices.dat", "r");
	printf("\t***** Invoice of %s *****", cName);

	while(fread(&order, sizeof(struct orders), 1, fp)) {
		float ttl = 0;

		if (!strcmp(order.customer, cName)) {
			generateBillHeader(order.customer, order.date);
			for (int i = 0; i < order.numOfItems; i++) {
				generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
				ttl += order.itm[i].qty * order.itm[i].price;
			}
			generateBillFooter(ttl);
			invoiceFound = 1;
		}
	}

	if (!invoiceFound) {
		printf("\nInvoice for customer %s doesn't exist", cName);
	}
	fclose(fp);
}

int main () {
	system("color 0b");
	int opt;
	char contFlag = 'y';

	//Print dashboard
	while(contFlag == 'y') {
		system("cls");

		printf("\t============ CAFE HOUSE ============");
		printf("\n\nSelect your preferred operation");

		printf("\n\n1 - Generate Invoice");
		printf("\n2 - Show All Invoices");
		printf("\n3 - Search Invoice");
		printf("\n0 - Exit");

		printf("\n\nYour Choice:\t");
		scanf("%d", &opt);
		fgetc(stdin); // Remove the \n from the scanf - same as getchar()

		switch (opt) {
			case 1:
				FILE *fp;
				struct orders orders;
				fp = fopen("Invoices.dat", "r");

				if (fread(&orders, sizeof(struct orders), 1, fp) > 0) {
					appendInvoice();
				} else {
					addInvoice();
				}
				fclose(fp);
			break;

			case 2:
				displayInvoices();
			break;

			case 3:
				searchInvoice();
			break;

			case 0:
				printf("\n\t\t Exiting...\n");
				printf("\t\t Bye bye :)\n\n");
				exit(0);
			break;

			default:
				printf("\nSorry, invalid option");
			break;
		}
		printf("\nDo you want to perform another operation? [y/n]:\t");
		scanf("%s", &contFlag);
	}
	printf("\n\t\t Exiting...\n");
	printf("\t\t Bye bye :)\n\n");
	return 0;
}
