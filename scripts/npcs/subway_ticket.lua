--[[
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
--]]
-- Jake, sells tickets for Kerning Jump Quests

addText("You must purchase the ticket to enter. Once you have made the purchase, you can enter through The Ticket Gate on the right. What would you like to buy?");
addText("\r\n#b#L0#construction site B1#l");
addText("\r\n#L1#construction site B2#l");
addText("\r\n#L2#construction site B3#l#k");
choice = askChoice();

if choice == 0 then
	addText("Will you purchase the ticket to #bconstruction site B1#k? It'll cost you 500 mesos. Before making the purchase, please make sure you have an empty slot on your etc. inventory.");
elseif choice == 1 then
	addText("Will you purchase the ticket to #bconstruction site B2#k? It'll cost you 1200 mesos. Before making the purchase, please make sure you have an empty slot on your etc. inventory.");
elseif choice == 2 then
	addText("Will you purchase the ticket to #bconstruction site B3#k? It'll cost you 2000 mesos. Before making the purchase, please make sure you have an empty slot on your etc. inventory.");
else
	return;
end

yes = askYesNo();

if yes == 1 then
	item = 0;
	text = "You can insert the ticket in the The Ticket Gate. I heard ";

	if choice == 0 and giveMesos(-500) then
		item = 4031036;
		text = text .. "Area 1";
	elseif choice == 1 and giveMesos(-1200) then
		item = 4031037;
		text = text .. "Area 2";
	elseif choice == 2 and giveMesos(-2000) then
		item = 4031038;
		text = text .. "Area 3";
	end

	if item == 0 then
		addText("Are you lacking mesos? Check and see if you have an empty slot on your etc. inventory or not.");
	else
		text = text .. " has some precious items available but with so many traps all over the place most come back out early. Wishing you the best of luck.";
		giveItem(item, 1);
		addText(text);
	end
else
	addText("You can enter the premise once you have bought the ticket. I heard there are strange devices in there everywhere but in the end, rare precious items await you. So let me know if you ever decide to change your mind.");
end

sendOK();