#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tailLen = 0;
enum eDirection
{
	STOP = 0,
	LEFT,
	RIGHT,
	DOWN,
	UP
};
eDirection dir;
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = 1 + (rand() % (width - 1));
	fruitY = 1 + (rand() % (height - 1));
	score = 0;
}
void Draw()
{
	system("cls");
	for (int i = 0; i < width; ++i)
	{
		printf("#");
	}
	printf("\n");

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (i == fruitY & j == fruitX)
			{
				printf("f");
			}
			else if (i == y & j == x)
			{
				printf("O");
			}
			else if (j == 0)
			{
				printf("#");
			}
			else if (j == width - 1)
			{
				printf("#");
			}
			else
			{
				bool print = false;
				for (int k = 0; k < tailLen; ++k)
				{
					if (i == tailY[k] && j == tailX[k])
					{
						print = true;
						printf("o");
					}
				}
				if (!print)
				{
					printf(" ");
				}
			}
		}
		printf("\n");
	}

	for (int i = 0; i < width; ++i)
	{
		printf("#");
	}
	printf("\n");
	printf("Score: %d\n", score);
	printf("\n");
	printf("Use W,A,S,D for movement and Q for quit");
}
void Input()
{
	if (kbhit())     //Kbhit to know any key is pressed or not
	{
		switch (getch())
		{
		case 97:
			dir = LEFT;
			break;
		case 100:
			dir = RIGHT;
			break;
		case 119:
			dir = UP;
			break;
		case 115:
			dir = DOWN;
			break;
		case 113:
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLen; ++i)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
	default:
		break;
	}
	// if (x == width-1 || x == 0 || y == height || y < 0){
	// 	gameOver = true;
	// }
	if (x == width - 1)
	{
		x = 1;
	}
	else if (y == height)
	{
		y = 0;
	}
	else if (x == 0)
	{
		x = width - 2;
	}
	else if (y < 0)
	{
		y = height;
	}

	for (int i = 0; i < tailLen; ++i)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = 1 + (rand() % (width - 1));
		fruitY = 1 + (rand() % (height - 1));
		tailLen++;
	}
}
int main(int argc, char const *argv[])
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(80);
	}
	return 0;
}