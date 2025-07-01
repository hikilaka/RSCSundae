-- https://classic.runescape.wiki/w/Transcript:Helemos

function talknpc_helemos(player, npc)
	npcsay(npc, "Welcome to the hero's guild")
	local resp = multi(player,
		"So do you sell anything here?",
		"So what can I do here?")
	if resp == 1 then
		say(player, "So do you sell anything here?")
		npcsay(npc, "Why yes we do run an exclusive shop for our members")
		openshop(player, "dragonaxeshop")
	elseif resp == 2 then
		say(player, "so what can I do here?")
		npcsay(npc, "Look around there are all sorts of things " ..
			    "to keep our members entertained")
	end
end
