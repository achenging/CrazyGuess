#include "NumberSprite.h"
#include <cstdlib>
#include <sstream>
#include <ctime>
USING_NS_CC;


bool NumberSprite::init() {
	if (!Sprite::init()) {
		return false;
	}
	//字体配置
	TTFConfig config("fonts/girl.ttc", 100.f);
	mathExpression = Label::createWithTTF(config, "", TextHAlignment::CENTER);
	mathExpression->setTextColor(Color4B::ORANGE);
	mathExpression->setAnchorPoint(Point::ANCHOR_MIDDLE);
	Size size = Director::getInstance()->getVisibleSize();
	mathExpression->setPosition(size.width / 2, size.height / 2);
	this->setPosition(size.width, 0);
	auto action = MoveTo::create(0.1, ccp(0, 0));
	this->runAction(action);
	addChild(mathExpression);

	return true;
}




bool NumberSprite::getConfirm() {
	return confirm;
}

void NumberSprite::setMathExpression(ScoreSprite *score) {
	//得到分数，并逐渐提高难度

	int maxScore = score->getScore();
	if (maxScore <= 10) {
		max = 10;
	} else if (maxScore <= 20) {
		max = 20;
	} else if (maxScore <= 30) {
		max = 30;
	} else if (maxScore <= 40) {
		max = 40;
	} else if (maxScore <= 50) {
		max = 50;
	}

	//生成随机数
	srand((unsigned)time(0));
	int num1 = rand() % max + 1;
	int num2 = rand() % max + 1;
	int num3 = rand() % max + 1;
	int answer = num1*num2;
	int flag = rand() % 10;			//设置答案正确与错误的比例


	int num[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::stringstream sstream;
	if (flag > 4 && flag < 7) {
		log("flag > 4 && flag <7");
		sstream << num1 << " X " << num2 << " = " << answer + num[flag] << " ? ";
		confirm = false;
	} else if (flag >= 7) {
		log("flag >= 7");
		confirm = false;
		sstream << num1 << " X " << num2 << " = " << ((answer - num[flag]) > 0 ? (answer - num[flag]) : answer + num[flag]) << " ? ";
	} else {
		log("else");
		confirm = true;
		sstream << num1 << " X " << num2 << " = " << answer << " ? ";
	}

	mathExpression->setString(sstream.str());

	mathExpression->setTextColor(Color4B::ORANGE);
}
