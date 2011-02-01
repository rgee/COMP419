#include "util.h"

float min(float x, float y){
	return x > y ? y : x;
}

void renderImageWorldSpace(CIwFVec2& position, float angle, float scaleFactor,
                        int textureSize, float worldRot, int frameNumber, int numFrames, float z) {
	
	static CIwSVec3 vertices[4];
	static CIwSVec2 UVs[4];
	
	//set up model space vertices
	
	int vertexDist = scaleFactor*textureSize/2;
	
	vertices[0] = CIwSVec3(-1*vertexDist, -1*vertexDist, z);
	vertices[2] = CIwSVec3(vertexDist, -1*vertexDist,    z);
	vertices[3] = CIwSVec3(vertexDist, vertexDist,       z);
	vertices[1] = CIwSVec3(-1*vertexDist, vertexDist,    z);
	
	CIwMat modelTransform = CIwMat::g_Identity;
	modelTransform.SetRotZ(IW_ANGLE_FROM_RADIANS(angle));
	modelTransform.SetTrans(CIwVec3(position.x, -position.y, 0));
	    
	CIwMat rot = CIwMat::g_Identity;
 	rot.SetRotZ(IW_ANGLE_FROM_RADIANS(worldRot));
	modelTransform = modelTransform*rot;
	
	IwGxSetModelMatrix(&modelTransform, false);
	
	float frameRatio = 1.0/numFrames;
	
	//set up sprite UV's
    
    iwfixed cf = IW_FIXED((float)frameNumber  / numFrames);
    iwfixed nf = IW_FIXED((frameNumber + 1.0) / numFrames);
    
	UVs[0] = CIwSVec2(cf, 0);
	UVs[2] = CIwSVec2(nf, 0);
	UVs[3] = CIwSVec2(nf, IW_GEOM_ONE);
	UVs[1] = CIwSVec2(cf, IW_GEOM_ONE);
		
	//render the unit in model space
	IwGxSetUVStream(UVs);
	
	IwGxSetZDepthFixed(8);	
	
	IwGxSetVertStreamModelSpace(vertices, 4);
	IwGxDrawPrims(IW_GX_QUAD_STRIP, NULL, 4);
	
    IwGxFlush();
}

void polarize(CIwFVec2& v){
    float r = v.GetLength();
    v.y = atan2(v.y, v.x);
    v.x = r;
}

CIwFVec2 worldify(int32 x, int32 y, float innerRadius, float rotation){
    int h = IwGxGetScreenHeight();
            
    int32 world_x = x + (innerRadius - 10);
    int32 world_y = h/2 - y;
    
    rotation = -rotation;
    
    // Rotates (world_x, world_y) around world origin (w/2 + radii.x - 20, h/2) by theta
    
    return CIwFVec2(world_x * cos(rotation) - world_y * sin(rotation),
                    world_x * sin(rotation) + world_y * cos(rotation));
    
}

float angle_diff(const CIwFVec2& pos1, const CIwFVec2&  pos2) {
	return atan2(pos2.y, pos2.x) - atan2(pos1.y, pos1.x);
}


bool isInWorld(CIwFVec2 position, float innerRad, float outerRad) {
	polarize(position);
	return position.x > innerRad &&  position.x < outerRad;
}
void polarToXY(CIwFVec2& v) {
	float r     = v.x;
	float theta = v.y;
    
	v.x = r * cos(theta);
	v.y = r * sin(theta);
}


template <class TList>
void wrapIncr(TList& lst, typename TList::iterator itr){
    itr++;
    if(itr == lst.end()) itr = lst.begin();
}

template <class TList>
void wrapDecr(TList& lst, typename TList::iterator itr){
    if(itr == lst.begin()) itr = lst.end();
    itr--;
}

void CNode::remove(){
    prev->next = next;
    next->prev = prev;
    delete this;
}

CList::CList(){
    head = NULL;
}

void CList::insert(WorldObject& w){
    if(head == NULL){
        head = new CNode();
        head->value = &w;
        head->next = head;
        head->prev = head;
    } else {
        CNode *newNode = new CNode();
        newNode->value = &w;
        
        newNode->prev = head->prev;
        newNode->next = head;
        
        head->prev = newNode;        
        newNode->prev->next = newNode;
    }
}

void CList::sort(){
    bool swapped = true;
    
    while(swapped){
        swapped = false;
        CNode *itr = head;
        
        while(itr->next != head){
            if(itr->next->value->getTheta() < itr->value->getTheta()){
                
                WorldObject *w = itr->value;
                itr->value = itr->next->value;
                itr->next->value = w;
                
                swapped = true;
            }
            
            itr = itr->next;
        }   
    }
}
