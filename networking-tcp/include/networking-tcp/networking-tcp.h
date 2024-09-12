#pragma once

#pragma once
#include <string>
#include <boost/asio.hpp>

namespace tcp {
	static std::string LOCALHOST = "127.0.0.1";
	// if multiple clients connect to the server, we need to keep track of them
	class Connection;
	using ConnectionPtr = std::shared_ptr<Connection>;


	/// @brief TcpServer class for handling reading and writing data to a socket in a server/client relationship.
	class Server {
	public:
		enum IpVersion {
			IPV4 = 0,
			IPV6 = 1
		};

		using TcpServer = std::unique_ptr<Server>;

		/// @brief Factory method for creating a new 'Server' object.
		static TcpServer Create(
			boost::asio::io_context& ioContext,
			const std::string& port,
			const IpVersion version) {
			TcpServer ptr = std::make_unique<Server>(port, ioContext, version);

			return ptr;
		}

		~Server();

		/// @brief Starts communication with the server.
		/// @return 0 if successful, otherwise an error code.
		int Start();

		/// @brief Returns the cached port number.
		unsigned short GetPort() const;

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

		friend class Connection;
	private:
		boost::asio::io_context& GetContext() const;
		void Run();
		void Stop();
		void Handle(ConnectionPtr&, const boost::system::error_code&);

		bool m_isRunning = false;
		const unsigned short m_port;
		const boost::asio::ip::tcp m_ipVersion;
		boost::asio::ip::tcp::acceptor m_acceptor; // listens for new connections
		boost::asio::io_context& m_ioContext;
		std::vector<tcp::ConnectionPtr> m_connections{};
	};

	class Connection : public std::enable_shared_from_this<Connection> {
	public:
		// creates a new 'Connection' object wrt io_context from an instance of 'Server'
		static ConnectionPtr Create(boost::asio::io_context& ctx) {
			ConnectionPtr ptr = std::shared_ptr<Connection>(new Connection(ctx));
			return ptr;
		}

		boost::asio::ip::tcp::socket& GetSocket() {
			return  m_socket;
		}

		void Write();
		void HandleWrite();

		~Connection() = default;

	private:
		Connection(boost::asio::io_context& ctx) : m_socket(ctx) {}
		boost::asio::ip::tcp::socket m_socket;
	};
}
