function talknpc_count_draynor(player, npc)
	npcsay(npc, "Did you request an audience?")
	mes(player, "You feel a sudden, invisible hand grasp your neck")
	delay(3)
	mes(player, "You are unable to respond")
	delay(3)
	npcsay(npc, "No?")
	npcsay(npc, "Then leave me be, fresh meat")
end
