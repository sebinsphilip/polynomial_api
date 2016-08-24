#include "polynomial.h"

typedef struct parser_ctx_t{
	const char* str;
}parser_ctx_t;

polynomial create_poly()
{
	polynomial head = (polynomial)malloc(sizeof( poly));
	if (head != NULL)
		head->next = NULL;
	return head;
}

void delete_poly(polynomial p)
{
	polynomial temp;
	if (p!=NULL)
	{
		while(p->next != NULL)
		{
			temp = p;
			p = p->next;
			free(temp);
		}
	free(p);
	}
	p	= NULL;

}
void display_polynomial(polynomial p)
{
	if(p!=NULL)
		p = p->next;	
	while(p!=NULL){
		printf("%0.2f X^ %d||",p->coeff,p->exp);
		p = p->next;
	}
	printf("\n");
}


void accept_space(parser_ctx_t* ctx)
{

	while(isspace(*ctx->str))
		ctx->str++;


}
int accept_staroperator(parser_ctx_t* ctx)
{
	accept_space(ctx);
	if(*ctx->str== '*' ){
		ctx->str++;
		return 1;
	}
	return 0;

}
int accept_sign(parser_ctx_t* ctx)
{
	int sign;
	sign	=1;
	
	accept_space(ctx);

	if(*ctx->str == '-'){
		sign = -1;
		ctx->str++;
	}else if(*ctx->str == '+'){
		ctx->str++;
	}
	
	return sign;

}
double accept_number(parser_ctx_t* ctx)
{
	double 	num;
	char*	end;
	
	printf("\n%s\n",ctx->str);
	num 	= strtod(ctx->str,&end);
	if(ctx->str == end){
		num= 1.0;
	}
	ctx->str	= end;

	return num;
}
double accept_coefficient(parser_ctx_t* ctx)
{
	double c= 1.0;
	int sign;

	sign 	 = accept_sign(ctx);
	c	 = accept_number(ctx);
	if(accept_staroperator(ctx))
		c *= accept_coefficient(ctx);
	return c*sign;

}
int accept_exponent(parser_ctx_t* ctx)
{
	int e;

	e	=0;

	accept_space(ctx);
	accept_staroperator(ctx);
	accept_space(ctx);
	if(*ctx->str == 'x'){
		e =1;
		ctx->str++;

		if(*ctx->str == '^'){
			ctx->str++;
			e = accept_number(ctx);
		}
	}
	
	return e;
}
polynomial new_term(double c,int e)
{
	polynomial poly;
	poly = (polynomial)malloc(sizeof(poly));
	if (poly == NULL)
		error(__FILE__,__LINE__,__func__,"Failed to allocate poly.");
	poly->coeff 	=c;
	poly->exp	=e;
	poly->next	=NULL;

	return poly;


}
polynomial  accept_term(parser_ctx_t* ctx)
{
	polynomial term;
	double	c;
	int 	e;

	c	=accept_coefficient(ctx);
	e 	=accept_exponent(ctx);
	if(accept_staroperator(ctx))
		c *= accept_coefficient(ctx);
	term 	= new_term(c,e);

	return term;

}


int read_poly(polynomial p ,const char * s)
{
	polynomial temp,prev,t;
	parser_ctx_t ctx;
	ctx.str= s;
	temp= prev= t= NULL;
	
	while(*ctx.str){
		if((p->next) == NULL){//first node
			(p->next) = accept_term(&ctx);
		}else{	
			t = accept_term(&ctx);
			temp = p->next;
			prev = p;
			while(temp!=NULL){//find position in the sorted list to insert new node t
				if(temp->exp>t->exp){
					prev = temp;
					temp = temp->next;
				}
				else if (temp->exp<t->exp){
					prev->next = t;
					t->next = temp;
					break;
				}
				else{
					temp->coeff += t->coeff;
					if(temp->coeff==0){//delete node if coeff is 0
					prev->next = temp->next;
					free(temp);
					temp=p;	
					}
					break;
				}	

			}
			if(temp==NULL){
			prev->next = t;
			}
			t=NULL;

		}

	}
	
	return 1;
}

polynomial add_poly(polynomial a ,polynomial b)
{
	polynomial a_pos,b_pos,c_pos,c;
	c	= (polynomial)malloc(sizeof(poly));
	if(c!=NULL)
		c_pos 	= c;
	else{
		printf("\nError allocating m/m in add_poly()!");
		return c;
	}
		
	if(a!=NULL) 
		a_pos	= a->next;
	else
		a_pos	= NULL;
	if(b!=NULL)
		b_pos	= b->next;
	else
		b_pos	= NULL;


	while(a_pos!=NULL && b_pos!=NULL){
		if((a_pos->exp)>(b_pos->exp)){
			(c_pos->next) = new_term(a_pos->coeff,a_pos->exp);
			a_pos = a_pos->next;
		}
		else if((b_pos->exp)>(a_pos->exp)){
			(c_pos->next) = new_term(b_pos->coeff,b_pos->exp);
			b_pos = b_pos->next;
		}
		else{
			(c_pos->next) = new_term((a_pos->coeff)+(b_pos->coeff),a_pos->exp);
			a_pos 	= a_pos->next;
			b_pos 	= b_pos->next;
			if((c_pos->next)->coeff==0){
				free(c_pos->next);
				c_pos->next = NULL;
				continue;
			}
		}
		c_pos	= c_pos->next;
	}

	if(a_pos!=NULL)
		while(a_pos!=NULL){
			(c_pos->next)	= new_term(a_pos->coeff,a_pos->exp);
			a_pos 		= a_pos->next;
			c_pos 		= c_pos->next;
		}
	else if (b_pos!=NULL)
		while(b_pos!=NULL){
			(c_pos->next)	= new_term(b_pos->coeff,b_pos->exp);
			b_pos		= b_pos->next;
			c_pos		= c_pos->next;
		}
	return c;
}

polynomial subtract_poly(polynomial a,polynomial b)
{
	polynomial b_copy,temp,b_copy_pos ;
	b_copy		= create_poly();
	b_copy_pos	= b_copy;
	if(b!=NULL)
		temp = b->next;
	else
		temp = NULL;
	while(temp!=NULL){//reverse sign of coeffs in b and store in b_copy
		b_copy_pos->next = new_term(-1.0*temp->coeff,temp->exp);
		b_copy_pos	 = b_copy_pos->next;
		temp 		 = temp->next;
	}
	return add_poly(a,b_copy);
}

polynomial multiply_poly(polynomial a,polynomial b)
{
	polynomial c=NULL,a_pos,b_pos,result=NULL,temp,temp_pos;
	if(a==NULL || b==NULL)
		return c;

	c 	= create_poly();
	temp	= create_poly();
	if(a->next==NULL || b->next == NULL) //zero polynomial
		return c;
	
	a_pos 	= a->next;
	b_pos	= b->next;
	temp 	= create_poly();
	temp_pos= temp;	
	while(a_pos!=NULL){
		temp_pos->next = new_term(a_pos->coeff,a_pos->exp);
		temp_pos       = temp_pos->next;
		a_pos	       = a_pos->next;	
	}
	
	while(b_pos!=NULL){
		a_pos 	 = a->next;
		temp_pos = temp->next;
		while(a_pos!=NULL){
			temp_pos->coeff = a_pos->coeff * b_pos->coeff;
			temp_pos->exp   = a_pos->exp   + b_pos->exp;
			temp_pos	= temp_pos->next;
			a_pos		= a_pos->next;
		}	
		
		result 	= add_poly(temp,result);
		delete_poly(c);
		c	= result;
		b_pos	= b_pos->next;

	}
	
	return result;
}

double evaluate_poly(polynomial a,double val)
{

	double result= 0.0;
	if(a==NULL || a->next == NULL)
		return result;
	a	= a->next;

	while(a!=NULL){
	result += a->coeff * pow(val,a->exp);
	a	= a->next;
	}
	
	return result;
}
