#pragma once
#include "iostream"
#include "string"
#include "Book.h"
#include "FileOperations.h"

class MenuOperations
{
public:
	MenuOperations();
	~MenuOperations();

	/**
	 * Sets this object's FileOperations to given object.
	 * @param fo - FileOperations to be set.
	 */
	void setFileOperations(FileOperations fo);

	/**
	 * Shows main menu options on console and gets a input from user for choice.
	 */
	void showMainMenu();
private:
	/**
	 * Shows user mode menu options on console and gets a input from user for choice.
	 * Calls appropriate function according to choice.
	 */
	void showUserModeMenu();

	/**
	 * Shows admin mode menu options on console and gets a input from user for choice.
	 * Calls appropriate function according to choice.
	 */
	void showAdminModeMenu();

	/**
	 * Gets a input from user and calls searchByISBN() function from FileOperations.
	 * Prints the returned object's attributes in a formatted way.
	 */
	void searchByISBN();

	/**
	 * Gets necessary inputs from user, checks their lengths, assigns them to a Book object's attributes.
	 * Calls writeRecord() function from FileOperations.
	 */
	void addRecord();

	/**
	 * Gets a input from user and calls deleteRecord() function from FileOperations.
	 */
	void deleteRecord();

	/**
	 * This is for using FileOperations' member functions in this class.
	 */
	FileOperations fo;

	/**
	 * Prints 50 endl to create clean console effect.
	 */
	void addNewLinesToConsole();

	/**
	 * Creates something like a waiting screen for letting user to read other functions prints on console.
	 * Gets a input from user if it is '1' goes to main menu.
	 */
	void waitMenu();
};

