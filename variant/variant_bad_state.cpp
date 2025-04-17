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
  std::variant<std::monostate, ExplosiveType> v;
  try {
    v = ExplosiveType{};
  } catch (const std::exception& e) {
    std::cout << v.valueless_by_exception() << std::endl;
  }
  return 0;
}