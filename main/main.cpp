#include"../src/serial.h"
#include"../src/detecting.h"
#include"../src/convey.h"

int main( int argc, char** argv )
{
    //int fd;
    //char a;
    //char buf[300];
 
    //if((fd = uart_init((char*)"ttyACM0", 0)) <0)   //打开串口，波特率为115200；
    //{
        //printf("Open uart err \n");
        //return -1;
    //}
    int sefd = 55,new_sockfd;
    char ack;
    Detect dt;
    Convey conv;
    dt.detectinit(1);
    conv.socketinit(sefd);
    cout<<sefd<<endl;
    new_sockfd = conv.accept_m(sefd);
    cout<<new_sockfd<<endl;
    while(1)
    {
        dt.detecting();
        conv.sendimg(new_sockfd,dt.frame);
        if(!conv.recvall(new_sockfd,&ack,1)) break;
    }
    close(new_sockfd);
    close(sefd);
    //sprintf(buf, "Hello world !\n");   //输出内容
  
    //while(1)
    //{
        //memset(buf, 0 ,sizeof(buf));
        //scanf("%c",&a);
        //write(fd,&a,sizeof(a));
        //read(fd,buf,64);
        //printf("%s\n",buf);
    //}
    return 0;
}
