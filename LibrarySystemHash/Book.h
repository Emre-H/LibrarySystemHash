#pragma once
#include "string"

class Book
{
public:
	Book();
	~Book();
	std::string isbn;
	std::string name;
	std::string author;
	std::string price;
	int index;
	int inBucketIndex;
	int numberOfProbes;
	/**
	 * @returns {std::string} Concatenates attributes together in a fixed record format. (261 bytes)
	 */
	std::string getRecordFormatString();
};