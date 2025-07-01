-- https://classic.runescape.wiki/w/Transcript:Gaius

function talknpc_gaius(player, npc)
	npcsay(npc, "Welcome to my two handed sword shop")
	local resp = multi(player, "Let's trade", "thankyou")
	if resp == 1 then
		say(player, "Let's trade")
		openshop(player, "2handedshop")
	elseif resp == 2 then
		say(player, "Thankyou")
	end
end
