#pragma once

#include <QVector>
#include <QDateTime>
#include <QDataStream>
#include "IMOS.h"
#include <QByteArray>
class GraphData
{
public:
	GraphData();
	GraphData(const GraphData &);
	QVector<double> data;
	QString datefileName;
	QDateTime start;
	QDateTime end;
	char szResCode[IMOS_RES_CODE_LEN];
	QByteArray resCode;
	QString placeText;
	friend QDataStream & operator <<(QDataStream &out, GraphData const &tmp);
	friend QDataStream & operator >> (QDataStream &out, GraphData &tmp);
};
