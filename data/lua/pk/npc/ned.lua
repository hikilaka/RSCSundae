function talknpc_ned(player, npc)
	npcsay(npc, "Hello, would you like some freshly caught lobsters?")
	local resp = multi(player,
		"Yes please",
		"No thanks")
	if resp == 1 then
		say(player, "Yes please")
		give(player, "lobster", 30)
		if male(player) then
			npcsay(npc, "Here you go lad")
		else
			npcsay(npc, "Here you go lass")
		end
		say(player, "Thanks Ned")
	elseif resp == 2 then
		say(player, "No thanks")
	end
end
