-- RSC 2001/replays master archive/Skilling/Magic/spell- law- telekinetic grab (basics, range tests).pcap

register_spellobj("ghostskull", "telekinetic grab", function(player, item, x, y)
	mes(player, "@que@I can't use telekinetic grab on this object")
end)

local function area_telegrab_restrict(x, y)
	-- varrock museum upstairs
	if x >= 97 and x <= 106 and y >= 1428 and y <= 1440 then
		return true
	end
	-- varrock castle upstairs empty room
	if x >= 118 and x <= 127 and y >= 1410 and y <= 1423 then
		return true
	end
	-- falador castle
	if x >= 256 and x <= 267 then
		if y >= 535 and y <= 544 then
			return true
		end
		if y >= (535 + 944) and y <= (544 + 944) then
			return true
		end
	end
	-- falador park
	if x >= 278 and x <= 303 and y >= 529 and y <= 548 then
		return true
	end

	return false
end

register_spellobj("_", "telekinetic grab", function(player, item, x, y)
	if area_telegrab_restrict(x, y) then
		mes(player, "@que@You can't cast this spell within the vicinity of the party hall")
		return
	end
	mes(player, "@que@Cast spell successfully")
	takeobject(player, item, x, y)
	advancestat(player, STAT_MAGIC, 344, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 1)
	end
	remove(player, "law-rune", 1)
	showeffect(1, x, y)
end)
