-- https://classic.runescape.wiki/w/Transcript:Irksol

function talknpc_irksol(player, npc)
	npcsay(npc, "selling ruby rings")
	npcsay(npc, "The best deals in all the planes of existance")
	local resp = multi(player,
		"I'm interested in these deals",
		"No thankyou")
	if resp == 1 then
		say(player, "I'm interested in these deals")
		npcsay(npc, "Take a look at these beauties")
		openshop(player, "cheapringshop")
	elseif resp == 2 then
		say(player, "no thankyou")
	end
end
