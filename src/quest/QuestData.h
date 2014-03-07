/*
 * QuestData.h
 *
 *  Created on: 07.03.2014
 *      Author: Sergey Kashin
 */

#ifndef QUESTDATA_H_
#define QUESTDATA_H_

#include <QObject>

class QuestData: public QObject {
Q_OBJECT
public:
	QuestData(QObject* parent);
	virtual ~QuestData();
};

#endif /* QUESTDATA_H_ */
