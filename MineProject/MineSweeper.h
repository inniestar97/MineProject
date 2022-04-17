#pragma once
#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <typeinfo>
#include <conio.h>
#include <iomanip>
#include <fstream>

using std::string;
using std::unique_ptr;
using std::to_string;
using std::vector;

enum class isMine {
	MINE = 10,
	NOTHING = 0
};

class MineSweeper
{
private:
	int row = 0;
	int col = 0;
	int difficulty = 0;
	int mineCount = 0;
	unique_ptr<unique_ptr<string[]>[]> display;
	unique_ptr<unique_ptr<int[]>[]> func;
	vector<vector<vector<string>>> replay;

public:
	MineSweeper() = default; // ������
	~MineSweeper();
	MineSweeper(const MineSweeper& sweeper); // ���������
	MineSweeper(MineSweeper&& sweeper) noexcept; // �̵�������
	MineSweeper& operator=(const MineSweeper& sweeper); // ���� ������
	MineSweeper& operator=(MineSweeper&& sweeper) noexcept; // �̵����� ������

	void start();

	void init(); // ���� ���� row, col, difficulty, mineCount
	void initMap(); // �� �ʱ�ȭ
	bool loadGame(); // ����� ���� �ε�
	void restoreGame(); // ���� ����
	void drawMap() const; // �� �׸��� 
	bool gameOverIf() const; // ���� ���� ���� - �¸�
	void endGame() const; // ����, Ȥ�� �������� ���� â
	void recurExtension(int x ,int y); // Ȯ��
	void playGame();
	void replayGame();

	//  recurExtension -> ���� �Լ�
	void recurUpLeft(int x, int y); // ���� ��
	void recurUp(int x, int y); // ��
	void recurUpRight(int x, int y); // ������ ��
	void recurLeft(int x, int y); // ����
	void recurRight(int x, int y); // ������
	void recurDownLeft(int x, int y); // ���� �Ʒ�
	void recurDown(int x, int y); // �Ʒ�
	void recurDownRight(int x, int y); // ������ �Ʒ�
};

// Window API
void setCursorView(bool visible);
void gotoxy(int x, int y);
