/*
 * QuestMap.cpp
 *
 *  Created on: 07.03.2014
 *      Author: Sergey Kashin
 */

#include "QuestMap.h"

using namespace bb::cascades;
using namespace bb::cascades::maps;// too lazy to type this everywhere...

QuestMap::QuestMap(Container* parent)
: MapView(parent),
  mQuestData(0)
{
}

QuestMap::~QuestMap()
{
}

QuestData* QuestMap::questData() const
{
	return mQuestData;
}

void QuestMap::setQuestData(QuestData* newData)
{
	if (mQuestData != newData)
	{
		if (mQuestData)
		{
			delete mQuestData;
		}
		mQuestData = newData;
		emit questDataChanged(mQuestData);
	}
}
