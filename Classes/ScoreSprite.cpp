#include "ScoreSprite.h"
#include <sstream>
USING_NS_CC;

bool ScoreSprite::init() {
	if (!Sprite::init()) {
		return false;
	}
	Size visible = Director::getInstance()->getVisibleSize();
	TTFConfig config("fonts/girl.ttc", 50.f);
	std::stringstream scoreString;
	scoreString << "score:" << score;
	scoreLabel = Label::createWithTTF(config, scoreString.str(), TextHAlignment::CENTER);
	scoreLabel->setPosition(Point(visible.width - 100, visible.height - 50));
	addChild(scoreLabel);
	return true;
}

int ScoreSprite::getScore() {
	return score;
}

void ScoreSprite::changeScore() {

	std::stringstream scoreString;
	scoreString << "score:" << ++score;
	scoreLabel->setString(scoreString.str());
}