#include <gtest/gtest.h>

#include "ClientProtocol.h"
#include "ServerProtocol.h"
#include "SimulatedSocket.h"

#include <Collidable.h>


//  PROTOCOL TESTS
TEST(ClientToServer, SendCreate) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>("SALA", TypeGame(SURVIVAL_CODE), TypeOperator(SCOUT_CODE), TypeDifficulty(DIFFICULTY_HARD));
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
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(22, TypeOperator(IDF_CODE));
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_join, recvEvent.getEvent());
  EXPECT_EQ(22, recvEvent.getN());
  EXPECT_EQ(TypeOperator::operator_idf, recvEvent.getTypeOperator());
}

TEST(ClientToServer, SendStartGame) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_start_game, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_start_game, recvEvent.getEvent());
}

TEST(ClientToServer, SendMove) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_move, MoveTo::move_up, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_move, recvEvent.getEvent());
  EXPECT_EQ(MoveTo::move_up, recvEvent.getMoveTo());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendStopMove) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_stop_move, MoveTo::move_down, 6);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_stop_move, recvEvent.getEvent());
  EXPECT_EQ(MoveTo::move_down, recvEvent.getMoveTo());
  EXPECT_EQ(6, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendSmoke) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_throw_smoke, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_throw_smoke, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendStopSmoke) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_stop_smoke, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_stop_smoke, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendGrenade) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_throw_grenade, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_throw_grenade, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendStopGrenade) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_stop_grenade, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_stop_grenade, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendBlitz) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_blitz_atack, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_blitz_atack, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendShoot) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_shoot, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_shoot, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendStopShoot) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_stop_shoot, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_stop_shoot, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendLeave) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_leave, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_leave, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendRecharge) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_recharge, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_recharge, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendReanimate) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_reanimate, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_reanimate, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendStopReanimate) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_stop_reanimate, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_stop_reanimate, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendCheatFinish) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_cheat_finish_game, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_cheat_finish_game, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendCheatMunition) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_cheat_infinite_munition, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_cheat_infinite_munition, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendCheatVelocity) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_cheat_more_velocity, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_cheat_more_velocity, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendCheatKills) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_cheat_kill_enemies, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_cheat_kill_enemies, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ClientToServer, SendCheatHealth) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<EventDTO> event = std::make_shared<EventDTO>(Event::event_cheat_infinite_health, 2);
  client.sendEvent(event, skt);
  EventDTO recvEvent = server.getEvent(skt);
  EXPECT_EQ(Event::event_cheat_infinite_health, recvEvent.getEvent());
  EXPECT_EQ(2, recvEvent.getIdPlayer());
}

TEST(ServerToClient, SendCreate) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<Snapshot> snap = std::make_shared<Snapshot>(Event::event_create, 22, 6);
  server.sendSnapshot(snap, skt);
  Snapshot recvSnap = client.getSnapshot(skt);
  EXPECT_EQ(Event::event_create, recvSnap.getEvent());
  EXPECT_EQ(22, recvSnap.getCode());
  EXPECT_EQ(6, recvSnap.getIdPlayer());
}

TEST(ServerToClient, SendJoin) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;
  std::shared_ptr<Snapshot> snap = std::make_shared<Snapshot>(Event::event_join, 0x00, 6, 3);
  server.sendSnapshot(snap, skt);
  Snapshot recvSnap = client.getSnapshot(skt);
  EXPECT_EQ(Event::event_join, recvSnap.getEvent());
  EXPECT_EQ(0, recvSnap.getOk());
  EXPECT_EQ(6, recvSnap.getIdPlayer());
  EXPECT_EQ(3, recvSnap.getSize());
}

TEST(ServerToClient, SendStart) {
  std::shared_ptr<SimulatedSocket> skt = std::make_shared<SimulatedSocket>();
  ClientProtocol<SimulatedSocket> client;
  ServerProtocol<SimulatedSocket> server;

  std::vector<StOperator> playersInfo;
  playersInfo.push_back(StOperator(3,
                                  TypeOperator::operator_scout,
                                  State::moving,
                                  std::pair<int16_t, int16_t>(22,33), 
                                  30,
                                  22));

  
  std::vector<EnemyDto> enemies;
  enemies.push_back(EnemyDto(1,
                            TypeInfected::infected_zombie,
                            State::atack,
                            std::pair<int16_t, int16_t>(15,40)));

  std::vector<ObstacleDto> obsts;
  obsts.push_back(ObstacleDto(5,
                              TypeObstacle::obstacle_crater,
                              std::pair<int16_t, int16_t>(8,30)));
    
  std::shared_ptr<Snapshot> snap = std::make_shared<Snapshot>(playersInfo, enemies, obsts, TypeGame::game_survival, 2);
  
  server.sendSnapshot(snap, skt);
  Snapshot recvSnap = client.getSnapshot(skt);

  EXPECT_EQ(Event::event_start_game, recvSnap.getEvent());
  EXPECT_EQ(TypeGame::game_survival, recvSnap.getTypeGame());
  EXPECT_EQ(2, recvSnap.getMap());

  StOperator recvOp = recvSnap.getInfo().at(0);
  EXPECT_EQ(3, recvOp.getId());
  EXPECT_EQ(TypeOperator::operator_scout, recvOp.getTypeOperator());
  EXPECT_EQ(State::moving, recvOp.getState());
  EXPECT_EQ(22, recvOp.getPosition().first);
  EXPECT_EQ(33, recvOp.getPosition().second);
  EXPECT_EQ(30, recvOp.getHealth());
  EXPECT_EQ(22, recvOp.getMunition());

  EnemyDto recvEn = recvSnap.getEnemies().at(0);
  EXPECT_EQ(1, recvEn.getId());
  EXPECT_EQ(TypeInfected::infected_zombie, recvEn.getTypeInfected());
  EXPECT_EQ(State::atack, recvEn.getState());
  EXPECT_EQ(15, recvEn.getPosition().first);
  EXPECT_EQ(40, recvEn.getPosition().second);

  ObstacleDto recvOb = recvSnap.getObstacles().at(0);
  EXPECT_EQ(5, recvOb.getId());
  EXPECT_EQ(TypeObstacle::obstacle_crater, recvOb.getTypeObstacle());
  EXPECT_EQ(8, recvOb.getPosition().first);
  EXPECT_EQ(30, recvOb.getPosition().second);
}
/*
sendPlaying
sendEnd
sendStats
*/

//  COLLIDABLE TESTS

TEST(Collidable, FalseCollidesWith) {
  std::pair<int16_t, int16_t> posFirst(10, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(30, 30);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);

  std::map<uint8_t, std::shared_ptr<Collidable>> collidables;
  collidables.insert(std::make_pair(2, second));
  
  EXPECT_EQ(false, first.collidesWith(collidables));
}


TEST(Collidable, TrueCollidesWith) {
  std::pair<int16_t, int16_t> posFirst(10, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(10, 10);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);

  std::map<uint8_t, std::shared_ptr<Collidable>> collidables;
  collidables.insert(std::make_pair(2, second));
  
  EXPECT_EQ(true, first.collidesWith(collidables));
}

TEST(Collidable, TrueLeftCollidesWith) {
  std::pair<int16_t, int16_t> posFirst(15, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(10, 10);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);

  std::map<uint8_t, std::shared_ptr<Collidable>> collidables;
  collidables.insert(std::make_pair(2, second));
  
  EXPECT_EQ(true, first.collidesWith(collidables));
}

TEST(Collidable, TrueRightCollidesWith) {
  std::pair<int16_t, int16_t> posFirst(10, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(15, 10);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);

  std::map<uint8_t, std::shared_ptr<Collidable>> collidables;
  collidables.insert(std::make_pair(2, second));
  
  EXPECT_EQ(true, first.collidesWith(collidables));
}

TEST(Collidable, TrueUpCollidesWith) {
  std::pair<int16_t, int16_t> posFirst(10, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(10, 15);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);

  std::map<uint8_t, std::shared_ptr<Collidable>> collidables;
  collidables.insert(std::make_pair(2, second));
  
  EXPECT_EQ(true, first.collidesWith(collidables));
}

TEST(Collidable, TrueDownCollidesWith) {
  std::pair<int16_t, int16_t> posFirst(10, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(10, 5);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);

  std::map<uint8_t, std::shared_ptr<Collidable>> collidables;
  collidables.insert(std::make_pair(2, second));
  
  EXPECT_EQ(true, first.collidesWith(collidables));
}

TEST(Collidable, FalseIsAlignedRight) {
  std::pair<int16_t, int16_t> posFirst(10, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(18, 20);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);
  
  EXPECT_EQ(false, first.isAlignedRight(second));
}

TEST(Collidable, TrueIsAlignedRight) {
  std::pair<int16_t, int16_t> posFirst(10, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(18, 10);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);
  
  EXPECT_EQ(true, first.isAlignedRight(second));
}

TEST(Collidable, FalseIsAlignedLeft) {
  std::pair<int16_t, int16_t> posFirst(20, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(12, 20);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);
  
  EXPECT_EQ(false, first.isAlignedLeft(second));
}

TEST(Collidable, TrueIsAlignedLeft) {
  std::pair<int16_t, int16_t> posFirst(20, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(12, 10);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);
  
  EXPECT_EQ(true, first.isAlignedLeft(second));
}

TEST(Collidable, FalseIsCloseTo) {
  std::pair<int16_t, int16_t> posFirst(5, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(15, 10);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);
  
  EXPECT_EQ(false, first.isCloseTo(second, 2));
}

TEST(Collidable, TrueFalseIsCloseTo) {
  std::pair<int16_t, int16_t> posFirst(5, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(15, 10);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);
  
  EXPECT_EQ(true, first.isCloseTo(second, 11));
}


// isOnRight method -> other is on my right side?

TEST(Collidable, FalseIsOnRight) {
  std::pair<int16_t, int16_t> posFirst(15, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(5, 10);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);
  
  EXPECT_EQ(false, first.isOnRight(second));
}

TEST(Collidable, TrueIsOnRight) {
  std::pair<int16_t, int16_t> posFirst(5, 10);
  Collidable first(1, posFirst, 6, 6);
  std::pair<int16_t, int16_t> postSecond(15, 10);
  std::shared_ptr<Collidable> second = std::make_shared<Collidable>(2, postSecond, 6, 6);
  
  EXPECT_EQ(true, first.isOnRight(second));
}

// isDown(std::shared_ptr<Collidable>& other);

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
