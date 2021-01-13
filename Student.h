#include<string>
#include "ConsoleTextStyle.h"

#ifndef STUDENT_H
#define STUDENT_H

using namespace std;
struct SubjectMark {
	string subject;
	string  mark;
};

class Student {
public:
	Student();
	Student(string _fio, string _group);
	Student(string _fio, string _group, int _subjCount, SubjectMark *_subjectMarks);
	Student(string _description);
	Student(const Student &ref);
	~Student();

	//добавление оценок
	bool AddSubjectMark(string _subjectName, string _subjectMark);
	bool AddSubjectMark(SubjectMark _subjectMark);
	string GetFio() const;
	string GetGroup() const;
	int GetSubjectMarkCount() const;
	SubjectMark *GetAllSubjects();
	SubjectMark GetSubjectMark(int number) const;
	SubjectMark GetSubjectMark(string _subjectName) const;
	bool SetFio(string _fio);
	bool SetGroup(string _group);
	bool SetAllSubjectMarks(int _subjCount, SubjectMark *_subjectsMarks);
	bool SetAllSubjectMarks(string _subjectsMarks);
	bool SetSubjectMark(SubjectMark _subjectMark, int number);
	bool SetSubjectMark(SubjectMark _subjectMark);
	virtual void Print() const;
	virtual string ToString() const;

	static string GetListName();
	static void SetListName(string _listName);
	/****************************************/
	Student &operator=(const Student &ref);
	Student &operator=(SubjectMark _subjectMark);
	Student &operator+=(SubjectMark _subjectMark);
	bool &operator==(SubjectMark const _subjectMark) const;
	operator bool() const;
private:
	string fio;
	string group;
	int subjCount;
	SubjectMark *subjectsMarks;
	bool InitStudentFromString(string student);
	bool AddSubjectsMarksFromString(string subjects);

	static string listName;
};
#endif