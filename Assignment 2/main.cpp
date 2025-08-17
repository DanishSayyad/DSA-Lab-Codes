#include<iostream>
#include"sort.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./sort <employee.txt>" << endl;
        return 1;
    }

    Employee* empList = nullptr;
    int numEmployees = 0;
    string filename = argv[1];

    readFile(filename, empList, numEmployees);

    quickSort(empList, 0, numEmployees - 1);
    displayEmployees(empList, numEmployees);

    mergeSort(empList, 0, numEmployees - 1);
    displayEmployees(empList, numEmployees);

    delete[] empList;
    return 0;
}
