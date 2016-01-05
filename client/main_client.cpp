#include "../src/convey.h"

#define IPADDR "127.0.0.1"
int main( int argc, char** argv )
{
    int fd;
    char key,ack='o';
    Mat frame(Size(640,480),CV_8UC3) ;
    Convey conv;
    conv.clientinit(fd,IPADDR);
    while(1)
    {
        conv.recvimg(fd,frame);
        imshow("frame",frame);
        key = waitKey(1)&0xFF;
        if (key == 'q') break;
        send(fd,&ack,1,0);
    }
    close(fd);
}
