/*
 * Operator.cpp
 *
 *  Created on: Nov 30, 2015
 *      Author: sina
 */
#include "Node.h"
//#include "Identifier.h"
//#include "Operator.h"

//#include "../Parser/parser.hpp"

//extern int TPLUS;

//extern auto yytokentype;

//extern int TPLUS;

Value* NBinaryOperator::codeGen(Arendelle* arendelle)
{
	Value* resVal;
	Value* lValue = lhs->codeGen(arendelle);
	int lVal = static_cast<VInt*>(lValue)->value;

	Value* rValue = rhs->codeGen(arendelle);
	int rVal = static_cast<VInt*>(rValue)->value;
	if(this->op == TPLUS)
	{
		resVal = new VInt(lVal + rVal);
	}
	if(this->op == TMINUS)
		resVal = new VInt(lVal - rVal);
	if(this->op == TMUL)
		resVal = new VInt(lVal * rVal);
	if(this->op == TDIV)
		resVal = new VInt(lVal / rVal);
	return resVal;
	//Value* tmpVal = new Value;
	//return tmpVal;
}

Value* NSingularOperator::codeGen(Arendelle* arendelle)
{
	Value* resVal;
	Value* dfValue = df->codeGen(arendelle);
	int dfVal = static_cast<VInt*>(dfValue)->value;

	Value* hsValue = hs->codeGen(arendelle);
	int hsVal = static_cast<VInt*>(hsValue)->value;
	if(this->op == TPLUS)
	{
		resVal = new VInt(dfVal + hsVal);
	}
	if(this->op == TMINUS)
		resVal = new VInt(dfVal - hsVal);
	if(this->op == TMUL)
		resVal = new VInt(dfVal * hsVal);
	if(this->op == TDIV)
		resVal = new VInt(dfVal / hsVal);
	return resVal;
	//Value* tmpVal = new Value;
	//return tmpVal;
}

