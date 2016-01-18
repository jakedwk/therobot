#include"../src/serial.h"
#include"../src/detecting.h"
#include"../src/convey.h"


void load_data(vector<int> &data,Detect* dt)
{
    data[0] = dt->dir;
    data[1] = dt->ret.width;
    data[2] = dt->ret.height;
}



int main( int argc, char** argv )
{
    bool serial_flag = false;
    int serial_fd;
    if((serial_fd = uart_init((char*)"ttyACM0", 0)) <0)   //打开串口，波特率为115200；
    {
        printf("Open uart err \n");
        serial_flag = 1;
    }
    int sefd,new_sockfd;
    char ack = 'o';
    vector<int> data;
    vector<short int> accxyz;
    Detect dt;
    Convey conv;
    dt.detectinit(-1);
    conv.socketinit(sefd);
    cout<<sefd<<endl;
    data.resize(6);
    accxyz.resize(3);
    while(1)
    {
        cout<<"accepting!"<<endl;
        new_sockfd = conv.accept_m(sefd);
        cout<<new_sockfd<<endl;
        while(1)
        {
            dt.detecting();
            if(serial_flag)
            {
                read(serial_fd,&accxyz,4*3);
                write(serial_fd,&dt.dir,4);
                for(int i=0;i<3;i++)
                {
                    data[i+3] = accxyz[i];
                }

            }
            load_data(data,&dt);
            conv.recvall(new_sockfd,&ack,1) ;
            if(ack== 'q') break;
            conv.sendimg(new_sockfd,dt.frame);
            conv.senddata(new_sockfd,data,data.size());
        }
        close(new_sockfd);
        if(ack == 's') break;
    }
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


