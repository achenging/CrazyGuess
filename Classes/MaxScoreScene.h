#pragma once
#include <cocos2d.h>
#include <cocos-ext.h>
#include <vector>
class MaxScoreScene :public cocos2d::LayerColor
	, public  cocos2d::extension::TableViewDataSource, public  cocos2d::extension::TableViewDelegate {
private:
	int scoreRank[5];
	cocos2d::Size visibleSize;
	cocos2d::TTFConfig config = cocos2d::TTFConfig("fonts/girl.ttc", 80.f);
public:

	virtual bool init();

	CREATE_FUNC(MaxScoreScene);


	static cocos2d::Scene* createScene() {
		auto s = cocos2d::Scene::create();
		auto l = MaxScoreScene::create();
		s->addChild(l);
		return s;
	};

	//实现TableViewDataSource的虚函数

	/**
	* cell size for a given index
	*
	* @param idx the index of a cell to get a size
	* @return size of a cell at given index
	*/
	virtual  cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	/**
	* cell height for a given table.
	*
	* @param table table to hold the instances of Class
	* @return cell size
	*/
	virtual  cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
	/**
	* a cell instance at a given index
	*
	* @param idx index to search for a cell
	* @return cell found at idx
	*/
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	/**
	* Returns number of cells in a given table view.
	*
	* @return number of cells
	*/
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);


	//实现TableViewDelegate的虚函数
	/**
	* Delegate to respond touch event
	*
	* @param table table contains the given cell
	* @param cell  cell that is touched
	* @js NA
	* @lua NA
	*/
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) {};


};

