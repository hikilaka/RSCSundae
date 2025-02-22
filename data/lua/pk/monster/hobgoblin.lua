function killnpc_hobgoblin(player, npc, x, y)
	local ran = randomvar(128)

	local weight = 0

	if ran < 1 then
		addobject(player, "rune battle axe", 1, x, y)
	elseif ran < 2 then
		addobject(player, "medium rune helmet", 1, x, y)
	elseif ran < 15 then
		addobject(player, "anchovie pizza", 1, x, y)
		addobject(player, "meat pizza", 1, x, y)
		addobject(player, "meat pizza", 1, x, y)
	elseif ran < 19 then
		addobject(player, "knife", 1, x, y)
	elseif ran < 25 then
		addobject(player, "coins", 150, x, y)
	elseif ran < 50 then
		addobject(player, "death-rune", 9, x, y)
	elseif ran < 60 then
		addobject(player, "magic cabbage", 1, x, y)
	elseif ran < 70 then
		addobject(player, "crossbow bolts", 50, x, y)
	else
		addobject(player, "coins", 120, x, y)
	end
end
