#include <iostream>
 #include <cstring>
 #include <cctype>  
 
 using namespace std;
 
 class Node {
 public:
     char data;
     Node* left;
     Node* right;
     Node* next;
 
     Node(char d) : data(d), left(nullptr), right(nullptr), next(nullptr) {}
 
     char getData() { 
         return data; 
     }
     void setData(char d) { 
         data = d; 
     }
     Node* getNext() { 
         return next; 
     }
     void setNext(Node* n) { 
         next = n; 
     }
     void setLeft(Node* l) { 
         left = l; 
     }
     void setRight(Node* r) { 
         right = r; 
     }
     Node* getLeft() { 
         return left; 
     }  
     Node* getRight() { 
         return right; 
     } 
 };
 
 
 class Stack {
 public:
     Node* first;
     Stack() : first(nullptr) {}
 
 void push(Node* node) {
     node->setNext(first);
     first=node;
 }
 Node* pop() {
     if (first == nullptr) {
         return nullptr;
     } else {
         Node* temp = first;
         first = first->getNext();
         temp->setNext(nullptr);
         return temp;
     }
 }
 Node* peek() {
     return first;
 }
 bool isEmpty() {
     return first == nullptr;
 }
 };
 
 class Queue {
 public:
     Node* front;
     Node* back;
     Queue() : front(nullptr), back(nullptr) {}
 
 void enqueue(Node* value) {
     if (back == nullptr) {
         front = back = value;
     } else {
         back->setNext(value);
         back = value;
     }
 }
 Node* dequeue() {
     if (front == nullptr) {
         return nullptr;
     } else {
         Node* temp = front;
         front = front->getNext();
         if (front == nullptr) {
             back = nullptr;
         }
         temp->setNext(nullptr);  
         return temp;
     }
 }
 Node* peek() {
   return front;
 }
 
 bool isEmpty() {
     return front == nullptr;
 }
 };
 
 int main() {
     char expression[100];
     cout << "Enter an infix expression (with spaces between tokens): ";
     cin.getline(expression, 100);
 
     return 0;
 }
