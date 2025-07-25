#include<iostream>
#include<fstream>
#include<cctype>

using namespace std;

struct Employee {
    int id;
    string name;
    float salary;
};

bool isBefore(string s1, string s2) {
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (tolower(s1[i]) < tolower(s2[i])) return true;
        if (tolower(s1[i]) > tolower(s2[i])) return false;
    }
    return s1.length() < s2.length();
}

int partition(Employee arr[], int low, int high) {
    int pivot = arr[high].id;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].id < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(Employee arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(Employee arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Employee* L = new Employee[n1];
    Employee* R = new Employee[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (isBefore(L[i].name, R[j].name))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(Employee arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void readFile(string fname, Employee* &e, int &n) {
    ifstream f1(fname);
    if (!f1) {
        cout << "Error opening file.\n";
        return;
    }

    f1 >> n;
    if (n <= 0) {
        cout << "No records to read.\n";
        f1.close();
        return;
    }

    e = new Employee[n];
    for (int i = 0; i < n; i++) {
        f1 >> e[i].id >> e[i].name >> e[i].salary;
    }

    f1.close();
}

void displayEmployees(Employee e[], int n) {
    cout << "EMP-ID\tName\tSalary\n";
    for (int i = 0; i < n; i++) {
        cout << e[i].id << "\t" << e[i].name << "\t" << e[i].salary << endl;
    }
}

