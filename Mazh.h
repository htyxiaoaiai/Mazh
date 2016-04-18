# Mazh
回溯解决迷宫问题
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<assert.h>
using namespace std;

struct Pos
{
	int _row;
	int _col;
};

Pos GetSize();
void GetMaze(int *a, int row, int col);
void PrintMaze(int*a, int row, int col);
bool MazePath(int *a, int row, int col, const Pos& entry, stack<Pos>& path);
void TestMaze();
