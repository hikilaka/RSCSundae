#ifndef OPCODES_H
#define OPCODES_H
#include <stdint.h>

#define OP_CLI_LOGIN		(0)
#define OP_CLI_REGISTER		(2)
#define OP_CLI_PUBLIC_CHAT	(3)
#define OP_CLI_PING		(5)
#define OP_CLI_LOGOUT		(6)
#define OP_CLI_ADMIN_COMMAND	(7)
#define OP_CLI_RECONNECT	(19)
#define OP_CLI_ADD_FRIEND	(26)
#define OP_CLI_REMOVE_FRIEND	(27)
#define OP_CLI_PRIVATE_MESSAGE	(28)
#define OP_CLI_ADD_IGNORE	(29)
#define OP_CLI_REMOVE_IGNORE	(30)
#define OP_CLI_PRIVACY_SETTINGS	(31)
#define OP_CLI_TRADE_CONFIRM	(202)
#define OP_CLI_BANK_DEPOSIT	(205)
#define OP_CLI_BANK_WITHDRAW	(206)
#define OP_CLI_BANK_CLOSE	(207)
#define OP_CLI_PRAYER_OFF	(211)
#define OP_CLI_PRAYER_ON	(212)
#define OP_CLI_SAVE_SETTING	(213)
#define OP_CLI_FOLLOW_PLAYER	(214)
#define OP_CLI_WALK_ENTITY	(215)
#define OP_CLI_SHOP_SELL	(216)
#define OP_CLI_SHOP_BUY		(217)
#define OP_CLI_SHOP_CLOSE	(218)
#define OP_CLI_PLAYER_USEWITH	(219)
#define OP_CLI_INV_CAST		(220)
#define OP_CLI_LOC_CAST		(222)
#define OP_CLI_BOUND_CAST	(223)
#define OP_CLI_ITEM_CAST	(224)
#define OP_CLI_NPC_CAST		(225)
#define OP_CLI_PLAYER_CAST	(226)
#define OP_CLI_SELF_CAST	(227)
#define OP_CLI_ATTACK_PLAYER	(228)
#define OP_CLI_BOUND_OP2	(229)
#define OP_CLI_LOC_OP2		(230)
#define OP_CLI_COMBAT_STYLE	(231)
#define OP_CLI_TRADE_ACCEPT	(232)
#define OP_CLI_TRADE_DECLINE	(233)
#define OP_CLI_TRADE_UPDATE	(234)
#define OP_CLI_TRADE_PLAYER	(235)
#define OP_CLI_ACCEPT_DESIGN	(236)
#define OP_CLI_ANSWER_MULTI	(237)
#define OP_CLI_BOUND_OP1	(238)
#define OP_CLI_BOUND_USEWITH	(239)
#define OP_CLI_INV_USEWITH	(240)
#define OP_CLI_LOC_USEWITH	(241)
#define OP_CLI_LOC_OP1		(242)
#define OP_CLI_NPC_USEWITH	(243)
#define OP_CLI_NPC_ATTACK	(244)
#define OP_CLI_NPC_TALK		(245)
#define OP_CLI_INV_OP1		(246)
#define OP_CLI_INV_UNWEAR	(248)
#define OP_CLI_INV_WEAR		(249)
#define OP_CLI_ITEM_USEWITH	(250)
#define OP_CLI_INV_DROP		(251)
#define OP_CLI_ITEM_TAKE	(252)
#define OP_CLI_WALK_TILE	(255)
#define OP_CLI_WALK_TILE2	(194) /* mudclient136 and higher */

#define OP_SRV_MESSAGE			(8)
#define OP_SRV_LOGOUT			(9)
#define OP_SRV_LOGOUT_REJECT		(10)
#define OP_SRV_INIT_FRIENDS		(23)
#define OP_SRV_FRIEND_UPDATE		(24)
#define OP_SRV_INIT_IGNORE		(26)
#define OP_SRV_PRIVACY_SETTINGS		(27)
#define OP_SRV_PRIVATE_MESSAGE		(28)
#define OP_SRV_SHOW_MESBOX		(204)
#define OP_SRV_SHOW_EFFECT		(206)
#define OP_SRV_STAT			(211)
#define OP_SRV_INVENTORY_REMOVE		(212)
#define OP_SRV_INVENTORY_ITEM		(213)
#define OP_SRV_TRADE_CONFIRM		(217)
#define OP_SRV_STAT_XP			(220)
#define OP_SRV_BANK_CLOSE		(221)
#define OP_SRV_BANK_SHOW		(222)
#define OP_SRV_QUESTS			(226)
#define OP_SRV_PRAYERS			(227)
#define OP_SRV_CLIENT_SETTINGS		(228)
#define OP_SRV_TRADE_STATE_LOCAL	(229)
#define OP_SRV_SHOP_CLOSE		(233)
#define OP_SRV_SHOP_OPEN		(234)
#define OP_SRV_TRADE_STATE_REMOTE	(235)
#define OP_SRV_UPDATE_TRADE_OFFER	(236)
#define OP_SRV_CLOSE_TRADE		(237)
#define OP_SRV_SHOW_TRADE		(238)
#define OP_SRV_SHOW_DESIGN		(239)
#define OP_SRV_DEATH			(241)
#define OP_SRV_EQUIP_BONUSES		(242)
#define OP_SRV_INIT_STATS		(243)
#define OP_SRV_INIT_PLANE		(244)
#define OP_SRV_HIDE_MULTI		(245)
#define OP_SRV_SHOW_MULTI		(246)
#define OP_SRV_NPC_APPEARANCE		(247)
#define OP_SRV_NPC_MOVEMENT		(248)
#define OP_SRV_BOUNDARIES		(249)
#define OP_SRV_PLAYER_APPEARANCE	(250)
#define OP_SRV_INVENTORY		(252)
#define OP_SRV_LOCS			(253)
#define OP_SRV_GROUND_ITEMS		(254)
#define OP_SRV_PLAYER_MOVEMENT		(255)

#define RESP_LOGIN_OK		(0)
#define RESP_REGISTER_OK	(2)
#define RESP_INVALID		(3)
#define RESP_ACCOUNT_USED	(4)
#define RESP_CLIENT_OUTDATED	(5)
#define RESP_IP_USED		(6)
#define RESP_RATE_LIMIT		(7)
#define RESP_TEMP_DISABLED	(11)
#define RESP_PERM_DISABLED	(12)
#define RESP_FULL		(14)

extern uint8_t opcodes_in_201[256];
extern uint8_t opcodes_out_201[256];
extern uint8_t opcodes_in_203[256];
extern uint8_t opcodes_out_203[256];

void init_opcodes_201(void);
void init_opcodes_203(void);
#endif
