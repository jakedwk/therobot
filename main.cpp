#include"serial.h"
int main()
{
    int fd,len = 0;
    char a;
    char buf[300];
 
    if((fd = uart_init((char*)"ttyACM0", 0)) <0)   //打开串口，波特率为115200；
    {
        printf("Open uart err \n");
        return -1;
    }
    sprintf(buf, "Hello world !\n");   //输出内容
  
    while(1)
    {
        memset(buf, 0 ,sizeof(buf));
        scanf("%c",&a);
        write(fd,&a,sizeof(a));
        len = read(fd,buf,64);
        printf("%s\n",buf);
    }
    return 0;
}
