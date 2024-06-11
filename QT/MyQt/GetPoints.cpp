#include "GetPoints.h"
#include <random>

QMap<QString, int> nameToInedx_Mot;
Point point[numOfPoints];
bool visited[numOfPoints];
int nPoints;
double AMGraph[numOfPoints][numOfPoints];
double dis[numOfPoints];
int path[numOfPoints];							//dis保存最短路径总权值、path通过保存路径的前驱结点来保存路径
bool book[numOfPoints];
std::vector<int> MyEnd;
int start;

Point::Point(double longitude, QString type, QString name, double latitude, int num, int sub)
{
    Longitude = longitude;
    Name = name;
    Type = type;
    Latitude = latitude;
    pointsAdjNum = num;
    subPointsNum = sub;
}

subPoint::subPoint(double longitude, QString name, double latitude, int num)
{
	Longitude = longitude;
	Name = name;
	Latitude = latitude;
	pointsAdjNum = num;
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
    nPoints = 0;
    double lo, la;
    QFile file("D:\\MyCode\\DataStructure Project\\university.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "ERROR!";
        return;
    }
    QTextStream stream(&file);
    stream.setEncoding (QStringConverter::System); //------------------------
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        if (nPoints == 0)
        {
            nPoints++;
            continue;
        }
        QStringList row = line.split(',', Qt::SkipEmptyParts);

        lo = row[1].toDouble();
        la = row[2].toDouble();
        QString name = row[0].toUtf8();
        QString type = row[3].toUtf8();
        point[nPoints] = Point(lo, type, name, la , 0 , 0);
        nameToInedx_Mot.insert(name, nPoints);
        qDebug() << name << la << nPoints;
        nPoints++;
    }

    file.close();
	//===================================================

    for (int i = 1; i <= nPoints; i++)
    {
        QFile file("D:\\MyCode\\DataStructure Project\\" + point[i].Name + ".csv");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            //qDebug() << point[i].Name << "没有子点";
            continue;
        }
        QTextStream stream(&file);
        int j = 0;
        while (!stream.atEnd())
        {
            QString line = stream.readLine();
            QStringList row = line.split(',', Qt::SkipEmptyParts);
            if (j != 0)
            {
                lo = row[1].toDouble();
                la = row[2].toDouble();
                QString name = row[0];
                //QString type = row[3];
                point[i].subpoint[j] = subPoint(lo , name, la, 0);
                point[i].subpoint[j].nameToInedxSub.insert(name, j);

            }
            point[i].subPointsNum = j;
            j++;

        }
    }
	

	//===================================================
	GetRoutes();
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
