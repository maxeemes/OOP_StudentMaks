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
//÷вета: 7 - белый(стандартный), 10 - зеленый, 12 - красный, 14 - желтый, 224 - черный на желтом фоне
bool AddConsoleTextColor(const string _text, const int color = 7);
bool AddConsoleTable(OutputTable * outTable);

#endif