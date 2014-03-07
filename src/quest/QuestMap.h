/*
 * QuestMap.h
 *
 *  Created on: 07.03.2014
 *      Author: Sergey Kashin
 */

#ifndef QUESTMAP_H_
#define QUESTMAP_H_

#include <bb/cascades/maps/MapView>

#include "QuestData.h"

class QuestMap: public bb::cascades::maps::MapView {
public:
	/// @brief QuestMap owns a ref on a passed QuestData
	/// and frees memory when QuestMap object is destroyed.
	QuestMap(QuestData* data);
	virtual ~QuestMap();

private:
	QuestData* mQuestData;
};

#endif /* QUESTMAP_H_ */
