#pragma once
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class nod {
public:
	int c;
	nod *prev, *next;
	friend class big_int;
};

class big_int {
	nod *first, *last;
	char s;
public:
	// constructori si destructori
	big_int();
	big_int(long long int x);
	big_int(const char* x);
	big_int(const big_int& X);
	~big_int();

	// metode ajutatoare
	char get_sign();
	void set_sign(char s);
	void add_first(int x);
	void add_last(int x);
	int length();
	bool is_zero();
	bool greater_abs(big_int& X);
	int cut_zeroes();
	big_int division(big_int X, int precis, int& exp_loss);

	// supraincarcari de operatori aritmetici
	big_int operator+(big_int& X);
	big_int operator-(big_int& X);
	big_int operator*(long long int x);
	big_int operator*(big_int& X);
	big_int operator/(big_int X);
	big_int& operator=(const big_int& X);
	big_int operator-();
	big_int& operator++();
	big_int operator++(int);
	big_int& operator--();
	big_int operator--(int);
	big_int& operator+=(big_int& X);
	big_int& operator-=(big_int& X);

	// supraincarcari de operatori logici
	bool operator==(big_int& X);
	bool operator!=(big_int& X);
	bool operator<(big_int& X);
	bool operator<=(big_int& X);
	bool operator>(big_int& X);
	bool operator>=(big_int& X);

	// supraincarcari pentru intrare/iesire
	friend istream& operator>>(istream& is, big_int& X);
	friend ostream& operator<<(ostream& os, const big_int& X);


	friend class big_real;
};

class big_real {
	big_int B, E;
public:
	big_real();
	big_real(long long int x, long long int y = 0);
	big_real(const char* x, const char* y);
	big_real(const big_int& X);
	big_real(const big_int& X, const big_int& Y);
	big_real(const big_real& X);
	~big_real();

	void transform();
	bool greater_abs(big_real &X);

	big_real operator+(big_real& X);
	big_real operator-(big_real& X);
	big_real operator*(big_real& X);
	big_real operator/(big_real& X);
	big_real& operator=(const big_real& X);
	big_real operator-();
	
	bool operator==(big_real& X);
	bool operator!=(big_real& X);
	bool operator<(big_real& X);
	bool operator<=(big_real& X);
	bool operator>(big_real& X);
	bool operator>=(big_real& X);

	friend istream& operator>>(istream& is, big_real& X);
	friend ostream& operator<<(ostream& os, const big_real& X);
};