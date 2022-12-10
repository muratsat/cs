#include "bird.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

Bird::Bird() {}
Bird::~Bird() {}

void Bird::Initialize() {
  pid_ = getpid();

  // create key for message queue
  key_ = ftok("bird", 1);
  if (key_ < 0) {
    perror("ftok");
    exit(1);
  }

  // create message queue
  msg_id_ = msgget(key_, 0666 | IPC_CREAT);
  if (msg_id_ < 0) {
    perror("msgget");
    exit(1);
  }
}

void Bird::Uninitialize() {
  // delete message queue
  int status = msgctl(msg_id_, IPC_RMID, NULL);
  if (status < 0) {
    perror("msgctl");
    exit(1);
  }
}

void Bird::SendMessage(int type, int food_in_bowl) {
  // prepare message
  msg.mtype = type;
  msg.food_in_bowl = food_in_bowl;
  size_t msg_size = sizeof(msg);

  // send message
  int status = msgsnd(msg_id_, &msg, msg_size, 0);
  if (status < 0) {
    perror("msgsnd");
    exit(1);
  }
}

int Bird::ReceiveMessage(int type) {
  // receive message
  int status = msgrcv(msg_id_, &msg, sizeof(msg), type, 0);
  if (status < 0) {
    perror("msgrcv");
    exit(1);
  }

  return msg.food_in_bowl;
}
