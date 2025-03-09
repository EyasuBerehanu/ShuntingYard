//Eyasu Berehanu
//3/7/2025
//Take a mathematical expression containing the four basic arithmetic 
//expressions, power, integer numbers, and parentheses. 
//Translate it into postfix notation. Then take in the postfix notation 
//and create an expression tree allowing the user to output the expression 
//as infix, prefix, or postfix notation using the expression tree.
//Sources
//Got help from my brother 
//https://stackoverflow.com/questions/12684086/convert-from-an-infix-expression-to-postfix-c-using-stacks
//https://www.geeksforgeeks.org/stack-push-and-pop-in-c-stl/
//https://www.youtube.com/watch?v=Wz85Hiwi5MY (Comp Sci in 5: Shunting Yard Algorithm)
//https://dengking.github.io/compiler-principle/Guide/Expression-tree/geeksforgeeks-Expression-Tree/Expression-Tree/
//https://en.wikipedia.org/wiki/Shunting_yard_algorithm
//https://www.geeksforgeeks.org/infix-postfix-prefix-notation/

#include <iostream>
#include <cstring>
#include <cctype>  

using namespace std;

void infixToPostfix(const char* expression, char* output);
int getPrecedence(char c);

class Node { //node class for nodes for the other functions like the stack and queue
public:
    char data; //stores the orpateror symobles and the numbers
    Node* left;
    Node* right;
    Node* next;

    Node(char d) : data(d), left(nullptr), right(nullptr), next(nullptr) {}

    char getData() { //getter for data
        return data; 
    }
    void setData(char d) { //setter for data
        data = d; 
    }
    Node* getNext() { //getter for next
        return next; 
    }
    void setNext(Node* n) { //setter for next
        next = n; 
    }
    void setLeft(Node* l) { //setter for left
        left = l; 
    }
    void setRight(Node* r) { //setter for right
        right = r; 
    }
    Node* getLeft() {  //getter for left
        return left; 
    }  
    Node* getRight() { //getter for right
        return right;  
    } 
};


class Stack { //used for holds operators not yet added to the output queue and the tree
public:
    Node* first;
    Stack() : first(nullptr) {}

void push(Node* node) { //pushes node onto stack
    node->setNext(first);
    first=node;
}
Node* pop() { //pops node from stack
    if (first == nullptr) {
        return nullptr;
    } else {
        Node* temp = first;
        first = first->getNext();
        temp->setNext(nullptr);
        return temp;
    }
}
Node* peek() { //returts value on top without removing it
    return first;
}
bool isEmpty() {
    return first == nullptr;
}

};

class Queue { //class for queue which store and manage data in a specific order also used for postfix output
public:
    Node* front; //front of queue
    Node* back; //back of queue
    Queue() : front(nullptr), back(nullptr) {}

void enqueue(Node* value) { //adds node to the end of queue
    if (back == nullptr) {
        front = back = value;
    } else {
        back->setNext(value);
        back = value;
    }
}
Node* dequeue() { //removes node from front of queue and returns that node that was removed
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
Node* peek() { //used peek twice for stack and queue i dont think i could have used one peek for both
    return front;
}

bool isEmpty() {
    return front == nullptr;
}

};

int getPrecedence(char c) { //for precdednce or like priority according to pendas
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

void infixToPostfix(const char* expression, char* output) { //converts infix to postifix using Shunting Yard algorithm 
    Queue* outputQueue = new Queue();  //queue for postfix sorting
    Stack* operatorStack = new Stack();  //stack for oprators
    int out = 0;
    int len = strlen(expression);
    bool isNumber = false;

    for (int i = 0; i < len; i++) {
        char c = expression[i];

        if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            outputQueue->enqueue(new Node(c));   //this is so the numbers go imdently to the queue unlike the opprators
            isNumber = true;
        } else if (isspace(c)) { //attpemt to do spaces but doesnt work so i did it without it :/
            if (isNumber) {
                outputQueue->enqueue(new Node(' '));  
                isNumber = false;
            }
        } else if (c == '(') {
            operatorStack->push(new Node(c)); //pushes ( onto stack)
        } else if (c == ')') {
            while (!operatorStack->isEmpty() && operatorStack->peek()->getData() != '(') {
                outputQueue->enqueue(operatorStack->pop());  //pop operator to the queue until a ( shows up
            }
            operatorStack->pop();  
        } else {  
            while (!operatorStack->isEmpty() && getPrecedence(c) <= getPrecedence(operatorStack->peek()->getData())) {
                outputQueue->enqueue(operatorStack->pop());  //pop higher precedence operator to queue
            }
            operatorStack->push(new Node(c));  //pushes current opprator 
        }
    }

    while (!operatorStack->isEmpty()) {
        outputQueue->enqueue(operatorStack->pop()); //pops anything else that was remaining
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

Node* expressionTree(const char* postfix) { //contsructs expression tree using the postfix equation
    Stack* tree = new Stack();  //holds the nodes for the tree
    int len = strlen(postfix);

    for (int i = 0; i < len; i++) { //goes or loops through each thing in postix equation
        char c = postfix[i];
        Node* node = new Node(c);

        if (c >= '0' && c <= '9') {  // if its a number its a leaf node 
            tree->push(node);  //pushes node or number onto stack
        } else { 
            node->setRight(tree->pop());  //pops right number from stack and sets it to right child
            node->setLeft(tree->pop());  //pops left number from stack and sets it to left child
            tree->push(node);  //pushs operator node back onto stack
        }
    }

    Node* root = tree->pop();  
    delete tree;
    return root;
}


void infix(Node* tree) { //uses recurstion to print the infix which uses parentatheis
    if (tree != NULL) {
        if (tree->getData() == '+' || tree->getData() == '-' || tree->getData() == '/' || tree->getData() == '*' || tree->getData() == '^') {
            cout << '(';
        }
        infix(tree->getLeft());   
        cout << tree->getData();
        infix(tree->getRight()); 

        if (tree->getData() == '+' || tree->getData() == '-' || tree->getData() == '/' || tree->getData() == '*' || tree->getData() == '^') {
            cout << ')';
        }
    }
}

void postfix(Node* tree) { //uses recurstion to print the postfix verison
    if (tree != NULL) {
        postfix(tree->getLeft());  
        postfix(tree->getRight());
        cout << tree->getData();
    }
}

void prefix(Node* tree) { //uses recurstion to print prefix verison
    if (tree != NULL) {
        cout << tree->getData();
        prefix(tree->getLeft());   
        prefix(tree->getRight());  
    }
}

int main() { //prompts user for equation and conversts it to postfix then converting it to trhe chose verisons after that
    char expression[100];
    cout << "Enter an equation to convert (no spaces please): ";
    cin.getline(expression, 100);

    char postfixExpression[100];
    infixToPostfix(expression, postfixExpression);

    cout << "Postfix Expression: " << postfixExpression << endl;

    Node* root = expressionTree(postfixExpression);

    char choice[100];  

    while (true) {  
        cout << "Choose notation version you want being, infix, prefix, postfix (type end to end): " << endl;
        cin >> choice;

        if (strcmp(choice, "infix") == 0) {
            cout << "Infix Expression: " << endl;
            infix(root);
            cout << endl;
            
        } else if (strcmp(choice, "prefix") == 0) {
            cout << "Prefix Expression: " << endl;
            prefix(root);
            cout << endl;
            
        } else if (strcmp(choice, "postfix") == 0) {
            cout << "Postfix Expressionm from the tree: " << endl;
            postfix(root);
            cout << endl;
            
        } else if (strcmp(choice, "end") == 0) {
            break;  
            
        } 
    }

    return 0;
}
