#include "GetPoints.h"
#include <random>
#include <QDir>
#include "MySQL_Operate.h"
QMap<QString, int> nameToInedx_Mot;
Point point[numOfPoints];
bool visited[numOfPoints];
int nPoints;
double AMGraph[500][500];
double dis[numOfPoints];
int path[numOfPoints];							//dis保存最短路径总权值、path通过保存路径的前驱结点来保存路径
bool book[numOfPoints];
std::vector<int> MyEnd;
int start;

Point::Point(double longitude, QString type, QString name, double latitude, int num, int sub ,double m,double v)
{
    Longitude = longitude;
    Name = name;
    Type = type;
    Latitude = latitude;
    pointsAdjNum = num;
    subPointsNum = sub;
    //Type_ = type_;
    marks = m;
    views = v;
}

subPoint::subPoint(double longitude, QString name, double latitude, int num,std::set<int> adj,QString t)
{
	Longitude = longitude;
	Name = name;
	Latitude = latitude;
	pointsAdjNum = num;
    pointsAdj = adj;
    type = t;
}

subPoint::subPoint()
{

}



Point::Point()
{

}

void Point::printInfo()
{
    //cout << Name << endl;
    qDebug() << Longitude;
    qDebug() << Latitude;
    //cout << Type << endl;
}




void readPoints()
{
    nPoints = 1;
    // QFile file("./point/Point.CSV");
    // if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    // {
    //     qDebug() << "ERROR!";
    //     return;
    // }
    // QTextStream stream(&file);
    // stream.setEncoding (QStringConverter::System); //------------------------
    // while (!stream.atEnd())
    // {
    //     QString line = stream.readLine();
    //     if (nPoints == 0)
    //     {
    //         nPoints++;
    //         continue;
    //     }
    //     QStringList row = line.split(',', Qt::SkipEmptyParts);

    //     lo = row[1].toDouble();
    //     la = row[2].toDouble();
    //     QString name = row[0].trimmed().toUtf8();  // 去除首尾空白字符
    //     QString type = row[3].trimmed().toUtf8();  // 去除首尾空白字符
    //     QString temp = type;
    //     QStringList type_temp = temp.split(';' , Qt::SkipEmptyParts);
    //     if (type_temp[0].compare(QString::fromLocal8Bit("科教文化服务")) == 0)
    //     {
    //         point[nPoints] = Point(lo, QString::fromLocal8Bit("学校"), name, la , 0 , 0 , EDU);
    //         QSqlQuery query;
    //         QString myquery = QString("INSERT INTO points (index_point, name, longitude, latitude, type, marks, views) VALUES (%1, '%2', %3, %4, '%5', %6, %7)")
    //                               .arg(nPoints)  // 使用你的索引值或其他适当的值
    //                               .arg(name) // 避免 SQL 注入攻击，替换单引号s
    //                               .arg(lo)
    //                               .arg(la)
    //                               .arg(QString::fromLocal8Bit("学校"))
    //                               .arg(0)  // 使用适当的标记值或其他默认值
    //                               .arg(0);
    //         query.exec(myquery);
    //     }
    //     else if (type_temp[0].compare(QString::fromLocal8Bit("医疗保健服务")) == 0)
    //     {
    //         point[nPoints] = Point(lo, QString::fromLocal8Bit("医院"), name, la , 0 , 0 , hospital);
    //         QSqlQuery query;
    //         QString myquery = QString("INSERT INTO points (index_point, name, longitude, latitude, type, marks, views) VALUES (%1, '%2', %3, %4, '%5', %6, %7)")
    //                               .arg(nPoints)  // 使用你的索引值或其他适当的值
    //                               .arg(name) // 避免 SQL 注入攻击，替换单引号s
    //                               .arg(lo)
    //                               .arg(la)
    //                               .arg(QString::fromLocal8Bit("医疗保健服务"))
    //                               .arg(0)  // 使用适当的标记值或其他默认值
    //                               .arg(0);
    //         query.exec(myquery);
    //     }
    //     else if(type_temp[0].compare(QString::fromLocal8Bit("风景名胜")) == 0)
    //     {
    //         point[nPoints] = Point(lo, QString::fromLocal8Bit("风景名胜"), name, la , 0 , 0 , landscape);
    //         QSqlQuery query;
    //         QString myquery = QString("INSERT INTO points (index_point, name, longitude, latitude, type, marks, views) VALUES (%1, '%2', %3, %4, '%5', %6, %7)")
    //                               .arg(nPoints)  // 使用你的索引值或其他适当的值
    //                               .arg(name) // 避免 SQL 注入攻击，替换单引号s
    //                               .arg(lo)
    //                               .arg(la)
    //                               .arg(QString::fromLocal8Bit("风景名胜"))
    //                               .arg(0)  // 使用适当的标记值或其他默认值
    //                               .arg(0);
    //         query.exec(myquery);
    //     }
    //     else if(type_temp[0].compare(QString::fromLocal8Bit("交通设施服务")) == 0)
    //     {
    //         point[nPoints] = Point(lo, QString::fromLocal8Bit("交通设施服务"), name, la , 0 , 0 , traffic);
    //         QSqlQuery query;
    //         QString myquery = QString("INSERT INTO points (index_point, name, longitude, latitude, type, marks, views) VALUES (%1, '%2', %3, %4, '%5', %6, %7)")
    //                               .arg(nPoints)  // 使用你的索引值或其他适当的值
    //                               .arg(name) // 避免 SQL 注入攻击，替换单引号s
    //                               .arg(lo)
    //                               .arg(la)
    //                               .arg(QString::fromLocal8Bit("交通设施服务"))
    //                               .arg(0)  // 使用适当的标记值或其他默认值
    //                               .arg(0);
    //         query.exec(myquery);
    //     }
    //     else if (type_temp[0].compare(QString::fromLocal8Bit("餐饮服务")) == 0)
    //     {
    //         point[nPoints] = Point(lo, QString::fromLocal8Bit("餐饮"), name, la , 0 , 0 , FOOD);
    //         QSqlQuery query;
    //         QString myquery = QString("INSERT INTO points (index_point, name, longitude, latitude, type, marks, views) VALUES (%1, '%2', %3, %4, '%5', %6, %7)")
    //                               .arg(nPoints)  // 使用你的索引值或其他适当的值
    //                               .arg(name) // 避免 SQL 注入攻击，替换单引号s
    //                               .arg(lo)
    //                               .arg(la)
    //                               .arg(QString::fromLocal8Bit("餐饮"))
    //                               .arg(0)  // 使用适当的标记值或其他默认值
    //                               .arg(0);
    //         query.exec(myquery);
    //     }
    //     else
    //     {
    //         point[nPoints] = Point(lo, "nothing important", name, la , 0 , 0 , other);
    //         QSqlQuery query;
    //         QString myquery = QString("INSERT INTO points (index_point, name, longitude, latitude, type, marks, views) VALUES (%1, '%2', %3, %4, '%5', %6, %7)")
    //                               .arg(nPoints)  // 使用你的索引值或其他适当的值
    //                               .arg(name) // 避免 SQL 注入攻击，替换单引号s
    //                               .arg(lo)
    //                               .arg(la)
    //                               .arg("nothing important")
    //                               .arg(0)  // 使用适当的标记值或其他默认值
    //                               .arg(0);
    //         query.exec(myquery);
    //     }
    QSqlQuery query("SELECT * FROM points");
    while (query.next()) {
        int index_point = query.value(0).toInt();
        QString name = query.value(1).toString().toUtf8();
        double longitude = query.value(2).toDouble();
        double latitude = query.value(3).toDouble();
        QString type = query.value(4).toString().toUtf8();
        double marks = query.value(5).toDouble();
        int views = query.value(6).toInt();
        point[nPoints] = Point(longitude, type, name, latitude , 0 , 0 , marks , views);

        nameToInedx_Mot.insert(name, nPoints);
        //qDebug() << point[nPoints].Name << point[nPoints].Type << point[nPoints].Longitude;
        nPoints++;
    }


        //qDebug() << name << point[nPoints].Type << nPoints << point[nPoints].Type_;



	//===================================================

    for (int i = 1; i < nPoints; i++)
    {
        QString pointName = (point[i].Name);
        QFile file("./point/" + (pointName) + ".csv");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            //qDebug() << point[i].Name << "没有子点";
            continue;
        }
        qDebug() << "./point/" + point[i].Name + ".csv";
        QTextStream stream(&file);
        int j = 1;
        // while (!stream.atEnd())
        // {
        //     QString line = stream.readLine();
        //     QStringList row = line.split(',', Qt::SkipEmptyParts);
        //     double lo = row[1].toDouble();
        //      double la = row[2].toDouble();
        //     QString name = row[0].trimmed().toUtf8();
        //     QString type = row[4].trimmed().toUtf8();
        //     QString padj = row[5].trimmed();
        //     QStringList pointsList = padj.split(',', Qt::SkipEmptyParts);
        //     std::set<int> pointsadj;
        //     for (const QString& point_ : pointsList)
        //     {
        //         bool ok;
        //         int pointInt = point_.toInt(&ok);
        //         if (ok) {
        //             pointsadj.insert(pointInt);
        //     }
        //     point[i].subpoint[j] = subPoint(lo , name, la, 0 , pointsadj ,type);
        //     point[i].subpoint[j].nameToInedxSub.insert(name, j);

        //     }
        //     point[i].subPointsNum = j;
        //     j++;

        // }
    }
	

	//===================================================
    //GetRoutes();
	//point[100].printInfo();
	//show_Detail(48);
	//cout << point[48].subPointsNum << endl;
	//printDis();
    //bestRoutes();
    return;
}

void GetRoutes()
{
	int adjNum, adjIndex;
    std::default_random_engine x, y;
    memset(visited, false, sizeof(visited));
	x.seed(time(0));
	y.seed(time(0));

	for (int i = 1; i <= nPoints; i++)
	{
		if (point[i].pointsAdjNum == pointsAdjNum_MAX) continue;
        std::uniform_int_distribution<int> u(1, pointsAdjNum_MAX - point[i].pointsAdjNum); // 左闭右闭区间
		adjNum = u(x);
		for (int j = 0; j < adjNum; j++)
		{
            std::uniform_int_distribution<int> w(1, nPoints);
			adjIndex = w(y);
			if (point[i].pointsAdj.find(adjIndex) != point[i].pointsAdj.end() || point[adjIndex].pointsAdjNum == pointsAdjNum_MAX || adjIndex == i) continue;
			point[i].pointsAdjNum++;
			point[i].pointsAdj.insert(adjIndex);
			point[adjIndex].pointsAdjNum++;
			point[adjIndex].pointsAdj.insert(i);
		}
	}
}

void bestRoutes()
{

}


void create_AMGraph()
{
	initAMGraph();
	double distance;
	CalculateDistance calculateDistance;
	for (int i = 1; i <= nPoints; i++)
	{
		AMGraph[i][i] = 0;
		if (!point[i].pointsAdjNum) continue;
		for (auto it = point[i].pointsAdj.begin();it != point[i].pointsAdj.end();it++)
		{
			distance = calculateDistance.GetDistance(point[i].Latitude, point[i].Longitude, point[*it].Latitude, point[*it].Longitude);
			AMGraph[i][*it] = distance;
			AMGraph[*it][i] = distance;
		}
	}
}

double Dijkstra(int start_point , int end_point)	
{
	memset(path, -1, nPoints);
	memset(book, false, nPoints);
	create_AMGraph();
	for (int i = 1; i <= nPoints; i++)
	{
		dis[i] = AMGraph[start_point][i];						
		path[i] = dis[i] < DBL_MAX ? start_point : -1;			
	}
	book[start_point] = true;
	dis[start_point] = 0;										
	for (int i = 1; i <= nPoints; i++)				
	{
		if (i == start_point) continue;
		double mins = DBL_MAX;
		int u = start_point;
		for (int j = 1; j <= nPoints; j++)			
		{
			if (!book[j] && mins > dis[j]) {
				mins = dis[j];
				u = j;
			}
		}
		book[u] = true;								
		for (int j = 1; j <= nPoints; j++)			
		{
			if (!book[j] && dis[j] > dis[u] + AMGraph[u][j]) {
				dis[j] = dis[u] + AMGraph[u][j];		
				path[j] = u;						
			}
		}
	}
	return dis[end_point];
}

void _ffind(int start_point)									//递归输出最短路径
{
	if (path[start_point] == start_point) {
		//cout << point[start_point].Name;
	}
	else {
		_ffind(path[start_point]);
	}
    qDebug() << " -> " << point[start_point].Name;
	return;
}

void show_Detail(int index)
{
	if (!point[index].subPointsNum)
	{
        qDebug() << point[index].Name << "没有子点";
		return;
	}
    qDebug() << point[index].Name << "有以下子点：";
	for (int i = 1; i <= point[index].subPointsNum; i++)
	{
        qDebug() << point[index].subpoint[i].Name << "(" << "经度：" << point[index].subpoint[i].Longitude << "," << " 纬度:" << point[index].subpoint[i].Latitude << ")";
	}
}

void initAMGraph()
{
	for (int i = 1; i <= nPoints; i++)
	{
		for (int j = 1; j <= nPoints; j++)
		{
			AMGraph[i][j] = DBL_MAX;
		}
	}
}

void printDis()
{

}
