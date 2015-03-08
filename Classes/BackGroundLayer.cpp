#include "BackGroundLayer.h"
#include "NumberSprite.h"
USING_NS_CC;

bool BackGroundLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto backGroundColor = LayerColor::create(Color4B::WHITE);

	addChild(backGroundColor);

	return true;
}