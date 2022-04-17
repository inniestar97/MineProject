#include "MineSweeper.h"

using std::cout;
using std::cin;
using std::endl;
using std::make_unique;
using std::ofstream;
using std::ifstream;
using std::stoi;
using std::make_pair;

MineSweeper::~MineSweeper()
{
}

MineSweeper::MineSweeper(const MineSweeper& sweeper)
	:row(sweeper.row), col(sweeper.col), difficulty(sweeper.difficulty), mineCount(sweeper.mineCount)
{
	// 복사 생성자
	display = make_unique<unique_ptr<string[]>[]>(row);
	for (size_t i = 0; i < row; i++) {
		display[i] = make_unique<string[]>(col);
		for (size_t j = 0; j < col; j++) {
			display[i][j] = sweeper.display[i][j];
		}
	}

	func = make_unique<unique_ptr<int[]>[]>(row);
	for (size_t i = 0; i < row; i++) {
		func[i] = make_unique<int[]>(col);
		for (size_t j = 0; j < col; j++) {
			func[i][j] = sweeper.func[i][j];
		}
	}
}

MineSweeper::MineSweeper(MineSweeper&& sweeper) noexcept
	:row(sweeper.row), col(sweeper.col), difficulty(sweeper.difficulty), mineCount(sweeper.mineCount)
{
	display = move(sweeper.display);
	func = move(sweeper.func);
}

MineSweeper& MineSweeper::operator=(const MineSweeper& sweeper)
{
	if (&sweeper == this) {
		return *this;
	}
	row = sweeper.row;
	col = sweeper.col;
	difficulty = sweeper.difficulty;
	mineCount = sweeper.mineCount;

	display = make_unique<unique_ptr<string[]>[]>(row);
	for (size_t i = 0; i < row; i++) {
		display[i] = make_unique<string[]>(col);
		for (size_t j = 0; j < col; j++) {
			display[i][j] = sweeper.display[i][j];
		}
	}

	func = make_unique<unique_ptr<int[]>[]>(row);
	for (size_t i = 0; i < row; i++) {
		func[i] = make_unique<int[]>(col);
		for (size_t j = 0; j < col; j++) {
			func[i][j] = sweeper.func[i][j];
		}
	}

	return *this;
}

MineSweeper& MineSweeper::operator=(MineSweeper&& sweeper) noexcept
{
	if (&sweeper == this) {
		return *this;
	}
	row = sweeper.row;
	col = sweeper.col;
	difficulty = sweeper.difficulty;
	mineCount = sweeper.mineCount;

	display = move(sweeper.display);
	func = move(sweeper.func);

	return *this;
}

void MineSweeper::init()
{
	while (true) {
		cout << endl;
		cout << "-----------------------------------" << endl;;
		cout << "Set Map of Row ( 5 <= row <= 15 ) : ";
		cin >> row;

		if (row >= 5 && row <= 15) {
			// 범위와 타입이 맞을경우
			break;
		}
		while (getchar() != '\n');

		cout << "Out of Bound or Type Different." << endl;
		cout << endl;
	}

	while (true) {
		cout << endl;
		cout << "-----------------------------------" << endl;
		cout << "Set Map of Col ( 5 <= col <= 15 ) : ";
		cin >> col;

		if (col >= 5 && col <= 15) {
			break;
		}
		while (getchar() != '\n');

		cout << "Out of Bound or Type Different." << endl;
		cout << endl;
	}

	cout << endl;
	cout << row << " x " << col << " Size Map Loaded." << endl;
	Sleep(1000);
	cout << endl;

	while (true) {
		cout << "-----------------------------------" << endl;
		cout << "Choose the Difficulty." << endl;
		cout << "(1) Easy\t(2) Normal\t(3) Hard" << endl;
		cout << "Choose the Number : ";
		cin >> difficulty;

		if (difficulty >= 1 && difficulty < 3) {
			break;
		}
		while (getchar() != '\n');

		cout << "Check your Difficulty Number or Type." << endl;
		cout << endl;
	}

	system("cls");
	cout << "202011334 이상인" << endl << endl;
	switch (difficulty) {
	case 1:
		cout << "Difficulty : \"Easy\" mode." << endl;
		mineCount = row * col * (1.f / 10);
		break;
	case 2:
		cout << "Difficulty : \"Normal\" mode." << endl;
		mineCount = row * col * (2.f / 10);
		break;
	case 3:
		cout << "Difficulty : \"Hard\" mode." << endl;
		mineCount = row * col * (3.f / 10);
		break;
	 

	cout << "Mine : " << mineCount << endl;
	Sleep(1000);
	system("cls");
	// 사용자의 의도 -> 맵의 크기, 난이도 설정 완료.
}


void MineSweeper::initMap()
{
	// bluePrint 맵 생성
	func = make_unique<unique_ptr<int[]>[]>(row);
	for (size_t i = 0; i < row; i++) {
		func[i] = make_unique<int[]>(col);
		for (size_t j = 0; j < col; j++) {
			func[i][j] = static_cast<int>(isMine::NOTHING);
		}
	}

	// 맵 생성
	display = make_unique<unique_ptr<string[]>[]>(row);
	for (size_t i = 0; i < row; i++) {
		display[i] = make_unique<string[]>(col);
		for (size_t j = 0; j < col; j++) {
			display[i][j] = "■";
		}
	}

	int mine = static_cast<int>(isMine::MINE); // mine = 10
	// 지뢰 심기
	for (size_t i = 0; i < mineCount; i++) {
		int r_x = rand() % row;
		int r_y = rand() % col;
		if (func[r_x][r_y] != mine) {
			func[r_x][r_y] = mine;
		}
		else {
			i--;
		}
	}

	// 힌트 심기
	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < col; j++) {
			if (func[i][j] == mine) {
				if (i != 0 && func[i - 1][j] != mine) {
					func[i - 1][j] == 0 ? func[i - 1][j] = 1 : func[i - 1][j]++;
				}
				if (i + 1 < row && func[i + 1][j] != mine) {
					func[i + 1][j] == 0 ? func[i + 1][j] = 1 : func[i + 1][j]++;
				}
				if (j != 0 && func[i][j - 1] != mine) {
					func[i][j - 1] == 0 ? func[i][j - 1] = 1 : func[i][j - 1]++;
				}
				if (j + 1 < col && func[i][j + 1] != mine) {
					func[i][j + 1] == 0 ? func[i][j + 1] = 1 : func[i][j + 1]++;
				}
				if (i != 0 && j != 0 && func[i - 1][j - 1] != mine) {
					func[i - 1][j - 1] == 0 ? func[i - 1][j - 1] = 1 : func[i - 1][j - 1]++;
				}
				if (i != 0 && j + 1 < col && func[i - 1][j + 1] != mine) {
					func[i - 1][j + 1] == 0 ? func[i - 1][j + 1] = 1 : func[i - 1][j + 1]++;
				}
				if (i + 1 < row && j != 0 && func[i + 1][j - 1] != mine) {
					func[i + 1][j - 1] == 0 ? func[i + 1][j - 1] = 1 : func[i + 1][j - 1]++;
				}
				if (i + 1 < row && j + 1 < col && func[i + 1][j + 1] != mine) {
					func[i + 1][j + 1] == 0 ? func[i + 1][j + 1] = 1 : func[i + 1][j + 1]++;
				}
			}
		}
	}
}

bool MineSweeper::loadGame()
{
	ifstream fin("data.txt");

	if (fin.fail()) {
		cout << "There is No Load File" << endl;
		return false;
	}

	fin >> row;
	fin >> col;
	fin >> difficulty;
	fin >> mineCount;

	fin.get();

	if (display == nullptr && func == nullptr) {
		display = make_unique<unique_ptr<string[]>[]>(row);
		for (size_t i = 0; i < row; i++) {
			display[i] = make_unique<string[]>(col);
		}

		func = make_unique<unique_ptr<int[]>[]>(row);
		for (size_t i = 0; i < row; i++) {
			func[i] = make_unique<int[]>(col);
		}
	}

	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < col; j++) {
			char idx[3] = "";
			fin.get(idx[0]);
			fin.get(idx[1]);
			idx[2] = 0;

			int x = stoi(idx);
			func[i][j] = x;
		}
	}

	fin.get();
	cout << endl;

	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < col; j++) {
			string xx = "";
			fin >> xx;
			if (xx.length() == 1) {
				xx = " " + xx;
			}

			display[i][j] = xx;
		}
	}

	int count = 0;
	fin >> count;

	// vector 에서 저장값 불러오기
	for (size_t k = 0; k < count; k++) {
		vector<vector<string>> arr;
		for (size_t i = 0; i < row; i++) {
			vector<string> arr_under;
			for (size_t j = 0; j < col; j++) {
				string str;
				fin >> str;
				if (str.length() == 1) {
					str = " " + str;
				}
				arr_under.push_back(str);
			}
			arr.push_back(arr_under);
		}
		replay.push_back(arr);
	}

}

void MineSweeper::restoreGame()
{
	string data = "data.txt";

	ofstream fout(data);
	if (!fout.is_open()) {
		cout << "Fail to Write Storing File" << endl;
	}
	else {
		fout << row << " " << col << endl;;
		fout << difficulty << endl;
		fout << mineCount << endl;

		for (size_t i = 0; i < row; i++) {
			for (size_t j = 0; j < col; j++) {
				fout << std::right << std::setw(2) << func[i][j];
			}
		}
		fout << endl;

		for (size_t i = 0; i < col; i++) {
			for (size_t j = 0; j < col; j++) {
				fout << display[i][j] << " ";
			}
		}
		fout << endl;

		fout << replay.size();
		fout << endl;
		for (const auto& it : replay) {
			for (const auto& it2 : it) {
				for (const auto& it3 : it2) {
					fout << it3 << " ";
				}
			}
			fout << endl;
		}

	}
	fout.close();

	gotoxy(10, 5 + row + 1);
	cout << "It has been Restored";
	Sleep(1000);
	system("cls");
}

void MineSweeper::start()
{
	cout << "202011334 이상인" << endl << endl;;
	cout << "------MINE SWEEPER------" << endl;
	cout << "please any key to continue..." << endl;
	char nothing = _getch();
	system("cls");

	while (true) {
		while (true) {
			cout << "202011334 이상인" << endl << endl;
			cout << "New Game : (N)" << endl;
			cout << "Load Your Game : (L)" << endl;
			char choice;
			cout << "Choose the Game : ";
			cin >> choice;


			if (choice == 'n' || choice == 'N') { // 게임 처음 시작
				cout << endl;
				cout << "-----------New Game-----------" << endl;
				init(); // 맵 크기, 난이도 설정
				initMap(); // 맵 동적할당
				break;
			}
			else if (choice == 'l' || choice == 'L') { // 저장된 게임 로드
				if (loadGame()) {
					cout << endl;
					cout << "-----------Load Game-----------" << endl;
					cout << "Game is Loading ........" << endl;
					Sleep(1500);
					cout << "Load is Compleate!" << endl;
					Sleep(1000);
					system("cls");
					break;
				}
				else {
					continue;
				}
			}
			else {
				cout << "Check Your Answer!" << endl;
				while (getchar() != '\n');
			}
			Sleep(500);
			system("cls");
		}

		playGame();

		char reOrQuit;
		while (true) {
			gotoxy(10, 5 + row + 7);
			cout << "ReGame (Press key 'r')";
			gotoxy(10, 5 + row + 8);
			cout << "Quit (Press key 'q')";

			cin >> reOrQuit;
			if (reOrQuit == 'r' || reOrQuit == 'q') {
				break;
			}
			while (getchar() != '\n');
		}

		if (reOrQuit == 'r') {
			system("cls");
			replay.clear();
			continue;
		}
		else if (reOrQuit == 'q')
			break;
	}
	
	cout << endl;
}

void MineSweeper::drawMap() const
{
	gotoxy(0, 0);
	cout << "202011334 이상인" << endl;
	for (size_t i = 0; i < row; i++) {
		gotoxy(10, 5 + i);
		for (size_t j = 0; j < col; j++) {
			cout << display[i][j];
		}
		cout << endl;
	}

	for (size_t i = 0; i < row; i++) {
		gotoxy(50, 5 + i);
		for (size_t j = 0; j < col; j++) {
			cout << std::right << std::setw(2) << func[i][j];
		}
		cout << endl;
	}

	gotoxy(10, 5 + row + 5);
	cout << "Up : ↑\tDown : ↓";
	gotoxy(10, 5 + row + 6);
	cout << "Left : ←\tRight : →";
	gotoxy(10, 5 + row + 7);
	cout << "OPEN : (key - space bar)";
	gotoxy(10, 5 + row + 8);
	cout << "FLAG (key - 'f') : ★";
	gotoxy(10, 5 + row + 9);
	cout << "MINE : ※";
	gotoxy(10, 5 + row + 10);
	cout << "RESTORE AND BACK TO MENU : (key - 'r')";
}

bool MineSweeper::gameOverIf() const
{
	int count = 0;
	int count_2 = 0;
	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < col; j++) {
			if (func[i][j] == static_cast<int>(isMine::MINE)
				&& display[i][j] == "★") { // 모든 지뢰를 다 찾은경우
				count++;
			}

			if (func[i][j] != static_cast<int>(isMine::MINE)
				&& display[i][j] != "■") { // 모든 지뢰를 찾진 않았지만 다른곳을 모두 열람한경우
				count_2++;
			}
		}
	}

	if (count == mineCount || count_2 == (row * col) - mineCount) {
		return true;
	}

	return false;
}

void MineSweeper::endGame() const
{
	gotoxy(0, 0);
	cout << "202011334 이상인" << endl;
	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < col; j++) {
			if (func[i][j] == static_cast<int>(isMine::MINE)) {
				display[i][j] = "※";
			}
		}
	}

	for (size_t i = 0; i < row; i++) {
		gotoxy(10, 5 + i);
		for (size_t j = 0; j < col; j++) {
			cout << display[i][j];
		}
		cout << endl;
	}
}

void MineSweeper::recurExtension(int x, int y)
{
	recurUpLeft(x, y);
	recurUp(x, y);
	recurUpRight(x, y);
	recurLeft(x, y);
	recurRight(x, y);
	recurDownLeft(x, y);
	recurDown(x, y);
	recurDownRight(x, y);
}

void MineSweeper::playGame()
{
	int x, y;
	x = 10;
	y = 5;
	drawMap();
	bool isWin;

	// --------------------- 커서 이동과 클릭 --------------------- //
	while (true) {

		isWin = false;
		gotoxy(x, y);

		// 키 입력
		int input = _getch();
		if (input == 224) { // 방향키 입력시
			switch (_getch()) {
			case 72:
				y -= 1;
				if (y < 5) { y = 5; }
				break;
			case 80:
				y += 1;
				if (y > 5 + row - 1) { y = 5 + row - 1; }
				break;
			case 75:
				x -= 2;
				if (x < 10) { x = 10; }
				break;
			case 77:
				x += 2;
				if (x > 10 + col * 2 - 1) { x = 10 + col * 2 - 2; }
				break;
			}
		}
		else if (input == 32) { // 스페이스 입력시

			if (func[y - 5][(x - 10) / 2] == static_cast<int>(isMine::MINE)
				&& display[y - 5][(x - 10) / 2] != "★") {
				// 지뢰를 골랐을 시
				system("cls");
				gotoxy(10, 5);
				endGame();

				vector<vector<string>> array1;
				for (size_t i = 0; i < row; i++) {
					vector<string> array2;
					for (size_t j = 0; j < col; j++) {
						array2.push_back(display[i][j]);
					}
					array1.push_back(array2);
				}
				replay.push_back(array1);

				gotoxy(10, 5 + row + 5);
				cout << "You Catch Mine. You Lose. Game Over" << endl;
				Sleep(2000);
				replayGame();
				gotoxy(10, 5 + row + 6);
				cout << "Please any key to continue..." << endl;
				if (_getch()) {
					break;
				}
			}
			else if (display[y - 5][(x - 10) / 2] != "■") {
				// 아무것도 하지 않는다.
			}
			else if (func[y - 5][(x - 10) / 2] != static_cast<int>(isMine::MINE)) {
				// 지뢰가 아닌곳을 선택하는 경우
				// 8방향 재귀호출 
				if (func[y - 5][(x - 10) / 2] > 0) {
					display[y - 5][(x - 10) / 2] = " " + to_string(func[y - 5][(x - 10) / 2]);
				}
				else {
					display[y - 5][(x - 10) / 2] = "□";
				}
				recurExtension(y - 5, (x - 10) / 2);
				drawMap();
			}
			else if (display[y - 5][(x - 10) / 2] == "★"
				&& func[y - 5][(x - 10) / 2] == static_cast<int>(isMine::MINE)) {
				// 지뢰를 찾은경우 -> 찾은 지뢰를 다시 누른경우 반응이 없다.
				continue;
			}

			// push back replay
			vector<vector<string>> array1;
			for (size_t i = 0; i < row; i++) {
				vector<string> array2;
				for (size_t j = 0; j < col; j++) {
					array2.push_back(display[i][j]);
				}
				array1.push_back(array2);
			}

			replay.push_back(array1);
		}
		else if (input == static_cast<int>('f')) {

			if (display[y - 5][(x - 10) / 2] == "■") // 지뢰 선택
				display[y - 5][(x - 10) / 2] = "★";
			else if (display[y - 5][(x - 10) / 2] == "★") // 선택된 지뢰 취소
				display[y - 5][(x - 10) / 2] = "■";
			drawMap();
			
			//replay push_back
			vector<vector<string>> array1;
			for (size_t i = 0; i < row; i++) {
				vector<string> array2;
				for (size_t j = 0; j < col; j++) {
					array2.push_back(display[i][j]);
				}
				array1.push_back(array2);
			}

			replay.push_back(array1);
		}
		else if (input == static_cast<int>('r')) {
			// 게임 저장
			restoreGame();
			break;
		}
		// --------------------------------------------------------------- //

		isWin = gameOverIf(); // 게임 종료조건

		if (isWin) {
			endGame();
			gotoxy(10, 5 + row + 3);
			cout << "You Win!!" << endl;
			Sleep(2000);
			replayGame();
			gotoxy(10, 5 + row + 6);
			cout << "Please any key to continue..." << endl;
			if (_getch()) {
				break;
			}
		}
	}
}

void MineSweeper::replayGame()
{
	system("cls");
	for (const auto& it : replay) {
		system("cls");
		gotoxy(0, 0);
		cout << "202011334 이상인" << endl;
		for (size_t i = 0; i < it.size(); i++) {
			gotoxy(10, 5 + i);
			for (size_t j = 0; j < it[i].size(); j++) {
				cout << it[i][j];
			}
			gotoxy(10, 5 + row + 5);
			cout << "RePlaying...";
		}
		Sleep(1000);
	}
	gotoxy(10, 5 + row + 5);
	cout << "Game is Done...";
}


void MineSweeper::recurUpLeft(int x, int y)
{
	if (x - 1 == -1 || y - 1 == -1 || func[x - 1][y - 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x - 1 == -1 || func[x - 1][y] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (y - 1 == -1 || func[x][y - 1] == static_cast<int>(isMine::MINE)) {
		return;
	}

	func[x - 1][y] > 0 ? (display[x - 1][y] = " " + to_string(func[x - 1][y])) : display[x - 1][y] = "□";
	func[x - 1][y - 1] > 0 ? (display[x - 1][y - 1] = " " + to_string(func[x - 1][y - 1])) : display[x - 1][y - 1] = "□";
	func[x][y - 1] > 0 ? (display[x][y - 1] = " " + to_string(func[x][y - 1])) : display[x][y - 1] = "□";

	recurUpLeft(x - 1, y - 1);
}

void MineSweeper::recurUp(int x, int y)
{
	if (x - 1 == -1 || func[x - 1][y] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x - 1 == -1 || y - 1 == -1 || func[x - 1][y - 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x - 1 == -1 || y + 1 == col || func[x - 1][y + 1] == static_cast<int>(isMine::MINE)) {
		return;
	}

	func[x - 1][y] > 0 ? (display[x - 1][y] = " " + to_string(func[x - 1][y])) : display[x - 1][y] = "□";
	func[x - 1][y - 1] > 0 ? (display[x - 1][y - 1] = " " + to_string(func[x - 1][y - 1])) : display[x - 1][y - 1] = "□";
	func[x - 1][y + 1] > 0 ? (display[x - 1][y + 1] = " " + to_string(func[x - 1][y + 1])) : display[x - 1][y + 1] = "□";

	recurUp(x - 1, y);
}

void MineSweeper::recurUpRight(int x, int y) 
{
	if (x - 1 == -1 || y + 1 == col || func[x - 1][y + 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x - 1 == -1 || func[x - 1][y] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (y + 1 == col || func[x][y + 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	
	func[x - 1][y] > 0 ? (display[x - 1][y] = " " + to_string(func[x - 1][y])) : display[x - 1][y] = "□";
	func[x - 1][y + 1] > 0 ? (display[x - 1][y + 1] = " " + to_string(func[x - 1][y + 1])) : display[x - 1][y + 1] = "□";
	func[x][y + 1] > 0 ? (display[x][y + 1] = " " + to_string(func[x][y + 1])) : display[x][y + 1] = "□";

	recurUpRight(x - 1, y + 1);
}

void MineSweeper::recurLeft(int x, int y) {
	if (y - 1 == -1 || func[x][y - 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x - 1 == -1 || y - 1 == -1 || func[x - 1][y - 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x + 1 == row || y - 1 == -1 || func[x + 1][y - 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	
	func[x][y - 1] > 0 ? (display[x][y - 1] = " " + to_string(func[x][y - 1])) : display[x][y - 1] = "□";
	func[x - 1][y - 1] > 0 ? (display[x - 1][y - 1] = " " + to_string(func[x - 1][y - 1])) : display[x - 1][y - 1] = "□";
	func[x + 1][y - 1] > 0 ? (display[x + 1][y - 1] = " " + to_string(func[x + 1][y - 1])) : display[x + 1][y - 1] = "□";

	recurLeft(x, y - 1);
}

void MineSweeper::recurRight(int x, int y) 
{
	if (y + 1 == col || func[x][y + 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x - 1 == -1 || y + 1 == col || func[x - 1][y + 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x + 1 == row || y + 1 == col || func[x + 1][y + 1] == static_cast<int>(isMine::MINE)) {
		return;
	}

	func[x][y + 1] > 0 ? (display[x][y + 1] = " " + to_string(func[x][y + 1])) : display[x][y + 1] = "□";
	func[x - 1][y + 1] > 0 ? (display[x - 1][y + 1] = " " + to_string(func[x - 1][y + 1])) : display[x - 1][y + 1] = "□";
	func[x + 1][y + 1] > 0 ? (display[x + 1][y + 1] = " " + to_string(func[x + 1][y + 1])) : display[x + 1][y + 1] = "□";

	recurRight(x, y + 1);
}

void MineSweeper::recurDownLeft(int x, int y) 
{
	if (x + 1 == row || y - 1 == -1 || func[x + 1][y - 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (y - 1 == -1 || func[x][y - 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x + 1 == row || func[x + 1][y] == static_cast<int>(isMine::MINE)) {
		return;
	}

	func[x + 1][y - 1] > 0 ? (display[x + 1][y - 1] = " " + to_string(func[x + 1][y - 1])) : display[x + 1][y - 1] = "□";
	func[x][y - 1] > 0 ? (display[x][y - 1] = " " + to_string(func[x][y - 1])) : display[x][y - 1] = "□";
	func[x + 1][y] > 0 ? (display[x + 1][y] = " " + to_string(func[x + 1][y])) : display[x + 1][y] = "□";

	recurDownRight(x + 1, y - 1);
}

void MineSweeper::recurDown(int x, int y) {
	if (x + 1 == row || func[x + 1][y] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x + 1 == row || y - 1 == -1 || func[x + 1][y - 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x + 1 == row || y + 1 == col || func[x + 1][y + 1] == static_cast<int>(isMine::MINE)) {
		return;
	}

	func[x + 1][y] > 0 ? (display[x + 1][y] = " " + to_string(func[x + 1][y])) : display[x + 1][y] = "□";
	func[x + 1][y - 1] > 0 ? (display[x + 1][y - 1] = " " + to_string(func[x + 1][y - 1])) : display[x + 1][y - 1] = "□";
	func[x + 1][y + 1] > 0 ? (display[x + 1][y + 1] = " " + to_string(func[x + 1][y + 1])) : display[x + 1][y + 1] = "□";

	recurDown(x + 1, y);
}

void MineSweeper::recurDownRight(int x, int y) {
	if (x + 1 == row || y + 1 == col || func[x + 1][y + 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (y + 1 == col || func[x][y + 1] == static_cast<int>(isMine::MINE)) {
		return;
	}
	if (x + 1 == row || func[x + 1][y] == static_cast<int>(isMine::MINE)) {
		return;
	}

	func[x + 1][y + 1] > 0 ? (display[x + 1][y + 1] = " " + to_string(func[x + 1][y + 1])) : display[x + 1][y + 1] = "□";
	func[x][y + 1] > 0 ? (display[x][y + 1] = " " + to_string(func[x][y + 1])) : display[x][y + 1] = "□";
	func[x + 1][y] > 0 ? (display[x + 1][y] = " " + to_string(func[x + 1][y])) : display[x + 1][y] = "□";

	recurDownRight(x + 1, y + 1);
}

void setCursorView(bool visible)
{
	CONSOLE_CURSOR_INFO cursor = { 1, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
