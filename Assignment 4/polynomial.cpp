#include<iostream>

using namespace std;

struct term {
	int coeff, exp;
	term *next;
	
	term(int c, int e) {
		coeff = c;
		exp = e;
	}
};

class Polynomial {
	private:
		term *head, *tail;
		void showTerm(term *ptr) {
			if(ptr -> coeff != 1) cout << ptr -> coeff;
			cout << ((ptr -> exp < 1) ? "" : "x");
			if(ptr -> exp > 1) cout << "^" << ptr -> exp;
		};
	
	public:
		Polynomial() {
			head = tail = NULL;
			return;
		}
		Polynomial(int len, int **data) {
			return;
		}
		void addTerm(int, int);
		void display();
};

int main() {
	Polynomial p1, p2;
	p1.addTerm(2, 5);
	p1.addTerm(-19, 2);
	p1.addTerm(1, 1);
	p1.addTerm(-5, 0);
	p1.addTerm(0, 6);
	p1.display();
	p2.display();
	return 0;
}

void Polynomial :: addTerm(int c, int e) {
	if(!c) return;
	term *temp = new term(c, e);
	if(!temp) {
		cout << "Couldn't add new term!\n";
		return;
	}
	if(!head) {
		head = tail = temp;
	}
	else {
		tail -> next = temp;
		tail = temp;
	}
	temp -> next = NULL;
	return;
}

void Polynomial :: display() {
	term *ptr = head;
	if(!head) {
		cout << "0\n";
		return;
	}
	while(ptr) {
		showTerm(ptr);
		ptr = ptr -> next;
		if(ptr) {
			cout << ((ptr -> coeff < 0) ? " " : " +");
		}
	}
	cout << endl;
	return;
}

