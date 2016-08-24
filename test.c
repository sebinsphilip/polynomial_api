#include<stdio.h>
#include "polynomial.h"

void main()
{
	int i;
	double result;
	const char * str ="2*2*-x*25-59+ 100x - 5514x^6 *- 10 * 10 +985.25  *x^23";
	const char * str1 = "00002 x^009+ 51400*x^00006";
	//const char str[30],str1[30];
	//str="2*2*-x*25-59+ 100x - 5514x^6 *- 10 * 10 +985.25  *x^23";
	//str1= "00002 x^009+ 51400*x^00006";
	const char * str1_mul = "4x^6-2*x^3";
	const char * str2_mul = "x-x^4*5";
	polynomial a,b,c;
	b 	= create_poly();	
	a	= create_poly();
	i = read_poly(a,str);
	i = read_poly(b,str1);
	if (i)
		printf("\nRead success\n");
	display_polynomial(a);
	display_polynomial(b);
	c	= add_poly(a,b);
	if(c){
		printf("\nAddition successful!\n");
		display_polynomial(c);
		delete_poly(c);
	}
	c	= subtract_poly(a,b);

	if(c){
		printf("\nSubtraction successful!\n");
		display_polynomial(c);
		delete_poly(c);
	}	
	delete_poly(a);
	delete_poly(b);
	a	= create_poly();
	b	= create_poly();
	read_poly(a,str1_mul);
	display_polynomial(a);
	read_poly(b,str2_mul);
	display_polynomial(b);
	c	= multiply_poly(a,b);
	if(c){
		printf("\nMultiplication successfull\n");
 		display_polynomial(c);
		result = evaluate_poly(c,10.0);
		printf("\nEvaluate with x=10 = %lf\n",result);
		delete_poly(c);
	}
	delete_poly(a);
	delete_poly(b);
}
