#ifndef STACK_H
#define STACK_H

#include "BookResource.h"

using namespace std;

// ==================== 书库类 Stack ====================
// 职责单一：只负责"管理一批资源"（存资源、显示所有资源的状态）。
// 不去管某一资源自己的属性，也不去管学生怎么借阅。
//
// 与 BookResource 的关系：
//   聚合：resLib 里存的是 BookResource 派生类对象的地址，
//   资源在书库外创建，生命周期不随书库。
//
// 本次升级：原 Book* → BookResource*，可统一收纳一般图书、杂志、电子资源。

class Stack {
private:
    static const int MAX_BOOKS = 50;        // 书库容量上限
    BookResource* resLib[MAX_BOOKS];        // 存放所有资源的地址
    int           bookCount;                // 当前资源数量

public:
    // ---------- 构造函数 ----------
    Stack();                                // 刚创建的书库是空的

    // ---------- 存资源 ----------
    void addBook(BookResource* r);          // 接受任何 BookResource 派生类

    // ---------- 显示 ----------
    void showbook();                         // ⚠️ 这次未引入 virtual，
                                            //    通过 BookResource* 调用
                                            //    printInfo() 时只执行基类版本
};

#endif // STACK_H