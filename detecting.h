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
    int times;
    String svtime,path;  //保存路径与文件名
    VideoCapture cap;
    vector<vector<Point> > contours;
    Scalar color,mean;
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
        bool occ;
        char key;
        Mat gray,avg,differ,frame,frameold,bigger,thresh;
        Detect();
        ~Detect();
        int ckcamera();
        void detectinit(int i);
        void detecting();
};
