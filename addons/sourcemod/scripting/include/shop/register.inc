typedef CategoryDisplayCallback = function bool(int client, CategoryId category_id, const char[] category, const char[] name, char[] buffer, int maxlen);
typedef CategoryDescriptionCallback = function bool(int client, CategoryId category_id, const char[] category, const char[] description, char[] buffer, int maxlen);
typedef CategoryShouldDisplayCallback = function bool(int client, CategoryId category_id, const char[] category);
typedef CategorySelectCallback = function bool(int client, CategoryId category_id, const char[] category, ShopMenu menu);

typeset ItemUseToggleCallback
{
	function ShopAction (int client, CategoryId category_id, const char[] category, ItemId item_id, const char[] item);
	function ShopAction (int client, CategoryId category_id, const char[] category, ItemId item_id, const char[] item, bool isOn, bool elapsed);
}
typedef ItemRegister = function void(CategoryId category_id, const char[] category, const char[] item, ItemId item_id);
typedef ItemCommon = function void(int client, CategoryId category_id, const char[] category, ItemId item_id, const char[] item);
typedef ItemShouldDisplayCallback = function bool(int client, CategoryId category_id, const char[] category, ItemId item_id, const char[] item, ShopMenu menu);
typedef ItemDisplayCallback = function bool(int client, CategoryId category_id, const char[] category, ItemId item_id, const char[] item, ShopMenu menu, bool &disabled, const char[] name, char[] buffer, int maxlen);
typedef ItemDescriptionCallback = function bool(int client, CategoryId category_id, const char[] category, ItemId item_id, const char[] item, ShopMenu menu, const char[] description, char[] buffer, int maxlen);
typedef ItemBuyCallback = function bool(int client, CategoryId category_id, const char[] category, ItemId item_id, const char[] item, ItemType type, int price, int sell_price, int value);
typedef ItemSellCallback = function bool(int client, CategoryId category_id, const char[] category, ItemId item_id, const char[] item, ItemType type, int sell_price);

/**
 *	Registers new category id
 *	-
 *	@param category				Category unique name
 *	@param name					Default category display name
 *	@param description			Default category description
 *	@param cat_display			Callback called on category being displayed
 *	@param cat_desc				Callback called on category's description being displayed
 *	@param cat_should			Callback called whether the category should be displayed to a player
 *	@param cat_select			Callback called when a player is trying to select the category
 *	-
 *	@return Category id of the category
*/
native CategoryId:Shop_RegisterCategory(const String:category[], const String:name[], const String:description[], 
								CategoryDisplayCallback:cat_display=CategoryDisplayCallback:INVALID_FUNCTION, 
								CategoryDescriptionCallback:cat_desc=CategoryDescriptionCallback:INVALID_FUNCTION,
								CategoryShouldDisplayCallback:cat_should=CategoryShouldDisplayCallback:INVALID_FUNCTION,
								CategorySelectCallback:cat_select=CategorySelectCallback:INVALID_FUNCTION);

/**
 *	Starts an item to register
 *	-
 *	@param category_id			Category id to register an item for
 *	@param item					Item unique name
 *	-
 *	@return true to success, false otherwise
*/
native bool:Shop_StartItem(CategoryId:category_id, const String:item[]);

/**
 *	Sets the item information
 *	-
 *	@param name					Default display name
 *	@param description			Default description
 *	@param price				Item price. Can not be lower than sell_price
 *	@param sell_price			Item sell price. 0 to make item free and -1 to make it unsaleable. Can not be higher than price
 *	@param type					Item type. See ItemType enum
 *	@param value				Sets count if the item type is finite and sets duration if the item is togglable or non-togglable
 *	-
 *	@noreturn
*/
native Shop_SetInfo(const String:name[], const String:description[], price, sell_price = -1, ItemType:type, value = 1);

/**
 *	Sets the item callbacks
 *	-
 *	@param register				Callback called when the item is registered
 *	@param use_toggle			Callback called when the item is being used
 *	@param should				Callback called when the item is being displayed. Here you can stop displaying the item
 *	@param display				Callback called when the item is being displayed. Here you can change item display name
 *	@param description			Callback called when the item description is being displayed. Here you can change item description
 *	@param preview				Callback called when the item is previewing
 *	@param buy					Callback called when the item is being bought
 *	@param sell					Callback called when the item is being sold
 *	@param elapse				Callback called when the item is elapsed
 *	-
 *	@noreturn
*/
native Shop_SetCallbacks(ItemRegister:register=ItemRegister:INVALID_FUNCTION,
							ItemUseToggleCallback:use_toggle=ItemUseToggleCallback:INVALID_FUNCTION, 
							ItemShouldDisplayCallback:should=ItemShouldDisplayCallback:INVALID_FUNCTION, 
							ItemDisplayCallback:display=ItemDisplayCallback:INVALID_FUNCTION, 
							ItemDescriptionCallback:description=ItemDescriptionCallback:INVALID_FUNCTION, 
							ItemCommon:preview=ItemCommon:INVALID_FUNCTION,
							ItemBuyCallback:buy=ItemBuyCallback:INVALID_FUNCTION,
							ItemSellCallback:sell=ItemSellCallback:INVALID_FUNCTION,
							ItemCommon:elapse=ItemCommon:INVALID_FUNCTION);

/**
 *	Sets item custom info
 *	-
 *	@param info			Name of the key
 *	@param value			Value to set
 *	-
 *	@noreturn
*/
native Shop_SetCustomInfo(const String:info[], value);

/**
 *	Sets item custom info
 *	-
 *	@param info			Name of the key
 *	@param value			Value to set
 *	-
 *	@noreturn
*/
native Shop_SetCustomInfoFloat(const String:info[], Float:value);

/**
 *	Sets item custom info
 *	-
 *	@param info			Name of the key
 *	@param value			Value to set
 *	-
 *	@noreturn
*/
native Shop_SetCustomInfoString(const String:info[], String:value[]);

/**
 *	Copies sub keys of the given kv structure to the item
 *	-
 *	@param info			Name of the key
 *	@param value			Value to set
 *	-
 *	@noreturn
*/
native Shop_KvCopySubKeysCustomInfo(Handle:kv);

/**
 *	Copletes the item info structure and start to register. Can not be used before an item has been started to register
 *	-
 *	@noparams
 *	-
 *	@noreturn
*/
native Shop_EndItem();