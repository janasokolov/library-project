

## UML diagram



## Класове 

### **Book (book.h)**

Клас, съхраняващ информация за учебници.

#### **Променливи**

* `string title`: Заглавие на учебника.
* `string author`: Автор на учебника.
* `int edition`: Поредно издание на учебника.
* `string isbn`: ISBN на учебника.
* `string publishDate`: Дата на излизане на учебника от печат и тираж.
* `string* certificationDate`: Одобрение/Сертификат от Министерството на образованието

#### **Конструктори**

* `Book()`: Default конструктор.
* `Book(const Book& b)`: Copy конструктор, използва се за създаване на копие на съществуващ обект от клас Book.

#### **Функции**

* `virtual Book* clone()`: Виртуален метод за създаде на копие на текущия обект от класа.
* `virtual Book& operator=(const Book& b)`: Виртуален метод за присвояване на стойности на обекта.
* `friend ostream& operator<<(ostream& out, Book& b)`: Предефинира оператора << за извеждане на детайлите на Book обект в изходен поток(output stream).
* `virtual void WriteInFile(ofstream& file)`: Виртуален метод за записисване на данни във файл.
* `static Book* ReadFromFile(ifstream& file)`: Метод за четене на данни от файл.
* `string getTitle()`: Връща заглавието на учебника.
* `void setTitle(string title)`: Задава заглавието на учебника.
* `string getAuthor()`: Връща автора на учебника.
* `void setAuthor(string author)`: Задава автора на учебника.
* `int getEdition()`: Връща изданието на учебника.
* `void setEdition(int edition)`: Задава изданието на учебника.
* `string getIsbn()`: Връща ISBN-а на учебника.
* `void setIsbn(string isbn)`: Задава ISBN-а на учебника.
* `string getPublishDate()`: Връща дата на издаване на учебника.
* `void setPublishDate(string publishDate)`: Задава дата на изадаване на учебника.
* `string* getCertificationDate()`: Връща дата на сертификация на учебника.
* `void setCertificationDate(string* certificationDate)`: Задава дата на сертификация на учебника.
* `bool getIsCertified()`: Връща булев резултат, който показва дали книгата е сертифицирана
* `static Book* InputBook()`: Статичен метод, който се използва за въвеждане на информация за нов обект от класа Book от потребителя чрез клавиатурата.
* `static bool validateTitle(string title)`: Валидация на данни за заглавие.
* `static bool validateAuthor(string author)`: Валидация на данни за автор.
* `static bool validateEdition(int edition)`: Валидация на данни за издание.
* `static bool validateIsbn(string isbn)`: Валидация на данни за ISBN.
* `static bool validateDate(string date)`: Валидация на данни за дата.

---

### **Publisher (Publisher.h)**

Клас, съхраняващ информация за издатели.

#### **Променливи**

* `string name`: Име на издателя.
* `string address`: Адреса на издателя.
* `string phoneNumber`: Телефонен номер на издателя.
* `Book** books`: Указател към указател към обекти от класа Book.
* `int numberOfBooks`: Брой книги.
* `int booksLenght`: Дължина на книгата.

#### **Конструктори**

* `Publisher()`: Default конструктор.
* `Publisher(const Publisher&)`: Copy конструктор.

#### **Функции**

* `Publisher& operator=(Publisher& p)`: Присвояване на стойности на обекта.
* `void WriteInFile(ofstream& file)`: Записване на данни във файл.
* `static Publisher* ReadFromFile(ifstream& file)`: Метод за четене на данни от файл.
* `friend ostream& operator<<(ostream& out, Publisher& p)`: Приятелска функцоя, предефинира оператора << за извеждане на детайлите на Book обект в изходен поток(output stream).
* `string getName()`: Връща името на издателя.
* `void setName(string name)`: Задава името на издателя.
* `string getAddress()`: Връща адреса на издателя.
* `void setAddress(string address)`: Задава адреса на издателя.
* `string getPhoneNumber()`: Връща името на издателя.
* `void setPhoneNumber(string phoneNumber)`: Задава телефонния номер на издателя.
* `Book* getBookByIsbn(string isbn)`: Връща телефонния номер на издателя.
* `void addBook(Book* b)`: Добавяне на нова книга към списъка на книгите, асоцииран с издателя.
* `static Publisher* InputPublisher()`: Статичен метод, за въвеждане на информация за нов обект от класа Book от потребителя чрез клавиатурата.

---

### **StoreBook (StoreBook.h)**

Extends the `Base` class. Manages a collection of `Optic_Material` objects with functionalities for handling the collection and serialization/deserialization.

#### **Променливи**

* `vector<Optic_Material> optic_materials`: A collection of `Optic_Material` objects.

#### **Конструктор**

* `Optic_Materials()`: Default constructor.

#### **Функции**

* `virtual StoreBook& operator=(StoreBook& b)`: 
* `friend ostream& operator<<(ostream& out, StoreBook& b)`: 
* `void setPrice(int price)`:   
* `int getPrice()`: 
* `static StoreBook* ReadFromFile(ifstream& file)`:
* `static StoreBook* InputStoreBook()`:
* `static bool validatePrice(int price)`:

#### **Overrides**

* `virtual StoreBook* clone() override`: 
* `жoid WriteInFile(ofstream& file)`:

---

### **Store (Store.h)**

Extends the `Base` class. Represents an order, encompassing optic materials and a supplier, with functionalities for managing the order and calculating its total cost.

#### **Променливи**

* `Publisher** publishers`: 
* `int numberOfPublishers`:
* `int publishersLength`: 

#### **Конструктор**

* `Store()`: Default constructor.
* `Store(int n)`: 

#### **Функции**

* `void printOptions()`: 
* `void printAvailablePublishers()`: 
* `void printAll()`: 
* `void createPubisher()`: 
* `void createBook()`:
* `void orderBooks()`:
* `void writeInFile()`:
* `void loadFromFile()`:
* `StoreBook* findBookByIsbn(string isbn)`: 
---


---

### Main (`main.cpp`)

* 

---
