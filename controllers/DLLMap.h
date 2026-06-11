#pragma once
#include <cstddef>
#include <utility>
#include <stdexcept>

template <typename K, typename V>
struct DLLMapNode {
    K first;
    V second;
    DLLMapNode* next;
    DLLMapNode* prev;
    DLLMapNode(const K& theKey, const V& theVal) : first(theKey), second(theVal), next(nullptr), prev(nullptr) {}
};

template <typename K, typename V>
class DLLMap {
private:
    DLLMapNode<K, V>* head;
    DLLMapNode<K, V>* tail;
    size_t mySize;

public:
    class Iterator {
    public:
        DLLMapNode<K, V>* ptr;
        Iterator(DLLMapNode<K, V>* thePtr = nullptr) : ptr(thePtr) {}
        DLLMapNode<K, V>& operator*() const { return *ptr; }
        DLLMapNode<K, V>* operator->() const { return ptr; }
        Iterator& operator++() { if (ptr) ptr = ptr->next; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; if (ptr) ptr = ptr->next; return tmp; }
        Iterator& operator--() { if (ptr) ptr = ptr->prev; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; if (ptr) ptr = ptr->prev; return tmp; }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    class ConstIterator {
    public:
        const DLLMapNode<K, V>* ptr;
        ConstIterator(const DLLMapNode<K, V>* thePtr = nullptr) : ptr(thePtr) {}
        const DLLMapNode<K, V>& operator*() const { return *ptr; }
        const DLLMapNode<K, V>* operator->() const { return ptr; }
        ConstIterator& operator++() { if (ptr) ptr = ptr->next; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; if (ptr) ptr = ptr->next; return tmp; }
        ConstIterator& operator--() { if (ptr) ptr = ptr->prev; return *this; }
        ConstIterator operator--(int) { ConstIterator tmp = *this; if (ptr) ptr = ptr->prev; return tmp; }
        bool operator==(const ConstIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }
    };

    DLLMap() : head(nullptr), tail(nullptr), mySize(0) {}

    // Copy constructor
    DLLMap(const DLLMap& other) : head(nullptr), tail(nullptr), mySize(0) {
        DLLMapNode<K, V>* curr = other.head;
        while (curr) {
            insert_or_update(curr->first, curr->second);
            curr = curr->next;
        }
    }

    // Move constructor
    DLLMap(DLLMap&& other) noexcept : head(other.head), tail(other.tail), mySize(other.mySize) {
        other.head = nullptr;
        other.tail = nullptr;
        other.mySize = 0;
    }

    // Copy assignment
    DLLMap& operator=(const DLLMap& other) {
        if (this != &other) {
            clear();
            DLLMapNode<K, V>* curr = other.head;
            while (curr) {
                insert_or_update(curr->first, curr->second);
                curr = curr->next;
            }
        }
        return *this;
    }

    // Move assignment
    DLLMap& operator=(DLLMap&& other) noexcept {
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

    ~DLLMap() {
        clear();
    }

    void clear() {
        DLLMapNode<K, V>* curr = head;
        while (curr) {
            DLLMapNode<K, V>* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        mySize = 0;
    }

    size_t size() const { return mySize; }
    bool empty() const { return mySize == 0; }

    V& operator[](const K& theKey) {
        DLLMapNode<K, V>* curr = head;
        while (curr) {
            if (curr->first == theKey) return curr->second;
            curr = curr->next;
        }
        // If not found, insert a new node at the end
        DLLMapNode<K, V>* newNode = new DLLMapNode<K, V>(theKey, V());
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        mySize++;
        return newNode->second;
    }

    void insert_or_update(const K& theKey, const V& theVal) {
        DLLMapNode<K, V>* curr = head;
        while (curr) {
            if (curr->first == theKey) {
                curr->second = theVal;
                return;
            }
            curr = curr->next;
        }
        // If not found, insert
        DLLMapNode<K, V>* newNode = new DLLMapNode<K, V>(theKey, theVal);
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
};
