-- https://classic.runescape.wiki/w/Transcript:Harry
-- original was probably copy and pasted from the gerrant script

function talknpc_harry(player, npc)
	npcsay(npc, "Welcome you can buy fishing equipment at my store")
	npcsay(npc, "We'll also buy anything you catch off you")
	local resp = multi(player,
		"Let's see what you've got then",
		"Sorry, I'm not interested")
	if resp == 1 then
		say(player, "Let's see what you've got then")
		openshop(player, "fishingshop2")
	elseif resp == 2 then
		say(player, "Sorry,I'm not interested")
	end
end
