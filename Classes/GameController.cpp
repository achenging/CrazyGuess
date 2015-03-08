#include "GameController.h"
#include "StartScene.h"
USING_NS_CC;
bool GameController::init() {

	if (!Layer::init()) {
		return false;
	}
	score = ScoreSprite::create();
	score->setTag(10);
	//背景层
	backGround = BackGroundLayer::create();
	//数学表达式层
	number = NumberSprite::create();
	number->setMathExpression(score);
	number->setTag(5);
	//number->setPosition(ccp(0, Director::getInstance()->getVisibleSize().height));
	//选择层
	select = SelectSprite::create();
	select->setTag(7);


	//进度条
	auto progress = ProgressBarSprite::create();
	progress->setTag(9);

	this->addChild(backGround);
	this->addChild(number);
	this->addChild(select);
	this->addChild(score);
	this->addChild(progress);
	valid();
	this->scheduleUpdate();
	return true;
}
void GameController::valid() {
	auto listener = EventListenerTouchOneByOne::create();
	auto sele = (SelectSprite *) this->getChildByTag(7);
	listener->onTouchBegan = [sele, this](Touch *touch, Event *event) {

		auto maxScore = (ScoreSprite *)this->getChildByTag(10);
		auto numberSprite = (NumberSprite *) this->getChildByTag(5);

		//得到答案
		bool confirm = numberSprite->getConfirm();
		//判断点击的精灵
		if ((sele->getYesSprite()->getBoundingBox().containsPoint(touch->getLocation()) && confirm) || (sele->getNoSprite()->getBoundingBox().containsPoint(touch->getLocation()) && !confirm)) {
			this->removeChildByTag(5);
			this->removeChildByTag(9);
			auto number = NumberSprite::create();
			maxScore->changeScore();
			number->setTag(5);
			number->setMathExpression(score);
			auto progress = ProgressBarSprite::create();
			progress->setTag(9);
			this->addChild(number);
			this->addChild(progress);
			return false;
		} else {
			int sc = score->getScore();
			auto gameOver = GameOverScene::createScene(sc);
			this->unscheduleUpdate();
			Director::getInstance()->replaceScene(gameOver);
			return false;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sele);

	this->setKeyboardEnabled(true);
	this->setKeypadEnabled(true);
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case  EventKeyboard::KeyCode::KEY_BACKSPACE:
			Director::getInstance()->replaceScene(StartScene::createScene(0));
			break;
		case  EventKeyboard::KeyCode::KEY_ESCAPE:
			Director::getInstance()->replaceScene(StartScene::createScene(0));
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

}

void GameController::update(float delta) {
	auto progress = (ProgressBarSprite *)this->getChildByTag(9);
	auto timer = progress->getTimer();
	if (timer->getPercentage() == 100.f) {
		int sc = score->getScore();

		auto gameOver = GameOverScene::createScene(sc);
		this->unscheduleUpdate();
		Director::getInstance()->replaceScene(gameOver);
	}
}