#include "Student.h"

string Student::listName = "studentsMarks";

Student::Student() :fio(""), group(""), subjCount(0)
{
	subjectsMarks = 0;
	AddConsoleTextColor("Создан студент без информации");
}

Student::Student(string _fio, string _group) :fio(_fio), group(_group), subjCount(0)
{
	subjectsMarks = 0;
	AddConsoleTextColor("Студент " + fio + " добавлен без оценок");
}

Student::Student(string _fio, string _group, int _subjCount, SubjectMark * _subjectMarks) :fio(_fio), group(_group), subjCount(_subjCount)
{
	subjectsMarks = new SubjectMark[subjCount];
	for (int i = 0; i < subjCount; i++) {
		subjectsMarks[i] = _subjectMarks[i];
	}
	AddConsoleTextColor("Студент " + fio + " добавлен");
}

Student::Student(string _description)
{
	if (InitStudentFromString(_description)) {
		AddConsoleTextColor("Студент " + fio + " добавлен из строки");
	}
	else {
		AddConsoleTextColor("Ошибка добавления студента из строки: """ + _description + """", 12);
	}
}

Student::Student(const Student & ref) :fio(ref.fio), group(ref.group), subjCount(ref.subjCount)
{
	if (subjCount) {
		subjectsMarks = new SubjectMark[subjCount];
		for (int i = 0; i < subjCount; i++) {
			subjectsMarks[i] = ref.subjectsMarks[i];
		}
	}
	else
		subjectsMarks = 0;
	AddConsoleTextColor("Студент " + fio + " скопирован");
}

Student::~Student()
{
	delete[] subjectsMarks;
	AddConsoleTextColor("Студент " + fio + " удален");
}

bool Student::AddSubjectMark(string _subjectName, string _subjectMark)
{
	SubjectMark newSubjectMark = { _subjectName, _subjectMark };
	return AddSubjectMark(newSubjectMark);
}

bool Student::AddSubjectMark(SubjectMark _subjectMark)
{
	if (*this == _subjectMark) {
		return false;
	}
	*this += _subjectMark;
	return true;
}

string Student::GetFio() const
{
	return fio;
}

string Student::GetGroup() const
{
	return group;
}

int Student::GetSubjectMarkCount() const
{
	return subjCount;
}

SubjectMark * Student::GetAllSubjects()
{
	SubjectMark* _subjectsMarks = new SubjectMark[subjCount];
	for (int i = 0; i < subjCount; i++) {
		_subjectsMarks[i] = subjectsMarks[i];
	}
	return _subjectsMarks;
}

SubjectMark Student::GetSubjectMark(int number) const
{
	if (number < subjCount && number >= 0) {
		return subjectsMarks[number];
	}
	return SubjectMark();
}

SubjectMark Student::GetSubjectMark(string _subjectName) const
{
	if (subjCount > 0) {
		for (int i = 0; i < subjCount; i++) {
			if (subjectsMarks[i].subject == _subjectName) {
				return subjectsMarks[i];
			}
		}
	}
	return SubjectMark();
}

string Student::GetListName()
{
	return listName;
}

bool Student::SetFio(string _fio)
{
	fio = _fio;
	return true;
}

bool Student::SetGroup(string _group)
{
	group = _group;
	return true;
}

bool Student::SetAllSubjectMarks(int _subjCount, SubjectMark * _subjectsMarks)
{
	if (_subjCount > 0) {
		//создание копии на случай неудачного выполнения
		int tmpSubjCount = subjCount;
		SubjectMark * tmpSubjMarks = 0;
		if (tmpSubjCount > 0) {
			tmpSubjMarks = new SubjectMark[tmpSubjCount];
			for (int i = 0; i < tmpSubjCount; i++) {
				tmpSubjMarks[i] = subjectsMarks[i];
			}
			delete[] subjectsMarks;
			subjCount = 0;
		}
		for (int i = 0; i < _subjCount; i++) {
			if (AddSubjectMark(_subjectsMarks[i]) == false) {
				subjCount = tmpSubjCount;
				subjectsMarks = tmpSubjMarks;
				return false;
			}
		}
		if (tmpSubjCount > 0) {
			delete[] tmpSubjMarks;
		}
		return true;
	}
	else if (_subjCount = 0)
	{
		delete[] subjectsMarks;
		subjCount = 0;
	}
	AddConsoleTextColor("Ошибка добавления всех оценок!", 12);
	return false;
}

bool Student::SetAllSubjectMarks(string _subjectsMarks)
{
	//создание копии на случай неудачного выполнения
	int tmpSubjCount = subjCount;
	SubjectMark * tmpSubjMarks = 0;
	if (tmpSubjCount > 0) {
		tmpSubjMarks = new SubjectMark[tmpSubjCount];
		for (int i = 0; i < tmpSubjCount; i++) {
			tmpSubjMarks[i] = subjectsMarks[i];
		}
		delete[] subjectsMarks;
		subjCount = 0;
	}
	if (AddSubjectsMarksFromString(_subjectsMarks)) {
		if (tmpSubjCount > 0) {
			delete[] tmpSubjMarks;
		}
		return true;
	}
	else {
		if (tmpSubjCount > 0) {
			subjCount = tmpSubjCount;
			subjectsMarks = tmpSubjMarks;
		}
	}
	AddConsoleTextColor("Ошибка выставления новых оценок студента! Изменения отменены.", 12);
	return false;
}

bool Student::SetSubjectMark(SubjectMark _subjectMark, int number)
{
	if (number >= 0 && number < subjCount) {
		subjectsMarks[number] = _subjectMark;
		return true;
	}
	return false;
}

bool Student::SetSubjectMark(SubjectMark _subjectMark)
{
	for (int i = 0; i < subjCount; i++) {
		if (subjectsMarks[i].subject.compare(_subjectMark.subject) == 0) {
			subjectsMarks[i].mark = _subjectMark.mark;
			return true;
		}
	}
	return false;
}

void Student::SetListName(string _listName)
{
	listName = _listName;
}

void Student::Print() const
{
	AddConsoleTextColor("Студент: " + fio);
	AddConsoleTextColor("Группа: " + group);
	AddConsoleTextColor("ОЦЕНКИ");
	OutputTable *studentsMarks = CreateOutputTable();
	studentsMarks->columnsCount = 2;
	studentsMarks->rowsCount = subjCount + 1;
	studentsMarks->content = new string*[subjCount + 1];
	studentsMarks->content[0] = new string[2]{"ПРЕДМЕТ", "ОЦЕНКА"};
	for (int i = 0; i < subjCount; i++) {
		studentsMarks->content[i + 1] = new string[2]{subjectsMarks[i].subject, subjectsMarks[i].mark};
	}
	studentsMarks->highLightsCount = 1;
	studentsMarks->highLights = new string[1]{ "не зачет" };
	studentsMarks->highLightsColor = 12;
	if (AddConsoleTable(studentsMarks) == false)
	{
		for (int s = 0; s < subjCount; s++) {
			AddConsoleTextColor(subjectsMarks[s].subject + '-' + subjectsMarks[s].mark);
		}
	}
	KillOutputTable(studentsMarks);
}

string Student::ToString() const
{
	string res = "";
	res += "Студент: " + (fio.empty() ? "ИМЯ ОТСУТСТВУЕТ" : fio) + "; ";
	res += "Группа: " + (group.empty() ? "ГРУППА ОТСУТСТВУЕТ" : group) + "; ";
	res += "Оценки: ";
	if (subjCount) {
		for (int i = 0; i < subjCount; i++) {
			res += i > 0 ? ", " : "";
			res += (subjectsMarks[i].subject.empty() ? "ИМЯ ПРЕДМЕТА ОТСУТСТВУЕТ" : subjectsMarks[i].subject) + " - ";
			res += (subjectsMarks[i].mark.empty() ? "ОЦЕНКА ОТСУТСТВУЕТ" : subjectsMarks[i].mark);
		}
	}
	res += "; ";
	return res;
}

Student & Student::operator=(const Student & ref)
{
	if (this != &ref) {
		delete[] subjectsMarks;
		fio = ref.fio;
		group = ref.group;
		subjCount = ref.subjCount;
		subjectsMarks = new SubjectMark[subjCount];
		for (int i = 0; i < subjCount; i++) {
			subjectsMarks[i] = ref.subjectsMarks[i];
		}
	}
	return *this;
}

Student & Student::operator=(SubjectMark _subjectMark)
{
	if (SetSubjectMark(_subjectMark)) {
		return *this;
	}
	else {
		*this += _subjectMark;
	}
	return *this;
}

Student & Student::operator+=(SubjectMark _subjectMark)
{
	SubjectMark *newSubjectsMarks = new SubjectMark[subjCount + 1];
	if (subjCount > 0) {
		for (int i = 0; i < subjCount; i++) {
			newSubjectsMarks[i] = subjectsMarks[i];
		}
		delete[] subjectsMarks;
	}
	newSubjectsMarks[subjCount] = _subjectMark;
	subjCount++;
	subjectsMarks = newSubjectsMarks;
	return *this;
}

bool & Student::operator==(SubjectMark const _subjectMark) const
{
	bool isFound = false;
	int number = 0;
	while (isFound == false && number < subjCount)
	{
		isFound = _subjectMark.subject == subjectsMarks[number].subject;
		number++;
	}
	return isFound;
}

Student::operator bool() const
{
	if (fio.empty() == true) return false;
	if (group.empty() == true) return false;
	if (subjCount <= 0) return false;
	for (int i = 0; i < subjCount; i++)
	{
		if (subjectsMarks[i].subject.empty() == true) return false;
		if (subjectsMarks[i].mark.empty() == true) return false;
	}
	return true;
}

bool Student::InitStudentFromString(string student)
{
	int fioPos = -1, groupPos = -1, marksPos = -1, endPos = -1;
	fioPos = student.find("Студент: ") + 9;
	groupPos = student.find("; Группа: ", fioPos) + 10;
	marksPos = student.find("; Оценки: ", groupPos) + 10;
	endPos = student.find(';', marksPos);
	if (fioPos >= 9 && groupPos >= 10 && marksPos >= 10 && endPos >= 1)
	{
		fio = student.substr(fioPos, groupPos - 10 - fioPos);
		group = student.substr(groupPos, marksPos - 10 - groupPos);
		subjCount = 0;
		if (marksPos != endPos)
		{
			AddSubjectsMarksFromString(student.substr(marksPos, endPos - marksPos + 1));
		}
		return true;
	}
	else
	{
		AddConsoleTextColor("Ошибка распознавания строки!", 12);
		if (fioPos < 9) AddConsoleTextColor("Не найдено имя студента!", 12);
		if (groupPos < 10) AddConsoleTextColor("Не найдена группа студента!", 12);
		if (marksPos < 10) AddConsoleTextColor("На найдены оценки студента!", 12);
		if (endPos < 1) AddConsoleTextColor("Не найдено окончание строки!", 12);
	}
	return false;
}

bool Student::AddSubjectsMarksFromString(string subjects)
{
	int endPos = subjects.find(";");
	if (endPos > 0)
	{
		int nextPos = -2, newSubjectsCount = subjCount;
		do
		{
			newSubjectsCount++;
			nextPos = subjects.find(", ", nextPos + 2);
		} while (nextPos > 0);

		SubjectMark *newSubjects = new SubjectMark[newSubjectsCount];

		for (int i = 0; i < subjCount; i++) {
			newSubjects[i].mark = subjectsMarks[i].mark;
			newSubjects[i].subject = subjectsMarks[i].subject;
		}

		string strSubj = "";
		int prevPos = 0, partPos;
		nextPos = 0;
		for (int i = subjCount; i < newSubjectsCount; i++)
		{
			nextPos = subjects.find(", ", prevPos);
			nextPos = nextPos > 0 ? nextPos : endPos;
			strSubj = subjects.substr(prevPos, nextPos - prevPos);
			prevPos = nextPos + 2;
			partPos = strSubj.find(" - ");
			if (partPos > 0)
			{
				newSubjects[i].subject = strSubj.substr(0, partPos);
				newSubjects[i].mark = strSubj.substr(partPos + 3);
			}
			else
			{
				newSubjects[i].subject = strSubj;
				newSubjects[i].mark = "-";
			}
		}
		if(subjCount > 0) delete[] subjectsMarks;
		subjCount = newSubjectsCount;
		subjectsMarks = newSubjects;
		return true;
	}
	else {
		return false;
	}
}
