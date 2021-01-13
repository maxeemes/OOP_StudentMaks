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
int mainMode = 1;//1 - общий список; 2 - список студентов заочного отделения; 3 - список студентов очного отделения
string exampleStudentString = "Студент: Иванов Иван Иванович; Группа: имя_группы; Оценки: Математика - 4, Русский язык - зачет; ";
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
	//тестирование
	/*
	string Fio = "Савва Максим Русланович";
	string Group = "19ИСТ-в1";

	SubjectMark mark1 = { "ООП", "5" };
	SubjectMark mark2 = { "Математика", "4" };
	SubjectMark mark3 = { "ОСА", "зачет" };
	SubjectMark mark4 = { "Методы оптимизации", "зачет" };
	SubjectMark addMark1 = { "Технологии программирования", "5" };
	SubjectMark addMark2 = { "Моделирование систем", "зачет" };
	string StudentDesc =
		"Студент: " + Fio + "; " + 
		"Группа: " + Group + "; " + 
		"Оценки: " + mark1.subject + " - " + mark1.mark + ", " + mark2.subject + " - " + mark2.mark + ", " + mark3.subject + " - " + mark3.mark + ";";
	int subjectMarksCountTest = 6;
	SubjectMark *subjectMarksTest = new SubjectMark[6]{ mark1, mark2, mark3, mark4, addMark1, addMark2};
	Student StudentTest = Student(StudentDesc);
	StudentTest.Print();
	StudentTest.SetAllSubjectMarks(subjectMarksCountTest, subjectMarksTest);

	StudentTest.Print();
	*/
	///тестирование
	Student::SetListName(defaultListName);
	mainModeMenu();
	if (mainMode > 1)
	{
		if (mainMode > 2)
		{
			exampleStudentString += "Форма обучения: коммерция; ";
		}
		exampleStudentString += "Статус оплаты: не оплачено; ";
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
		AddConsoleTextColor("______Режим работы программы______", 224);
		AddConsoleTextColor("1. Работа с общим списком студентов (без возможности просмотра формы и статуса оплаты обучения)", 14);
		AddConsoleTextColor("2. Работа со списком студентов заочного отделения(есть возможность просмотра статуса оплаты обучения)", 14);
		AddConsoleTextColor("3. Работа со списком студентов очного отделения(есть возможность просмотра формы  и статуса оплаты обучения у студентов с коммерческой формой обучения)", 14);
		AddConsoleTextColor("Введите номер действия...");
		cin >> selectedMode;
		if (selectedMode < 1 || selectedMode > 3) {
			AddConsoleTextColor("Ошибочный номер действия!", 12);
		}
	} while (selectedMode < 1 || selectedMode > 3);
	mainMode = selectedMode;
}

int mainMenu() {
	AddConsoleTextColor("______МЕНЮ______", 224);
	AddConsoleTextColor("1. Добавить студентов из файла", 14);
	AddConsoleTextColor("2. Просмотр/редактирование списка студентов " + Student::GetListName(), 14);
	AddConsoleTextColor("3. Сохранить студентов в файл", 14);
	AddConsoleTextColor("4. ВЫХОД", 12);
	AddConsoleTextColor("Введите номер действия...");
	int selected = 0;
	cin >> selected;
	return selected;
}

int modeSelectMenu() {
	AddConsoleTextColor("______Просмотр/редактирование списка студентов " + Student::GetListName() + "______", 224);
	AddConsoleTextColor("1. Добавить студента", 14);
	AddConsoleTextColor("2. Изменить информацию о студенте", 14);
	AddConsoleTextColor("3. Удалить студента", 14);
	AddConsoleTextColor("4. Удалить всех студентов", 12);
	AddConsoleTextColor("5. Изменить название списка", 14);
	AddConsoleTextColor("6. Вернуться в главное меню", 14);
	AddConsoleTextColor("Введите номер действия...", 7);
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
	AddConsoleTextColor("______Добавление студентов из файла______", 224);
	bool isExit = false;
	bool isSuccess = false;
	do {
		string filePath = readFilePath(Student::GetListName() + ".txt");
		isSuccess = AddStudentsFromFile(filePath);
		if (isSuccess == false) {
			AddConsoleTextColor("Ошибка! Неверный путь к файлу\nВвести снова?\n0. Да\t1. Нет");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
}

void printAllStudents()
{
	AddConsoleTextColor("Список студентов: " + Student::GetListName(), 224);
	if (studentsCount > 0) {
		for (int i = 0; i < studentsCount; i++) {
			AddConsoleTextColor("Номер студента - " + to_string(i), 224);
			students[i]->Print();
		}
	}
	else {
		AddConsoleTextColor("Список студентов пуст!");
	}
}

void userStudentAdd()
{
	Student *newStudent = CreateStudent();
	AddConsoleTextColor("______Добавление студента______", 224);
	bool isSuccess = false, isExit = false;
	do
	{
		isSuccess = userStudentCreate(&newStudent, exampleStudentString);
		isSuccess = isSuccess ? AddStudent(newStudent) : isSuccess;
		if (isSuccess == false && studentsCount < maxStudentsCount) {
			AddConsoleTextColor("Попробовать создать студента снова?\n0. Да\t1. Нет");
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
	AddConsoleTextColor("______Изменение студента______", 224);
	int studentNum = -1;
	bool isExit = false, isSuccess = false;
	do
	{
		isSuccess = SelectStudentNum(studentNum);
		if (isSuccess == false) {
			AddConsoleTextColor("Ошибка! Неверный номер студента\nВвести снова?\n0. Да\t1. Нет");
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
				AddConsoleTextColor("Попробовать создать студента снова?\n0. Да\t1. Нет");
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
	AddConsoleTextColor("______Удаление студента______", 224);
	int studentNum = -1;
	bool isExit = false, isSuccess = false;
	do
	{
		isSuccess = SelectStudentNum(studentNum);
		if (isSuccess == false) {
			AddConsoleTextColor("Ошибка! Неверный номер студента\nВвести снова?\n0. Да\t1. Нет");
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
		AddConsoleTextColor("Студент " + deletedStudent + " успешно удален!", 10);
	}
}

void userStudentDeleteAll()
{
	AddConsoleTextColor("______Удаление всех студентов______", 224);
	AddConsoleTextColor("Вы уверены что хотите удалить всех студентов?\n0. Да\t1. Нет", 12);
	bool isExit = true;
	cin >> isExit;
	if (isExit == false) {
		for (int i = 0; i < studentsCount; i++) {
			delete students[i];
		}
		studentsCount = 0;
		delete students;
		students = 0;
		AddConsoleTextColor("Все студенты успешно удаленты!", 10);
	}
	else {
		AddConsoleTextColor("Удаление студентов отменено!", 10);
	}

}

void userStudentChangeListName()
{
	AddConsoleTextColor("______Изменение имени списка студентов______", 224);
	AddConsoleTextColor("Текщее имя списка студентов: " + Student::GetListName(), 14);
	AddConsoleTextColor("Вы уверены, что хотите изменить имя списка студентов?\n0. Да\t1. Нет", 12);
	bool isExit = true;
	cin >> isExit;
	if (isExit == false) {
		AddConsoleTextColor("Введите новое имя списка без пробелов...", 14);

		string newListName = "";
		cin >> newListName;

		Student::SetListName(newListName);
		AddConsoleTextColor("Имя списка студентов изменено на " + Student::GetListName() + "!", 10);
	}
	else {
		AddConsoleTextColor("Изменение имени списка отменено!", 10);
	}
}

void userSaveStudentsToFile()
{
	AddConsoleTextColor("______Сохранение студентов в файл______", 224);
	bool isExit = false, isSuccess = false;
	do {
		string filePath = readFilePath(Student::GetListName() + ".txt");
		isSuccess = SaveStudentsToFile(filePath);
		if (isSuccess == false) {
			AddConsoleTextColor("Ошибка! Неверный путь к файлу\nВвести снова?\n0. Да\t1. Нет");
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
		AddConsoleTextColor("Ошибка добавления студента в список! Превышено максимальное количество студентов: " + to_string(maxStudentsCount) + "!", 12);
	}
	else {
		AddConsoleTextColor("Ошибка добавления студента в список! Ошибка валидации студента!", 12);
	}
	return false;
}

bool AddStudentsFromFile(string filePath)
{
	AddConsoleTextColor("Чтение студентов из файла " + filePath + "...");
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
		AddConsoleTextColor("Ошибка добавления студентов из файла! Файл не найден!", 12);
		fileStudents.close();
	}

	return false;
}

bool SelectStudentNum(int & studentNum)
{
	if (studentsCount > 0)
	{
		AddConsoleTextColor("Введите номер студента...", 14);
		cin >> studentNum;
		if (studentNum >= 0 && studentNum < studentsCount) {
			return true;
		}
	}
	else
	{
		AddConsoleTextColor("Ошибка выбора номера студента! Список студентов пуст!", 12);
	}
	return false;
}

bool userStudentCreate(Student ** student, string exampleStudent)
{
	AddConsoleTextColor("______Создание студента______", 224);
	AddConsoleTextColor("Введите информацию о студенте в формате \"" + exampleStudent + "\"", 14);
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
	AddConsoleTextColor("Сохранение " + to_string(studentsCount) + " студентов в файл " + filePath + "...", 14);
	ofstream outFile;
	outFile.open(filePath);
	if (outFile.is_open()) {
		for (int i = 0; i < studentsCount; i++) {
			outFile << students[i]->ToString() << endl;
		}
		AddConsoleTextColor("Студенты сохранены в файл", 10);
		return true;
	}
	outFile.close();
	return false;
}

string readFilePath(string _defPath)
{
	string filePath = "";
	AddConsoleTextColor("Введите адрес файла или любой сивол, чтобы выбрать стандартный путь: " + _defPath + "...", 14);
	cin >> filePath;
	filePath = filePath.length() > 1 ? filePath : _defPath;
	return filePath;
}
