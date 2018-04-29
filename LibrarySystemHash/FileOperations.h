#pragma once
#include "vector"
#include "Book.h"
#include "fstream"
#include "string"
#include "iostream"

class FileOperations
{
public:
	FileOperations();
	~FileOperations();

	/**
	 * Returns 5 books in bucket at given index.
	 * @param index - Index of the bucket.
	 * @returns {std::vector< Book >} Found books.
	 */
	std::vector< Book > getBucket(int index);

	/**
	 * Searches the record with given ISBN in given bucket.
	 * @param isbn - ISBN of the book that is going to be searched.
	 * @param books - Bucket that the book is going to be searched in.
	 * @returns {Book} Found book after the search.
	 * @throws Will throw an error if the record is not found or null found.
	 */
	Book searchBookInBucket(std::string isbn, std::vector< Book > books);

	/**
	 * Searches deleted record or null record in given bucket.
	 * @param books - Bucket that is going to be searched in.
	 * @returns {int} Index of empty place in bucket. (-1 if not found.)
	 */
	int searchEmptyPlaceInBucket(std::vector<Book> books);

	/**
	 * Writes given book to the rigth place in file as fixed record format.
	 * @param book - The book going to be written to file.
	 * @throws Will throw an error if the file is full.
	 */
	void writeRecord(Book book);

	/**
	 * Creates the file if not exists,
	 * Fills it with null,
	 * Calls copySampleData() function below.
	 * @returns {bool} False if	"books.txt" file is not found.
	 */
	bool createFile();

	/**
	 * Gets sample data from "books.txt" and writes it to "booksSequentialFile.bin"
	 * @returns {bool} False if	"books.txt" file is not found.
	 */
	bool copySampleData();

	/**
	 * Deletes a record from the file by making its first character '*'.
	 * @param isbn - ISBN of the book that is going to be deleted.
	 * @returns {bool} False if the record is not in the file.
	 */
	bool deleteRecord(std::string isbn);

	/**
	 * Searches the record with given ISBN.
	 * @param isbn - ISBN of the book that is going to be searched.
	 * @returns {Book} Found book after the search.
	 * @throws Will throw an error if the record is not found.
	 */
	Book searchByISBN(std::string isbn);

	/**
	 * Counts the number of records stored in file at that time.
	 * @returns {int} Number of records stored.
	 */
	int getNumberOfRecordsStored();

	/**
	 * Calculates packing factor by (NumberOfRecordsStored / TotalNumberOfStorageLocations)
	 * @returns {double} Packing factor.
	 */
	double getPackingFactor();

	/**
	 * Calculates average number of probes by (TotalProbesForEveryRecord / NumberOfRecordsStored)
	 * @returns {double} Average number of probes.
	 */
	double getAverageNumberOfProbes();
};

