#include <server.h>

static const char *const HEADER = "\nInitial Project\n\n";
static const char *const USAGE = "Usage.\n";

int main(int argc, const char *argv[]) {
  std::cout << HEADER;

  // ensure the correct number of parameters are used.
  if (argc < 1) {
    std::cout << USAGE;
    return 1;
  }

  Server tc = Server("Hi!");
  tc.sayHi();

  return 0;
}
