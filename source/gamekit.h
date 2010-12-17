#ifndef _GAME_KIT_H
#define _GAME_KIT_H

#include <list>
#include <string.h>

#include "s3e.h"
#include "s3eExt_OSReadString.h"
#include "s3eExt_IPhoneGameKit.h"
#include "s3eExt_IPhone.h"

#include "muncher.h"
#include "shooter.h"
#include "wrecker.h"
#include "spreader.h"
#include "thrower.h"
#include "leader.h"

class GameKitPlayer;
#include "game.h"

#define SESSION_ID_STRING "_s3echatexample._tcp"

struct gk_data_t {
    unit_type type;
    float x, y;
};

// GameKit data -- move me into class plz
static bool connected;
static s3eGKPeer* peers[2];
static s3eGKSession *session;
static std::list<Unit *> queued_units;

class GameKitPlayer : public RemotePlayer {
    private:
        bool sychronized;
    
        // Callbacks
        static void sendData(const float*);
        static void sessConnected(s3eGKSession*,       s3eGKSessionConnectResult*,         void*);
        static void peerConnected(s3eGKSession*,       s3eGKSessionPeerConnectAttempt*,    void*);
        static void receivedData(s3eGKSession*,        s3eGKSessionRecievedData*,          void*);
        static void sessDisconnected(s3eGKSession*,    s3eGKSessionDisconnectInfo*,        void*);
        
    public:
        GameKitPlayer(CIwColour& col);
        virtual bool connect();
        
        virtual void sendUpdate(Unit *);
        virtual void applyUpdates();
        
        virtual void sendSync();
        virtual void receiveSync();
};

#endif
