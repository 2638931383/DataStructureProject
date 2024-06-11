#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>
#include <random>
#include <set>
#include <cmath>

using namespace std;
#define numOfPoints 900
#define pointsAdjNum_MAX 9
#define M_PI 3.1415926535897932384626
#define EARTH_RADIUS 6378.137

void GetRoutes();
void bsetRoutes();
void create_AMGraph();
double Dijkstra(int , int);
void _ffind(int);

class subPoint
{
public:
	double Longitude;
	string Name;
	double Latitude;
	set<int> pointsAdj;
	int pointsAdjNum;

public:
	subPoint();
	subPoint(double, string, double, int);
	void printInfo();
	//subPoint();
	//subPoint(double, string, string, double, int, int);
	map<string, int> nameToInedxSub;
};

subPoint::subPoint(double longitude, string name, double latitude, int num)
{
	Longitude = longitude;
	Name = name;
	Latitude = latitude;
	pointsAdjNum = num;
}

subPoint::subPoint()
{

}

class Point
{
public:
	double Longitude;
	string Name;
	string Type;
	double Latitude;
	set<int> pointsAdj;
	int pointsAdjNum;
	float Scores;
	subPoint subpoint[numOfPoints];
	int subPointsNum;

public:
	Point();
	Point(double , string , string , double , int , int);
	void printInfo();
};

Point::Point(double longitude, string type, string name, double latitude, int num, int sub)
{
	Longitude = longitude;
	Name = name;
	Type = type;
	Latitude = latitude;
	pointsAdjNum = num;
	subPointsNum = sub;
}

Point::Point()
{

}

void Point::printInfo()
{
	cout << Name << endl;
	cout << Longitude << endl;
	cout << Latitude << endl;
	cout << Type << endl;
}

/***********************************************************/
class CalculateDistance 
{
private:
	static double rad(double d) 
	{
		return d * M_PI / 180.0;
	}

public:
	/**
	 * Calculate the distance between two points based on latitude and longitude coordinates (double values), in meters
	 */
	static double GetDistance(double lat1, double lng1, double lat2, double lng2) 
	{
		double radLat1 = rad(lat1);
		double radLat2 = rad(lat2);
		double a = radLat1 - radLat2;
		double b = rad(lng1) - rad(lng2);
		double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2)));
		s = s * EARTH_RADIUS;
		s = (s * 10000) / 10;
		return s;
	}
};

/***********************************************************/
map<string, int> nameToInedx;
Point point[numOfPoints];
bool visited[numOfPoints];
int nPoints;
double AMGraph[numOfPoints][numOfPoints];
double dis[numOfPoints];
int path[numOfPoints];							//dis保存最短路径总权值、path通过保存路径的前驱结点来保存路径
bool book[numOfPoints];
vector<int> MyEnd;
int start;
void show_Detail(int);
void bestRoutes();
void initAMGraph();
void printDis();

int  main()
{
	ifstream ifs;

	ifs.open("D:\\MyCode\\DataStructure Project\\university.csv", ios::in);	 //gonna to read universities

	if (!ifs.is_open())						
	{
		cout << "error";
		return 0;
	}

	vector<string> item;		

	string temp;				

	while (getline(ifs, temp))  
	{
		item.push_back(temp);
	}

	nPoints = 0;	
	double lo, la;


	for (auto it = item.begin(); it != item.end(); it++)
	{

		if (nPoints != 0)
		{
			string str[4];
			//其作用是把字符串分解为单词(在此处就是把一行数据分为单个数据)
			istringstream istr(*it);
			//将字符串流 istr 中的字符读入到 str 字符串中，读取方式是以逗号为分隔符 
			getline(istr, str[0], ',');
			getline(istr, str[1], ',');
			getline(istr, str[2], ',');
			getline(istr, str[3], ',');
			lo = stod(str[1]);
			la = stod(str[2]);
			point[nPoints] = Point(lo, str[3], str[0], la , 0 , 0);
			nameToInedx.insert(pair<string, int>(str[0], nPoints));

		}
		nPoints++;

	}

	//===================================================

	for (int i = 1; i <= nPoints; i++)
	{
		ifstream ifs;

		ifs.open("D:\\MyCode\\DataStructure Project\\" + point[i].Name + ".csv", ios::in);	 //gonna to read universities

		if (!ifs.is_open())
		{
			//cout << point[i].Name << "没有子点" << endl;
			continue;
		}

		vector<string> item;

		string temp;

		while (getline(ifs, temp))
		{
			item.push_back(temp);
		}

		int j = 0;
		double lo, la;


		for (auto it = item.begin(); it != item.end(); it++)
		{

			if (j != 0)
			{
				string str[4];
				//其作用是把字符串分解为单词(在此处就是把一行数据分为单个数据)
				istringstream istr(*it);
				//将字符串流 istr 中的字符读入到 str 字符串中，读取方式是以逗号为分隔符 
				getline(istr, str[0], ',');
				getline(istr, str[1], ',');
				getline(istr, str[2], ',');
				getline(istr, str[3], ',');
				lo = stod(str[1]);
				la = stod(str[2]);
				point[i].subpoint[j] = subPoint(lo , str[0], la, 0);
				point[i].subpoint[j].nameToInedxSub.insert(pair<string, int>(str[0], j));

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
	bestRoutes();
	return 0;
}

void GetRoutes()
{
	int adjNum, adjIndex;
	default_random_engine x, y;
	memset(visited, false, sizeof(visited));
	x.seed(time(0));
	y.seed(time(0));

	for (int i = 1; i <= nPoints; i++)
	{
		if (point[i].pointsAdjNum == pointsAdjNum_MAX) continue;
		uniform_int_distribution<int> u(1, pointsAdjNum_MAX - point[i].pointsAdjNum); // 左闭右闭区间
		adjNum = u(x);
		for (int j = 0; j < adjNum; j++)
		{
			uniform_int_distribution<int> w(1, nPoints);
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
	string start_point_temp;	//set<string> end_point;
	set<int> end;
	MyEnd.clear();
	string temp;
	cout << "请输入你的起点：" << endl;
	cin >> start_point_temp;
	start = nameToInedx[start_point_temp];
	cout << "请输入你的终点,\"#\"结束:" << endl;
	for (;;)
	{
		cin >> temp;
		if (temp == "#") break;
		if (nameToInedx[temp] == start) continue;
		if (!nameToInedx[temp])
		{
			cout << temp << "是无效地址" << endl;
			continue;
		}
		end.insert(nameToInedx[temp]);
	}
	int nEnd = end.size();
	int nEnd_temp = nEnd - 1;
	auto it = end.begin();
	int minsEnd = *it;
	double minDis = Dijkstra(start, *it);
	double distance;
	for (int i = 0; i < nEnd; i++)
	{
		for (auto it = end.begin();it != end.end();it++)
		{
			//it++;
			distance = Dijkstra(start, *it);
			if (distance <= minDis)
			{
				minDis = distance;
				minsEnd = *it;
			}
		}
		end.erase(minsEnd);
		MyEnd.push_back(minsEnd);
		Dijkstra(start, minsEnd);
		//nEnd--;
		_ffind(minsEnd);
		start = minsEnd;
		it = end.begin();
		if (i != nEnd - 1) minDis = Dijkstra(start, *it);
		cout << endl;
		cout << "距离为" << minDis << 'm' << endl;
	}

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
	cout << " -> " << point[start_point].Name;
	return;
}

void show_Detail(int index)
{
	if (!point[index].subPointsNum)
	{
		cout << point[index].Name << "没有子点" << endl;
		return;
	}
	cout << point[index].Name << "有以下子点：" << endl;
	for (int i = 1; i <= point[index].subPointsNum; i++)
	{
		cout << point[index].subpoint[i].Name << "(" << "经度：" << point[index].subpoint[i].Longitude << "," << " 纬度:" << point[index].subpoint[i].Latitude << ")" << endl;
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
	double test = Dijkstra(13, 78);

	std::stringstream ss;
	ss << std::fixed << test;
	std::cout << ss.str() << std::endl;
	_ffind(78);
}
