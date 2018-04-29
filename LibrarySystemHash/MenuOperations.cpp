#include "stdafx.h"
#include "MenuOperations.h"

MenuOperations::MenuOperations()
{
}

MenuOperations::~MenuOperations()
{
}

void MenuOperations::setFileOperations(FileOperations fo) {
	this->fo = fo;
}

void MenuOperations::showMainMenu()
{
	char choice;
	while (true) {
		addNewLinesToConsole();
		std::cout << "Choose one of the modes below:" << std::endl << std::endl;
		std::cout << "1) User Mode" << std::endl;
		std::cout << "2) Admin Mode" << std::endl << std::endl;
		std::cout << "3) Exit" << std::endl << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case '1':
			showUserModeMenu();
			break;
		case '2':
			showAdminModeMenu();
			break;
		case '3':
			return;
		default:
			break;
		}
	}
}

void MenuOperations::showUserModeMenu()
{
	char choice;
	while (true) {
		addNewLinesToConsole();
		std::cout << "Choose one of the options below:" << std::endl << std::endl;
		std::cout << "1) Search by ISBN" << std::endl;
		std::cout << "2) Main Menu" << std::endl << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case '1':
			searchByISBN();
			return;
		case '2':
			return;
		default:
			break;
		}
	}
}

void MenuOperations::showAdminModeMenu()
{
	char choice;
	while (true) {
		addNewLinesToConsole();
		std::cout << "Choose one of the options below:" << std::endl << std::endl;
		std::cout << "1) Search by ISBN" << std::endl;
		std::cout << "2) Add Book" << std::endl;
		std::cout << "3) Delete Book" << std::endl;
		std::cout << "4) Main Menu" << std::endl << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case '1':
			searchByISBN();
			return;
		case '2':
			addRecord();
			return;
		case '3':
			deleteRecord();
			return;
		case '4':
			return;
		default:
			break;
		}
	}
}

void MenuOperations::searchByISBN()
{
	addNewLinesToConsole();
	Book book;
	std::string input;
	std::cout << "ISBN:" << std::endl << std::endl;
	std::cin.ignore();
	std::getline(std::cin, input);
	try
	{
		book = fo.searchByISBN(input);
		std::cout << "ISBN: " << book.isbn << std::endl;
		std::cout << "Name: " << book.name << std::endl;
		std::cout << "Author: " << book.author << std::endl;
		std::cout << "Price: " << book.price << std::endl;
		std::cout << "Index: " << book.index << std::endl;
		std::cout << "In Bucket Index: " << book.inBucketIndex << std::endl;
		std::cout << "Number Of Probes: " << book.numberOfProbes << std::endl;
	}
	catch (const std::exception&)
	{
		std::cout << std::endl << "Couldn't Find the Book." << std::endl;
	}
	std::cout << std::endl << "Average Number Of Probes: " << fo.getAverageNumberOfProbes() << std::endl;
	waitMenu();
	return;
}

void MenuOperations::addRecord()
{
	addNewLinesToConsole();
	Book book = Book();
	std::string input;
	std::cin.ignore();
	do {
		std::cout << "ISBN:" << std::endl << std::endl;
		std::getline(std::cin, input);
	} while (input.size() != 10);
	book.isbn = input;

	do {
		std::cout << std::endl << "Name:" << std::endl << std::endl;
		std::getline(std::cin, input);
	} while (input.size() > 99);
	book.name = input;

	do {
		std::cout << std::endl << "Author:" << std::endl << std::endl;
		std::getline(std::cin, input);
	} while (input.size() > 99);
	book.author = input;

	do {
		std::cout << std::endl << "Price:" << std::endl << std::endl;
		std::getline(std::cin, input);
	} while (input.size() > 49);
	book.price = input;

	try {
		fo.writeRecord(book);
		std::cout << std::endl << std::endl << "Added." << std::endl;
	}
	catch (const std::exception&) {
		std::cout << std::endl << std::endl << "File is full!" << std::endl;
	}
	std::cout << std::endl << "Packing Factor: " << fo.getPackingFactor() << std::endl;
	waitMenu();
	return;
}

void MenuOperations::deleteRecord()
{
	addNewLinesToConsole();
	std::string input;
	std::cout << "ISBN of the Book You Want to Delete:" << std::endl << std::endl;
	std::cin.ignore();
	std::getline(std::cin, input);
	if (fo.deleteRecord(input)) {
		std::cout << std::endl << "Deleted." << std::endl;
	}
	else {
		std::cout << std::endl << "Couldn't Find the Book." << std::endl;
	}
	waitMenu();
	return;
}

void MenuOperations::addNewLinesToConsole()
{
	for (int i = 0; i < 60; i++)
	{
		std::cout << std::endl;
	}
}

void MenuOperations::waitMenu()
{
	int choice;
	std::cout << std::endl << "1) Main Menu" << std::endl << std::endl;
	while (true) {
		std::cin >> choice;
		if (choice == 1) {
			return;
		}
	}
}