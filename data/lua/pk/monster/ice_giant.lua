function killnpc_ice_giant(player, npc, x, y)
	local ran = randomvar(128)

	local weight = 0

	if ran < 2 then
		addobject(player, "rune 2-handed sword", 1, x, y)
	elseif ran < 4 then
		addobject(player, "large rune helmet", 1, x, y)
	elseif ran < 6 then
		addobject(player, "rune kite shield", 1, x, y)
	elseif ran < 8 then
		addobject(player, "rune chain mail body", 1, x, y)
	elseif ran < 20 then
		addobject(player, "anchovie pizza", 1, x, y)
		addobject(player, "anchovie pizza", 1, x, y)
		addobject(player, "anchovie pizza", 1, x, y)
	elseif ran < 30 then
		addobject(player, "death-rune", 40, x, y)
	elseif ran < 40 then
		addobject(player, "swordfish", 1, x, y)
		addobject(player, "swordfish", 1, x, y)
		addobject(player, "swordfish", 1, x, y)
	elseif ran < 55 then
		addobject(player, "magic cabbage", 1, x, y)
		addobject(player, "magic cabbage", 1, x, y)
	elseif ran < 60 then
		addobject(player, "coins", 750, x, y)
	elseif ran < 80 then
		addobject(player, "coins", 500, x, y)
	else
		addobject(player, "coins", 250, x, y)
	end
end
