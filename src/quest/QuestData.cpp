/*
 * QuestData.cpp
 *
 *  Created on: 07.03.2014
 *      Author: Sergey Kashin
 */

#include "QuestData.h"
#include <QFile>
#include <QDir>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QXmlStreamAttributes>

using namespace bb::cascades::maps;

static const QString QUESTS_FOLDER = "quests/";

static const QString QUEST_ID_XML_NAME = "ID";
static const QString QUEST_NAME_XML_NAME = "Name";

QuestData::QuestData(QObject* parent)
: MapData(parent)
{
}

QuestData::~QuestData()
{
}

void QuestData::setName(const QString& newName)
{
	if (!mQuestName.compare(newName))
	{
		mQuestName = newName;
		emit nameChanged(mQuestName);
		QStringList fileNames = findQuestFilesAndDirsByName(mQuestName);
		if (fileNames.isEmpty())
		{
			qDebug() << "QuestData::setName: no xml file is found for name=" << mQuestName;
		}
		else if (fileNames.count() == 1)
		{
			loadDataFromFile(fileNames.first());
		}
	}
}

QString QuestData::name() const
{
	return mQuestName;
}

void QuestData::setQuestID(const QString& newQuestID)
{
	if (!mQuestID.compare(newQuestID))
	{
		mQuestID = newQuestID;
		emit questIDChanged(mQuestID);
		loadDataByQuestID(mQuestID);
	}
}

QString QuestData::questID() const
{
	return mQuestID;
}

void QuestData::saveQuest()
{
	if (mFileName.isEmpty())
	{
		mFileName = mQuestID + QString('_') + mQuestName + QString(".xml");
	}
	QFile file(mFileName);
	file.open(QIODevice::WriteOnly);

	QXmlStreamWriter xmlWriter(&file);
	xmlWriter.setAutoFormatting(true);

	xmlWriter.writeStartDocument();
	{

		xmlWriter.writeStartElement("QuestDescription");
		{
			xmlWriter.writeTextElement(QUEST_ID_XML_NAME, mQuestID );
			xmlWriter.writeTextElement(QUEST_NAME_XML_NAME, mQuestName);
		}
		xmlWriter.writeEndElement();
	}
	xmlWriter.writeEndDocument();

	file.close();
}

bool QuestData::isUniqueQuestName(const QString& name) const
{
	bool result = false;

	QStringList foundFilesAndDirs = findQuestFilesAndDirsByName(QString("*") + name);
    if (!foundFilesAndDirs.isEmpty())
    {
    	result = true;
    }
    return result;
}

QStringList QuestData::findQuestFilesAndDirsByName(const QString& name) const
{
    QStringList nameFilter(name +"*.xml");
    QDir directory(QUESTS_FOLDER);
    return directory.entryList(nameFilter);
}

void QuestData::loadDataFromFile(const QString& fileName)
{
	mFileName = fileName;
	QFile file(mFileName);
	qWarning() << "QuestData::loadDataFromFile: is called for file" << fileName;
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
			qWarning() << "QuestData::loadDataFromFile: can't load a file with name =" << mFileName;
	}
	else
	{
		QXmlStreamReader xmlReader;
		xmlReader.setDevice(&file);
		xmlReader.readNext();

		while(!xmlReader.atEnd())
		{
			if(xmlReader.isStartElement())
			{
				if (xmlReader.name() == "QuestDescription")
				{
					QXmlStreamAttributes attributes = xmlReader.attributes();
					if (attributes.hasAttribute(QUEST_ID_XML_NAME))
					{
						setQuestID(attributes.value(QUEST_ID_XML_NAME).toString());
					}
					else
					{
						qWarning() << "QuestData::loadDataFromFile: no ID attribute" ;
					}

					if (attributes.hasAttribute(QUEST_NAME_XML_NAME))
					{
						setName(attributes.value(QUEST_NAME_XML_NAME).toString());
					}
					else
					{
						qWarning() << "QuestData::loadDataFromFile: no Name attribute" ;
					}
				}
			}
			else
			{
				qWarning() << "QuestData::loadDataFromFile: not a first element" ;
			}
			xmlReader.readNext();
		}
	}
}

void QuestData::loadDataByQuestID(const QString& questID)
{
	QStringList foundFiles = findQuestFilesAndDirsByName(questID + QString("_"));
	if (foundFiles.isEmpty())
	{
		qDebug() << "QuestData::loadDataByQuestID: file is not found for questID =" << questID;
	}
	else if (foundFiles.count() == 1)
	{
		loadDataFromFile(foundFiles.first());
	}
	else
	{
		qWarning() << "QuestData::loadDataByQuestID: found more then one file for questID =" << questID;
	}
}
