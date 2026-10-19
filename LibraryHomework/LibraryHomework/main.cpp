#include <iostream>
#include "BookResource.h"
#include "GeneralBook.h"
#include "Magazine.h"
#include "ElectronicResource.h"
#include "Stack.h"
#include "Students.h"

using namespace std;

// 实验四测试主函数：多态与虚函数 + 依赖倒置原则（DIP）
// 覆盖场景：
//   1) 基类指针数组统一收纳三种子类对象（DIP 数据结构）
//   2) 通过基类指针调用虚函数 printInfo()——动态派发到各子类版本
//   3) Stack::showbook() 自动显示子类特有字段（Stack 零改动）
//   4) Student::borrowBook(BookResource*) 多态借阅任意类型资源
//   5) 各子类不同的借还流程（扫码/登记/直接访问）全部正常发挥

int main() {
    // ============================================================
    // 1. 准备三种资源（具体子类对象）
    // ============================================================
    GeneralBook b1("C++ Primer Plus", "Stephen Prata", 2012,
                   "Addison-Wesley", 1200,
                   "978-0321776402", 6);
    b1.setPrice(99.00);

    GeneralBook b2("Effective C++", "Scott Meyers", 2005,
                   "Addison-Wesley", 320,
                   "978-0321334879", 3);
    b2.setPrice(58.00);

    Magazine m1("程序员", "程序员的良师益友", 2024,
                "《程序员》杂志社", 96,
                312, "月刊", "张主编");
    m1.setPrice(20.00);

    ElectronicResource e1("Clean Architecture (eBook)", "Robert C. Martin", 2017,
                          "Pearson", 0,
                          "EPUB", "https://lib.example/clean-arch.epub", 12.5);
    e1.setPrice(30.00);

    ElectronicResource e2("设计模式：可复用面向对象软件的基础 (PDF)", "GoF", 1994,
                          "机械工业出版社", 0,
                          "PDF", "https://lib.example/gof.pdf", 8.2);
    e2.setPrice(0.00);
    e2.setAvailable(false);   // 模拟已被借出，用于测试失败分支

    // ============================================================
    // 2. 【DIP 核心演示】基类指针数组统一收纳三种子类对象
    //    高层代码只认 BookResource*，不关心具体是什么子类
    // ============================================================
    cout << "===== 基类指针数组统一处理（多态调用 printInfo）=====" << endl;
    BookResource* resources[] = { &b1, &b2, &m1, &e1, &e2 };
    const int RES_COUNT = 5;
    for (int i = 0; i < RES_COUNT; i++) {
        // 同一行代码，五种对象各自执行自己的 printInfo 版本
        resources[i]->printInfo();
        cout << endl;
    }

    // ============================================================
    // 3. 放入书库，showbook() 展示多态效果（Stack 一行未改）
    // ============================================================
    Stack lib;
    lib.addBook(&b1);
    lib.addBook(&b2);
    lib.addBook(&m1);
    lib.addBook(&e1);
    lib.addBook(&e2);

    cout << endl
         << "===== 书库清单（Stack::showbook 现在能显示子类完整信息）=====" << endl;
    lib.showbook();

    // ============================================================
    // 4. 多态借还：基类指针调用虚函数 borrow/returnBook
    // ============================================================
    cout << endl
         << "===== 基类指针多态借还（同一句调用，不同子类流程）=====" << endl;
    BookResource* p = NULL;   // 只用一个基类指针演示

    cout << "--- 指向一般图书：扫码流程 ---" << endl;
    p = &b1;
    p->borrow();

    cout << "--- 指向杂志：登记流程 ---" << endl;
    p = &m1;
    p->borrow();

    cout << "--- 指向电子资源：直接访问流程 ---" << endl;
    p = &e1;
    p->borrow();

    cout << "--- 重复借同一本（应失败）---" << endl;
    p->borrow();

    cout << "--- 多态归还：电子资源撤销权限 ---" << endl;
    p->returnBook();

    // ============================================================
    // 5. 学生借阅：依赖倒置后，任意类型资源都能借
    // ============================================================
    cout << endl
         << "===== 学生借阅（borrowBook(BookResource*)，三种资源通借）=====" << endl;
    Student s1("张三", "2021001", "计算机 2101 班");
    Student s2("李四", "2021002", "计算机 2102 班");

    cout << "--- 测试 1：借一般图书 ---" << endl;
    s1.borrowBook(&b2);

    cout << endl << "--- 测试 2：借杂志（实验三做不到，现在可以）---" << endl;
    s1.borrowBook(&m1);

    cout << endl << "--- 测试 3：借已被借出的电子资源（应失败）---" << endl;
    s1.borrowBook(&e2);

    cout << endl << "--- 测试 4：借电子资源 ---" << endl;
    s1.borrowBook(&e1);

    cout << endl << "--- 测试 5：已达借阅上限（应失败）---" << endl;
    s1.borrowBook(&b1);

    cout << endl << "--- 测试 6：传入空地址（应失败）---" << endl;
    BookResource* pNull = NULL;
    s1.borrowBook(pNull);

    cout << endl << "--- 测试 7：李四借另一本 ---" << endl;
    s2.borrowBook(&b1);

    // ============================================================
    // 6. 输出学生信息与借阅记录
    // ============================================================
    cout << endl << "===== 张三的信息 =====" << endl;
    s1.printInfo();
    cout << endl;
    s1.printBorrowRecords();

    cout << endl << "===== 李四的信息 =====" << endl;
    s2.printInfo();
    cout << endl;
    s2.printBorrowRecords();

    // ============================================================
    // 7. 借书后的书库状态（对象共享，状态已同步更新）
    // ============================================================
    cout << endl << "===== 借阅后的书库状态 =====" << endl;
    lib.showbook();

    return 0;
}