#include "Magazine.h"

// ==================== Magazine 类的成员函数实现 ====================

// ---------- 构造函数 ----------
Magazine::Magazine() : BookResource() {
    issueNo = 0;
    period = "";
    chiefEditor = "";
}

Magazine::Magazine(string t, string a, int y, string pub,
                   int pages, int issue, string per, string editor)
    : BookResource(t, a, y, pub, pages) {
    issueNo = issue;
    period = per;
    chiefEditor = editor;
}

// ---------- 修改器 ----------
void Magazine::setIssueNo(int i)             { issueNo = i; }
void Magazine::setPeriod(const string& p)   { period = p; }
void Magazine::setChiefEditor(const string& c){ chiefEditor = c; }

// ---------- 访问器 ----------
int    Magazine::getIssueNo()     const { return issueNo; }
string Magazine::getPeriod()      const { return period; }
string Magazine::getChiefEditor() const { return chiefEditor; }

// ---------- 输出信息（重写基类纯虚函数） ----------
void Magazine::printInfo() {
    cout << "===== 杂志 =====" << endl;
    printCommonInfo();
    cout << "  期号: "  << issueNo     << endl;
    cout << "  周期: "  << period      << endl;
    cout << "  主编: " << chiefEditor << endl;
}

// ---------- 杂志特有借书：登记期号 ----------
void Magazine::borrow() {
    if (!isAvailable()) {
        cout << "  借阅失败：《" << getTitle() << "》第 "
             << issueNo << " 期已被借出！" << endl;
        return;
    }
    cout << "  [杂志] 登记借阅：第 " << issueNo << " 期（"
         << period << "） ……  借阅成功！" << endl;
    setAvailable(false);
}

// ---------- 杂志特有还书：登记归还 ----------
void Magazine::returnBook() {
    if (isAvailable()) {
        cout << "  归还失败：《" << getTitle() << "》第 "
             << issueNo << " 期本就在馆内！" << endl;
        return;
    }
    cout << "  [杂志] 登记归还：第 " << issueNo
         << " 期 ……  归还成功！" << endl;
    setAvailable(true);
}

// ---------- 序列化（实验六：文件输入输出流） ----------
// 一行格式：RES|MG|编号|共有字段…|期号|周期|主编
const char* Magazine::typeTag() const { return "MG"; }

void Magazine::saveTo(ostream& os) const {
    os << "RES|MG|";
    saveCommon(os);
    os << '|' << issueNo << '|' << period << '|' << chiefEditor;
}

void Magazine::loadFrom(istream& is) {
    loadCommon(is);
    string f;
    getline(is, f, '|');  issueNo = f.empty() ? 0 : stoi(f);
    getline(is, period, '|');
    getline(is, chiefEditor);
}