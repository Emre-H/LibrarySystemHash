#include "stdafx.h"
#include "Book.h"

Book::Book()
{
}

Book::~Book()
{
}

std::string Book::getRecordFormatString()
{
	std::string str = "";
	std::string tempName = name;
	std::string tempAuthor = author;
	std::string tempPrice = price;
	str = str + isbn;
	str = str + '\0';
	while (tempName.length() < 99) {
		tempName = tempName + '\0';
	}
	str = str + tempName;
	str = str + '\0';
	while (tempAuthor.length() < 99) {
		tempAuthor = tempAuthor + '\0';
	}
	str = str + tempAuthor;
	str = str + '\0';
	while (tempPrice.length() < 49) {
		tempPrice = tempPrice + '\0';
	}
	str = str + tempPrice;
	str = str + '\0';
	return (str);
}
