#include <fstream>
#include <sstream>
#include "LibraryRepository.h"
#include "GeneralBook.h"
#include "Magazine.h"
#include "ElectronicResource.h"

// ==================== LibraryRepository 实现 ====================

// ---------- 工厂函数：按类型标签 new 出对应的子类 ----------
// 这是全工程唯一"认识所有子类"的地方，其余模块只认 BookResource*（依赖倒置）。
static BookResource* createByTag(const string& tag) {
    if (tag == "GB") return new GeneralBook();
    if (tag == "MG") return new Magazine();
    if (tag == "ER") return new ElectronicResource();
    return nullptr;                       // 未知标签返回空，调用方跳过该行
}

// ---------- 资源：读入 ----------
bool LibraryRepository::loadResources(const string& path, Stack<BookResource*>& lib) {
    ifstream in(path);
    if (!in.is_open()) {                                  // 必须检查是否打开成功
        cout << "[提示] 无法打开 " << path
             << "（可能是首次运行），本次使用空书库。" << endl;
        return false;
    }
    string line;
    int count = 0;
    while (getline(in, line)) {           // 用 getline 做循环条件，不要用 !in.eof()
        if (line.empty() || line[0] == ';') continue;      // 跳过空行与注释行
        istringstream iss(line);          // 字符串流逐字段拆分
        string head, tag;
        getline(iss, head, '|');
        getline(iss, tag, '|');
        if (head != "RES") continue;

        BookResource* r = createByTag(tag);
        if (r == nullptr) {
            cout << "[警告] 未知的资源类型标签：" << tag << "，跳过该行。" << endl;
            continue;
        }
        r->loadFrom(iss);                 // ★ 虚调用：由子类读自己的字段
        lib.push(r);
        count++;
    }
    in.close();
    cout << "已从 " << path << " 读入 " << count << " 份资源。" << endl;
    return true;
}

// ---------- 资源：写出 ----------
bool LibraryRepository::saveResources(const string& path, const Stack<BookResource*>& lib) {
    ofstream out(path);
    if (!out.is_open()) {
        cout << "[错误] 无法写入 " << path << "，保存失败！" << endl;
        return false;
    }
    out << "; 图书资源数据 v1" << endl;
    out << "; 字段：RES|类型标签|编号|名称|责任人|年份|出版社|页数|定价|是否可借(1/0)|子类特有字段…" << endl;
    for (Stack<BookResource*>::const_iterator it = lib.begin(); it != lib.end(); ++it) {
        out << **it << endl;              // ★ operator<< → 内部虚派发 saveTo()
    }
    out.close();
    cout << "已保存 " << lib.size() << " 份资源到 " << path << endl;
    return true;
}

// ---------- 学生：读入（必须在资源之后调用） ----------
bool LibraryRepository::loadStudents(const string& path, Stack<Student>& roster,
                                     const Stack<BookResource*>& lib) {
    ifstream in(path);
    if (!in.is_open()) {
        cout << "[提示] 无法打开 " << path
             << "（可能是首次运行），本次没有学生数据。" << endl;
        return false;
    }
    string line;
    int count = 0;
    while (getline(in, line)) {
        if (line.empty() || line[0] == ';') continue;
        istringstream iss(line);
        string head;
        getline(iss, head, '|');
        if (head != "STU") continue;
        Student s;
        s.loadFrom(iss, lib);             // 内部按编号反查资源指针
        roster.push(s);
        count++;
    }
    in.close();
    cout << "已从 " << path << " 读入 " << count << " 名学生。" << endl;
    return true;
}

// ---------- 学生：写出 ----------
bool LibraryRepository::saveStudents(const string& path, const Stack<Student>& roster) {
    ofstream out(path);
    if (!out.is_open()) {
        cout << "[错误] 无法写入 " << path << "，保存失败！" << endl;
        return false;
    }
    out << "; 学生数据 v1" << endl;
    out << "; 字段：STU|姓名|学号|班级|当前借阅中的资源编号(多个用 ; 分隔)" << endl;
    for (Stack<Student>::const_iterator it = roster.begin(); it != roster.end(); ++it) {
        it->saveTo(out);
        out << endl;
    }
    out.close();
    cout << "已保存 " << roster.size() << " 名学生到 " << path << endl;
    return true;
}

// ---------- 账号：读入 ----------
bool LibraryRepository::loadUsers(const string& path, Stack<User>& users) {
    ifstream in(path);
    if (!in.is_open()) {
        cout << "[提示] 无法打开 " << path << "（可能是首次运行），暂无可用账号。" << endl;
        return false;
    }
    string line;
    int count = 0;
    while (getline(in, line)) {
        if (line.empty() || line[0] == ';') continue;
        istringstream iss(line);
        string head;
        getline(iss, head, '|');
        if (head != "USR") continue;
        User u;
        u.loadFrom(iss);
        users.push(u);
        count++;
    }
    in.close();
    cout << "已从 " << path << " 读入 " << count << " 个账号。" << endl;
    return true;
}

// ---------- 账号：写出 ----------
bool LibraryRepository::saveUsers(const string& path, const Stack<User>& users) {
    ofstream out(path);
    if (!out.is_open()) {
        cout << "[错误] 无法写入 " << path << "，保存失败！" << endl;
        return false;
    }
    out << "; 账号数据 v1" << endl;
    out << "; 字段：USR|用户名|密码|角色(admin/reader)|绑定的学号(管理员留空)" << endl;
    for (Stack<User>::const_iterator it = users.begin(); it != users.end(); ++it) {
        it->saveTo(out);
        out << endl;
    }
    out.close();
    cout << "已保存 " << users.size() << " 个账号到 " << path << endl;
    return true;
}
