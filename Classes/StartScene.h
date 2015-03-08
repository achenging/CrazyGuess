#pragma once
#include <cocos2d.h>
class StartScene :public cocos2d::LayerColor {
public:
	virtual bool init();
	CREATE_FUNC(StartScene);
	static cocos2d::Scene* createScene(int score) {
		auto s = cocos2d::Scene::create();
		auto l = StartScene::create();
		s->addChild(l);
		return s;
	};


private:
	cocos2d::TTFConfig config = cocos2d::TTFConfig("fonts/girl.ttc", 80.f);
};

