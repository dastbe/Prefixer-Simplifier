// Implementation of classes that inherit from Visitor
//
// Created by: David Bell
// April 26th, 2012

#include "visitor.h"
#include "stdio.h"

/* Visitor to print tree in prefix order */

class PrintVisitor : public Visitor
{
public:
	virtual void visitRoot(Root *p)
	{
		p->visitSubExpr(this);
	}
	
	virtual void visitDiv(Div *p)
	{
		printf("( / ");
		p->visitSubExpr(this);
		printf(") ");
	}
	virtual void visitMinus(Minus *p)
	{
		printf("( - ");
		p->visitSubExpr(this);
		printf(") ");
	}
	virtual void visitPlus(Plus *p)
	{
		printf("( + ");
		p->visitSubExpr(this);
		printf(") ");
	}
	virtual void visitTimes(Times *p)
	{
		printf("( * ");
		p->visitSubExpr(this);
		printf(") ");
	}
	virtual void visitUMinus(UMinus *p)
	{
		printf("( - ");
		p->visitSubExpr(this);
		printf(") ");
	}
	virtual void visitIdent(Ident *p)
	{
		printf("%c ",p->identifier);
		p->visitSubExpr(this);
	}
	virtual void visitInt(Int *p)
	{
		printf("%i ",p->value);
		p->visitSubExpr(this);
	}
};

void printTree(ExprTree* e)
{
	PrintVisitor *v = new PrintVisitor;
	e->accept(v);
	delete v;
}

/* Visitor to simplify tree */

class SimplifyVisitor : public Visitor
{
private:
	bool is_integer(ExprTree *e) { return dynamic_cast<Int*>(e) != NULL; }
public:
	
	virtual void visitRoot(Root *p)
	{
		p->visitSubExpr(this);
		if (p->expr->isIntExpr())
		{
			ExprTree *temp = p->expr;
			p->expr = new Int(p->expr->resolveValue());
			delete temp;
		}
	}
	
	virtual void visitDiv(Div *p)
	{
		p->visitSubExpr(this);
		if (p->op1->isIntExpr())
		{
			ExprTree *temp = p->op1;
			p->op1 = new Int(p->op1->resolveValue());
			delete temp;
		}
		if (p->op2->isIntExpr())
		{
			ExprTree *temp = p->op2;
			p->op2 = new Int(p->op2->resolveValue());
			delete temp;
		}
	}
	virtual void visitMinus(Minus *p)
	{
		p->visitSubExpr(this);
		if (p->op1->isIntExpr())
		{
			ExprTree *temp = p->op1;
			p->op1 = new Int(p->op1->resolveValue());
			delete temp;
		}
		if (p->op2->isIntExpr())
		{
			ExprTree *temp = p->op2;
			p->op2 = new Int(p->op2->resolveValue());
			delete temp;
		}
	}
	virtual void visitPlus(Plus *p)
	{
		p->visitSubExpr(this);
		if (p->op1->isIntExpr())
		{
			ExprTree *temp = p->op1;
			p->op1 = new Int(p->op1->resolveValue());
			delete temp;
		}
		if (p->op2->isIntExpr())
		{
			ExprTree *temp = p->op2;
			p->op2 = new Int(p->op2->resolveValue());
			delete temp;
		}
	}
	virtual void visitTimes(Times *p)
	{
		p->visitSubExpr(this);
		if (p->op1->isIntExpr())
		{
			ExprTree *temp = p->op1;
			p->op1 = new Int(p->op1->resolveValue());
			delete temp;
		}
		if (p->op2->isIntExpr())
		{
			ExprTree *temp = p->op2;
			p->op2 = new Int(p->op2->resolveValue());
			delete temp;
		}
	}
	virtual void visitUMinus(UMinus *p)
	{
		p->visitSubExpr(this);
		if (p->op1->isIntExpr())
		{
			ExprTree *temp = p->op1;
			p->op1 = new Int(p->op1->resolveValue());
			delete temp;
		}
	}
	virtual void visitIdent(Ident *p)
	{
		// p->visitSubExpr(this);
	}
	virtual void visitInt(Int *p)
	{
		// p->visitSubExpr(this);
	}
};

void simplifyTree(ExprTree* e)
{
	SimplifyVisitor *v = new SimplifyVisitor;
	e->accept(v);
	delete v;
}