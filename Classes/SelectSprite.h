#include <cocos2d.h>

class SelectSprite :public cocos2d::Sprite {
public:
	virtual bool init();
	CREATE_FUNC(SelectSprite);
	cocos2d::Sprite *getYesSprite();
	cocos2d::Sprite *getNoSprite();
private:
	cocos2d::Sprite *yes;
	cocos2d::Sprite *no;
};