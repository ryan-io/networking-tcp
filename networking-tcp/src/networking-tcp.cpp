#include "networking-tcp/networking-tcp.h"
#include <iostream> 
#include <stdexcept>


/// @brief Assuming the server is in a valid state (running)
///        and the port is open, this method will start the server.
/// this method will invoke io_context.run()
/// @return     0 if successful, -1 if an error occurred.
///	-2 if the server is already running.
int tcp::Server::Start() {
	if (m_isRunning) {
		std::cout << "Server is already running." << '\n';
		return -2;
	}

	std::cout << "Server is starting..." << '\n';
	m_isRunning = true;

	try {
		Run();
		// why explained here: https://www.boost.org/doc/libs/1_86_0/doc/html/boost_asio/tutorial/tutdaytime3.html
		// this should be invoked in an application entry point so it will perform asynchronous operations
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}

unsigned short tcp::Server::GetPort() const {
	return m_port;
}

boost::asio::ip::tcp tcp::Server::GetIpVersion() const {
	return m_ipVersion;
}

/// @brief Creates a new instance of 'Server'.
/// @param port Port; throw 'invalid_argument' if empty.
/// @param version Ipv4 or Ipv6.
/// @param ioContext Reference to the IO context. This class does NOT managed your reference.
tcp::Server::Server(
	const std::string& port,
	boost::asio::io_context& ioContext,
	const IpVersion version) : m_port(static_cast<unsigned short>(std::stoi(port))),
	m_ipVersion(version == IPV4
		? boost::asio::ip::tcp::v4()
		: boost::asio::ip::tcp::v6()),
	m_acceptor(boost::asio::ip::tcp::acceptor(ioContext,
		boost::asio::ip::tcp::endpoint(
			m_ipVersion,
			static_cast<unsigned short>(std::stoi(port))))),
	m_ioContext(ioContext) {
	if (port.empty()) {
		throw std::invalid_argument("Port cannot be empty - please specify.");
	}

	std::cout << "Server created - PORT: " << m_port << '\n';
	Start();	// needs to be invoked from in here -> correct pointer
}

boost::asio::io_context& tcp::Server::GetContext() const {
	return m_ioContext;
}

/// creates a connection and defines an endpoint to the server
void tcp::Server::Run() {
	using namespace boost::asio;

	auto connectionPtr = Connection::Create(m_ioContext);
	m_connections.push_back(connectionPtr);
	m_acceptor.async_accept(connectionPtr->GetSocket(),
		std::bind(&tcp::Server::Handle, this, connectionPtr, boost::asio::placeholders::error));
}

// if the server is running, stop it; early return if not
void tcp::Server::Stop() {
	if (!m_isRunning) {
		return;
	}

	std::cout << "Server is stopping..." << '\n';
	m_isRunning = false;
	m_acceptor.cancel();
	m_ioContext.stop();
	m_acceptor.close();
}

void tcp::Server::Handle(ConnectionPtr& ptr, const boost::system::error_code& error) {
	if (!error) {
		std::cout << "Writing..." << '\n';
		std::string message = "Hello from server!";
		ptr->Write();
	}

	Run();
}

void tcp::Connection::HandleWrite() {
	std::cout << "Data written to client." << '\n';
}

void tcp::Connection::Write() {
	// this is the information that is written to all clients when invoked
	std::string msg = "hello";
	boost::asio::async_write(m_socket, 
		boost::asio::buffer(msg), 
		std::bind(&tcp::Connection::HandleWrite, this));
		
}

/// @brief Default implementation
tcp::Server::~Server() {
	Stop();
}