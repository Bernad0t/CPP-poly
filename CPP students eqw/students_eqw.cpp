#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <vector>
using namespace std;

class quadratic_equation {
private:
	double a;
	double b;
	double c;
	double discriminant;
	double GetDiscriminant(const double a, const double b, const double c) {
		return b * b - 4.0 * a * c;
	}
public:
	int number_solutions;
	double* solution;

	quadratic_equation() {

	}

	quadratic_equation(const double valueA, const double valueB, const double valueC) {
		discriminant = GetDiscriminant(valueA, valueB, valueC);
		if (discriminant == 0.0) number_solutions = 1;
		else if (discriminant > 0.0) number_solutions = 2;
		else number_solutions = 0;
		a = valueA;
		b = valueB;
		c = valueC;
		//get_solution();
	}

	quadratic_equation(const quadratic_equation & other) {
		a = other.a;
		b = other.b;
		c = other.c;
		discriminant = other.discriminant;
		number_solutions = other.number_solutions;
		if (number_solutions == 0) solution = nullptr;
		solution = new double[number_solutions];
		for (int i_solution = 0; i_solution < number_solutions; i_solution++) {
			solution[i_solution] = other.solution[i_solution];
		}
	}

	void get_solution() {
		if (discriminant < 0) {
			solution = nullptr;
			return;
		}
		solution = new double[number_solutions];
		for (int i = 0; i < number_solutions; i++) {
			solution[i] = (-b + pow(-1, i) * pow(discriminant, 0.5)) / 2.0 / a;
		}
	}
	
	~quadratic_equation() {
		if (solution != nullptr) delete[] solution;
	}
};

class Student {
public:
	int count_eqw;
	vector<quadratic_equation*> solutions;
	string second_name;
	
	Student() {

	}

	Student(int count_eqw, string second_name) {
		this->second_name = second_name;
		this->count_eqw = count_eqw;
		//solutions = new quadratic_equation[count_eqw];
	}

	virtual void Solwe_eqw(const vector<quadratic_equation*> list_task){};

	/*~Student() {
		delete[] solutions;
	}*/
};

class Bad_student : public  Student {
public:
	Bad_student(int count_eqw, string second_name) : Student(count_eqw, second_name){
	
	}

	void Solwe_eqw(const vector<quadratic_equation*> list_task) override {
		cout << "(Bad) ";
		for (int number_eqw = 0; number_eqw < count_eqw; number_eqw++) {
			quadratic_equation* eqw = new quadratic_equation;
			eqw->solution = new double[1];
			eqw->solution[0] = 0;
			eqw->number_solutions = 1;
			solutions.push_back(eqw);
		}
	}
};

class Average_student : public Student {
public:
	Average_student(int count_eqw, string second_name) : Student(count_eqw, second_name) {

	}

	void Solwe_eqw(const vector<quadratic_equation*> list_task) override {
		cout << "(Average) ";
		double chance;
		for (int number_eqw = 0; number_eqw < count_eqw; number_eqw++) {
			chance = (float)rand() / RAND_MAX * 100;
			if (chance <= 55.0) {
				quadratic_equation* eqw = new quadratic_equation(*list_task[number_eqw]);
				solutions.push_back(eqw);
			}
			else {
				quadratic_equation* eqw = new quadratic_equation;
				eqw->solution = new double[1];
				eqw->solution[0] = 0;
				eqw->number_solutions = 1;
				solutions.push_back(eqw);
			}
		}
	}
};

class Excellent_student : public Student {
public:
	Excellent_student(int count_eqw, string second_name) : Student(count_eqw, second_name) {

	}

	void Solwe_eqw(const vector<quadratic_equation*> list_task) override {
		cout << "(Excellent) ";
		for (int number_eqw = 0; number_eqw < count_eqw; number_eqw++) {
			quadratic_equation* eqw = new quadratic_equation(*list_task[number_eqw]);
			solutions.push_back(eqw);
		}
	}
};


class Teacher {
public:
	void print_grade(vector<Student*> students, const vector<quadratic_equation*> list_task) {
		for (int number_student = 0; number_student < students.size(); number_student++) {
			int res = 0;
			students[number_student]->Solwe_eqw(list_task);
			for (int number_task = 0; number_task < list_task.size(); number_task++) {
				if (students[number_student]->solutions[number_task]->number_solutions == list_task[number_task]->number_solutions) {
					int status_solutoin = 0;
					for (int i = 0; i < list_task[number_task]->number_solutions; i++) {
						if (students[number_student]->solutions[number_task]->solution[i]\
						  != list_task[number_task]->solution[i]) {
							status_solutoin = 1;
							break;
						}
					}
					if (status_solutoin == 0) res += 1;
				}
			}
			cout << students[number_student]->second_name << "   right solutions = " << res << endl;
		}
	}
};

double convert_str_to_double(const string str) {
	double res_whole = 0;
	int degree_whole = 0;//целая и дробная должеы быть
	double res_fractional = 0;
	int degree_fractional = 0;//целая и дробная должеы быть
	int i = str.length() - 1;
	char separator = '.';
	while (i > -1 && str[i] != separator) {
		res_fractional += (double)((int)(str[i] - '0') * pow(10, degree_fractional));
		degree_fractional += 1;
		i -= 1;
	}
	if (i == -1) return res_fractional;
	i -= 1;
	res_whole /= pow(10, degree_whole + 1);
	while (i > -1) {
		res_whole += (double)((int)(str[i] - '0') * pow(10, degree_whole));
		degree_whole += 1;
		i -= 1;
	}
	return res_whole + res_fractional;
}

void parse_str(vector<quadratic_equation*>* list_task, const string str) {
	char separator = ' ';
	int str_position = 0;
	string parse_str;
	vector<double> coeff;
	int sign;
	while (str[str_position] != '\0') {
		sign = 1;
		if (str[str_position] != separator) {
			if (str[str_position] == '-') {
				sign = -1;
				str_position++;
				continue;
			}
			parse_str += str[str_position];
		}
		else {
			coeff.push_back(sign * convert_str_to_double(parse_str));
			parse_str.clear();
		}
		str_position++;
	}
	coeff.push_back(sign * convert_str_to_double(parse_str));
	parse_str.clear();
	quadratic_equation* eqw = new quadratic_equation(coeff[0], coeff[1], coeff[2]);
	eqw->get_solution();
	list_task->push_back(eqw);
}

void ReadFileCoeff(ifstream& file, vector<quadratic_equation*>* list_task) {
	int size_list_task = 0;
	/*vector<quadratic_equation>* tmp_list_task = list_task;*///сделать собственноручно реаллок, мб эту строку даж туда вынести. число = а - '0'
	string str;
	while (getline(file, str)) {
		size_list_task += 1;
		parse_str(list_task, str);
	}
}

int main() {
	ifstream file_coeff("../qwtr eqw.txt"); //(x^2 - 1 записан как 1 0 -1 и тд)
	vector<quadratic_equation*> list_task;
	ReadFileCoeff(file_coeff, &list_task); 
	file_coeff.close();
	vector<string> list_names = { "Tkachev", "Drekalov", "Tishkovec", "Murigin", "Hoai" };
	vector<Student*> list_students;
	int count_eqw = list_task.size();
	for (int i = 0; i < list_names.size(); i++) {
		Student* student;
		double future_status_student = (float)rand() / RAND_MAX * 99;
		if (future_status_student <= 33.0) {
			student = new Bad_student(count_eqw, list_names[i]);
		}
		else if (future_status_student <= 66.0) {
			student = new Average_student(count_eqw, list_names[i]);
		}
		else {
			student = new Excellent_student(count_eqw, list_names[i]);
		}
		list_students.push_back(student);
	}
	Teacher teacher;
	teacher.print_grade(list_students, list_task);
	return 0;
}