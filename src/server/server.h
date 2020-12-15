#ifndef CMAKE_SERVER_H
#define CMAKE_SERVER_H

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "../connection/connection.h"

using boost::asio::ip::tcp;
using namespace std;

class Server {
public:
  Server(boost::asio::io_context& io_context, Config& config)
    : m_io_context(io_context),
    m_config(config),
    m_acceptor(io_context, tcp::endpoint(tcp::v4(), config.getPort())) {}

  ~Server() {}

  void run();

private:
  void listen();
  void connect(Connection::pointer, const boost::system::error_code&);

  boost::asio::io_context& m_io_context;
  Config& m_config;
  tcp::acceptor m_acceptor;
};

#endif //CMAKE_SERVER_H
