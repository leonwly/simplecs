﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Net.NetworkInformation;
using System.Runtime.InteropServices;//for StructLayoutAttribute
namespace winClient2
{
    [StructLayoutAttribute(LayoutKind.Sequential,CharSet=CharSet.Ansi,Pack=1)]
    public class  Test {
        public int first;
        public int second;
    }
    class Program
    {
        private static byte[] result = new byte[1024];
      
        static void Main(string[] args)
        {
            IPAddress ip = IPAddress.Parse("182.254.233.115");
            Random rd=new Random();
            int mPort = 9201;
            Socket clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        
            try
            {  
                clientSocket.Connect(new IPEndPoint(ip, mPort)); //配置服务器IP与端口
                //clientSocket.Connect(new IPEndPoint(ip,9201)); //配置服务器IP与端口
                Console.WriteLine("连接服务器成功");
            }
            catch
            {
                Console.WriteLine("连接服务器失败，请按回车键退出！");
                //return;
            }

            Test tst=new Test();
            tst.first=9;
            tst.second=13;
            int counts = 0;
            int MAXTIME = 3;
            byte[] msg = Transform.StructToBytes(tst);
            while (counts < MAXTIME)
            {
                Thread.Sleep(2000);
                try
                {
                    //string sendMessage = " hello guang server ,I come in at  " + DateTime.Now + "  with times:" + counts;
                    clientSocket.Send(msg);
                    Console.WriteLine("send success at " + counts);
                }
                catch (Exception e)
                {
                    Console.WriteLine("At times " + counts + "  send error!" + e.Message);
                    break;
                    
                }
                try
                {
                    byte[] result=new byte[1024];
                    int receiveLength = clientSocket.Receive(result);
                    Type type=typeof(Test);
                    Test rr = (Test)Transform.BytesToStruct(result,type);
                    Console.WriteLine("接收服务器消息：result.first={0},result.second={1}",rr.first,rr.second );
                }
                catch {
                    Console.WriteLine("接收失败!");
                    break;
                }
                counts++;
            }
            Console.ReadKey();
        }
        
    }
}
