function opinv_wine(player)
	-- ./rscplus-replays-master/RSC 2001/replays master archive/Stat effects/Consumable Stat effects/Alcohol/jug of wine- (level 1-1-1 base)
	thinkbubble(player, "wine")
	remove(player, "wine", 1)
	give(player, "jug", 1)
	mes(player, "@que@You drink the wine")
	mes(player, "@que@It makes you feel a bit dizzy")
	substat(player, STAT_ATTACK, 3, 0)
	if statdown(player, STAT_HITS) then
		-- Logg/Tylerbeg/07-26-2018 11.44.01 mapping the kharazi jungle.pcap
		healstat(player, STAT_HITS, 11, 0)
		mes(player, "@que@But it heals some health")
	end
end

function opinv_half_full_wine_jug(player)
	-- https://www.youtube.com/watch?v=3Zv4G_t3TWI&t=658
	thinkbubble(player, "wine")
	remove(player, "half full wine jug", 1)
	give(player, "jug", 1)
	mes(player, "@que@You drink the wine")
	mes(player, "@que@It makes you feel a bit dizzy")
	-- XXX: not confirmed, taken from OSRS
	substat(player, STAT_ATTACK, 2, 0)
	if statdown(player, STAT_HITS) then
		healstat(player, STAT_HITS, 7, 0)
		mes(player, "@que@But it heals some health")
	end
end
