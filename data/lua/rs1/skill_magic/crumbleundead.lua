function skillnpc_crumble_undead(player, target)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 392, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 2)
	end
	if not has_earth_staff(player) then
		remove(player, "earth-rune", 2)
	end
	remove(player, "chaos-rune", 1)
	shootnpc(player, target, "monmissile12")
end

register_skillnpc("skeleton", "crumble undead", skillnpc_crumble_undead)
register_skillnpc("zombie", "crumble undead", skillnpc_crumble_undead)
register_skillnpc("ghost", "crumble undead", skillnpc_crumble_undead)
register_skillnpc("_", "crumble undead", function(player, target)
	-- ./rscplus-replays-master/kRiStOf/Salarin The Twisted
	mes(player, "@que@This spell can only be used on skeletons, zombies and ghosts")
end)
