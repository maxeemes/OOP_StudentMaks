#include "Zaochn.h"

Zaochn::Zaochn(): Student(), isPayed(false)
{
}

Zaochn::Zaochn(string _fio, string _group, int _subjCount, SubjectMark * _subjectMarks, bool _isPayed) : Student(_fio, _group, _subjCount, _subjectMarks), isPayed(_isPayed)
{
}

Zaochn::Zaochn(string _description): Student(_description)
{
	if(ParseIsPayed(_description) == false) 
		AddConsoleTextColor(
			"У студента " + 
			Student::GetFio() + 
			" не распознан статус оплаты, установлено значение: не оплачено", 
			12
		);
}

Zaochn::Zaochn(const Zaochn & ref):Student(ref), isPayed(ref.isPayed)
{
}

Zaochn & Zaochn::operator=(const Zaochn & right)
{
	Student::operator=(right);
	isPayed = right.isPayed;
	return *this;
}

void Zaochn::Print() const
{
	AddConsoleTextColor("Студент заочного отделения", 224);
	Student::Print();

	AddConsoleTextColor("Статус оплаты: " + string(isPayed ? "оплачено" : "не оплачено"), isPayed ? 10 : 12);
}

string Zaochn::ToString() const
{
	return Student::ToString() + "Статус оплаты: " + string(isPayed ? "оплачено" : "не оплачено") + "; ";
}

bool Zaochn::GetIsPayed() const
{
	return isPayed;
}

bool Zaochn::SetIsPayed(bool _isPayed)
{
	isPayed = _isPayed;
	return true;
}

bool Zaochn::ParseIsPayed(string _description)
{
	int startPos = -1, endPos = -1;
	startPos = _description.find("Статус оплаты: ") + 15;
	endPos = _description.find(";", startPos);
	if (endPos > 15) {
		string _isPayed = _description.substr(startPos, endPos - startPos);
		if (_isPayed == "оплачено") {
			isPayed = true;
			return true;
		}
		else if (_isPayed == "не оплачено")
		{
			isPayed = false;
			return true;
		}
	}
	return false;
}

