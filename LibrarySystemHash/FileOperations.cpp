#include "stdafx.h"
#include "FileOperations.h"

FileOperations::FileOperations()
{
}

FileOperations::~FileOperations()
{
}

std::vector< Book > FileOperations::getBucket(int index) {
	std::ifstream file;
	file.open("booksSequentialFile.bin", std::ios::in | std::ios::binary);
	file.seekg(index * 261 * 5);
	char bucket[1305];
	file.read((char *)& bucket, 1305 * sizeof(char));
	file.close();
	std::string bucketString = "";
	for (int i = 0; i < 1305; i++) {
		bucketString = bucketString + bucket[i];
	}
	Book book;
	std::vector< Book > books;
	for (int i = 0; i < 5; i++) {
		book = Book();
		
		book.isbn = std::string((bucketString.substr(261 * i + 0, 11)).c_str());

		book.name = std::string((bucketString.substr(261 * i + 11, 100)).c_str());

		book.author = std::string((bucketString.substr(261 * i + 111, 100)).c_str());

		book.price = std::string((bucketString.substr(261 * i + 211, 50)).c_str());

		book.index = index;

		books.push_back(book);
	}
	return books;
}

Book FileOperations::searchBookInBucket(std::string isbn, std::vector< Book > books) {
	for (int i = 0; i < books.size(); i++) {
		if (books[i].isbn == isbn) {
			books[i].inBucketIndex = i;
			return books[i];
		}
		if (books[i].isbn[0] == '\0') {
			throw std::exception("NULL FOUND.");
		}
	}
	throw std::exception("NOT FOUND.");
}

int FileOperations::searchEmptyPlaceInBucket(std::vector< Book > books) {
	for (int i = 0; i < books.size(); i++) {
		if (books[i].isbn[0] == '\0' || books[i].isbn[0] == '*') {
			return i;
		}
	}
	return -1;
}

void FileOperations::writeRecord(Book book) {
	book.index = atoll(book.isbn.c_str()) % 41;
	for (int i = 0; i < 41; i++) {
		book.inBucketIndex = searchEmptyPlaceInBucket(getBucket(book.index));
		if (book.inBucketIndex == -1) {
			book.index = book.index + 1;
			if (book.index == 41) {
				book.index = 0;
			}
		} else {
			std::fstream file;
			file.open("booksSequentialFile.bin", std::ios::in | std::ios::out | std::ios::binary);
			std::string str = book.getRecordFormatString();
			file.seekg(book.index * 261 * 5 + book.inBucketIndex * 261);
			file << str;
			file.close();
			return;
		}
	}
	throw std::exception("NO PLACE.");
}

bool FileOperations::createFile() {
	std::fstream file("booksSequentialFile.bin");
	if (!file.good()) {
		file.open("booksSequentialFile.bin", std::ios::binary | std::ios::out);
		for (int i = 0; i < 53505; i++) {
			file << '\0';
		}
		file.close();
		if (!copySampleData()) {
			return false;
		}
		return true;
	}
	file.close();
	return true;
}

bool FileOperations::copySampleData() {
	char wait;
	std::ifstream inputFile;
	inputFile.open("books.txt", std::ios::in);
	if (!inputFile.is_open()) {
		std::cout << "'books.txt' NOT FOUND." << std::endl;
		std::cin >> wait;
		return false;
	}
	std::string line;
	while (!inputFile.eof()) {
		Book book = Book();

		std::getline(inputFile, line);
		book.isbn = line;

		getline(inputFile, line);
		book.name = line;

		getline(inputFile, line);
		book.author = line;

		getline(inputFile, line);
		book.price = line;

		getline(inputFile, line);

		writeRecord(book);

		if (inputFile.fail()) {
			break;
		}
	}
	inputFile.close();
	return true;
}

bool FileOperations::deleteRecord(std::string isbn)
{
	Book book;
	try {
		book = searchByISBN(isbn);
	} catch (const std::exception&)
	{
		return false;
	}
	std::fstream file;
	file.open("booksSequentialFile.bin", std::ios::in | std::ios::out | std::ios::binary);
	file.seekg(book.index * 261 * 5 + book.inBucketIndex * 261);
	file.write("*", 1);
	file.close();
	return true;
}

Book FileOperations::searchByISBN(std::string searchISBN)
{
	int index = atoll(searchISBN.c_str()) % 41;
	Book book;
	int numberOfProbes = 0;
	for (int i = 0; i < 41; i++) {
		numberOfProbes = numberOfProbes + 1;
		try {
			book = searchBookInBucket(searchISBN, getBucket(index));
			book.numberOfProbes = numberOfProbes;
			return book;
		}
		catch (const std::exception& e) {
			if (std::string(e.what()) == "NULL FOUND.") {
				break;
			}
			index = index + 1;
			if (index == 41) {
				index = 0;
			}
		}
	}
	throw std::exception("NOT FOUND.");
}

int FileOperations::getNumberOfRecordsStored() {
	std::ifstream file;
	file.open("booksSequentialFile.bin", std::ios::in | std::ios::binary);
	char firstChar;
	int numberOfRecordsStored = 0;
	for (int i = 0; i < 205; i++) {
		firstChar = file.get();
		if (firstChar != '*' && firstChar != '\0') {
			numberOfRecordsStored = numberOfRecordsStored + 1;
		}
		file.seekg(260, std::ios_base::cur);
	}
	file.close();
	return numberOfRecordsStored;
}

double FileOperations::getPackingFactor() {
	return (double)getNumberOfRecordsStored() / (double)205;
}

double FileOperations::getAverageNumberOfProbes() {
	std::ifstream file;
	file.open("booksSequentialFile.bin", std::ios::in | std::ios::binary);
	int numberOfRecordsStored = 0;
	int totalProbes = 0;
	int index = -1;
	char isbnTemp[11];
	Book book;
	for (int i = 0; i < 205; i++) {
		if (i % 5 == 0) {
			index = index + 1;
		}
		file.read((char *)& isbnTemp, 11 * sizeof(char));
		if (isbnTemp[0] != '*' && isbnTemp[0] != '\0') {
			book = searchByISBN(isbnTemp);
			book.numberOfProbes = index - atoll(book.isbn.c_str()) % 41;
			if (book.numberOfProbes < 0) {
				book.numberOfProbes = 40 + book.numberOfProbes + 1;
			}
			book.numberOfProbes = book.numberOfProbes + 1;
			totalProbes = totalProbes + book.numberOfProbes;
			numberOfRecordsStored = numberOfRecordsStored + 1;
		}
		file.seekg(250, std::ios_base::cur);
	}
	file.close();
	return (double)totalProbes / (double)numberOfRecordsStored;
}