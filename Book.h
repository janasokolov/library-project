#pragma once
#include<iostream>
#include <regex>
#include<fstream>
using namespace std;

class Book
{
protected:
	string title;
	string author;
	int edition;
	string isbn;
	string publishDate;
	string* certificationDate;

public:
	Book()
	{
		certificationDate = nullptr;
	}

	Book(const Book& b)
	{
		title = b.title;
		author = b.author;
		edition = b.edition;
		isbn = b.isbn;
		publishDate = b.publishDate;
		if (b.certificationDate != nullptr)
		{
			certificationDate = new string(*b.certificationDate);
		} else
		{
			certificationDate = nullptr;
		}
	}

	virtual Book* clone()
	{
		return new Book(*this);
	}

	~Book()
	{
		clean();
	}

	virtual Book& operator=(const Book& b)
	{
		title = b.title;
		author = b.author;
		edition = b.edition;
		isbn = b.isbn;
		publishDate = b.publishDate;
		if (b.certificationDate != nullptr)
		{
			certificationDate = new string(*b.certificationDate);
		}
		else
		{
			certificationDate = nullptr;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, Book& b)
	{
		string certificationDate = ", Not certified";
		if (b.certificationDate != nullptr)
		{
			certificationDate = ", Certification date: " + *b.certificationDate;
		}

		out << "Title: " << b.title << ", Author: " << b.author << ", Edition: " << b.edition << ", ISBN: " << b.isbn << ", Publish date: " << b.publishDate << certificationDate << endl;

		return out;
	}

	virtual void WriteInFile(ofstream& file)
	{
		string certDate = "NULL";
		if (certificationDate != nullptr)
		{
			certDate = *certificationDate;
		}

		file << title << endl << author << endl << edition << endl << isbn << endl << publishDate << endl << certDate << endl;
	}

	static Book* ReadFromFile(ifstream& file)
	{
		Book* b = new Book();
		getline(file, b->title);
		getline(file, b->author);
		string tmp;
		getline(file, tmp);
		b->edition = stoi(tmp);
		getline(file, b->isbn);
		getline(file, b->publishDate);

		string certificationDate;
		getline(file, certificationDate);
		if (certificationDate != "NULL")
		{
			b->certificationDate = new string;
			*b->certificationDate = certificationDate;
		}

		return b;
	}

	string getTitle()
	{
		return title;
	}

	void setTitle(string title)
	{
		if (!validateTitle(title))
		{
			throw "Invlid title";
		}

		this->title = title;
	}

	string getAuthor()
	{
		return author;
	}

	void setAuthor(string author)
	{
		if (!validateAuthor(author))
		{
			throw "Invalid author";
		}

		this->author = author;
	}

	int getEdition()
	{
		return edition;
	}

	void setEdition(int edition)
	{
		if (!validateEdition(edition))
		{
			throw "Invlid edition";
		}

		this->edition = edition;
	}

	string getIsbn()
	{
		return isbn;
	}

	void setIsbn(string isbn)
	{
		if (!validateIsbn(isbn))
		{
			throw "Invlid ISBN";
		}

		this->isbn = isbn;
	}

	string getPublishDate()
	{
		return publishDate;
	}

	void setPublishDate(string publishDate)
	{
		if (!validateDate(publishDate))
		{
			throw "Invlid publish date";
		}

		this->publishDate = publishDate;
	}

	string* getCertificationDate()
	{
		return certificationDate;
	}

	void setCertificationDate(string* certificationDate)
	{
		delete certificationDate;
		if (certificationDate != nullptr && !validateDate(*certificationDate))
		{
			throw "Invlid certification date";
		}

		this->certificationDate = certificationDate;
	}

	bool getIsCertified()
	{
		return certificationDate != nullptr;
	}

	static Book* InputBook()
	{
		Book* b = new Book();
		bool inputValid = false;

		do
		{
			cout << "Enter book title:" << endl;
			getline(cin, b->title);
			inputValid = validateTitle(b->title);
			if (!inputValid)
			{
				cout << "Invalid title. Must have at least 2 characters." << endl;
			}
		} while (!inputValid);

		inputValid = false;
		do
		{
			cout << "Enter book author:" << endl;
			getline(cin, b->author);
			inputValid = validateAuthor(b->author);
			if (!inputValid)
			{
				cout << "Invalid author. Must have at least 2 characters." << endl;
			}
		} while (!inputValid);

		inputValid = false;
		do
		{
			cout << "Enter book edition:" << endl;
			string tmp;
			getline(cin, tmp);
			b->edition = stoi(tmp);
			inputValid = validateEdition(b->edition);
			if (!inputValid)
			{
				cout << "Invalid edition. Must be a number greater then 0." << endl;
			}
		} while (!inputValid);

		inputValid = false;
		do
		{
			cout << "Enter book ISBN:" << endl;
			getline(cin, b->isbn);
			inputValid = validateIsbn(b->isbn);
			if (!inputValid)
			{
				cout << "Invalid ISBN. Must have 13 characters." << endl;
			}
		} while (!inputValid);

		inputValid = false;
		do
		{
			cout << "Enter book publish date:" << endl;
			getline(cin, b->publishDate);
			inputValid = validateDate(b->publishDate);
			if (!inputValid)
			{
				cout << "Invalid date. Must have the following format: 'yyyy-mm-dd'." << endl;
			}
		} while (!inputValid);

		inputValid = false;
		do
		{
			cout << "Is the book certified (y/n):" << endl;
			string certified;
			getline(cin, certified);
			if (certified == "y")
			{
				cout << "Enter book certification date:" << endl;
				b->certificationDate = new string;
				getline(cin, *b->certificationDate);
				inputValid = validateDate(*b->certificationDate);
			}
			else if (certified == "n")
			{
				inputValid = true;
			}
			if (!inputValid)
			{
				cout << "Invalid date. Must have the following format: 'yyyy-mm-dd'." << endl;
			}
		} while (!inputValid);

		return b;
	}

protected:
	void clean()
	{
		delete certificationDate;
	}

private:
	static bool validateTitle(string title)
	{
		return title != "" && title != " " && title.length() >= 2;
	}

	static bool validateAuthor(string author)
	{
		return author != "" && author != " " && author.length() >= 2;
	}

	static bool validateEdition(int edition)
	{
		return edition > 0;
	}

	static bool validateIsbn(string isbn)
	{
		return isbn != "" && isbn != " " && isbn.length() == 13;
	}

	static bool validateDate(string date)
	{
		if (date == "" || date == " " || date.length() != 10)
		{
			return false;
		}
		regex pattern("^\\d{4}-\\d{2}-\\d{2}$");
		if (regex_search(date, pattern))
		{
			return true;
		}

		return false;
	}
};
