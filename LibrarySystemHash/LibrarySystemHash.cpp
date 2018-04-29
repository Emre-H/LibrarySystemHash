// LibrarySystem.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "FileOperations.h"
#include "MenuOperations.h"

int main()
{
	FileOperations fo = FileOperations();
	MenuOperations mo = MenuOperations();
	if (fo.createFile()) {
		mo.setFileOperations(fo);
		mo.showMainMenu();
	}
	return 0;
}

