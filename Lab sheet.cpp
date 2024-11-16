/* 1.	Implementing Stacks and Queues:
o	Implement a stack using both array-based and linked list-based approaches.
o	Implement a queue using both array-based and linked list-based approaches*/

#include <iostream>
using namespace std;

class ArrayStack {
private:
    int* stack;
    int top;
    int capacity;

public:
    ArrayStack(int size) {
        stack = new int[size];
        capacity = size;
        top = -1;
    }

    ~ArrayStack() {
        delete[] stack;
    }

    void push(int value) {
        if (top == capacity - 1) {
            cout << "Stack overflow!" << endl;
            return;
        }
        stack[++top] = value;
    }

    void pop() {
        if (top == -1) {
            cout << "Stack underflow!" << endl;
            return;
        }
        top--;
    }

    int peek() {
        if (top == -1) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return stack[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

int main() {
    ArrayStack stack(5);
    stack.push(10);
    stack.push(20);
    cout << "Top element: " << stack.peek() << endl;
    stack.pop();
    cout << "Top element after pop: " << stack.peek() << endl;
    return 0;
}
//Implement a stack using both array-based and linked list-based approaches.
class LinkedListStack {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* top;

public:
    LinkedListStack() : top(nullptr) {}

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (!top) {
            cout << "Stack underflow!" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    int peek() {
        if (!top) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

int main() {
    LinkedListStack stack;
    stack.push(10);
    stack.push(20);
    cout << "Top element: " << stack.peek() << endl;
    stack.pop();
    cout << "Top element after pop: " << stack.peek() << endl;
    return 0;
}
// 2. Queue Implementation
//Array-Based Queue
class LinkedListQueue {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* front;
    Node* rear;

public:
    LinkedListQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (!front) {
            cout << "Queue underflow!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (!front) {
            rear = nullptr;
        }
        delete temp;
    }

    int getFront() {
        if (!front) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return front->data;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

int main() {
    LinkedListQueue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    cout << "Front element: " << queue.getFront() << endl;
    queue.dequeue();
    cout << "Front element after dequeue: " << queue.getFront() << endl;
    return 0;
}
/* System Stack: Simulate the call stack of a program using the stack implementation. Write a function to display the state of the stack at any point.
o	Reversing Data: Use a stack to reverse the contents of a given string.
o	Queue Management in Systems: Simulate a basic print queue system where documents are enqueued and dequeued for printing */
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class SystemStack {
private:
    stack<string> callStack;

public:
    // Function to simulate entering a function
    void enterFunction(const string& functionName) {
        callStack.push(functionName);
    }

    // Function to simulate exiting a function
    void exitFunction() {
        if (!callStack.empty()) {
            cout << "Exiting function: " << callStack.top() << endl;
            callStack.pop();
        } else {
            cout << "Call stack is empty!" << endl;
        }
    }

    // Function to display the current state of the stack
    void displayStack() {
        cout << "Current Call Stack:" << endl;
        if (callStack.empty()) {
            cout << "Stack is empty!" << endl;
            return;
        }
        stack<string> temp = callStack;
        while (!temp.empty()) {
            cout << temp.top() << endl;
            temp.pop();
        }
    }
};

int main() {
    SystemStack systemStack;

    systemStack.enterFunction("main");
    systemStack.enterFunction("functionA");
    systemStack.enterFunction("functionB");
    systemStack.displayStack();

    systemStack.exitFunction();
    systemStack.displayStack();

    return 0;
}
//  Reversing Data: Use a Stack to Reverse a String
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class StringReversal {
public:
    string reverseString(const string& input) {
        stack<char> charStack;

        // Push each character onto the stack
        for (char c : input) {
            charStack.push(c);
        }

        // Pop each character to get the reversed string
        string reversed = "";
        while (!charStack.empty()) {
            reversed += charStack.top();
            charStack.pop();
        }

        return reversed;
    }
};

int main() {
    StringReversal reverser;
    string input = "Hello, World!";
    string output = reverser.reverseString(input);

    cout << "Original string: " << input << endl;
    cout << "Reversed string: " << output << endl;

    return 0;
}
// Queue Management in Systems: Simulate a Print Queue System
#include <iostream>
#include <queue>
#include <string>
using namespace std;

class PrintQueue {
private:
    queue<string> printQueue;

public:
    // Enqueue a document to the print queue
    void enqueueDocument(const string& document) {
        printQueue.push(document);
        cout << "Document added to queue: " << document << endl;
    }

    // Dequeue a document from the print queue
    void dequeueDocument() {
        if (!printQueue.empty()) {
            cout << "Printing document: " << printQueue.front() << endl;
            printQueue.pop();
        } else {
            cout << "Print queue is empty!" << endl;
        }
    }

    // Display the current print queue
    void displayQueue() {
        if (printQueue.empty()) {
            cout << "Print queue is empty!" << endl;
            return;
        }

        cout << "Current Print Queue: " << endl;
        queue<string> tempQueue = printQueue;
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << endl;
            tempQueue.pop();
        }
    }
};

int main() {
    PrintQueue queue;
    
    queue.enqueueDocument("Document 1");
    queue.enqueueDocument("Document 2");
    queue.enqueueDocument("Document 3");
    
    queue.displayQueue();
    
    queue.dequeueDocument();
    queue.displayQueue();
    
    return 0;
}
/*1.	Stack Implementation:
o	Create a class ArrayStack with methods for push, pop, peek, and isEmpty.
o	Create a class LinkedListStack with methods for push, pop, peek, and isEmpty*/
#include <iostream>
using namespace std;

class ArrayStack {
private:
    int* stack;
    int top;
    int capacity;

public:
    // Constructor to initialize stack with a given size
    ArrayStack(int size) {
        stack = new int[size];
        capacity = size;
        top = -1;
    }

    // Destructor to free allocated memory
    ~ArrayStack() {
        delete[] stack;
    }

    // Push an element onto the stack
    void push(int value) {
        if (top == capacity - 1) {
            cout << "Stack overflow!" << endl;
            return;
        }
        stack[++top] = value;
    }

    // Pop an element from the stack
    void pop() {
        if (top == -1) {
            cout << "Stack underflow!" << endl;
            return;
        }
        top--;
    }
 // Peek the top element of the stack
    int peek() {
        if (top == -1) {
            cout << "Stack is empty!" << endl;
            return -1; // Return -1 if stack is empty
        }
        return stack[top];
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == -1;
    }
};

int main() {
    ArrayStack stack(5);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Top element: " << stack.peek() << endl;

    stack.pop();
    cout << "Top element after pop: " << stack.peek() << endl;

    stack.pop();
    stack.pop();

    if (stack.isEmpty()) {
        cout << "Stack is empty!" << endl;
    }

    return 0;
}
//Linked List-Based Stack Implementation
#include <iostream>
using namespace std;

class LinkedListStack {
private:
    // Node structure representing each element in the stack
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* top;

public:
    // Constructor to initialize the stack
    LinkedListStack() : top(nullptr) {}

    // Destructor to free all dynamically allocated memory
    ~LinkedListStack() {
        while (top != nullptr) {
            pop();
        }
    }

    // Push an element onto the stack
    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    // Pop an element from the stack
    void pop() {
        if (top == nullptr) {
            cout << "Stack underflow!" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    // Peek the top element of the stack
    int peek() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return -1; // Return -1 if stack is empty
        }
        return top->data;
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }
};

int main() {
    LinkedListStack stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Top element: " << stack.peek() << endl;

    stack.pop();
    cout << "Top element after pop: " << stack.peek() << endl;

    stack.pop();
    stack.pop();

    if (stack.isEmpty()) {
        cout << "Stack is empty!" << endl;
    }

    return 0;
}
/*Queue Implementation:
o	Create a class ArrayQueue with methods for enqueue, dequeue, peek, and isEmpty.
o	Create a class LinkedListQueue with methods for enqueue, dequeue, peek, and isEmpty*/
#include <iostream>
using namespace std;

class ArrayQueue {
private:
    int* queue;
    int front, rear, capacity, size;

public:
    // Constructor to initialize the queue with a given size
    ArrayQueue(int cap) {
        queue = new int[cap];
        capacity = cap;
        front = 0;
        rear = -1;
        size = 0;
    }
// Destructor to free allocated memory
    ~ArrayQueue() {
        delete[] queue;
    }
 // Enqueue an element to the queue
    void enqueue(int value) {
        if (size == capacity) {
            cout << "Queue overflow!" << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        queue[rear] = value;
        size++;
    }
 // Dequeue an element from the queue
    void dequeue() {
        if (size == 0) {
            cout << "Queue underflow!" << endl;
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }

    // Peek the front element of the queue
    int peek() {
        if (size == 0) {
            cout << "Queue is empty!" << endl;
            return -1;  // Return -1 if the queue is empty
        }
        return queue[front];
    }

    bool isEmpty() {
        return size == 0;
    }
};
int main() {
    ArrayQueue queue(5);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    cout << "Front element: " << queue.peek() << endl;

    queue.dequeue();
    cout << "Front element after dequeue: " << queue.peek() << endl;

   if (queue.isEmpty()) {
        cout << "Queue is empty!" << endl;
    }

    return 0;
}
// . Linked List-Based Queue Implementation
#include <iostream>
using namespace std;

class LinkedListQueue {
private:
    // Node structure representing each element in the queue
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    // Constructor to initialize the queue
    LinkedListQueue() : front(nullptr), rear(nullptr) {}

    // Destructor to free all dynamically allocated memory
    ~LinkedListQueue() {
        while (front != nullptr) {
            dequeue();
        }
    }

    // Enqueue an element to the queue
    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Dequeue an element from the queue
    void dequeue() {
        if (front == nullptr) {
            cout << "Queue underflow!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    // Peek the front element of the queue
    int peek() {
        if (front == nullptr) {
            cout << "Queue is empty!" << endl;
            return -1;  // Return -1 if the queue is empty
        }
        return front->data;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }
};

int main() {
    LinkedListQueue queue;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    cout << "Front element: " << queue.peek() << endl;

    queue.dequeue();
    cout << "Front element after dequeue: " << queue.peek() << endl;

    queue.dequeue();
    queue.dequeue();

    if (queue.isEmpty()) {
        cout << "Queue is empty!" << endl;
    }

    return 0;
}
/* System Stack Simulation:
o	Write a function that simulates the system stack for a simple program with nested function calls.*/
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class SystemStackSimulation {
private:
    stack<string> callStack; // Stack to simulate the system stack

public:
    // Simulate entering a function
    void enterFunction(const string& functionName) {
        callStack.push(functionName);
        cout << "Entering function: " << functionName << endl;
    }

    // Simulate exiting a function
    void exitFunction() {
        if (!callStack.empty()) {
            cout << "Exiting function: " << callStack.top() << endl;
            callStack.pop();
        } else {
            cout << "Call stack is empty!" << endl;
        }
    }

    // Display the current state of the stack (active function calls)
    void displayStack() {
        cout << "Current Call Stack:" << endl;
        if (callStack.empty()) {
            cout << "Stack is empty!" << endl;
            return;
        }
        stack<string> tempStack = callStack;
        while (!tempStack.empty()) {
            cout << tempStack.top() << endl;
            tempStack.pop();
        }
    }
};

// A few simple functions to demonstrate the nested function calls
void functionC(SystemStackSimulation& systemStack) {
    systemStack.enterFunction("functionC");
    // Simulate some work
    systemStack.displayStack();
    systemStack.exitFunction();
}

void functionB(SystemStackSimulation& systemStack) {
    systemStack.enterFunction("functionB");
    // Call another function
    functionC(systemStack);
    systemStack.displayStack();
    systemStack.exitFunction();
}

void functionA(SystemStackSimulation& systemStack) {
    systemStack.enterFunction("functionA");
    // Call another function
    functionB(systemStack);
    systemStack.displayStack();
    systemStack.exitFunction();
}

int main() {
    SystemStackSimulation systemStack;
    // Start with the main function
    systemStack.enterFunction("main");
    // Simulate nested function calls
    functionA(systemStack);
      return 0;
}
