#include "connection.h"

void Connection::start() {
  system_clock::time_point start_time = system_clock::now();
  cout << "Start reading data" << endl;

  boost::asio::async_read(this->m_socket, this->m_buffer.prepare(this->m_config.getMaxFileSize()),
                          boost::bind(&Connection::handle_read, shared_from_this(),
                          boost::asio::placeholders::error,
                          boost::asio::placeholders::bytes_transferred));

  this->setTimer();
  system_clock::time_point end_time = system_clock::now();
  std::cout << "start: " << (end_time - start_time).count() << " nanoseconds" << std::endl;
}

void Connection::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
  system_clock::time_point start_time = system_clock::now();
  this->m_timer.cancel();

  this->m_transferred_amount += bytes_transferred;
  cout << "Got data: " << bytes_transferred << " bytes" << endl;
  cout << "Transferred amount: " << this->m_transferred_amount << " bytes" << endl;

  if (((!error) || (error == boost::asio::error::eof)) && (bytes_transferred > 0)) {
    this->m_buffer.commit(bytes_transferred);
    std::istream is(&this->m_buffer);
    std::string result(std::istreambuf_iterator<char>(is),{});
    cout << result << endl;
    this->writeToFile(result);
    if (this->m_transferred_amount < this->m_config.getMaxFileSize() || (error != boost::asio::error::eof)) {
      this->start();
    }
  } else {
    cerr << error.message() << endl;
  }

  system_clock::time_point end_time = system_clock::now();
  std::cout << "handle_read: " << (end_time - start_time).count() << " nanoseconds" << std::endl;
}

void Connection::setTimer() {
  this->m_timer.expires_after(std::chrono::seconds(this->m_config.getTimeout()));
  this->m_timer.async_wait(boost::bind(&Connection::onTimeout, shared_from_this(),boost::asio::placeholders::error));
}

void Connection::onTimeout(const boost::system::error_code& error) {
  if (error) {
    if (error != boost::asio::error::operation_aborted) {
      cerr << "Timeout: " << error.message() << endl;
    }
  } else {
    cout << "Timeout!" << endl;
    this->m_socket.cancel();
  }
}

string Connection::getNameDir() {
  string basename = "cns";
  string dateTime = this->m_connectionTime;
  int opt = 0;
  string dir_name = basename + "_" + dateTime;

  while(std::filesystem::is_directory(dir_name)
        || std::filesystem::exists(dir_name)) {
    cout << "Checking for dir " << dir_name << endl;
    dir_name = basename + "_" + dateTime + "_" + to_string(++opt);
  }
  return dir_name;
}

void Connection::makeDir(string dir_name) {
  if(!(std::filesystem::is_directory(dir_name)
        && std::filesystem::exists(dir_name))) {
    std::filesystem::create_directory(dir_name);
  }
}

string Connection::createFilePath(const string dir) {
  string basename = this->m_config.getFileNamePrefix();
  string dateTime = this->m_connectionTime;
  int opt = 0;
  string file_name = basename + "_" + dateTime;
  string file_path = dir + "/" + file_name;

  while(std::filesystem::is_directory(dir)
        && std::filesystem::exists(file_path)) {
    cout << "Checking for file path " << file_path << endl;
    file_name = basename + "_" + dateTime + "_" + to_string(++opt);
    file_path = dir + "/" + file_name;
  }

  return file_path;
}

string Connection::getConnectionTime() {
	time_t curr_time;
	tm * curr_tm;
	char date_string[16];

	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(date_string, 16, "%Y%m%d%H%M%S", curr_tm);

  return date_string;
}

void Connection::writeToFile(const string data) {
  system_clock::time_point start_time = system_clock::now();

  this->makeDir(this->m_connectionDirName);
  string dir_name = this->m_connectionDirName;
  string file_path = this->createFilePath(dir_name);

  cout << "Writing file " << file_path << endl;
  ofstream file;
  file.open(file_path);
  file << data;
  file.close();

  system_clock::time_point end_time = system_clock::now();
  std::cout << "writeToFile: " << (end_time - start_time).count() << " nanoseconds" << std::endl;
}
