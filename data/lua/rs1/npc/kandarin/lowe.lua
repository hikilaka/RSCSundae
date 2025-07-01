-- https://classic.runescape.wiki/w/Transcript:Hickton
-- original was probably copy and pasted from the lowe script

function talknpc_hickton(player, npc)
	npcsay(npc, "Welcome to Hickton's Archery Store")
	npcsay(npc, "Do you want to see my wares?")
	local resp = multi(player,
		"Yes please",
		"No, I prefer to bash things close up")
	if resp == 1 then
		say(player, "Yes Please")
		openshop(player, "archeryshop2")
	elseif resp == 2 then
		say(player, "No, I prefer to bash things close up")
	end
end
