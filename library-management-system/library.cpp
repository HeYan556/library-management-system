// 图书管理系统（仅运用 C++ 类与对象的知识）
// 涉及知识点：类的定义、封装（私有成员 + 公有接口）、构造函数、
//              成员函数、对象数组、this 指针、常成员函数

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_BOOKS = 100;   // 最多图书数
const int MAX_READERS = 50;  // 最多读者数
const int NAME_LEN = 40;     // 名称长度上限

// ============ 图书类 ============
class Book {
private:
    int id;                  // 图书编号
    char title[NAME_LEN];    // 书名
    char author[NAME_LEN];   // 作者
    bool borrowed;           // 是否被借出
public:
    Book() {
        id = 0;
        title[0] = '\0';
        author[0] = '\0';
        borrowed = false;
    }
    Book(int id_, const char* title_, const char* author_) {
        this->id = id_;
        strcpy(this->title, title_);
        strcpy(this->author, author_);
        this->borrowed = false;
    }
    int getId() const { return id; }
    const char* getTitle() const { return title; }
    const char* getAuthor() const { return author; }
    bool isBorrowed() const { return borrowed; }
    void setBorrowed(bool b) { borrowed = b; }
    void display() const {
        cout << id << "\t" << title << "\t" << author << "\t"
             << (borrowed ? "已借出" : "可借阅") << endl;
    }
};

// ============ 读者类 ============
class Reader {
private:
    int id;                  // 读者编号
    char name[NAME_LEN];     // 读者姓名
    int borrowedBookId;      // 当前借的图书编号（-1 表示没借书）
public:
    Reader() {
        id = 0;
        name[0] = '\0';
        borrowedBookId = -1;
    }
    Reader(int id_, const char* name_) {
        this->id = id_;
        strcpy(this->name, name_);
        this->borrowedBookId = -1;
    }
    int getId() const { return id; }
    const char* getName() const { return name; }
    int getBorrowedBookId() const { return borrowedBookId; }
    void setBorrowedBookId(int bookId) { borrowedBookId = bookId; }
    void display() const {
        cout << id << "\t" << name << "\t";
        if (borrowedBookId == -1)
            cout << "未借书" << endl;
        else
            cout << "借阅图书编号: " << borrowedBookId << endl;
    }
};

// ============ 图书馆类（管理图书和读者） ============
class Library {
private:
    Book books[MAX_BOOKS];       // 图书对象数组
    int bookCount;               // 当前图书数量
    Reader readers[MAX_READERS]; // 读者对象数组
    int readerCount;             // 当前读者数量
    int nextBookId;              // 下一个图书编号
    int nextReaderId;            // 下一个读者编号

    // 按编号查找图书，返回数组下标，找不到返回 -1
    int findBookIndex(int bookId) const {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getId() == bookId)
                return i;
        }
        return -1;
    }
    // 按编号查找读者，返回数组下标，找不到返回 -1
    int findReaderIndex(int readerId) const {
        for (int i = 0; i < readerCount; i++) {
            if (readers[i].getId() == readerId)
                return i;
        }
        return -1;
    }
public:
    Library() {
        bookCount = 0;
        readerCount = 0;
        nextBookId = 1;
        nextReaderId = 1;
    }

    // ---------- 图书管理 ----------
    void addBook(const char* title, const char* author) {
        if (bookCount >= MAX_BOOKS) {
            cout << "图书已达上限，无法添加！" << endl;
            return;
        }
        books[bookCount] = Book(nextBookId, title, author);
        bookCount++;
        cout << "添加成功，图书编号为 " << nextBookId << endl;
        nextBookId++;
    }
    void showAllBooks() const {
        if (bookCount == 0) {
            cout << "暂无图书。" << endl;
            return;
        }
        cout << "编号\t书名\t作者\t状态" << endl;
        for (int i = 0; i < bookCount; i++)
            books[i].display();
    }
    void searchBook(const char* title) const {
        bool found = false;
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getTitle(), title) == 0) {
                books[i].display();
                found = true;
            }
        }
        if (!found)
            cout << "未找到该书。" << endl;
    }
    void removeBook(int bookId) {
        int idx = findBookIndex(bookId);
        if (idx == -1) {
            cout << "图书不存在。" << endl;
            return;
        }
        if (books[idx].isBorrowed()) {
            cout << "该书已被借出，无法删除。" << endl;
            return;
        }
        // 用后面的图书依次前移覆盖
        for (int i = idx; i < bookCount - 1; i++)
            books[i] = books[i + 1];
        bookCount--;
        cout << "删除成功。" << endl;
    }

    // ---------- 读者管理 ----------
    void addReader(const char* name) {
        if (readerCount >= MAX_READERS) {
            cout << "读者已达上限，无法添加！" << endl;
            return;
        }
        readers[readerCount] = Reader(nextReaderId, name);
        readerCount++;
        cout << "注册成功，读者编号为 " << nextReaderId << endl;
        nextReaderId++;
    }
    void showAllReaders() const {
        if (readerCount == 0) {
            cout << "暂无读者。" << endl;
            return;
        }
        cout << "编号\t姓名\t借阅情况" << endl;
        for (int i = 0; i < readerCount; i++)
            readers[i].display();
    }

    // ---------- 借阅 / 归还 ----------
    void borrowBook(int readerId, int bookId) {
        int ri = findReaderIndex(readerId);
        if (ri == -1) {
            cout << "读者不存在。" << endl;
            return;
        }
        int bi = findBookIndex(bookId);
        if (bi == -1) {
            cout << "图书不存在。" << endl;
            return;
        }
        if (readers[ri].getBorrowedBookId() != -1) {
            cout << "该读者已借过书，请先归还。" << endl;
            return;
        }
        if (books[bi].isBorrowed()) {
            cout << "该书已被借出。" << endl;
            return;
        }
        books[bi].setBorrowed(true);
        readers[ri].setBorrowedBookId(bookId);
        cout << "借书成功：" << readers[ri].getName()
             << " 借了《" << books[bi].getTitle() << "》" << endl;
    }
    void returnBook(int readerId) {
        int ri = findReaderIndex(readerId);
        if (ri == -1) {
            cout << "读者不存在。" << endl;
            return;
        }
        int bookId = readers[ri].getBorrowedBookId();
        if (bookId == -1) {
            cout << "该读者没有借书。" << endl;
            return;
        }
        int bi = findBookIndex(bookId);
        if (bi != -1)
            books[bi].setBorrowed(false);
        readers[ri].setBorrowedBookId(-1);
        cout << "还书成功。" << endl;
    }
};

// ============ 主函数：菜单交互 ============
int main() {
    Library lib;
    int choice;
    char title[NAME_LEN];
    char author[NAME_LEN];
    char name[NAME_LEN];
    int bookId, readerId;

    while (true) {
        cout << "\n===== 图书管理系统 =====" << endl;
        cout << "1. 添加图书" << endl;
        cout << "2. 显示所有图书" << endl;
        cout << "3. 按书名查找图书" << endl;
        cout << "4. 删除图书" << endl;
        cout << "5. 注册读者" << endl;
        cout << "6. 显示所有读者" << endl;
        cout << "7. 借书" << endl;
        cout << "8. 还书" << endl;
        cout << "0. 退出系统" << endl;
        cout << "请选择: ";
        cin >> choice;

        if (cin.fail()) {          // 输入非数字时清空缓冲区
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "输入无效，请重新选择。" << endl;
            continue;
        }
        cin.ignore(10000, '\n');   // 清掉行尾换行符，便于读字符串

        switch (choice) {
        case 1:
            cout << "请输入书名: ";
            cin.getline(title, NAME_LEN);
            cout << "请输入作者: ";
            cin.getline(author, NAME_LEN);
            lib.addBook(title, author);
            break;
        case 2:
            lib.showAllBooks();
            break;
        case 3:
            cout << "请输入要查找的书名: ";
            cin.getline(title, NAME_LEN);
            lib.searchBook(title);
            break;
        case 4:
            cout << "请输入要删除的图书编号: ";
            cin >> bookId;
            cin.ignore(10000, '\n');
            lib.removeBook(bookId);
            break;
        case 5:
            cout << "请输入读者姓名: ";
            cin.getline(name, NAME_LEN);
            lib.addReader(name);
            break;
        case 6:
            lib.showAllReaders();
            break;
        case 7:
            cout << "请输入读者编号: ";
            cin >> readerId;
            cout << "请输入图书编号: ";
            cin >> bookId;
            cin.ignore(10000, '\n');
            lib.borrowBook(readerId, bookId);
            break;
        case 8:
            cout << "请输入读者编号: ";
            cin >> readerId;
            cin.ignore(10000, '\n');
            lib.returnBook(readerId);
            break;
        case 0:
            cout << "感谢使用，再见！" << endl;
            return 0;
        default:
            cout << "无效选项，请重新选择。" << endl;
        }
    }
    return 0;
}
