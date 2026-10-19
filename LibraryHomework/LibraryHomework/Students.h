#ifndef STUDENTS_H
#define STUDENTS_H

#include <string>
#include <vector>
#include <cstddef>
#include "BookResource.h"

using namespace std;

// 一个学生最多可以借的资源份数
const int MAX_BORROW = 3;

// ==================== 学生类 Student ====================
// 实验四升级：遵守依赖倒置原则（DIP）。
//
//   升级前：borrowBook(GeneralBook*) + GeneralBook 值数组
//           → 高层模块依赖具体子类，杂志/电子资源借不了
//   升级后：borrowBook(BookResource*) + BookResource* 指针数组
//           → 高层模块只依赖抽象基类，任意子类资源都能借
//
// 与 BookResource 的关系：
//   1) 依赖关系：borrowBook 通过基类指针调用虚函数 borrow()，
//      具体执行哪个子类的流程由运行时的对象类型决定（多态）。
//   2) 组合关系：borrowedBooks 是基类指针数组，
//      保存所借资源的地址（资源本身在书库/主函数中创建）。

class Student {
private:
    string name;        // 姓名
    string id;          // 学号
    string className;   // 班级

    // 【组合】学生"拥有"自己的借阅区（基类指针数组，统一管理各类资源）
    BookResource* borrowedBooks[MAX_BORROW];
    int           borrowedCount;

    // 借阅记录
    vector<string> borrowRecords;

public:
    // ---------- 构造函数 ----------
    Student();
    Student(string n, string id, string className);

    // ---------- 访问器 ----------
    string getName();
    string getId();
    string getClassName();
    int    getBorrowedCount();
    int    getMaxBorrow();

    bool canBorrow();

    // ---------- 借书（依赖抽象 BookResource，多态调用） ----------
    void borrowBook(BookResource* book);

    // ---------- 输出信息 ----------
    void printInfo();
    void printBorrowRecords();
};

#endif // STUDENTS_H