#pragma once
#include <cocos2d.h>
#include "BackGroundLayer.h"
#include "NumberSprite.h"
#include "SelectSprite.h"
#include "ScoreSprite.h"
#include "ProgressBarSprite.h"
#include "GameOverScene.h"
class GameController:public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameController);
	void valid();
	virtual void update(float delta);

	static cocos2d::Scene* createScene() {
		auto s = cocos2d::Scene::create();
		auto l = GameController::create();
		s->addChild(l);
		return s;
	};
private:
	BackGroundLayer *backGround;
	NumberSprite *number;
	SelectSprite *select;
	ScoreSprite *score;
	//ProgressBarSprite *progress;
};


