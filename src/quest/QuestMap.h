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
	Q_OBJECT
public:
	QuestMap(bb::cascades::Container* parent = 0);
	virtual ~QuestMap();

	Q_PROPERTY(QuestData* questData READ questData WRITE setQuestData NOTIFY questDataChanged)

	QuestData* questData() const;
	/// @brief QuestMap become a parent of a QuestData and it frees its memory when ever it need to do so.
	void setQuestData(QuestData* newData);

signals:
	void questDataChanged(QuestData* newData);

private:
	QuestData* mQuestData;
};

#endif /* QUESTMAP_H_ */
