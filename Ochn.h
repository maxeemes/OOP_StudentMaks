#include "Zaochn.h"
#ifndef OCHN_H
#define OCHN_H
class Ochn : public Zaochn
{
public:
	Ochn();
	Ochn(string _fio, string _group, int _subjCount, SubjectMark *_subjectMarks, bool _isBudget, bool _isPayed);
	Ochn(string _description);
	Ochn(const Ochn &ref);
	Ochn &operator=(const Ochn &ref);
	virtual void Print() const;
	virtual string ToString() const;
	bool GetIsBudget() const;
	bool SetIsBudget(bool _isBudget);
private:
	bool isBudget = false;
	bool ParseIsBudget(string _description);
};
#endif