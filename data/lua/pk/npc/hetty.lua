local function hetty_go(player, npc)
	say(player, "I have to go now")
	npcsay(npc, "Fare thee well")
end

local function hetty_shop(player, npc)
	say(player, "Show me your instruments of the dark arts")
	openshop(player, "magicshop")
end

local function hetty_tower(player, npc)
	say(player, "What are you doing in this tower?")
	npcsay(npc, "Well, I used to live in this little village called Rimmington")
	npcsay(npc, "Not much going on there though")
	npcsay(npc, "I thought my talents could be put to better use on the frontier")
	npcsay(npc, "And the tower means nobody's out of sight")
	mes(player, "Hetty cackles ominously")
	delay(1)
	local resp = multi(player,
		"Show me your instruments of the dark arts",
		"I have to go now")
	if resp == 1 then
		hetty_shop(player, npc)
	elseif resp == 2 then
		hetty_go(player, npc)
	end
end

function talknpc_hetty(player, npc)
	npcsay(npc, "Greetings Traveller")
	npcsay(npc, "Are you here for my dark magical artefacts?")
	local resp = multi(player,
		"Show me your instruments of the dark arts",
		"What are you doing in this tower?",
		"I have to go now")
	if resp == 1 then
		hetty_shop(player, npc)
	elseif resp == 2 then
		hetty_tower(player, npc)
	elseif resp == 3 then
		hetty_go(player, npc)
	end
end
