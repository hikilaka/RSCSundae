-- stitched together from too many different replays, including
-- Logg/Tylerbeg/08-02-2018 02.12.01 white knight castle and dwarven mine
-- Logg/Tylerbeg/08-04-2018 00.10.40 zanaris.pcap
-- RSC 2001/replays master archive/Skilling/Smithing/5-admantite/smithing- smith- adamantite plate mail chest.pcap
-- flying sno (redacted chat) replays/fsnom2@aol.com/06-24-2018 06.45.51.pcap
-- 1e_Luis/Skilling/Rune smithing table reqs complete.pcap

local forging_table = {
	["bronze bar"] = {
		["dagger"] = {
			level = 1, name = "bronze dagger"
		},
		["hatchet"] = {
			level = 1, name = "bronze axe"
		},
		["mace"] = {
			level = 2, name = "bronze mace"
		},
		["medium helmet"] = {
			level = 3, name = "medium bronze helmet"
		},
		["short sword"] = {
			level = 4, name = "bronze short sword"
		},
		["scimitar"] = {
			level = 5, name = "bronze scimitar"
		},
		["long sword"] = {
			level = 6, name = "bronze long sword"
		},
		["large helmet"] = {
			level = 7, name = "large bronze helmet"
		},
		["square shield"] = {
			level = 8, name = "bronze square shield"
		},
		["battle axe"] = {
			level = 10, name = "bronze battle axe"
		},
		["chain mail body"] = {
			level = 11, name = "bronze chain mail body"
		},
		["kite shield"] = {
			level = 12, name = "bronze kite shield"
		},
		["2-handed sword"] = {
			level = 14, name = "bronze 2-handed sword"
		},
		["plated skirt"] = {
			level = 16, name = "bronze plated skirt"
		},
		["plate mail legs"] = {
			level = 16, name = "bronze plate mail legs"
		},
		["plate mail body"] = {
			level = 18, name = "bronze plate mail body"
		},
	},
	["iron bar"] = {
		["dagger"] = {
			level = 15, name = "iron dagger"
		},
		["hatchet"] = {
			level = 16, name = "iron axe"
		},
		["mace"] = {
			level = 17, name = "iron mace"
		},
		["medium helmet"] = {
			level = 18, name = "medium iron helmet"
		},
		["short sword"] = {
			level = 19, name = "iron short sword"
		},
		["scimitar"] = {
			level = 20, name = "iron scimitar"
		},
		["long sword"] = {
			level = 21, name = "iron long sword"
		},
		["large helmet"] = {
			level = 22, name = "large iron helmet"
		},
		["square shield"] = {
			level = 23, name = "iron square shield"
		},
		["battle axe"] = {
			level = 25, name = "iron battle axe"
		},
		["chain mail body"] = {
			level = 26, name = "iron chain mail body"
		},
		["kite shield"] = {
			level = 27, name = "iron kite shield"
		},
		["2-handed sword"] = {
			level = 29, name = "iron 2-handed sword"
		},
		["plated skirt"] = {
			level = 31, name = "iron plated skirt"
		},
		["plate mail legs"] = {
			level = 31, name = "iron plate mail legs"
		},
		["plate mail body"] = {
			level = 33, name = "iron plate mail body"
		},
	},
	["steel bar"] = {
		["dagger"] = {
			level = 30, name = "steel dagger"
		},
		["hatchet"] = {
			level = 31, name = "steel axe"
		},
		["mace"] = {
			level = 32, name = "steel mace"
		},
		["medium helmet"] = {
			level = 33, name = "medium steel helmet"
		},
		["short sword"] = {
			level = 34, name = "steel short sword"
		},
		["nails"] = {
			level = 34, name = "nails"
		},
		["scimitar"] = {
			level = 35, name = "steel scimitar"
		},
		["long sword"] = {
			level = 36, name = "steel long sword"
		},
		["large helmet"] = {
			level = 37, name = "large steel helmet"
		},
		["square shield"] = {
			level = 38, name = "steel square shield"
		},
		["battle axe"] = {
			level = 40, name = "steel battle axe"
		},
		["chain mail body"] = {
			level = 41, name = "steel chain mail body"
		},
		["kite shield"] = {
			level = 42, name = "steel kite shield"
		},
		["2-handed sword"] = {
			level = 44, name = "steel 2-handed sword"
		},
		["plated skirt"] = {
			level = 46, name = "steel plated skirt"
		},
		["plate mail legs"] = {
			level = 46, name = "steel plate mail legs"
		},
		["plate mail body"] = {
			level = 48, name = "steel plate mail body"
		},
	},
	["mithril bar"] = {
		["dagger"] = {
			level = 50, name = "mithril dagger"
		},
		["hatchet"] = {
			level = 51, name = "mithril axe"
		},
		["mace"] = {
			level = 52, name = "mithril mace"
		},
		["medium helmet"] = {
			level = 53, name = "medium mithril helmet"
		},
		["short sword"] = {
			level = 54, name = "mithril short sword"
		},
		["scimitar"] = {
			level = 55, name = "mithril scimitar"
		},
		["long sword"] = {
			level = 56, name = "mithril long sword"
		},
		["large helmet"] = {
			level = 57, name = "large mithril helmet"
		},
		["square shield"] = {
			level = 58, name = "mithril square shield"
		},
		["battle axe"] = {
			level = 60, name = "mithril battle axe"
		},
		["chain mail body"] = {
			level = 61, name = "mithril chain mail body"
		},
		["kite shield"] = {
			level = 62, name = "mithril kite shield"
		},
		["2-handed sword"] = {
			level = 64, name = "mithril 2-handed sword"
		},
		["plated skirt"] = {
			level = 66, name = "mithril plated skirt"
		},
		["plate mail legs"] = {
			level = 66, name = "mithril plate mail legs"
		},
		["plate mail body"] = {
			level = 68, name = "mithril plate mail body"
		},
	},
	["adamantite bar"] = {
		["dagger"] = {
			level = 70, name = "adamantite dagger"
		},
		["hatchet"] = {
			level = 71, name = "adamantite axe"
		},
		["mace"] = {
			level = 72, name = "adamantite mace"
		},
		["medium helmet"] = {
			level = 73, name = "medium adamantite helmet"
		},
		["short sword"] = {
			level = 74, name = "adamantite short sword"
		},
		["scimitar"] = {
			level = 75, name = "adamantite scimitar"
		},
		["long sword"] = {
			level = 76, name = "adamantite long sword"
		},
		["large helmet"] = {
			level = 77, name = "large adamantite helmet"
		},
		["square shield"] = {
			level = 78, name = "adamantite square shield"
		},
		["battle axe"] = {
			level = 80, name = "adamantite battle axe"
		},
		["chain mail body"] = {
			level = 81, name = "adamantite chain mail body"
		},
		["kite shield"] = {
			level = 82, name = "adamantite kite shield"
		},
		["2-handed sword"] = {
			level = 84, name = "adamantite 2-handed sword"
		},
		["plated skirt"] = {
			level = 86, name = "adamantite plated skirt"
		},
		["plate mail legs"] = {
			level = 86, name = "adamantite plate mail legs"
		},
		["plate mail body"] = {
			level = 88, name = "adamantite plate mail body"
		},
	},
	["runite bar"] = {
		["dagger"] = {
			level = 85, name = "rune dagger"
		},
		["hatchet"] = {
			level = 86, name = "rune axe"
		},
		["mace"] = {
			level = 87, name = "rune mace"
		},
		["medium helmet"] = {
			level = 88, name = "medium rune helmet"
		},
		["short sword"] = {
			level = 89, name = "rune short sword"
		},
		["scimitar"] = {
			level = 90, name = "rune scimitar"
		},
		["long sword"] = {
			level = 91, name = "rune long sword"
		},
		["large helmet"] = {
			level = 92, name = "large rune helmet"
		},
		["square shield"] = {
			level = 93, name = "rune square shield"
		},
		["battle axe"] = {
			level = 95, name = "rune battle axe"
		},
		["chain mail body"] = {
			level = 96, name = "rune chain mail body"
		},
		["kite shield"] = {
			level = 97, name = "rune kite shield"
		},
		["2-handed sword"] = {
			level = 99, name = "rune 2-handed sword"
		},
		["plated skirt"] = {
			level = 99, name = "rune plated skirt"
		},
		["plate mail legs"] = {
			level = 99, name = "rune plate mail legs"
		},
		["plate mail body"] = {
			level = 99, name = "rune plate mail body"
		},
	},
}

local function make_item(player, item_type, bar_type, num_bars)
	local req = forging_table[bar_type][item_type].level

	if not statatleast(player, STAT_SMITHING, req) then
		-- 1e_Luis/Skilling/Mithril smithing table reqs complete
		mes(player, string.format("You need to be at least level %d smithing to do that", req))
		return
	end

	if not held(player, bar_type, num_bars) then
		local bar_req = "two"
		if num_bars == 3 then
			bar_req = "three"
		elseif num_bars == 4 then
			bar_req = "four"
		elseif num_bars == 5 then
			bar_req = "five"
		end
		bar_type = string.gsub(bar_type, " bar", "")
		-- Logg/Tylerbeg/08-01-2018 21.50.15 cooking pizza and cake.pcap
		mes(player,
		    string.format("@que@You need %s bars of %s to make this item.",
		    bar_req, bar_type))
		return
	end

	thinkbubble(player, bar_type)
	remove(player, bar_type, num_bars)

	local base_xp = 0
	if bar_type == "bronze bar" then
		base_xp = 50
	elseif bar_type == "iron bar" then
		base_xp = 100
	elseif bar_type == "steel bar" then
		base_xp = 150
	elseif bar_type == "mithril bar" then
		base_xp = 200
	elseif bar_type == "adamantite bar" then
		base_xp = 250
	elseif bar_type == "runite bar" then
		base_xp = 300
	end

	advancestat(player, STAT_SMITHING, base_xp * num_bars, 0)

	if item_type == "nails" then
		give(player, forging_table[bar_type][item_type].name, 2)
		mes(player, "@que@You hammer the metal and make some nails")
	elseif item_type == "hatchet" then
		give(player, forging_table[bar_type][item_type].name, 1)
		-- oddly inconsistent messaging here
		-- https://youtu.be/Gsv0Vend8HE?t=487
		mes(player, "@que@You hammer the metal and make an axe")
	else
		give(player, forging_table[bar_type][item_type].name, 1)
		mes(player, "@que@You hammer the metal and make a " .. item_type)
	end
end

local function make_helmet(player, bar_type)
	mes(player, "@que@What sort of helmet do you want to make?")
	local resp = multi(player,
		"Medium Helmet",
		"Large Helmet (2 bars)")
	if resp == 1 then
		make_item(player, "medium helmet", bar_type, 1)
	elseif resp == 2 then
		make_item(player, "large helmet", bar_type, 2)
	end
end

local function make_shield(player, bar_type)
	mes(player, "@que@What sort of shield do you want to make?")
	local resp = multi(player,
		"Square Shield (2 bars)", "Kite Shield (3 bars)")
	if resp == 1 then
		make_item(player, "square shield", bar_type, 2)
	elseif resp == 2 then
		make_item(player, "kite shield", bar_type, 3)
	end
end

local function make_plate_armour(player, bar_type)
	mes(player, "@que@What sort of armour do you want to make?")
	local resp = multi(player,
		"Chain mail body (3 bars)",
		"Plate mail body (5 bars)",
		"Plate mail legs (3 bars)",
		"Plated Skirt (3 bars)")
	if resp == 1 then
		make_item(player, "chain mail body", bar_type, 3)
	elseif resp == 2 then
		make_item(player, "plate mail body", bar_type, 5)
	elseif resp == 3 then
		make_item(player, "plate mail legs", bar_type, 3)
	elseif resp == 4 then
		make_item(player, "plated skirt", bar_type, 3)
	end
end

local function make_axe(player, bar_type)
	mes(player, "@que@What sort of axe do you want to make?")
	local resp = multi(player, "Hatchet", "Battle Axe (3 bars)")
	if resp == 1 then
		make_item(player, "hatchet", bar_type, 1)
	elseif resp == 2 then
		make_item(player, "battle axe", bar_type, 3)
	end
end

local function make_sword(player, bar_type)
	mes(player, "@que@What sort of sword do you want to make?")
	local resp = multi(player,
		"Short sword",
		"Long sword (2 bars)",
		"Scimitar (2 bars)",
		"2-handed sword (3 bars)")
	if resp == 1 then
		make_item(player, "short sword", bar_type, 1)
	elseif resp == 2 then
		make_item(player, "long sword", bar_type, 2)
	elseif resp == 3 then
		make_item(player, "scimitar", bar_type, 2)
	elseif resp == 4 then
		make_item(player, "2-handed sword", bar_type, 3)
	end
end

local function make_weapon(player, bar_type)
	mes(player, "@que@Choose a type of weapon to make")
	local resp = multi(player, "Dagger", "Sword", "Axe", "Mace")
	if resp == 1 then
		make_item(player, "dagger", bar_type, 1)
	elseif resp == 2 then
		make_sword(player, bar_type)
	elseif resp == 3 then
		make_axe(player, bar_type)
	elseif resp == 4 then
		make_item(player, "mace", bar_type, 1)
	end
end

local function make_armour(player, bar_type)
	mes(player, "@que@Choose a type of armour to make")
	local resp = multi(player, "Helmet", "Shield", "Armour")
	if resp == 1 then
		make_helmet(player, bar_type)
	elseif resp == 2 then
		make_shield(player, bar_type)
	elseif resp == 3 then
		make_plate_armour(player, bar_type)
	end
end

local function start_smithing(player, bar_type)
	if not held(player, "hammer", 1) then
		-- RSC 2001/replays master archive/Skilling/Smithing/smithing- anvil- fail- no hammer
		mes(player, "@que@You need a hammer to work the metal with.")
		return
	end

	mes(player, "@que@What would you like to make?")
	if bar_type == "steel bar" then
		local resp = multi(player,
		    "Make Weapon", "Make Armour", "Make Nails", "Cancel")
		if resp == 1 then
			make_weapon(player, bar_type)
		elseif resp == 2 then
			make_armour(player, bar_type)
		elseif resp == 3 then
			make_item(player, "nails", bar_type, 1)
		end
	else
		local resp = multi(player, "Make Weapon", "Make Armour", "Cancel")
		if resp == 1 then
			make_weapon(player, bar_type)
		elseif resp == 2 then
			make_armour(player, bar_type)
		end
	end
end

local function check_doric(player)
	if getvar(player, "doric_stage") >= 2 then
		return true
	end

	local npc = nearnpc(player, "doric")
	if npc then
		-- https://classic.runescape.wiki/w/Transcript:Doric
		npcsay(npc, "Heh who said you could use that?")
	else
		-- https://i.imgur.com/tSe5u.png
		say(player, "I'd better ask Doric if I can use this first")
	end

	return false
end

register_useloc("doric's anvil", "bronze bar", function(player, x, y)
	if not check_doric(player) then
		return
	end
	start_smithing(player, "bronze bar")
end)

register_useloc("doric's anvil", "iron bar", function(player, x, y)
	if not check_doric(player) then
		return
	end
	start_smithing(player, "iron bar")
end)

register_useloc("doric's anvil", "steel bar", function(player, x, y)
	if not check_doric(player) then
		return
	end
	start_smithing(player, "steel bar")
end)

register_useloc("doric's anvil", "mithril bar", function(player, x, y)
	if not check_doric(player) then
		return
	end
	start_smithing(player, "mithril bar")
end)

register_useloc("doric's anvil", "adamantite bar", function(player, x, y)
	if not check_doric(player) then
		return
	end
	start_smithing(player, "adamantite bar")
end)

register_useloc("doric's anvil", "runite bar", function(player, x, y)
	if not check_doric(player) then
		return
	end
	start_smithing(player, "runite bar")
end)

register_useloc("anvil", "bronze bar", function(player, x, y)
	start_smithing(player, "bronze bar")
end)

register_useloc("anvil", "iron bar", function(player, x, y)
	start_smithing(player, "iron bar")
end)

register_useloc("anvil", "steel bar", function(player, x, y)
	start_smithing(player, "steel bar")
end)

register_useloc("anvil", "mithril bar", function(player, x, y)
	start_smithing(player, "mithril bar")
end)

register_useloc("anvil", "adamantite bar", function(player, x, y)
	start_smithing(player, "adamantite bar")
end)

register_useloc("anvil", "runite bar", function(player, x, y)
	start_smithing(player, "runite bar")
end)
