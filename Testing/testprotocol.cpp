#include <gtest/gtest.h>
#include "ClientProtocol.h"
#include "ServerProtocol.h"
#include "SimulatedSocket.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(ClientToServer, SendCreate) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  EventDTO event("SALA", TypeGame(SURVIVAL_CODE), TypeOperator(SCOUT_CODE), TypeDifficulty(DIFFICULTY_HARD));
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_create, recvEvent.getEvent());
  EXPECT_EQ(TypeGame::game_survival, recvEvent.getTypeGame());
  EXPECT_EQ(TypeOperator::operator_scout, recvEvent.getTypeOperator());
  EXPECT_EQ(TypeDifficulty::difficulty_hard, recvEvent.getTypeDifficulty());
  EXPECT_EQ("SALA", recvEvent.getStr());
}

TEST(ClientToServer, SendJoin) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  EventDTO event(22, TypeOperator(IDF_CODE));
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_join, recvEvent.getEvent());
  EXPECT_EQ(22, recvEvent.getN());
  EXPECT_EQ(TypeOperator::operator_idf, recvEvent.getTypeOperator());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
