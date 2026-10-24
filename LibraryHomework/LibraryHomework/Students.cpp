#include <algorithm>
#include "Students.h"

// ==================== Student 类的成员函数实现 ====================

// ---------- 构造函数 ----------
// 借阅区由 vector 自己初始化为空，不再需要手工把每个元素置 NULL
Student::Student() : name(""), id(""), className("") {}

Student::Student(string n, string i, string c)
    : name(n), id(i), className(c) {}

// ---------- 访问器 ----------
string Student::getName()          const { return name; }
string Student::getId()            const { return id; }
string Student::getClassName()     const { return className; }
int    Student::getBorrowedCount() const { return (int)borrowedBooks.size(); }
int    Student::getMaxBorrow()     const { return MAX_BORROW; }

const vector<BookResource*>& Student::getBorrowedBooks() const { return borrowedBooks; }

// 业务上限仍由 MAX_BORROW 决定；容器只负责装得下
bool Student::canBorrow() const {
    return (int)borrowedBooks.size() < MAX_BORROW;
}

// ---------- 借书（依赖倒置 + 多态的体现） ----------
// 形参是抽象基类指针：GeneralBook/Magazine/ElectronicResource 都能传进来。
// borrow() 是虚函数：传哪种资源，就执行哪种资源自己的借阅流程。
void Student::borrowBook(BookResource* book) {
    // 第 1 步：地址有效性
    if (book == nullptr) {
        cout << "借阅失败：资源不存在（传入的是空地址）！" << endl;
        return;
    }
    // 第 2 步：学生状态（业务规则）
    if (!canBorrow()) {
        cout << "借阅失败：学生 " << name << " 已借满 "
             << MAX_BORROW << " 份，不能继续借！" << endl;
        return;
    }
    // 第 3 步：资源状态（通过基类接口访问）
    if (!book->isAvailable()) {
        cout << "借阅失败：《" << book->getTitle()
             << "》已被借出，暂不可借！" << endl;
        return;
    }
    // 第 4 步：多态调用——扫码/登记/直接访问，由对象真实类型决定
    book->borrow();

    // 4.1 存入借阅区（容器自动扩容，无需关心下标）
    borrowedBooks.push_back(book);
    // 4.2 记录本次借阅
    borrowRecords.push_back("《" + book->getTitle() +
                            "》  作者：" + book->getAuthor());

    cout << "借阅成功：" << name << "（学号 " << id << "）借了《"
         << book->getTitle() << "》，当前已借 "
         << borrowedBooks.size() << "/" << MAX_BORROW << " 份。" << endl;
}

// ---------- 还书（实验五新增） ----------
// 依赖 vector 的 erase：借了哪份就摘掉哪份，借阅区可以被再次利用。
// 这正是原先定长数组不方便的地方：数组只能把元素置 NULL，size 语义还要手工维护。
void Student::returnBook(BookResource* book) {
    if (book == nullptr) {
        cout << "归还失败：资源不存在（传入的是空地址）！" << endl;
        return;
    }
    vector<BookResource*>::iterator it =
        find(borrowedBooks.begin(), borrowedBooks.end(), book);
    if (it == borrowedBooks.end()) {
        cout << "归还失败：" << name << " 并未借阅《"
             << book->getTitle() << "》！" << endl;
        return;
    }
    book->returnBook();            // ★ 多态归还：扫码 / 登记 / 撤销权限自动分流
    borrowedBooks.erase(it);       // ★ 从容器中摘除
    borrowRecords.push_back("归还：《" + book->getTitle() + "》");

    cout << "归还成功：" << name << " 归还了《" << book->getTitle()
         << "》，当前已借 " << borrowedBooks.size() << "/" << MAX_BORROW
         << " 份。" << endl;
}

// ---------- 输出学生信息 ----------
void Student::printInfo() const {
    cout << "姓名: " << name << endl;
    cout << "学号: " << id << endl;
    cout << "班级: " << className << endl;
    cout << "当前借阅数: " << borrowedBooks.size() << " / " << MAX_BORROW << endl;
}

// ---------- 输出借阅记录（历史，含归还流水） ----------
void Student::printBorrowRecords() const {
    cout << "--- " << name << " 的借阅记录 ---" << endl;
    if (borrowRecords.empty()) {
        cout << "暂无借阅记录。" << endl;
        return;
    }
    int i = 1;
    for (const string& rec : borrowRecords) {
        cout << i++ << ". " << rec << endl;
    }
}