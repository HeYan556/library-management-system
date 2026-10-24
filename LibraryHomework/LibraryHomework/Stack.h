#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <cstddef>
#include "BookResource.h"

using namespace std;

// ==================== 类模板 Stack<T> ====================
// 实验五升级：从"只能装 BookResource* 的书库类"升级为"装什么都行的类模板"。
// 底层容器由定长数组 BookResource* resLib[50] 换成 std::vector<T>，
// 容量不再受 MAX_BOOKS 限制，也无需手工维护 bookCount。
//
//   实例化方式：
//     Stack<BookResource*>  lib;      书库：装基类指针 —— 多态完整保留
//     Stack<Student>        roster;   花名册：完全另一种类型，复用同一份代码
//
//   ⚠️ 为什么不能写 Stack<BookResource>：
//     1) BookResource 含纯虚函数 printInfo/borrow/returnBook，是抽象类，
//        无法按值实例化（可用 static_assert + is_abstract_v 在编译期验证）；
//     2) 即便没有纯虚函数，按值存放会发生"对象切片"：
//        Magazine 会被切成 BookResource，issueNo/period/chiefEditor 全部丢失，
//        Magazine::borrow() 再也调不到。
//
//   ⚠️ 为什么 addBook()/showbook() 里用了 -> 和 getTitle()，Stack<Student> 却没问题？
//     类模板的成员函数采用"延迟实例化"：只有被真正调用时才生成代码。
//     只要不对 Stack<Student> 调用这两个业务方法，编译器就不会去检查它们。

template <typename T>
class Stack {
private:
    vector<T> data_;        // 底层容器：容量自管理，无需 MAX_BOOKS

public:
    // ---------- 嵌套类型别名（与 STL 容器保持一致的使用习惯） ----------
    // 有了它们，就可以写 Stack<BookResource*>::iterator it = lib.begin();
    using value_type      = T;
    using iterator        = typename vector<T>::iterator;
    using const_iterator  = typename vector<T>::const_iterator;

    // ---------- 构造（vector 自己会初始化为空） ----------
    Stack() = default;

    // ---------- 通用容器接口（与元素类型无关） ----------
    void push(const T& item)   { data_.push_back(item); }
    void pop()                 { if (!data_.empty()) data_.pop_back(); }
    // 按下标删除（管理员删除资源时用）—— 底层是 vector 的 erase，删除后元素整体前移
    void erase(size_t index)   { if (index < data_.size()) data_.erase(data_.begin() + index); }
    T&   top()                 { return data_.back(); }
    const T& top() const       { return data_.back(); }

    size_t size()  const { return data_.size(); }
    bool   empty() const { return data_.empty(); }
    void   clear()       { data_.clear(); }

    T&       operator[](size_t i)       { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

    // 迭代器：对外暴露后即支持范围 for 与 std::sort 等 STL 算法
    iterator        begin()       { return data_.begin(); }
    iterator        end()         { return data_.end();   }
    const_iterator  begin() const { return data_.begin(); }
    const_iterator  end()   const { return data_.end();   }
    const_iterator  cbegin() const { return data_.cbegin(); }
    const_iterator  cend()   const { return data_.cend();   }

    // ---------- 面向图书馆业务的便捷方法（仅 Stack<BookResource*> 使用） ----------
    void addBook(const T& item);   // 入馆 + 友好提示
    void showbook();               // 遍历打印（内部仍是虚调用）
};

// ==================== 模板实现（必须写在头文件里） ====================
// 若把这些定义放进 Stack.cpp，链接时会报 LNK2019 无法解析的外部符号：
// 编译器在实例化点（如 main.cpp）看不到模板定义，无法生成对应类型的代码。

template <typename T>
void Stack<T>::addBook(const T& item) {
    if (item == nullptr) {
        cout << "添加失败：资源地址无效！" << endl;
        return;
    }
    data_.push_back(item);
    cout << "《" << item->getTitle() << "》已放入书库（当前共 "
         << data_.size() << " 份）。" << endl;
}

template <typename T>
void Stack<T>::showbook() {
    cout << "========== 书库资源清单（共 " << data_.size()
         << " 份） ==========" << endl;
    if (data_.empty()) {
        cout << "书库暂时为空。" << endl;
        return;
    }
    int i = 1;
    for (iterator it = data_.begin(); it != data_.end(); ++it, ++i) {
        cout << "----- 第 " << i << " 份 -----" << endl;
        (*it)->printInfo();     // ★ 虚调用：多态效果与实验四完全一致
    }
}

#endif // STACK_H
