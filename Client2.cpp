#ifdef WIN32
#define _WIN_WINNT 0x0501
#include<stdio.h>
#endif
#include"Client2.h"
using boost::asio::ip::tcp;
using namespace boost::asio;
using namespace std;
io_service service;
vector <string> vec;
ip::tcp::socket sock(service);//创建socket
ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 1000);//创建要链接的嵌套字
typedef boost::system::error_code error_code;

void connect()
{
	sock.connect(ep);//连接
}

void write(float a, float b)//发送数据
{
	char write_message[50];
	chat_message msg;
	sprintf_s(write_message, "1%.2f %.2f", a, b);
	msg.body_length(strlen(write_message));
	memcpy(msg.body(), write_message, msg.body_length());
	msg.encode_header();
	sock.send(buffer(msg.data(), msg.length()));//同步发送数据
}

void write(float a, float b, float c, float d)
{
	char write_message[50];
	chat_message msg;
	sprintf_s(write_message, "2%.2f %.2f %.2f %.2f", a, b, c, d);
	msg.body_length(strlen(write_message));
	memcpy(msg.body(), write_message, msg.body_length());
	msg.encode_header();
	sock.send(buffer(msg.data(), msg.length()));//同步发送数据
}

void write(char ch[12], float a, float b)
{
	char write_message[50];
	chat_message msg;
	sprintf_s(write_message, "3%s %.2f %.2f", ch, a, b);
	msg.body_length(strlen(write_message));
	memcpy(msg.body(), write_message, msg.body_length());
	msg.encode_header();
	sock.send(buffer(msg.data(), msg.length()));//同步发送数据
}

void read()//读取数据
{
	while (true)
	{
		float a, b,c ,d;
		chat_message read_message;
		char ch_[1];cocos2d::log("0");
		read(sock, buffer(read_message.data(), 2));
		read_message.decode_header();
		read(sock, buffer(ch_, 1)); cocos2d::log("1");
		if (ch_[0] == '1')
		{
			
			read(sock, buffer(read_message.body(), read_message.body_length() - 1));
			sscanf_s(read_message.body(), "%f %f", &a, &b);
			cocos2d::log("2");
			a1 = a; b1 = b;
			cocos2d::log("%f %f", &a, &b);
		}
		else if (ch_[0] == '2')
		{
			
			read(sock, buffer(read_message.body(), read_message.body_length() - 1));
			sscanf_s(read_message.body(), "%f %f %f %f", &a, &b, &c, &d);
			a1 = a; b1 = b; a2 = c; b2 = d;
			
		}
		else if (ch_[0] == '3')
		{
			
			
			read(sock, buffer(read_message.body(), read_message.body_length() - 1));
			sscanf_s(read_message.body(), "%s %f %f", s_message, sizeof(s_message), &a, &b);
			a1 = a; b1 = b;
		}
		else;
		cocos2d::log("final");
	}
}

void thread__()
{
	boost::thread t(read);
}