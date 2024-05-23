#include <iostream>
#include "SimpleSerial.h"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;


char com_port[] = "\\\\.\\COM5";
//DWORD COM_BAUD_RATE = CBR_250000;
SimpleSerial Serial(com_port, CBR_256000);

int reply_wait_time = 1;
string syntax_type = "greater_less_than";



float *extractIntegerWords(string str)
{
    stringstream ss;
    /* Storing the whole string into string stream */
    ss << str;
    /* Running loop till the end of the stream */
    string temp;
    float found;
    int i =0;
    static float array[18];

    while (!ss.eof())
    {
        /* extracting word by word from stream */
        ss >> temp;
        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found)
        {
            //cout << found << " ";
            array[i] = found;
            i++;
        }
        /* To save from space at the end of string */
        temp = ",";

    }
    return array;
}




float *num;
const int t_time = 500;

std::vector<float> arr_time(t_time);
std::vector<float> arr_accx(t_time);
std::vector<float> arr_accy(t_time);
std::vector<float> arr_accz(t_time);
ofstream outfile;

float tim, roll, pitch, yaw, accx, accy, accz, gyrox, gyroy, gyroz, magx, magy, magz, calibStat, q0, q1, q2, q3;


int main()
{
    cout << "Hello world!" << endl;
    outfile.open("D:/IMU/get_imu_data_cppt/result.csv");

    outfile << " Time" << "," << "Roll"  << ","<< "Pitch"  << ","<< "Yaw"  << ","<<"accx"  << ","<<"accy"  << ","<<"accz"  << ","<<"gyrox"  << ","<<"gyroy"  << ","<<"gyroz"  << ","<<"magx"  << ","<<"magy"  << ","<<"magz"  << ","<<"Calb Status"<<std::endl;

    for (int i=0; i<=t_time; i++)
    {
i--;
        string incoming = Serial.ReadSerialPort(reply_wait_time, syntax_type);
        //std::cout << incoming << std::endl;
        num=extractIntegerWords(incoming);


        tim = num[0];
        roll=num[1];
        pitch=num[2];
        yaw=num[3];
        accx=num[4];
        accy=num[5];
        accz=num[6];
        gyrox=num[7];
        gyroy=num[8];
        gyroz=num[9];
        magx=num[10];
        magy=num[11];
        magz=num[12];
        calibStat=num[13];
        q0=num[14];
        q1=num[15];
        q2=num[16];
        q3=num[17];


/*        for (int i=0; i<=12; i++)
        {
            printf("num %f ", num[i]);
        }
        printf("num %f \n ", num[13]);

*/
        arr_accx[i]=accx;
        arr_accy[i]=accy;
        arr_accz[i]=accz;
        arr_time[i]=i;



        std::cout << " roll = " << roll <<  " pitch = " << pitch <<"  yaw = "  <<  yaw <<"  Calib = " << calibStat<< std::endl;


        // saving data in .csv file
        for(int j=0; j<=13; j++)
        {
            outfile << num[j] << ", ";
        }
        outfile << endl;


    }
    outfile.close();


    std::vector<double> x = {1, 2, 3, 4};
    std::vector<double> y = {1, 4, 9, 16};

//   dot([1,2,3],[2,3,4]);
    printf("sz_time = %d", arr_time.size());
    printf("sz_accx = %d", arr_accx.size());
    printf("sz_accx = %d", arr_accy.size());
    printf("sz_accx = %d", arr_accz.size());


plt::plot(arr_accx);
plt::show();



    return 0;
}
