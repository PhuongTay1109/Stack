#pragma once
RECT beginPos = { 250, 150, 370, 200 }; // tọa độ node xuất hiện để di chuyển vào stack
RECT topPos; // tọa độ của top stack
RECT firstNodePos = { 440, 390, 560, 440 }; 
RECT endPos = { 630, 150, 755, 200 }; // tọa độ node dừng sau khi di chuyển khỏi stack
int sleepTime = 100;
int maxCap = 4; // số node tối đa

struct NODE {
    string data;
    NODE* next;
};

struct STACK {
    NODE* top;

    void init() {
        top = nullptr;
    }

    bool isEmpty() {
        if (top == nullptr)
            return true;
        return false;
    }

    NODE* makeNode(string x) {
        NODE* newNode = new NODE();
        newNode->data = x;
        newNode->next = nullptr;
        return newNode;
    }

   // Push
    void insert(string x) {
        NODE* newNode = makeNode(x);
        if (this->isEmpty())
            top = newNode;
        else {
            newNode->next = top;
            top = newNode;
        }
    }

    // Pop
    void deleteElement() {
        if (this->isEmpty())
            return;
        NODE* newTop = top->next;
        delete (top);
        top = newTop;
    }

    int size()
    {
        NODE* tmp = top;
        int cnt = 0;
        while (tmp != nullptr) {
            cnt++;
            tmp = tmp->next;
        }
        return cnt;
    }
};

void drawStackFrame()
{
    setcolor(15);
    line(420, 200, 420, 450);
    line(420, 450, 578, 450);
    line(578, 200, 578, 450);
}







