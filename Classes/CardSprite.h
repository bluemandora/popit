#include "cocos2d.h"
USING_NS_CC;
class CardSprite:public Sprite {
public:
	static CardSprite* createCardSprite(int num, int width, int height, double card_x, double card_y);
	virtual bool init();
	CREATE_FUNC(CardSprite);

	void setNum(int num);
	int getNum();
	void setSizeAndColor(int num);
private:
	int number;
	//Êý×Ö
	Label* cardNumber;
	void cardInit(int num, int width, int height, double card_x, double card_y);
	//±³¾°
	LayerColor* cardBgcolor;
};
