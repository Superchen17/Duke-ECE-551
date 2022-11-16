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
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * _lhs, Expression * _rhs) : lhs(_lhs), rhs(_rhs) {}
  virtual ~PlusExpression() {
    delete this->lhs;
    delete this->rhs;
  }
  virtual std::string toString() const {
    std::stringstream ss;

    ss << "(" << this->lhs->toString() << " + " << this->rhs->toString() << ")";
    return ss.str();
  }
};

#endif
