#include <iostream>
#include<string>

using namespace std;
class Book {
private:
	string title;
	string author;
	int year;
	string publisher;
	int pages;
public:
	Book(string t, string a, int y, string publisher, int pages);
	string getTitle();
	string getAuthor();
	int getYear();
	string getPublisher();
	int getPages();

	// 可直接访问的公有字段：定价与在馆状态
	double price;
	bool available; // true = 可借, false = 不可借

	// 基本操作：修改器（setters）
	void setTitle(const string& t);
	void setAuthor(const string& a);
	void setYear(int y);
	void setPublisher(const string& p);
	void setPages(int p);
	void setPrice(double p);
	void setAvailable(bool a);

	// 基本操作：访问器（getters）
	double getPrice();
	bool isAvailable();

	// 输出信息
	void printInfo();
};

// 方法实现
Book::Book(string t, string a, int y, string publisher, int pages)
{
    title = t;
    author = a;
    year = y;
    this->publisher = publisher;
    this->pages = pages;
    // 初始化公有字段默认值
    price = 0.0;
    available = true;
}

string Book::getTitle()
{
    return title;
}

string Book::getAuthor()
{
    return author;
}

int Book::getYear()
{
    return year;
}

string Book::getPublisher()
{
    return publisher;
}

int Book::getPages()
{
    return pages;
}

// setters
void Book::setTitle(const string& t)
{
    title = t;
}

void Book::setAuthor(const string& a)
{
    author = a;
}

void Book::setYear(int y)
{
    year = y;
}

void Book::setPublisher(const string& p)
{
    publisher = p;
}

void Book::setPages(int p)
{
    pages = p;
}

void Book::setPrice(double p)
{
    price = p;
}

void Book::setAvailable(bool a)
{
    available = a;
}

// getters for price/available

double Book::getPrice()
{
    return price;
}

bool Book::isAvailable()
{
    return available;
}

void Book::printInfo()
{
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Year: " << year << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "Pages: " << pages << endl;
    cout << "Price: " << price << endl;
    cout << "Available: " << (available ? "Yes" : "No") << endl;
}