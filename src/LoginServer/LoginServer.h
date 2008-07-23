/*
Copyright (C) 2008 Vana Development Team

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
#ifndef LOGINSERVER_H
#define LOGINSERVER_H

#include "AbstractServer.h"
#include "InitializeLogin.h"
#include "Config.h"
#include "PlayerLogin.h"
#include "LoginServerAcceptPlayer.h"

// LoginServer main application class, implemented as singleton
class LoginServer : public AbstractServer {
public:
	static LoginServer * Instance() {
		if (singleton == 0)
			singleton = new LoginServer;
		return singleton;
	}
	void loadData();
	void loadConfig();
	void listen();
	void shutdown();

	bool getPinEnabled() const { return pinEnabled; }
	void setPinEnabled(bool enabled) { pinEnabled = enabled; }
	int getInvalidLoginThreshold() const { return invalid_login_threshold; }
private:
	LoginServer() {};
	LoginServer(const LoginServer&);
	LoginServer& operator=(const LoginServer&);
	static LoginServer *singleton;

	bool pinEnabled;
	short port;
	short inter_port;
	int invalid_login_threshold;
};

#endif
