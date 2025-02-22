function talknpc_chaosmonk2(player, npc)
	npcsay(npc, "Praise be to Zamorak, traveller")
	local resp = multi(player,
		"Can you heal me? I'm injured",
		"Isn't something a little... off?")
	if resp == 1 then
		say(player, "Can you heal me? I'm injured")
		npcsay(npc, "Ok")
		mes(player, "The monk places his hands on your head")
		delay(3)
		mes(player, "You feel much better")
		healstat(player, STAT_ATTACK, 0, 100)
		healstat(player, STAT_DEFENSE, 0, 100)
		healstat(player, STAT_STRENGTH, 0, 100)
		healstat(player, STAT_HITS, 0, 100)
	elseif resp == 2 then
		say(player, "Isn't something a little... off?")
		npcsay(npc, "Don't be ridiculous")
		npcsay(npc, "This is an ordinary temple to our lord of chaos, Zamorak")
		npcsay(npc, "He has been worshipped in our land for centuries")
		npcsay(npc, "What are you, some kind of heretic?")
	end
end
