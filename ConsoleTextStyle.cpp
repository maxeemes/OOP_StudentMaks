#include "ConsoleTextStyle.h"
#include <iostream>
#include <windows.h>

const int consoleWidth = 120;

OutputTable * CreateOutputTable()
{
	OutputTable * outTable = new OutputTable();
	outTable->content = 0;
	outTable->columnsCount = 0;
	outTable->rowsCount = 0;
	outTable->highLights = 0;
	outTable->highLightsCount = 0;
	outTable->primaryColor = 7;
	outTable->headerColor = 14;
	outTable->highLightsColor = 12;
	return outTable;
}

bool KillOutputTable(OutputTable * outTable)
{
	for (int r = 0; r < outTable->rowsCount; r++) {
		delete[] outTable->content[r];
	}
	delete[] outTable->content;
	delete[] outTable->highLights;
	delete outTable;
	return true;
}

//Цвета: 7 - белый(стандартный), 10 - зеленый, 12 - красный, 14 - желтый, 224 - черный на желтом фоне
bool AddConsoleTextColor(const string _text, const int color)
{
	if (color == 7) {
		cout << _text << endl;
	}
	else {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
		cout << _text << endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
	return true;
}

bool AddConsoleTable(OutputTable * outTable)
{
	if (outTable->columnsCount <= 0 || outTable->columnsCount >= 29 || outTable->rowsCount <= 0 || outTable->rowsCount >= 9000) {
		AddConsoleTextColor("Ошибка отображения таблицы! Невозможно отобразить таблицу!", 12);
		return false;
	}
	//Объявление основных переменных
	//max width 120
	int *columsWidth = new int[outTable->columnsCount];
	int columnWidth = 0, sumColumsWidth = 0, spaceForColumnContent = consoleWidth - 1 - outTable->columnsCount;
	//Валидация таблицы
	for (int c = 0; c < outTable->columnsCount; c++) {
		columsWidth[c] = 0;
		for (int r = 0; r < outTable->rowsCount; r++) {
			columnWidth = outTable->content[r][c].length();
			columsWidth[c] = columnWidth > columsWidth[c] ? columnWidth : columsWidth[c];
		}
		if (columsWidth[c] <= 0) {
			delete[] columsWidth;
			AddConsoleTextColor("Ошибка отображения таблицы! В колонке номер " + to_string(c + 1) + " все значения пустые!", 12);
			return false;
		}
		sumColumsWidth += columsWidth[c];
	}
	//Масштабирование размеров колонок под размер консоли
	if (sumColumsWidth > spaceForColumnContent) {
		int newColumnWidth = 0;
		for (int c = 0; c < outTable->columnsCount; c++) {
			newColumnWidth = columsWidth[c] * 100 / sumColumsWidth * spaceForColumnContent / 100;
			if (newColumnWidth >= 3 && (spaceForColumnContent - newColumnWidth) > ((outTable->columnsCount - c - 1) * 3)) {
				columsWidth[c] = newColumnWidth;
			}
			else if (columsWidth[c] <= newColumnWidth) {
				columsWidth[c] = newColumnWidth;
			}
			else if ((spaceForColumnContent - newColumnWidth) < ((outTable->columnsCount - c - 1) * 3)) {
				spaceForColumnContent -= 3 - newColumnWidth;
				columsWidth[c] = 3;
			}
			else {
				AddConsoleTextColor("Ошибка отображения таблицы! Колонка номер " + to_string(c + 1) + " слишком большая!", 12);
				return false;
			}
		}
		sumColumsWidth = spaceForColumnContent;
	}
	//подготовка к отображению
	sumColumsWidth += 1 + outTable->columnsCount;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, outTable->headerColor);
	cout.fill('_');
	cout.width(sumColumsWidth);
	cout << "" << endl;
	//Отображение заголовка таблицы
	cout.width();
	cout << "|";
	for (int r = 0, c = 0; c < outTable->columnsCount; c++) {
		cout.width(columsWidth[c]);
		cout << left << outTable->content[r][c].substr(0, columsWidth[c]);
		cout.width();
		cout << "|";
	}
	cout << endl;
	//отображение тела таблицы
	SetConsoleTextAttribute(hConsole, outTable->primaryColor);
	for (int r = 1; r < outTable->rowsCount; r++) {
		cout.width();
		cout << "|";
		for (int c = 0; c < outTable->columnsCount; c++) {
			cout.width(columsWidth[c]);
			if (outTable->highLightsCount > 0) {
				bool isFound = false;
				int h = 0;
				do {
					isFound = outTable->content[r][c] == outTable->highLights[h];
					h++;
				} while (isFound == false && h < outTable->highLightsCount);
				if (isFound) {
					SetConsoleTextAttribute(hConsole, outTable->highLightsColor);
					cout << left << outTable->content[r][c].substr(0, columsWidth[c]);
					SetConsoleTextAttribute(hConsole, outTable->primaryColor);
				}
				else {
					cout << left << outTable->content[r][c].substr(0, columsWidth[c]);
				}
			}
			else {
				cout << left << outTable->content[r][c].substr(0, columsWidth[c]);
			}
			cout.width();
			cout << "|";
		}
		cout << endl;
	}
	//Возвращение исходных настроек
	cout.fill('-');
	cout.width(sumColumsWidth);
	cout << "" << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout.fill();
	return true;
}
