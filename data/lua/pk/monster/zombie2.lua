function killnpc_zombie2(player, npc, x, y)
	local ran = randomvar(128)

	local weight = 0

	if ran < 1 then
		addobject(player, "rune battle axe", 1, x, y)
	elseif ran < 10 then
		addobject(player, "bronze chain mail body", 1, x, y)
	elseif ran < 20 then
		addobject(player, "meat pizza", 1, x, y)
		addobject(player, "meat pizza", 1, x, y)
		addobject(player, "meat pizza", 1, x, y)
	elseif ran < 40 then
		addobject(player, "magic cabbage", 1, x, y)
	elseif ran < 80 then
		addobject(player, "death-rune", 5, x, y)
	else
		addobject(player, "coins", 50, x, y)
	end
end
