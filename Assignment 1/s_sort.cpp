#include<iostream>
#include<fstream>
#include<cctype>

using namespace std;

// Student record - Roll no, Name, marks
struct Student {
	int rNum;
	string name;
	int marks;
};

// A count of students
int count = 0;

// Reads the records from the file and stores in an array
void readFile(string, Student*&);

// Writes the given array into the file
void writeFile(Student[], int, string);

// Insertion sort for Roll no
void rollSort(Student[], int);

// Shell sort for Names
void nameSort(Student[], int);

// Radix sort for GPA
void gpaSort(Student[], int);

// Returns true if first string is alphabetically earlt, else false
bool isBefore(string, string);

int main(int argc, char* argv[]) {
    // Read file from command line argument, make the students array(here) store the data, and delete[] (in here itself) that array
    if(argc != 2) {
        cout << "Invalid parameters\n";
        return 1;
    }

    Student *students;

    readFile(argv[1], students);

    rollSort(students, count);
    writeFile(students, count, "rollSorted.txt");
    nameSort(students, count);
    writeFile(students, count, "nameSorted.txt");
    gpaSort(students, count);
    writeFile(students, count, "gpaSorted.txt");

    delete[] students;

    return 0;
}

void readFile(string fname, Student* &s) {
    ifstream f1(fname);
    if (!f1) return;
    
    int n;
    f1 >> n;
    if(n <= 0) {
        cout << "No records to read.\n";
        f1.close();
        return;
    }
    
    s = new Student[n];
    ::count = n;

    for (int i = 0; i < n; i++) {
        f1 >> s[i].rNum >> s[i].name >> s[i].marks;
    }
    
    f1.close();
    return;
}

void writeFile(Student s[], int n, string fname) {
    ofstream f1;
	f1.open(fname, ios::out);
	if(!f1) return;
	
	for(int i = 0; i < n; i++) {
        f1 << s[i].rNum << "\t" << s[i].name << "\t" << s[i].marks << "\n";
	}
	
	f1.close();
	return;
}

void rollSort(Student s[], int n) {
    int i, j;
	for(i = 1; i < n; i++) {
		Student key = s[i];
		for(j = i - 1; j >= 0 && key.rNum < s[j].rNum; j--) {
            s[j + 1] = s[j];
		}
		s[j + 1] = key;
	}
    return;
}

void nameSort(Student s[], int n) {
    int i, j;
    for(int gap = n / 2; gap > 0; gap /= 2) {
        for(int k = 0; k < gap; k++) {
            for(i = gap + k; i < n; i += gap) {
                Student key = s[i];
                for(j = i - gap; j >= 0 && isBefore(key.name, s[j].name); j -= gap) {
                    s[j + gap] = s[j];
                }
                s[j + gap] = key;
            }
        }
    }
    return;
}

void gpaSort(Student s[], int n) {
    Student* output = new Student[n];
    int maxMarks = s[0].marks;
    for (int i = 1; i < n; i++)
        if (s[i].marks > maxMarks)
            maxMarks = s[i].marks;

    for (int exp = 1; maxMarks / exp > 0; exp *= 10) {
        
        int count[10] = {0};
        for (int i = 0; i < n; i++) {
            int digit = (s[i].marks / exp) % 10;
            count[digit]++;
        }

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int digit = (s[i].marks / exp) % 10;
            output[count[digit] - 1] = s[i];
            count[digit]--;
        }

        for (int i = 0; i < n; i++)
            s[i] = output[i];

    }

    delete[] output;
    return;
}


bool isBefore(string s1, string s2) {
    for(int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (tolower(s1[i]) < tolower(s2[i])) return true;
        if (tolower(s1[i]) > tolower(s2[i])) return false;
    }
    return s1.length() < s2.length();
}
