// HyulinServer.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Defines.h"
#include "CTCP_Server.h"

using boost::asio::ip::tcp;


int _tmain()
{
	try
	{
		boost::asio::io_service io;

		CTCP_Server server(io);
		io.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
