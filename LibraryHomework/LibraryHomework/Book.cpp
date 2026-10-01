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

void Book::setPublisher(const string& pu)
{
    publisher = pu;
}

void Book::setPages(int pa)
{
    pages = pa;
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

// ==================== 书库相关（静态成员实现） ====================
// 静态成员变量必须在类外定义并初始化（所有 Book 对象共享这一份数据）
int   Book::bookCount = 0;               // 一开始书库里没有书
Book* Book::bookLib[Book::MAX_BOOKS];    // 书库：50 个"放书的位置"

// 把一本图书放入书库（参数传地址）
void Book::addBook(Book* b)
{
    // 先判断地址是否有效
    if (b == NULL)
    {
        cout << "添加失败：图书地址无效！" << endl;
        return;
    }
    // 再判断书库是否已满
    if (bookCount >= MAX_BOOKS)
    {
        cout << "书库已满（上限 " << MAX_BOOKS << " 本），无法再添加！" << endl;
        return;
    }
    bookLib[bookCount] = b;   // 存入这本书的地址
    bookCount++;              // 书库数量加 1
    cout << "《" << b->getTitle() << "》已放入书库（当前共 "
         << bookCount << " 本）。" << endl;
}

// 显示书库中所有图书信息和状态
void Book::showbook()
{
    cout << "========== 书库图书清单（共 " << bookCount << " 本） ==========" << endl;
    if (bookCount == 0)
    {
        cout << "书库暂时为空。" << endl;
        return;
    }
    for (int i = 0; i < bookCount; i++)
    {
        cout << "----- 第 " << i + 1 << " 本 -----" << endl;
        bookLib[i]->printInfo();   // 复用已有的输出函数（含"可借"状态）
    }
}
