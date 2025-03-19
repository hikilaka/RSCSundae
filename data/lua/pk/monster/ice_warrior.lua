function killnpc_ice_warrior(player, npc, x, y)
	local ran = randomvar(128)

	local weight = 0

	if ran < 2 then
		addobject(player, "rune plate mail legs", 1, x, y)
	elseif ran < 4 then
		addobject(player, "rune skirt", 1, x, y)
	elseif ran < 6 then
		addobject(player, "rune plate mail body", 1, x, y)
	elseif ran < 20 then
		addobject(player, "anchovie pizza", 1, x, y)
		addobject(player, "swordfish", 1, x, y)
	elseif ran < 30 then
		addobject(player, "death-rune", 12, x, y)
	elseif ran < 40 then
		addobject(player, "swordfish", 1, x, y)
	elseif ran < 50 then
		addobject(player, "coins", 200, x, y)
	elseif ran < 60 then
		addobject(player, "black mace", 1, x, y)
	elseif ran < 62 then
		addobject(player, "rune mace", 1, x, y)
	elseif ran < 80 then
		addobject(player, "death-rune", 8, x, y)
	else
		addobject(player, "coins", 275, x, y)
	end
end
