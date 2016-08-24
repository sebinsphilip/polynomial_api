# polynomial_api
All basic polynomial operations in C. Polynomials are stored as linked lists.

## Polynomial operations

	* Create polynomial - p = create_poly()
	* Read a polynomial string 'str' and convert it into polynomial type p - read_poly(p,str)
	* Add two polynomials p1 and p2 - p3 =  add_poly(p1,p2)
	* Subtract two polynomials p1 and p2 - p3 =  subtract_poly(p1,p2)
	* Multiply two polynomials p1 and p2 - p3 =  multiply_poly(p1,p2)
	* Evaluate a polynomial p with a double value val - result = evaluate_poly(p,val)
	* Display a polynomial p - display_polynomial(p)
	* Delete a polynomial - delete_poly(p)

## Files
	- polynomial.h - Header file containing all the function prototypes and data structures.
	- polynomial.c - The implementation of the polynomial functions.
	- test.c       - Test file .

## Run the code
	For compiling and linking both test code and library functions in gcc compiler.
```sh
	>	gcc test.c polynomial.c -o polynomial -lm
```
	
	For running the executable
```sh
	>	./polynomial
```
