
#include <cocos2d.h>
#include "ScoreSprite.h"
class NumberSprite :public cocos2d::Sprite {
public:
	virtual bool init();
	CREATE_FUNC(NumberSprite);
	bool getConfirm();
	void setMathExpression(ScoreSprite *score);
private:
	cocos2d::Sprite *number_one;
	cocos2d::Sprite *number_two;
	cocos2d::Label *mathExpression;
	int max;
	bool confirm;


};
