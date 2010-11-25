#include "muncher.h"

Muncher::Muncher(Player* owner, Game* game, CIwFVec2 position)
		 : Unit(100.0f, 50.0f, 10.0f, 25.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game, position), UnitType("Muncher")
{
	spriteSize = 256;
	numFrames = 12;
	curFrame = 0;
    scale = 0.2f;
	circleOffset = 0.0;
    statAttacks = {{"Muncher",0},{"Wrecker",10},{"Thrower",0},{"Shooter",0},{"Invader",0},{"Spreader",0},{"Leader",0}};
}

bool Muncher::update() {
    curFrame = (curFrame + 1) % numFrames;
   
    if(curFrame == 0)
        game->getAI()->updateAI(this);
    
	return true;
}
void Muncher::Attack(){
    int attackDmg = this->GetDammage();
    cking.RecieveDammage(attackDmg, this);
}

virtual int GetDammage(){
    string enemyType = attacking->getType();
    int attackDmg;
    for(CIwArray<CIwArray>::iterator itr = statAttacks->begin(); itr != statAttacks->end(); itr++){
        if(itr[0]==enemyType){
            attackDmg = itr[1];
        }
    }
    return attackDmg;
}

void Muncher::RecieveDammage(int dammage, Unit* attacker){
    if(hp<dammage){
        //call the death animation function
        attacker.setAttacking(NULL);
        delete this;
    }
    else{
        hp = hp - damage
    }
}


const char* Muncher::getTextureName() {
	return "muncher_sprite_sheet";
}