#include <iostream>
#include "Book.h"
#include "Students.h"

using namespace std;

// ==================== 测试主函数 ====================
// 覆盖场景：正常借书、借不可借的书、达到借书上限、传空地址、多学生共享图书
int main()
{
    // ---------- 1. 准备图书馆里的图书 ----------
    Book b1("The C++ Programming Language", "Bjarne Stroustrup", 2013, "Addison-Wesley", 1366);
    b1.setPrice(79.99);          // 使用 Book 自己的公有接口

    Book b2("Data Structures and Algorithm Analysis", "Mark Allen Weiss", 2006, "Pearson", 576);
    b2.setPrice(59.00);

    Book b3("Computer Networks", "Andrew S. Tanenbaum", 2011, "Pearson", 960);
    b3.setPrice(89.00);

    Book b4("Operating System Concepts", "Abraham Silberschatz", 2012, "Wiley", 944);
    b4.setPrice(99.00);

    // 一本已经被借走（不可借）的书，用于测试书的状态判断
    Book b5("Clean Code", "Robert C. Martin", 2008, "Prentice Hall", 464);
    b5.setAvailable(false);

    // ---------- 1.5 把所有图书放入书库 ----------
    Book::addBook(&b1);          // 传地址：书库中保存的是书本身的地址
    Book::addBook(&b2);
    Book::addBook(&b3);
    Book::addBook(&b4);
    Book::addBook(&b5);

    // 调用 showbook：显示书库中所有图书的信息和状态（借书前的初始状态）
    cout << endl << "===== 书库初始状态（Book::showbook） =====" << endl;
    Book::showbook();

    // ---------- 2. 创建学生对象 ----------
    Student s1("张三", "2021001", "计算机 2101 班");
    Student s2("李四", "2021002", "计算机 2102 班");

    // ---------- 3. 借书测试 ----------
    cout << "===== 测试 1：正常借书 =====" << endl;
    s1.borrowBook(&b1);          // 传地址（指针）
    s1.borrowBook(&b2);

    cout << endl << "===== 测试 2：借一本已被借出（不可借）的书 =====" << endl;
    s1.borrowBook(&b5);          // 书的状态不允许 -> 失败

    cout << endl << "===== 测试 3：借第 3 本，刚好达到借书上限 =====" << endl;
    s1.borrowBook(&b3);

    cout << endl << "===== 测试 4：已达上限后继续借书 =====" << endl;
    s1.borrowBook(&b4);          // 学生状态不允许 -> 失败

    cout << endl << "===== 测试 5：传入空地址 =====" << endl;
    Book* pNull = NULL;
    s1.borrowBook(pNull);        // 地址无效 -> 失败

    // ---------- 4. 输出学生最终状态与借阅记录 ----------
    cout << endl << "===== 张三的信息 =====" << endl;
    s1.printInfo();
    cout << endl;
    s1.printBorrowRecords();

    // ---------- 5. 验证"书被借出后系统状态已更新" ----------
    cout << endl << "===== 验证图书 b1 的状态 =====" << endl;
    b1.printInfo();

    // ---------- 6. 另一个学生借走仍然可借的书 ----------
    cout << endl << "===== 李四借书 =====" << endl;
    s2.borrowBook(&b4);
    s2.printBorrowRecords();

    // ---------- 7. 借书后再看书库：图书状态已同步更新 ----------
    cout << endl << "===== 借书后的书库状态 =====" << endl;
    Book::showbook();

    return 0;
}
