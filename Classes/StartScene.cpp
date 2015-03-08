#include "StartScene.h"
#include "GameController.h"
#include "MaxScoreScene.h"
USING_NS_CC;

bool StartScene::init() {
	if (!LayerColor::init()) {
		return false;
	}
	LayerColor::initWithColor(cocos2d::Color4B::WHITE);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	/************************************************************************/
	/* 开始游戏按钮                                                         */
	/************************************************************************/
	auto startLabel = Label::create();
	startLabel->setString(Configuration::getInstance()->getValue("start", Value("Start Game")).asString());
	startLabel->setTTFConfig(config);
	startLabel->setColor(Color3B::ORANGE);
	startLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 60);
	startLabel->runAction(CCRepeatForever::create(EaseElasticInOut::create(CCSequence::create(CCScaleTo::create(2.f, 1.2f), CCScaleTo::create(1.8f, 1.f), NULL))));
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [startLabel](Touch *touch, Event *event) {
		if (startLabel->getBoundingBox().containsPoint(touch->getLocation())) {
			Director::getInstance()->replaceScene(GameController::createScene());
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, startLabel);
	;
	addChild(startLabel);
	/************************************************************************/
	/* 最高分                                                               */
	/************************************************************************/
	auto maxScoreLabel = Label::create();
	maxScoreLabel->setString(Configuration::getInstance()->getValue("rank", Value("Max Score")).asString());
	maxScoreLabel->setTTFConfig(config);
	maxScoreLabel->setColor(Color3B::RED);
	maxScoreLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 60);
	maxScoreLabel->runAction(CCRepeatForever::create(EaseElasticInOut::create(CCSequence::create(CCScaleTo::create(2.f, 1.2f), CCScaleTo::create(2.f, 1.f), NULL))));
	addChild(maxScoreLabel);
	auto maxListener = EventListenerTouchOneByOne::create();
	maxListener->onTouchBegan = [maxScoreLabel](Touch *touch, Event *event) {
		if (maxScoreLabel->getBoundingBox().containsPoint(touch->getLocation())) {
			Director::getInstance()->replaceScene(MaxScoreScene::createScene());
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(maxListener, maxScoreLabel);
	;


	/************************************************************************/
	/* 键盘返回按键的监听                                                   */
	/************************************************************************/

	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case  EventKeyboard::KeyCode::KEY_BACKSPACE:
			Director::getInstance()->end();
			break;
		case  EventKeyboard::KeyCode::KEY_ESCAPE:
			Director::getInstance()->end();
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	return true;
}
