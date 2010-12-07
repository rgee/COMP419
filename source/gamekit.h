#ifndef _GAME_KIT_H
#define _GAME_KIT_H

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


void GKSessionConnectionCallback(s3eGKSession* session, s3eGKSessionConnectResult* result, void* userData);
void GKSessionPeerAttemptedToConnectCallback(s3eGKSession* session, s3eGKSessionPeerConnectAttempt* result, void* userData);
void GKSessionRecieveDataCallback(s3eGKSession* session, s3eGKSessionRecievedData* result, void* userData);
void GKSessionDisconnectionCallback(s3eGKSession* session, s3eGKSessionDisconnectInfo* result, void* userData);
int32 PushNotificationRecieved(void* systemData, void* userData);

void ProcessCommand(char* data);

void ExampleInit();

bool ExampleUpdate();

#endif
