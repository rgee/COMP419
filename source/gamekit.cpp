#include "gamekit.h"

bool connected = false;
static std::set<s3eGKPeer*> gConnectingSet;
s3eGKPeer* peer;
bool session = false;
static s3eGKSession* g_GKSession = 0;

void GKSessionConnectionCallback(s3eGKSession* session, s3eGKSessionConnectResult* result, void* userData)
{
    const char *pPeerName = s3eGKPeerGetString(result->m_peer, S3E_GKPEER_DISPLAY_NAME);    
    
    printf("`x66ee66GKSessionConnectionCallback %s %s"/*,pPeerName*/);
    
    std::set<s3eGKPeer*>::iterator iter = gConnectingSet.find(result->m_peer);
    
    if (iter != gConnectingSet.end()){
        gConnectingSet.erase(iter);
    }
    
}
void GKSessionPeerAttemptedToConnectCallback(s3eGKSession* session, s3eGKSessionPeerConnectAttempt* connectInfo, void* userData)
{   
    const char *pPeerName = s3eGKPeerGetString(connectInfo->m_peer, S3E_GKPEER_DISPLAY_NAME);   
    
    connectInfo->m_accept = S3E_TRUE;   
    
    printf("`x6666ee'%s' `x66ee66Connected"/*pPeerName*/);    
}
void GKSessionRecieveDataCallback(s3eGKSession* session, s3eGKSessionRecievedData* data, void* userData)
{
    const char *pPeerName = s3eGKPeerGetString(data->m_peer, S3E_GKPEER_DISPLAY_NAME);
    
    printf("`x66ee66%s: `x666666%s"/*+pPeerName+(char*)data->m_data*/);
    //ProcessCommand((char*)data->m_data);
}

void GKSessionDisconnectionCallback(s3eGKSession* session, s3eGKSessionDisconnectInfo* info, void* userData)
{
    if (info->m_peer)
    {
        // A peer disconnected
        const char *pPeerName = s3eGKPeerGetString(info->m_peer, S3E_GKPEER_DISPLAY_NAME);  
        printf("`x6666ee'%s' `xee6666Disconnected", pPeerName);
    }
    else // An error occured with the session
    {
        if (info->m_error == S3E_IPHONEGAMEKIT_ERR_BLUETOOTH_DISABLED)
            printf("`x6666eeSession failed: bluetooth is disabled");
        else if (info->m_error == S3E_IPHONEGAMEKIT_ERR_BLUETOOTH_NOT_SUPPORTED)
            printf("`x6666eeSession failed: bluetooth is unsupported");
        else
            printf("`x6666eeSession failed with error '%d'", info->m_error);
        
        // Stop the session due to error and reset all the buttons
        s3eIPhoneGameKitStopSession(session);
        g_GKSession = NULL;
        connected = false;
    }
}

void ProcessCommand(char* data){
    printf("THIS SHIT WORKS");
}


void ExampleInit()
{
    if (!s3eExtIPhoneGameKitAvailable())
        return;
    
    s3eDeviceRegister(S3E_DEVICE_NOTIFY_PUSH_NOTIFICATION, PushNotificationRecieved, 0);
    
}

bool ExampleUpdate(){
    
    if(!s3eExtIPhoneGameKitAvailable())
        return false;
    
    if(!session){
        g_GKSession = s3eIPhoneGameKitStartSession(SESSION_ID_STRING, 
                                                   0, 
                                                   S3E_GKSESSION_MODE_PEER, 
                                                   GKSessionConnectionCallback, 
                                                   GKSessionPeerAttemptedToConnectCallback, 
                                                   GKSessionRecieveDataCallback, 
                                                   GKSessionDisconnectionCallback,
                                                   0);
    }
    
    if(!connected){
        uint32 s3eGKSessionGetPeersWithConnectionState(s3eGKSession *session,
                                                       s3eGKPeerConnectionState state,
                                                       s3eGKPeer ** 	peers,
                                                       uint32 	maxPeers);
        connected = true;
        session = true;
    }
    
    
    if(connected){
        s3eGKPeer* peers[1]; 
        
        // Find all available peers (devices using the same session ID but not yet connected)
        // Servers cannot search for other peers to connect to (will return 0)
        uint32 num = s3eGKSessionGetPeersWithConnectionState(g_GKSession, 
                                                             S3E_GKPEER_STATE_AVAILABLE,
                                                             peers,
                                                             1);
        
        // Yield substantially to allow OS to perform internal Bluetooth tasks
        s3eDeviceYield(500);
        
        if (num > 1)
            num = 1;
        
        // For each peer found, try to connect to it
        for (uint32 i = 0; i < num; i++)
        {
            if (gConnectingSet.find(peers[i]) == gConnectingSet.end())
            {       
                gConnectingSet.insert(peers[i]);
                s3eGKConnectToPeer(g_GKSession, peers[i], 10);
            }
        }
        return false;
    }
    
    return true;
}

int32 PushNotificationRecieved(void* systemData, void* userData)
{
    return 0;
}



