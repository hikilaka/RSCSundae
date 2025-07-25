-- https://classic.runescape.wiki/w/Confuse
-- https://classic.runescape.wiki/w/Weaken
-- https://classic.runescape.wiki/w/Curse

local function remove_confuse_runes(player)
	if not has_water_staff(player) then
		remove(player, "water-rune", 3)
	end
	if not has_earth_staff(player) then
		remove(player, "earth-rune", 2)
	end
	remove(player, "body-rune", 1)
end

local function remove_curse_runes(player)
	if not has_water_staff(player) then
		remove(player, "water-rune", 2)
	end
	if not has_earth_staff(player) then
		remove(player, "earth-rune", 3)
	end
	remove(player, "body-rune", 1)
end

function skillplayer_confuse(player, target)
	if statdown(target, STAT_ATTACK) then
		mes(player, "Your opponent already has weakened attack")
	else
		mes(player, "@que@Cast spell successfully")
		advancestat(player, STAT_MAGIC, 104, 0)
		remove_confuse_runes(player)
		shootplayer(player, target, "dummybolt")
		substat(target, STAT_ATTACK, 1, 5)
		mes(target, "Your attack has been reduced by a confuse spell!")
	end
end

register_skillnpc("_", "confuse", function(player, target)
	if npcstatdown(target, STAT_ATTACK) then
		mes(player, "Your opponent already has weakened attack")
	else
		mes(player, "@que@Cast spell successfully")
		advancestat(player, STAT_MAGIC, 104, 0)
		remove_confuse_runes(player)
		shootnpc(player, target, "dummybolt")
		npcsubstat(target, STAT_ATTACK, 1, 5)
	end
end)

function skillplayer_weaken(player, target)
	if statdown(target, STAT_STRENGTH) then
		mes(player, "Your opponent already has weakened strength")
	else
		mes(player, "@que@Cast spell successfully")
		advancestat(player, STAT_MAGIC, 168, 0)
		remove_confuse_runes(player)
		shootplayer(player, target, "dummybolt")
		substat(target, STAT_STRENGTH, 1, 5)
		mes(target, "Your strength has been reduced by a weaken spell!")
	end
end

register_skillnpc("_", "weaken", function(player, target)
	if npcstatdown(target, STAT_STRENGTH) then
		mes(player, "Your opponent already has weakened strength")
	else
		mes(player, "@que@Cast spell successfully")
		advancestat(player, STAT_MAGIC, 168, 0)
		remove_confuse_runes(player)
		shootnpc(player, target, "dummybolt")
		npcsubstat(target, STAT_STRENGTH, 1, 5)
	end
end)

function skillplayer_curse(player, target)
	if statdown(target, STAT_DEFENSE) then
		mes(player, "Your opponent already has weakened defence")
	else
		mes(player, "@que@Cast spell successfully")
		advancestat(player, STAT_MAGIC, 232, 0)
		remove_curse_runes(player)
		shootplayer(player, target, "dummybolt")
		substat(target, STAT_DEFENSE, 1, 5)
		mes(target, "Your defense has been reduced by a curse spell!")
	end
end

register_skillnpc("_", "curse", function(player, target)
	if npcstatdown(target, STAT_DEFENSE) then
		mes(player, "Your opponent already has weakened defence")
	else
		mes(player, "@que@Cast spell successfully")
		advancestat(player, STAT_MAGIC, 232, 0)
		remove_curse_runes(player)
		shootnpc(player, target, "dummybolt")
		npcsubstat(target, STAT_DEFENSE, 1, 5)
	end
end)
