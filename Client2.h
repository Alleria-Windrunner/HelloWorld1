
#include <string>
#include <vector>
#include <iostream>  
#include <boost/bind.hpp>  
#include <boost/asio.hpp>  
#include <boost/shared_ptr.hpp>  
#include <boost/thread.hpp>  
#include <boost/enable_shared_from_this.hpp>
#include "chat.hpp"
#include "cocos2d.h"
void connect();
void write(float a, float b);//·¢ËÍÊý¾Ý
void write(float a, float b, float c, float d);
void write(char ch[12], float a, float b);
void read();
void thread__();