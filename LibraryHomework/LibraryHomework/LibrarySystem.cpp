#include <iomanip>
#include <limits>
#include <sstream>
#include "LibrarySystem.h"
#include "Algorithms.h"
#include "GeneralBook.h"
#include "Magazine.h"
#include "ElectronicResource.h"
#include "LibraryRepository.h"

// ==================== 输入辅助函数 ====================
// readLine：整行读取（可含空格与中文）
static string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

// readInt / readDouble：先读数字，再把回车从缓冲区里清掉。
// ★ 这一步很关键：cin >> 不会吃掉回车，后面的 getline 会读到空字符串。
static void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static int readInt(const string& prompt) {
    cout << prompt;
    int x = 0;
    while (!(cin >> x)) {                  // 输入了非数字时给出提示并重试
        cout << "请输入数字：";
        clearCin();
    }
    clearCin();                            // ★ 吃掉残留的回车（修复：必须清缓冲区）
    return x;
}

static double readDouble(const string& prompt) {
    cout << prompt;
    double x = 0.0;
    while (!(cin >> x)) {
        cout << "请输入数字：";
        clearCin();
    }
    clearCin();
    return x;
}

// ==================== 构造 ====================
LibrarySystem::LibrarySystem(Stack<BookResource*>& l, Stack<Student>& r, Stack<User>& u)
    : lib(l), roster(r), users(u),
      resPath("data/resources.txt"),
      stuPath("data/students.txt"),
      usrPath("data/users.txt") {}

// ---------- 类型标签转中文 ----------
string LibrarySystem::typeName(const char* tag) {
    string t(tag);
    if (t == "GB") return "一般图书";
    if (t == "MG") return "杂志";
    if (t == "ER") return "电子资源";
    return "未知";
}

// ---------- 新编号 ----------
int LibrarySystem::nextId() const {
    int maxId = 1000;
    for (Stack<BookResource*>::const_iterator it = lib.begin(); it != lib.end(); ++it) {
        if ((*it)->getId() > maxId) maxId = (*it)->getId();
    }
    return maxId + 1;
}

// ==================== 登录 ====================
User* LibrarySystem::login() {
    cout << "\n========== 图书管理系统 登录 ==========" << endl;
    for (int chance = 3; chance > 0; --chance) {
        string name = readLine("用户名：");
        string pwd  = readLine("密  码：");

        for (Stack<User>::iterator it = users.begin(); it != users.end(); ++it) {
            if (it->getUsername() == name && it->checkPassword(pwd)) {
                cout << "登录成功，欢迎 " << name << "！" << endl;
                return &(*it);
            }
        }
        cout << "用户名或密码错误，还剩 " << chance - 1 << " 次机会。" << endl;
    }
    return nullptr;
}

// ==================== 管理员菜单 ====================
void LibrarySystem::runAdmin(User& u) {
    cout << "\n欢迎管理员 " << u.getUsername() << "！" << endl;
    bool running = true;
    while (running) {
        cout << "\n===== 管理员菜单 =====" << endl
             << "  1 列出全部资源    2 添加资源    3 删除资源" << endl
             << "  4 按条件查询      5 查看学生    6 查看账号" << endl
             << "  7 立即保存        0 退出" << endl;
        int c = readInt("请选择：");
        switch (c) {
        case 1: listResources();                       break;
        case 2: addResource();                         break;
        case 3: removeResource();                      break;
        case 4: queryResource();                       break;
        case 5: listStudents();                        break;
        case 6: listUsers();                           break;
        case 7: saveAll();                             break;
        case 0:
            cout << "即将退出并保存数据……" << endl;
            running = false;
            break;
        default: cout << "无效选项，请重新选择。" << endl; break;
        }
    }
}

// ==================== 读者菜单 ====================
void LibrarySystem::runReader(User& u) {
    Student* me = findStudentById(u.getStudentId());
    if (me == nullptr) {
        cout << "[错误] 账号绑定的学号 " << u.getStudentId() << " 不存在，无法使用读者功能。" << endl;
        return;
    }
    cout << "\n欢迎读者 " << me->getName() << "！" << endl;
    bool running = true;
    while (running) {
        cout << "\n===== 读者菜单 =====" << endl
             << "  1 列出可借资源    2 查询资源    3 借阅" << endl
             << "  4 归还            5 我的信息    0 退出" << endl;
        int c = readInt("请选择：");
        switch (c) {
        case 1: listResources();      break;
        case 2: queryResource();      break;
        case 3: borrowFor(*me);       break;
        case 4: returnFor(*me);       break;
        case 5: showStudent(*me);     break;
        case 0:
            cout << "即将退出并保存数据……" << endl;
            running = false;
            break;
        default: cout << "无效选项，请重新选择。" << endl; break;
        }
    }
}

// ==================== 资源清单（iomanip 表格） ====================
void LibrarySystem::listResources() const {
    cout << "\n========== 资源清单（共 " << lib.size() << " 份） ==========" << endl;
    if (lib.empty()) {
        cout << "书库暂时为空。" << endl;
        return;
    }
    cout << left << setw(7) << "编号" << setw(26) << "名称"
         << setw(12) << "类型" << setw(10) << "定价" << setw(8) << "状态" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (Stack<BookResource*>::const_iterator it = lib.begin(); it != lib.end(); ++it) {
        BookResource* r = *it;
        cout << left << setw(7) << r->getId()
             << setw(26) << r->getTitle()
             << setw(12) << typeName(r->typeTag())
             << setw(10) << fixed << setprecision(2) << r->getPrice()
             << setw(8) << (r->isAvailable() ? "可借" : "已借出") << endl;
    }
    cout << right;   // 还原对齐方式
}

// ==================== 添加资源 ====================
void LibrarySystem::addResource() {
    cout << "\n--- 添加资源 ---" << endl;
    cout << "类型：1 一般图书   2 杂志   3 电子资源" << endl;
    int t = readInt("请选择类型：");

    string title = readLine("名称：");
    if (title.empty()) {
        cout << "[错误] 名称不能为空，已取消添加。" << endl;
        return;
    }
    string author = readLine("责任人：");
    int year  = readInt("出版年份：");
    string pub = readLine("出版社/发布方：");
    int pages = readInt("页数（电子资源填 0）：");
    double price = readDouble("定价：");

    BookResource* r = nullptr;
    if (t == 1) {
        string isbn = readLine("ISBN：");
        int ed = readInt("版次：");
        r = new GeneralBook(title, author, year, pub, pages, isbn, ed);
    } else if (t == 2) {
        int issue = readInt("期号：");
        string period = readLine("出版周期（如 月刊）：");
        string editor = readLine("主编：");
        r = new Magazine(title, author, year, pub, pages, issue, period, editor);
    } else if (t == 3) {
        string fmt = readLine("格式（PDF/EPUB/MOBI）：");
        string url = readLine("访问链接：");
        double size = readDouble("文件大小(MB)：");
        r = new ElectronicResource(title, author, year, pub, pages, fmt, url, size);
    } else {
        cout << "类型无效，已取消。" << endl;
        return;
    }

    r->setPrice(price);
    r->setId(nextId());
    lib.push(r);
    cout << "添加成功，新资源编号为 " << r->getId() << "。" << endl;
}

// ==================== 删除资源 ====================
void LibrarySystem::removeResource() {
    int id = readInt("请输入要删除的资源编号：");
    for (size_t i = 0; i < lib.size(); ++i) {
        if (lib[i]->getId() == id) {
            cout << "已删除：" << lib[i]->getTitle() << endl;
            delete lib[i];              // ★ 虚析构：通过基类指针正确销毁派生对象
            lib.erase(i);               // vector 的 erase：后续元素整体前移
            return;
        }
    }
    cout << "未找到编号为 " << id << " 的资源。" << endl;
}

// ==================== 查询（复用实验五泛型算法） ====================
void LibrarySystem::queryResource() const {
    string key = readLine("请输入名称关键字（直接回车表示查全部可借）：");
    vector<BookResource*> result =
        filter(lib.begin(), lib.end(), [&key](BookResource* r) {
            if (key.empty()) return r->isAvailable();
            return r->getTitle().find(key) != string::npos;
        });
    cout << "查询结果 " << result.size() << " 份：" << endl;
    printAll(result.begin(), result.end());
}

// ==================== 学生 / 账号 ====================
void LibrarySystem::listStudents() const {
    cout << "\n========== 学生名册（共 " << roster.size() << " 人） ==========" << endl;
    for (Stack<Student>::const_iterator it = roster.begin(); it != roster.end(); ++it) {
        it->printInfo();
        cout << "  当前借阅：" << it->getBorrowedCount() << " 份" << endl;
    }
}

void LibrarySystem::listUsers() const {
    cout << "\n========== 账号列表（共 " << users.size() << " 个） ==========" << endl;
    for (Stack<User>::const_iterator it = users.begin(); it != users.end(); ++it) {
        it->printInfo();
    }
}

void LibrarySystem::showStudent(const Student& s) const {
    cout << endl;
    s.printInfo();
    cout << endl;
    s.printBorrowRecords();
}

// ==================== 查找 ====================
BookResource* LibrarySystem::findResourceById(int id) {
    auto it = findIf(lib.begin(), lib.end(),
                     [id](BookResource* r) { return r->getId() == id; });
    return (it == lib.end()) ? nullptr : *it;
}

Student* LibrarySystem::findStudentById(const string& sid) {
    for (Stack<Student>::iterator it = roster.begin(); it != roster.end(); ++it) {
        if (it->getId() == sid) return &(*it);
    }
    return nullptr;
}

// ==================== 借阅 / 归还 ====================
void LibrarySystem::borrowFor(Student& s) {
    listResources();
    int id = readInt("请输入要借阅的资源编号：");
    BookResource* r = findResourceById(id);
    if (r == nullptr) {
        cout << "未找到编号为 " << id << " 的资源。" << endl;
        return;
    }
    s.borrowBook(r);                 // ★ 多态：扫码 / 登记 / 开放访问权限自动分流
}

void LibrarySystem::returnFor(Student& s) {
    int id = readInt("请输入要归还的资源编号：");
    BookResource* r = findResourceById(id);
    if (r == nullptr) {
        cout << "未找到编号为 " << id << " 的资源。" << endl;
        return;
    }
    s.returnBook(r);
}

// ==================== 落盘 ====================
void LibrarySystem::saveAll() const {
    LibraryRepository::saveResources(resPath, lib);
    LibraryRepository::saveStudents(stuPath, roster);
    LibraryRepository::saveUsers(usrPath, users);
}
