-- ./rscplus-replays-master/Zephyr/zephyr (originals only)/08-05-2018 16.59.13 eating a pumpkin

function opinv_pumpkin(player)
	remove(player, "pumpkin", 1)
	mes(player, "@que@You eat the pumpkin")
	if statdown(player, STAT_HITS) then
		-- notably, no message.
		-- your soul is damaged. think about what you've done.
		healstat(player, STAT_HITS, 14, 0)
	end
end
