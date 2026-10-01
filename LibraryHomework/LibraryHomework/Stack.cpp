#include "Stack.h"

// ==================== Stack 类的成员函数实现 ====================

// 构造函数：刚创建的书库一本书也没有
Stack::Stack()
{
    bookCount = 0;
}

// 把一本图书放入书库（参数传地址）
void Stack::addBook(Book* b)
{
    // 先判断地址是否有效
    if (b == NULL)
    {
        cout << "添加失败：图书地址无效！" << endl;
        return;
    }
    // 再判断书库是否已满
    if (bookCount >= MAX_BOOKS)
    {
        cout << "书库已满（上限 " << MAX_BOOKS << " 本），无法再添加！" << endl;
        return;
    }
    bookLib[bookCount] = b;   // 存入这本书的地址
    bookCount++;              // 书库数量加 1
    cout << "《" << b->getTitle() << "》已放入书库（当前共 "
         << bookCount << " 本）。" << endl;
}

// 显示书库中所有图书信息和状态
void Stack::showbook()
{
    cout << "========== 书库图书清单（共 " << bookCount << " 本） ==========" << endl;
    if (bookCount == 0)
    {
        cout << "书库暂时为空。" << endl;
        return;
    }
    for (int i = 0; i < bookCount; i++)
    {
        cout << "----- 第 " << i + 1 << " 本 -----" << endl;
        bookLib[i]->printInfo();   // 复用 Book 自己的输出函数（依赖 Book 的接口）
    }
}
