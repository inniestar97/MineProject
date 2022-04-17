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
	MineSweeper() = default; // 생성자
	~MineSweeper();
	MineSweeper(const MineSweeper& sweeper); // 복사생성자
	MineSweeper(MineSweeper&& sweeper) noexcept; // 이동생성자
	MineSweeper& operator=(const MineSweeper& sweeper); // 대입 연산자
	MineSweeper& operator=(MineSweeper&& sweeper) noexcept; // 이동대입 연산자

	void start();

	void init(); // 변수 설정 row, col, difficulty, mineCount
	void initMap(); // 맵 초기화
	bool loadGame(); // 저장된 게임 로드
	void restoreGame(); // 게임 저장
	void drawMap() const; // 맵 그리기 
	bool gameOverIf() const; // 게임 종료 조건 - 승리
	void endGame() const; // 실패, 혹은 성공했을 때의 창
	void recurExtension(int x ,int y); // 확장
	void playGame();
	void replayGame();

	//  recurExtension -> 포함 함수
	void recurUpLeft(int x, int y); // 왼쪽 위
	void recurUp(int x, int y); // 위
	void recurUpRight(int x, int y); // 오른쪽 위
	void recurLeft(int x, int y); // 왼쪽
	void recurRight(int x, int y); // 오른쪽
	void recurDownLeft(int x, int y); // 왼쪽 아래
	void recurDown(int x, int y); // 아래
	void recurDownRight(int x, int y); // 오른쪽 아래
};

// Window API
void setCursorView(bool visible);
void gotoxy(int x, int y);
