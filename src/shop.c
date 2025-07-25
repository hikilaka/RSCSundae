#include <assert.h>
#include <limits.h>
#include <string.h>
#include "config/config.h"
#include "config/item.h"
#include "entity.h"
#include "inventory.h"
#include "server.h"

#define MAX_SHOP_STACK UINT16_MAX

static int shop_remove(struct shop_config *, struct player *, uint16_t);
static uint32_t shop_price(struct shop_config *, struct shop_item *, bool);

int
shop_price_modifier(struct shop_config *shop, struct shop_item *item)
{
	int difference;

	(void)shop;

	/* TODO: should use delta here */

	difference = item->quantity - (int)item->cur_quantity;
	if (difference < -127) {
		difference = -127;
	}
	if (difference > 127) {
		difference = 127;
	}

	return difference;
}

static uint32_t
shop_price(struct shop_config *shop, struct shop_item *item, bool sale)
{
	struct item_config *config;
	int price_mod;
	int difference;

	config = server_item_config_by_id(item->id);
	assert(config != NULL);

	difference = shop_price_modifier(shop, item);

	if (sale) {
		price_mod = shop->sell_modifier + difference;
	} else {
		price_mod = shop->buy_modifier + difference;
	}

	if (price_mod < 10) {
		price_mod = 10;
	}

	return (price_mod * config->value) / 100;
}

void
shop_sell(struct shop_config *shop, struct player *p, uint16_t id)
{
	struct item_config *item;
	struct item_config *coins;
	uint32_t price;

	coins = server_item_config_by_id(ITEM_COINS);
	assert(coins != NULL);

	item = server_item_config_by_id(id);
	if (p->shop == NULL || item == NULL ||
	    !player_inv_held_id(p, id, 1)) {
		return;
	}

	/*
	 * see /Logg/Loggykins/08-04-2018 14.01.18
	 * seems silly but likely really was an engine-level restriction
	 */
	if (id == ITEM_SILK && strcmp(shop->name, "generalshop3") == 0) {
		player_send_message(p,
		    "You can't sell silk here, try selling it in Varrock or Lumbridge");
		return;
	}
	for (size_t i = 0; i < shop->item_count; ++i) {
		if (shop->items[i].id == id) {
			if (shop->items[i].cur_quantity == MAX_SHOP_STACK) {
				return;
			}
			player_inv_remove_id(p, id, 1);
			price = shop_price(shop, &shop->items[i], false);
			if (price > 0) {
				player_inv_give(p, coins, price);
			}
			shop->items[i].cur_quantity++;
			shop->changed = true;
			return;
		}
	}
	if (shop->item_count < MAX_SHOP_ITEMS) {
		if (p->mob.server->untradables && item->quest_item) {
			return;
		}
		if (shop->pawn_limit == 0) {
			return;
		}
		price = (shop->buy_modifier * item->value) / 100;
		player_inv_remove_id(p, id, 1);
		if (price > 0) {
			player_inv_give(p, coins, price);
		}
		shop->items[shop->item_count].id = id;
		shop->items[shop->item_count].restock = 0;
		shop->items[shop->item_count].restock_timer =
		    shop->pawn_limit / 5;
		shop->items[shop->item_count].quantity = 0;
		shop->items[shop->item_count++].cur_quantity = 1;
		shop->changed = true;
	}
}

static int
shop_remove(struct shop_config *shop, struct player *p, uint16_t id)
{
	uint32_t price;

	for (size_t i = 0; i < shop->item_count; ++i) {
		if (shop->items[i].id != id) {
			continue;
		}
		if (shop->items[i].cur_quantity == 0) {
			return -1;
		}
		if (p != NULL) {
			price = shop_price(shop, &shop->items[i], true);
			if (!player_inv_held(p, "coins", price)) {
				player_send_message(p,
				    "You don't have enough money!");
				return -1;
			}
			player_inv_remove(p, "coins", price);
		}
		if (shop->items[i].cur_quantity == 1 && !shop->items[i].restock) {
			shop->item_count--;
			for (size_t j = i; j < shop->item_count; ++j) {
				shop->items[j] = shop->items[j + 1];
			}
		} else {
			shop->items[i].restock_timer =
			    (shop->items[i].restock / 5);
			shop->items[i].cur_quantity--;
		}
		shop->changed = true;
		return 0;
	}
	return -1;
}

void
shop_buy(struct shop_config *shop, struct player *p, uint16_t id)
{
	struct item_config *item;

	item = server_item_config_by_id(id);
	if (p->shop == NULL || item == NULL) {
		return;
	}
	if (item->weight == 0) {
		for (size_t i = 0; i < p->inv_count; ++i) {
			if (p->inventory[i].id != id) {
				continue;
			}
			if (shop_remove(shop, p, id) != -1) {
				player_inv_give(p, item, 1);
			}
			return;
		}
	}
	if (p->inv_count == MAX_INV_SIZE) {
		player_send_message(p,
		    "You can't hold the objects you are trying to buy!");
	} else {
		if (shop_remove(shop, p, id) != -1) {
			player_inv_give(p, item, 1);
		}
	}
	return;
}

void
shop_process(struct shop_config *shop)
{
	struct shop_item *item;

	for (size_t i = 0; i < shop->item_count; ++i) {
		item = &shop->items[i];
		if (item->quantity == 0 && shop->pawn_limit > 0) {
			if (item->restock_timer > 0) {
				item->restock_timer--;
				continue;
			}
			if (item->restock_timer == 0) {
				shop_remove(shop, NULL, item->id);
				item->restock_timer = shop->pawn_limit / 5;
			}
		} else if (item->cur_quantity != item->quantity) {
			if (item->restock_timer > 0) {
				item->restock_timer--;
				continue;
			}
			if (item->cur_quantity < item->quantity) {
				item->cur_quantity++;
				shop->changed = true;
			} else if (item->cur_quantity > item->quantity) {
				item->cur_quantity--;
				shop->changed = true;
			}
			item->restock_timer = item->restock / 5;
		}
	}
}
