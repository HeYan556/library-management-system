#ifndef STUDENTS_H
#define STUDENTS_H

#include <string>
#include <vector>
#include <cstddef>
#include "BookResource.h"
#include "Stack.h"

using namespace std;

// 一个学生最多可以借的资源份数
// 实验五说明：MAX_BORROW 是"业务规则"，容器容量交给 vector 自己管理，
// 二者分工明确 —— 容器负责存得下，规则负责借几份。
const int MAX_BORROW = 3;

// ==================== 学生类 Student ====================
// 依赖倒置原则（DIP）：只认 BookResource*，任意子类资源都能借。
//
// 实验五升级：
//   借阅区 borrowedBooks 由定长数组 BookResource* borrowedBooks[MAX_BORROW]
//   换成 std::vector<BookResource*>，于是可以支持"归还"（从容器中 erase），
//   这是原先定长数组很难干净做到的。
//
// 与 BookResource 的关系：
//   1) 依赖关系：borrowBook/returnBook 通过基类指针调用虚函数，
//      具体执行哪个子类的流程由运行时的对象类型决定（多态）。
//   2) 组合关系：借阅区保存所借资源的地址（资源本身在书库/主函数中创建）。

class Student {
private:
    string name;        // 姓名
    string id;          // 学号
    string className;   // 班级

    // 【组合】学生的借阅区：容量由容器自管理，业务上限仍由 MAX_BORROW 控制
    vector<BookResource*> borrowedBooks;

    // 借阅历史记录（归还后记录保留，作为历史凭证）
    vector<string>        borrowRecords;

public:
    // ---------- 构造函数 ----------
    Student();
    Student(string n, string id, string className);

    // ---------- 访问器（统一加 const：便于 const 对象/谓词调用） ----------
    string getName()      const;
    string getId()        const;
    string getClassName() const;
    int    getBorrowedCount() const;
    int    getMaxBorrow()     const;

    // 对外提供借阅区只读视图，便于用泛型算法遍历
    const vector<BookResource*>& getBorrowedBooks() const;

    bool canBorrow() const;

    // ---------- 借书（依赖抽象 BookResource，多态调用） ----------
    void borrowBook(BookResource* book);

    // ---------- 还书（实验五新增：依赖 vector 的 erase） ----------
    void returnBook(BookResource* book);

    // ---------- 序列化（实验六：文件输入输出流） ----------
    // 一行格式：STU|姓名|学号|班级|借阅中的资源编号(;分隔，可为空)
    void saveTo(ostream& os) const;
    void loadFrom(istream& is, const Stack<BookResource*>& lib);

    // 从文件恢复借阅区时使用：只登记、不打印提示、不再走借书流程
    void restoreBorrowed(BookResource* book);

    // ---------- 输出信息 ----------
    void printInfo() const;
    void printBorrowRecords() const;
};

#endif // STUDENTS_H
