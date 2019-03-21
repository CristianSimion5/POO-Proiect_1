#include "pch.h"
#include "big_real.h"

#define precision 20



big_real::big_real() {
	big_int Z;
	B = E = Z;
}

big_real::big_real(long long int x, long long int y) {
	big_int X(x), Y(y);
	B = X;
	E = Y;
	transform();
}

big_real::big_real(const char* x, const char* y) {
	big_int X(x), Y(y);
	B = X;
	E = Y;
	transform();
}

big_real::big_real(const big_int & X) {
	big_int ZERO;
	B = X;
	E = ZERO;
	transform();
}

big_real::big_real(const big_int& X, const big_int& Y) {
	B = X;
	E = Y;
	transform();
}

big_real::big_real(const big_real& X) {
	B = X.B;
	E = X.E;
	transform();
}

big_real::~big_real() {}



void big_real::transform() {
	int a = B.cut_zeroes();
	big_int CIF(a);
	E += CIF;
	if (B.is_zero()) {
		big_int ZERO;
		E = ZERO;
	}
}

bool big_real::greater_abs(big_real& X) {
	int l1 = B.length(), l2 = X.B.length();
	big_int M(l1), N(l2);
	M += E;
	N += X.E;
	if (M > N)
		return true;
	if (M < N)
		return false;
	if (l1 > l1)
		return true;
	if (l1 < l2)
		return false;
	return B.greater_abs(X.B);
}



big_real big_real::operator+(big_real &X) {
	big_real A = *this, B = X, C;
	if (A.E < B.E) {
		C = A;
		A = B;
		B = C;
	}
	while (A.E > B.E) {
		A.B.add_first(0);
		A.E--;
	}
	C.E = A.E;
	C.B = A.B + B.B;
	C.transform();
	return C;
}

big_real big_real::operator-(big_real &X) {
	big_real A = *this, B = X, C;
	if (A.E < B.E) {
		C = A;
		A = B;
		B = C;
	}
	while (A.E > B.E) {
		A.B.add_first(0);
		A.E--;
	}
	C.E = A.E;
	C.B = A.B - B.B;
	C.transform();
	return C;
}

big_real big_real::operator*(big_real& X) {
	if (B.is_zero() || X.B.is_zero()) {
		big_real ZERO;
		return ZERO;
	}
	big_real P;
	P.B = B * X.B;
	P.E = E + X.E;
	P.transform();
	return P;
}

big_real big_real::operator/(big_real& X) {
	try {
		if (X.B.is_zero())
			throw 0;
	}
	catch (...) {
		cout << "Impartirea la 0 nu este permisa!" << endl;
		big_real ZERO;
		return ZERO;
	}
	if (B.is_zero()) {
		big_real ZERO;
		return ZERO;
	}
	big_real I;
	int exp_loss;
	I.B = B.division(X.B, precision, exp_loss);
	big_int LOSS(exp_loss);
	I.E = E - X.E - LOSS;
	I.transform();
	return I;
}

big_real& big_real::operator=(const big_real& X) {
	if (this == &X)
		return *this;
	B = X.B;
	E = X.E;
	return *this;
}

big_real big_real::operator-() {
	if (B.is_zero())
		return *this;
	big_real A(*this);
	if (A.B.get_sign() == '+')
		A.B.set_sign('-');
	else
		A.B.set_sign('+');
	return A;
}



bool big_real::operator==(big_real& X) {
	if (B == X.B && E == X.E)
		return true;
	return false;
}

bool big_real::operator!=(big_real& X) {
	return !(*this == X);
}

bool big_real::operator<(big_real& X) {
	if (*this == X)
		return false;
	char s1 = B.get_sign(), s2 = X.B.get_sign();
	if (s1 != s2) {
		if (s1 == '-')
			return true;
		return false;
	}
	if (s1 == '-')
		return greater_abs(X);
	return !greater_abs(X);
}

bool big_real::operator<=(big_real& X) {
	if (*this == X || *this < X)
		return true;
	return false;
}

bool big_real::operator>(big_real& X) {
	return !(*this <= X);
}

bool big_real::operator>=(big_real& X) {
	return !(*this < X);
}



istream& operator>>(istream& is, big_real& X) {
	is >> X.B >> X.E;
	X.transform();
	big_int Z;
	if (X.B.is_zero())
		X.E = Z;
	return is;
}

ostream& operator<<(ostream& os, const big_real& X) {
	os << X.B << "e" << X.E;
	return os;
}
