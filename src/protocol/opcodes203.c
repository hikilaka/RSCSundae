#include "opcodes.h"

uint8_t opcodes_in_203[256];
uint8_t opcodes_out_203[256];

void
init_opcodes_203(void)
{
	opcodes_in_203[0] = OP_CLI_LOGIN;
	opcodes_in_203[1] = OP_CLI_RECONNECT;
	opcodes_out_203[OP_SRV_PLAYER_MOVEMENT] = 191;
	opcodes_out_203[OP_SRV_PRAYERS] = 206;
	opcodes_out_203[OP_SRV_STAT_XP] = 33;
	opcodes_out_203[OP_SRV_INIT_PLANE] = 25;
	opcodes_out_203[OP_SRV_PLAYER_APPEARANCE] = 234;
}
