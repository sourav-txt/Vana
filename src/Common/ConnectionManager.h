/*
Copyright (C) 2008-2012 Vana Development Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#pragma once

#include "ConnectionAcceptor.h"
#include "noncopyable.hpp"
#include "SessionManager.h"
#include "Types.h"
#include <list>
#include <memory>
#include <string>
#include <thread>

using std::string;

class AbstractConnectionFactory;
class ConnectionAcceptor;

class ConnectionManager : private boost::noncopyable {
public:
	static ConnectionManager * Instance() {
		if (singleton == nullptr)
			singleton = new ConnectionManager;
		return singleton;
	}

	void accept(port_t port, AbstractConnectionFactory *acf, const LoginConfig &loginConfig, bool isServer, const string &patchLocation = "");
	void connect(ip_t serverIp, port_t serverPort, const LoginConfig &loginConfig, AbstractConnection *connection);
	void stop();

	void run();
	void join();
private:
	void handleRun();
	void handleStop();

	ConnectionManager();
	static ConnectionManager *singleton;

	std::unique_ptr<std::thread> m_thread;
	boost::asio::io_service m_ioService;
	SessionManagerPtr m_clients;
	std::list<ConnectionAcceptorPtr> m_servers;
	std::unique_ptr<boost::asio::io_service::work> m_work; // "Work" for io_service
};