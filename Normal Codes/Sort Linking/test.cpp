<<<<<<< HEAD
#include<iostream>
#include "Sorts.h"

#define sqr(a) a * a

using namespace std;

int main(int argc, char* argv[]) {

	MergeSort(argv[1], atoi(argv[2]));
	QuickSort(argv[1], atoi(argv[2]));
	cout << endl << sqr(5) << endl;
	return 0;

}

=======
#include<iostream>
#include "Sorts.h"

#define sqr(a) a * a

using namespace std;

int main(int argc, char* argv[]) {

	MergeSort(argv[1], atoi(argv[2]));
	QuickSort(argv[1], atoi(argv[2]));
	cout << endl << sqr(5) << endl;
	return 0;

}

>>>>>>> 995501c532bde0fcac677ba09c133489afa1eb8b
