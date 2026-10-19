#include "ElectronicResource.h"

// ==================== ElectronicResource 类的成员函数实现 ====================

// ---------- 构造函数 ----------
ElectronicResource::ElectronicResource() : BookResource() {
    format = "";
    url = "";
    fileSize = 0.0;
}

ElectronicResource::ElectronicResource(string t, string a, int y,
                                       string pub, int pages,
                                       string fmt, string link,
                                       double size)
    : BookResource(t, a, y, pub, pages) {
    format = fmt;
    url = link;
    fileSize = size;
}

// ---------- 修改器 ----------
void ElectronicResource::setFormat(const string& f){ format = f; }
void ElectronicResource::setUrl(const string& u)  { url = u; }
void ElectronicResource::setFileSize(double s)    { fileSize = s; }

// ---------- 访问器 ----------
string ElectronicResource::getFormat()  { return format; }
string ElectronicResource::getUrl()     { return url; }
double ElectronicResource::getFileSize(){ return fileSize; }

// ---------- 输出信息（重写基类纯虚函数） ----------
void ElectronicResource::printInfo() {
    cout << "===== 电子资源 =====" << endl;
    printCommonInfo();
    cout << "  格式: " << format   << endl;
    cout << "  链接: " << url      << endl;
    cout << "  大小: " << fileSize << " MB" << endl;
}

// ---------- 电子资源特有借阅：直接访问（不扫码） ----------
void ElectronicResource::borrow() {
    if (!isAvailable()) {
        cout << "  借阅失败：《" << getTitle()
             << "》电子资源已被借出（访问权限已关闭）！" << endl;
        return;
    }
    cout << "  [电子资源] 直接借阅：开放访问权限 " << url
         << " ……  借阅成功！" << endl;
    setAvailable(false);
}

// ---------- 电子资源特有归还：撤销访问权限 ----------
void ElectronicResource::returnBook() {
    if (isAvailable()) {
        cout << "  归还失败：《" << getTitle()
             << "》电子资源本就可访问，无需归还！" << endl;
        return;
    }
    cout << "  [电子资源] 直接归还：撤销访问权限 " << url
         << " ……  归还成功！" << endl;
    setAvailable(true);
}