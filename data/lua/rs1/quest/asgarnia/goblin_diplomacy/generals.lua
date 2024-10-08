-- https://classic.runescape.wiki/w/Transcript:General_Bentnoza
-- https://classic.runescape.wiki/w/Transcript:General_wartface
-- Revisionism/06-15-2018 04.23.22 goblin diplomacy.pcap

-- this is a bit messy because of the frequent switching
-- furthermore there's evidence that bentnoze doesn't stay
-- busy the entire time...

local function generals_argue(player)
	local wartface
	local bentnoze

	wartface = nearnpc(player, "general wartface")
	npcbusy(wartface)
	npcsay(wartface, "green armour best")
	npcunbusy(wartface)

	bentnoze = nearnpc(player, "general bentnoze")
	npcbusy(bentnoze)
	npcsay(bentnoze, "No no Red every time")
	npcunbusy(bentnoze)

	wartface = nearnpc(player, "general wartface")
	npcbusy(wartface)
	npcsay(wartface, "go away human, we busy")
	npcunbusy(wartface)
end

local function generals_talk(player, npc, is_wartface)
	local wartface
	local bentnoze

	npcunbusy(npc)

	wartface = nearnpc(player, "general wartface")

	if is_wartface and getvar(player, "dragon_stage") == 2 then
		npcbusy(wartface)
		-- defined in ../../dragon_slayer/wartface.lua
		if wartface_wormbrain(player, wartface) then
			npcunbusy(wartface)
			return
		end
		npcunbusy(wartface)
	end

	local stage = getvar(player, "goblin_stage")

	if stage == 0 then
		generals_argue(player)
	elseif stage == 1 then
		generals_argue(player)
		local resp = multi(player,
			"Why are you arguing about the colour of your armour?",
			"Wouldn't you prefer peace?",
			"Do you want me to pick an armour colour for you?")
		if resp == 1 then
			wartface = nearnpc(player, "general wartface")
			npcbusy(wartface)
			say(player, "Why are you arguing about the colour of your armour?")
			npcsay(wartface, "We decide to celebrate goblin new century")
			npcsay(wartface, "By changing the colour of our armour")
			npcsay(wartface, "Light blue get boring after a bit")
			npcsay(wartface, "And we want change")
			npcsay(wartface, "Problem is they want different change to us")
			npcunbusy(wartface)
		elseif resp == 2 then
			wartface = nearnpc(player, "general wartface")
			npcbusy(wartface)
			say(player, "Wouldn't you prefer peace?")
			npcsay(wartface, "Yeah peace is good as long as it is peace wearing Green armour")
			npcunbusy(wartface)

			bentnoze = nearnpc(player, "general bentnoze")
			npcbusy(bentnoze)
			npcsay(bentnoze, "But green to much like skin!")
			npcsay(bentnoze, "Nearly make you look naked!")
			npcunbusy(bentnoze)
		elseif resp == 3 then
			wartface = nearnpc(player, "general wartface")
			npcbusy(wartface)
			say(player, "Do you want me to pick an armour colour for you?")
			say(player, "different to either green or red")
			npcsay(wartface, "Hmm me dunno what that'd look like")
			npcsay(wartface, "You'd have to bring me some, so us could decide")
			npcunbusy(wartface)

			bentnoze = nearnpc(player, "general bentnoze")
			npcbusy(bentnoze)
			npcsay(bentnoze, "Yep bring us orange armour")
			npcunbusy(bentnoze)

			wartface = nearnpc(player, "general wartface")
			npcbusy(wartface)
			npcsay(wartface, "Yep orange might be good")
			setvar(player, "goblin_stage", 2)
			npcunbusy(wartface)
		end
	elseif stage == 2 then
		generals_argue(player)

		wartface = nearnpc(player, "general wartface")
		npcbusy(wartface)
		npcsay(wartface, "Oh it you")

		if held(player, "orange goblin armour", 1) then
			say(player, "I have some orange armour")
			mes(player, "You give some goblin armour to the goblins")
			delay(3)
			remove(player, "orange goblin armour", 1)

			npcsay(wartface, "No I don't like that much")
			npcunbusy(wartface)

			bentnoze = nearnpc(player, "general wartface")
			npcbusy(bentnoze)
			npcsay(bentnoze, "It clashes with my skin colour")
			npcunbusy(bentnoze)

			wartface = nearnpc(player, "general wartface")
			npcbusy(wartface)
			npcsay(wartface, "Try bringing us dark blue armour")
			setvar(player, "goblin_stage", 3)
			npcunbusy(wartface)
		else
			npcsay(wartface, "Have you got some orange goblin armour yet?")
			say(player, "Err no")
			npcsay(wartface, "Come back when you have some")
			npcunbusy(wartface)
		end
	elseif stage == 3 then
		if held(player, "dark blue goblin armour", 1) then
			generals_argue(player)

			wartface = nearnpc(player, "general wartface")
			npcbusy(wartface)

			say(player, "I have some dark blue armour")
			mes(player, "You give some goblin armour to the goblins")
			delay(3)
			remove(player, "dark blue goblin armour", 1)

			npcsay(wartface, "Doesn't seem quite right")
			npcunbusy(wartface)

			bentnoze = nearnpc(player, "general bentnoze")
			npcbusy(bentnoze)
			npcsay(bentnoze, "maybe if it was a bit lighter")
			npcunbusy(bentnoze)

			wartface = nearnpc(player, "general wartface")
			npcbusy(wartface)
			npcsay(wartface, "Yeah try light blue")
			npcunbusy(wartface)

			say(player, "I thought that was the armour you were changing from")
			say(player, "But never mind, anything is worth a try")
			setvar(player, "goblin_stage", 4)
		else
			wartface = nearnpc(player, "general wartface")
			npcbusy(wartface)
			npcsay(wartface, "Have you got some Dark Blue goblin armour yet?")
			say(player, "Err no")
			npcsay(wartface, "Come back when you have some")
			npcunbusy(wartface)
		end
	elseif stage == 4 then
		if held(player, "light blue goblin armour", 1) then
			say(player, "Ok I've got light blue armour")
			mes(player, "You give some goblin armour to the goblins")
			remove(player, "light blue goblin armour", 1)

			wartface = nearnpc(player, "general wartface")
			npcbusy(wartface)
			npcsay(wartface, "That is rather nice")
			npcunbusy(wartface)

			bentnoze = nearnpc(player, "general bentnoze")
			npcbusy(bentnoze)
			npcsay(bentnoze, "Yes I could see myself wearing somethin' like that")
			npcunbusy(bentnoze)

			wartface = nearnpc(player, "general wartface")
			npcbusy(wartface)
			npcsay(wartface, "It' a deal then")
			npcsay(wartface, "Light blue it is")
			npcsay(wartface, "Thank you for sorting our argument")
			npcunbusy(wartface)

			mes(player, "Well done you have completed the goblin diplomacy quest")
			setvar(player, "goblin_stage", 5)
			giveqp(player, 5)
			advancestat(player, STAT_CRAFTING, 500, 60)
			mes(player, "general wartface gives you a gold bar as thanks")
			give(player, "gold bar", 1)
		else
			wartface = nearnpc(player, "general wartface")
			npcbusy(wartface)
			npcsay(wartface, "Have you got some Light Blue goblin armour yet?")
			say(player, "Err no")
			npcsay(wartface, "Come back when you have some")
			npcunbusy(wartface)
		end
	elseif stage == 5 then
		wartface = nearnpc(player, "general wartface")
		npcbusy(wartface)
		npcsay(wartface, "Now you've solved our argument we gotta think of something else to do")
		npcunbusy(wartface)

		bentnoze = nearnpc(player, "general bentnoze")
		npcbusy(bentnoze)
		npcsay(bentnoze, "Yep, we bored now")
		npcunbusy(bentnoze)
	end
end

function talknpc_general_wartface(player, npc)
	generals_talk(player, npc, true)
end

function talknpc_general_bentnoze(player, npc)
	generals_talk(player, npc, false)
end
