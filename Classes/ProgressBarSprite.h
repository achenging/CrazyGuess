#pragma once
#include <cocos2d.h>
class ProgressBarSprite :public cocos2d::Sprite {
public:
	virtual bool init();
	CREATE_FUNC(ProgressBarSprite);
	cocos2d::ProgressTimer *getTimer();
private:
	cocos2d::ProgressTimer *timer;
};

