/*1.	Text Editor Operations:
o	Implement the text editor using an array to store the characters.
o	Implement a stack to manage the undo and redo operations.
o	Implement a queue for clipboard management to support copy-paste */
#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

class TextEditor {
private:
    string text;                     // Array-based string for storing characters
    stack<string> undoStack;         // Stack for undo operations
    stack<string> redoStack;         // Stack for redo operations
    queue<string> clipboardQueue;    // Queue for clipboard management

public:
    // Function to display the current text
    void display() {
        cout << "Current Text: " << text << endl;
    }

    // Add text to the editor
    void addText(const string& newText) {
        // Save the current state for undo
        undoStack.push(text);
        // Clear redo stack on new edit
        while (!redoStack.empty()) redoStack.pop();

        text += newText;  // Append new text
        cout << "Added text: \"" << newText << "\"" << endl;
    }
void deleteText(int n) {
        if (n > text.size()) n = text.size(); // Prevent deletion beyond text size

        undoStack.push(text);
        while (!redoStack.empty()) redoStack.pop();

        text.erase(text.size() - n);
        cout << "Deleted last " << n << " characters." << endl;
    }

    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }

        // Save the current state for redo
        redoStack.push(text);
        // Restore the last state from undo stack
        text = undoStack.top();
        undoStack.pop();
        cout << "Undo performed." << endl;
    }

    // Redo the last undone operation
    void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }

        // Save the current state for undo
        undoStack.push(text);
        // Restore the last state from redo stack
        text = redoStack.top();
        redoStack.pop();
        cout << "Redo performed." << endl;
    }

    // Copy text to the clipboard
    void copyToClipboard(const string& clipText) {
        clipboardQueue.push(clipText); // Add the copied text to the clipboard queue
        cout << "Copied to clipboard: \"" << clipText << "\"" << endl;
    }

    // Paste text from the clipboard
    void pasteFromClipboard() {
        if (clipboardQueue.empty()) {
            cout << "Clipboard is empty!" << endl;
            return;
        }

        // Save the current state for undo
        undoStack.push(text);
        // Clear redo stack on new edit
        while (!redoStack.empty()) redoStack.pop();

        string clipText = clipboardQueue.front(); // Retrieve the text from the clipboard
        clipboardQueue.pop();                     // Remove the text from the clipboard queue
        text += clipText;                         // Append it to the text

        cout << "Pasted from clipboard: \"" << clipText << "\"" << endl;
    }
};

int main() {
    TextEditor editor;

    // Demonstration
    editor.display();

    // Add text
    editor.addText("Hello");
    editor.display();

    editor.addText(", World!");
    editor.display();

    // Undo and redo operations
    editor.undo();
    editor.display();

    editor.redo();
    editor.display();

    // Copy-paste operations
    editor.copyToClipboard(" New Content");
    editor.pasteFromClipboard();
    editor.display();

    // Delete operations
    editor.deleteText(5);
    editor.display();

    editor.undo();
    editor.display();

    return 0;
}

/*Functional Requirements:
o	Insert Text: Insert characters at a specified position.
o	Delete Text: Delete characters from a specified position.
o	Undo/Redo: Implement undo and redo functionalities using stacks.
o	Copy-Paste: Implement clipboard management using a queue to support copy and paste operations.*/
#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

class TextEditor {
private:
    string text;                     // Stores the text
    stack<string> undoStack;         // Stack for undo operations
    stack<string> redoStack;         // Stack for redo operations
    queue<string> clipboardQueue;    // Queue for clipboard management

public:
    // Display the current text
    void display() {
        cout << "Current Text: \"" << text << "\"" << endl;
    }

    // Insert text at a specific position
    void insertText(const string& newText, int position) {
        if (position < 0 || position > text.size()) {
            cout << "Invalid position!" << endl;
            return;
        }

        // Save the current state for undo
        undoStack.push(text);
        // Clear the redo stack for a new operation
        while (!redoStack.empty()) redoStack.pop();

        // Insert text
        text.insert(position, newText);
        cout << "Inserted text: \"" << newText << "\" at position " << position << endl;
    }

    // Delete text starting at a specific position
    void deleteText(int position, int length) {
        if (position < 0 || position >= text.size() || length <= 0) {
            cout << "Invalid position or length!" << endl;
            return;
        }

        // Adjust length to avoid overflow
        if (position + length > text.size()) {
            length = text.size() - position;
        }

        // Save the current state for undo
        undoStack.push(text);
        // Clear the redo stack for a new operation
        while (!redoStack.empty()) redoStack.pop();

        // Delete text
        text.erase(position, length);
        cout << "Deleted " << length << " characters starting at position " << position << endl;
    }

    // Undo the last operation
    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }
void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }

        // Save the current state for undo
        undoStack.push(text);
        // Restore the last state from the redo stack
        text = redoStack.top();
        redoStack.pop();
        cout << "Redo performed." << endl;
    }
void copyToClipboard(int position, int length) {
        if (position < 0 || position >= text.size() || length <= 0) {
            cout << "Invalid position or length!" << endl;
            return;
        }

        // Adjust length to avoid overflow
        if (position + length > text.size()) {
            length = text.size() - position;
        }
clipboardQueue.push(text.substr(position, length));
        cout << "Copied \"" << text.substr(position, length) << "\" to clipboard." << endl;
    }
void pasteFromClipboard(int position) {
        if (position < 0 || position > text.size()) {
            cout << "Invalid position!" << endl;
            return;
        }

        if (clipboardQueue.empty()) {
            cout << "Clipboard is empty!" << endl;
            return;
        }

        // Save the current state for undo
        undoStack.push(text);
        // Clear the redo stack for a new operation
        while (!redoStack.empty()) redoStack.pop();

        // Paste the text from the clipboard
        string clipText = clipboardQueue.front();
        text.insert(position, clipText);
        clipboardQueue.pop();
        cout << "Pasted \"" << clipText << "\" at position " << position << endl;
    }
};

int main() {
    TextEditor editor;

    // Demonstrating functionality
    editor.display();

    // Insert text
    editor.insertText("Hello", 0);
    editor.display();

    editor.insertText(" World", 5);
    editor.display();

    // Delete text
    editor.deleteText(5, 6);
    editor.display();

    // Undo and Redo
    editor.undo();
    editor.display();

    editor.redo();
    editor.display();

  return 0;
}
/*Text Editor Implementation:
o	Create a class TextEditor that uses an array to store text characters.
o	Implement methods for inserting and deleting text.
o	Use stacks to manage undo and redo operations.
o	Use a queue to implement clipboard functionality.*/
#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

class TextEditor {
private:
    string text;                     // Array-based storage for text
    stack<string> undoStack;         // Stack to manage undo operations
    stack<string> redoStack;         // Stack to manage redo operations
    queue<string> clipboardQueue;    // Queue for clipboard management

public:
    // Display the current text
    void display() {
        cout << "Current Text: \"" << text << "\"" << endl;
    }

    // Insert text at a specific position
    void insertText(const string& newText, int position) {
        if (position < 0 || position > text.size()) {
            cout << "Invalid position!" << endl;
            return;
        }

        // Save the current state for undo
        undoStack.push(text);
        // Clear the redo stack for a new operation
        while (!redoStack.empty()) redoStack.pop();

        // Insert the new text
        text.insert(position, newText);
        cout << "Inserted \"" << newText << "\" at position " << position << endl;
    }

    // Delete text from a specified position
    void deleteText(int position, int length) {
        if (position < 0 || position >= text.size() || length <= 0) {
            cout << "Invalid position or length!" << endl;
            return;
        }

        // Adjust length to avoid overflow
        if (position + length > text.size()) {
            length = text.size() - position;
        }

        // Save the current state for undo
        undoStack.push(text);
        // Clear the redo stack for a new operation
        while (!redoStack.empty()) redoStack.pop();

        // Delete the text
        text.erase(position, length);
        cout << "Deleted " << length << " characters starting at position " << position << endl;
    }

    // Undo the last operation
    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }

        // Save the current state for redo
        redoStack.push(text);
        // Restore the last state from the undo stack
        text = undoStack.top();
        undoStack.pop();
        cout << "Undo performed." << endl;
    }

    // Redo the last undone operation
    void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }

        // Save the current state for undo
        undoStack.push(text);
        // Restore the last state from the redo stack
        text = redoStack.top();
        redoStack.pop();
        cout << "Redo performed." << endl;
    }

    // Copy text to the clipboard
    void copyToClipboard(int position, int length) {
        if (position < 0 || position >= text.size() || length <= 0) {
            cout << "Invalid position or length!" << endl;
            return;
        }

        // Adjust length to avoid overflow
        if (position + length > text.size()) {
            length = text.size() - position;
        }

        // Add the copied text to the clipboard
        clipboardQueue.push(text.substr(position, length));
        cout << "Copied \"" << text.substr(position, length) << "\" to clipboard." << endl;
    }

    // Paste text from the clipboard at a specific position
    void pasteFromClipboard(int position) {
        if (position < 0 || position > text.size()) {
            cout << "Invalid position!" << endl;
            return;
        }

        if (clipboardQueue.empty()) {
            cout << "Clipboard is empty!" << endl;
            return;
        }

        // Save the current state for undo
        undoStack.push(text);
        // Clear the redo stack for a new operation
        while (!redoStack.empty()) redoStack.pop();

        // Paste the text from the clipboard
        string clipText = clipboardQueue.front();
        text.insert(position, clipText);
        clipboardQueue.pop();
        cout << "Pasted \"" << clipText << "\" at position " << position << endl;
    }
};

int main() {
    TextEditor editor;

    // Display the initial state
    editor.display();

    // Insert text
    editor.insertText("Hello", 0);
    editor.display();

    editor.insertText(" World", 5);
    editor.display();

    // Delete text
    editor.deleteText(5, 6);
    editor.display();

    // Undo and redo operations
    editor.undo();
    editor.display();
editor.redo();
    editor.display();

    // Copy-Paste functionality
    editor.copyToClipboard(0, 5); // Copy "Hello"
    editor.pasteFromClipboard(5);
    editor.display();

    // Delete and undo-paste
    editor.deleteText(5, 5); // Deletes "Hello" pasted earlier
    editor.undo();
    editor.display();

    return 0;
}
/*Insert Text:
o	Method insertText(position, text) to insert text at the specified position.*/
#include <iostream>
#include <string>
using namespace std;

class TextEditor {
private:
    string text; // Array-like storage for text

public:
    // Display the current text
    void display() {
        cout << "Current Text: \"" << text << "\"" << endl;
    }

    // Method to insert text at a specified position
    void insertText(int position, const string& newText) {
        if (position < 0 || position > text.size()) {
            cout << "Invalid position!" << endl;
            return;
        }
text.insert(position, newText);
        cout << "Inserted \"" << newText << "\" at position " << position << endl;
    }
};

int main() {
    TextEditor editor;

    // Display the initial state
    editor.display();

    // Insert text at various positions
    editor.insertText(0, "Hello");   // Insert "Hello" at the beginning
    editor.display();

    editor.insertText(5, " World"); // Insert " World" at the end of "Hello"
    editor.display();

    editor.insertText(6, "Beautiful "); // Insert "Beautiful " in between
    editor.display();

    return 0;
}
/*Delete Text:
o	Method deleteText(position, length) to delete a specified number of characters from the specified position.*/
#include <iostream>
#include <string>
using namespace std;

class TextEditor {
private:
    string text; // Array-like storage for text

public:
    // Display the current text
    void display() {
        cout << "Current Text: \"" << text << "\"" << endl;
    }

    // Method to delete a specified number of characters from a given position
    void deleteText(int position, int length) {
        if (position < 0 || position >= text.size() || length <= 0) {
            cout << "Invalid position or length!" << endl;
            return;
        }

        // Adjust the length to avoid out-of-bounds access
        if (position + length > text.size()) {
            length = text.size() - position;
        }

        // Erase the specified characters
        text.erase(position, length);
        cout << "Deleted " << length << " characters starting at position " << position << endl;
    }
};

int main() {
    TextEditor editor;

    // Insert initial text
    editor.insertText(0, "Hello World");
    editor.display();

    // Delete a section of the text
    editor.deleteText(6, 5); // Delete "World"
    editor.display();

    // Delete from an invalid position
    editor.deleteText(20, 5);
    editor.display();

    // Delete more than the available text
    editor.deleteText(0, 20);
    editor.display();

    return 0;
}
/*Undo/Redo Operations:
o	Methods undo() and redo() to reverse and reapply the last editing operations.*/
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class TextEditor {
private:
    string text;                     // Current text
    stack<string> undoStack;         // Stack to manage undo operations
    stack<string> redoStack;         // Stack to manage redo operations

public:
    // Display the current text
    void display() {
        cout << "Current Text: \"" << text << "\"" << endl;
    }

    // Insert text at a specific position
    void insertText(int position, const string& newText) {
        if (position < 0 || position > text.size()) {
            cout << "Invalid position!" << endl;
            return;
        }

        // Save current state to undo stack
        undoStack.push(text);
        // Clear redo stack as this is a new operation
        while (!redoStack.empty()) redoStack.pop();

        // Insert the text
        text.insert(position, newText);
        cout << "Inserted \"" << newText << "\" at position " << position << endl;
    }

    // Delete text from a specified position
    void deleteText(int position, int length) {
        if (position < 0 || position >= text.size() || length <= 0) {
            cout << "Invalid position or length!" << endl;
            return;
        }

        // Adjust length to avoid out-of-bounds deletion
        if (position + length > text.size()) {
            length = text.size() - position;
        }

        // Save current state to undo stack
        undoStack.push(text);
        // Clear redo stack as this is a new operation
        while (!redoStack.empty()) redoStack.pop();

        // Delete the text
        text.erase(position, length);
        cout << "Deleted " << length << " characters starting at position " << position << endl;
    }

    // Undo the last operation
    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }

        // Save current state to redo stack
        redoStack.push(text);
        // Restore the previous state from the undo stack
        text = undoStack.top();
        undoStack.pop();
        cout << "Undo performed." << endl;
    }

    // Redo the last undone operation
    void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }

        // Save current state to undo stack
        undoStack.push(text);
        // Restore the last undone state from the redo stack
        text = redoStack.top();
        redoStack.pop();
        cout << "Redo performed." << endl;
    }
};

int main() {
    TextEditor editor;

    // Insert initial text
    editor.insertText(0, "Hello");
    editor.display();

    // Insert more text
    editor.insertText(5, " World");
    editor.display();

    // Delete some text
     return 0;
}

