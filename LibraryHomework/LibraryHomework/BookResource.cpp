#include "BookResource.h"

// ==================== BookResource 类的成员函数实现 ====================
// 实验四：抽象基类 + 纯虚接口。共有字段与共有输出在此实现，
// 三个纯虚函数（printInfo / borrow / returnBook）由各子类分别实现。

// ---------- 构造函数 ----------
BookResource::BookResource() {
    id = 0;
    title = "";
    author = "";
    year = 0;
    publisher = "";
    pages = 0;
    price = 0.0;
    available = true;
}

BookResource::BookResource(string t, string a, int y, string pub, int pages) {
    this->id = 0;
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

// ---------- 访问器（const：查询不修改对象状态） ----------
string BookResource::getTitle()     const { return title; }
string BookResource::getAuthor()    const { return author; }
int    BookResource::getYear()      const { return year; }
string BookResource::getPublisher() const { return publisher; }
int    BookResource::getPages()     const { return pages; }
double BookResource::getPrice()     const { return price; }
bool   BookResource::isAvailable()  const { return available; }

// ---------- 共有字段输出（供子类 printInfo 复用） ----------
void BookResource::printCommonInfo() const {
    cout << "  名称: "    << title       << endl;
    cout << "  责任人: "  << author      << endl;
    cout << "  年份: "    << year        << endl;
    cout << "  出版社: "  << publisher   << endl;
    cout << "  页数: "    << pages       << endl;
    cout << "  定价: "    << price       << endl;
    cout << "  状态: "
         << (available ? "可借" : "已借出")    << endl;
}

// ---------- 编号 ----------
int  BookResource::getId() const  { return id; }
void BookResource::setId(int i)   { id = i; }

// ---------- 序列化：共有字段 ----------
// 子类 saveTo/loadFrom 复用这两个函数，字段顺序与资源文件保持一致：
//   编号 | 名称 | 责任人 | 年份 | 出版社 | 页数 | 定价 | 是否可借(1/0)
void BookResource::saveCommon(ostream& os) const {
    os << id << '|' << title << '|' << author << '|' << year << '|'
       << publisher << '|' << pages << '|' << price << '|'
       << (available ? 1 : 0);
}

void BookResource::loadCommon(istream& is) {
    string f;
    getline(is, f, '|');  id        = f.empty() ? 0 : stoi(f);
    getline(is, title, '|');
    getline(is, author, '|');
    getline(is, f, '|');  year      = f.empty() ? 0 : stoi(f);
    getline(is, publisher, '|');
    getline(is, f, '|');  pages     = f.empty() ? 0 : stoi(f);
    getline(is, f, '|');  price     = f.empty() ? 0.0 : stod(f);
    getline(is, f, '|');  available = (f == "1");
}

// ---------- 流运算符：非虚接口，内部调用虚函数派发 ----------
ostream& operator<<(ostream& os, const BookResource& r) {
    r.saveTo(os);          // ★ 虚调用：写到哪个子类由对象真实类型决定
    return os;
}

istream& operator>>(istream& is, BookResource& r) {
    r.loadFrom(is);        // ★ 虚调用
    return is;
}

// ---------- 纯虚函数在此不提供实现 ----------
// printInfo / borrow / returnBook 的函数体由
// GeneralBook、Magazine、ElectronicResource 各自提供。