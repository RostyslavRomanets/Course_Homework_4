//
// Created by Rostik on 3/14/2024.
//

#ifndef HOMEWORK_4_FORWARDLIST_H
#define HOMEWORK_4_FORWARDLIST_H

#include <memory>
#include <functional>

template <typename T>
using SplitPredicate = std::function<bool(const T& val)>;

template <typename T>
struct ForwardListNode {
    ForwardListNode(const T& val, ForwardListNode<T> *next = nullptr)
            : Val(val), Next(next) {}

    ForwardListNode(T&& val, ForwardListNode<T> *next = nullptr)
            : Val(std::move(val)), Next(next) {}

    T Val;
    ForwardListNode<T>* Next;
};

template <typename FList>
class ForwardListIterator {
public:
    using ValueType = typename FList::ValueType;
    using NodeType = typename FList::Node;

private:
    NodeType *node_;

public:
    ForwardListIterator(NodeType *node)
        : node_(node) {}

    ValueType& operator*() {
        return node_->Val;
    }

    ForwardListIterator<FList>& operator++() {
        if (node_)
            node_ = node_->Next;
        return *this;
    }

    ForwardListIterator<FList> operator++(int) {
        ForwardListIterator<FList> temp(*this);
        ++*this;
        return temp;
    }

    bool operator==(const ForwardListIterator<FList>& other) {
        return node_ == other.node_;
    }

    bool operator!=(const ForwardListIterator<FList>& other) {
        return node_ != other.node_;
    }
};

template <typename T>
class ForwardList {
public:
    using ValueType = T;
    using Node = ForwardListNode<ValueType>;
    using Iterator = ForwardListIterator<ForwardList<ValueType>>;

public:
    ForwardList() = default;

    explicit ForwardList(size_t count) : ForwardList(count, {}) {}

    ForwardList(size_t count, const T& val)
            : size_(count) {
        for (int i = 0; i < size_; i++)
            head_ = new Node(val, head_);
    }

    ForwardList(std::initializer_list<T> items)
            : size_(items.size()) {
        for (auto it = std::rbegin(items); it != std::rend(items); ++it)
            head_ = new Node(*it, head_);
    }

    ForwardList(const ForwardList<T>& other)
            : size_(other.size_) {
        Node *tail;

        for (auto curr = other.head_; curr != nullptr; curr = curr->Next)
        {
            auto newNode = new Node(curr->Val);
            if (head_ == nullptr)
                head_ = newNode;
            else
                tail->Next = newNode;

            tail = newNode;
        }
    }

    ForwardList(ForwardList<T>&& other) noexcept {
        other.swap(*this);
    }

    ForwardList& operator=(const ForwardList<T>& other) {
        // We get copy of other and swaps it with *this
        ForwardList<T> temp(other);
        temp.swap(*this);
        return *this;
    }

    ForwardList& operator=(ForwardList<T>&& other) noexcept {
        // Basically, "other" is a temporary variable, so we don't care what will be there after move assignment
        // clear();
        other.swap(*this);
        return *this;
    }

    ~ForwardList() {
        clear();
    }

    // Iterators
    Iterator begin() {
        return Iterator(head_);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    Iterator before_begin() {
        return Iterator(ForwardListNode(nullptr, head_));
    }

    T& front() {
        return head_->Val;
    }

    ForwardList<T> split_when(SplitPredicate<T> condition) {
        Node* prev = nullptr;

        size_t newSize = 0;
        for (auto curr = head_; curr; prev = curr, curr = curr->Next)
        {
            if (condition(curr->Val))
            {
                if (prev)
                    prev->Next = nullptr;

                ForwardList<T> newList;
                newList.head_ = curr;
                newList.size_ = size_ - newSize;
                size_ = newSize;
                return newList;
            }
            newSize++;
        }

        return {};
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void swap(ForwardList<T> &other) {
        std::swap(head_, other.head_);
        std::swap(size_, other.size_);
    }

    void push_front(const T& val) {
        head_ = new Node(val, head_);
        size_++;
    }

    void push_front(T&& val) {
        head_ = new Node(std::move(val), head_);
        size_++;
    }

    void pop_front() {
        auto pop = head_;
        head_ = head_->Next;
        delete pop;
        size_--;
    }

    void clear() {
        Node* next;
        for (; head_; head_ = next)
        {
            next = head_->Next;
            delete head_;
        }
        size_ = 0;
    }

private:
    size_t size_ = 0;
    Node* head_ = nullptr;
};


#endif //HOMEWORK_4_FORWARDLIST_H
