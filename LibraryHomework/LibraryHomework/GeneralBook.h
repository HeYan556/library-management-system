#ifndef GENERALBOOK_H
#define GENERALBOOK_H

#include <string>
#include "BookResource.h"

using namespace std;

// ==================== 一般图书子类 GeneralBook ====================
// 角色：纸质一般图书，继承自 BookResource。
// 特点：借还书需要"扫码"（模拟扫码流程），这是与其他子类的关键区别。
//
// 与 BookResource 的关系：
//   is-a：一般图书"是"图书资源的一种。
//   字段复用：title/author/year/publisher/pages/price/available 均来自基类，
//             本类不再重复定义，只新增一般图书特有字段。

class GeneralBook : public BookResource {
private:
    // ---- 一般图书特有字段（不进基类）----
    string isbn;    // ISBN 号
    int    edition; // 版次

public:
    // ---------- 构造函数 ----------
    GeneralBook();
    GeneralBook(string t, string a, int y, string pub, int pages,
                string isbnVal, int ed);

    // ---------- 修改器 ----------
    void setIsbn(const string& i);
    void setEdition(int e);

    // ---------- 访问器（const：便于 const 对象与泛型谓词调用） ----------
    string getIsbn()    const;
    int    getEdition() const;

    // ---------- 重写基类纯虚函数（override 显式声明） ----------
    void printInfo() override;
    void borrow() override;
    void returnBook() override;

    // ---------- 序列化（实验六）：标签 GB，特有字段 ISBN / 版次 ----------
    const char* typeTag() const override;
    void saveTo(ostream& os) const override;
    void loadFrom(istream& is) override;
};

#endif // GENERALBOOK_H