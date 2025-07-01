-- https://classic.runescape.wiki/w/Transcript:Jatix

function talknpc_jatix(player, npc)
	npcsay(npc, "Hello how can I help you?")
	local resp = multi(player,
		"What are you selling?",
		"You can't, I'm beyond help",
		"I'm okay, thankyou")
	if resp == 1 then
		say(player, "What are you selling?")
		openshop(player, "herblawshop")
	elseif resp == 2 then
		say(player, "You can't, I'm beyond help")
	elseif resp == 3 then
		say(player, "I'm okay, thankyou")
	end
end
