#include "config.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void Config::setConfigFileName(string config_file_name) {
  this->m_config_file_name = config_file_name;
  if (config_file_name.compare("") != 0) {
    this->readConfigFile();
  }
}

string Config::getConfigFileName() const {
  return this->m_config_file_name;
}

void Config::setTimeout(int timeout_sec) {
  this->m_timeout_sec = timeout_sec;
}

int Config::getTimeout() const {
  return this->m_timeout_sec;
}

void Config::setPort(uint16_t port) {
  this->m_socket_port = port;
}

uint16_t Config::getPort() const {
  return this->m_socket_port;
}

void Config::setFileNamePrefix(string prefix) {
  this->m_file_name_prefix = prefix;
}

string Config::getFileNamePrefix() const {
  return m_file_name_prefix;
}

void Config::setMaxFileSize(size_t max_file_size) {
  this->m_max_file_size = max_file_size;
}

size_t Config::getMaxFileSize() const {
  return this->m_max_file_size;
}

void Config::readConfigFile() {
    ifstream file(this->m_config_file_name.c_str());
    if (file.is_open()) {
      cout << "Configuration file read" << endl;
        std::string line;
        while(getline(file, line)){
            line.erase(remove_if(line.begin(), line.end(), ::isspace),line.end());
            if(line[0] == '#' || line.empty())
                continue;
            auto delimiterPos = line.find("=");
            auto name = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);
            if (name.compare("FileNamePrefix") == 0) {
              this->setFileNamePrefix(value);
            }
            if (name.compare("MaxFileSize") == 0) {
              this->setMaxFileSize(stoi(value));
            }
            if (name.compare("SocketPort") == 0) {
              this->setPort(stoi(value));
            }
            if (name.compare("Timeout") == 0) {
              this->setTimeout(stoi(value));
            }
        }
        cout << "FileNamePrefix set as " << this->getFileNamePrefix() << endl;
        cout << "MaxFileSize set as " << this->getMaxFileSize() << endl;
        cout << "SocketPort set as " << this->getPort() << endl;
        cout << "Timeout set as " << this->getTimeout() << endl;
    }
    else {
        cerr << "Couldn't open config file for reading.\n";
    }
}
