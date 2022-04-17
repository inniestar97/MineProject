#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>
#include "MineSweeper.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif //!DBG_NEW
#endif

int main(void) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand((size_t)time(NULL));

	MineSweeper sweeper;

	sweeper.start();


	return 0;
}

