#include "pch.h"
#include "big_real.h"



big_int::big_int() {
	first = new nod;
	first->next = NULL;
	first->prev = NULL;
	first->c = 0;
	last = first;
	s = '+';
}

big_int::big_int(long long int x) {
	first = new nod;
	first->next = NULL;
	first->prev = NULL;
	s = '+';
	if (x < 0) {
		s = '-';
		x = -x;
	}
	if (x == 0) {
		add_last(0);
		return;
	}
	while (x != 0) {
		add_last(x % 10);
		x /= 10;
	}
}

big_int::big_int(const char* x) {
	first = new nod;
	first->next = NULL;
	first->prev = NULL;
	int semn = 0;
	if (x[0] == '+' || x[0] == '-') {
		s = x[0];
		semn = 1;
	}
	else
		s = '+';
	int l = strlen(x) - 1;
	while (l >= semn) {
		add_last(x[l] - '0');
		l--;
	}
}

big_int::big_int(const big_int& X) {
	s = X.s;
	first = new nod;
	first->next = NULL;
	first->prev = NULL;
	last = first;
	first->c = X.first->c;
	nod *p = X.first->next;
	while (p != NULL) {
		add_last(p->c);
		p = p->next;
	}
}

big_int::~big_int() {
	nod *p = first, *q;
	while (p != NULL) {
		q = p;
		p = p->next;
		delete q;
	}
}



char big_int::get_sign() {
	return s;
}

void big_int::set_sign(char s) {
	this->s = s;
}

void big_int::add_first(int x) {
	nod *p = new nod;
	p->next = first;
	p->prev = NULL;
	p->c = x;
	if (first != NULL)
		first->prev = p;
	first = p;
	p = last;
	nod *q;
	while (p->c == 0 && p->prev != NULL) {
		q = p;
		p = p->prev;
		delete q;
		p->next = NULL;
	}
	last = p;
	int l = length();
	while (p->c == 0 && l > 1) {
		last = last->prev;
		delete p;
		p = last;
		last->next = NULL;
		l--;
	}
}

void big_int::add_last(int x) {
	if (last == NULL) {
		last = first;
		last->c = x;
		return;
	}
	nod *p = new nod;
	p->c = x;
	p->prev = last;
	p->next = NULL;
	last->next = p;
	last = p;
}

int big_int::length() {
	nod *p = first;
	int lung = 0;
	while (p != NULL) {
		lung++;
		p = p->next;
	}
	return lung;
}

bool big_int::is_zero() {
	if (first->c == 0 && first->next == NULL)
		return true;
	return false;
}

bool big_int::greater_abs(big_int& X) {
	int x = length(), y = X.length();
	if (x > y)
		return true;
	if (x < y)
		return false;
	nod *p = last, *q = X.last;
	while (p != NULL && p->c == q->c) {
		p = p->prev;
		q = q->prev;
	}
	if (p == NULL)
		return false;
	if (p->c < q->c)
		return false;
	return true;
}

int big_int::cut_zeroes() {
	if (is_zero())
		return 0;
	int zeroes = 0;
	nod *p = first, *q;
	while (p->c == 0) {
		zeroes++;
		q = p;
		p = p->next;
		delete q;
		p->prev = NULL;
	}
	first = p;
	return zeroes;
}

big_int big_int::division(big_int X, int precis, int& exp_loss) {
	big_int I;
	if (s == X.s)
		I.s = '+';
	else
		I.s = '-';
	X.s = '+';
	big_int Y, Z = *this;
	int imp, precizie = 0;
	nod *p = Z.last;
	while (X > Y && p != NULL) {
		Y.add_first(p->c);
		p = p->prev;
	}
	while (X > Y && precizie < precis) {
		Y.add_first(0);
		precizie++;
	}
	if (X > Y) {
		exp_loss = 0;
		return I;
	}
	while (precizie == 0) {
		imp = 0;
		while (Y >= X) {
			Y = Y - X;
			imp++;
		}
		I.add_first(imp);
		if (X > Y && p != NULL) {
			Y.add_first(p->c);
			p = p->prev;
		}
		else if (p == NULL) {
			if (!Y.is_zero()) {
				Y.add_first(0);
				precizie++;
			}
			break;
		}
	}
	if (!Y.is_zero())
		while (true) {
			imp = 0;
			while (Y >= X) {
				Y = Y - X;
				imp++;
			}
			I.add_first(imp);
			if (Y.is_zero() || precizie == precis)
				break;
			if (X > Y && precizie < precis) {
				Y.add_first(0);
				precizie++;
			}
		}
	p = I.last;
	nod *q;
	while (p->c == 0 && p->prev != NULL) {
		q = p;
		p = p->prev;
		delete q;
		p->next = NULL;
	}
	exp_loss = precizie;
	if (I.is_zero())
		I.s = '+';
	return I;
}



big_int big_int::operator+(big_int& X) {
	if (s != X.s) {
		big_int D, A1, A2;
		A1 = *this;
		A1.s = '+';
		A2 = X;
		A2.s = '+';
		if (greater_abs(X)) {
			D = A1 - A2;
			D.s = s;
			if (D.is_zero())
				D.s = '+';
			return D;
		}
		D = A2 - A1;
		D.s = X.s;
		if (D.is_zero())
			D.s = '+';
		return D;
	}
	big_int S;
	S.s = s;
	int rest = 0, suma;
	nod *p = first, *q = X.first;
	suma = p->c + q->c;
	if (suma >= 10) {
		rest = suma / 10;
		suma -= 10;
	}
	S.first->c = suma;
	p = p->next;	q = q->next;
	while (p != NULL && q != NULL) {
		suma = p->c + q->c + rest;
		rest = suma / 10;
		if (suma >= 10)
			suma -= 10;
		S.add_last(suma);
		p = p->next;	q = q->next;
	}
	while (p != NULL) {
		suma = p->c + rest;
		rest = suma / 10;
		if (suma >= 10)
			suma -= 10;
		S.add_last(suma);
		p = p->next;
	}
	while (q != NULL) {
		suma = q->c + rest;
		rest = suma / 10;
		if (suma >= 10)
			suma -= 10;
		S.add_last(suma);
		q = q->next;
	}
	if (rest > 0)
		S.add_last(rest);
	if (S.is_zero())
		S.s = '+';
	return S;
}

big_int big_int::operator-(big_int& X) {
	if (s != X.s) {
		big_int S, A1, A2;
		A1 = *this;
		A1.s = '+';
		A2 = X;
		A2.s = '+';
		S = A1 + A2;
		S.s = s;
		if (S.is_zero())
			S.s = '+';
		return S;
	}
	big_int D;
	int rest = 0, dif;
	nod *p, *q;
	if (greater_abs(X)) {
		p = first;
		q = X.first;
		D.s = s;
	}
	else {
		p = X.first;
		q = first;
		if (X.s == '+')
			D.s = '-';
		else
			D.s = '+';
	}
	dif = p->c - q->c;
	if (dif < 0) {
		rest = -1;
		dif += 10;
	}
	D.first->c = dif;
	p = p->next;	q = q->next;
	while (p != NULL && q != NULL) {
		dif = p->c - q->c + rest;
		if (dif < 0) {
			rest = -1;
			dif += 10;
		}
		else
			rest = dif / 10;
		D.add_last(dif);
		p = p->next;	q = q->next;
	}
	while (p != NULL) {
		dif = p->c + rest;
		if (dif < 0) {
			rest = -1;
			dif += 10;
		}
		else
			rest = dif / 10;
		D.add_last(dif);
		p = p->next;
	}
	while (q != NULL) {
		dif = q->c + rest;
		if (dif < 0) {
			rest = -1;
			dif += 10;
		}
		else
			rest = dif / 10;
		D.add_last(dif);
		q = q->next;
	}
	p = D.last;
	int l = D.length();
	while (p->c == 0 && l > 1) {
		D.last = D.last->prev;
		delete p;
		p = D.last;
		D.last->next = NULL;
		l--;
	}
	if (D.is_zero())
		D.s = '+';
	return D;
}

big_int big_int::operator*(long long int x) {
	big_int A;
	if (is_zero() || x == 0)
		return A;
	if (x < 0) {
		if (s == '+')
			A.s = '-';
		else
			A.s = '+';
		x = -x;
	}
	long long int prod, rest = 0;
	nod *p = first;
	prod = p->c * x;
	rest = prod / 10;
	prod = prod % 10;
	A.first->c = prod;
	p = p->next;
	while (p != NULL) {
		prod = p->c * x + rest;
		rest = prod / 10;
		prod = prod % 10;
		A.add_last(prod);
		p = p->next;
	}
	while (rest > 0) {
		A.add_last(rest % 10);
		rest = rest / 10;
	}
	return A;
}

big_int big_int::operator*(big_int& X) {
	big_int P;
	if (is_zero() || X.is_zero())
		return P;
	big_int temp1 = *this, temp2;
	nod *p = X.first;
	while (p != NULL) {
		temp2 = temp1 * p->c;
		P = P + temp2;
		temp1.add_first(0);
		p = p->next;
	}
	if (s == X.s)
		P.s = '+';
	else
		P.s = '-';
	return P;
}

big_int big_int::operator/(big_int X) {
	big_int I;
	try {
		if (X.is_zero())
			throw 0;
	}
	catch (...) {
		cout << "Impartirea la 0 nu este permisa!" << endl;
		return I;
	}
	if (is_zero())
		return I;
	if (s == X.s)
		I.s = '+';
	else
		I.s = '-';
	X.s = '+';
	big_int Y, Z = *this;
	int imp;
	nod *p = Z.last;
	while (X > Y && p != NULL) {
		Y.add_first(p->c);
		p = p->prev;
	}
	if (X > Y) {
		I.s = '+';
		return I;
	}
	while (true) {
		imp = 0;
		while (Y >= X) {
			Y = Y - X;
			imp++;
		}
		I.add_first(imp);
		if (X > Y && p != NULL) {
			Y.add_first(p->c);
			p = p->prev;
		}
		else if (p == NULL)
			break;
	}
	p = I.last;
	nod *q;
	while (p->c == 0 && p->prev != NULL) {
		q = p;
		p = p->prev;
		delete q;
		p->next = NULL;
	}
	if (I.is_zero())
		I.s = '+';
	return I;
}

big_int& big_int::operator=(const big_int& X) {
	if (this != &X) {
		s = X.s;
		nod *p = first->next, *q;
		while (p != NULL) {
			q = p;
			p = p->next;
			delete q;
		}
		last = first;
		first->next = NULL;
		p = X.first->next;
		first->c = X.first->c;
		while (p != NULL) {
			add_last(p->c);
			p = p->next;
		}
	}
	return *this;
}

big_int big_int::operator-() {
	big_int A(*this);
	if (A.is_zero())
		return A;
	if (A.s == '+')
		A.s = '-';
	else
		A.s = '+';
	return A;
}

big_int& big_int::operator++() {
	big_int A(1);
	*this = *this + A;
	return *this;
}

big_int big_int::operator++(int) {
	big_int A(1), temp;
	temp = *this;
	*this = *this + A;
	return temp;
}

big_int& big_int::operator--() {
	big_int A(1);
	*this = *this - A;
	return *this;
}

big_int big_int::operator--(int) {
	big_int A(1), temp;
	temp = *this;
	*this = *this - A;
	return temp;
}

big_int& big_int::operator+=(big_int& X) {
	*this = *this + X;
	return *this;
}

big_int& big_int::operator-=(big_int& X) {
	*this = *this - X;
	return *this;
}



bool big_int::operator==(big_int& X) {
	if (s != X.s)
		return false;
	if (length() != X.length())
		return false;
	nod *p = first, *q = X.first;
	while (p != NULL && p->c == q->c) {
		p = p->next;
		q = q->next;
	}
	if (p == NULL)
		return true;
	return false;
}

bool big_int::operator!=(big_int& X) {
	return !(*this == X);
}

bool big_int::operator<(big_int& X) {
	if (*this == X)
		return false;
	if (s != X.s) {
		if (s == '-')
			return true;
		return false;
	}
	if (s == '-')
		return greater_abs(X);
	return !greater_abs(X);
}

bool big_int::operator<=(big_int& X) {
	if (*this == X || *this < X)
		return true;
	return false;
}

bool big_int::operator>(big_int& X) {
	return !(*this <= X);
}

bool big_int::operator>=(big_int& X) {
	return !(*this < X);
}



istream& operator>>(istream& is, big_int& X) {
	char a[1000];
	is >> a;
	big_int dummy(a);
	X = dummy;
	return is;
}

ostream& operator<<(ostream& os, const big_int& X) {
	nod *p = X.last;
	if (X.s == '-')
		os << X.s;
	while (p != NULL) {
		os << p->c;
		p = p->prev;
	}
	return os;
}