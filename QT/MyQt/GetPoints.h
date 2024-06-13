#ifndef GETPOINTS_H
#define GETPOINTS_H
//#include <iostream>
//#include <fstream>
//#include <sstream>
#include <QFile>
#include <QTextStream>
#include <vector>
//#include <map>
//#include <ctime>
//#include <random>
#include <set>
//#include <cmath>
//#include <cstring>
#include <QMap>
#include <QDebug>
//using namespace std;
#define numOfPoints 900
#define pointsAdjNum_MAX 9
//#define M_PI 3.1415926535897932384626
#define EARTH_RADIUS 6378.137
#define DBL_MAX std::numeric_limits<double>::max()


void GetRoutes();
void bsetRoutes();
void create_AMGraph();
double Dijkstra(int , int);
void _ffind(int);
void show_Detail(int);
void bestRoutes();
void initAMGraph();
void printDis();
void readPoints(void);
//------------------------------------

enum Point_Type
{
    EDU , FOOD , landscape , hospital , traffic , other
};

class subPoint
{
public:
    double Longitude;
    QString Name;
    double Latitude;
    std::set<int> pointsAdj;
    int pointsAdjNum;
    QString type;

public:
    subPoint();
    subPoint(double, QString, double, int ,std::set<int>,QString t);
    void printInfo();
    //subPoint();
    //subPoint(double, string, string, double, int, int);

};

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

    CalculateDistance(){}
    ~CalculateDistance(){}
};

/***********************************************************/

class Point
{
public:
    double Longitude;
    QString Name;
    QString Type;
    double Latitude;
    std::set<int> pointsAdj;
    int pointsAdjNum;
    float Scores;
    subPoint subpoint[numOfPoints];
    int subPointsNum;
    //Point_Type Type_;
    double marks;
    double views;
    QMap<QString, int> nameToInedxSub;
public:
    Point();
    Point(double , QString , QString , double , int , int ,double , double );
    void printInfo();
};

extern QMap<QString, int> nameToInedx_Mot;
extern Point point[numOfPoints];
extern bool visited[numOfPoints];
extern int nPoints;
extern double AMGraph[numOfPoints][numOfPoints];
extern double dis[numOfPoints];
extern int path[numOfPoints];							//dis保存最短路径总权值、path通过保存路径的前驱结点来保存路径
extern bool book[numOfPoints];
extern std::vector<int> MyEnd;
extern int start;



#endif // GETPOINTS_H
