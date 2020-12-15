#ifndef CMAKE_CONNECTION_H
#define CMAKE_CONNECTION_H

#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <filesystem>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include "../config/config.h"

using boost::asio::ip::tcp;
using namespace boost::chrono;
using namespace std;

class Connection
  : public boost::enable_shared_from_this<Connection> {
public:

  typedef boost::shared_ptr<Connection> pointer;

  Connection(boost::asio::io_context& io_context, Config& config)
    : m_socket(io_context),
    m_timer(io_context),
    m_config(config),
    m_transferred_amount(0) {
    this->m_connectionTime = this->getConnectionTime();
    this->m_connectionDirName = this->getNameDir();
  }

  ~Connection() {
  }

  static pointer create(boost::asio::io_context& io_context, Config& config) {
    return pointer(new Connection(io_context,config));
  }

  tcp::socket& socket() {
    return this->m_socket;
  }

  void start();
  void listen();

private:
  void handle_read(const boost::system::error_code&, size_t);
  void writeToFile(const string);
  string getConnectionTime();
  string getNameDir();
  void makeDir(string);
  string createFilePath(const string);
  void setTimer();
  void onTimeout(const boost::system::error_code&);

  tcp::socket m_socket;
  boost::asio::steady_timer m_timer;
  Config& m_config;
  size_t m_transferred_amount;
  boost::asio::streambuf m_buffer;
  string m_connectionDirName;
  string m_connectionTime;
};

#endif //CMAKE_CONNECTION_H
