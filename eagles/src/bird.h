#pragma once
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#include <cstddef>

enum {
  BIRD_CALL_MOTHER = 1,
  BIRD_FOOD_READY = 2,
} MESSAGE_TYPES;

class Bird {
 public:
  Bird();
  virtual ~Bird() = 0;

  virtual void Action() = 0;

 protected:
  // process id
  pid_t pid_;

  // key for message queue
  key_t key_;

  // shared memory id
  int msg_id_;

  // message buffer
  struct msgbuf {
    long mtype;
    int food_in_bowl;
  } msg;

  // initialize message queue
  void Initialize();

  // uninitialize message queue
  void Uninitialize();

  // send message
  void SendMessage(int type, int food_in_bowl);

  // receive message
  int ReceiveMessage(int type);
};
