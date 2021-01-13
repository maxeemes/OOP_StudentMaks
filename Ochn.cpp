#include "Ochn.h"

Ochn::Ochn() : Zaochn(), isBudget(false)
{
}

Ochn::Ochn(string _fio, string _group, int _subjCount, SubjectMark * _subjectMarks, bool _isBudget, bool _isPayed) : Zaochn(_fio, _group, _subjCount, _subjectMarks, _isPayed), isBudget(_isBudget) {}

Ochn::Ochn(string _description): Zaochn(_description)
{
	if(ParseIsBudget(_description) == false) 
		AddConsoleTextColor(
			"�� ���������� ����� ��������, ����������� ��������: ���������", 
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
	AddConsoleTextColor("������� ������ ���������", 224);
	Student::Print();
	if (isBudget) {
		AddConsoleTextColor("����� ��������: ������", 10);
	}
	else
	{
		AddConsoleTextColor("����� ��������: ���������");
		AddConsoleTextColor("������ ������: " + string(GetIsPayed() ? "��������" : "�� ��������"), GetIsPayed() ? 10 : 12);
	}
}

string Ochn::ToString() const
{
	string res = Student::ToString();
	if (isBudget) {
		res += "����� ��������: ������; ";
	}
	else
	{
		res = res + "������ ������: " + string(GetIsPayed() ? "��������" : "�� ��������") + "; ";
		res += "����� ��������: ���������; ";
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
	startPos = _description.find("����� ��������: ") + 16;
	endPos = _description.find(";", startPos);
	if (endPos > 16)
	{
		string _isBudget = _description.substr(startPos, endPos - startPos);
		if (_isBudget == "������") {
			isBudget = true;
			return true;
		}
		else if (_isBudget == "���������")
		{
			isBudget = false;
			return true;
		}
	}
	return false;
}
