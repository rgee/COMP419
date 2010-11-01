#include "uimanager.h"

UIManager::UIManager() {
	pointerOffset = 0;
}

int UIManager::getWorldOffset() {
	return Iw2DGetSurfaceHeight() - pointerOffset;
}

void UIManager::updateOffset() {
	pointerOffset = s3ePointerGetY();
}