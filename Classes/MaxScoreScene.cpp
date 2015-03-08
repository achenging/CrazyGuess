

#include "MaxScoreScene.h"
#include "GameMain.h"
#include <fstream>
#include <string>
USING_NS_CC;
USING_NS_CC_EXT;
bool MaxScoreScene::init() {
	if (!LayerColor::init()) {
		return false;
	}

	for (size_t i = 0; i < 5; i++) { scoreRank[i] = 0; }

	auto futil = FileUtils::getInstance();
	auto filePath = futil->fullPathFromRelativeFile("rank.dat", futil->getWritablePath());

	std::ifstream input;
	input.open(filePath, std::ifstream::binary);
	if (!input) {
		std::ofstream out;
		out.open(filePath, std::ofstream::binary);
		int tmp = 0;
		while (tmp < 5) {
			out << scoreRank[tmp] << " ";
			++tmp;
		}
		out.close();
	} else {
		log("input");
		int tmp;
		int index = 0;
		while (input >> tmp) scoreRank[index++] = tmp;
	}
	input.close();


	LayerColor::initWithColor(cocos2d::Color4B::WHITE);
	visibleSize = Director::getInstance()->getVisibleSize();

	/************************************************************************/
	/*           Back Game                                                  */
	/************************************************************************/

	auto backGameLabel = Label::create(
		Configuration::getInstance()->getValue("back_str", Value("Back")).asString(),
		"Arial", 80);
	backGameLabel->setPosition(Point(0, visibleSize.height));
	backGameLabel->setAnchorPoint(Point(0, 1));
	backGameLabel->setTextColor(Color4B::RED);
	auto backGameLabelListener = EventListenerTouchOneByOne::create();
	backGameLabelListener->onTouchBegan = [backGameLabel](Touch *touch, Event *event) {
		if (backGameLabel->getBoundingBox().containsPoint(touch->getLocation())) {
			Director::getInstance()->replaceScene(GameMain::createScene());
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(backGameLabelListener, backGameLabel);
	addChild(backGameLabel);


	/************************************************************************/
	/*                         排行榜标题                                    */
	/************************************************************************/
	auto ranklabel = Label::create();
	ranklabel->setString(Configuration::getInstance()->getValue("rank", Value("Rank")).asString());
	ranklabel->setColor(Color3B::ORANGE);
	config.fontSize = 80;
	ranklabel->setTTFConfig(config);
	ranklabel->setPosition(Point(visibleSize.width / 2, visibleSize.height - 70));
	addChild(ranklabel);


	/************************************************************************/
	/*                          榜单                                         */
	/************************************************************************/
	//创建tableView并设置一些参数
	auto tableView = TableView::create(this, Size(400, visibleSize.height / 2));
	//设置TableViewDelegate
	tableView->setDelegate(this);
	tableView->setPosition(Point(visibleSize.width * 3 / 7, visibleSize.height / 4));
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
	tableView->reloadData();
	return true;
}



Size MaxScoreScene::cellSizeForTable(cocos2d::extension::TableView *table) {
	return Size(visibleSize.width / 2, visibleSize.height / 10);
}
Size MaxScoreScene::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) {
	return CCSizeMake(visibleSize.width / 2, visibleSize.height / 10);
}


TableViewCell* MaxScoreScene::tableCellAtIndex(TableView *table, ssize_t idx) {

	int fuck[] = { 1, 2, 3, 4, 5 };
	auto rankCell = table->dequeueCell();
	Label *rankNumLabel;

	if (rankCell == NULL) {
		rankNumLabel = Label::create(StringUtils::format("", fuck[idx], scoreRank[idx]), "fonts/girl.ttc", 20);
		rankNumLabel->setTextColor(Color4B::RED);
		rankNumLabel->setAnchorPoint(ccp(0,0));
		rankNumLabel->setTag(2);
		rankCell = TableViewCell::create();
		rankCell->addChild(rankNumLabel);
	} else {
		auto rankNumLabel = (Label *)rankCell->getChildByTag(2);
		rankNumLabel->setString(StringUtils::format(
			Configuration::getInstance()->getValue("ranking", Value("No.%d：%d")).asString().c_str(),
			fuck[idx], scoreRank[idx]));
	}

	return rankCell;
}

ssize_t MaxScoreScene::numberOfCellsInTableView(TableView *table) {
	return 5;
}