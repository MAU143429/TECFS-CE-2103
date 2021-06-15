//
// Created by njohnson on 6/13/21.
//

#ifndef TEC_FS_SIMPLYLIST_H
#define TEC_FS_SIMPLYLIST_H

#include <cstdlib>
#include <iostream>

using namespace std;

template<typename T>
class Node {

    T value;
public:
    explicit Node(T value) : value(value) {}

private:
    Node* next;
public:
    const T& getValue() const {
        return value;
    }

    void setValue(const T& value) {
        Node::value = value;
    }

    Node* getNext() const {
        return next;
    }

    void setNext(Node* next) {
        Node::next = next;
    }
};

template<typename T>
class SimplyLinkedList {

public:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int len{};

    SimplyLinkedList() {
        this->head = NULL;
        this->len = 0;
        this->tail = NULL;
    }

    Node<T>* getHead() const {
        return head;
    }
    /**
     * @brief Deletes an element in the list
     * @param element
     */
    void del(T element) {

        if (element == this->head->getValue()) {
            this->head = this->head->getNext();
            this->len--;
        }
        else {
            Node<T>* tmp = this->head;
            for (int i = 0; i < (this->len - 1); ++i) {
                if (tmp->getNext()->getValue() == element) {
                    tmp->setNext(tmp->getNext()->getNext());
                    this->len--;
                    return;
                }
                else {
                    tmp = tmp->getNext();
                }
            }
        }
    }
    /**
     * @brief Appends an element in the list
     * @param element
     */
    void append(T element) {
        auto* newElement = (Node<T> *) (malloc(sizeof(Node<T>)));
        newElement = new(newElement) Node<T>(element);

        if (this->head == nullptr) {
            this->head = this->tail = newElement;
        }
        else {
            this->tail->setNext(newElement);
            this->tail = newElement;
        }
        this->len += 1;
    }
    /**
     * @brief prints the simply linked list
     */
    void show() const {

        if (this->head == nullptr) {
            cout << "[]";
        }
        else {
            cout << "[";
            Node<T>* tmp = this->head;
            for (int i = 0; i < (this->len - 1); ++i) {
                cout << tmp->getValue() << ", ";
                tmp = tmp->getNext();
            }
            cout << tmp->getValue() << "]" << "\n";
        }
    }
    /**
     * @brief method that searches for the position inserted and gets the value
     * @param i
     * @return
     */
    T get(int i) {

        if (i >= this->len) {
            return 0;
        }
        Node<T>* tmp = this->head;
        for (int j = 0; j < i; ++j) {

            tmp = tmp->getNext();

        }
        return tmp->getValue();
    }
    /**
     * @brief searches for an element contained in the list
     * @param element
     * @return returns true if the item is contained in the list, false if not.
     */
    bool boolSearch(T element) {
        bool result = false;
        Node<T>* tmp = this->head;
        for (int i = 0; i < (this->len); ++i) {
            if (tmp->getValue() == element) {
                result = true;
                break;
            }
            tmp = tmp->getNext();
        }
        return result;
    }
    /**
     * @brief deletes the head
     */
    void delHead() {
        this->del(this->head->getValue());
    }

    void Clean_list() {

        for (int i = 0; i < (this->len); ++i) {
            Node<T>* tmp = this->head;
            if (this->len != 1) {

                this->del(this->head);
                tmp->next = this->head;
                len--;
            }
        }
        this->head = nullptr;


    }

    void Clear() {
        this->head = nullptr;
        this->tail = nullptr;
        len = 0;
    }

    int getLen() {
        return this->len;
    }
};
#endif //TEC_FS_SIMPLYLIST_H
