#ifndef BOOKRESOURCE_H
#define BOOKRESOURCE_H

#include <iostream>
#include <string>

using namespace std;

// ==================== 图书资源抽象基类 BookResource ====================
// 实验四升级：引入多态与虚函数，遵守依赖倒置原则（DIP）。
//
//   依赖倒置的体现：
//     高层模块（Stack、Student）只依赖本抽象类，
//     不依赖 GeneralBook / Magazine / ElectronicResource 等具体子类。
//     具体子类可以随时增删，高层模块一行不用改。
//
//   多态要点：
//     1) 纯虚函数使本类成为抽象类，不能被实例化（"泛泛的资源"不该存在）。
//     2) 虚析构保证通过基类指针销毁派生类对象时行为正确。
//     3) printCommonInfo() 是普通函数，供各子类的 printInfo() 复用共有字段输出，
//        避免纯虚函数无法提供默认实现的问题。

class BookResource {
private:
    // ---- 共有字段（所有资源类型都具备）----
    int    id;         // 资源编号（实验六：持久化与借阅都靠它定位资源）
    string title;      // 名称（书名/刊名/资源名）
    string author;     // 责任人（作者/主编/出品方）
    int    year;       // 出版年份
    string publisher;  // 出版社 / 发布方
    int    pages;      // 页数（电子资源可填 0）
    double price;      // 定价
    bool   available;  // 是否可借

public:
    // ---------- 构造函数 ----------
    BookResource();
    BookResource(string t, string a, int y, string pub, int pages);

    // ---------- 虚析构函数（多态销毁的安全保障） ----------
    virtual ~BookResource();

    // ---------- 修改器（setters） ----------
    void setTitle(const string& t);
    void setAuthor(const string& a);
    void setYear(int y);
    void setPublisher(const string& p);
    void setPages(int p);
    void setPrice(double p);
    void setAvailable(bool a);

    // ---------- 访问器（getters） ----------
    // 实验五：统一加 const —— 不修改对象状态的查询操作都应是 const，
    // 这样 const BookResource* 也能调用（泛型算法的谓词中常用）。
    string getTitle()     const;
    string getAuthor()    const;
    int    getYear()      const;
    string getPublisher() const;
    int    getPages()     const;
    double getPrice()     const;
    bool   isAvailable()  const;

    // ---------- 编号（实验六新增） ----------
    int  getId() const;
    void setId(int i);

    // ---------- 序列化接口（实验六：输入输出流） ----------
    // typeTag   ：标明具体子类，写入文件与读回时靠它判断该 new 哪个子类
    // saveTo    ：把本对象写成一行文本
    // loadFrom  ：从一行文本恢复本对象
    //
    // 说明：operator<< / operator>> 无法声明为虚函数（左操作数是流对象），
    // 因此采用"非虚接口 + 虚实现"：运算符内部调用虚函数完成派发。
    virtual const char* typeTag() const = 0;
    virtual void saveTo(ostream& os) const = 0;
    virtual void loadFrom(istream& is) = 0;

    friend ostream& operator<<(ostream& os, const BookResource& r);
    friend istream& operator>>(istream& is, BookResource& r);

    // ---------- 共有字段输出（普通函数，供子类复用） ----------
    void printCommonInfo() const;

    // ---------- 纯虚函数：接口契约，强制各子类实现 ----------
    virtual void printInfo() = 0;     // 完整信息输出（含子类特有字段）
    virtual void borrow() = 0;        // 借（各子类流程不同：扫码/登记/直接访问）
    virtual void returnBook() = 0;    // 还（各子类流程不同）

protected:
    // 供三个子类的 saveTo / loadFrom 复用，避免把共有字段抄三遍
    void saveCommon(ostream& os) const;
    void loadCommon(istream& is);
};

#endif // BOOKRESOURCE_H