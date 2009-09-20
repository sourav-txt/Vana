/*
Copyright (C) 2008-2009 Vana Development Team

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
#include "PacketReader.h"
#include "Pos.h"

PacketReader::PacketReader() : m_length(0), m_pos(0) { }
PacketReader::PacketReader(unsigned char *buffer, size_t length) : m_buffer(buffer), m_length(length), m_pos(0) { }

void PacketReader::skipBytes(int32_t len) {
	m_pos += len;
}

int16_t PacketReader::getHeader() {
	return (*(int16_t *)(m_buffer));
}

string PacketReader::getString() {
	return getString(get<int16_t>());
}

string PacketReader::getString(size_t len) {
	string s((char *) m_buffer + m_pos, len);
	m_pos += len;
	return s;
}

unsigned char * PacketReader::getBuffer() {
	return m_buffer + m_pos;
}

size_t PacketReader::getBufferLength() {
	return m_length - m_pos;
}

PacketReader & PacketReader::reset(int32_t len) {
	if (len >= 0) {
		m_pos = len;
	}
	else {
		m_pos = m_length + len; // In this case, len is negative here so we take the total length and plus (minus) it by len
	}

	return *this;
}

Pos PacketReader::getPos() {
	Pos ret;
	ret.x = get<int16_t>();
	ret.y = get<int16_t>();
	return ret;
}

bool PacketReader::getBool() {
	return (get<int8_t>() != 0);
}