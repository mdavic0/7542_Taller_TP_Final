#include <gtest/gtest.h>
#include "client_protocol.h"
#include "server_protocol.h"
#include "common_socket.h"



// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(ClientToServer, SendCreate) {
  MockSocket skt;
  ClientProtocol client(skt);
  ServerProtocol server(skt);
  EventDTO event(Event::event_create, "", 0);
  client.sendEvent(event);
  EXPECT_EQ(Event::event_create, server.getEvent().getEvent());
}

TEST(ClientToServer, SendJoin) {
  MockSocket skt;
  ClientProtocol client(skt);
  ServerProtocol server(skt);
  EventDTO event(Event::event_join, "", 11);
  client.sendEvent(event);
  EXPECT_EQ(Event::event_join, server.getEvent().getEvent());
}

TEST(ClientToServer, SendJoinCorrectCode) {
  MockSocket skt;
  ClientProtocol client(skt);
  ServerProtocol server(skt);
  EventDTO event(Event::event_join, "", 11);
  client.sendEvent(event);
  EXPECT_EQ(11, server.getEvent().getN());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
