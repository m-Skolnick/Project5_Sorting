//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Project5.cpp          ASSIGNMENT #:  5            Grade: _________          *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Micaiah Skolnick                                              *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                            DUE DATE:  March 24, 2017                    *
//*                                                                                                   *
//*****************************************************************************************************
//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS:  Each of the inventory records are read into an array of records. The records are then *
//*             sorted using various methods. In between each sort, the list of records is printed.   *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     : Footer - Prints a footer to signify end of program output                        *
//*                  Header - Prints a header to signify start of program output                      *
//*                  newPage - Inserts blank lines until the start of a new page                      *
//*                  getData - Gets all of the records from the data file                             *
//*                  printDataLabels - Prints labels for each of the columns of the data              *
//*                  printHeaders - Prints a header for each sort type                                *
//*                  printList - Prints the entire array of elements with correct spacing             *
//*                  bubbleSort - Sorts the array of records using the bubble sort method             *
//*                  quickSort - Sorts the array of records using the quick sort method               *
//*                  shellSort - Sorts the array of records using the shell sort method               *
//*                  main - Calls each function in order in order to accomplish the desired task      *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <locale>
#include <string>
#include <sstream>
using namespace std;
int lineCount = 0; // Declare and initialize a line counter
//*************************************  FUNCTION HEADER  *********************************************
void Header(ofstream &Outfile)
{       // Receives – the output file
		// Task - Prints the output preamble
		// Returns - Nothing
	Outfile << setw(30) << "Micaiah Skolnick ";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(27) << "Spring 2017";
	Outfile << setw(30) << "Assignment #5" << endl;
	Outfile << setw(35) << "---------------------------------- - ";
	Outfile << setw(35) << "---------------------------------- - " << endl << endl;
	lineCount += 4; // Increment the line count
	return;
}
//************************************* END OF FUNCTION HEADER  ***************************************
//*************************************  FUNCTION FOOTER  *********************************************
void Footer(ofstream &Outfile)
{
	// Receives – the output file
	// Task - Prints the output salutation
	// Returns - Nothing
	Outfile << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	Outfile << setw(35) << " | END OF PROGRAM OUTPUT | " << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	lineCount += 4; // Increment the line counter
	return;
}
//************************************* END OF FUNCTION FOOTER  ***************************************
void newPage(ofstream&dataOUT) {
		// Receives – the output file
		// Task - Skip to the top of the next page
		// Returns - Nothing
		// Insert lines until the end of the page is reached
	int MAXPAGELINES = 50;
	while (lineCount < MAXPAGELINES) {
		dataOUT << endl;
		lineCount++;
	}		
	lineCount = 0; // Reset line counter to 0
}
//*****************************************************************************************************
struct recordType {
		// The structure "recordType" holds each record of the record list
	int iNum, quantity, reoNum;
	string iDes;
	float cost, price;
};
//*****************************************************************************************************
int getData(ifstream&dataIN, recordType recordList[]) {
		// Receives – The input file and the list of records
		// Task - Read in all data from input file
		// Returns - An integer signifying the number of records
		// Declare local variables
	int iNum = 0, quantity = 0, reoNum = 0, i = 0;
	char description[26];
	float cost = 0, price = 0;
	dataIN >> ws >> iNum; //Read in first inventory number
	while (iNum > 0){ //Keep reading in items until a negative value is reached
		dataIN.get(description, 20); //Read in 20 characters for description
			//Read in the quantity, re-order number, cost and price
		dataIN >> ws >> quantity >> reoNum >> cost >> price;
			//Set each of the values just read to the current array record.
		recordList[i].iNum = iNum;
		recordList[i].iDes = string(description);
		recordList[i].quantity = quantity;
		recordList[i].reoNum = reoNum;
		recordList[i].cost = cost;
		recordList[i].price = price;
		i++; // Increment the inventory count
		dataIN >> ws >> iNum; //Get the next inventory number
	}
	return i; //return the number of records read
}
//*****************************************************************************************************
void printList(ofstream&dataOUT, recordType recordList[], int recordCount) {
			// Receives – The output file, the record list and the record count
			// Task - Print each record in the list
			// Returns - Nothing
		//Keep printing until the end of the list is reached
	for (int i = 0; i < recordCount; i++) {
		dataOUT << setw(6) << recordList[i].iNum << "    "; //Print the inventory number
			//Print the description and quantity
		dataOUT << recordList[i].iDes << setw(9) << recordList[i].quantity; 
			//Print re-order number and cost
		dataOUT << setw(9) << recordList[i].reoNum << setw(9) << recordList[i].cost
			<< setw(9) << recordList[i].price; //Print the selling price
		dataOUT << endl;
		lineCount++; //Increment the line counter
	}
}
//*****************************************************************************************************
void printDataLabels(ofstream&dataOUT) {
		// Receives – The output file
		// Task - Print data titles for array elements
		// Returns - Nothing	
		//Print data labels
	dataOUT << "Inventory  Item                 Quantity  Reorder  Cost of  Selling" << endl;
	dataOUT << " Number    Description          on hand   Number   Item     Price" << endl;
	dataOUT << "--------   -----------------    --------  -------  -------  -------" << endl;
	lineCount += 3; // increment the line counter
}
//*****************************************************************************************************
void printHeaders(ofstream&dataOUT, string sortType) {
		// Receives – The output file, and the type of sort for which a label is needed
		// Task - prints a header for the specific type of sort
		// Returns - Nothing
		//If array not sorted yet, print header for original sort
	if (sortType == "original") {
		dataOUT << "The Original Inventory Array:" << endl;
		lineCount++;
	}	//If sorted by bubble sort, print bubble sort header
	if (sortType == "bubble") {
		dataOUT << "The Inventory Array sorted in descending order according to the Quantity on Hand" << endl;
		dataOUT << "using the Bubble Sort:" << endl;
		lineCount += 2;
	}	//If sorted by shell sort, print shell sort header
	if (sortType == "shell") {
		dataOUT << "The Inventory Array sorted in descending order according to the Selling Price" << endl;
		dataOUT << "using the Shell Sort:" << endl;
		lineCount += 2;
	}	//If sorted by quick sort, print quick sort header
	if (sortType == "quick") {
		dataOUT << "The Inventory Array sorted in ascending order according to the Inventory Number" << endl;
		dataOUT << "using the Quick Sort:" << endl;
		lineCount += 2;
	}
	printDataLabels(dataOUT); // Print data labels beneath the sort type header
}
//*****************************************************************************************************
void bubbleSort(recordType recordList[], int recordCount) {
		// Receives – The list of records and the record count
		// Task - Sort list in descending order by quantity using bubble sort
		// Returns - The sorted list
	bool sorted = false; //Initialize bool to track whether list is sorted
	while (!sorted) { //Keep sorting until the whole list is sorted
		sorted = true; //Set bool to indicate list is sorted
		for (int i = 0; i < recordCount-1; i++) { //Go throgh each of the records
				//If any are found out of place, switch them and indicate list is not sorted
			if (recordList[i].quantity < recordList[i + 1].quantity) {
					//Switch records
				recordType temp = recordList[i];
				recordList[i] = recordList[i + 1];
				recordList[i + 1] = temp;
				sorted = false; //Set sorted bool to false
			}
		}
	}
}
//*****************************************************************************************************
void shellSort(recordType recordList[], int recordCount) {
		// Receives – The list of records, and the record count
		// Task - Sort the list based on price using the shell sort method
		// Returns - The sorted list
	int NumOfStages = 3; // Initialize the number of stages
	int KValue[] = { 7, 3, 1 }; // Initialize the k-value for each stage
	int index = 0, j = 0, kVal = 0, Stage=0; // Initialize the various counters
	recordType Temp; //Create a variable to store a temporary record
	bool  Found;
		//Sort the list one time for each of the stages
	for (Stage = 1; Stage <= NumOfStages; Stage++)
	{		//Sort based on the k-value of the corresponding stage
		kVal = KValue[Stage-1];
			//Search through each of the records
		for (index = kVal; index < recordCount; index++)
		{		//Temporarily store the first record in this sub array
			Temp = recordList[index];
			j = index - kVal;
			Found = false;
				//Apply bubble sort to the sub array
			while ((j >= 0) && (!Found))
			{ //Switch positions of the records if a lower price is found earlier in array
				if (Temp.price > recordList[j].price) {
					recordList[j + kVal] = recordList[j];
					j -= kVal;
				}
				else{
					Found = true;
				}
			}   // End of while loop
			recordList[j + kVal] = Temp;
		}  // End of for loop 
	}
}
//*****************************************************************************************************
void quickSort(recordType recordList[], int first, int last) {
		// Receives – The list of records, and the index of the first and last record
		// Task - Sort the list based on inventory number using the quicksort method
		// Returns - The sorted list
	int f, l, mid, midVal; 
		//Initialize local variables
	f = first;
	l = last;
	mid = (f+l) / 2; 
	midVal = recordList[mid].iNum;
		//Keep looping until f reaches l
	while (f <= l) {
			//Increment f until the value of the inventory number of that record is no longer less
			// than the pivot value
		while (recordList[f].iNum < midVal) {
			f++;
		}
			//Decrement l until the value of the inventory number of that record is not higher than
			// the pivot value
		while (recordList[l].iNum > midVal) {
			l--;
		}
			//If f is still less than or equal to l, swap the records, increment f and decrement l
		if (f <= l) {
			recordType temp;
			temp = recordList[f];
			recordList[f] = recordList[l];
			recordList[l] = temp;
			f++;
			l--;
		}
	}
		//If l is greater than the first value, recursively sort using the current positions
	if (l > first) {
		quickSort(recordList, first, l);
	}
		//If f is less than the last value, recursively sort using the current positions
	if (f < last) {
		quickSort(recordList, f, last);
	}
}
//*****************************************************************************************************
int main() {
		// Receives – Nothing
		// Task - Call each necessary function of the program in order
		// Returns - Nothing
	ifstream dataIN("data_in.txt");  // Open the file containing data.
	ofstream dataOUT("dataOUT.docx");  // Create and open the file to write data to.	
	Header(dataOUT); // Print data header.
	recordType recordList[50]; //Initialize array to hold records
	int recordCount = 0;
	recordCount = getData(dataIN, recordList); //Read in all of the data from the input file
	printHeaders(dataOUT, "original"); //Print header for the original data
	printList(dataOUT, recordList, recordCount); //Print the list of data	
	newPage(dataOUT); // Start a new page for the new data
	printHeaders(dataOUT, "bubble"); //Print a header for the bubble sort
	bubbleSort(recordList, recordCount); //Sort the list by quantity using bubble sort
	printList(dataOUT, recordList, recordCount); //Print the list after sorting
	newPage(dataOUT); // Start a new page for the new data
	printHeaders(dataOUT,"shell"); //Print a header for the shell sort
	shellSort(recordList, recordCount); //Sort the list by price using shell sort
	printList(dataOUT, recordList, recordCount); //Print the list after sorting
	newPage(dataOUT); // Start a new page for the new data
	printHeaders(dataOUT, "quick"); //Print a header for the quick sort
	quickSort(recordList, 0, recordCount -1); //Sort the list by inventory number using quick sort
	printList(dataOUT, recordList, recordCount); //Print the list after sorting
	Footer(dataOUT); // Print footer. 
	dataIN.close(); // Close input data file. 
	dataOUT.close(); // Close output data file.
	return 0;
}
//*****************************************************************************************************