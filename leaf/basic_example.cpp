#include <boost/leaf.hpp>
#include <iostream>

namespace leaf = boost::leaf;

struct MyError {
  int code;
  const char* message;
};

leaf::result<int> failing_func(int x) {
  if (x > 42) {
    return 228;
  }
  return leaf::new_error(MyError{
      0xDEAD, "Everything's broken"});
}

int main() {
  std::ignore = leaf::try_handle_some(
      []() -> leaf::result<void> {
        std::cout << BOOST_LEAF_CHECK(failing_func(12)) << '\n';
      },
      [](MyError const& e) {
        std::cerr << "Error: " << e.message << std::endl;
      });
}