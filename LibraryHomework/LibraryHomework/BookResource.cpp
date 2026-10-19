#include "BookResource.h"

// ==================== BookResource 类的成员函数实现 ====================
// 实验四：抽象基类 + 纯虚接口。共有字段与共有输出在此实现，
// 三个纯虚函数（printInfo / borrow / returnBook）由各子类分别实现。

// ---------- 构造函数 ----------
BookResource::BookResource() {
    title = "";
    author = "";
    year = 0;
    publisher = "";
    pages = 0;
    price = 0.0;
    available = true;
}

BookResource::BookResource(string t, string a, int y, string pub, int pages) {
    this->title = t;
    this->author = a;
    this->year = y;
    this->publisher = pub;
    this->pages = pages;
    price = 0.0;
    available = true;
}

// ---------- 虚析构函数 ----------
// 通过基类指针销毁派生类对象时，虚析构保证先调用子类析构、再调用基类析构。
BookResource::~BookResource() {
    // 当前子类无动态资源需要释放，此处留空即可。
}

// ---------- 修改器 ----------
void BookResource::setTitle(const string& t)    { title = t; }
void BookResource::setAuthor(const string& a)   { author = a; }
void BookResource::setYear(int y)               { year = y; }
void BookResource::setPublisher(const string& p){ publisher = p; }
void BookResource::setPages(int p)              { pages = p; }
void BookResource::setPrice(double p)           { price = p; }
void BookResource::setAvailable(bool a)         { available = a; }

// ---------- 访问器 ----------
string BookResource::getTitle()    { return title; }
string BookResource::getAuthor()   { return author; }
int    BookResource::getYear()     { return year; }
string BookResource::getPublisher(){ return publisher; }
int    BookResource::getPages()    { return pages; }
double BookResource::getPrice()    { return price; }
bool   BookResource::isAvailable() { return available; }

// ---------- 共有字段输出（供子类 printInfo 复用） ----------
void BookResource::printCommonInfo() {
    cout << "  名称: "    << title       << endl;
    cout << "  责任人: "  << author      << endl;
    cout << "  年份: "    << year        << endl;
    cout << "  出版社: "  << publisher   << endl;
    cout << "  页数: "    << pages       << endl;
    cout << "  定价: "    << price       << endl;
    cout << "  状态: "
         << (available ? "可借" : "已借出")    << endl;
}

// ---------- 纯虚函数在此不提供实现 ----------
// printInfo / borrow / returnBook 的函数体由
// GeneralBook、Magazine、ElectronicResource 各自提供。