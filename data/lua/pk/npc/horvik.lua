function talknpc_horvik_the_armourer(player, npc)
	npcsay(npc, "Take a look at some of my protective equipment")
	npcsay(npc, "You'll need it out in the deep wilderness")
	local resp = multi(player, "Yes please", "No thanks")
	if resp == 1 then
		say(player, "Yes please")
		openshop(player, "armourshop")
	elseif resp == 2 then
		say(player, "No thanks")
	end
end
