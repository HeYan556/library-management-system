#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <iostream>
#include <string>
#include "Stack.h"
#include "Students.h"
#include "User.h"

using namespace std;

// ==================== 业务系统 LibrarySystem ====================
// 实验六新增：负责登录、菜单与各项业务流程。
// 它不直接碰文件（交给 LibraryRepository），只操作三个容器：
//   Stack<BookResource*>  资源库
//   Stack<Student>       学生名册
//   Stack<User>          账号表
// 这三个容器都是实验五的类模板 Stack<T> 的实例 —— 实验五成果在此继续复用。

class LibrarySystem {
private:
    Stack<BookResource*>& lib;
    Stack<Student>&       roster;
    Stack<User>&          users;

    string resPath;   // data/resources.txt
    string stuPath;   // data/students.txt
    string usrPath;   // data/users.txt

    int    nextId() const;                 // 新资源的编号 = 现有最大编号 + 1
    static string typeName(const char* tag);

public:
    LibrarySystem(Stack<BookResource*>& l, Stack<Student>& r, Stack<User>& u);

    // ---------- 登录 ----------
    User* login();                         // 最多 3 次机会，成功返回账号指针

    // ---------- 两套菜单 ----------
    void runAdmin(User& u);
    void runReader(User& u);

    // ---------- 功能 ----------
    void saveAll() const;                  // 立即落盘
    void listResources() const;            // iomanip 表格输出
    void addResource();
    void removeResource();
    void queryResource() const;            // 泛型算法 + lambda 过滤
    void listStudents() const;
    void listUsers() const;
    void showStudent(const Student& s) const;

    BookResource* findResourceById(int id);
    Student*      findStudentById(const string& sid);

    void borrowFor(Student& s);
    void returnFor(Student& s);
};

#endif // LIBRARYSYSTEM_H
