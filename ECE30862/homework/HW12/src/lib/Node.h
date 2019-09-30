#ifndef NODE_H_
#define NODE_H_
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

template <typename T>
class Node {
public:
    Node<T> * prev;
    T data;
    Node<T> * next;
    Node(  ) {
        prev = NULL;
        next = NULL;
        data = 0;
    }
    Node(T d) {
        prev = NULL;
        next = NULL;
        data = d;
    }
    virtual ~Node( ) {  };

    void setNext( Node<T> * nxt ) {
        next = nxt;
    }
    void setPrev( Node<T> * prv ) {
        prev = prv;
    }
    Node<T> * getNext( ) {
        return next;
    }
    Node<T> * getPrev( ) {
        return prev;
    }
    T getData( ) {
        return data;
    }

    /*bool operator<(const Node<T>& rhs) const {
       return this->data < rhs.data;
    }
    bool operator==(const Node<T>& rhs) const {
       return this->data == rhs.data;
    }
    ostream& operator<<(ostream& os) {
       os << "<" << this->data << "> ";
       return os;
   }*/
};

#endif /* NODE_H_ */
