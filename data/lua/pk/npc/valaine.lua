local function valaine_done(player, npc)
	npcsay(npc, "Ok, it's done. I can change your other levels too")
	valaine_menu(player, npc)
end

local function valaine_change_magic(player, npc, stat)
	npcsay(npc, "What would you like your magic level changed to?")
	local resp = multi(player,
		"Change it to Level 1 please",
		"Change it to Level 17 please",
		"Change it to Level 45 please",
		"Change it to Level 70 please",
		"Leave it as-is please")

	if resp == 1 then
		say(player, "Change it to Level 1 please")
		advancestat(player, STAT_MAGIC, 0, 0)
		valaine_done(player, npc) 
	elseif resp == 2 then
		say(player, "Change it to Level 17 please")
		advancestat(player, STAT_MAGIC, 12460, 0)
		valaine_done(player, npc)
	elseif resp == 3 then
		say(player, "Change it to Level 45 please")
		advancestat(player, STAT_MAGIC, 246048, 0)
		valaine_done(player, npc)
	elseif resp == 4 then
		say(player, "Change it to Level 70 please")
		advancestat(player, STAT_MAGIC, 2950508, 0)
		valaine_done(player, npc)
	elseif resp == 4 then
		say(player, "Leave it as-is please")
		npcsay(npc, "Ok fine")
	end
end

local function valaine_change_prayer(player, npc, stat)
	npcsay(npc, "What would you like your prayer level changed to?")
	local resp = multi(player,
		"Change it to Level 1 please",
		"Change it to Level 16 please",
		"Change it to Level 34 please",
		"Change it to Level 40 please",
		"Leave it as-is please")

	if resp == 1 then
		say(player, "Change it to Level 1 please")
		advancestat(player, STAT_PRAYER, 0, 0)
		valaine_done(player, npc) 
	elseif resp == 2 then
		say(player, "Change it to Level 16 please")
		advancestat(player, STAT_PRAYER, 10984, 0)
		valaine_done(player, npc)
	elseif resp == 3 then
		say(player, "Change it to Level 34 please")
		advancestat(player, STAT_PRAYER, 80896, 0)
		valaine_done(player, npc)
	elseif resp == 4 then
		say(player, "Change it to Level 40 please")
		advancestat(player, STAT_PRAYER, 148896, 0)
		valaine_done(player, npc)
	elseif resp == 4 then
		say(player, "Leave it as-is please")
		npcsay(npc, "Ok fine")
	end
end

local function valaine_change(player, npc, stat)
	npcsay(npc, "What would you like it changed to?")
	local resp = multi(player,
		"Change it to Level 1 please",
		"Change it to Level 10 please",
		"Change it to Level 20 please",
		"Change it to Level 30 please",
		"More...")

	if resp == 1 then
		say(player, "Change it to Level 1 please")
		advancestat(player, stat, 0, 0)
		valaine_done(player, npc)
		return
	elseif resp == 2 then
		say(player, "Change it to Level 10 please")
		advancestat(player, stat, 4616, 0)
		valaine_done(player, npc)
		return
	elseif resp == 3 then
		say(player, "Change it to Level 20 please")
		advancestat(player, stat, 17880, 0)
		valaine_done(player, npc)
		return
	elseif resp == 4 then
		say(player, "Change it to Level 30 please")
		advancestat(player, stat, 53452, 0)
		valaine_done(player, npc)
		return
	end

	resp = multi(player,
		"Change it to Level 40 please",
		"Change it to Level 50 please",
		"Change it to Level 60 please",
		"Change it to Level 70 please",
		"More...")
	if resp == 1 then
		say(player, "Change it to Level 40 please")
		advancestat(player, stat, 148896, 0)
		valaine_done(player, npc)
		return
	elseif resp == 2 then
		say(player, "Change it to Level 50 please")
		advancestat(player, stat, 405332, 0)
		valaine_done(player, npc)
		return
	elseif resp == 3 then
		say(player, "Change it to Level 60 please")
		advancestat(player, stat, 1094968, 0)
		valaine_done(player, npc)
		return
	elseif resp == 4 then
		say(player, "Change it to Level 70 please")
		advancestat(player, stat, 2950508, 0)
		valaine_done(player, npc)
		return
	end

	resp = multi(player,
		"Change it to Level 80 please",
		"Change it to Level 90 please",
		"Change it to Level 99 please",
		"Leave it as-is please")
	if resp == 1 then
		say(player, "Change it to Level 80 please")
		advancestat(player, stat, 7944272, 0)
		valaine_done(player, npc)
		return
	elseif resp == 2 then
		say(player, "Change it to Level 90 please")
		advancestat(player, stat, 21385328, 0)
		valaine_done(player, npc)
		return
	elseif resp == 3 then
		say(player, "Change it to Level 99 please")
		advancestat(player, stat, 52137724, 0)
		valaine_done(player, npc)
		return
	elseif resp == 4 then
		say(player, "Leave it as-is please")
		npcsay(npc, "Ok fine")
	end
end

local function valaine_others(player, npc)
	local resp = multi(player,
		"Change my ranged level please",
		"Change my magic level please",
		"Change my prayer level please",
		"Never mind I'll come back later")
	if resp == 1 then
		say(player, "Change my ranged level please")
		valaine_change(player, npc, STAT_RANGED)
	elseif resp == 2 then
		say(player, "Change my magic level please")
		valaine_change_magic(player, npc)
	elseif resp == 3 then
		say(player, "Change my prayer level please")
		valaine_change_prayer(player, npc)
	elseif resp == 4 then
		say(player, "Never mind I'll come back later")
		npcsay(npc, "See you soon")
	end
end

function valaine_menu(player, npc)
	local resp = multi(player,
		"Change my attack level please",
		"Change my defense level please",
		"Change my strength level please",
		"Change my other levels please",
		"Ok thanks I'll come back later")
	if resp == 1 then
		say(player, "Change my attack level please")
		valaine_change(player, npc, STAT_ATTACK)
	elseif resp == 2 then
		say(player, "Change my defense level please")
		valaine_change(player, npc, STAT_DEFENSE)
	elseif resp == 3 then
		say(player, "Change my strength level please")
		valaine_change(player, npc, STAT_STRENGTH)
	elseif resp == 4 then
		valaine_others(player, npc)
	elseif resp == 5 then
		say(player, "Ok thanks I'll come back later")
		npcsay(npc, "Good luck with your travels")
	end
end

function talknpc_valaine(player, npc)
	npcsay(npc, "Hello I can change your combat stats")
	npcsay(npc, "So that you might fight foes of similar experience")
	valaine_menu(player, npc)
end
