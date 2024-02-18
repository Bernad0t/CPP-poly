#include <iostream>
#include <math.h>

class quadratic_equation {
private:
	double a;
	double b;
	double c;
	double discriminant;
	double GetDiscriminant(const double a, const double b, const double c) {
		return b * b - 4 * a * c;
	}
public:
	quadratic_equation(const double valueA, const double valueB, const double valueC) {
		discriminant = GetDiscriminant(valueA, valueB, valueC);
		if (discriminant < 0 || valueA == 0) {
			std::cout << "the discriminant is less than zero or this equation is not square" << std::endl;
			exit(-3);
		}
		a = valueA;
		b = valueB;
		c = valueC;
	}
	void get_solution(double *& const solution, int & const size) {
		double x1 = (-b + pow(discriminant, 0.5)) / 2 / a;
		if (discriminant == 0) {
			solution = new double;
			solution[0] = x1;
			size = 1;
		}
		double x2 = (-b - pow(discriminant, 0.5)) / 2 / a;
		solution = new double[2];
		solution[0] = x1;
		solution[1] = x2;
		size = 2;
	}
};

void get_solution_from_console(double *& const solution, int & const size) {
	double a, b, c;
	std::cout << "enter the coefficients of the quadratic equation in decreasing order of degree" << std::endl;
	std::cin >> a >> b >> c;
	quadratic_equation equation(a, b, c);
	equation.get_solution(solution, size);
}

void print_solution(const int size, const double* const solution) {
	for (int i = 0; i < size; i++) {
		std::cout << "solution #" << i << " = " << solution[i] << std::endl;
	}
}

int main() {
	double* solution = nullptr;
	int size;
	get_solution_from_console(solution, size);
	print_solution(size, solution);
	return 0;
}