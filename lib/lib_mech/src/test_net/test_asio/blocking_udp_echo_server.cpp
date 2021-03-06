#include "stdafx.h"
//
// blocking_udp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

using boost::asio::ip::udp;


static void run_server(boost::asio::io_service& io_service, short port)
{
	udp::socket sock(io_service, udp::endpoint(udp::v4(), port));
	for (;;)
	{
		char data[iMAX_LENGTH];
		udp::endpoint sender_endpoint;
		size_t length = sock.receive_from(
			boost::asio::buffer(data, iMAX_LENGTH), sender_endpoint);
		sock.send_to(boost::asio::buffer(data, length), sender_endpoint);
	}
}

int main_blocking_udp_echo_server(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: blocking_udp_echo_server <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		using namespace std; // For atoi.
		run_server(io_service, atoi(argv[1]));
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
