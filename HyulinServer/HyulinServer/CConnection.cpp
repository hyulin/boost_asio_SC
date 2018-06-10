#include "stdafx.h"
#include "CConnection.h"


// ��¥�ð� �޼����� �����. 
std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime; 
	time_t now = time(0);
	return ctime(&now); // ctime_s ����. �����ϱ� �׳� ���� �Ѿ���� 
}

void CConnection::handle_Accept(const boost::system::error_code &, size_t)
{
}

void CConnection::handle_Wait_Recv(const boost::system::error_code & error, size_t)
{
	if (!error)  // 0 �� ���� �������� ���� �÷��� 
	{
		std::cout << "Waiting..." << std::endl;
		m_Socket.async_read_some(boost::asio::buffer(m_RecvBuf),
			boost::bind(&CConnection::handle_Send, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
	else
		std::cout << m_nID << " Disconnect(Read) : " << error.message() << std::endl;
}

void CConnection::handle_Send(const boost::system::error_code & error, size_t)
{
	if (!error)  // 0 �� ���� �������� ���� �÷��� 
	{
		// ��ó�� �� 
		if (m_RecvBuf.size())
		{
			std::cout << "Recv : " << (*(char*)(m_RecvBuf.data())) << std::endl;
			m_RecvBuf.assign(NULL); // ���� �ʱ�ȭ 
		}

		if (true)    // ������ ������ ������ 
		{
			boost::asio::async_write(m_Socket, boost::asio::buffer("handle_read", 32),
				boost::bind(&CConnection::handle_Wait_Recv, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
			std::cout << "Send " << std::endl;
		}
		else        // ������ ���� 
		{
			boost::array<BYTE, eBuffSize> buf;
			m_Socket.async_read_some(boost::asio::buffer(buf),
				boost::bind(&CConnection::handle_Send, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		}
	}
	else
		std::cout << m_nID << " Disconnect(Write) : " << error.message() << std::endl;
}

void CConnection::start(int nID)
{
	std::cout << "new connect id : " << nID << " ::: Welcome !" << std::endl;
	m_nID = nID;
	m_sMessage = make_daytime_string();

	boost::asio::async_write(m_Socket, boost::asio::buffer(m_sMessage),
		boost::bind(&CConnection::handle_Accept, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	boost::array<BYTE, eBuffSize> buf;
	m_Socket.async_receive(boost::asio::buffer(buf),
		boost::bind(&CConnection::handle_Send, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}
