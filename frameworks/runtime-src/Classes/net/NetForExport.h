#ifndef __Boids_Net_for_Export_h_
#define __Boids_Net_for_Export_h_

#include <string>

//��Ӧ��ʵ����Net.cpp��

class Net
{
public:
	static void initialize(std::string server_ip, int server_port);

	static std::string getUserId();
};

#endif