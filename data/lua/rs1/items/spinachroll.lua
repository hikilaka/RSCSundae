-- rscplus-replays-master/RSC 2001/replays master archive/Stat effects/Consumable Stat effects/Healing/spinach roll- consume- heal hp shown- (+2)

function opinv_spinach_roll(player)
	remove(player, "spinach roll", 1)
	mes(player, "@que@You eat the spinach roll")
	if statdown(player, STAT_HITS) then
		healstat(player, STAT_HITS, 2, 0)
		mes(player, "@que@It tastes a bit weird, but fills you up")
	end
end
