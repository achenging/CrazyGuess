#pragma once
#include <cocos2d.h>
#include "GameOverScene.h"
class GameOverScene :public cocos2d::LayerColor {

public:
	virtual bool init();

	CREATE_FUNC(GameOverScene);
	static cocos2d::Scene* createScene(int score) {
		auto s = cocos2d::Scene::create();
		auto l = GameOverScene::create();
		l->setScore(score);
		l->saveMaxScore(score);
		s->addChild(l);
		return s;
	};


private:
	cocos2d::TTFConfig config = cocos2d::TTFConfig("fonts/girl.ttc", 80.f);
	cocos2d::Size visibleSize;
	cocos2d::Label *maxScore;
	int score;
	void setScore(int s);
	void saveMaxScore(int s);
};

