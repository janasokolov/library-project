#pragma once
#include<iostream>
#include<fstream>
#include "Book.h"
using namespace std;

class StoreBook : public Book
{
private:
	int price;

public:
	StoreBook()
		:Book()
	{
	}

	StoreBook(const Book& b)
		:Book(b)
	{
	}

	StoreBook(const StoreBook& b)
		:Book(b)
	{
		price = b.price;
	}

	virtual StoreBook* clone() override
	{
		return new StoreBook(*this);
	}

	virtual StoreBook& operator=(StoreBook& b)
	{
		Book::operator=(b);
		price = b.price;

		return *this;
	}

	friend ostream& operator<<(ostream& out, StoreBook& b)
	{
		out << "Book price: " << b.price << ", ";
		out << static_cast<Book&>(b);

		return out;
	}

	void setPrice(int price)
	{
		if (!validatePrice(price))
		{
			throw "Invlid price";
		}

		this->price = price;
	}

	int getPrice()
	{
		return price;
	}

	void WriteInFile(ofstream& file) override
	{
		file << price << endl;
		Book::WriteInFile(file);
	}

	static StoreBook* ReadFromFile(ifstream& file)
	{
		string price;
		getline(file, price);
		Book* tmp = Book::ReadFromFile(file);
		StoreBook* b = new StoreBook(*tmp);
		b->price = stoi(price);
		delete tmp;
		return b;
	}

	static StoreBook* InputStoreBook()
	{
		Book* tmp = InputBook();
		StoreBook* b = new StoreBook(*tmp);
		delete tmp;

		bool inputValid = false;
		do
		{
			cout << "Enter book price:" << endl;
			string price;
			getline(cin, price);
			b->price = stoi(price);
			inputValid = validatePrice(b->price);
			if (!inputValid)
			{
				cout << "Invalid price. Must be a number greater then 0." << endl;
			}
		} while (!inputValid);

		return b;
	}

private:
	static bool validatePrice(int price)
	{
		return price > 0;
	}
};
