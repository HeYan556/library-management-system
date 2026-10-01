#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

using namespace std;

// ==================== 图书类 Book ====================
// 职责：保存一本书的信息，并对外提供访问/修改接口。
// 说明：Student 类会通过公有接口使用本类，因此本类是 Student 的"被依赖者"。
class Book {
private:
    string title;      // 书名
    string author;     // 作者
    int    year;       // 出版年份
    string publisher;  // 出版社
    int    pages;      // 页数

public:
    // ---------- 构造函数 ----------
    // 默认构造函数：Student 类中组合了 Book 对象数组，需要它才能创建对象
    Book();
    // 带参构造函数
    Book(string t, string a, int y, string publisher, int pages);

    // ---------- 公有字段：定价与在馆状态 ----------
    double price;      // 定价
    bool   available;  // true = 可借, false = 不可借

    // ---------- 修改器（setters） ----------
    void setTitle(const string& t);
    void setAuthor(const string& a);
    void setYear(int y);
    void setPublisher(const string& p);
    void setPages(int p);
    void setPrice(double p);
    void setAvailable(bool a);

    // ---------- 访问器（getters） ----------
    string getTitle();
    string getAuthor();
    int    getYear();
    string getPublisher();
    int    getPages();
    double getPrice();
    bool   isAvailable();

    // ---------- 输出信息 ----------
    void printInfo();

    // ---------- 书库（静态成员：全体 Book 对象共享同一份数据） ----------
    static const int MAX_BOOKS = 50;   // 书库容量上限（图书数量少于 50 本）

    static int   bookCount;            // 【成员变量】书库中当前图书数量
    static Book* bookLib[MAX_BOOKS];   // 【成员变量】书库：存放所有图书的地址
                                       //（存地址而不是复制品，保证显示的状态始终是最新的）

    static void addBook(Book* b);      // 把一本图书放入书库（传地址）
    static void showbook();            // 【成员函数】显示书库中所有图书信息和状态
};

#endif // BOOK_H
