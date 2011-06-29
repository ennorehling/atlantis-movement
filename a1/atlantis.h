#pragma once

#ifndef ATLANTIS_H
#define ATLANTIS_H

#define	NAMESIZE					81
#define	DISPLAYSIZE				161
#define	addlist2(l,p)			(*l = p, l = &p->next)
#define	min(a,b)					((a) < (b) ? (a) : (b))
#define	max(a,b)					((a) > (b) ? (a) : (b))
#define	xisdigit(c)				((c) == '-' || ((c) >= '0' && (c) <= '9'))
#define	addptr(p,i)				((void *)(((char *)p) + i))

#define	ORDERGAP					4
#define	BLOCKSIZE				7
#define	BLOCKBORDER				1
#define	MAINTENANCE				10
#define	STARTMONEY				5000
#define	RECRUITCOST				50
#define	RECRUITFRACTION		4
#define	ENTERTAININCOME		20
#define	ENTERTAINFRACTION		20
#define	TAXINCOME				200
#define	COMBATEXP				10
#define	PRODUCEEXP				10
#define	TEACHNUMBER				10
#define	STUDYCOST				200
#define	POPGROWTH				5
#define	PEASANTMOVE				5

enum
{
	T_OCEAN,
	T_PLAIN,
	T_MOUNTAIN,
	T_FOREST,
	T_SWAMP,
};

enum
{
	SH_LONGBOAT,
	SH_CLIPPER,
	SH_GALLEON,
};

enum
{
	SK_MINING,
	SK_LUMBERJACK,
	SK_QUARRYING,
	SK_HORSE_TRAINING,
	SK_WEAPONSMITH,
	SK_ARMORER,
	SK_BUILDING,
	SK_SHIPBUILDING,
	SK_ENTERTAINMENT,
	SK_STEALTH,
	SK_OBSERVATION,
	SK_TACTICS,
	SK_RIDING,
	SK_SWORD,
	SK_CROSSBOW,
	SK_LONGBOW,
	SK_MAGIC,
	MAXSKILLS
};

enum
{
	I_IRON,
	I_WOOD,
	I_STONE,
	I_HORSE,
	I_SWORD,
	I_CROSSBOW,
	I_LONGBOW,
	I_CHAIN_MAIL,
	I_PLATE_ARMOR,
	I_AMULET_OF_DARKNESS,
	I_AMULET_OF_DEATH,
	I_AMULET_OF_HEALING,
	I_AMULET_OF_TRUE_SEEING,
	I_CLOAK_OF_INVULNERABILITY,
	I_RING_OF_INVISIBILITY,
	I_RING_OF_POWER,
	I_RUNESWORD,
	I_SHIELDSTONE,
	I_STAFF_OF_FIRE,
	I_STAFF_OF_LIGHTNING,
	I_WAND_OF_TELEPORTATION,
	MAXITEMS
};

enum
{
	SP_BLACK_WIND,
	SP_CAUSE_FEAR,
	SP_CONTAMINATE_WATER,
	SP_DAZZLING_LIGHT,
	SP_FIREBALL,
	SP_HAND_OF_DEATH,
	SP_HEAL,
	SP_INSPIRE_COURAGE,
	SP_LIGHTNING_BOLT,
	SP_MAKE_AMULET_OF_DARKNESS,
	SP_MAKE_AMULET_OF_DEATH,
	SP_MAKE_AMULET_OF_HEALING,
	SP_MAKE_AMULET_OF_TRUE_SEEING,
	SP_MAKE_CLOAK_OF_INVULNERABILITY,
	SP_MAKE_RING_OF_INVISIBILITY,
	SP_MAKE_RING_OF_POWER,
	SP_MAKE_RUNESWORD,
	SP_MAKE_SHIELDSTONE,
	SP_MAKE_STAFF_OF_FIRE,
	SP_MAKE_STAFF_OF_LIGHTNING,
	SP_MAKE_WAND_OF_TELEPORTATION,
	SP_SHIELD,
	SP_SUNFIRE,
	SP_TELEPORT,
	MAXSPELLS
};

enum
{
	K_ACCEPT,
	K_ADDRESS,
	K_ADMIT,
	K_ALLY,
	K_ATTACK,
	K_BEHIND,
	K_BOARD,
	K_BUILD,
	K_BUILDING,
	K_CAST,
	K_CLIPPER,
	K_COMBAT,
	K_DEMOLISH,
	K_DISPLAY,
	K_EAST,
	K_END,
	K_ENTER,
	K_ENTERTAIN,
	K_FACTION,
	K_FIND,
	K_FORM,
	K_GALLEON,
	K_GIVE,
	K_GUARD,
	K_LEAVE,
	K_LONGBOAT,
	K_MOVE,
	K_NAME,
	K_NORTH,
	K_PAY,
	K_PRODUCE,
	K_PROMOTE,
	K_QUIT,
	K_RECRUIT,
	K_RESEARCH,
	K_RESHOW,
	K_SAIL,
	K_SHIP,
	K_SINK,
	K_SOUTH,
	K_STUDY,
	K_TAX,
	K_TEACH,
	K_TRANSFER,
	K_UNIT,
	K_WEST,
	K_WORK,
	MAXKEYWORDS
};

typedef struct list
{
	struct list *next;
} list;

typedef struct strlist
{
	struct strlist *next;
	char s[1];
} strlist;

struct unit;

typedef struct building
{
	struct building *next;
	int no;
	char name[NAMESIZE];
	char display[DISPLAYSIZE];
	int size;
	int sizeleft;
} building;

typedef struct ship
{
	struct ship *next;
	int no;
	char name[NAMESIZE];
	char display[DISPLAYSIZE];
	int type;
	int left;
} ship;

typedef struct region
{
	struct region *next;
	int x,y;
	char name[NAMESIZE];
	struct region *connect[4];
	int terrain;
	int peasants;
	int money;
	building *buildings;
	ship *ships;
	struct unit *units;
	int immigrants;
} region;

struct faction;

typedef struct rfaction
{
	struct rfaction *next;
	struct faction *faction;
	int factionno;
} rfaction;

typedef struct faction
{
	struct faction *next;
	int no;
	char name[NAMESIZE];
	char addr[NAMESIZE];
	int lastorders;
	char seendata[MAXSPELLS];
	char showdata[MAXSPELLS];
	rfaction *accept;
	rfaction *admit;
	rfaction *allies;
	strlist *mistakes;
	strlist *messages;
	strlist *battles;
	strlist *events;
	int alive;
	int attacking;
	int seesbattle;
	int dh;
	int nunits;
	int number;
	int money;
} faction;

typedef struct unit
{
	struct unit *next;
	int no;
	char name[NAMESIZE];
	char display[DISPLAYSIZE];
	int number;
	int money;
	faction *faction;
	building *building;
	ship *ship;
	int owner;
	int behind;
	int guard;
	char thisorder[NAMESIZE];
	char lastorder[NAMESIZE];
	int combatspell;
	int skills[MAXSKILLS];
	int items[MAXITEMS];
	int spells[MAXSPELLS];
	strlist *orders;
	int alias;
	int dead;
	int learning;
	int n;
	int *litems;
	int side;
	int isnew;
} unit;

int interactive(void);
struct unit *createunit (struct region *r1);
struct region * createregion(int x, int y);
void resetgame(void);
void destroyunit(struct unit * u, struct region * r);
void moveunit(struct unit * u, struct region * r, struct region *r2);
struct region *findregion (int x,int y);
void process_movement(void);
int igetkeyword (const char *s);
struct region *movewhere (struct region *r);
struct ship *createship(struct region * r, int type);
void addevent(struct faction *f, const char * str);
char *unitid (const struct unit *u);
void mistake (struct faction *f, const char *s, const char *comment);
struct faction *createfaction(void);

extern char buf[];
extern struct region * regions;
#endif
