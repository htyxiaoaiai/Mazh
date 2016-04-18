# Mazh
回溯解决迷宫问题
#include"Maze.h"

stack<Pos> MinLength;

Pos GetSize()
{
	FILE* maze = fopen("MazeMap.txt", "r");
	assert(maze);
	Pos result;
	int row = 0;
	int col = 0;
	char ch = fgetc(maze);
	while (ch >= '0'&& ch <= '9')
	{
		row = (ch - '0')  + row * 10;
		char c = fgetc(maze);
		if ( c== ' ')
		{
			break;
		}
		else
		{
			ungetc(c, maze);
		}
		ch = fgetc(maze);
	}
	result._row = row;

	ch = fgetc(maze);
	while (ch>= '0'&&ch <= '9')
	{
		col = (ch - '0') + col * 10;
		char c = fgetc(maze);
		if ( c == ' '&& c == '\n')
		{
			break;
		}
		else
		{
			ungetc(c, maze);
		}
		ch = fgetc(maze);
	}
	result._col = col;

	fclose(maze);
	return result;
}

void GetMaze(int *a, int row, int col)
{
	FILE* maze = fopen("MazeMap.txt", "r");
	assert(maze);
	char ch = fgetc(maze);
	while (ch != '\n')
	{
		ch = fgetc(maze);
	}//先读取第一行

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col;)
		{
			ch = fgetc(maze);
			if (ch == '0' || ch == '1')
			{
				a[row*i + j] = ch - '0';
				j++;
			}
			else
			{
				continue;
			}
		}
	}
	fclose(maze);
	PrintMaze(a, row, col);
}

void PrintMaze(int*a, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << a[i*row + j] << " ";
		}
		cout << endl;
	}
}

bool IsAcess(int *a, int row, int col, const Pos& p)//判断是否越界
{
	if (p._row >= 0 && p._row < row&&p._col >= 0 && p._col < col)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool IsVaild(int *a,int row, int col, const Pos& p)//判断是否通路
{
	if (IsAcess(a,row,col,p)&&a[p._row*row+p._col]==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MazePath(int *a, int row, int col, const Pos& entry, stack<Pos>& path)
{
	Pos cur = entry;
	Pos next;
	path.push(cur);
	while(!path.empty())
	{
		
		if (cur._row == row - 1)
		{
			a[cur._row*row + cur._col] = 1;
			return true;
		}

		a[cur._row*row + cur._col] = 2;

		//向右探测
		next = cur;
		next._col++;
		if (IsVaild(a, row, col, next))
		{
			path.push(next);
			cur = next;
			continue;
		}
		//向下探测
		next = cur;
		next._row++;
		if (IsVaild(a, row, col, next))
		{
			path.push(next);
			cur = next;
			continue;
		}
		//向上探测
		next = cur;
		next._row--;
		if (IsVaild(a, row, col, next))
		{
			path.push(next);
			cur = next;
			continue;
		}
		
		//向左探测
		next = cur;
		next._col--;
		if (IsVaild(a, row, col, next))
		{
			path.push(next);
			cur = next;
			continue;
		}
	
		//回溯
		
		cur = path.top();
		a[cur._row*row + cur._col] = 0;
		path.pop();
	}
	return false;
}


void TestMaze()
{
	Pos entry = { 2,0 };
	stack<Pos> first;
    stack<Pos> second;

	cout << GetSize()._row << endl;
	cout << GetSize()._col << endl;
	int row = GetSize()._row;
	int col = GetSize()._col;
	int *a = new int[row*col];
	GetMaze(a, row, col);
	//delete[]a;

	//cout << "第一条出路" << endl;
	if (MazePath(a, row, col, entry, first))
	{
		MinLength = first;
	}
	//PrintMaze(a, row, col);

	//将第一条路恢复并堵住
	if (!first.empty())
	{
		first.pop();
	}
	while (!first.empty())
	{
		a[first.top()._row*row + first.top()._col] = 0;
		first.pop();
	}

	/*cout << "恢复之后的结果" << endl;
	PrintMaze(a, row, col);*/
	while (MazePath(a, row, col, entry, second))
	{
		//cout << "第二条" << endl;
		//PrintMaze(a, row, col);
		if (second.size() < MinLength.size())
		{
			MinLength = second;
		}
		cout << endl;

		if (!second.empty())
		{
			second.pop();
		}
		//将second清空
		while (!second.empty())
		{
			a[second.top()._row*row + second.top()._col] = 0;
			second.pop();
		}
		//cout << "恢复上一条" << endl;
		//PrintMaze(a, row, col);
	}


	cout << "最佳路径为：" << endl;
	while (!MinLength.empty())
	{
		a[MinLength.top()._row*row + MinLength.top()._col] = 0;
		MinLength.pop();
	}
	
	PrintMaze(a, row, col);
}
