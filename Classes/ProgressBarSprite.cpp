#include "ProgressBarSprite.h"
USING_NS_CC;

bool ProgressBarSprite::init() {
	if (!Sprite::init()) {
		return false;
	}
	auto rectProgress = Sprite::create("progress.png");
	auto progressTo = ProgressTo::create(2, 100);
	Size size = Director::getInstance()->getVisibleSize();
	timer = ProgressTimer::create(rectProgress);
	timer->getPercentage();
	timer->setType(kCCProgressTimerTypeBar);			//设置进度条的类型为条形的进度条。
	timer->setMidpoint(ccp(0, 0));
	timer->setBarChangeRate(ccp(1, 0));
	timer->setPosition(ccp(size.width / 2, size.height));
	timer->runAction(progressTo);
	addChild(timer);

	return true;
}
ProgressTimer *ProgressBarSprite::getTimer() {
	return timer;
}
