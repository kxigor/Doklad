#include <boost/process.hpp>
#include <iostream>
#include <string>

namespace bp = boost::process;

int main() {
  bp::ipstream pipe_stream;
  bp::child c("gcc --version", bp::std_out > pipe_stream);

  for (std::string line; pipe_stream && std::getline(pipe_stream, line) && !line.empty();) {
    std::cout << line << std::endl;
  }

  c.wait();
}