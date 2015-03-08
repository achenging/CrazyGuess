#include "GameOverScene.h"
#include "StartScene.h"
#include "GameController.h"
#include "MaxScoreScene.h"
#include "GameMain.h"
#include <fstream>
#include <vector>
#include <algorithm>
USING_NS_CC;
bool GameOverScene::init() {
	LayerColor::initWithColor(Color4B::WHITE);

	visibleSize = Director::getInstance()->getVisibleSize();
	/************************************************************************/
	/*           Back Game                                                  */
	/************************************************************************/

	auto backGameLabel = Label::create(Configuration::getInstance()->getValue("back_str", Value("Back")).asString(), "Arial", 80);
	backGameLabel->setAnchorPoint(Point(0, 1));
	backGameLabel->setTextColor(Color4B::RED);
	backGameLabel->setPosition(Point(0, visibleSize.height));
	auto backGameLabelListener = EventListenerTouchOneByOne::create();
	backGameLabelListener->onTouchBegan = [backGameLabel](Touch *touch, Event *event) {
		if (backGameLabel->getBoundingBox().containsPoint(touch->getLocation())) {
			Director::getInstance()->replaceScene(GameMain::createScene());
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(backGameLabelListener, backGameLabel);



	/************************************************************************/
	/*           GAME OVER                                                  */
	/************************************************************************/
	auto label = Label::create();
	label->setString("Game Over");
	config.fontSize = 80.0f;
	label->setTTFConfig(config);
	label->setColor(Color3B::ORANGE);
	label->setAnchorPoint(Point(0.5, 1));
	label->setPosition(visibleSize.width / 2, visibleSize.height - 70);




	/************************************************************************/
	/*                      Max Score                                       */
	/************************************************************************/
	maxScore = Label::create();
	config.fontSize = 60;
	maxScore->setTTFConfig(config);
	maxScore->setColor(Color3B::RED);
	maxScore->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//maxScore->runAction(CCRepeatForever::create(EaseElasticInOut::create(CCSequence::create(CCScaleTo::create(2.f, 1.5f), CCScaleTo::create(2.f, 1.f), NULL))));




	/************************************************************************/
	/*                            play again                                */
	/************************************************************************/
	auto againLabel = Label::create();
	againLabel->setString(Configuration::getInstance()->getValue("play_again", Value("再来一次")).asString());
	config.fontSize = 50;
	againLabel->setTTFConfig(config);
	againLabel->setColor(Color3B::MAGENTA);
	againLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100);
	auto againLabelListener = EventListenerTouchOneByOne::create();
	againLabelListener->onTouchBegan = [againLabel](Touch *touch, Event *event) {
		if (againLabel->getBoundingBox().containsPoint(touch->getLocation())) {
			Director::getInstance()->replaceScene(GameController::createScene());
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(againLabelListener, againLabel);



	/************************************************************************/
	/*                            return start scene                        */
	/************************************************************************/

	auto lookRankLabel = Label::create();
	lookRankLabel->setString(Configuration::getInstance()->getValue("look_rank", Value("查看排行榜")).asString());
	config.fontSize = 50;
	lookRankLabel->setTTFConfig(config);
	lookRankLabel->setColor(Color3B::MAGENTA);
	lookRankLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
	auto scoreLabelListener = EventListenerTouchOneByOne::create();
	scoreLabelListener->onTouchBegan = [lookRankLabel](Touch *touch, Event *event) {
		if (lookRankLabel->getBoundingBox().containsPoint(touch->getLocation())) {
			Director::getInstance()->replaceScene(MaxScoreScene::createScene());
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(scoreLabelListener, againLabel);


	/************************************************************************/
	/*                            add sprite to scene                       */
	/************************************************************************/

	addChild(backGameLabel);
	addChild(label);
	addChild(maxScore);
	addChild(againLabel);
	addChild(lookRankLabel);



	/************************************************************************/
	/*                        BackSpace  Key Listener                       */
	/************************************************************************/
	this->setKeyboardEnabled(true);
	this->setKeypadEnabled(true);
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case  EventKeyboard::KeyCode::KEY_BACKSPACE:
			Director::getInstance()->replaceScene(StartScene::createScene(0));
			break;
		case EventKeyboard::KeyCode::KEY_BACK:
			Director::getInstance()->replaceScene(StartScene::createScene(0));
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
	return true;
}


void GameOverScene::setScore(int s) {
	score = s;
	std::stringstream sstream;
	sstream << "Score: " << score;
	maxScore->setString(sstream.str());
}

void GameOverScene::saveMaxScore(int s) {
	std::vector<int> vec;
	auto futil = FileUtils::getInstance();
	auto filePath = futil->fullPathFromRelativeFile("rank.dat", futil->getWritablePath());
	log(">>>>>>>>>>>>>>>>>>>%s", filePath.c_str());

	std::ifstream input;
	input.open(filePath, std::ifstream::binary);
	if (input) {
		log("input");
		int tmp;
		int index = 0;
		while (input >> tmp) { vec.push_back(tmp); }
		input.close();
	} else {
		int index = 0;
		while (index++ < 6) { vec.push_back(0); }
	}
	vec.push_back(s);
	std::sort(vec.begin(), vec.end(), std::greater<int>());
	vec.pop_back();
	if (std::find(vec.begin(), vec.end(), s) != vec.end()) {
		std::ofstream out;
		out.open(filePath, std::ofstream::binary);
		int tmp = 0;
		while (tmp < 5) {
			out << *(vec.begin() + tmp) << " ";
			++tmp;
		}
		out.close();
	}
}
