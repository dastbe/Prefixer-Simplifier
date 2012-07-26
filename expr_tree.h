// Definition of ExprTree, its subclasses, and the visitor interface
//
// Created by: David Bell
// April 26th, 2012

#ifndef _EXPR_TREE_HPP_
#define _EXPR_TREE_HPP_

/* Expr Forward Declarations */

class Root;
class Div;
class Minus;
class Plus;
class Times;
class UMinus;
class Ident;
class Int;

/* Visitor Interface for ExprTree */

class Visitor{
public:
	virtual ~Visitor() {}
	virtual void visitRoot(Root *p) = 0;
	virtual void visitDiv(Div *p) = 0;
	virtual void visitMinus(Minus *p) = 0;
	virtual void visitPlus(Plus *p) = 0;
	virtual void visitTimes(Times *p) = 0;
	virtual void visitUMinus(UMinus *p) = 0;
	virtual void visitIdent(Ident *p) = 0;
	virtual void visitInt(Int *p) = 0;

};

class ExprTree
{
public:
	ExprTree *parent;
	virtual ~ExprTree() {}
	virtual void visitSubExpr(Visitor *v) = 0;
	virtual void accept(Visitor *v) = 0;
	virtual bool isIntExpr() = 0;
	virtual int resolveValue() = 0;
};

class Root : public ExprTree {
public:
	ExprTree *expr;
	Root(ExprTree *e);
	~Root();
	void visitSubExpr(Visitor *v);
	void accept(Visitor *v);
	bool isIntExpr();
	int resolveValue();
};

class Ident : public ExprTree {
public:
	char identifier;
	Ident(char c);
	~Ident();
	void visitSubExpr(Visitor *v);
	void accept(Visitor *v);
	bool isIntExpr();
	int resolveValue();

};

class Int : public ExprTree {
public:
	int value;
	Int(int i);
	~Int();
	void visitSubExpr(Visitor *v);
	void accept(Visitor *v);
	bool isIntExpr();
	int resolveValue();
};

class Div : public ExprTree {
public:
	ExprTree *op1,*op2;
	Div(ExprTree *lhs, ExprTree *rhs);
	~Div();
	void visitSubExpr(Visitor *v);
	void accept(Visitor *v);
	bool isIntExpr();
	int resolveValue();
};

class Times : public ExprTree {
public:
	ExprTree *op1,*op2;
	Times(ExprTree *lhs, ExprTree *rhs);
	~Times();
	void visitSubExpr(Visitor *v);
	void accept(Visitor *v);
	bool isIntExpr();
	int resolveValue();
};

class Plus : public ExprTree {
public:
	ExprTree *op1,*op2;
	Plus(ExprTree *lhs, ExprTree *rhs);
	~Plus();
	void visitSubExpr(Visitor *v);
	void accept(Visitor *v);
	bool isIntExpr();
	int resolveValue();
};

class Minus : public ExprTree {
public:
	ExprTree *op1,*op2;
	Minus(ExprTree *lhs, ExprTree *rhs);
	~Minus();
	void visitSubExpr(Visitor *v);
	void accept(Visitor *v);
	bool isIntExpr();
	int resolveValue();
};

class UMinus : public ExprTree {
public:
	ExprTree *op1;
	UMinus(ExprTree *rhs);
	~UMinus();
	void visitSubExpr(Visitor *v);
	void accept(Visitor *v);
	bool isIntExpr();
	int resolveValue();
};

#endif