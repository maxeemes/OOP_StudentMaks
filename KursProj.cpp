#include "Student.h"
#include "Ochn.h"
#include "Zaochn.h"
#include "ConsoleTextStyle.h"
#include <Windows.h>
#include <iostream>
#include <fstream>

using namespace std;

const int maxStudentsCount = 1000;
const string defaultListName = "studentsMarks";
int mainMode = 1;//1 - ����� ������; 2 - ������ ��������� �������� ���������; 3 - ������ ��������� ������ ���������
string exampleStudentString = "�������: ������ ���� ��������; ������: ���_������; ������: ���������� - 4, ������� ���� - �����; ";
int studentsCount = 0;
Student **students = 0;

void mainModeMenu();
int mainMenu();
int modeSelectMenu();
void studentsEditSubMenu();
void userAddStudentsFromFile();
void printAllStudents();
void userStudentAdd();
void userStudentEdit();
void userStudentDelete();
void userStudentDeleteAll();
void userStudentChangeListName();
void userSaveStudentsToFile();

Student *CreateStudent(string _description = "");
bool AddStudent(Student *newStudent);
bool AddStudentsFromFile(string filePath);
bool SelectStudentNum(int &studentNum);
bool userStudentCreate(Student **newStudent, string exampleStudent);
bool SaveStudentsToFile(const string filePath);

string readFilePath(string _defPath);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//������������
	/*
	string Fio = "����� ������ ����������";
	string Group = "19���-�1";

	SubjectMark mark1 = { "���", "5" };
	SubjectMark mark2 = { "����������", "4" };
	SubjectMark mark3 = { "���", "�����" };
	SubjectMark mark4 = { "������ �����������", "�����" };
	SubjectMark addMark1 = { "���������� ����������������", "5" };
	SubjectMark addMark2 = { "������������� ������", "�����" };
	string StudentDesc =
		"�������: " + Fio + "; " + 
		"������: " + Group + "; " + 
		"������: " + mark1.subject + " - " + mark1.mark + ", " + mark2.subject + " - " + mark2.mark + ", " + mark3.subject + " - " + mark3.mark + ";";
	int subjectMarksCountTest = 6;
	SubjectMark *subjectMarksTest = new SubjectMark[6]{ mark1, mark2, mark3, mark4, addMark1, addMark2};
	Student StudentTest = Student(StudentDesc);
	StudentTest.Print();
	StudentTest.SetAllSubjectMarks(subjectMarksCountTest, subjectMarksTest);

	StudentTest.Print();
	*/
	///������������
	Student::SetListName(defaultListName);
	mainModeMenu();
	if (mainMode > 1)
	{
		if (mainMode > 2)
		{
			exampleStudentString += "����� ��������: ���������; ";
		}
		exampleStudentString += "������ ������: �� ��������; ";
	}
	int selected = 0;
	do {
		selected = mainMenu();
		switch (selected)
		{
		case 1:
			userAddStudentsFromFile();
			break;
		case 2:
			studentsEditSubMenu();
			break;
		case 3:
			userSaveStudentsToFile();
			break;
		default:
			break;
		}
	} while (selected != 4);

	getchar();
	return 0;
}

void mainModeMenu()
{
	int selectedMode = 0;
	do
	{
		AddConsoleTextColor("______����� ������ ���������______", 224);
		AddConsoleTextColor("1. ������ � ����� ������� ��������� (��� ����������� ��������� ����� � ������� ������ ��������)", 14);
		AddConsoleTextColor("2. ������ �� ������� ��������� �������� ���������(���� ����������� ��������� ������� ������ ��������)", 14);
		AddConsoleTextColor("3. ������ �� ������� ��������� ������ ���������(���� ����������� ��������� �����  � ������� ������ �������� � ��������� � ������������ ������ ��������)", 14);
		AddConsoleTextColor("������� ����� ��������...");
		cin >> selectedMode;
		if (selectedMode < 1 || selectedMode > 3) {
			AddConsoleTextColor("��������� ����� ��������!", 12);
		}
	} while (selectedMode < 1 || selectedMode > 3);
	mainMode = selectedMode;
}

int mainMenu() {
	AddConsoleTextColor("______����______", 224);
	AddConsoleTextColor("1. �������� ��������� �� �����", 14);
	AddConsoleTextColor("2. ��������/�������������� ������ ��������� " + Student::GetListName(), 14);
	AddConsoleTextColor("3. ��������� ��������� � ����", 14);
	AddConsoleTextColor("4. �����", 12);
	AddConsoleTextColor("������� ����� ��������...");
	int selected = 0;
	cin >> selected;
	return selected;
}

int modeSelectMenu() {
	AddConsoleTextColor("______��������/�������������� ������ ��������� " + Student::GetListName() + "______", 224);
	AddConsoleTextColor("1. �������� ��������", 14);
	AddConsoleTextColor("2. �������� ���������� � ��������", 14);
	AddConsoleTextColor("3. ������� ��������", 14);
	AddConsoleTextColor("4. ������� ���� ���������", 12);
	AddConsoleTextColor("5. �������� �������� ������", 14);
	AddConsoleTextColor("6. ��������� � ������� ����", 14);
	AddConsoleTextColor("������� ����� ��������...", 7);
	int selected = 0;
	cin >> selected;
	return selected;
}

void studentsEditSubMenu()
{
	int selectedMode = 0;
	do {

		printAllStudents();
		selectedMode = modeSelectMenu();
		switch (selectedMode)
		{
		case 1:
			userStudentAdd();
			break;
		case 2:
			userStudentEdit();
			break;
		case 3:
			userStudentDelete();
			break;
		case 4:
			userStudentDeleteAll();
			break;
		case 5:
			userStudentChangeListName();
			break;
		default:
			break;
		}
	} while (selectedMode != 6);
}

void userAddStudentsFromFile()
{
	AddConsoleTextColor("______���������� ��������� �� �����______", 224);
	bool isExit = false;
	bool isSuccess = false;
	do {
		string filePath = readFilePath(Student::GetListName() + ".txt");
		isSuccess = AddStudentsFromFile(filePath);
		if (isSuccess == false) {
			AddConsoleTextColor("������! �������� ���� � �����\n������ �����?\n0. ��\t1. ���");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
}

void printAllStudents()
{
	AddConsoleTextColor("������ ���������: " + Student::GetListName(), 224);
	if (studentsCount > 0) {
		for (int i = 0; i < studentsCount; i++) {
			AddConsoleTextColor("����� �������� - " + to_string(i), 224);
			students[i]->Print();
		}
	}
	else {
		AddConsoleTextColor("������ ��������� ����!");
	}
}

void userStudentAdd()
{
	Student *newStudent = CreateStudent();
	AddConsoleTextColor("______���������� ��������______", 224);
	bool isSuccess = false, isExit = false;
	do
	{
		isSuccess = userStudentCreate(&newStudent, exampleStudentString);
		isSuccess = isSuccess ? AddStudent(newStudent) : isSuccess;
		if (isSuccess == false && studentsCount < maxStudentsCount) {
			AddConsoleTextColor("����������� ������� �������� �����?\n0. ��\t1. ���");
			cin >> isExit;
		}
		else if (isSuccess == false) {
			isExit = true;
		}
	} while (isSuccess == false && isExit == false);
	if (isExit) {
		delete newStudent;
	}
}

void userStudentEdit()
{
	AddConsoleTextColor("______��������� ��������______", 224);
	int studentNum = -1;
	bool isExit = false, isSuccess = false;
	do
	{
		isSuccess = SelectStudentNum(studentNum);
		if (isSuccess == false) {
			AddConsoleTextColor("������! �������� ����� ��������\n������ �����?\n0. ��\t1. ���");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
	if (isExit == false) {
		Student *newStudent = CreateStudent();
		isSuccess = false;
		do
		{
			isSuccess = userStudentCreate(&newStudent, students[studentNum]->ToString());
			if (isSuccess == false) {
				AddConsoleTextColor("����������� ������� �������� �����?\n0. ��\t1. ���");
				cin >> isExit;
			}
		} while (isSuccess == false && isExit == false);
		if (isExit == false) {
			delete students[studentNum];
			students[studentNum] = newStudent;
		}
		else {
			delete newStudent;
		}
	}
}

void userStudentDelete()
{
	AddConsoleTextColor("______�������� ��������______", 224);
	int studentNum = -1;
	bool isExit = false, isSuccess = false;
	do
	{
		isSuccess = SelectStudentNum(studentNum);
		if (isSuccess == false) {
			AddConsoleTextColor("������! �������� ����� ��������\n������ �����?\n0. ��\t1. ���");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
	if (isExit == false) {
		int newStudentsCount = studentsCount - 1, tmpStudentNum = 0, tmpNewStudentNum = 0;
		Student **newStudents = new Student*[newStudentsCount];
		isSuccess = true;
		do
		{
			if (tmpStudentNum != studentNum) {
				newStudents[tmpNewStudentNum] = students[tmpStudentNum];
				tmpNewStudentNum++;
			}
			tmpStudentNum++;
		} while (tmpStudentNum < studentsCount);
		string deletedStudent = students[studentNum]->GetFio();
		delete students[studentNum];
		studentsCount = newStudentsCount;
		students = newStudents;
		AddConsoleTextColor("������� " + deletedStudent + " ������� ������!", 10);
	}
}

void userStudentDeleteAll()
{
	AddConsoleTextColor("______�������� ���� ���������______", 224);
	AddConsoleTextColor("�� ������� ��� ������ ������� ���� ���������?\n0. ��\t1. ���", 12);
	bool isExit = true;
	cin >> isExit;
	if (isExit == false) {
		for (int i = 0; i < studentsCount; i++) {
			delete students[i];
		}
		studentsCount = 0;
		delete students;
		students = 0;
		AddConsoleTextColor("��� �������� ������� ��������!", 10);
	}
	else {
		AddConsoleTextColor("�������� ��������� ��������!", 10);
	}

}

void userStudentChangeListName()
{
	AddConsoleTextColor("______��������� ����� ������ ���������______", 224);
	AddConsoleTextColor("������ ��� ������ ���������: " + Student::GetListName(), 14);
	AddConsoleTextColor("�� �������, ��� ������ �������� ��� ������ ���������?\n0. ��\t1. ���", 12);
	bool isExit = true;
	cin >> isExit;
	if (isExit == false) {
		AddConsoleTextColor("������� ����� ��� ������ ��� ��������...", 14);

		string newListName = "";
		cin >> newListName;

		Student::SetListName(newListName);
		AddConsoleTextColor("��� ������ ��������� �������� �� " + Student::GetListName() + "!", 10);
	}
	else {
		AddConsoleTextColor("��������� ����� ������ ��������!", 10);
	}
}

void userSaveStudentsToFile()
{
	AddConsoleTextColor("______���������� ��������� � ����______", 224);
	bool isExit = false, isSuccess = false;
	do {
		string filePath = readFilePath(Student::GetListName() + ".txt");
		isSuccess = SaveStudentsToFile(filePath);
		if (isSuccess == false) {
			AddConsoleTextColor("������! �������� ���� � �����\n������ �����?\n0. ��\t1. ���");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
}

Student * CreateStudent(string _description)
{
	if (_description.length() > 0) {
		if (mainMode == 2)
		{
			return new Zaochn(_description);
		}
		else if (mainMode == 3)
		{
			return new Ochn(_description);
		}
		return new Student(_description);
	}
	if (mainMode == 2)
	{
		return new Zaochn();
	}
	else if (mainMode == 3)
	{
		return new Ochn();
	}
	return new Student();

}

bool AddStudent(Student * newStudent)
{
	int newStudentsCount = studentsCount + 1;
	if (newStudentsCount <= maxStudentsCount && (bool)*newStudent)
	{
		Student **newStudents = new Student *[newStudentsCount];
		newStudents[studentsCount] = newStudent;
		if (studentsCount > 0)
		{
			for (int i = 0; i < studentsCount; i++)
			{
				newStudents[i] = students[i];
			}
			delete[] students;
		}
		studentsCount = newStudentsCount;
		students = newStudents;
		return true;
	}
	else if (newStudentsCount > maxStudentsCount)
	{
		AddConsoleTextColor("������ ���������� �������� � ������! ��������� ������������ ���������� ���������: " + to_string(maxStudentsCount) + "!", 12);
	}
	else {
		AddConsoleTextColor("������ ���������� �������� � ������! ������ ��������� ��������!", 12);
	}
	return false;
}

bool AddStudentsFromFile(string filePath)
{
	AddConsoleTextColor("������ ��������� �� ����� " + filePath + "...");
	ifstream fileStudents(filePath);
	if (fileStudents.is_open()) {
		const int maxLen = 1024;
		Student *newStudent;
		string line;
		bool isExit = false;
		while (isExit == false && getline(fileStudents,line))
		{
			newStudent = CreateStudent(line);
			if (AddStudent(newStudent) == false)
			{
				delete newStudent;
				isExit = true;
			}
		}
		return isExit == false;
	}
	else {
		AddConsoleTextColor("������ ���������� ��������� �� �����! ���� �� ������!", 12);
		fileStudents.close();
	}

	return false;
}

bool SelectStudentNum(int & studentNum)
{
	if (studentsCount > 0)
	{
		AddConsoleTextColor("������� ����� ��������...", 14);
		cin >> studentNum;
		if (studentNum >= 0 && studentNum < studentsCount) {
			return true;
		}
	}
	else
	{
		AddConsoleTextColor("������ ������ ������ ��������! ������ ��������� ����!", 12);
	}
	return false;
}

bool userStudentCreate(Student ** student, string exampleStudent)
{
	AddConsoleTextColor("______�������� ��������______", 224);
	AddConsoleTextColor("������� ���������� � �������� � ������� \"" + exampleStudent + "\"", 14);
	string sNewStudent = "";
	getline(cin, sNewStudent);
	getline(cin, sNewStudent);
	Student *newStudent = CreateStudent(sNewStudent);
	if ((bool)*newStudent) {
		delete *student;
		*student = newStudent;
		return true;
	}
	else
	{
		delete newStudent;
	}
	return false;
}

bool SaveStudentsToFile(const string filePath)
{
	AddConsoleTextColor("���������� " + to_string(studentsCount) + " ��������� � ���� " + filePath + "...", 14);
	ofstream outFile;
	outFile.open(filePath);
	if (outFile.is_open()) {
		for (int i = 0; i < studentsCount; i++) {
			outFile << students[i]->ToString() << endl;
		}
		AddConsoleTextColor("�������� ��������� � ����", 10);
		return true;
	}
	outFile.close();
	return false;
}

string readFilePath(string _defPath)
{
	string filePath = "";
	AddConsoleTextColor("������� ����� ����� ��� ����� �����, ����� ������� ����������� ����: " + _defPath + "...", 14);
	cin >> filePath;
	filePath = filePath.length() > 1 ? filePath : _defPath;
	return filePath;
}
