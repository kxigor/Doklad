#include <iostream>
#include <memory>
#include <variant>
#include <vector>

struct AddExpr;
struct SubExpr;

#include <boost/variant2/variant.hpp>

using Expr = boost::variant2::variant<int, AddExpr, SubExpr>;

struct AddExpr {
  Expr children;
};
struct SubExpr {
  Expr children;
};

int main() { Expr aaaa = SubExpr{}; }
