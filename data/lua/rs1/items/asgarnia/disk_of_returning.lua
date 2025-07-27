function opinv_disk_of_returning(player)
	local x, y = playercoord(player)
	if x == 300 and y == 2600 then
		mes(player, "You spin the disk")
		teleport(player, 311, 3348)
		remove(player, "disk of returning", 1)
	else
		-- ./Logg/Tylerbeg/08-05-2018 13.14.13 @@ disk of returning science.pcap
		mes(player, "The disk will only work from in Thordur's black hole")
	end
end
