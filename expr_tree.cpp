// Implementation of ExprTree subclasses
//
// Created by: David Bell
// April 26th, 2012

#include "expr_tree.h"
#include "stdio.h"

/* Root */

Root::Root(ExprTree *e) : expr(e) { e->parent = this; }
Root::~Root() { delete expr; }
void Root::visitSubExpr(Visitor *v) { expr->accept(v); }
void Root::accept(Visitor *v) { v->visitRoot(this); }
bool Root::isIntExpr() { return expr->isIntExpr(); }
int Root::resolveValue() { return expr->resolveValue(); }

/* Ident */
Ident::Ident(char c) : identifier(c) {}
Ident::~Ident() {}
void Ident::visitSubExpr(Visitor *v) { return; }
void Ident::accept(Visitor *v) { v->visitIdent(this); }
bool Ident::isIntExpr() { return false; }
int Ident::resolveValue() { return NULL; }

/* Int */

Int::Int(int i) : value(i) {}
Int::~Int() {}
void Int::visitSubExpr(Visitor *v) { return; }
void Int::accept(Visitor *v) { v->visitInt(this); }
bool Int::isIntExpr() { return true; }
int Int::resolveValue() { return value; }

/* Div */

Div::Div(ExprTree *lhs, ExprTree *rhs) : op1(lhs), op2(rhs)
{
	op1->parent = this;
	op2->parent = this;
}
Div::~Div() { delete op1; delete op2; }
void Div::visitSubExpr(Visitor *v) { op1->accept(v); op2->accept(v); }
void Div::accept(Visitor *v) { v->visitDiv(this); }
bool Div::isIntExpr() 
{ 
	if (op1->isIntExpr() and op2->isIntExpr() and op1->resolveValue() % op2->resolveValue() == 0)
		return true;
	return false;
}
int Div::resolveValue() { return op1->resolveValue() / op2->resolveValue(); }

/* Times */

Times::Times(ExprTree *lhs, ExprTree *rhs) : op1(lhs), op2(rhs) {}
Times::~Times() { delete op1; delete op2; }
void Times::visitSubExpr(Visitor *v) { op1->accept(v); op2->accept(v); }
void Times::accept(Visitor *v) { v->visitTimes(this); }
bool Times::isIntExpr() { return op1->isIntExpr() and op2->isIntExpr(); }
int Times::resolveValue() { return op1->resolveValue() * op2->resolveValue(); }

/* Plus */

Plus::Plus(ExprTree *lhs, ExprTree *rhs) : op1(lhs), op2(rhs)
{
	op1->parent = this;
	op2->parent = this;
}
Plus::~Plus() { delete op1; delete op2; }
void Plus::visitSubExpr(Visitor *v) { op1->accept(v); op2->accept(v); }
void Plus::accept(Visitor *v) { v->visitPlus(this); }
bool Plus::isIntExpr() { return op1->isIntExpr() and op2->isIntExpr(); }
int Plus::resolveValue() { return op1->resolveValue() + op2->resolveValue(); }

/* Minus */

Minus::Minus(ExprTree *lhs, ExprTree *rhs) : op1(lhs), op2(rhs)
{
	op1->parent = this;
	op2->parent = this;
}
Minus::~Minus() { delete op1; delete op2; }
void Minus::visitSubExpr(Visitor *v) { op1->accept(v); op2->accept(v); }
void Minus::accept(Visitor *v) { v->visitMinus(this); }
bool Minus::isIntExpr() { return op1->isIntExpr() and op2->isIntExpr(); }
int Minus::resolveValue() { return op1->resolveValue() - op2->resolveValue(); }

/* UMinus */

UMinus::UMinus(ExprTree *rhs) : op1(rhs)
{
	op1->parent = this;
}
UMinus::~UMinus() { delete op1; }
void UMinus::visitSubExpr(Visitor *v) { op1->accept(v); }
void UMinus::accept(Visitor *v) { v->visitUMinus(this); }
bool UMinus::isIntExpr() { return op1->isIntExpr(); }
int UMinus::resolveValue() { return -(op1->resolveValue()); }