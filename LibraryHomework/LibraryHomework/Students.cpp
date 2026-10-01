#include "Students.h"

// ==================== Student 类的成员函数实现 ====================

Student::Student()
{
    name = "";
    id = "";
    className = "";
    borrowedCount = 0;   // 一开始没有借书
}

Student::Student(string n, string id, string className)
{
    this->name = n;
    this->id = id;
    this->className = className;
    borrowedCount = 0;   // 一开始没有借书
}

// ---------- 访问器 ----------
string Student::getName()
{
    return name;
}

string Student::getId()
{
    return id;
}

string Student::getClassName()
{
    return className;
}

int Student::getBorrowedCount()
{
    return borrowedCount;
}

int Student::getMaxBorrow()
{
    return MAX_BORROW;
}

// 学生状态判断：当前借的书还没到上限，就可以再借
bool Student::canBorrow()
{
    return borrowedCount < MAX_BORROW;
}

// ---------- 借书：体现与 Book 的依赖关系和组合关系 ----------
void Student::borrowBook(Book* book)
{
    // 第 1 步：参数是地址，先判断这个地址是否有效
    if (book == NULL)
    {
        cout << "借书失败：图书不存在（传入的是空地址）！" << endl;
        return;
    }

    // 第 2 步：判断学生状态——是否达到借书上限
    if (!canBorrow())
    {
        cout << "借书失败：学生 " << name << " 已借满 "
             << MAX_BORROW << " 本，不能继续借书！" << endl;
        return;
    }

    // 第 3 步：判断书的状态——是否可借
    if (!book->isAvailable())          // 依赖 Book 的公有接口
    {
        cout << "借书失败：《" << book->getTitle()
             << "》已被借出，暂不可借！" << endl;
        return;
    }

    // 第 4 步：两种状态都允许，允许借书
    // 4.1 组合关系：把这本书存入学生自己的借阅区（Book 是学生的组成部分）
    borrowedBooks[borrowedCount] = *book;
    // 4.2 记录本次借阅信息（vector 尾部追加一条记录）
    borrowRecords.push_back("《" + book->getTitle() +
                            "》  作者：" + book->getAuthor());
    // 4.3 更新学生状态
    borrowedCount++;
    // 4.4 更新这本书在系统中的状态（借出后不可再借）
    book->setAvailable(false);         // 依赖 Book 的公有接口

    cout << "借书成功：" << name << "（学号 " << id << "）借了《"
         << book->getTitle() << "》，当前已借 "
         << borrowedCount << "/" << MAX_BORROW << " 本。" << endl;
}

// ---------- 输出学生信息 ----------
void Student::printInfo()
{
    cout << "姓名: " << name << endl;
    cout << "学号: " << id << endl;
    cout << "班级: " << className << endl;
    cout << "当前借书数: " << borrowedCount << " / " << MAX_BORROW << endl;
}

// ---------- 输出借阅记录 ----------
void Student::printBorrowRecords()
{
    cout << "--- " << name << " 的借阅记录 ---" << endl;
    if (borrowedCount == 0)
    {
        cout << "暂无借阅记录。" << endl;
        return;
    }
    // vector 的 size() 返回当前元素个数，逐条输出借阅记录
    for (int i = 0; i < (int)borrowRecords.size(); i++)
    {
        cout << i + 1 << ". " << borrowRecords[i] << endl;
    }
}
