#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
	cocos2d::Point begin, end;
	CardSprite* card[4][4];
	CardSprite* select_card;
	int score, high_score;
	cocos2d::Label* score_label, * high_score_label;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	bool doUp();
	bool doDown();
	bool doLeft();
	bool doRight();
	CardSprite* getCardSprite(Size size, Point point);
	void createAllCardSprite(Size size);
	void autoCreateCard();
	void checkGameOver();
	void addScore(int num);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
