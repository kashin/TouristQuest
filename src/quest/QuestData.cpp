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
static const QString QUEST_FILES_DIR_PATH = QDir::currentPath() + QString("/data/") + QUESTS_FOLDER;

QuestData::QuestData(QObject* parent)
: MapData(parent)
{
}

QuestData::~QuestData()
{
}

void QuestData::setName(const QString& newName)
{
	if (mQuestName.compare(newName) != 0)
	{
		mQuestName = newName;
		emit nameChanged(mQuestName);
		QStringList fileNames = findQuestFilesAndDirsByName(QString('*') + mQuestName);
		if (fileNames.count() == 1)
		{
			loadDataFromFile(fileNames.first());
			QStringList tmpList = fileNames.first().split('_');
			mQuestID = tmpList.first();
		}
		else
		{
			qDebug() << "QuestData::setName: no xml file is found for name=" << mQuestName;
			// clear quest ID if name is changed
			setQuestID("");
		}
	}
}

QString QuestData::name() const
{
	return mQuestName;
}

void QuestData::setQuestID(const QString& newQuestID)
{
	if (mQuestID.compare(newQuestID) != 0)
	{
		mQuestID = newQuestID;
		emit questIDChanged(mQuestID);
		if (!mQuestID.isEmpty())
		{
			loadDataByQuestID(mQuestID);
		}
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
		if (mQuestID.isEmpty())
		{
			// TODO: generate quest ID
			mQuestID = "1";
		}
		mFileName = mQuestID + QString('_') + mQuestName + QString(".xml");
	}
	QString path = QUEST_FILES_DIR_PATH;
	QDir dir(path);
	if (!dir.exists())
	{
		qDebug() << "dir was not exist" << "created path=" << path << dir.mkpath(path);
		dir.cd(path);
	}

	QFile file(dir.absoluteFilePath(mFileName));
	if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
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
	else
	{
		qWarning() << "QuestData::saveQuest: can't open file" << file.fileName() << "; error:" << file.error();
	}
}

bool QuestData::isUniqueQuestName(const QString& name) const
{
	bool result = false;

	QStringList foundFilesAndDirs = findQuestFilesAndDirsByName(QString("*") + name);
    if (foundFilesAndDirs.count() == 1)
    {
    	result = true;
    }
    return result;
}

QStringList QuestData::findQuestFilesAndDirsByName(const QString& name) const
{
    QStringList nameFilter(name +"*.xml");
    QDir directory(QUEST_FILES_DIR_PATH);
    return directory.entryList(nameFilter, QDir::Files);
}

void QuestData::loadDataFromFile(const QString& fileName)
{
	mFileName = fileName;
	QFile file(QUEST_FILES_DIR_PATH + mFileName);
	qDebug() << file.fileName();
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
		QStringList tmpList = foundFiles.first().split('_');
		if (tmpList.count() > 1 )
		{
			QString tmpStr = tmpList.at(1);
			tmpList = tmpStr.split(QString(".xml"));
			mQuestName = tmpList.first();
		}
	}
	else
	{
		qWarning() << "QuestData::loadDataByQuestID: found more then one file for questID =" << questID;
	}
}
