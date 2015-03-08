#include "SelectSprite.h"

USING_NS_CC;

bool SelectSprite::init() {
	if (!Sprite::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	yes = Sprite::create("right.png");
	no = Sprite::create("wrong.png");
	yes->setPosition(ccp(visibleSize.width / 2 + 100, visibleSize.height / 3 - 80));
	no->setPosition(ccp(visibleSize.width / 2 - 100, visibleSize.height / 3 - 80));
	this->addChild(yes);
	this->addChild(no);
	return true;
}
Sprite *SelectSprite::getYesSprite() {
	return yes;
}
Sprite *SelectSprite::getNoSprite() {
	return no;
}
