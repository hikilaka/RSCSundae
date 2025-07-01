-- https://classic.runescape.wiki/w/Transcript:Jakut

function talknpc_jakut(player, npc)
	npcsay(npc, "Dragon swords, get your Dragon swords")
	npcsay(npc, "Straight from the plane of frenaskrae")
	local resp = multi(player,
		"Yes please",
		"No thankyou, I'm just browsing the marketplace")
	if resp == 1 then
		say(player, "Yes Please")
		openshop(player, "dragonswordshop")
	elseif resp == 2 then
		say(player, "No thankyou, I'm just browsing the marketplace")
	end
end
