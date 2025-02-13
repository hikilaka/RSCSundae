function talknpc_gaius(player, npc)
	npcsay(npc, "In times like these, you don't want to travel far")
	npcsay(npc, "Without a weapon by your side")
	local resp = multi(player,
		"Let's have a look then",
		"I'm already armed enough, thanks")
	if resp == 1 then
		say(player, "Let's have a look then")
		openshop(player, "2handedshop")
	elseif resp == 2 then
		say(player, "I'm already armed enough, thanks")
		npcsay(npc, "Suit yourself")
	end
end
