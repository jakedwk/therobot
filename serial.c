#include "serial.h" 
int uart_init(char* arg, int baud)
{
    int fd;
    char port[20];
    struct termios Opt;
    int uartbiit[50]= {B115200,B9600,B19200,B4800,B2400,B1200};
 
    sprintf(port,"/dev/%s",arg);   
    printf("Use port: %s \n", port);
    fd = open(port, O_RDWR);     //打开串口
    if (fd<0)
    {
        return -1;                 //没有打开返回
    }
 
    tcgetattr(fd,&Opt);      //初始化
    tcflush(fd,TCIFLUSH);
    cfsetispeed(&Opt,uartbiit[baud]);    //设置波特率
    cfsetospeed(&Opt,uartbiit[baud]);
 
    Opt.c_cflag |= CS8;                          //设置数据位
    Opt.c_cflag &= ~PARENB;
    Opt.c_oflag &= ~(OPOST);
    Opt.c_cflag &= ~CSTOPB;
    Opt.c_lflag &= ~(ICANON|ISIG|ECHO|IEXTEN);
    Opt.c_iflag &= ~(INPCK|BRKINT|ICRNL|ISTRIP|IXON);
 
    Opt.c_cc[VMIN] = 64;            //最大长度
    Opt.c_cc[VTIME] = 1;            //超时时间
 
    if (tcsetattr(fd,TCSANOW,&Opt) != 0)       //装载初始化参数
    {
        perror("SetupSerial!\n");
        close(fd);
        return -1;
    }
    return(fd);
 
}
 
