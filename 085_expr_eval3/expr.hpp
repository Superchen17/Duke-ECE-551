#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 public:
  Expression() {}
  virtual ~Expression() {}
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long n) : number(n) {}
  virtual ~NumExpression() {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << this->number;
    return ss.str();
  }
  virtual long evaluate() const { return this->number; }
};

class MathExpression : public Expression {
 private:
  std::string operand;
  Expression * lhs;
  Expression * rhs;

 public:
  MathExpression(std::string _operand, Expression * _lhs, Expression * _rhs) :
      operand(_operand),
      lhs(_lhs),
      rhs(_rhs){};
  virtual ~MathExpression() {
    delete this->lhs;
    delete this->rhs;
  }
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "( " << this->lhs->toString() << " " << this->operand << " "
       << this->rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const {
    if (this->operand == "+") {
      return lhs->evaluate() + rhs->evaluate();
    }
    else if (this->operand == "-") {
      return lhs->evaluate() - rhs->evaluate();
    }
    else if (this->operand == "*") {
      return lhs->evaluate() * rhs->evaluate();
    }
    else if (this->operand == "/") {
      return lhs->evaluate() / rhs->evaluate();
    }
    return lhs->evaluate() + rhs->evaluate();
  }
};

class PlusExpression : public MathExpression {
 public:
  PlusExpression(Expression * _lhs, Expression * _rhs) :
      MathExpression("+", _lhs, _rhs) {}
};

class MinusExpression : public MathExpression {
 public:
  MinusExpression(Expression * _lhs, Expression * _rhs) :
      MathExpression("-", _lhs, _rhs) {}
};

class TimesExpression : public MathExpression {
 public:
  TimesExpression(Expression * _lhs, Expression * _rhs) :
      MathExpression("*", _lhs, _rhs) {}
};

class DivExpression : public MathExpression {
 public:
  DivExpression(Expression * _lhs, Expression * _rhs) : MathExpression("/", _lhs, _rhs) {}
};

#endif
