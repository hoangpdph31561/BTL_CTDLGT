#pragma once
#include <initializer_list>
#include <cstddef>
#include <utility>
#include <stdexcept>

template <typename T>
struct DLLNode {
    T data;
    DLLNode* next;
    DLLNode* prev;
    DLLNode(const T& theData) : data(theData), next(nullptr), prev(nullptr) {}
    DLLNode(T&& theData) : data(std::move(theData)), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoubleLinkedList {
private:
    DLLNode<T>* head;
    DLLNode<T>* tail;
    size_t mySize;

public:
    class Iterator {
    public:
        DLLNode<T>* ptr;
        Iterator(DLLNode<T>* thePtr = nullptr) : ptr(thePtr) {}
        T& operator*() const { return ptr->data; }
        T* operator->() const { return &(ptr->data); }
        Iterator& operator++() { if (ptr) ptr = ptr->next; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; if (ptr) ptr = ptr->next; return tmp; }
        Iterator& operator--() { if (ptr) ptr = ptr->prev; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; if (ptr) ptr = ptr->prev; return tmp; }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    class ConstIterator {
    public:
        const DLLNode<T>* ptr;
        ConstIterator(const DLLNode<T>* thePtr = nullptr) : ptr(thePtr) {}
        const T& operator*() const { return ptr->data; }
        const T* operator->() const { return &(ptr->data); }
        ConstIterator& operator++() { if (ptr) ptr = ptr->next; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; if (ptr) ptr = ptr->next; return tmp; }
        ConstIterator& operator--() { if (ptr) ptr = ptr->prev; return *this; }
        ConstIterator operator--(int) { ConstIterator tmp = *this; if (ptr) ptr = ptr->prev; return tmp; }
        bool operator==(const ConstIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }
    };

    DoubleLinkedList() : head(nullptr), tail(nullptr), mySize(0) {}

    DoubleLinkedList(std::initializer_list<T> theList) : head(nullptr), tail(nullptr), mySize(0) {
        for (const auto& item : theList) {
            push_back(item);
        }
    }

    // Copy constructor
    DoubleLinkedList(const DoubleLinkedList& other) : head(nullptr), tail(nullptr), mySize(0) {
        DLLNode<T>* curr = other.head;
        while (curr) {
            push_back(curr->data);
            curr = curr->next;
        }
    }

    // Move constructor
    DoubleLinkedList(DoubleLinkedList&& other) noexcept : head(other.head), tail(other.tail), mySize(other.mySize) {
        other.head = nullptr;
        other.tail = nullptr;
        other.mySize = 0;
    }

    // Copy assignment
    DoubleLinkedList& operator=(const DoubleLinkedList& other) {
        if (this != &other) {
            clear();
            DLLNode<T>* curr = other.head;
            while (curr) {
                push_back(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    // Move assignment
    DoubleLinkedList& operator=(DoubleLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            mySize = other.mySize;
            other.head = nullptr;
            other.tail = nullptr;
            other.mySize = 0;
        }
        return *this;
    }

    ~DoubleLinkedList() {
        clear();
    }

    void clear() {
        DLLNode<T>* curr = head;
        while (curr) {
            DLLNode<T>* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        mySize = 0;
    }

    size_t size() const { return mySize; }
    bool empty() const { return mySize == 0; }

    void push_back(const T& theData) {
        DLLNode<T>* newNode = new DLLNode<T>(theData);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        mySize++;
    }

    void push_back(T&& theData) {
        DLLNode<T>* newNode = new DLLNode<T>(std::move(theData));
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        mySize++;
    }

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    ConstIterator begin() const { return ConstIterator(head); }
    ConstIterator end() const { return ConstIterator(nullptr); }

    T& operator[](size_t index) {
        DLLNode<T>* curr = head;
        size_t count = 0;
        while (curr) {
            if (count == index) return curr->data;
            curr = curr->next;
            count++;
        }
        throw std::out_of_range("Index out of range");
    }

    const T& operator[](size_t index) const {
        DLLNode<T>* curr = head;
        size_t count = 0;
        while (curr) {
            if (count == index) return curr->data;
            curr = curr->next;
            count++;
        }
        throw std::out_of_range("Index out of range");
    }

    // A list-friendly remove method
    template <typename Predicate>
    bool erase_if(Predicate pred) {
        bool found = false;
        DLLNode<T>* curr = head;
        while (curr) {
            DLLNode<T>* nextNode = curr->next;
            if (pred(curr->data)) {
                if (curr->prev) {
                    curr->prev->next = curr->next;
                } else {
                    head = curr->next;
                }
                if (curr->next) {
                    curr->next->prev = curr->prev;
                } else {
                    tail = curr->prev;
                }
                delete curr;
                mySize--;
                found = true;
            }
            curr = nextNode;
        }
        return found;
    }

    // Custom sorting using selection sort
    template <typename Compare>
    void sort(Compare comp) {
        if (!head || !head->next) return;
        for (DLLNode<T>* i = head; i != nullptr; i = i->next) {
            for (DLLNode<T>* j = i->next; j != nullptr; j = j->next) {
                if (comp(j->data, i->data)) {
                    std::swap(i->data, j->data);
                }
            }
        }
    }
};
