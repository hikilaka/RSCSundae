function killnpc_chaos_dwarf(player, npc, x, y)
	local ran = randomvar(128)

	local weight = 0

	if ran < 2 then
		addobject(player, "rune battle axe", 1, x, y)
	elseif ran < 4 then
		addobject(player, "rune 2-handed sword", 1, x, y)
	elseif ran < 6 then
		addobject(player, "medium rune helmet", 1, x, y)
	elseif ran < 20 then
		addobject(player, "anchovie pizza", 1, x, y)
		addobject(player, "anchovie pizza", 1, x, y)
	elseif ran < 40 then
		addobject(player, "coins", 200, x, y)
	elseif ran < 50 then
		addobject(player, "muddy key", 1, x, y)
	elseif ran < 65 then
		addobject(player, "death-rune", 40, x, y)
	else
		addobject(player, "coins", 180, x, y)
	end
end
