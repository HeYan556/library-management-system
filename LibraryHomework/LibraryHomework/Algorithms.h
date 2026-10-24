#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

// ==================== 泛型算法（函数模板） ====================
// 实验五新增。设计要点：
//   这些算法操作的是"迭代器区间 [first, last)"而不是某个具体容器类，
//   因此与容器类型完全解耦 —— Stack<BookResource*> 内部的 vector、
//   手写的 std::vector、甚至原生数组，都能用同一份算法代码。
//   这正是 STL「容器 + 算法」分离思想的体现。
//
//   与实验四的分工：
//     行为差异（borrow/returnBook/printInfo 各不相同）→ 虚函数，运行期多态
//     遍历/查找/统计（逻辑相同、只是元素不同）        → 函数模板，编译期泛型
//   二者互不替代。

// ---------- 遍历：对每个元素執行 fn ----------
template <typename Iter, typename Fn>
void forEach(Iter first, Iter last, Fn fn) {
    for (; first != last; ++first) fn(*first);
}

// ---------- 查找：返回第一个满足 pred 的迭代器，找不到返回 last ----------
template <typename Iter, typename Pred>
Iter findIf(Iter first, Iter last, Pred pred) {
    for (; first != last; ++first)
        if (pred(*first)) return first;
    return last;
}

// ---------- 计数：统计满足 pred 的元素个数 ----------
template <typename Iter, typename Pred>
int countIf(Iter first, Iter last, Pred pred) {
    int n = 0;
    for (; first != last; ++first)
        if (pred(*first)) ++n;
    return n;
}

// ---------- 筛选：把满足 pred 的元素拷到新 vector 返回 ----------
// value_type 从迭代器萃取而来，所以返回值容器类型随实参自动确定。
template <typename Iter, typename Pred>
vector<typename iterator_traits<Iter>::value_type>
filter(Iter first, Iter last, Pred pred) {
    vector<typename iterator_traits<Iter>::value_type> out;
    for (; first != last; ++first)
        if (pred(*first)) out.push_back(*first);
    return out;
}

// ---------- 按真实类型计数 ----------
// 三件事在这里同时发生：
//   模板（编译期生成代码） + dynamic_cast（运行期类型识别） + 多态（通过基类指针操作）
// 注意：dynamic_cast 能工作，前提是 BookResource 有虚函数（RTTI 依赖多态类型）。
template <typename Sub, typename Iter>
int countType(Iter first, Iter last) {
    int n = 0;
    for (; first != last; ++first)
        if (dynamic_cast<Sub*>(*first)) ++n;
    return n;
}

// ---------- 逐个打印（取代原先写在 Stack 里的 showbook 逻辑） ----------
// 适用于元素为 BookResource* 的区间：->printInfo() 自动派发到各子类版本。
template <typename Iter>
void printAll(Iter first, Iter last) {
    int i = 1;
    for (; first != last; ++first, ++i) {
        cout << "----- 第 " << i << " 份 -----" << endl;
        (*first)->printInfo();
    }
}

#endif // ALGORITHMS_H
