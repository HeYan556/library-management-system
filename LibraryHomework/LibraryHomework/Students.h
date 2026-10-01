#ifndef STUDENTS_H
#define STUDENTS_H

#include <string>
#include <vector>
#include <cstddef>
#include "Book.h"

using namespace std;

// 一个学生最多可以借的书本数（借书上限）
const int MAX_BORROW = 3;

// ==================== 学生类 Student ====================
// 抽象出的属性：姓名、学号、班级、当前借了多少本书、借阅记录。
//
// 与 Book 类的两种关系：
//   1) 依赖关系（主要）：borrowBook(Book* book) 的参数传递地址，
//      方法内部通过 Book 的公有接口判断/修改书的状态。
//   2) 组合关系（次要）：borrowedBooks 是 Book 对象数组，
//      它是学生自身的一部分，随学生对象一起创建、一起销毁。
class Student {
private:
    string name;        // 姓名
    string id;          // 学号
    string className;   // 班级

    // 【组合关系】学生"拥有"自己的借阅区，Book 对象是 Student 的组成部分
    Book borrowedBooks[MAX_BORROW];   // 当前借在手里的书

    int borrowedCount;                // 当前借了多少本书（学生状态）

    // 借阅记录：用 STL 容器 vector<string>（动态数组）保存，借一本就追加一条
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

    // 判断学生自身状态是否允许再借书（是否达到借书上限）
    bool canBorrow();

    // ---------- 借书（依赖关系所在） ----------
    // 参数必须传地址：这里使用 Book 指针。
    // 借书能否成功，取决于"学生状态"和"书的状态"是否都允许。
    void borrowBook(Book* book);

    // ---------- 输出信息 ----------
    void printInfo();
    void printBorrowRecords();
};

#endif // STUDENTS_H
