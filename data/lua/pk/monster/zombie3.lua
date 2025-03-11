function killnpc_zombie3(player, npc, x, y)
	local ran = randomvar(128)

	local weight = 0

	if ran < 1 then
		addobject(player, "rune battle axe", 1, x, y)
	elseif ran < 10 then
		addobject(player, "bronze medium helmet", 1, x, y)
	elseif ran < 20 then
		addobject(player, "anchovie pizza", 1, x, y)
	elseif ran < 30 then
		addobject(player, "knife", 1, x, y)
	elseif ran < 35 then
		addobject(player, "arrows", 50, x, y)
	elseif ran < 45 then
		addobject(player, "chaos-rune", 50, x, y)
	elseif ran < 90 then
		addobject(player, "death-rune", 7, x, y)
	else
		addobject(player, "coins", 100, x, y)
	end
end
