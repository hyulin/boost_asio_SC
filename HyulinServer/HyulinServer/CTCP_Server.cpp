#include "stdafx.h"
#include "CTCP_Server.h"


void CTCP_Server::WaitAccept()
{
	++m_nAcceptCnt;
	CConnection::pointer new_connection =
		CConnection::create(m_Acceptor.get_io_service());

	m_Acceptor.async_accept(new_connection->socket(),
		boost::bind(&CTCP_Server::handle_Accept, this, new_connection,
			boost::asio::placeholders::error));
}

void CTCP_Server::handle_Accept(CConnection::pointer new_connection, const boost::system::error_code & error)
{
	if (!error)
	{
		new_connection->start(m_nAcceptCnt);
		WaitAccept();
	}
}

CTCP_Server::CTCP_Server(boost::asio::io_service & io) : m_Acceptor(io, tcp::endpoint(tcp::v4(), 13)), m_nAcceptCnt(0)
{
	WaitAccept();
}
