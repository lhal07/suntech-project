#include "server.h"
#include "gtest/gtest.h"

using namespace std;

class ServerTest : public ::testing::Test {

protected:
  const string salutation = "Hi!";

  virtual void SetUp() {
  };

  virtual void TearDown() {
  };

  virtual void verify() {
  }
};

TEST_F(ServerTest, salutation) {
  verify();
}
