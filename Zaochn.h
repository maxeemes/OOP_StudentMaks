#include "Student.h"
#ifndef ZAOCHN_H
#define ZAOCHN_H
class Zaochn : public Student
{
public:
	Zaochn();
	Zaochn(string _fio, string _group, int _subjCount, SubjectMark *_subjectMarks, bool _isPayed);
	Zaochn(string _description);
	Zaochn(const Zaochn &ref);
	Zaochn &operator=(const Zaochn &ref);
	virtual void Print() const;
	virtual string ToString() const;
	bool GetIsPayed() const;
	bool SetIsPayed(bool _isPayed);
private:
	bool isPayed = false;
	bool ParseIsPayed(string _description);
};
#endif