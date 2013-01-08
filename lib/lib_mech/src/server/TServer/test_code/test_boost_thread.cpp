#include <stdafx.h>
// Copyright (C) 2001-2003
// William E. Kempf
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>
#include <boost/utility.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>
#include <conio.h>

class bounded_buffer : private boost::noncopyable
{
public:
	typedef boost::mutex::scoped_lock lock;

	bounded_buffer(int n) : begin(0), end(0), buffered(0), circular_buf(n) { }

	void send (int m) {
		lock lk(monitor);
		while (buffered == circular_buf.size())
			buffer_not_full.wait(lk);
		circular_buf[end] = m;
		end = (end+1) % circular_buf.size();
		++buffered;
		buffer_not_empty.notify_one();
	}
	int receive() {
		lock lk(monitor);
		while (buffered == 0)
			buffer_not_empty.wait(lk);
		int i = circular_buf[begin];
		begin = (begin+1) % circular_buf.size();
		--buffered;
		buffer_not_full.notify_one();
		return i;
	}

private:
	int begin, end, buffered;
	std::vector<int> circular_buf;
	boost::condition buffer_not_full, buffer_not_empty;
	boost::mutex monitor;
};

bounded_buffer buf(2);

boost::mutex io_mutex;

void sender() {
	int n = 0;
	while (n < 100000) {
		buf.send(n);
		{
			boost::mutex::scoped_lock io_lock(io_mutex);
			//std::cout << "sent: " << n << std::endl;
		}
		++n;
	}
	buf.send(-1);
}

void receiver() {
	int n;
	do {
		n = buf.receive();
		{
			boost::mutex::scoped_lock io_lock(io_mutex);
			std::cout << "received: " << n << std::endl;
		}
	} while (n != -1); // -1 indicates end of buffer
}

boost::thread_group threads;
std::vector<boost::thread*>ts;
void get_key()
{
	_getch();
	{
		printf("threads.interrupt_all();");
		for(int i=0;i<ts.size();++i)
			threads.remove_thread(ts[i]);
		printf("threads.interrupt_all();");
	}

}
int main(int, char*[])
{
	ts.push_back(threads.create_thread(&sender));
	ts.push_back(threads.create_thread(&receiver));
	ts.push_back(threads.create_thread(&get_key));
	threads.join_all();
	//char ch = _getch();
	return 0;
}

