#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct p {
	int exp;
	double coeff;
	struct p *next;
}*polynomial,poly;

	polynomial create_poly();
	int read_poly(polynomial,const char*);
	polynomial add_poly(polynomial,polynomial);
	polynomial subtract_poly(polynomial,polynomial);
	polynomial multiply_poly(polynomial,polynomial);
	char *display_poly(polynomial);
	double evaluate_poly(polynomial,double);
	void delete_poly(polynomial);
	void display(polynomial);
#endif
