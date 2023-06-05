#include <gtest/gtest.h>
#include "ClientProtocol.h"
#include "ServerProtocol.h"
#include "Socket.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
/*
TEST(ClientToServer, SendCreate) {
  MockSocket skt;
  ClientProtocol client(skt);
  ServerProtocol server(skt);
  EventDTO event(Event::event_create, MoveTo::move_not, "", 0);
  client.sendEvent(event);
  EXPECT_EQ(Event::event_create, server.getEvent().getEvent());
}

TEST(ClientToServer, SendJoin) {
  MockSocket skt;
  ClientProtocol client(skt);
  ServerProtocol server(skt);
  EventDTO event(Event::event_join, MoveTo::move_not, "", 11);
  client.sendEvent(event);
  EXPECT_EQ(Event::event_join, server.getEvent().getEvent());
}

TEST(ClientToServer, SendJoinCorrectCode) {
  MockSocket skt;
  ClientProtocol client(skt);
  ServerProtocol server(skt);
  EventDTO event(Event::event_join, MoveTo::move_not, "", 11);
  client.sendEvent(event);
  EXPECT_EQ(11, server.getEvent().getN());
}
*/
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

