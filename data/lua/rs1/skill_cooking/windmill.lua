-- rsc-preservation.xyz/Quests/cooks-assistant.pcap
-- ./Logg/Tylerbeg/08-01-2018 19.32.34 varrock pt2.pcap

local function use_hopper(player, varname)
	local hopper_grain = getvar(player, varname)
	if hopper_grain > 0 then
		mes(player, "@que@There is already grain in the hopper")
	else
		thinkbubble(player, "grain")
		remove(player, "grain", 1)
		mes(player, "@que@You put the grain in the hopper")
		setvar(player, varname, 1)
	end
end

local function operate_hopper(player, varname, x, y)
	local hopper_grain = getvar(player, varname)
	mes(player, "@que@You operate the hopper")
	if hopper_grain > 0 then
		mes(player, "@que@The grain slides down the chute")
		addobject(player, "flourheap", 1, x, y)
		setvar(player, varname, 0)
	else
		mes(player, "@que@Nothing interesting happens")
	end
end

function takeobj_flourheap(player, x, y)
	-- RSC 2001/replays master archive/Item info/Alphabetical/P/itemspawn-pot of flour (chute)- attempt to pick up without pot.pcap
	mes(player, "@que@I can't pick it up!")
	mes(player, "@que@I need a pot to hold it in")
end

register_useobj("flourheap", "pot", function(player, x, y)
	delobject(player, "flourheap", x, y)
	mes(player, "@que@You put the flour in the pot")
	remove(player, "pot", 1)
	give(player, "flourpot", 1)
end)

register_useloc("hopper1", "grain", function(player, x, y)
	use_hopper(player, "hopper_grain")
end)

function oploc1_hopper1(player)
	operate_hopper(player, "hopper_grain", 166, 599)
end

register_useloc("hopper2", "grain", function(player, x, y)
	use_hopper(player, "hopper2_grain")
end)

function oploc1_hopper2(player)
	operate_hopper(player, "hopper2_grain", 179, 481)
end
