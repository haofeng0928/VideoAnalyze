#include "graphdata.h"
GraphData::GraphData()
{
	this->data.resize(87000);
	for (int i = 0; i < data.size(); i++)
	{
		data[i] = 0;
	}
}
GraphData::GraphData(const GraphData &tmp)
{
	this->data = tmp.data;
	this->datefileName = tmp.datefileName;
}
QDataStream & operator <<(QDataStream &out, const GraphData &tmp)
{
	out << tmp.data;
	out << tmp.start;
	out << tmp.end;
	out << tmp.placeText;
	tmp.resCode.fromRawData(tmp.szResCode, IMOS_RES_CODE_LEN);
	out << tmp.resCode;
	return out;
}
QDataStream & operator >> (QDataStream &in, GraphData &tmp)
{
	in >> tmp.data;
	in >> tmp.start;
	in >> tmp.end;
	in >> tmp.placeText;
	in >> tmp.resCode;
	memcpy(tmp.szResCode, tmp.resCode.data(), IMOS_RES_CODE_LEN);
	return in;
}