#include "game.h"
#include "unit.h"

Game::Game(Player* _local, RemotePlayer* opponent) : localPlayer(_local), opponentPlayer(opponent), numUnits(0), rotation(0),
        innerRadius(112*.85), outerRadius(358*.85), timesteps(0) {

    IwGetResManager()->LoadGroup("resource_groups/game.group");
	sprites = IwGetResManager()->GetGroupNamed("Sprites");
	game = IwGetResManager()->GetGroupNamed("Game");
	initRenderState();
            
    localIcing.clear();
    opponentIcing.clear();
                    
	CIwResList* resources = sprites->GetListHashed(IwHashString("CIwTexture"));
	for(CIwManaged** itr = resources->m_Resources.GetBegin(); itr != resources->m_Resources.GetEnd(); ++itr) {
		unitBucket[(*itr)->m_Hash] = new std::set<Unit*>();
	}
}  

Game::~Game(){
	
	for (UnitBucket::iterator itr = unitBucket.begin(); itr != unitBucket.end(); ++itr) {
		(*itr).second->clear();
		delete (*itr).second;
	}
	
	for(std::list<Unit*>::iterator itr = units.begin(); itr != units.end(); ++itr) {
		delete *itr;
	}
	
	for(std::list<Icing*>::iterator itr = localIcing.begin(); itr != localIcing.end(); ++itr) {
		delete *itr;
	}
	
	for(std::list<Icing*>::iterator itr = opponentIcing.begin(); itr != opponentIcing.end(); ++itr) {
		delete *itr;
	}
	
 	units.clear();
	unitBuffer.clear();
    unitBucket.clear();
	
	localIcing.clear();
	opponentIcing.clear();
    
    sprites->Finalise();
    game->Finalise();
}

UnitBucket* Game::getUnitBucket() {
	return &unitBucket;
}

void Game::initRenderState() {
	//set up the camera position and view transform
    int w = IwGxGetScreenWidth();

	IwGxSetPerspMul(9);
	IwGxSetFarZNearZ(12, 8);
	view = CIwMat::g_Identity;
	view.SetTrans(CIwVec3(innerRadius+w/2-30, 0, -9));
	IwGxSetViewMatrix(&view);
}

std::list<Unit*>* Game::getUnits(){
	return &units;
}
 
void Game::addIcing(Icing* i) {
		
	if (i->getOwner() == localPlayer) {
		
		if(localIcing.empty()) {
			localIcing.push_back(i);
		} else {
			localIcingBuffer.push_back(i);
		}
		
	} else {
		
		if(opponentIcing.empty()) {
			opponentIcing.push_back(i);
		} else {
			opponentIcingBuffer.push_back(i);
		}
		
	}
	
}


void Game::addUnit(Unit *u, bool pay){
    
    CIwFVec2 pos = u->getPosition();
    std::list<Icing*> *icing = &localIcing;
    
    if(&u->getOwner() == opponentPlayer)
        icing = &opponentIcing;
    else
        opponentPlayer->sendUpdate(u);

    
    bool paid_for = !pay;
    if(!paid_for && icing->size() > 0)
        for(std::list<Icing*>::iterator itr = icing->begin(); itr != icing->end(); ++itr){
            if(((*itr)->getPosition() - pos).GetLengthSquared() < 200){
                icing->erase(itr);
                paid_for = true;
                break;
            }
        }
        
    if(!paid_for)
        return;

    u->setId(numUnits++);

	if(units.empty()) {
		units.push_back(u);
	} else {
		unitBuffer.push_back(u);
	}
    	
	if(unitBucket.find(u->getTextureName()) == unitBucket.end())
		unitBucket[u->getTextureName()] = new std::set<Unit*>();
	
	(unitBucket[u->getTextureName()])->insert(u);

}

void Game::tick(){
    
    //if(true || timesteps % 2 == 0){
        //opponentPlayer->sendSync();
        //s3eExtOSReadUserStringUTF8("Sync sent");
        // opponentPlayer->applyUpdates();
    //}

	for(std::list<Unit*>::iterator itr = units.begin(); itr != units.end(); ++itr) {
        (*itr)->update(itr);
    }
    
    for(std::list<Unit*>::iterator itr = units.begin(); itr != units.end(); ++itr) {
        if((*itr)->getHp() < 0){
			// Remove the unit from all data structures
			unitBucket[(*itr)->getTextureName()]->erase(unitBucket[(*itr)->getTextureName()]->find((*itr)));
			
			delete (*itr);
            itr = units.erase(itr);

        }
    }  
	
	for(std::list<Icing*>::iterator itr = localIcing.begin(); itr != localIcing.end(); ++itr) {
        Icing* foo = *itr;
		(*itr)->update();
        
        //if(itr != localIcing.begin() &&
		//       ((*itr)->getPosition() + (*(itr-1))->getPosition())->GetLengthSquared() < 15)
		//  localIcing->erase(itr);
	}
	
	for(std::list<Icing*>::iterator itr = opponentIcing.begin(); itr != opponentIcing.end(); ++itr) {
		(*itr)->update();
	}
    
    unitBuffer.sort();
    units.merge(unitBuffer);
    
    localIcingBuffer.sort();
	localIcing.merge(localIcingBuffer);
    
    opponentIcingBuffer.sort();
	opponentIcing.merge(opponentIcingBuffer);
    
    ++timesteps;
}

void Game::render() {		    
	renderWorld();
	renderIcing();
	renderSprites();
}

void Game::renderSprites() {
	unsigned int curTexture = IwHashString("");
	CIwMaterial* mat = new CIwMaterial();
	
	for (UnitBucket::iterator itr = unitBucket.begin(); itr != unitBucket.end(); ++itr) {
        
		if (curTexture != (*itr).first != 0) {
			curTexture = (*itr).first;
			mat->SetTexture((CIwTexture*)sprites->GetResHashed(curTexture, IW_GX_RESTYPE_TEXTURE));
			mat->SetModulateMode(CIwMaterial::MODULATE_RGB);
			mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
			IwGxSetMaterial(mat);
		}
		
		std::set<Unit*>* renderUnits = (*itr).second;
		
		for (std::set<Unit*>::iterator u_it = renderUnits->begin(); u_it != renderUnits->end(); ++u_it) {
            if((*u_it)->getHp() <= 0){
                renderUnits->erase(u_it);
            }
            
			(*u_it)->display();
		}
	}
	
	delete mat;
}

void Game::renderIcing() {
	
	CIwMaterial* mat = new CIwMaterial();
	mat->SetTexture((CIwTexture*)game->GetResNamed("icing", IW_GX_RESTYPE_TEXTURE));
	mat->SetModulateMode(CIwMaterial::MODULATE_RGB);
	mat->SetAlphaMode(CIwMaterial::ALPHA_BLEND);
	IwGxSetMaterial(mat);
	
	for (std::list<Icing*>::iterator itr = localIcing.begin(); itr != localIcing.end(); ++itr) {
		(*itr)->display();
	}
	
	for (std::list<Icing*>::iterator itr = opponentIcing.begin(); itr != opponentIcing.end(); ++itr) {
		(*itr)->display();
	}
	
	delete mat;
}

void Game::renderWorld() {

	CIwMaterial* mat = new CIwMaterial();
	mat->SetTexture((CIwTexture*)game->GetResNamed("paper-world", IW_GX_RESTYPE_TEXTURE));
	mat->SetModulateMode(CIwMaterial::MODULATE_NONE);
	mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
	IwGxSetMaterial(mat);

	renderImageWorldSpace(CIwFVec2::g_Zero, 0.0, 0.85, 960, rotation, 0, 1, 0.0f);
	
	delete mat;
}

std::list<Icing*>* Game::getLocalIcing() {
	return &localIcing;
}

std::list<Icing*>* Game::getOpponentIcing() {
	return &opponentIcing;
}

CIwFVec2 Game::getWorldRadius() {
	return CIwFVec2(innerRadius, outerRadius);
}

CIwMat* Game::getViewMatrix(){
    return &view;
}

float Game::getRotation(){
    return rotation;
}

float Game::rotate(float rot) {
    return rotation += rot;
}

CIwResGroup* Game::getSprites(){
    return sprites;
}

Player *Game::getLocalPlayer(){
    return localPlayer;
}

Player *Game::getOpponentPlayer(){
    return opponentPlayer;
}
