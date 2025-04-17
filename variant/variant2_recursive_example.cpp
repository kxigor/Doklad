#include <boost/variant2/variant.hpp>
#include <iostream>
#include <vector>

namespace v2 = boost::variant2;

struct AddExpr;
struct SubExpr;

using Expr = v2::variant<int, AddExpr, SubExpr>;

struct AddExpr {
  std::vector<Expr> children;
};
struct SubExpr {
  std::vector<Expr> children;
};

int eval(const Expr& expr) {
  return v2::visit(
      [](auto&& arg) -> int {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
          return arg;
        } else if constexpr (std::is_same_v<T, AddExpr>) {
          int sum = 0;
          for (const auto& child : arg.children) {
            sum += eval(child);
          }
          return sum;
        } else if constexpr (std::is_same_v<T, SubExpr>) {
          if (arg.children.empty()) {
            return 0;
          }
          int res = eval(arg.children[0]);
          for (size_t i = 1; i < arg.children.size(); ++i) {
            res -= eval(arg.children[i]);
          }
          return res;
        }
      },
      expr);
}

int main() {
  Expr expr = AddExpr{{5, SubExpr{{10, 3}}, 1}};
  std::cout << "Result: " << eval(expr) << std::endl;

  return 0;
}