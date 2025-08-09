function spellnpc_crumble_undead(player, target)
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

register_spellnpc("skeleton", "crumble undead", spellnpc_crumble_undead)
register_spellnpc("zombie", "crumble undead", spellnpc_crumble_undead)
register_spellnpc("ghost", "crumble undead", spellnpc_crumble_undead)
register_spellnpc("_", "crumble undead", function(player, target)
	-- ./rscplus-replays-master/kRiStOf/Salarin The Twisted
	mes(player, "@que@This spell can only be used on skeletons, zombies and ghosts")
end)
