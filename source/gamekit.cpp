#include "gamekit.h"

/* EXPLANATION OF MULTIPLAYER

When a GameKitPlayer (GKP) is created, it will open up a ad hoc GameKit session.
 
When remotePlayer.connect() is called by Game, GKP will see if there are peers and try to connect.
If it cannot, it will return false. This function should be while-looped.
 
When local player creates a unit u, Game calls remotePlayer.sendUpdate(u).
For GKP, it will immediately dispatch {unit type, unit x, unit y} to its peer.
 
At every synchronization frame, if there are no units being created, Game will call remotePlayer.sendSync().
GKP will dispatch an empty message to its peer, informing it of the sync.
 
When s3eDeviceYield is ever called, if a peer has sent a message, GKP will process any messages received.
If it receives a sync, it will toggle a flag. If it receives a unit, it'll queue it up.
 
When Game calls remotePlayer.applyUpdates(), GKP will s3eDeviceYield until it gets a sync or a unit.
It will then add any queued units to the game.
 
IT IS THE RESPONSIBILITY OF THE GAME TO DECIDE WHAT FRAMES ARE SYNC FRAMES AND TO EITHER CALL sendUpdate
OR sendSync, and then to call applyUpdates.
 
 */


GameKitPlayer::GameKitPlayer(CIwColour& col) : RemotePlayer(col), sychronized(true) {
    if(s3eExtIPhoneGameKitAvailable())
        session = s3eIPhoneGameKitStartSession(SESSION_ID_STRING, 0, S3E_GKSESSION_MODE_PEER,
                                               sessConnected,
                                               peerConnected,
                                               receivedData,
                                               sessDisconnected, this);
}

bool GameKitPlayer::connect(){
    if(!session) return false;
    
    uint32 num = s3eGKSessionGetPeersWithConnectionState(session, S3E_GKPEER_STATE_AVAILABLE, peers, 2);
    
    s3eDeviceYield(500);
    
    if(num){
        if(num >= 2)
             if(S3E_RESULT_SUCCESS != s3eGKConnectToPeer(session, peers[1], 30))
                 return false;
        return S3E_RESULT_SUCCESS == s3eGKConnectToPeer(session, peers[0], 30);
    } else {
        return false;
    }
}

void GameKitPlayer::sendUpdate(Unit *u){        
//    gk_data_t data = {u->getType(), u->getPosition().x, u->getPosition().y};
    float data[] = {(float) u->getType(), u->getPosition().x, u->getPosition().y};
    sendData(data);
}

void GameKitPlayer::sendSync(){
    if(!session) return;

    sendData(NULL);
}

void GameKitPlayer::receiveSync(){
    sychronized = true;
}

void GameKitPlayer::applyUpdates(){
    if(!session) return;
    
    while(false && queued_units.empty() && !sychronized){
        s3eDeviceYield(0);
    }
    
    for(std::list<float *>::iterator itr = queued_units.begin(); itr != queued_units.end(); ++itr){
        Unit *u = NULL;
        
        //char *msg;
//        asprintf(&msg, "Type, X, Y : %d, %f, %f", (*itr)->type, *(data + 1), *(data + 2));
//        s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, msg);
        
        float *data = *itr;
                
        switch ((int) (*data)) {
            case MUNCHER:  u = new  Muncher(this, game, *(data + 1), *(data + 2)); break;
            case SPREADER: u = new Spreader(this, game, *(data + 1), *(data + 2)); break;
            case WRECKER:  u = new  Wrecker(this, game, *(data + 1), *(data + 2)); break;
            case SHOOTER:  u = new  Shooter(this, game, *(data + 1), *(data + 2)); break;
            case THROWER:  u = new  Thrower(this, game, *(data + 1), *(data + 2)); break;
                
            default: break;
        }
                
        if(u != NULL)
            game->addUnit(u, false);
    }
    
    
    queued_units.clear();
    
    sychronized = false;
}

// CALLBACKS
void GameKitPlayer::sendData(const float *data){
    if(!session) return;

    
    if(data == NULL)
        s3eGKSessionSendDataToAllPeers(session, 0, 1, S3E_GK_SEND_DATA_RELIABLE);
    else {
        s3eGKSessionSendDataToAllPeers(session, data, sizeof(float)*3, S3E_GK_SEND_DATA_RELIABLE);
        //int i[] = {4, 2, 3};
//        s3eGKSessionSendDataToAllPeers(session, i, sizeof(int) * 3, S3E_GK_SEND_DATA_RELIABLE);
//        char *msg;
//        asprintf(&msg, "> %d %d %d", *i, *(i+1), *(i+2));
//        s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, msg);
    }
    
}

void GameKitPlayer::sessConnected(s3eGKSession* sess, s3eGKSessionConnectResult* result, void* userData){}
void GameKitPlayer::sessDisconnected(s3eGKSession* sess, s3eGKSessionDisconnectInfo* info, void* userData){}

void GameKitPlayer::peerConnected(s3eGKSession* sess, s3eGKSessionPeerConnectAttempt* connectInfo, void* userData){   
    const char *pPeerName = s3eGKPeerGetString(connectInfo->m_peer, S3E_GKPEER_DISPLAY_NAME);

    s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, pPeerName);

    connectInfo->m_accept = S3E_TRUE;     
}

void GameKitPlayer::receivedData(s3eGKSession* sess, s3eGKSessionRecievedData* data, void* userData){
    char *msg;
    float *i = (float *) data->m_data;
    asprintf(&msg, "%f %f %f", *i, *(i+1), *(i+2));
    s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, msg);

    
    if(data->m_dataSize < sizeof(float)*3)
        ((GameKitPlayer *)userData)->receiveSync();
    else
        queued_units.push_back((float *) data->m_data);
    
}

