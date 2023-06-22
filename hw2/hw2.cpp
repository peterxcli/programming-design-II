#include <bits/stdc++.h>
using namespace std;

class Employee {
public:
    string employee_id;
    int age;
    char gender;
    int salary;

    Employee(const string &id, int a, char g, int s)
        : employee_id(id), age(a), gender(g), salary(s) {}
};

bool compareEmployees(const Employee &a, const Employee &b) {
    if (a.salary != b.salary) {
        return a.salary < b.salary;
    }
    if (a.age != b.age) {
        return a.age < b.age;
    }
    if (a.gender == 'f' && b.gender == 'f') {
        return a.employee_id < b.employee_id;
    }
    if (a.gender == 'f' && b.gender == 'm') {
        return true;
    }
    if (a.gender == 'm' && b.gender == 'f') {
        return false;
    }
    else {
        return a.employee_id < b.employee_id;
    } 
}

int main(int argc, char *argv[]) {
    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    vector<Employee> employees;
    string line;

    while (getline(input_file, line)) {
        stringstream line_stream(line);
        string employee_id;
        int age;
        char gender;
        int salary;

        getline(line_stream, employee_id, ',');
        line_stream >> age;
        line_stream.ignore(1, ',');
        line_stream >> gender;
        line_stream.ignore(1, ',');
        line_stream >> salary;

        employees.emplace_back(employee_id, age, gender, salary);
    }

    sort(employees.begin(), employees.end(), compareEmployees);

    int current_salary = -1;
    for (const auto &employee : employees) {
        if (employee.salary != current_salary) {
            if (current_salary != -1) {
                cout << endl;
            }
            current_salary = employee.salary;
            cout << current_salary;
        }
        cout << "," << employee.employee_id;
    }
    cout << endl;

    return 0;
}
