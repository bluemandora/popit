#include "CardSprite.h"

CardSprite* CardSprite::createCardSprite(int num, int width, int height, double card_x, double card_y) {
	CardSprite* card = new CardSprite();
	if (card && card->init()) {
		card->autorelease();
		card->cardInit(num, width, height, card_x, card_y);
		return card;
	}
	CC_SAFE_DELETE(card);
	return NULL;
}

bool CardSprite::init() {
	if (!Sprite::init()) {
		return false;
	}
	return true;
}

void CardSprite::setSizeAndColor(int num) {
	//设置字体大小
	if (num >= 16384) {
		cardNumber->setSystemFontSize(60);
	}
	else if (num >= 1024) {
		cardNumber->setSystemFontSize(70);
	}
	else if (num >= 128) {
		cardNumber->setSystemFontSize(80);
	}
	else if (num >= 16) {
		cardNumber->setSystemFontSize(90);
	}
	else if (num >= 0) {
		cardNumber->setSystemFontSize(100);
	}


	//设置卡片颜色
	if (num == 0) {
		cardBgcolor->setColor(Color3B(200, 190, 180));
	}
	else if (num == 2) {
		cardBgcolor->setColor(Color3B(238, 230, 193));
	}
	else if (num == 4) {
		cardBgcolor->setColor(Color3B(255, 236, 139));
	}
	else if (num == 8) {
		cardBgcolor->setColor(Color3B(240, 180, 120));
	}
	else if (num == 16) {
		cardBgcolor->setColor(Color3B(240, 140, 90));
	}
	else if (num == 32) {
		cardBgcolor->setColor(Color3B(240, 120, 90));
	}
	else if (num == 64) {
		cardBgcolor->setColor(Color3B(240, 90, 60));
	}
	else if (num == 128) {
		cardBgcolor->setColor(Color3B(220, 90, 60));
	}
	else if (num == 256) {
		cardBgcolor->setColor(Color3B(240, 200, 70));
	}
	else if (num == 512) {
		cardBgcolor->setColor(Color3B(220, 200, 70));
	}
	else if (num == 1024) {
		cardBgcolor->setColor(Color3B(255, 236, 139));
	}
	else if (num == 2048) {
		cardBgcolor->setColor(Color3B(255, 236, 139));
	}
	else {
		cardBgcolor->setColor(Color3B(144, 144, 144));
	}
}

void CardSprite::setSelect() {
	//cardBgcolor->setColor(Color3B(240, 90, 60));
	GLenum src;
	GLenum dst;
	//设置混合方式  
	if (cardBgcolor->getBlendFunc().dst == GL_ZERO)
	{
		src = GL_SRC_ALPHA;
		dst = GL_ONE_MINUS_SRC_ALPHA;
	}
	else
	{
		src = GL_ONE_MINUS_DST_COLOR;
		dst = GL_ZERO;
	}
	BlendFunc bf = { src, dst };
	cardBgcolor->setBlendFunc(bf);
}

void CardSprite::clearSelect() {
	//cardBgcolor->setColor(Color3B(200, 190, 180));
	GLenum src;
	GLenum dst;
	//设置混合方式  
	if (cardBgcolor->getBlendFunc().dst == GL_ZERO)
	{
		src = GL_SRC_ALPHA;
		dst = GL_ONE_MINUS_SRC_ALPHA;
	}
	else
	{
		src = GL_ONE_MINUS_DST_COLOR;
		dst = GL_ZERO;
	}
	BlendFunc bf = { src, dst };
	cardBgcolor->setBlendFunc(bf);
}

void CardSprite::setX(int x) {
	X = x;
}
int CardSprite::getX(){
	return X;
}
void CardSprite::setY(int y) {
	Y = y;
}
int CardSprite::getY(){
	return Y;
}


void CardSprite::setNum(int num) {
	number = num;
	
	// 更新显示
	if (number != 0) {
		cardNumber->setString(__String::createWithFormat("%i", number)->getCString());
		cardBgcolor->setColor(Color3B(238, 230, 193));
	}
	else {
		cardNumber->setString("");
		cardBgcolor->setColor(Color3B(200, 190, 180));
	}
	CardSprite::setSizeAndColor(num);
}

int CardSprite::getNum() {
	return number;
}

void CardSprite::cardInit(int num, int width, int height, double card_x, double card_y) {
	number = num;
	cardBgcolor = LayerColor::create(Color4B(200, 190, 180, 255), width - 15, height - 15);
	
	cardBgcolor->setPosition(card_x, card_y);
	if (number != 0) {
		cardNumber = Label::create(__String::createWithFormat("%i", number)->getCString(), "Arial", 100);
		cardNumber->setPosition(cardBgcolor->getContentSize().width / 2, cardBgcolor->getContentSize().height / 2);
		cardBgcolor->addChild(cardNumber);
	}
	else {
		cardNumber = Label::create("", "Arial", 100);
		cardNumber->setPosition(cardBgcolor->getContentSize().width / 2, cardBgcolor->getContentSize().height / 2);
		cardBgcolor->addChild(cardNumber);
	}
	setSizeAndColor(num);
	addChild(cardBgcolor);
}
