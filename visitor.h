// Definitions for classes that inherit from Visitor
//
// Created by: David Bell
// April 26th, 2012

#ifndef _VISITOR_HPP_
#define _VISITOR_HPP_

#include "expr_tree.h"

/* Classes that implement the visitor interface */
class PrintVisitor;
class SimplifyVisitor;

/* Calls to these visitors */
void printTree(ExprTree*);
void simplifyTree(ExprTree*);

#endif