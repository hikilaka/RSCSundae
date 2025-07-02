local function identify_herb_fail(player)
	-- RSC 2001/replays master archive/Skilling/Herblaw/Kwuarm/herblaw-ID- kwuarm leaf- fail- insufficient lvl.pcap
	-- RSC 2001/replays master archive/Skilling/Herblaw/Dwarf weed/herblaw-ID Dwarf weed- fail- insufficient lvl.pcap
	mes(player, "@que@You cannot identify this herb")
	mes(player, "@que@you need a higher herblaw level")
end

function opinv_unidentified_guam(player)
	if not statatleast(player, STAT_HERBLAW, 3) then
		identify_herb_fail(player)
		return
	end
	-- RSC 2001/replays master archive/Skilling/Herblaw/Guam/item- guam leaf ID.pcap
	mes(player, "@que@This herb is a Guam leaf")
	remove(player, "unidentified guam", 1)
	give(player, "guam leaf", 1)
	advancestat(player, STAT_HERBLAW, 10, 0)
end

function opinv_unidentified_marrentill(player)
	if not statatleast(player, STAT_HERBLAW, 5) then
		identify_herb_fail(player)
		return
	end
	-- RSC 2001/replays master archive/Skilling/Herblaw/Marrentill/item- marrentill ID.pcap
	mes(player, "@que@This herb is Marrentill")
	remove(player, "unidentified marrentill", 1)
	give(player, "marrentill", 1)
	advancestat(player, STAT_HERBLAW, 15, 0)
end

function opinv_unidentified_tarromin(player)
	if not statatleast(player, STAT_HERBLAW, 11) then
		identify_herb_fail(player)
		return
	end
	-- RSC 2001/replays master archive/Skilling/Herblaw/Tarromin/item- tarromin ID.pcap
	mes(player, "@que@This herb is Tarromin")
	remove(player, "unidentified tarromin", 1)
	give(player, "tarromin", 1)
	advancestat(player, STAT_HERBLAW, 20, 0)
end

function opinv_unidentified_harralander(player)
	if not statatleast(player, STAT_HERBLAW, 20) then
		identify_herb_fail(player)
		return
	end
	-- RSC 2001/replays master archive/Skilling/Herblaw/Harralander/item- harralander leaf ID.pcap
	mes(player, "@que@This herb is Harralander")
	remove(player, "unidentified harralander", 1)
	give(player, "harralander", 1)
	advancestat(player, STAT_HERBLAW, 25, 0)
end

function opinv_unidentified_ranarr(player)
	if not statatleast(player, STAT_HERBLAW, 25) then
		identify_herb_fail(player)
		return
	end
	-- RSC 2001/replays master archive/Skilling/Herblaw/Rannar Weed/item- rannar weed ID.pcap
	mes(player, "@que@This herb is Ranarr Weed")
	remove(player, "unidentified ranarr", 1)
	give(player, "ranarr weed", 1)
	advancestat(player, STAT_HERBLAW, 30, 0)
end

function opinv_unidentified_irit(player)
	if not statatleast(player, STAT_HERBLAW, 40) then
		identify_herb_fail(player)
		return
	end
	-- RSC 2001/replays master archive/Skilling/Herblaw/Irit/item- irit leaf ID.pcap
	mes(player, "@que@This herb is Irit Leaf")
	remove(player, "unidentified irit", 1)
	give(player, "irit leaf", 1)
	advancestat(player, STAT_HERBLAW, 35, 0)
end

function opinv_unidentified_avantoe(player)
	if not statatleast(player, STAT_HERBLAW, 48) then
		identify_herb_fail(player)
		return
	end
	-- RSC 2001/replays master archive/Skilling/Herblaw/Avantoe/item- Avantoe ID.pcap
	mes(player, "@que@This herb is Avantoe")
	remove(player, "unidentified avantoe", 1)
	give(player, "avantoe", 1)
	advancestat(player, STAT_HERBLAW, 40, 0)
end

function opinv_unidentified_kwuarm(player)
	if not statatleast(player, STAT_HERBLAW, 54) then
		identify_herb_fail(player)
		return
	end
	-- flying sno (redacted chat) replays/fsnom2@aol.com/07-16-2018 16.31.43.pcap
	mes(player, "@que@This herb is Kwuarm")
	remove(player, "unidentified kwuarm", 1)
	give(player, "kwuarm", 1)
	advancestat(player, STAT_HERBLAW, 45, 0)
end

function opinv_unidentified_cadantine(player)
	if not statatleast(player, STAT_HERBLAW, 65) then
		identify_herb_fail(player)
		return
	end
	-- 1e_Luis/Skilling/Herb id and pots/Most herb id and pots.pcap
	mes(player, "@que@This herb is Cadantine")
	remove(player, "unidentified cadantine", 1)
	give(player, "cadantine", 1)
	advancestat(player, STAT_HERBLAW, 50, 0)
end

function opinv_unidentified_dwarf_weed(player)
	if not statatleast(player, STAT_HERBLAW, 70) then
		identify_herb_fail(player)
		return
	end
	-- 1e_Luis/Skilling/Herb id and pots/Most herb id and pots.pcap
	mes(player, "@que@This herb is Dwarf Weed")
	remove(player, "unidentified dwarf weed", 1)
	give(player, "dwarf weed", 1)
	advancestat(player, STAT_HERBLAW, 55, 0)
end
