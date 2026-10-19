#include "GeneralBook.h"

// ==================== GeneralBook 类的成员函数实现 ====================

// ---------- 构造函数 ----------
GeneralBook::GeneralBook() : BookResource() {
    isbn = "";
    edition = 0;
}

GeneralBook::GeneralBook(string t, string a, int y, string pub,
                         int pages, string isbnVal, int ed)
    : BookResource(t, a, y, pub, pages) {
    isbn = isbnVal;
    edition = ed;
}

// ---------- 修改器 ----------
void GeneralBook::setIsbn(const string& i){ isbn = i; }
void GeneralBook::setEdition(int e)       { edition = e; }

// ---------- 访问器 ----------
string GeneralBook::getIsbn()    { return isbn; }
int    GeneralBook::getEdition() { return edition; }

// ---------- 输出信息（重写基类纯虚函数） ----------
void GeneralBook::printInfo() {
    cout << "===== 一般图书 =====" << endl;
    // 先调基类的共有字段输出，再补本类特有字段
    printCommonInfo();
    // 再补上本类特有字段
    cout << "  ISBN: "  << isbn    << endl;
    cout << "  版次: " << edition << endl;
}

// ---------- 一般图书特有的借书流程：模拟扫码 ----------
void GeneralBook::borrow() {
    if (!isAvailable()) {
        cout << "  借书失败：《" << getTitle()
             << "》已被借出，暂不可借！" << endl;
        return;
    }
    cout << "  [纸质书] 扫码借出：扫描 ISBN " << isbn
         << "  ……  借出成功！" << endl;
    setAvailable(false);
}

// ---------- 一般图书特有的还书流程：模拟扫码 ----------
void GeneralBook::returnBook() {
    if (isAvailable()) {
        cout << "  还书失败：《" << getTitle()
             << "》本就在馆内，无需归还！" << endl;
        return;
    }
    cout << "  [纸质书] 扫码归还：扫描 ISBN " << isbn
         << "  ……  归还成功！" << endl;
    setAvailable(true);
}