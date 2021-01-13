#include<string>
#ifndef CONSOLETEXTSTYLE_H
#define CONSOLETEXTSTYLE_H

using namespace std;
struct OutputTable
{
	string **content;
	int columnsCount;
	int rowsCount;
	string *highLights;
	int highLightsCount;
	int primaryColor;
	int headerColor;
	int highLightsColor;
};
OutputTable *CreateOutputTable();
bool KillOutputTable(OutputTable * outTable);
//�����: 7 - �����(�����������), 10 - �������, 12 - �������, 14 - ������, 224 - ������ �� ������ ����
bool AddConsoleTextColor(const string _text, const int color = 7);
bool AddConsoleTable(OutputTable * outTable);

#endif