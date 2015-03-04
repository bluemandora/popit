#include "cocos2d.h"
USING_NS_CC;
class CardSprite:public Sprite {
public:
	static CardSprite* createCardSprite(int num, int width, int height, double card_x, double card_y);
	virtual bool init();
	CREATE_FUNC(CardSprite);

	void setNum(int num);
	void setNewNum(int num);
	LayerColor* getBgColor();
	int getNum();
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
	void setSizeAndColor(int num);
	void setSelect();
	void clearSelect();
private:
	int number, X, Y;
	//Êý×Ö
	Label* cardNumber;
	void cardInit(int num, int width, int height, double card_x, double card_y);
	//±³¾°
	LayerColor* cardBgcolor;
};
