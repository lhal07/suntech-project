#include <server.h>
#include <config.h>
#include <boost/asio.hpp>

int main(int argc, const char *argv[]) {
  if (argc < 1) {
    std::cout << "No arguments required";
    return 1;
  }

  try {
    boost::asio::io_context io_context;
    Config config = Config("file.conf");
    Server server = Server(io_context, config);
    server.run();
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
