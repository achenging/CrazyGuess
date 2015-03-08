#include "GameMain.h"
#include "StartScene.h"
USING_NS_CC;

Scene* GameMain::createScene() {
	auto scene = Scene::create();

	auto layer = GameMain::create();

	scene->addChild(layer);

	return scene;
}
bool GameMain::init() {

	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto start = StartScene::create();
	addChild(start);
	return true;
}
