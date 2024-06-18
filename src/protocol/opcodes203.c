#include "opcodes.h"

uint8_t opcodes_in_203[256];
uint8_t opcodes_out_203[256];

void
init_opcodes_203(void)
{
	opcodes_in_203[0] = OP_CLI_LOGIN;
	opcodes_in_203[1] = OP_CLI_RECONNECT;
}
