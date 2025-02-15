function oploc1_leverb(player, x, y)
	if damagetimer(player) < 15 then
		mes(player, "A mysterious force blocks your teleport spell!")
		mes(player, "You can't use teleport so soon after combat")
	else
		teleport(player, 226, 447)
		showeffect(0, 226, 446)
	end
end
