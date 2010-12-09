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
OR sendSync, and then to call applyUpdates. IT IS THE RESPONSIBILITY OF MAIN TO ENSURE THAT s3eExtIPhoneGameKitAvailable
RETURNS TRUE BEFORE USING gkp.
 
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

    
    s3eGKPeer* peers[1]; 
    uint32 num = s3eGKSessionGetPeersWithConnectionState(session, S3E_GKPEER_STATE_AVAILABLE, peers, 1);
    
    s3eDeviceYield(500);
    
    if(num){
        peer = peers[0];
        return S3E_RESULT_SUCCESS == s3eGKConnectToPeer(session, peer, 10);
    } else {
        return false;
    }
}

void GameKitPlayer::sendUpdate(Unit *u){
    if(!session) return;

    gk_data_t *data = (gk_data_t *) malloc(sizeof(gk_data_t));
    data->type = u->getType();
    data->x = u->getPosition().x;
    data->y = u->getPosition().y;
    sendData(data);
    free(data);
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
    
    while(queued_units.empty() && !sychronized){
        s3eDeviceYield();
    }
    
    for(std::list<gk_data_t *>::iterator itr = queued_units.begin(); itr != queued_units.end(); ++itr){
        Unit *u = NULL;
        switch ((*itr)->type) {
            case MUNCHER:  u = new  Muncher(this, game, (*itr)->x, (*itr)->y); break;
            case SPREADER: u = new Spreader(this, game, (*itr)->x, (*itr)->y); break;
            case WRECKER:  u = new  Wrecker(this, game, (*itr)->x, (*itr)->y); break;
            case SHOOTER:  u = new  Shooter(this, game, (*itr)->x, (*itr)->y); break;
            case THROWER:  u = new  Thrower(this, game, (*itr)->x, (*itr)->y); break;
                
            default: break;
        }
        
        if(u != NULL)
            game->addUnit(u, false);
    }
    
    sychronized = false;
}

// CALLBACKS
void GameKitPlayer::sendData(const gk_data_t *data){
    if(!session) return;
    
    if(data == NULL)
        s3eGKSessionSendDataToAllPeers(session, 0, 0, S3E_GK_SEND_DATA_RELIABLE);
    else
        s3eGKSessionSendDataToAllPeers(session, (void *) data, sizeof(gk_data_t), S3E_GK_SEND_DATA_RELIABLE);
}

void GameKitPlayer::sessConnected(s3eGKSession* sess, s3eGKSessionConnectResult* result, void* userData){}

void GameKitPlayer::peerConnected(s3eGKSession* sess, s3eGKSessionPeerConnectAttempt* connectInfo, void* userData){   
    connectInfo->m_accept = S3E_TRUE;     
}

void GameKitPlayer::receivedData(s3eGKSession* sess, s3eGKSessionRecievedData* data, void* userData){

    if(data->m_dataSize < sizeof(gk_data_t))
        ((GameKitPlayer *)userData)->receiveSync();
    
    //queued_units.push_back((gk_data_t *) data->m_data);
}

void GameKitPlayer::sessDisconnected(s3eGKSession* sess, s3eGKSessionDisconnectInfo* info, void* userData){}
