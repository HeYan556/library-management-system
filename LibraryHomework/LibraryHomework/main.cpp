#include <iostream>
#include <windows.h>        // SetConsoleOutputCP：让控制台按 UTF-8 显示中文

#include "BookResource.h"
#include "Stack.h"
#include "Students.h"
#include "User.h"
#include "LibraryRepository.h"
#include "LibrarySystem.h"

using namespace std;

// ==================== 实验六：文件输入输出流 + 用户登录 + 持久化 ====================
// 程序流程：
//   1) 从三个文本文件加载数据（资源 → 学生 → 账号，顺序不能乱）
//   2) 用户登录（最多 3 次机会），按角色进入不同菜单
//   3) 退出时把内存中的对象写回文件，下次启动状态还在
//
// 说明：控制台默认是 GBK 编码，而源码与数据文件都是 UTF-8，
// 若不做下面两行设置，中文会显示成乱码。

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 三个容器都是实验五的类模板 Stack<T> 的实例
    Stack<BookResource*> library;   // 资源库
    Stack<Student>       roster;    // 学生名册
    Stack<User>          users;     // 账号表

    cout << "========== 图书管理系统 启动 ==========" << endl;

    // ---------- 1. 加载（资源必须先于学生，学生要按编号反查资源） ----------
    LibraryRepository::loadResources("data/resources.txt", library);
    LibraryRepository::loadStudents ("data/students.txt",  roster, library);
    LibraryRepository::loadUsers    ("data/users.txt",     users);

    // ---------- 2. 登录 ----------
    LibrarySystem sys(library, roster, users);
    User* current = sys.login();
    if (current == nullptr) {
        cout << "三次登录均失败，程序退出。" << endl;
        return 0;
    }
    if (current->isAdmin()) sys.runAdmin(*current);
    else                    sys.runReader(*current);

    // ---------- 3. 退出前保存 ----------
    sys.saveAll();

    // ---------- 4. 释放资源（基类指针 + 虚析构，确保子类部分也被清理） ----------
    for (Stack<BookResource*>::iterator it = library.begin(); it != library.end(); ++it) {
        delete *it;
    }
    library.clear();

    cout << "数据已保存，再见！" << endl;
    return 0;
}
