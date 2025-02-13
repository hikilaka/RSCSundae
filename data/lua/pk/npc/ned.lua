function talknpc_ned(player, npc)
	npcsay(npc, "Hello, would you like some freshly caught lobsters?")
	local resp = multi(player,
		"Yes please",
		"No thanks")
	if resp == 1 then
		say(player, "Yes please")
		give(player, "lobster", 30)
	elseif resp == 2 then
		say(player, "No thanks")
	end
end
