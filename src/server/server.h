#ifndef CMAKE_SERVER_H
#define CMAKE_SERVER_H

#include <iostream>

using namespace std;

class Server {
public:
  explicit Server(string salutation) {
    this->salutation = salutation;
  }

  ~Server() {
  };

  void sayHi();

protected:
  string salutation;
};

#endif //CMAKE_SERVER_H
