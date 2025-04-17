#include <boost/variant2/variant.hpp>
#include <iostream>
#include <stdexcept>
#include <variant>

struct ExplosiveType {
  ExplosiveType() = default;
  ExplosiveType(const ExplosiveType&) { 
    throw std::runtime_error("VARIANT?"); 
  }
  ExplosiveType(ExplosiveType&&) noexcept(false) {
    throw std::runtime_error("VARIANT?");
  }
  ExplosiveType& operator=(ExplosiveType&&) noexcept(false) {
    throw std::runtime_error("VARIANT?");
  }
};

int main() {
  namespace v2 = boost::variant2;

  v2::variant<int, ExplosiveType> v = 55;
  try {
    v = ExplosiveType{};
  } catch (const std::exception& e) {
    std::cout << v.valueless_by_exception() << std::endl;
  }
  std::cout << v2::get<0>(v) << std::endl;
  return 0;
}