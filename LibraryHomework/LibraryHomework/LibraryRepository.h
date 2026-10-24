#ifndef LIBRARYREPOSITORY_H
#define LIBRARYREPOSITORY_H

#include <iostream>
#include <string>
#include "Stack.h"
#include "Students.h"
#include "User.h"

using namespace std;

// ==================== 数据仓库 LibraryRepository ====================
// 实验六新增：只负责"把内存里的对象写到文件、把文件里的文本还原成对象"。
// 它不参与任何业务逻辑，也不认识菜单 —— 职责单一。
//
// 三个数据文件（相对程序运行目录）：
//   data/resources.txt  资源库
//   data/students.txt   学生与借阅区
//   data/users.txt      登录账号
//
// 所有读写都用 C++ 输入输出流：ifstream / ofstream / istringstream。

class LibraryRepository {
public:
    static bool loadResources(const string& path, Stack<BookResource*>& lib);
    static bool saveResources(const string& path, const Stack<BookResource*>& lib);

    // 注意：学生必须"在资源之后"加载，否则按编号关联借阅关系时会找不到资源
    static bool loadStudents(const string& path, Stack<Student>& roster,
                             const Stack<BookResource*>& lib);
    static bool saveStudents(const string& path, const Stack<Student>& roster);

    static bool loadUsers(const string& path, Stack<User>& users);
    static bool saveUsers(const string& path, const Stack<User>& users);
};

#endif // LIBRARYREPOSITORY_H
