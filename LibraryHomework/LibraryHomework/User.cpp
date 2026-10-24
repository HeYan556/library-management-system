#include "User.h"

// ==================== User 类的成员函数实现 ====================

User::User() {}

User::User(string u, string p, string r, string sid)
    : username(u), password(p), role(r), studentId(sid) {}

// ---------- 访问器 ----------
string User::getUsername()  const { return username; }
string User::getRole()      const { return role; }
string User::getStudentId() const { return studentId; }

// ---------- 校验 ----------
bool User::checkPassword(const string& pwd) const { return password == pwd; }
bool User::isAdmin() const { return role == "admin"; }

// ---------- 序列化（实验六：输入输出流） ----------
void User::saveTo(ostream& os) const {
    os << "USR|" << username << '|' << password << '|' << role << '|' << studentId;
}

void User::loadFrom(istream& is) {
    string field;
    getline(is, username, '|');
    getline(is, password, '|');
    getline(is, role, '|');
    getline(is, studentId);
}

void User::printInfo() const {
    cout << "  用户名：" << username
         << "  角色：" << (isAdmin() ? "管理员" : "读者")
         << "  绑定学号：" << (studentId.empty() ? "（无）" : studentId) << endl;
}
