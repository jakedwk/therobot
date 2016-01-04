#include"serial.h"
#include"detecting.h"

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
    Detect dt;
    dt.detectinit(0);
    while(1)
    {
        dt.detecting();
        if(dt.key == 'q') break;
    }
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
