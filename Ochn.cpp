#include "Ochn.h"

Ochn::Ochn() : Zaochn(), isBudget(false)
{
}

Ochn::Ochn(string _fio, string _group, int _subjCount, SubjectMark * _subjectMarks, bool _isBudget, bool _isPayed) : Zaochn(_fio, _group, _subjCount, _subjectMarks, _isPayed), isBudget(_isBudget) {}

Ochn::Ochn(string _description): Zaochn(_description)
{
	if(ParseIsBudget(_description) == false) 
		AddConsoleTextColor(
			"Не разпознана форма обучения, установлено значение: коммерция", 
			12
		);
	if (isBudget) {
		SetIsPayed(true);
	}
}

Ochn::Ochn(const Ochn & ref) : isBudget(ref.isBudget)
{
	Student::Student(ref);
	if (isBudget) {
		SetIsPayed(true);
	}
	else
	{
		SetIsPayed(ref.GetIsPayed());
	}
}

Ochn & Ochn::operator=(const Ochn & right)
{
	Zaochn::operator=(right);
	isBudget = right.isBudget;
	return *this;
}

void Ochn::Print() const
{
	AddConsoleTextColor("Студент очного отделения", 224);
	Student::Print();
	if (isBudget) {
		AddConsoleTextColor("Форма обучения: бюджет", 10);
	}
	else
	{
		AddConsoleTextColor("Форма обучения: коммерция");
		AddConsoleTextColor("Статус оплаты: " + string(GetIsPayed() ? "оплачено" : "не оплачено"), GetIsPayed() ? 10 : 12);
	}
}

string Ochn::ToString() const
{
	string res = Student::ToString();
	if (isBudget) {
		res += "Форма обучения: бюджет; ";
	}
	else
	{
		res = res + "Статус оплаты: " + string(GetIsPayed() ? "оплачено" : "не оплачено") + "; ";
		res += "Форма обучения: коммерция; ";
	}
	return res;
}

bool Ochn::GetIsBudget() const
{
	return isBudget;
}

bool Ochn::SetIsBudget(bool _isBudget)
{
	isBudget = _isBudget;
	return true;
}

bool Ochn::ParseIsBudget(string _description)
{
	int startPos = -1, endPos = -1;
	startPos = _description.find("Форма обучения: ") + 16;
	endPos = _description.find(";", startPos);
	if (endPos > 16)
	{
		string _isBudget = _description.substr(startPos, endPos - startPos);
		if (_isBudget == "бюджет") {
			isBudget = true;
			return true;
		}
		else if (_isBudget == "коммерция")
		{
			isBudget = false;
			return true;
		}
	}
	return false;
}
