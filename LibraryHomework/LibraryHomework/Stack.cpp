#include "Stack.h"

// ==================== Stack 类的成员函数实现 ====================

// 构造函数：书库初始为空
Stack::Stack() {
    bookCount = 0;
}

// 把一份资源放入书库
void Stack::addBook(BookResource* r) {
    if (r == NULL) {
        cout << "添加失败：资源地址无效！" << endl;
        return;
    }
    if (bookCount >= MAX_BOOKS) {
        cout << "书库已满（上限 " << MAX_BOOKS
             << " 份），无法再添加！" << endl;
        return;
    }
    resLib[bookCount] = r;
    bookCount++;
    cout << "《" << r->getTitle() << "》已放入书库（当前共 "
         << bookCount << " 份）。" << endl;
}

// 显示书库中所有资源
void Stack::showbook() {
    cout << "========== 书库资源清单（共 " << bookCount
         << " 份） ==========" << endl;
    if (bookCount == 0) {
        cout << "书库暂时为空。" << endl;
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        cout << "----- 第 " << i + 1 << " 份 -----" << endl;
        // ⚠️ 由于未引入 virtual，此处只调用 BookResource::printInfo()，
        //    只能看到"共有字段"，看不到子类特有字段。
        resLib[i]->printInfo();
    }
}