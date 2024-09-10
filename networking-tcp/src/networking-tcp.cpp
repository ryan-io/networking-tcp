#include "networking-tcp/networking-tcp.h"
#include <stdexcept>
#include <iostream>

/// @brief Assuming the server is in a valid state (running)
//        and the port is open, this method will start the server.
/// @return     0 if successful, -1 if an error occurred.
int tcp::Server::Start() const
{
	try
	{
		m_ioContext.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}

const std::string& tcp::Server::GetPort() const
{
	return m_port;
}

boost::asio::ip::tcp tcp::Server::GetIpVersion() const
{
	return m_ipVersion;
}

/// @brief Creates a new instance of 'Server'.
/// @param port Port; throw 'invalid_argument' if empty.
/// @param version Ipv4 or Ipv6.
/// @param ioContext Reference to the IO context. This class does NOT managed your reference.
tcp::Server::Server(
	const std::string& port,
	boost::asio::io_context &ioContext,
	const IpVersion version) : m_port(port),
							   m_ipVersion(version == IpVersion::IPV4
											   ? boost::asio::ip::tcp::v4()
											   : boost::asio::ip::tcp::v6()),
							   m_acceptor(boost::asio::ip::tcp::acceptor(ioContext,
																		 boost::asio::ip::tcp::endpoint(m_ipVersion,
																			 std::stoi(port)))),
							   m_ioContext(ioContext)
{
	if (port.empty())
	{
		throw std::invalid_argument("Port cannot be empty - please specify.");
	}
}

/// @brief Default implementation
tcp::Server::~Server() = default;