-- https://classic.runescape.wiki/w/Transcript:Thordur

local function thordur_cost(player, npc)
	npcbusy(npc)
	say(player, "Yes please")
	npcsay(npc, "Ok it will cost you 10 gold coins")
	npcsay(npc, "For which you get to enter the hole")
	npcsay(npc, "And get a magic disk which lets you escape again")
	npcunbusy(npc)
	local resp = multi(player,
	    "Yes that sounds good",
	    "Oh I'm not paying money for it")
	if resp == 1 then
		npcbusy(npc)
		say(player, "Yes that sounds good")
		if held(player, "coins", 10) then
			mes(player, "You pay the dwarf ten coins and get given a disk")
			remove(player, "coins", 10)
			give(player, "disk of returning", 1)
			npcsay(npc, "Ok you may climb down the ladder to the black hole")
			npcsay(npc, "Have fun")
		else
			-- XXX assumed from similar interactions
			say(player, "Oh dear. I don't seem to have enough money")
		end
		npcunbusy(npc)
	elseif resp == 2 then
		say(player, "I'm not paying money for it")
	end
end

local function thordur_describe(player, npc)
	npcbusy(npc)
	say(player, "What's the black hole experience?")
	npcsay(npc, "Experience the mind numbing boredom")
	npcsay(npc, "As experienced by runescape's criminals and rulebreakers")
	npcsay(npc, "But with the comfort of being able to leave at any time")
	npcunbusy(npc)
	local resp = multi(player,
	    "Yes please",
	    "No thanks, I don't enjoy Mind numbing boredom")
	if resp == 1 then
		thordur_cost(player, npc)
	elseif resp == 2 then
		npcbusy(npc)
		say(player, "No thanks")
		say(player, "I don't enjoy mind numbing boredom")
		npcsay(npc, "Me neither")
		npcsay(npc, "I'm not well suited for this job")
		npcunbusy(npc)
	end
end

local function thordur_nothanks(player, npc)
	say(player, "No Thankyou")
end

function talknpc_thordur(player, npc)
	npcsay(npc, "Would you like to go on the black hole experience")
	local resp = multi(player,
	    "Yes please",
	    "No Thankyou",
	    "What's the black hole experience?")
	if resp == 1 then
		thordur_cost(player, npc)
	elseif resp == 2 then
		thordur_nothanks(player, npc)
	elseif resp == 3 then
		thordur_describe(player, npc)
	end
end

function oploc1_holeladder(player, x, y)
	if not held(player, "disk of returning", 1) then
		local npc = nearnpc(player, "thordur")
		if npc then
			npcbusy(npc)
			npcsay(npc, "Hey careful that's the ladder to the black hole experience")
			npcsay(npc, "You don't want to go down there unprepared")
			npcsay(npc, "So do you want to experience it?")
			npcunbusy(npc)
			local resp = multi(player,
			    "Yes please",
			    "No Thankyou",
			    "What's the black hole experience?")
			if resp == 1 then
				thordur_cost(player, npc)
			elseif resp == 2 then
				thordur_nothanks(player, npc)
			elseif resp == 3 then
				thordur_describe(player, npc)
			end
		end
	else
		-- XXX basically random coordinates
		-- don't know the real ones
		teleport(player, 300, 2600)
	end
end
