#ifndef _GAME_H
#define _GAME_H

#include "s3e.h"
#include "s3eExt_OSReadString.h"
#include "s3eExt_IPhoneGameKit.h"
#include "s3eExt_EMail.h"
#include "s3eExt_BackgroundMusic.h"
#include "s3eExt_BackgroundAudio.h"
#include "s3eExt_IPhone.h"
#include <set>
#include <string.h>

#define SESSION_ID_STRING "_s3echatexample._tcp"
#define S3E_DEVICE_NOTIFY_PUSH_NOTIFICATION S3E_DEVICE_PUSH_NOTIFICATION



bool connected = false;
static std::set<s3eGKPeer*> gConnectingSet;
s3eGKPeer* peer;
bool session = false;
static s3eGKSession* g_GKSession = 0;


void GKSessionConnectionCallback(struct s3eGKSession* session, s3eGKSessionConnectResult* result, void* userData);
void GKSessionPeerAttemptedToConnectCallback(struct s3eGKSession* session, s3eGKSessionPeerConnectAttempt* result, void* userData);
void GKSessionRecieveDataCallback(struct s3eGKSession* session, s3eGKSessionRecievedData* result, void* userData);
void GKSessionDisconnectionCallback(struct s3eGKSession* session, s3eGKSessionDisconnectInfo* result, void* userData);

void ProcessCommand(char* data);

void ExampleInit();

bool ExampleUpdate();

#endif

