#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <iostream>
#include <stdio.h>
#include <string>
#include "Node.h"
using namespace std;

template <class T>
class LinkedList : public Node<T> {
public:
    Node<T> * head;
    LinkedList(  ) {
        this->head = NULL;
    }
    LinkedList( T newData ) {
        Node<T> * newNode = new Node<T>;
        newNode->data = newData;
        this->head = newNode;
    }
    virtual ~LinkedList( ) {
        Node<T> * cur = head;
        while(cur != NULL) {
            Node<T> * tmp = cur->getNext();
            delete cur;
            cur = tmp;
        }
    }
    void print( ) {
        Node<T> * cur = head;
        while(cur->getNext() != NULL) {
            cout << cur->getData() << " ";
            cur = cur->getNext();
        }
        cout << cur->getData() << "\n";
    }


    /*T getNodeData( T findME ) {
        Node<T> * tmp = this->head;
        while(tmp != NULL) {
            if(tmp->getData() == findME) return tmp->getData();
            tmp = tmp->getNext();
        }
    }
    Node<T> * addNode( T addME ) {
        Node<T> cur = this->head;
        Node<T> newNode = new Node<T>(addME);
        while(cur != NULL) {
            if(cur->getPrev() == NULL && cur->getNext() == NULL) {
                if(cur < newNode) {
                    newNode->setPrev(cur);
                    cur->setNext(newNode);
                } else {
                    cur->setPrev(newNode);
                    newNode->setNext(cur);
                }
            } else {
                if(newNode < cur) {
                    Node<T> * tmp = cur->getPrev();
					cur->setPrev(newNode);
					newNode->setNext(cur);
					if (tmp == NULL) {
						newNode->setPrev(tmp);
						this->head = newNode;
					}
					else {
						tempnode->setNext(newNode);
                        newNode->setPrev(tmp);
					}
					return newNode;
				}
			}
			cur = cur->getNext;
		}
		cur = this->head;
		while (cur->getNext() != NULL) {
            cur = cur->getNext();
		}
		cur->setNext(newNode);
		newNode->setPrev(cur);
		return newNode;
    }
    void deleteNode(T deleteME) {
		Node<T> * cur = this->head;
		while(cur != NULL) {
			if (cur->getData() == deleteME) {
				if (cur->getPrev() == NULL) {
					Node<T>* delNode = cur;
					(cur->getNext())->setPrev(NULL);
					head = cur->getNext();
					delete delNode;
					return;
				}
				else if (cur->getNext() == NULL) {
					Node<T> * delNode = cur;
                    (cur->getPrev())->setNext(NULL);
					delete delNode;
					return;
				}
				else if (cur != head) {
					Node<T> * delNode = cur;
					(cur->getPrev())->setNext(delNode->getNext());
					(cur->getNext())->setPrev(delNode->getPrev());
					delete delNode;
					return;
				}
			}
			cur = cur->getNext();
		}
		return;
	}
    */

};

#endif /* LINKEDLIST_H_ */
