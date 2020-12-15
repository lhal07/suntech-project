#include "server.h"

void Server::run() {
  cout << "Running server" << endl;
  this->listen();
}

void Server::listen() {
  cout << "Listening for connections" << endl;
  Connection::pointer new_connection = Connection::create(this->m_io_context,this->m_config);

  this->m_acceptor.async_accept(new_connection->socket(),
                        boost::bind(&Server::connect, this, new_connection,
                        boost::asio::placeholders::error));
}

void Server::connect(Connection::pointer new_connection, const boost::system::error_code& error) {
  cout << "New connection received" << endl;
  if (!error) {
    new_connection->start();
  }
  this->listen();
}
