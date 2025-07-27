#include<iostream>
#include<fstream>

using namespace std;

// Student record - Roll no, Name, marks
struct Student {
    int rNum;
	string name;
	int marks;
};

// Student count in the file
int sCount = 0;

// Creates a file for user to enter the record into
void createFile(string);

int main(int argc, char* argv[]) {
    createFile(argv[1]);
    return 0;
}

void createFile(string fname1) {
	ofstream f1;
	f1.open(fname1, ios::out);
	if(!f1) return;
	
	Student s;
	int flag = 1;
	f1 << "\n";
	
	while(flag) {		
			cout << "Enter Student record: " << endl;
			cin >> s.rNum;
			cin >> s.name;
			cin >> s.marks;
			f1 << s.rNum << "\t" << s.name << "\t" << s.marks << "\n";
			cout << "\nMore records? (0/1) ";
			cin >> flag;
			sCount++;
	}
	f1.seekp(0);
	f1 << sCount;
	f1.close();
	return;
}
