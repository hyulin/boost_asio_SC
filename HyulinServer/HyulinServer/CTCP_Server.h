#pragma once

#include "stdafx.h"
#include "Defines.h"
#include "CConnection.h"

using boost::asio::ip::tcp;


class CTCP_Server
{
private:
	tcp::acceptor m_Acceptor;
	int m_nAcceptCnt;

private:
	void WaitAccept();
	void handle_Accept(CConnection::pointer new_connection, const boost::system::error_code& error);

public:
	CTCP_Server(boost::asio::io_service& io);
};
