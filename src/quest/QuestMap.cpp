/*
 * QuestMap.cpp
 *
 *  Created on: 07.03.2014
 *      Author: Sergey Kashin
 */

#include "QuestMap.h"

QuestMap::QuestMap(QuestData* data)
{
	mQuestData = data;
	mQuestData->setParent(this);
}

QuestMap::~QuestMap()
{
}

