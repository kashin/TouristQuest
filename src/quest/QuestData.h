/*
 * QuestData.h
 *
 *  Created on: 07.03.2014
 *      Author: Sergey Kashin
 */

#ifndef QUESTDATA_H_
#define QUESTDATA_H_

#include <bb/cascades/maps/MapData>

class QuestData: public bb::cascades::maps::MapData {
Q_OBJECT
public:

	/// @brief holds a name of a quest. Might be used to be able to determine a quest if name is unique.
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

	/// @brief holds a name of a quest. Might be used to be able to determine a quest if name is unique.
	Q_PROPERTY(QString questID READ questID WRITE setQuestID NOTIFY questIDChanged)


	QuestData(QObject* parent = 0);
	virtual ~QuestData();

// methods
public:
	void setName(const QString& newName);
	QString name() const;

	void setQuestID(const QString& newQuestID);
	QString questID() const;

public slots:
	/// @brief saves current quest data on a disk;
	void saveQuest();

signals:
	void nameChanged(const QString& newName);
	void questIDChanged(const QString& newQuestID);

private:
	bool isUniqueQuestName(const QString& name) const;
	QStringList findQuestFilesAndDirsByName(const QString& name) const;
	void loadDataFromFile(const QString& fileName);
	void loadDataByQuestID(const QString& questID);

private:
	QString mQuestName;
	QString mQuestID;
	QString mFileName;
};

#endif /* QUESTDATA_H_ */
