#ifndef CMAKE_CONFIG_H
#define CMAKE_CONFIG_H

#include <iostream>

using namespace std;

class Config {
public:
  explicit Config(string config_file_name = "") {
    this->setConfigFileName(config_file_name);
  }

  ~Config() {
  };

  Config(const Config& that) {
    this->setTimeout(that.getTimeout());
    this->setPort(that.getPort());
    this->setFileNamePrefix(that.getFileNamePrefix());
    this->setMaxFileSize(that.getMaxFileSize());
  }

  Config& operator=(const Config& other) {
    this->setTimeout(other.getTimeout());
    this->setPort(other.getPort());
    this->setFileNamePrefix(other.getFileNamePrefix());
    this->setMaxFileSize(other.getMaxFileSize());
    return *this;
  }

  void setConfigFileName(string config_file_name);
  string getConfigFileName() const;
  void setTimeout(int timeout_sec);
  int getTimeout() const;
  void setPort(uint16_t port);
  uint16_t getPort() const;
  void setFileNamePrefix(string prefix);
  string getFileNamePrefix() const;
  void setMaxFileSize(size_t max_file_size);
  size_t getMaxFileSize() const;

  void readConfigFile();

protected:
  string m_config_file_name;
  size_t m_max_file_size = 128;
  uint16_t m_socket_port = 5555;
  string m_file_name_prefix = "PREFIXO";
  int m_timeout_sec = 30;
};

#endif //CMAKE_CONFIG_H
