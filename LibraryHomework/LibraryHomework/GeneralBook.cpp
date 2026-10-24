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
string GeneralBook::getIsbn()    const { return isbn; }
int    GeneralBook::getEdition() const { return edition; }

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

// ---------- 序列化（实验六：文件输入输出流） ----------
// 一行格式：RES|GB|编号|共有字段…|ISBN|版次
const char* GeneralBook::typeTag() const { return "GB"; }

void GeneralBook::saveTo(ostream& os) const {
    os << "RES|GB|";
    saveCommon(os);                      // 基类共有字段（protected，子类可复用）
    os << '|' << isbn << '|' << edition;  // 本类特有字段
}

void GeneralBook::loadFrom(istream& is) {
    loadCommon(is);
    string f;
    getline(is, isbn, '|');
    getline(is, f);                       // 最后一个字段用不带分隔符的 getline
    edition = f.empty() ? 0 : stoi(f);
}