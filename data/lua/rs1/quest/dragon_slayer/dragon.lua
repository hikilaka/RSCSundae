-- https://classic.runescape.wiki/w/Dragon_(Dragon_slayer)
-- 1e_Luis/Quests/Dragon Slayer.pcap
-- Revisionism/06-16-2018 01.57.46-dragon-slayer.pcap
-- ShaunDreclin/06-08-2018 23.16.26 dragon slayer.pcap
--
-- Shaun's replay shows clearly that the player gets fire breathed
-- before each successful spell cast.

function attackbynpc_questdragon(player, npc)
	mes(player, "@que@The dragon breathes fire at you")
	if worn(player, "anti dragon breath shield") then
		mes(player, "@que@Your shield prevents some of the damage from the flames")
		substat(player, STAT_HITS, randomvar(13), 0)
	else
		mes(player, "@que@You are fried")
		substat(player, STAT_HITS, randomvar(65), 0)
	end
	-- revisionism goes from 46/46 prayer to 10/46
	-- ShaunDreclin goes from 35/42 prayer to 7/42
	-- assume 80% prayer reduction
	substat(player, STAT_PRAYER, 1, 80)
end

function killnpc_questdragon(player, npc, x, y)
	if getvar(player, "dragon_stage") == 3 then
		teleport(player, 410, 3481)
		mes(player, "Well done you have completed the dragon slayer quest")
		setvar(player, "dragon_stage", 4)
		setvar(player, "dragon_funchest", 0)
		setvar(player, "dragon_oraclechest", 0)
		giveqp(player, 2)
		advancestat(player, STAT_STRENGTH, 2600, 1200)
		advancestat(player, STAT_DEFENSE, 2600, 1200)
	end
end

register_skillnpc("questdragon", "wind strike", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile01")
	finalize_wind_strike(player)
end)

register_skillnpc("questdragon", "water strike", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile02")
	finalize_water_strike(player)
end)

register_skillnpc("questdragon", "earth strike", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile03")
	finalize_earth_strike(player)
end)

register_skillnpc("questdragon", "fire strike", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile04")
	finalize_fire_strike(player)
end)

register_skillnpc("questdragon", "wind bolt", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile05")
	finalize_wind_bolt(player)
end)

register_skillnpc("questdragon", "water bolt", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile06")
	finalize_water_bolt(player)
end)

register_skillnpc("questdragon", "earth bolt", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile07")
	finalize_earth_bolt(player)
end)

register_skillnpc("questdragon", "fire bolt", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile08")
	finalize_fire_bolt(player)
end)

register_skillnpc("questdragon", "wind blast", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile09")
	finalize_wind_blast(player)
end)

register_skillnpc("questdragon", "water blast", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile10")
	finalize_water_blast(player)
end)

register_skillnpc("questdragon", "earth blast", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile11")
	finalize_earth_blast(player)
end)

register_skillnpc("questdragon", "fire blast", function(player, target)
	attackbynpc_questdragon(player, target)
	shootnpc(player, target, "monmissile12")
	finalize_fire_blast(player)
end)
