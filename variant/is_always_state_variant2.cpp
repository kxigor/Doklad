#include <boost/variant2.hpp>
#include <iostream>

int main() {
  union VariantUnion {
    VariantUnion() {}
    ~VariantUnion() {}
    boost::variant2::variant<int, bool> v;
  } u;
  
  try {
    boost::variant2::get<int>(u.v);
  } catch (...) {
    std::cout << "Catched\n";
  }

  try {
    boost::variant2::get<bool>(u.v);
  } catch (...) {
    std::cout << "Catched\n";
  }
}