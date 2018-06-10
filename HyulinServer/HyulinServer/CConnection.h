#pragma once

#include "stdafx.h"
#include "Defines.h"

using boost::asio::ip::tcp;


class CConnection : public boost::enable_shared_from_this<CConnection>
{
private:
	enum EEnum
	{
		eBuffSize = 128,
	};

	tcp::socket m_Socket;
	int m_nID;

	boost::array<BYTE, eBuffSize> m_RecvBuf;
	std::string m_sMessage;

public:
	CConnection(boost::asio::io_service& io) : m_Socket(io), m_nID(-1) {}
	~CConnection() {}

private:
	void handle_Accept(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);
	void handle_Wait_Recv(const boost::system::error_code& error, size_t /*bytes_transferred*/);
	void handle_Send(const boost::system::error_code& error, size_t /*bytes_transferred*/);

public:
	typedef boost::shared_ptr<CConnection> pointer;

	static pointer create(boost::asio::io_service& io)
	{
		return pointer(new CConnection(io));
	}

	tcp::socket& socket()
	{
		return m_Socket;
	}

	void start(int nID);
};
