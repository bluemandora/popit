#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size size = Director::getInstance()->getVisibleSize();
	
	//对手机返回键的监听
	auto listener = EventListenerKeyboard::create();
	//和回调函数绑定
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	//添加到事件分发器中
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto lis = EventListenerTouchOneByOne::create();
	lis->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	lis->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, this);

	auto bgColor = LayerColor::create(Color4B(180, 170, 160, 255));
	addChild(bgColor);

	/*auto title_color = LayerColor::create(Color4B(0, 0, 0, 255), size.width, size.height/10);
	title_color->setPositionY(size.height*9/10);
	addChild(title_color);*/

	Label* text_label = Label::create("Score: ", "Arial", 80);
	text_label->setPosition(size.width / 3, size.height * 3 / 4);
	addChild(text_label);

	Label* text_label2 = Label::create("High Score: ", "Arial", 80);
	text_label2->setPosition(size.width / 3, size.height * 3 / 4 + 100);
	addChild(text_label2);

	score_label = Label::create("0", "Arial", 80);
	score_label->setPosition(size.width * 2 / 3, size.height * 3 / 4);
	addChild(score_label);
	score = 0;

	high_score = CCUserDefault::sharedUserDefault()->getIntegerForKey("high");
	high_score_label = Label::create(__String::createWithFormat("%i", high_score)->getCString(), "Arial", 80);
	high_score_label->setPosition(size.width * 2 / 3, size.height * 3 / 4 + 100);
	addChild(high_score_label);

	line_number = CCUserDefault::sharedUserDefault()->getIntegerForKey("line");
	if (line_number == 0)
		line_number = 4;
	
	select_card = NULL;
	HelloWorld::createAllCardSprite(size);
	HelloWorld::autoCreateCard();
	HelloWorld::autoCreateCard();

	initMenu();
    return true;
}

void HelloWorld::update()
{
	Size size = Director::getInstance()->getVisibleSize();

	score_label->setString("0");
	score = 0;

	high_score = CCUserDefault::sharedUserDefault()->getIntegerForKey("high");
	high_score_label->setString(__String::createWithFormat("%i", high_score)->getCString());

	line_number = CCUserDefault::sharedUserDefault()->getIntegerForKey("line");
	if (line_number == 0)
		line_number = 4;

	select_card = NULL;
	HelloWorld::createAllCardSprite(size);
	HelloWorld::autoCreateCard();
	HelloWorld::autoCreateCard();
}

bool HelloWorld::initMenu() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto update_item = MenuItemImage::create("update.png", "update.png", CC_CALLBACK_1(HelloWorld::menuUpdateCallback, this));
	update_item->setPosition(origin + Vec2(visibleSize) - Vec2(update_item->getContentSize() / 2));

	line_label = Label::create(__String::createWithFormat("%i", line_number)->getCString(), "Arial", 30);
	line_label->setPosition(origin + Vec2(visibleSize) - Vec2(update_item->getContentSize() / 2) - Vec2(100, 0));
	addChild(line_label);
	auto slider = Slider::create();
	slider->loadBarTexture("sliderTrack.png");
	slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	slider->loadProgressBarTexture("sliderProgress.png");
	slider->setPosition(origin + Vec2(visibleSize) - Vec2(update_item->getContentSize() / 2) - Vec2(500, 0));
	slider->addEventListener(CC_CALLBACK_2(HelloWorld::sliderEvent, this));
	slider->setPercent((line_number - 4) * 100 / 6);
	this->addChild(slider);

	auto menu = Menu::create(update_item, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

void HelloWorld::sliderEvent(Ref *pSender, Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* pSlider = (Slider*)pSender;
		int line_number = 4 + pSlider->getPercent() * 6 / 100;
		pSlider->setPercent((line_number - 4) * 100 / 6);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("line", line_number);
		line_label->setString(__String::createWithFormat("%i", line_number)->getCString());
		update();
	}
}

void HelloWorld::menuUpdateCallback(Ref* sender) {
	Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
}

void HelloWorld::createAllCardSprite(Size size) {
	int len = (size.width - 28) / line_number;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (card[i][j] != NULL) {
				removeChild(card[i][j]);
				card[i][j] = NULL;
			}

	for (int i = 0; i < line_number; i++) {
		for (int j = 0; j < line_number; j++) {
			card[i][j] = CardSprite::createCardSprite(0, len, len, (double)len*i+20, (double)len*j + size.height/8);
			card[i][j]->setX(i);
			card[i][j]->setY(j);
			addChild(card[i][j]);
		}
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE ||
			keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
	}
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event) {
	begin = touch->getLocation();
	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event) {
	end = touch->getLocation();
	if (abs(begin.x - end.x) < 5 && abs(begin.y - end.y) < 5) {
		//click
		Point point = touch->getLocation();
		Size size = Director::getInstance()->getVisibleSize();
		CardSprite* click_card = getCardSprite(size, point);
		if (click_card) {
			if (select_card == click_card) {
				click_card->clearSelect();
				select_card = NULL;
			}
			else if (select_card) {
				select_card->clearSelect();
				int tmp = select_card->getNum();
				select_card->setNum(click_card->getNum());
				click_card->setNum(tmp);
				select_card = NULL;
			}
			else {
				click_card->setSelect();
				select_card = click_card;
			}
			
		}
	}
	else {
		if (select_card) {
			select_card->clearSelect();
		}
		select_card = NULL;
		if (abs(begin.x - end.x) > abs(begin.y - end.y)) {

			//left or right
			if (end.x > begin.x + 5) {
				// right
				if (doRight()) {
					autoCreateCard();
					checkGameOver();
				}
			}
			else if (end.x < begin.x - 5) {
				//left
				if (doLeft()) {
					autoCreateCard();
					checkGameOver();
				}
			}
		}
		else {
			if (end.y > begin.y + 5) {
				//up
				if (doUp()) {
					autoCreateCard();
					checkGameOver();
				}
			}
			else if (end.y < begin.y - 5) {
				//down
				if (doDown()) {
					autoCreateCard();
					checkGameOver();
				}
			}
		}
	}
}

CardSprite* HelloWorld::getCardSprite(Size size, Point point) {
	int len = (size.width - 28) / line_number;
	int x = (point.x - 20) / len;
	int y = (point.y - size.height / 8) / len;
	if (x >= 0 && x < line_number && y >= 0 && y < line_number) {
		return card[x][y];
	}
	else {
		return NULL;
	}
}

void HelloWorld::addScore(int num) {
	score += num;
	score_label->setString(__String::createWithFormat("%i", score)->getCString());
	if (score > high_score) {
		high_score = score;
		CCUserDefault::sharedUserDefault()->setIntegerForKey("high", high_score);
		high_score_label->setString(__String::createWithFormat("%i", high_score)->getCString());
	}
}

bool HelloWorld::doUp() {
	bool ret = false;
	for (int i = 0; i < line_number; i++) {
		for (int j = line_number - 1; j >= 0; j--) {
			for (int y = j - 1; y >= 0; y--) {
				if (card[i][y]->getNum() == 0) continue;
				if (card[i][j]->getNum() == 0) {
					card[i][j]->setNum(card[i][y]->getNum());
					card[i][y]->setNum(0);
					j++;
					ret = true;
				}
				else if (card[i][j]->getNum() == card[i][y]->getNum()){
					card[i][j]->setNum(card[i][y]->getNum() * 2);
					addScore(card[i][j]->getNum());
					card[i][y]->setNum(0);
					ret = true;
				}
				break;
			}
		}
	}
	return ret;
}

bool HelloWorld::doDown() {
	bool ret = false;
	for (int i = 0; i < line_number; i++) {
		for (int j = 0; j < line_number; j++) {
			for (int y = j + 1; y < line_number; y++) {
				if (card[i][y]->getNum() == 0) continue;
				if (card[i][j]->getNum() == 0) {
					card[i][j]->setNum(card[i][y]->getNum());
					card[i][y]->setNum(0);
					j--;
					ret = true;
				}
				else if (card[i][j]->getNum() == card[i][y]->getNum()){
					card[i][j]->setNum(card[i][y]->getNum() * 2);
					addScore(card[i][j]->getNum());
					card[i][y]->setNum(0);
					ret = true;
				}
				break;
			}
		}
	}
	return ret;
}

bool HelloWorld::doLeft() {
	bool ret = false;
	for (int j = 0; j < line_number; j++) {
		for (int i = 0; i < line_number; i++) {
			for (int x = i + 1; x < line_number; x++) {
				if (card[x][j]->getNum() == 0) continue;
				if (card[i][j]->getNum() == 0) {
					card[i][j]->setNum(card[x][j]->getNum());
					card[x][j]->setNum(0);
					i--;
					ret = true;
				}
				else if (card[i][j]->getNum() == card[x][j]->getNum()){
					card[i][j]->setNum(card[x][j]->getNum() * 2);
					addScore(card[i][j]->getNum());
					card[x][j]->setNum(0);
					ret = true;
				}
				break;
			}
		}
	}
	return ret;
}

bool HelloWorld::doRight() {
	bool ret = false;
	for (int j = 0; j < line_number; j++) {
		for (int i = line_number - 1; i >= 0; i--) {
			for (int x = i - 1; x >= 0; x--) {
				if (card[x][j]->getNum() == 0) continue;
				if (card[i][j]->getNum() == 0) {
					card[i][j]->setNum(card[x][j]->getNum());
					card[x][j]->setNum(0);
					i++;
					ret = true;
				}
				else if (card[i][j]->getNum() == card[x][j]->getNum()){
					card[i][j]->setNum(card[x][j]->getNum() * 2);
					addScore(card[i][j]->getNum());
					card[x][j]->setNum(0);
					ret = true;
				}
				break;
			}
		}
	}
	return ret;
}

void HelloWorld::autoCreateCard() {
	int i = CCRANDOM_0_1() * line_number;
	int j = CCRANDOM_0_1() * line_number;
	while (card[i][j]->getNum() > 0) {
		i = CCRANDOM_0_1() * line_number;
		j = CCRANDOM_0_1() * line_number;
	}
	card[i][j]->setNum(CCRANDOM_0_1() * 10 < 2 ? 4 : 2);
	if (card[i][j] -> getNum() > 0)
	card[i][j]->getBgColor()->runAction(Sequence::create(ScaleTo::create(0, 0, 0), ScaleTo::create(0.3f, 1, 1), NULL));
}

void HelloWorld::checkGameOver() {
	for (int i = 0; i < line_number; i++) {
		for (int j = 0; j < line_number; j++) {
			if (card[i][j]->getNum() == 0 ||
				(i > 0 && card[i][j]->getNum() == card[i - 1][j]->getNum()) ||
				(j > 0 && card[i][j]->getNum() == card[i][j - 1]->getNum()))
				return;
		}
	}
	Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
}
