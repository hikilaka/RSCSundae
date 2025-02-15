function oploc1_levera(player, x, y)
	mes(player, "Choose a teleport location")
	local resp = multi(player,
		"Chaos temple (level-10)",
		"Graveyard (level-20)",
		"Hobgoblin mine (level-30)",
		"Ice plateau (level-45)",
		"I'll stay where I am")
	if resp == 1 then
		teleport(player, 116, 364)
		showeffect(0, 166, 363)
	elseif resp == 2 then
		teleport(player, 160, 312)
		showeffect(0, 160, 311)
	elseif resp == 3 then
		teleport(player, 237, 247)
		showeffect(0, 237, 246)
	elseif resp == 4 then
		teleport(player, 320, 163)
		showeffect(0, 320, 162)
	end
end
