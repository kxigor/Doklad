#include <fcntl.h>
#include <unistd.h>

#include <boost/leaf.hpp>
#include <cstdio>
#include <iostream>
#include <vector>

namespace leaf = boost::leaf;

struct FileOpenError {
  std::string filename;
  const char* mode;
};

struct FileWriteError {
  size_t bytes_requested;
};

leaf::result<void> write_file(const char* filename, const char* text) {
  int fd{};

  {
    auto error_ctx = leaf::on_error(FileOpenError{filename, "O_WRONLY"});

    fd = ::open(filename, O_WRONLY);
    if (fd == -1) {
      return leaf::new_error(leaf::e_errno{});
    }
  }

  auto text_size = strlen(text);

  ::close(fd);

  {
    auto error_ctx = leaf::on_error(FileWriteError{text_size});

    auto write_len = ::write(fd, text, text_size);
    ::close(fd);

    if (write_len != text_size) {
      return leaf::new_error(leaf::e_errno{});
    }
  }

  return {};
}

int main() {
  auto l = leaf::try_handle_some(
      []() -> leaf::result<int> {
        BOOST_LEAF_CHECK(write_file("test.txt", "bibibibbobobob"));
        return 0;
      },
      [](FileOpenError const& foe, leaf::e_errno const& e) {
        std::cerr << "FILE OPENING ERROR\n"
                  << "Filename: " << foe.filename << "\n"
                  << "Mode: " << foe.mode << "\n"
                  << "errno: " << e.value << " (" << strerror(e.value) << ")\n";
        return 1;
      },
      [](FileWriteError const& fre, leaf::e_errno const& e) {
        std::cerr << "FILE WRITING ERROR:\n"
                  << "Bytes required: " << fre.bytes_requested << "\n"
                  << "errno: " << e.value << " (" << strerror(e.value) << ")\n";
        return 2;
      },
      [] {
        std::cerr << "Unknown error!\n";
        return 3;
      });
}