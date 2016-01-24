#include <iostream>
#include "StockNode.hpp"

StockNode::StockNode()
{
	price = 0;
}

StockNode::~StockNode(){}


int StockNode::getStockPrice(void)
{
	return price;
}

void StockNode::setStockPrice(int priceValue)
{
	price = priceValue;
}

void StockNode::setStockTicker(const std::string &str)
{
	ticker = str;
}

const std::string& StockNode::getStockTicker(void)
{
	return ticker;
}