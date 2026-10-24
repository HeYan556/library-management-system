#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

// ==================== 账号类 User ====================
// 实验六新增：用于用户登录。
//   role = "admin"  ：管理员，可增删改资源、查看所有学生
//   role = "reader" ：读者，绑定一个学号，只能查询/借还自己的书
// 账号信息同样保存到文件（data/users.txt），由 LibraryRepository 统一读写。

class User {
private:
    string username;   // 用户名
    string password;   // 密码（教学示例，明文保存）
    string role;       // 角色：admin / reader
    string studentId;  // 读者绑定的学号；管理员为空

public:
    User();
    User(string u, string p, string r, string sid);

    // ---------- 访问器 ----------
    string getUsername()  const;
    string getRole()      const;
    string getStudentId() const;

    // ---------- 校验 ----------
    bool checkPassword(const string& pwd) const;
    bool isAdmin() const;

    // ---------- 序列化：一行格式 USR|用户名|密码|角色|学号 ----------
    void saveTo(ostream& os) const;
    void loadFrom(istream& is);

    void printInfo() const;
};

#endif // USER_H
