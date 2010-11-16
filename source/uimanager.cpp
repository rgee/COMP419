#include "uimanager.h"

UIManager::UIManager() {
	pointerOffset = 0;
}

int UIManager::getWorldOffset() {
	return pointerOffset;
}

void UIManager::updateOffset() {
	pointerOffset = s3ePointerGetY();
}


int getWidth(){
    return IwGxGetScreenHeight();
}

int getHeight(){
    return IwGxGetScreenHeight();
}