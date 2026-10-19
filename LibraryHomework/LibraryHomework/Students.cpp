#include "Students.h"

// ==================== Student 类的成员函数实现 ====================

Student::Student() {
    name = "";
    id = "";
    className = "";
    borrowedCount = 0;
    // 借阅区指针全部置空
    for (int i = 0; i < MAX_BORROW; i++) {
        borrowedBooks[i] = NULL;
    }
}

Student::Student(string n, string i, string c) {
    this->name = n;
    this->id = i;
    this->className = c;
    borrowedCount = 0;
    for (int k = 0; k < MAX_BORROW; k++) {
        borrowedBooks[k] = NULL;
    }
}

// ---------- 访问器 ----------
string Student::getName()        { return name; }
string Student::getId()          { return id; }
string Student::getClassName()   { return className; }
int    Student::getBorrowedCount(){ return borrowedCount; }
int    Student::getMaxBorrow()    { return MAX_BORROW; }

bool Student::canBorrow() {
    return borrowedCount < MAX_BORROW;
}

// ---------- 借书（依赖倒置 + 多态的体现） ----------
// 形参是抽象基类指针：GeneralBook/Magazine/ElectronicResource 都能传进来。
// borrow() 是虚函数：传哪种资源，就执行哪种资源自己的借阅流程。
void Student::borrowBook(BookResource* book) {
    // 第 1 步：地址有效性
    if (book == NULL) {
        cout << "借阅失败：资源不存在（传入的是空地址）！" << endl;
        return;
    }
    // 第 2 步：学生状态
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

    // 4.1 把这份资源的地址存入学生的借阅区（组合，基类指针统一保存）
    borrowedBooks[borrowedCount] = book;
    // 4.2 记录本次借阅
    borrowRecords.push_back("《" + book->getTitle() +
                            "》  作者：" + book->getAuthor());
    // 4.3 学生状态更新
    borrowedCount++;

    cout << "借阅成功：" << name << "（学号 " << id << "）借了《"
         << book->getTitle() << "》，当前已借 "
         << borrowedCount << "/" << MAX_BORROW << " 份。" << endl;
}

// ---------- 输出学生信息 ----------
void Student::printInfo() {
    cout << "姓名: " << name << endl;
    cout << "学号: " << id << endl;
    cout << "班级: " << className << endl;
    cout << "当前借阅数: " << borrowedCount << " / " << MAX_BORROW << endl;
}

// ---------- 输出借阅记录 ----------
void Student::printBorrowRecords() {
    cout << "--- " << name << " 的借阅记录 ---" << endl;
    if (borrowedCount == 0) {
        cout << "暂无借阅记录。" << endl;
        return;
    }
    for (int i = 0; i < (int)borrowRecords.size(); i++) {
        cout << i + 1 << ". " << borrowRecords[i] << endl;
    }
}