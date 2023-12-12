#pragma once
#include<iostream>
#include "Book.h"
#include "StoreBook.h"
using namespace std;

class Publisher
{
private:
	string name;
	string address;
	string phoneNumber;
	Book** books;
	int numberOfBooks;
	int booksLength;

public:
	Publisher()
	{
		books = nullptr;
		numberOfBooks = 0;
		booksLength = 0;
	}

	Publisher(const Publisher& p)
	{
		name = p.name;
		address = p.address;
		phoneNumber = p.phoneNumber;
		books = nullptr;
		numberOfBooks = p.numberOfBooks;
		booksLength = p.booksLength;
		if (p.books != nullptr)
		{
			books = new Book*[booksLength];
			for (int i = 0; i < numberOfBooks; i++)
			{
				books[i] = p.books[i]->clone();
			}
		}
	}

	~Publisher()
	{
		clean();
	}

	Publisher& operator=(Publisher& p)
	{
		name = p.name;
		address = p.address;
		phoneNumber = p.phoneNumber;
		books = nullptr;
		numberOfBooks = p.numberOfBooks;
		booksLength = p.booksLength;
		if (p.books != nullptr)
		{
			books = new Book*[booksLength];
			for (int i = 0; i < numberOfBooks; i++)
			{
				books[i] = p.books[i]->clone();
			}
		}

		return *this;
	}

	void WriteInFile(ofstream& file)
	{
		file << name << endl << address << endl << phoneNumber << endl << numberOfBooks << endl;
		for (int i = 0; i < numberOfBooks; i++)
		{
			books[i]->WriteInFile(file);
		}
	}

	static Publisher* ReadFromFile(ifstream& file)
	{
		Publisher* p = new Publisher();

		getline(file, p->name);
		getline(file, p->address);
		getline(file, p->phoneNumber);
		string tmp;
		getline(file, tmp);
		p->numberOfBooks = stoi(tmp);
		if (p->numberOfBooks > 0)
		{
			p->booksLength = p->numberOfBooks;
			p->books = new Book*[p->numberOfBooks];
			for (int i = 0; i < p->numberOfBooks; i++)
			{
				p->books[i] = StoreBook::ReadFromFile(file);
			}
		}

		return p;
	}

	friend ostream& operator<<(ostream& out, Publisher& p)
	{
		string bo = ", No books.";
		if (p.books != nullptr)
		{
			bo = ", Available books:";
		}
		out << "Publisher name: " << p.name << ", Address: " << p.address << ", Phone number: " << p.phoneNumber << bo << endl;

		if (p.books != nullptr)
		{
			for (int i = 0; i < p.numberOfBooks; i++)
			{
				out << "[" << i << "]: " << *p.books[i];
			}
		}

		out << endl;

		return out;
	}

	string getName()
	{
		return name;
	}

	void setName(string name)
	{
		if (!validateName(name))
		{
			throw "Invlid name";
		}

		this->name = name;
	}

	string getAddress()
	{
		return address;
	}

	void setAddress(string address)
	{
		if (!validateAddress(address))
		{
			throw "Invlid address";
		}

		this->address = address;
	}

	string getPhoneNumber()
	{
		return phoneNumber;
	}

	void setPhoneNumber(string phoneNumber)
	{
		if (!validatePhoneNumber(phoneNumber))
		{
			throw "Invlid phone number";
		}

		this->phoneNumber = phoneNumber;
	}

	Book* getBookByIsbn(string isbn)
	{
		for (int i = 0; i < numberOfBooks; i++)
		{
			if (books[i]->getIsbn() == isbn)
			{
				return books[i];
			}
		}

		return nullptr;
	}

	void addBook(Book* b)
	{
		if (numberOfBooks == booksLength)
		{
			booksLength *= 2;
			if (booksLength == 0)
			{
				booksLength = 10;
			}
			Book** tmp = new Book*[booksLength];
			for (int i = 0; i < numberOfBooks; i++)
			{
				tmp[i] = books[i];
			}
			tmp[numberOfBooks++] = b;
			delete[] books;
			books = tmp;
		}
		else
		{
			books[numberOfBooks++] = b;
		}
	}

	static Publisher* InputPublisher()
	{
		Publisher* p = new Publisher();
		bool inputValid = false;

		do
		{
			cout << "Enter publisher name:" << endl;
			getline(cin, p->name);
			inputValid = validateName(p->name);
			if (!inputValid)
			{
				cout << "Invalid name. Must have at least 2 characters." << endl;
			}
		} while (!inputValid);

		inputValid = false;
		do
		{
			cout << "Enter publisher address:" << endl;
			getline(cin, p->address);
			inputValid = validateAddress(p->address);
			if (!inputValid)
			{
				cout << "Invalid address. Must have at least 2 characters." << endl;
			}
		} while (!inputValid);

		inputValid = false;
		do
		{
			cout << "Enter publisher phone number (format: +XXXXXXXXX):" << endl;
			getline(cin, p->phoneNumber);
			inputValid = validatePhoneNumber(p->phoneNumber);
			if (!inputValid)
			{
				cout << "Invalid phone number. Must have at least 10 chars." << endl;
			}
		} while (!inputValid);

		return p;
	}

private:
	void clean()
	{
		delete[] books;
	}

	static bool validateName(string name)
	{
		return name != "" && name != " " && name.length() >= 2;
	}

	static bool validateAddress(string address)
	{
		return address != "" && address != " " && address.length() >= 2;
	}

	static bool validatePhoneNumber(string phoneNumber)
	{
		return phoneNumber != "" && phoneNumber != " " && phoneNumber.length() >= 10 && phoneNumber.rfind("+", 0) == 0;
	}
};
