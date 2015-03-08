#pragma once
#include <cocos2d.h>

class ScoreSprite :public cocos2d::Sprite {
public:
	virtual bool init();
	CREATE_FUNC(ScoreSprite);
	int getScore();
	void changeScore();
private:
	cocos2d::Sprite *scoreSprite;
	cocos2d::Label *scoreLabel;
	int score = 0;
};