 #include <iostream>
 #include <cstring>
 #include <cctype>  
 
 using namespace std;

 int getPrecedence(char c);
 void infixToPostfix(const char* expression, char* output);

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

 int getPrecedence(char c) {
     if (c == '+' || c == '-'){
        return 1; 
     } 
     if (c == '*' || c == '/'){
        return 2; 
     } 
     if (c == '^'){
        return 3; 
     } 
     return 0;
 }
 
 void infixToPostfix(const char* expression, char* output) {
     Queue* outputQueue = new Queue();  
     Stack* operatorStack = new Stack();  
     int out = 0;
     int len = strlen(expression);
     bool isNumber = false;
 
     for (int i = 0; i < len; i++) {
         char c = expression[i];
 
         if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
             outputQueue->enqueue(new Node(c));  
             isNumber = true;
         } else if (isspace(c)) {
             if (isNumber) {
                 outputQueue->enqueue(new Node(' '));  
                 isNumber = false;
             }
         } else if (c == '(') {
             operatorStack->push(new Node(c)); 
         } else if (c == ')') {
             while (!operatorStack->isEmpty() && operatorStack->peek()->getData() != '(') {
                 outputQueue->enqueue(operatorStack->pop());  
             }
            operatorStack->pop();  
         } else {  
             while (!operatorStack->isEmpty() && getPrecedence(c) <= getPrecedence(operatorStack->peek()->getData())) {
                 outputQueue->enqueue(operatorStack->pop());  
             }
             operatorStack->push(new Node(c));  
         }
     }
 
     while (!operatorStack->isEmpty()) {
         outputQueue->enqueue(operatorStack->pop());
     }
 
     Node* current = outputQueue->front;
     while (current != nullptr) {
         output[out++] = current->getData();
         current = current->getNext();
     }
     output[out] = '\0';  
 
     delete outputQueue;
     delete operatorStack;
 }
 
 int main() {
     char expression[100];
     cout << "Enter an infix expression (with spaces between tokens): ";
     cin.getline(expression, 100);
 
     return 0;
 }
