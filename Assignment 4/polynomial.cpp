#include<iostream>

using namespace std;

struct term {
	int coeff, exp;
	term *next;
	
	term(int c, int e) {
		coeff = c;
		exp = e;
		next = NULL;
	}
};

class Polynomial {
	private:
		term *head, *tail;
		void showTerm(term *ptr) {
			int c = ptr -> coeff, e = ptr -> exp;
			if(!(c == 1 || c == -1)) cout << c;
			else if(c == -1) cout << "-";
			cout << ((e < 1) ? "" : "x");
			if(e > 1) cout << "^" << e;
		};
	
	public:
		Polynomial() {
			head = tail = NULL;
			return;
		}
		Polynomial(int len, int (*data)[2]) {
			head = tail = NULL;
			for(int i = 0; i < len; i++)
				addTerm(data[i][0], data[i][1]);
			return;
		}
		void addTerm(int, int);
		void display();
		Polynomial operator+(Polynomial &p);
		Polynomial operator-(Polynomial &p);
};

int main() {
	Polynomial p1, p2(5, new int [5][2] {{3, 4}, {2, 3}, {-1, 1}, {7, 0}, {4, 2}});
	p1.addTerm(1, 1);
	p1.addTerm(2, 5);
	p1.addTerm(-5, 0);
	p1.addTerm(0, 6);
	p1.addTerm(-19, 2);
	Polynomial p3 = p1 + p2, p4 = p1 - p2;
	p1.display();
	p2.display();
	p3.display();
	p4.display();
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
		temp -> next = NULL;
	}
	else {
		term *ptr = head, *prev = NULL;
		while(ptr && ptr -> exp > e) {
			prev = ptr;
			ptr = ptr -> next;
		}
		if(!ptr) {
			tail -> next = temp;
			tail = temp;
			temp -> next = NULL;
			return;
		}
		if(!prev) {
			head = temp;
			temp -> next = ptr;
			return;
		}
		prev -> next = temp;
		temp -> next = ptr;
	}
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

Polynomial Polynomial :: operator+(Polynomial &p) {
	Polynomial res;
	term *ptr1 = head, *ptr2 = p.head;
	while(ptr1 && ptr2) {
		if(ptr1 -> exp == ptr2 -> exp) {
			int c = ptr1 -> coeff + ptr2 -> coeff;
			if(c) res.addTerm(c, ptr1 -> exp);
			ptr1 = ptr1 -> next;
			ptr2 = ptr2 -> next;
		}
		else if(ptr1 -> exp > ptr2 -> exp) {
			res.addTerm(ptr1 -> coeff, ptr1 -> exp);
			ptr1 = ptr1 -> next;
		}
		else {
			res.addTerm(ptr2 -> coeff, ptr2 -> exp);
			ptr2 = ptr2 -> next;
		}
	}
	while(ptr1) {
		res.addTerm(ptr1 -> coeff, ptr1 -> exp);
		ptr1 = ptr1 -> next;
	}
	while(ptr2) {
		res.addTerm(ptr2 -> coeff, ptr2 -> exp);
		ptr2 = ptr2 -> next;
	}
	return res;
}

Polynomial Polynomial :: operator-(Polynomial &p) {
	Polynomial res;
	term *ptr1 = head, *ptr2 = p.head;
	while(ptr1 && ptr2) {
		if(ptr1 -> exp == ptr2 -> exp) {
			int c = ptr1 -> coeff - ptr2 -> coeff;
			if(c) res.addTerm(c, ptr1 -> exp);
			ptr1 = ptr1 -> next;
			ptr2 = ptr2 -> next;
		}
		else if(ptr1 -> exp > ptr2 -> exp) {
			res.addTerm(ptr1 -> coeff, ptr1 -> exp);
			ptr1 = ptr1 -> next;
		}
		else {
			res.addTerm(-ptr2 -> coeff, ptr2 -> exp);
			ptr2 = ptr2 -> next;
		}
	}
	while(ptr1) {
		res.addTerm(ptr1 -> coeff, ptr1 -> exp);
		ptr1 = ptr1 -> next;
	}
	while(ptr2) {
		res.addTerm(-ptr2 -> coeff, ptr2 -> exp);
		ptr2 = ptr2 -> next;
	}
	return res;
}
