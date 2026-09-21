#include "Book.h"

// ==================== Book 类的成员函数实现 ====================

// 默认构造函数：把各字段置为初始值
Book::Book()
{
    title = "";
    author = "";
    year = 0;
    publisher = "";
    pages = 0;
    // 初始化公有字段默认值
    price = 0.0;
    available = true;
}

// 带参构造函数
Book::Book(string t, string a, int y, string publisher, int pages)
{
    title = t;
    author = a;
    year = y;
    this->publisher = publisher;  // 形参与成员同名，用 this 指针区分
    this->pages = pages;
    // 初始化公有字段默认值
    price = 0.0;
    available = true;
}

// ---------- 修改器 ----------
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

// 设置能否被借出：Student::borrowBook 会调用它来更新书的系统状态
void Book::setAvailable(bool a)
{
    available = a;
}

// ---------- 访问器 ----------
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

double Book::getPrice()
{
    return price;
}

// 查询书当前能否被借出
bool Book::isAvailable()
{
    return available;
}

// ---------- 输出全部信息 ----------
void Book::printInfo()
{
    cout << "书名: " << title << endl;
    cout << "作者: " << author << endl;
    cout << "年份: " << year << endl;
    cout << "出版社: " << publisher << endl;
    cout << "页数: " << pages << endl;
    cout << "定价: " << price << endl;
    cout << "可借: " << (available ? "是" : "否") << endl;
}
