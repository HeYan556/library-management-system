#ifndef MAGAZINE_H
#define MAGAZINE_H

#include <string>
#include "BookResource.h"

using namespace std;

// ==================== 杂志子类 Magazine ====================
// 角色：纸质杂志（区别于一般图书在于按期出版、有主编）。
// 特点：借还流程与一般图书不同——通过"登记期号"完成（也是扫码的同类形式）。

class Magazine : public BookResource {
private:
    // ---- 杂志特有字段（不进基类）----
    int    issueNo;       // 期号
    string period;        // 出版周期：月刊 / 双月刊 / 季刊 等
    string chiefEditor;   // 主编

public:
    // ---------- 构造函数 ----------
    Magazine();
    Magazine(string t, string a, int y, string pub, int pages,
             int issue, string per, string editor);

    // ---------- 修改器 ----------
    void setIssueNo(int i);
    void setPeriod(const string& p);
    void setChiefEditor(const string& c);

    // ---------- 访问器 ----------
    int    getIssueNo();
    string getPeriod();
    string getChiefEditor();

    // ---------- 重写基类纯虚函数（override 显式声明） ----------
    void printInfo() override;
    void borrow() override;
    void returnBook() override;
};

#endif // MAGAZINE_H