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

#ifndef PARTYHANDLER_H
#define PARTYHANDLER_H

#include "Players.h"
#include "Types.h"
#include <boost/unordered_map.hpp>
#include <vector>

using boost::unordered_map;
using std::vector;
using std::string;

class Party;
class WorldServerAcceptPlayer;

#define PARTY_LEAVE 0x01
#define PARTY_JOIN 0x02
#define PARTY_SET_LEADER 0x03
#define PARTY_SILENT_UPDATE 0x04
#define PARTY_LOG_IN_OUT 0x05
#define PARTY_EXPEL 0x06

namespace PartyHandler {
	extern int32_t partyCount;
	extern unordered_map<int32_t, Party *> parties;
	void createParty(WorldServerAcceptPlayer *player, int32_t playerid);
	void leaveParty(WorldServerAcceptPlayer *player, int32_t playerid);
	void invitePlayer(WorldServerAcceptPlayer *player, int32_t playerid, const string &invitee);
	void joinParty(WorldServerAcceptPlayer *player, int32_t playerid, int32_t partyid);
	void giveLeader(WorldServerAcceptPlayer *player, int32_t playerid, int32_t target, bool is);
	void expelPlayer(WorldServerAcceptPlayer *player, int32_t playerid, int32_t target);
	void silentUpdate(int32_t playerid);
	void logInLogOut(int32_t playerid);
};

class Party {
public:
	void setId(int32_t partyid) { this->partyid = partyid; }
	void setLeader(int32_t playerid) { this->leaderid = playerid; }
	void addMember(Player *player) { this->members[player->id] = player; }
	void deleteMember(Player *player) { this->members.erase(player->id); }

	int32_t getId() const { return this->partyid; }
	int32_t getLeader() const { return this->leaderid; }
	bool isLeader(int32_t playerid) const { return playerid == leaderid; }

	unordered_map<int32_t, Player *> members;
	vector<int32_t> oldLeader;
private:
	int32_t partyid;
	int32_t leaderid;
};

#endif
