#ifndef ELECTRONICRESOURCE_H
#define ELECTRONICRESOURCE_H

#include <string>
#include "BookResource.h"

using namespace std;

// ==================== 电子资源子类 ElectronicResource ====================
// 角色：可在线访问的电子资源（PDF / EPUB 等）。
// 特点：借还不扫码，直接通过 URL 访问——这是与纸质子类最显著的区别。

class ElectronicResource : public BookResource {
private:
    // ---- 电子资源特有字段（不进基类）----
    string format;    // 文件格式：PDF / EPUB / MOBI 等
    string url;       // 访问链接
    double fileSize;  // 文件大小（MB）

public:
    // ---------- 构造函数 ----------
    ElectronicResource();
    ElectronicResource(string t, string a, int y, string pub, int pages,
                       string fmt, string link, double size);

    // ---------- 修改器 ----------
    void setFormat(const string& f);
    void setUrl(const string& u);
    void setFileSize(double s);

    // ---------- 访问器（const：便于 const 对象与泛型谓词调用） ----------
    string getFormat()   const;
    string getUrl()      const;
    double getFileSize() const;

    // ---------- 重写基类纯虚函数（override 显式声明） ----------
    void printInfo() override;
    void borrow() override;
    void returnBook() override;

    // ---------- 序列化（实验六）：标签 ER，特有字段 格式 / 链接 / 大小 ----------
    const char* typeTag() const override;
    void saveTo(ostream& os) const override;
    void loadFrom(istream& is) override;
};

#endif // ELECTRONICRESOURCE_H