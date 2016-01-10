#include "detecting.h"

Detect::Detect(){};

Detect::~Detect(){
    destroyAllWindows();
    cap.release();
};

int Detect::ckcamera()
{
    if(!cap.isOpened())  // check if we succeeded
    {
        cout<<"设备打开错误";
        return -1;
    }
    for(int i=10;i>=0;i--)
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
    double thresh_value;
    cap >> frame;                                        // 获取一帧图像
    cvtColor(frame, gray, COLOR_BGR2GRAY);               //转化为灰度图像
    mean = cv::mean(gray); //名称空间重复故使用cv::
    thresh_value = mean[0]*0.4;
    threshold(gray,thresh, thresh_value, 225, CV_THRESH_BINARY_INV);    //根据给出的阈值二值化
    dilate(thresh,bigger, element,Point(-1,-1), 1);      //膨胀图像
    findContours(bigger,contours, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);  //寻找轮廓
    if(contours.size()>1)
        for(unsigned int j = 0; j < contours.size()-1; j++ )
        {
            if (contourArea(contours[0])<contourArea(contours[j+1]))
                contours[0] = contours[j+1];
        }
    if(contours.size()<=0||contourArea(contours[0])<50)
    {
        ior_dir.str("");
        ior_dir<<"nothing";
    }else
    {
        ret = boundingRect(contours[0]);
        rectangle(frame,ret,color,2);
        ior_dir.str("");
        dir = ret.x + ret.width/2;
        ior_dir<<dir;
    }
    putText(frame,ior_dir.str(),Point(20,25),FONT_HERSHEY_SIMPLEX,1,color);
    //imshow("gray",thresh);
    //imshow("frame",frame);
    //key = waitKey(25)&0xFF;
}
