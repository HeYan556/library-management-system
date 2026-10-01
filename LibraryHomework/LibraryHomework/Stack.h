#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "Book.h"

using namespace std;

// ==================== 书库类 Stack ====================
// 职责单一：只负责"管理一批图书"（存书、显示所有书的状态），
// 不去管某一本书自己的属性，也不去管学生怎么借书。
//（原来书库是 Book 类里的静态成员，现在拆出来单独成一个类，
//  让 Book 只描述"一本书"，Stack 只描述"一个书库"。）
//
// 与 Book 类的关系：
//   聚合关系：bookLib 里存的是 Book 的地址，书在书库外面创建，
//   生命周期不跟着书库走，所以是"整体-部分"关系中较松的一种（空心菱形）。
class Stack {
private:
    static const int MAX_BOOKS = 50;   // 书库容量上限（图书数量少于 50 本）

    Book* bookLib[MAX_BOOKS];   // 【成员变量】书库：存放所有图书的地址
                                //（存地址而不是复制品，保证显示的状态始终是最新的）
    int   bookCount;            // 【成员变量】书库中当前图书数量

public:
    // ---------- 构造函数 ----------
    Stack();                    // 刚创建的书库是空的（bookCount = 0）

    // ---------- 存书 ----------
    void addBook(Book* b);      // 把一本图书放入书库（参数传地址）

    // ---------- 显示 ----------
    void showbook();            // 显示书库中所有图书信息和状态
};

#endif // STACK_H
