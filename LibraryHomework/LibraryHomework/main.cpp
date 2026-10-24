#include <iostream>
#include <string>
#include "BookResource.h"
#include "GeneralBook.h"
#include "Magazine.h"
#include "ElectronicResource.h"
#include "Stack.h"
#include "Students.h"
#include "Algorithms.h"

using namespace std;

// ==================== 实验五测试主函数：模板与泛型算法 ====================
// 覆盖场景：
//   1) Stack<T> 类模板：同一份容器代码，既能装 BookResource* 也能装 Student
//   2) 迭代器接口：begin()/end() 让自定义容器也能吃泛型算法
//   3) 函数模板算法：forEach / findIf / countIf / filter / countType / printAll
//   4) 编译期泛型 + 运行期多态协同：同一句 ->printInfo() 各自派发到子类版本
//   5) 学生借阅区改用 vector 后，支持"归还"（erase），定长数组做不到

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
    // 2. 【类模板】Stack<BookResource*>：装基类指针，多态完整保留
    // ============================================================
    cout << "===== Stack<BookResource*>：类模板装基类指针 =====" << endl;
    Stack<BookResource*> lib;
    lib.addBook(&b1);
    lib.addBook(&b2);
    lib.addBook(&m1);
    lib.addBook(&e1);
    lib.addBook(&e2);
    cout << "书库共 " << lib.size() << " 份资源。" << endl;

    // ============================================================
    // 3. 【泛型算法】算法只认迭代器区间，与容器类型解耦
    // ============================================================
    cout << endl << "===== 泛型算法 printAll：遍历 + 多态打印 =====" << endl;
    printAll(lib.begin(), lib.end());

    // countIf：按谓词统计
    int expensive = countIf(lib.begin(), lib.end(),
                            [](BookResource* r) { return r->getPrice() >= 50.0; });
    cout << endl << "定价 >= 50 元的资源有 " << expensive << " 份。" << endl;

    // findIf：按谓词查找
    Stack<BookResource*>::iterator found =
        findIf(lib.begin(), lib.end(),
               [](BookResource* r) { return r->getTitle() == "程序员"; });
    cout << endl << "--- findIf：按刊名查找《程序员》---" << endl;
    if (found != lib.end()) (*found)->printInfo();
    else                    cout << "未找到。" << endl;

    // countType：模板 + dynamic_cast（运行期类型识别）+ 多态
    cout << endl << "--- countType：按真实类型分别统计 ---" << endl;
    cout << "纸质书 "   << countType<GeneralBook>(lib.begin(), lib.end())
         << " 本，杂志 " << countType<Magazine>(lib.begin(), lib.end())
         << " 份，电子资源 "
         << countType<ElectronicResource>(lib.begin(), lib.end())
         << " 份。" << endl;

    // filter + forEach：筛出子集后再遍历
    vector<BookResource*> cheap =
        filter(lib.begin(), lib.end(),
               [](BookResource* r) { return r->getPrice() < 50.0; });
    cout << endl << "--- filter：定价低于 50 元的共 " << cheap.size()
         << " 份 ---" << endl;
    forEach(cheap.begin(), cheap.end(),
            [](BookResource* r) { cout << "  - 《" << r->getTitle()
                                       << "》 " << r->getPrice() << " 元" << endl; });

    // ============================================================
    // 4. 借阅与归还：借阅区改用 vector，归还 = erase
    // ============================================================
    cout << endl << "===== 借阅与归还（vector 让「摘除」成为可能）=====" << endl;
    Student s1("张三", "2021001", "计算机 2101 班");
    Student s2("李四", "2021002", "计算机 2102 班");

    cout << "--- 借一般图书 ---" << endl;
    s1.borrowBook(&b2);
    cout << endl << "--- 借杂志 ---" << endl;
    s1.borrowBook(&m1);
    cout << endl << "--- 借已被借出的电子资源（应失败）---" << endl;
    s1.borrowBook(&e2);
    cout << endl << "--- 借电子资源 ---" << endl;
    s1.borrowBook(&e1);
    cout << endl << "--- 已达上限（应失败）---" << endl;
    s1.borrowBook(&b1);

    s1.printInfo();

    cout << endl << "--- 归还杂志（多态归还 + 从容器中 erase）---" << endl;
    s1.returnBook(&m1);
    s1.printInfo();
    cout << endl << "--- 归还一本没借过的资源（应失败）---" << endl;
    s1.returnBook(&b1);

    s2.borrowBook(&m1);
    s1.printBorrowRecords();
    s2.printBorrowRecords();

    // ============================================================
    // 5. 【同一份模板代码】Stack<Student>：装完全不同类型的元素
    // ============================================================
    cout << endl << "===== Stack<Student>：类模板复用，装另一种元素 =====" << endl;
    Stack<Student> roster;
    roster.push(s1);
    roster.push(s2);
    cout << "名册共 " << roster.size() << " 人：" << endl;
    forEach(roster.begin(), roster.end(),
            [](Student& s) { cout << "  " << s.getId() << "  " << s.getName()
                                  << "（" << s.getClassName() << "）" << endl; });

    // ============================================================
    // 6. 借还之后的书库状态（对象共享，状态已同步）
    // ============================================================
    cout << endl << "===== 借阅后的书库状态 =====" << endl;
    lib.showbook();

    return 0;
}
