// PLCConsole.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream> //标准的输入输出流头文件
#include <conio.h> //控制台输入输出头文件
#include <windows.h> //windowsAPI的函数声明和宏
#include "TcAdsDef.h" //结构体和常量的声明
#include "TcAdsAPI.h" // ADS函数的声明

# include <conio.h>
# include <stdio.h>

#include <time.h>

using namespace std;

using namespace std;
void delay(int sec) //编写定时器
{
    time_t start_time, cur_time; //变量声明
    time(&start_time);
    do
    {
        time(&cur_time);
    } while ((cur_time - start_time) < sec);
}



int main()
{

        long nErr, nPort; //定义端口变量
        AmsAddr Addr; //定义AMS地址变量
        PAmsAddr pAddr = &Addr; //定义端口地址变量
        bool BOOL1; //定义布尔量
        short INT1;//定义整型
        float FLOAT1;//定义浮点数

        //字符串
        unsigned long lHdlVar; //创建句柄
        char String[] = { "MAIN.String1" }; //定义字符串
        char szVar[] = { "MAIN.String1" };

        //数组
        unsigned long lHdlVar2; //创建句柄
        int nIndex; //定义循环变量
        short Array[10]; //定义数组
        char szVar2[] = { "MAIN.Array1" };

        //结构体
        struct PlcVarstruct //定义结构体
        {
            float floatVal; //浮点型
            INT32 intVal; //整型
            bool boolVal; //布尔型
        }PlcVar;
        
        nPort = AdsPortOpen(); //打开ADS通讯端口
        nErr = AdsGetLocalAddress(pAddr); //得到本地端口地址
        if (nErr) std::cerr << "Error: AdsGetLocalAddress: " << nErr << '\n'; //检查获取地址的操作是否执行成功
        pAddr->port = 851; //将指针指向851端口

        do
        {
            //READ
            //向PLC中读取BOOL量
            nErr = AdsSyncReadReq(pAddr, 0x4020, 0x0, 0x1, &BOOL1); //从ADS服务器同步读取数据，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，@BOOL1:接收数据的缓存
            if (nErr) std::cerr << "Error: AdsSyncReadReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
            cout << BOOL1 << '\n'; //输出”BOOL1”的值

            //从PLC中读取整型量
            nErr = AdsSyncReadReq(pAddr, 0x4020, 0x2, 0x4, &INT1);
            if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
            cout << INT1 << '\n'; //输出INT1的值

            //从PLC中读取浮点数
            nErr = AdsSyncReadReq(pAddr, 0x4020, 0x6, 0x4, &FLOAT1);
            if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
            cout << FLOAT1 << '\n';

            //通过句柄读取字符串
            nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x10, sizeof(lHdlVar), &lHdlVar, sizeof(szVar), szVar); // 同步写数据到ADS服务器并从ADS设备接收数据，pAddr：ADS设备的地址 0x0：偏移地址 sizeof(lHdlVar)：由ADS设备返回的句柄大小 &lHdlVar：由ADS设备返回的数据缓存 sizeof(szVar)：写入ADS设备的数据大小 szVar：写入ADS设备的数据缓存
            if (nErr) cerr << "Error: AdsSyncReadWriteReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
            nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(String), &String); //从ADS服务器同步读取数据
            if (nErr)
                cerr << "Error: AdsSyncReadReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
            else
                cout << "String:" << String << '\n'; //若正确，则输出String的值

            nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar2), &lHdlVar2, sizeof(szVar2), szVar2);
            if (nErr) cerr << "Error: AdsSyncReadWriteReq: " << nErr << '\n';
            nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar2, sizeof(Array), &Array[0]);
            if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
            else
            {
                for (nIndex = 0; nIndex < 10; nIndex++) //用for循环语句来实现读取数组中的元素
                    cout << "Array[" << nIndex << "]: " << Array[nIndex] << '\n';
            }

            //从PLC中读取结构体
            nErr = AdsSyncReadReq(pAddr, 0x4020, 0xa, 0x4, &PlcVar.intVal);
            if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
            cout << PlcVar.intVal << '\n';
            nErr = AdsSyncReadReq(pAddr, 0x4020, 0xe, 0x4, &PlcVar.floatVal);
            if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
            cout << PlcVar.floatVal << '\n';
            nErr = AdsSyncReadReq(pAddr, 0x4020, 0x12, 0x1, &PlcVar.boolVal);
            if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
            cout << PlcVar.boolVal << '\n';

            

            //WRITE
            //向PLC写入BOOL:
            cout << "BOOL:";
            cin >> BOOL1; //为BOOL1赋值
            nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x0, 0x1, &BOOL1); //同步写数据到ADS设备，pAddr：ADS设备的地址，0x4020：段地址，0x0偏移地址，0x1：数据长度，@BOOL1:接收数据的缓存
            if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功

           
            //向PLC写入整型量
            cout << "INT:";
            cin >> INT1;
            nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x2, 0x4, &INT1);
            if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';

            //向PLC写入浮点数
            cout << "FLOAT:";
            cin >> FLOAT1;
            nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x6, 0x4, &FLOAT1);
            if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';


            //向PLC写入字符串
            cout << "STRING:"; //输出STRING:
            cin >> String; //为String赋值
            nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x10, sizeof(lHdlVar), &lHdlVar, sizeof(szVar), szVar);
            if (nErr) cerr << "Error: AdsSyncReadWriteReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功
            nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(String), &String); //同步写数据到ADS设备
            if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n'; //检查获取地址的操作是否执行成功



            for (nIndex = 0; nIndex < 10; nIndex++) //通过for循环语句来实现为数组赋值
            {
                cout << "Array[" << nIndex << "]:";
                cin >> Array[nIndex];
            }
            //得到Array1的句柄
            nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar2), &lHdlVar2, sizeof(szVar2), szVar2);
            if (nErr) cerr << "Error: AdsSyncReadWriteReq: " << nErr << '\n';
            //通过句柄向PLC写入数组
            nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar2, sizeof(Array), &Array[0]);
            if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';

            //向PLC写入结构体
            cout << "PlcVar.intVal:";
            cin >> PlcVar.intVal;
            nErr = AdsSyncWriteReq(pAddr, 0x4020, 0xa, 0x4, &PlcVar.intVal);
            if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
            cout << "PlcVar.floatVal:";
            cin >> PlcVar.floatVal;
            nErr = AdsSyncWriteReq(pAddr, 0x4020, 0xe, 0x4, &PlcVar.floatVal);
            if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
            cout << "PlcVar.boolVal:";
            cin >> PlcVar.boolVal;
            nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x12, 0x1, &PlcVar.boolVal);
            if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
            cout << '\n';
            delay(5);
        }while (1);
        //while (_getch() == '\r'); //用do-while语句来实现循环读取

        nErr = AdsPortClose(); //关闭ADS通讯端口
        if (nErr) std::cerr << "Error: AdsPortClose: " << nErr << '\n'; //检查关闭通讯端口的操作是否执行成功



        return 1;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
