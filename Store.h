#pragma once
#include<iostream>
#include "Publisher.h"
#include "StoreBook.h"
using namespace std;

class Store
{
private:
	Publisher** publishers;
	int numberOfPublishers;
	int publishersLength;

public:
	Store()
	{
		publishersLength = 1;
		publishers = new Publisher*[publishersLength];
		numberOfPublishers = 0;
	}

	Store(int n)
	{
		publishersLength = n;
		numberOfPublishers = 0;
		publishers = new Publisher*[publishersLength];
	}

	~Store()
	{
		delete[] publishers;
	}

	void printOptions()
	{
		cout << "-----------------------------------------" << endl;
		cout << "[1]: Print available publishers and books" << endl;
		cout << "[2]: Create Publisher" << endl;
		cout << "[3]: Create Book" << endl;
		cout << "[4]: Order books and calculate price" << endl;
		cout << "[5]: Save store data in file" << endl;
		cout << "[6]: Load store data from file" << endl;
		cout << "[e]: Exit" << endl;
		cout << "-----------------------------------------" << endl << endl;
		string option;
		getline(cin, option);
		if (option == "e" || option == "E")
		{
			exit(0);
		}
		if (option == "1")
		{
			printAll();
		}
		else if (option == "2")
		{
			createPubisher();
		}
		else if (option == "3")
		{
			createBook();
		}
		else if (option == "4")
		{
			orderBooks();
		}
		else if(option == "5")
		{
			writeInFile();
		}
		else if (option == "6")
		{
			loadFromFile();
		}

		cout << endl;
	}

private:
	void printAvailablePublishers()
	{
		if (numberOfPublishers == 0)
		{
			cout << "No available publishers." << endl;
			return;
		}

		cout << "Avaiable publishers:" << endl;
		for (int i = 0; i < numberOfPublishers; i++)
		{
			cout << "[" << i << "]: " << "Publisher name: " << publishers[i]->getName() << endl;
		}
	}

	void printAll()
	{
		if (numberOfPublishers == 0)
		{
			cout << "No available data." << endl;
			return;
		}

		for (int i = 0; i < numberOfPublishers; i++)
		{
			cout << *publishers[i] << endl;
		}
	}

	void createPubisher()
	{
		Publisher* p = Publisher::InputPublisher();
		if (numberOfPublishers == publishersLength)
		{
			publishersLength *= 2;
			Publisher** tmp = new Publisher*[publishersLength];
			for (int i = 0; i < numberOfPublishers; i++)
			{
				tmp[i] = publishers[i];
			}
			tmp[numberOfPublishers++] = p;
			delete[] publishers;
			publishers = tmp;
		}
		else
		{
			publishers[numberOfPublishers++] = p;
		}
	}

	void createBook()
	{
		if (numberOfPublishers == 0)
		{
			cout << "Create a publisher first." << endl;
			return;
		}
		StoreBook* b = StoreBook::InputStoreBook();
		bool inputValid = false;
		int publisherIndex;
		do
		{
			cout << "Assign publisher to the book by inserting the number of the publisher (example 1):" << endl;
			printAvailablePublishers();
			string tmp;
			getline(cin, tmp);
			publisherIndex = stoi(tmp);
			if (publisherIndex >= 0 && publisherIndex < numberOfPublishers)
			{
				inputValid = true;
			}
			else
			{
				cout << "Invalid publisher number, Try again:" << endl;
			}
		} while (!inputValid);
		
		publishers[publisherIndex]->addBook(b);
	}

	void orderBooks()
	{
		string input;
		int price = 0;
		int numberOfOrderedBooks = 0;
		bool finished = false;
		do
		{
			cout << "Enter books ISBN to add to cart or 'f' to finish the order:" << endl;
			getline(cin, input);
			if (input == "f" || input == "F")
			{
				finished = true;
			}
			if (!finished)
			{
				StoreBook* b = findBookByIsbn(input);
				if (b != nullptr)
				{
					numberOfOrderedBooks++;
					price += b->getPrice();
				}
			}
		} while (!finished);

		if (numberOfOrderedBooks != 0)
		{
			cout << "Number of books ordered: " << numberOfOrderedBooks << ", Price: " << price << endl;
		}
		else
		{
			cout << "No books ordered." << endl;
		}
	}

	void writeInFile()
	{
		if (numberOfPublishers == 0)
		{
			throw "No data to write in file.";
		}

		ofstream out("store.txt");
		if (!out.good())
		{
			throw "Error while opening the file";
		}
		out << numberOfPublishers << endl;
		for (int i = 0; i < numberOfPublishers; i++)
		{
			publishers[i]->WriteInFile(out);
		}
	}

	void loadFromFile()
	{
		ifstream in("store.txt");
		if (!in.good())
		{
			throw "Error while opening the file";
		}
		string tmp;
		getline(in, tmp);
		numberOfPublishers = stoi(tmp);
		publishersLength = numberOfPublishers;
		if (numberOfPublishers > 0)
		{
			delete[] publishers;
			publishers = new Publisher* [numberOfPublishers];
			for (int i = 0; i < numberOfPublishers; i++)
			{
				publishers[i] = Publisher::ReadFromFile(in);
			}
		}
	}

	StoreBook* findBookByIsbn(string isbn)
	{
		for (int i = 0; i < numberOfPublishers; i++)
		{
			StoreBook* b = (StoreBook*)publishers[i]->getBookByIsbn(isbn);
			if (b != nullptr)
			{
				return b;
			}
		}

		return nullptr;
	}
};
