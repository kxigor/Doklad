#include <fmt/core.h>

#include <algorithm>
#include <boost/process.hpp>
#include <iostream>
#include <string>

namespace bp = boost::process;

int main() {
  bp::ipstream ls_pipe_stream;

  bp::child ls_process("ls -l /", bp::std_out > ls_pipe_stream);

  std::istream_iterator<std::string> ls_stream_it(ls_pipe_stream);
  std::istream_iterator<std::string> ls_stream_end;

  std::size_t word_count = std::distance(ls_stream_it, ls_stream_end);
  fmt::print("Total words in output: {}\n", word_count);

  ls_process.wait();

  return 0;
}