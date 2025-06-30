-- https://classic.runescape.wiki/w/Druid#Drops

local drops = {
	-- weapons and armour
	{ "iron dagger", 1, 6 },
	{ "druidrobetop", 1, 6 },
	{ "druidrobebottom", 1, 5 },
	{ "longbow", 1, 2 },

	-- weapons and armour
	{ "earth-rune", 18, 4 },
	{ "earth-rune", 6, 2 },
	{ "chaos-rune", 2, 2 },
	{ "fire-rune", 6, 2 },
	{ "water-rune", 6, 2 },
	{ "law-rune", 1, 1 },

	-- other
	{ "randomherb", 1, 29 },
	{ "emptyvial", 1, 10 },
	{ "limpwurt root", 1, 3 },
	{ "3doseantipoison", 1, 1 },
}

function killnpc_druid(player, npc, x, y)
	local ran = randomvar(128)

	local weight = 0

	for _, drop in ipairs(drops) do
		weight = weight + drop[3]

		if ran < weight then
			if drop[1] == "randomherb" then
				randomherb(player, x, y)
				break
			else
				addobject(player, drop[1], drop[2], x, y)
				break
			end
		end
	end
end
