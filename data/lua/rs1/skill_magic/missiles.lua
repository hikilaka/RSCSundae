-- 07-11-2018 16.12.51 autocast magic on some guards for 2 hours.pcap

function finalize_wind_strike(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 88, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 1)
	end
	remove(player, "mind-rune", 1)
end

function finalize_water_strike(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 120, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 1)
	end
	if nothas_water_staff(player) then
		remove(player, "water-rune", 1)
	end
	remove(player, "mind-rune", 1)
end

function finalize_earth_strike(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 152, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 1)
	end
	if not has_earth_staff(player) then
		remove(player, "earth-rune", 2)
	end
	remove(player, "mind-rune", 1)
end

function finalize_fire_strike(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 184, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 2)
	end
	if not has_fire_staff(player) then
		remove(player, "fire-rune", 3)
	end
	remove(player, "mind-rune", 1)
end

function finalize_wind_bolt(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 216, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 2)
	end
	remove(player, "chaos-rune", 1)
end

function finalize_water_bolt(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 264, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 2)
	end
	if nothas_water_staff(player) then
		remove(player, "water-rune", 2)
	end
	remove(player, "chaos-rune", 1)
end

function finalize_earth_bolt(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 312, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 2)
	end
	if not has_earth_staff(player) then
		remove(player, "earth-rune", 3)
	end
	remove(player, "chaos-rune", 1)
end

function finalize_fire_bolt(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 360, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 3)
	end
	if not has_fire_staff(player) then
		remove(player, "fire-rune", 4)
	end
	remove(player, "chaos-rune", 1)
end

function finalize_wind_blast(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 408, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 3)
	end
	remove(player, "death-rune", 1)
end

function finalize_water_blast(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 456, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 3)
	end
	if nothas_water_staff(player) then
		remove(player, "water-rune", 3)
	end
	remove(player, "death-rune", 1)
end

function finalize_earth_blast(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 504, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 3)
	end
	if not has_earth_staff(player) then
		remove(player, "earth-rune", 4)
	end
	remove(player, "death-rune", 1)
end

function finalize_fire_blast(player)
	mes(player, "@que@Cast spell successfully")
	advancestat(player, STAT_MAGIC, 552, 0)
	if not has_air_staff(player) then
		remove(player, "air-rune", 4)
	end
	if not has_fire_staff(player) then
		remove(player, "fire-rune", 5)
	end
	remove(player, "death-rune", 1)
end

function spellplayer_wind_strike(player, target)
	shootplayer(player, target, "missile01")
	finalize_wind_strike(player)
end

register_spellnpc("_", "wind strike", function(player, target)
	shootnpc(player, target, "monmissile01")
	finalize_wind_strike(player)
end)

function spellplayer_water_strike(player, target)
	shootplayer(player, target, "missile02")
	finalize_water_strike(player)
end

register_spellnpc("_", "water strike", function(player, target)
	shootnpc(player, target, "monmissile02")
	finalize_water_strike(player)
end)

function spellplayer_earth_strike(player, target)
	shootplayer(player, target, "missile03")
	finalize_earth_strike(player)
end

register_spellnpc("_", "earth strike", function(player, target)
	shootnpc(player, target, "monmissile03")
	finalize_earth_strike(player)
end)

function spellplayer_fire_strike(player, target)
	shootplayer(player, target, "missile04")
	finalize_fire_strike(player)
end

register_spellnpc("_", "fire strike", function(player, target)
	shootnpc(player, target, "monmissile04")
	finalize_fire_strike(player)
end)

function spellplayer_wind_bolt(player, target)
	shootplayer(player, target, "missile05")
	finalize_wind_bolt(player)
end

register_spellnpc("_", "wind bolt", function(player, target)
	shootnpc(player, target, "monmissile05")
	finalize_wind_bolt(player)
end)

function spellplayer_water_bolt(player, target)
	shootplayer(player, target, "missile06")
	finalize_water_bolt(player)
end

register_spellnpc("_", "water bolt", function(player, target)
	shootnpc(player, target, "monmissile06")
	finalize_water_bolt(player)
end)

function spellplayer_earth_bolt(player, target)
	shootplayer(player, target, "missile07")
	finalize_earth_bolt(player)
end

register_spellnpc("_", "earth bolt", function(player, target)
	shootnpc(player, target, "monmissile07")
	finalize_earth_bolt(player)
end)

function spellplayer_fire_bolt(player, target)
	shootplayer(player, target, "missile08")
	finalize_fire_bolt(player)
end

register_spellnpc("_", "fire bolt", function(player, target)
	shootnpc(player, target, "monmissile08")
	finalize_fire_bolt(player)
end)

function spellplayer_wind_blast(player, target)
	shootplayer(player, target, "missile09")
	finalize_wind_blast(player)
end

register_spellnpc("_", "wind blast", function(player, target)
	shootnpc(player, target, "monmissile09")
	finalize_wind_blast(player)
end)

function spellplayer_water_blast(player, target)
	shootplayer(player, target, "missile10")
	finalize_water_blast(player)
end

register_spellnpc("_", "water blast", function(player, target)
	shootnpc(player, target, "monmissile10")
	finalize_water_blast(player)
end)

function spellplayer_earth_blast(player, target)
	shootplayer(player, target, "missile11")
	finalize_earth_blast(player)
end

register_spellnpc("_", "earth blast", function(player, target)
	shootnpc(player, target, "monmissile11")
	finalize_earth_blast(player)
end)

function spellplayer_fire_blast(player, target)
	shootplayer(player, target, "missile12")
	finalize_fire_blast(player)
end

register_spellnpc("_", "fire blast", function(player, target)
	shootnpc(player, target, "monmissile12")
	finalize_fire_blast(player)
end)
