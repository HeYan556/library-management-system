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
};

#endif // BOOK_H
