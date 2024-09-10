#pragma once

#pragma once
#include <string>
#include <boost/asio.hpp>

namespace tcp {
	static std::string LOCALHOST = "127.0.0.1";

	/// @brief TcpServer class for handling reading and writing data to a socket in a server/client relationship.
	class Server {

	public:
		enum IpVersion {
			IPV4 = 0,
			IPV6 = 1
		};

		using Connection = std::shared_ptr<Server>;

		/// @brief Factory method for creating a new 'Server' object.
		static Connection Create(
			const std::string& port,
			boost::asio::io_context& ioContext,
			const IpVersion version) {
			Connection ptr = std::make_shared<Server>(port, ioContext, version);
			return ptr;
		}


		~Server();

		/// @brief Starts communication with the server.
		/// @return 0 if successful, otherwise an error code.
		int Start() const;

		/// @brief Returns the cached port number.
		const std::string& GetPort() const;

		/// @brief Returns the cached IP version.
		boost::asio::ip::tcp GetIpVersion() const;

		/// @brief Stores the version of the IP and the port.
		/// @param port Typically 13 or 1337.
		/// @param version An IP address to make the connection to.
		/// @param ioContext Reference to the IO context.
		Server(
			const std::string& port,
			boost::asio::io_context& ioContext,
			IpVersion version = IPV4);
	private:

		const std::string m_port;
		const boost::asio::ip::tcp m_ipVersion;
		boost::asio::ip::tcp::acceptor m_acceptor; // there is no default constructor for acceptor
		boost::asio::io_context& m_ioContext;
	};
}
