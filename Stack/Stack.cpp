﻿#include "graphics.h"
#include "Stack.h"
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

STACK* st = new STACK();
void drawWelcomeInterface();
void drawStackFrame();
void stackSimulation();
void drawPush(string data);
void drawPop(int x1, int y1, int x2, int y2, string preTop);
void drawObjectsInStack();

int main()
{
    st->init();
    initgraph();
    drawWelcomeInterface();
    _getch();
    system("cls");

    drawStackFrame();
    stackSimulation();

    return 0;
}

void drawWelcomeInterface()
{
    drawText(410, 50, "STACK SIMULATION", 255, 0, 0);
    drawStackFrame();

    // bắt đầu vẽ từ vị trí node đầu tiên
    int x1 = firstNodePos.left, y1 = firstNodePos.top, x2 = firstNodePos.right, y2 = firstNodePos.bottom;
    for (int i = 0; i < 3; i++)
    {
        if (i != 0)
        {
            y2 = y1 - 10; // mỗi node cách nhau 10 đơn vị
            y1 = y2 - 50; // mỗi node rộng 50 đơn vị
        }
        rectangle(x1, y1, x2, y2);
    }

    // Vẽ hình insert
    drawText(380, 148, "INSERT", 255, 255, 0);
    setcolor(12);
    line(375, 175, 450, 175);
    setcolor(12);
    line(450, 175, 450, 250);
    setcolor(12);
    line(440, 240, 450, 250);
    setcolor(12);
    line(450, 250, 460, 240);
    setcolor(12);
    line(450, 175, 450, 250);
    setcolor(12);
    rectangle(beginPos);

    // Vẽ hình delete
    drawText(550, 148, "DELETE", 255, 255, 0);
    setcolor(12);
    line(548, 175, 625, 175);
    setcolor(12);
    line(550, 175, 550, 250);
    setcolor(12);
    line(615, 165, 625, 175);
    setcolor(12);
    line(625, 175, 615, 185);
    setcolor(12);
    rectangle(endPos);

    drawText(320, 500, "This program simulates the stack having capacity of 4 objects.", 255, 255, 255);
    drawText(420, 530, "Press any key to start.", 255, 255, 255);
}

// Vẽ các node trong stack
void drawObjectsInStack()
{
    system("cls");
    drawStackFrame();

    // Nếu stack rỗng thì thoát luôn sau khi vẽ khung stack
    if (st->isEmpty()) {
        return;
    }

    // Duyệt stack và đưa các giá trị vào vector 
    NODE* tmp = st->top;
    vector<string> data;
    for (int i = 0; i < st->size(); i++)
    {
        data.push_back(tmp->data);
        tmp = tmp->next;
    }
    // Đảo ngược lại vector để giá trị đúng chiều
    reverse(data.begin(), data.end());

    // Bắt đầu vẽ từ tọa độ node đầu tiên
    int x1 = firstNodePos.left, y1 = firstNodePos.top, x2 = firstNodePos.right, y2 = firstNodePos.bottom;
    for (int i = 0; i < st->size(); i++)
    {
        if (i != 0)
        {
            y2 = y1 - 10; // mỗi node cách nhau 10 đơn vị
            y1 = y2 - 50; // độ rỗng mỗi node là 50 đơn vị
        }
        block(x1, y1, x2, y2, data[i].c_str()); // vẽ hình node
        // cập nhật vị trí của top
        topPos.left = x1;
        topPos.top = y1;
        topPos.right = x2;
        topPos.bottom = y2;
    }
}

// Vẽ stack khi xóa
void drawPop(int x1, int y1, int x2, int y2, string preTop)
{
    int stop_y1, stop_y2;
    // di chuyển chiều dọc
    for (int i = 0; i < 150; i += 40)
    {
        system("cls");
        block(x1, y1 - i, x2, y2 - i, preTop.c_str());
        stop_y1 = y1 - i;
        stop_y2 = y2 - i;
        drawObjectsInStack();
        Sleep(sleepTime);
    }
    // di chuyển chiều ngang
    for (int i = 0; i < 260; i += 40)
    {
        system("cls");
        block(x1 + i, stop_y1 - 40 * (maxCap-st->size()), x2 + i, stop_y2 - 40 * (maxCap - st->size()), preTop.c_str());
        drawObjectsInStack();
        Sleep(sleepTime);
    }
}

void drawPush(string data)
{
    int stop_x1, stop_x2;
    // di chuyển chiều ngang
    for (int i = 0; i < 200; i += 40)
    {
        system("cls");
        block(beginPos.left + i, beginPos.top, beginPos.right + i, beginPos.bottom, data.c_str());
        stop_x1 = beginPos.left + i;
        stop_x2 = beginPos.right + i;
        drawObjectsInStack();
        Sleep(sleepTime);
    }
    // di chuyển chiều dọc
    for (int i = 0; i < getmaxy(); i += 50)
    {
        if (beginPos.bottom + i > firstNodePos.bottom - 60 *st->size())
            break;
        system("cls");
        block(stop_x1 + 30, beginPos.top + i, stop_x2 + 30, beginPos.bottom + i, data.c_str());
        drawObjectsInStack();
        Sleep(sleepTime);
    }
    // thêm node mới vào stack và vẽ lại lần nữa
    st->insert(data);
    drawObjectsInStack();
}

void stackSimulation()
{
    cout << "Press '1' to Insert." << endl;
    cout << "Press '2' to Delete." << endl;
    cout << "Press any other key to esc." << endl;
    int opt;
    string data;
    cin >> opt;
    if (opt == 1)
    {
        if (st->size() >= 4)
        {
            cout << "Stack is full. You can only choose Delete." << endl;;
            stackSimulation();
        }
        else
        {
            cout << "Enter data: ";
            cin >> data;
            drawPush(data);
            stackSimulation();
        }
    }
    else if (opt == 2)
    {
        if (!st->isEmpty())
        {
            // lưu lại giá trị của top cũ
            string preTop = st->top->data;
            // xóa 
            st->deleteElement();
            drawPop(topPos.left, topPos.top, topPos.right, topPos.bottom, preTop);
            stackSimulation();
        }
        else
        {
            cout << "Stack is empty. You must insert data first." << endl;
            stackSimulation();
        }
    }
    else 
    {
        system("cls");
    } 
}
