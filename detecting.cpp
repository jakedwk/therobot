#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex> 

using namespace cv;
using namespace std;
class  Detect
{
    Rect ret;
    time_t now_time;
    struct tm *p;
    char fmt_time[100];
    bool occ;
    int times;
    char key;
    String svtime,path;  //保存路径与文件名
    VideoCapture cap;
    vector<vector<Point> > contours;
    Scalar color,mean;
    Mat gray,avg,differ,frame,frameold,bigger,thresh;
    Mat element ;
    int sockfd,client_fd,new_server_socket;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;
    struct sockaddr_in their_addr;
    vector<uchar> buff;//buffer for coding
    vector<int> param;
    unsigned int datasize;
    int freeman;
    struct timeval tpstart,tpend; 
    float timeuse; 
    uint vsize;
    vector<uchar> vbuf;
    vector<int> recv_sockets,send_sockets;
    public:
        Detect();
        int ckcamera();
        void detectinit(int i);
        void detecting();
};
Detect::Detect(){};

int Detect::ckcamera()
{
    if(!cap.isOpened())  // check if we succeeded
    {
        cout<<"设备打开错误";
        return -1;
    }
    for(int i=50;i>=0;i--)
    {
        cap >> frame;
    }
    return 1;
}
void Detect::detectinit(int i)
{

    cap = VideoCapture(i);
    ckcamera();
    cap >> frame;
    occ = 0;
    color = Scalar( 0, 255, 0);
    element = getStructuringElement( 0,Size( 3, 3 ), Point(1, 1 ) );
    //初始化背景帧
    cap >> frame;
    cvtColor(frame, avg, COLOR_BGR2GRAY);
    GaussianBlur(avg, avg, Size(7,7), 1.5, 1.5);
    gray = avg.clone();
    frameold = gray.clone();
}

void Detect::detecting()
{
    cap >> frame;                                        // 获取一帧图像
    cvtColor(frame, gray, COLOR_BGR2GRAY);               //转化为灰度图像
    threshold(differ,thresh, 40, 255, THRESH_BINARY);    //根据给出的阈值二值化
    dilate(thresh,bigger, element,Point(-1,-1), 1);      //膨胀图像
    findContours(bigger,contours, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);  //寻找轮廓
    for(unsigned int j = 0; j < contours.size()-1; j++ )
    {
        if (contourArea(contours[0])<contourArea(contours[j+1]))
        contours[0] = contours[j+1];
    }
    ret = boundingRect(contours[0]);
    rectangle(frame,ret,color,2);
    
}
