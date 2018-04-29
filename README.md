# LibrarySystemHash
Simple library system console application.

This project was a assignment for my "Data Management and File Structures" lesson at university.

You can add or delete books from system and you can search a book by its ISBN.

Search example:

![Example Image1](https://image.ibb.co/d4mzYc/Search_Isbn_SS.png "Example Image1")

## Details

Books are stored in a binary file as fixed-length records. Each record is total 261 byte long:

 - ISBN = 10 byte + ‘/0’ = 11 byte
 - Name = 99 byte + ‘/0’ = 100 byte
 - Author = 99 byte + ‘/0’ = 100 byte
 - Price = 49 byte + ‘/0’ = 50 byte

If the value is shorter, remaining empty places filled with ‘/0’.

![Example Image2](https://image.ibb.co/m4iDtc/Binary_File_SS.png "Example Image2")

Hash function in the system is (ISBN % 41).
Records are placed at buckets according to their hash values.

Buckets can hold up to 5 records each.

This project uses linear probing as collision resolution method.
More info: http://www.cs.rmit.edu.au/online/blackboard/chapter/05/documents/contribute/chapter/05/linear-probing.html

When a book is deleted its first character of ISBN in file is replaced with ‘*’.

Average number of probes calculating by (TotalProbesForEveryRecord / NumberOfRecordsStored) after every search.

Packing factor calculating by (NumberOfRecordsStored / TotalNumberOfStorageLocations) after every book added.

Program first copies sample books from "books.txt" that teacher gave us.

Comments for codes are in ".h" files.

Written and compiled using Microsoft Visual Studio Community 2017.

Assignment document: (Turkish)
https://tr.scribd.com/document/377704191/assignment
## License
MIT © [Emre Horsanalı](mailto:emrehorsanali@outlook.com)
