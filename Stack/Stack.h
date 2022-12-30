#pragma once

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









