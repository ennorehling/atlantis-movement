
/*	Atlantis v2.0  13 September 1993
	Copyright 1993 by Russell Wallace

	This is what's written so far of the code for Atlantis 2.0; it won't
	compile or run as is, but is made available in case anyone wants to use
	all or part of it, or just look at it.  Share and enjoy!

	This code may be freely used, modified and distributed.  It may not be
	sold or used commercially without prior written permission from the author.
*/

#define	PBLOCKINC			128
#define	ORDERGAP				4
#define	MAXMAGICIANS		5
#define	MAINTENANCE			10
#define	STARTMONEY			5000
#define	TEACHNUMBER			10

#define	addlist2(l,p)		(*l = p, l = &p->next)
#define	min(a,b)				((a) < (b) ? (a) : (b))
#define	max(a,b)				((a) > (b) ? (a) : (b))
#define	xisdigit(c)			((c) == '-' || ((c) >= '0' && (c) <= '9'))
#define	addptr(p,i)			((void *)(((char *)p) + i))

#define	fori(i,n)			for (i = 0; i != n; i++)
#define	forfaction(f)		for (f = factions; f; f = f->next)
#define	forattitude(f,a)	for (a = f->attitudes; a; a = a->next)
#define	forregion			fori (r,NREGIONS)
#define	forobject(o)		for (o = objects[r]; o; o = o->next)
#define	forunit(u)			for (u = units[r]; u; u = u->next)
#define	forcommand(u,S)	for (S = u->commands; S; S = S->next) switch (igetstr (S->s))
#define	fororder				for (O = orders; O; O = O->next)

enum
{
	F_WAR,
	F_TRADE,
	F_MAGIC,
};

enum
{
	A_ALLY,
	A_ADMIT,
	A_ACCEPT,
	A_NEUTRAL,
	A_UNFRIENDLY,
	A_HOSTILE,
};

enum
{
	T_OCEAN,
	T_CITY,
	T_TOWN,
	T_PLAIN,
	T_FOREST,
	T_MOUNTAIN,
	T_SWAMP,
	T_JUNGLE,
	T_DESERT,
	T_TUNDRA,
};

enum
{
	U_HUMAN,
};

enum
{
	O_TOWER,
	O_FORT,
	O_CASTLE,
	O_CITADEL,
	O_DUNGEON,
	O_LONGBOAT,
	O_CLIPPER,
	O_GALLEON,
};

enum
{
	SK_MINING,
	SK_LUMBERJACK,
	SK_QUARRYING,
	SK_HUNTING,
	SK_FISHING,
	SK_HERB_LORE,
	SK_HORSE_TRAINING,
	SK_WEAPONSMITH,
	SK_ARMORER,
	SK_CARPENTER,
	SK_BUILDING,
	SK_SHIPBUILDING,
	SK_ENTERTAINMENT,
	SK_TACTICS,
	SK_COMBAT,
	SK_RIDING,
	SK_CROSSBOW,
	SK_LONGBOW,
	SK_STEALTH,
	SK_OBSERVATION,
	SK_HEALING,
	SK_MAGIC,
	NSKILLS
};

enum
{
	I_SILVER,
	I_IRON,
	I_WOOD,
	I_STONE,
	I_GEMSTONE,
	I_FUR,
	I_FISH,
	I_HERBS,
	I_HORSE,
	I_SWORD,
	I_CROSSBOW,
	I_LONGBOW,
	I_CHAIN_MAIL,
	I_PLATE_ARMOR,
	I_WAGON,
	NITEMS
};

enum
{
	NSPELLS
};

enum
{
	M_FLY,
	M_RIDE,
	M_WALK,
};

struct list;
struct strlist;
struct faction;
struct attitude;
struct phrase;
struct pblock;
struct object;
struct unit;
struct order;
struct troop;

typedef struct list list;
typedef struct strlist strlist;
typedef struct faction faction;
typedef struct attitude attitude;
typedef struct phrase phrase;
typedef struct pblock pblock;
typedef struct object object;
typedef struct unit unit;
typedef struct order order;
typedef struct troop troop;

struct list
{
	list *next;
};

struct strlist
{
	strlist *next;
	char s[1];
};

struct faction
{
	faction *next;
	int no;
	char type;
	char *name;
	char *addr;
	int lastcommands;
	char seendata[NSPELLS];
	char showdata[NSPELLS];
	attitude *attitudes;
};

struct attitude
{
	attitude *next;
	faction *faction;
	char attitude;
};

struct phrase
{
	phrase *left,*right;
	char *s;
	unsigned short n;
};

struct pblock
{
	pblock *next;
	short n;
	unsigned short v[PBLOCKINC];
};

struct object
{
	object *next;
	int no;
	int alias;
	char type;
	char *name;
	char *desc;
	object *in;
	short remaining;
};

struct unit
{
	unit *next;
	int no;
	int alias;
	char type;
	char *name;
	char *desc;
	object *in;
	int number;
	faction *faction;
	char owner;
	char behind;
	char guard;
	char *thiscommand;
	char *lastcommand;
	char combatspell;
	int skills[NSKILLS];
	int items[NITEMS];
	char spells[NSPELLS];
	strlist *commands;
};

struct order
{
	order *next;
	unit *unit;
	int qty;
};

struct troop
{
	troop *next;
	unit *unit;
	char status;
	char side;
	char attacked;
	char weapon;
	char missile;
	char skill;
	char armor;
	char behind;
	char inside;
	char reload;
	char canheal;
	char invulnerable;
	char power;
	char shieldstone;
	char demoralized;
	char dazzled;
};

unsigned rndno;

FILE *F;
int nextc;
char buf[1024];
char idbuf[1024];

int nextphrasen;
phrase *phrases;
char **phrasev;

int turn;
faction *factions;
char gamedate[40];
int r;

char *terrainnames[] =
{
	0,
	"city",
	"town",
	"plain",
	"forest",
	"mountain",
	"swamp",
	"jungle",
	"desert",
	"tundra",
};

char *objectnames[] =
{
	"tower",
	"fort",
	"castle",
	"citadel",
	"dungeon",
	"longboat",
	"clipper",
	"galleon",
};

int capacity[] =
{
	0,
	20,
	80,
	180,
	320,
	200,
	800,
	1800,
};

int cost[] =
{
	0,
	100,
	200,
	300,
	400,
	100,
	200,
	300,
};

char *skillnames[] =
{
	"mining",
	"lumberjack",
	"quarrying",
	"hunting",
	"fishing",
	"herb lore",
	"horse training",
	"weaponsmith",
	"armorer",
	"carpenter",
	"building",
	"shipbuilding",
	"entertainment",
	"tactics",
	"combat",
	"riding",
	"crossbow",
	"longbow",
	"stealth",
	"observation",
	"healing",
	"magic",
};

char *itemnames[][NITEMS] =
{
	"silver",
	"iron",
	"wood",
	"stone",
	"gemstone",
	"fur",
	"fish",
	"herbs",
	"horse",
	"sword",
	"crossbow",
	"longbow",
	"chain mail",
	"plate armor",
	"wagon",

	"silver",
	"iron",
	"wood",
	"stone",
	"gemstones",
	"furs",
	"fish",
	"herbs",
	"horses",
	"swords",
	"crossbows",
	"longbows",
	"chain mail",
	"plate armor",
	"wagons",
};

char *monthnames[] =
{
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",
};

void error (char *s)
{
	puts (s);
	exit (1);
}

void *cmalloc (int n)
{
	void *p;

	if (n == 0)
		n = 1;

	p = malloc (n);

	if (!p)
		error ("Out of memory.");

	return p;
}

char *cstrdup (char *s1)
{
	char *s;

	if (!s1[0])
		return 0;

	s = cmalloc (strlen (s1) + 1);
	strcpy (s,s1);
	return s;
}

char *factionid (faction *f)
{
	if (f->name)
		sprintf (idbuf,"%s (%d)",f->name,f->no);
	else
		sprintf (idbuf,"(%d)",f->no);

	return idbuf;
}

char *objectid (object *o)
{
	if (o->name)
		sprintf (idbuf,"%s (%d)",o->name,o->no);
	else
		sprintf (idbuf,"(%d)",o->no);

	return idbuf;
}

char *unitid (unit *u)
{
	if (u->name)
		sprintf (idbuf,"%s (%d)",u->name,u->no);
	else
		sprintf (idbuf,"(%d)",u->no);

	return idbuf;
}

unit *createunit (void)
{
	int i,n;
	unit *u,*u2;
	char v[1024];

	u = cmalloc (sizeof (unit));
	memset (u,0,sizeof (unit));

	u->lastcommand = cstrdup ("work");
	u->combatspell = -1;

	stashr ();

	for (n = 0;; n += 1024)
	{
		memset (v,0,sizeof v);

		if (n == 0)
			v[0] = 1;

		forregion
			forunit (u2)
				if (u2->no >= n && u2->no < n + 1024)
					v[u2->no - n] = 1;

		for (i = 0; i != 1024; i++)
			if (!v[i])
			{
				u->no = n + i;
				addlist (&units[r1],u);
				fetchr ();
				return u;
			}
	}
}

object *createobject (void)
{
}

rnd (void)
{
	rndno = rndno * 1103515245 + 12345;
	return (rndno >> 16) & 0x7FFF;
}

lovar (int n)
{
	n /= 2;
	return (rnd () % n + 1) + (rnd () % n + 1);
}

distribute (int old,int new,int n)
{
	int i;
	int t;

	assert (new <= old);

	if (old == 0)
		return 0;

	t = (n / old) * new;

	for (i = (n % old); i; i--)
		if (rnd () % old < new)
			t++;

	return t;
}

magicians (faction *f)
{
	int n;
	int r2;
	unit *u;

	n = 0;

	fori (r2,NREGIONS)
		for (u = units[r2]; u; u = u->next)
			if (u->skills[SK_MAGIC] && u->faction == f)
				n += u->number;

	return n;
}

hasattitude (faction *f,faction *f2,int i)
{
	attitude *a;

	forattitude (f,a)
		if (a->attitude == i)
			return 1;

	return 0;
}

peopleweight (unit *u)
{
	return u->number * PERSONWEIGHT;
}

peoplecapacity (unit *u)
{
	return u->number * PERSONCAPACITY;
}

horseweight (unit *u)
{
	return u->items[I_HORSE] * weight[I_HORSE];
}

horsecapacity (unit *u)
{
	return u->items[I_HORSE] * HORSECAPACITY;
}

wagonweight (unit *u)
{
	return u->items[I_WAGON] * weight[I_WAGON];
}

wagoncapacity (unit *u)
{
	return u->items[I_WAGON] * WAGONCAPACITY;
}

itemweight (unit *u)
{
	int i;
	int n;

	n = 0;

	fori (i,NITEMS)
		switch (i)
		{
			case I_HORSE:
			case I_WAGON:
				break;

			default:
				n += weight[i];
		}

	return n;
}

canfly (unit *u)
{
	return 0;
}

canride (unit *u)
{
	return horsecapacity (u) >
			 peopleweight (u) +
			 wagonweight (u) +
			 itemweight (u);
}

canwalk (unit *u)
{
	return peoplecapacity (u) +
			 horsecapacity (u) +
			 wagoncapacity (u) >
			 itemweight (u);
}

void addlist (void *l1,void *p1)
{
	list **l;
	list *p,*q;

	l = l1;
	p = p1;

	p->next = 0;

	if (*l)
	{
		for (q = *l; q->next; q = q->next)
			;

		q->next = p;
	}
	else
		*l = p;
}

void choplist (list **l,list *p)
{
	list *q;

	if (*l == p)
		*l = p->next;
	else
	{
		for (q = *l; q->next != p; q = q->next)
			assert (q);

		q->next = p->next;
	}
}

void translist (void *l1,void *l2,void *p)
{
	choplist (l1,p);
	addlist (l2,p);
}

void removelist (void *l,void *p)
{
	choplist (l,p);
	free (p);
}

void freelist (void *p1)
{
	list *p,*p2;

	p = p1;

	while (p)
	{
		p2 = p->next;
		free (p);
		p = p2;
	}
}

listlen (void *l)
{
	int i;
	list *p;

	for (p = l, i = 0; p; p = p->next, i++)
		;

	return i;
}

_cdecl scramblecmp (void *p1,void *p2)
{
	return *((long *)p1) - *((long *)p2);
}

void scramble (void *v1,int n,int width)
{
	int i;
	void *v;

	v = cmalloc (n * (width + 4));

	for (i = 0; i != n; i++)
	{
		*(long *)addptr (v,i * (width + 4)) = rnd ();
		memcpy (addptr (v,i * (width + 4) + 4),addptr (v1,i * width),width);
	}

	qsort (v,n,width + 4,scramblecmp);

	for (i = 0; i != n; i++)
		memcpy (addptr (v1,i * width),addptr (v,i * (width + 4) + 4),width);

	free (v);
}

void rc (void)
{
	nextc = fgetc (F);
}

void cfopen (char *filename,char *mode)
{
	F = fopen (filename,mode);

	if (!F)
		error ("Can't open file.");

	rc ();
}

void rs (char *s)
{
	while (nextc != '"')
	{
		if (nextc == EOF)
			error ("Data file is truncated.");

		rc ();
	}

	rc ();

	while (nextc != '"')
	{
		if (nextc == EOF)
			error ("Data file is truncated.");

		*s++ = nextc;
		rc ();
	}

	rc ();
	*s = 0;
}

ri (void)
{
	int i;
	char buf[20];

	i = 0;

	while (!xisdigit (nextc))
	{
		if (nextc == EOF)
			error ("Data file is truncated.");

		rc ();
	}

	while (xisdigit (nextc))
	{
		buf[i++] = nextc;
		rc ();
	}

	buf[i] = 0;
	return atoi (buf);
}

void rl (void)
{
	int i;

	i = 0;

	for (;;)
	{
		if (nextc == EOF)
		{
			buf[0] = EOF;
			return;
		}

		if (nextc == '\n')
		{
			buf[i] = 0;
			return;
		}

		buf[i++] = nextc;
		rc ();
	}
}

void wc (int c)
{
	fputc (c,F);
}

void wsn (char *s)
{
	while (*s)
		wc (*s++);
}

void wnl (void)
{
	wc ('\n');
}

void wspace (void)
{
	wc (' ');
}

void ws (char *s)
{
	wc ('"');
	wsn (s);
	wc ('"');
}

void wi (int n)
{
	sprintf (buf,"%d",n);
	wsn (buf);
}

char *igetstr (char *s1)
{
	int i;
	static char *s;
	static char buf[256];

	if (s1)
		s = s1;

	while (*s == ' ')
		s++;

	i = 0;

	while (*s && *s != ' ')
	{
		buf[i] = *s;

		if (*s == '_')
			buf[i] = ' ';

		s++;
		i++;
	}

	buf[i] = 0;
	return buf;
}

char *getstr (void)
{
	return igetstr (0);
}

geti (void)
{
	return atoip (getstr ());
}

finddirection (char *s)
{
	switch (findkeyword (s))
	{
		case K_N:
		case K_NORTH:
			return 0;

		case K_NE:
		case K_NORTHEAST:
			return 1;

		case K_SE:
		case K_SOUTHEAST:
			return 2;

		case K_S:
		case K_SOUTH:
			return 3;

		case K_SW:
		case K_SOUTHWEST:
			return 4;

		case K_NW:
		case K_NORTHWEST:
			return 5;

		default:
			return -1;
	}
}

faction *findfaction (int i)
{
	faction *f;

	for (f = factions; f; f = f->next)
		if (f->no == i)
			return f;

	return 0;
}

phrase *makephrase (char *s)
{
	phrase *p;

	p = cmalloc (sizeof (phrase));

	p->left = p->right = 0;
	p->s = cstrdup (s);
	p->n = nextphrasen++;

	return p;
}

ispresent (faction *f)
{
	unit *u;

	forunit (u)
		if (u->faction == f)
			return 1;

	return 0;
}

void leave (unit *u)
{
	object *o;
	unit *u2;

	if (u->in)
	{
		o = u->in;
		u->in = 0;

		if (u->owner)
		{
			u->owner = 0;

			forunit (u2)
				if (u2->faction == u->faction && u2->in == o)
				{
					u2->owner = 1;
					return;
				}

			forunit (u2)
				if (u2->in == o)
				{
					u2->owner = 1;
					return;
				}
		}
	}
}

effskill (unit *u,int i)
{
	int n,j,result;

	n = 0;

	if (u->number)
		n = u->skills[i] / u->number;

	j = 1;
	result = 0;

	while (j <= n)
	{
		n -= j;
		j++;
		result++;
	}

	return result;
}

cansee (faction *f,unit *u)
{
	int n,o;
	int cansee;
	unit *u2;

	if (u->faction == f)
		return 2;

	cansee = 0;

	if (u->guard || u->in)
		cansee = 1;

	n = effskill (u,SK_STEALTH);

	forunit (u2)
		if (u2->faction == f)
		{
			o = effskill (u2,SK_OBSERVATION);

			if (o > n)
				return 2;

			if (o >= n)
				cansee = 1;
		}

	return cansee;
}

char *itostr (int i)
{
	static char buf[20];

	sprintf (buf,"%d",i);
	return buf;
}

char *itobracket (int i)
{
	static char buf[20];

	sprintf (buf,"(%d)",i);
	return buf;
}

char *itodollar (int i)
{
	static char buf[20];

	sprintf (buf,"$%d",i);
	return buf;
}

addphrase (char *s)
{
	int c;
	phrase *p;

	if (!phrases)
	{
		phrases = makephrase (s);
		return phrases->n;
	}

	p = phrases;

	for (;;)
	{
		c = strcmp (p->s,s);

		if (c == 0)
			return p->n;

		if (c < 0)
		{
			if (!p->right)
			{
				p->right = makephrase (s);
				return p->right->n;
			}

			p = p->right;
		}
		else
		{
			if (!p->left)
			{
				p->left = makephrase (s);
				return p->left->n;
			}

			p = p->left;
		}
	}
}

void locatephrase (phrase *p)
{
	if (p == 0)
		return;

	locatephrase (p->left);
	locatephrase (p->right);
	phrasev[p->n] = p->s;

	free (p);
}

void fmc (faction *f,int c)
{
	pblock *p;

	p = f->lastpblock;

	if (p == 0)
	{
		p = cmalloc (sizeof (pblock));

		p->next = 0;
		p->n = 0;

		f->pblocks = p;
		f->lastpblock = p;
	}

	if (p->n == PBLOCKINC)
	{
		p->next = cmalloc (sizeof (pblock));
		p = p->next;

		p->next = 0;
		p->n = 0;

		f->lastpblock = p;
	}

	p->v[p->n++] = c;
}

void fms (faction *f,char *s)
{
	fmc (addphrase (s));
}

void fmi (faction *f,int i)
{
	fms (f,itostr (i));
}

void fmp (faction *f)
{
}

void ms (unit *u,char *s)
{
	fms (u->faction,s);
}

void mi (unit *u,int i)
{
	fmi (u->faction,i);
}

void mp (unit *u)
{
	fmp (u->faction);
}

void rps (char *s)
{
	faction *f;

	forfaction (f)
		if (ispresent (f))
			fms (f,s);
}

void rpi (int i)
{
	rps (itostr (i));
}

void initworld (void)
{
}

void readdata (void)
{
}

void writedata (void)
{
}

void readcommands (void)
{
	rl ();

	while (buf[0] != EOF)
	{
		if (!memicmp (buf,"#atlantis",9))
		{
			NEXTPLAYER:

			igetstr (buf);
			i = geti ();
			f = findfaction (i);

			if (!f)
			{
				printf ("Invalid faction number %d.\n",i);
				continue;
			}

			forregion
				forunit (u)
					if (u->faction == f)
					{
						freelist (u->commands);
						u->commands = 0;
					}

			for (;;)
			{
				rl ();

				if (!memicmp (buf,"#atlantis",9))
					goto NEXTPLAYER;

				if (buf[0] == EOF || buf[0] == '\f' || buf[0] == '#')
					goto DONEPLAYER;

				if (!strcmpl (igetstr (buf),"unit"))
				{
					NEXTUNIT:

					i = geti ();
					u = findunitg (i);

					if (!u || u->faction != f)
					{
						fms (f,"Unit");
						fmi (f,i);
						fms (f,"is not one of your units");
						fmp (f);
						continue;
					}

					SP = &u->commands;
					u->faction->lastcommands = turn;

					for (;;)
					{
						rl ();

						if (!strcmpl (igetstr (buf),"unit"))
						{
							*SP = 0;
							goto NEXTUNIT;
						}

						if (!memicmp (buf,"#atlantis",9))
						{
							*SP = 0;
							goto NEXTPLAYER;
						}

						if (buf[0] == EOF || buf[0] == '\f' || buf[0] == '#')
						{
							*SP = 0;
							goto DONEPLAYER;
						}

						i = 0;
						j = 0;

						for (;;)
						{
							while (buf[i] == ' ' ||
									 buf[i] == '\t')
								i++;

							if (buf[i] == 0 ||
								 buf[i] == ';')
								break;

							if (buf[i] == '"')
							{
								i++;

								for (;;)
								{
									while (buf[i] == '_' ||
											 buf[i] == ' ' ||
											 buf[i] == '\t')
										i++;

									if (buf[i] == 0 ||
										 buf[i] == '"')
										break;

									while (buf[i] != 0 &&
											 buf[i] != '"' &&
											 buf[i] != '_' &&
											 buf[i] != ' ' &&
											 buf[i] != '\t')
										buf2[j++] = buf[i++];

									buf2[j++] = '_';
								}

								if (buf[i] != 0)
									i++;

								if (j && (buf2[j - 1] == '_'))
									j--;
							}
							else
							{
								for (;;)
								{
									while (buf[i] == '_')
										i++;

									if (buf[i] == 0 ||
										 buf[i] == ';' ||
										 buf[i] == '"' ||
										 buf[i] == ' ' ||
										 buf[i] == '\t')
										break;

									while (buf[i] != 0 &&
											 buf[i] != ';' &&
											 buf[i] != '"' &&
											 buf[i] != '_' &&
											 buf[i] != ' ' &&
											 buf[i] != '\t')
										buf2[j++] = buf[i++];

									buf2[j++] = '_';
								}

								if (j && (buf2[j - 1] == '_'))
									j--;
							}

							buf2[j++] = ' ';
						}

						if (j)
						{
							buf2[j - 1] = 0;
							S = makestrlist (buf2);
							addlist2 (SP,S);
						}
					}
				}
			}
		}

		DONEPLAYER:

		rl ();
	}
}

hasbracket (char *s)
{
	while (*s)
	{
		if (*s == '(')
			return 1;

		s++;
	}

	return 0;
}

void zerounit (unit *u)
{
	u->number = 0;
	memset (u->skills,0,sizeof u->skills);
	memset (u->spells,0,sizeof u->spells);
}

void getsilver (unit *u,int n)
{
	int i;
	unit *u2;

	n -= u->items[I_SILVER];

	forunit (u2)
	{
		if (n <= 0)
			break;

		if (u2->faction == u->faction && u2 != u)
		{
			i = min (u2->items[I_SILVER],n);
			u2->items[I_SILVER] -= i;
			u->items[I_SILVER] += i;
			n -= i;
		}
	}
}

void destroyfaction (faction *f)
{
	unit *u;

	forregion
		forunit (u)
			if (u->faction == f)
				zerounit (u);

	f->alive = 0;
}

void removeempty (void)
{
	int i;
	object *o,*o2;
	unit *u,*u2,*u3;

	forregion
	{
		for (u = units[r]; u;)
		{
			u2 = u->next;

			if (u->number == 0)
			{
				leave (u);

				forunit (u3)
					if (u3->faction == u->faction)
					{
						for (i = 0; i != NITEMS; i++)
							u3->items[i] += u->items[i];

						break;
					}

				freestr (u->name);
				freestr (u->desc);
				freelist (u->commands);
				removelist (&units[r],u);
			}

			u = u2;
		}

		if (terrain[r] == T_OCEAN)
			for (o = objects[r]; o;)
			{
				o2 = o->next;

				forunit (u)
					if (u->in == o)
						break;

				if (!u)
				{
					if (o->name)
						rps ("The");

					rps (shipid (o));
					rps ("sinks");
					rpp ();

					removelist (&objects[r],o);
				}

				o = o2;
			}
	}
}

void removenullfactions (void)
{
	faction *f,*f2,*f3;
	attitude *a,*a2;

	for (f = factions; f;)
	{
		f2 = f->next;

		if (!f->alive)
		{
			printf ("Removing %s.\n",factionid (f));

			forfaction (f3)
				for (a = f3->attitudes; a;)
				{
					a2 = a->next;

					if (a->faction == f)
						removelist (&f3->attitudes,a);

					a = a2;
				}

			freestr (f->name);
			freestr (f->addr);
			freelist (f->attitudes);

			removelist (&factions,f);
		}

		f = f2;
	}
}

void zerotemp (void)
{
	unit *u;

	forunit (u)
		u->temp = 0;
}

usecavalry (void)
{
	return terrain[r] == T_CITY ||
			 terrain[r] == T_TOWN ||
			 terrain[r] == T_PLAIN ||
			 terrain[r] == T_DESERT ||
			 terrain[r] == T_TUNDRA;
}

void maketroops (unit *u)
{
	int i;
	troop *t;
	static char skills[NSKILLS];
	static items[NITEMS];

	fori (i,NSKILLS)
		skills[i] = effskill (u,i);

	memcpy (items,u->items,sizeof items);

	initial[u->faction->side] += u->number;
	if (!u->behind)
		infront[u->faction->side] += u->number;

	fori (i,u->number)
	{
		t = cmalloc (sizeof (troop));
		memset (t,0,sizeof (troop));

		t->unit = u;
		t->side = u->faction->side;
		t->behind = u->behind;
		t->defendskill = skills[SK_COMBAT];

		if (u->combatspell >= 0)
			t->missile = 1;
		else if (items[I_LONGBOW] && skills[SK_LONGBOW])
		{
			t->weapon = I_LONGBOW;
			t->missile = 1;
			t->attackskill = skills[SK_LONGBOW] - 2;
			items[I_LONGBOW]--;
		}
		else if (items[I_CROSSBOW] && skills[SK_CROSSBOW])
		{
			t->weapon = I_CROSSBOW;
			t->missile = 1;
			t->attackskill = skills[SK_CROSSBOW];
			items[I_CROSSBOW]--;
		}
		else if (items[I_SWORD] && skills[SK_SWORD])
		{
			t->weapon = I_SWORD;
			t->attackskill = skills[SK_SWORD] + 2;
			t->defendskill = skills[SK_SWORD] + 2;
			items[I_SWORD]--;

			if (items[I_HORSE] && skills[SK_RIDING] >= 2 && usecavalry ())
			{
				t->attackskill += 2;
				t->defendskill += 2;
				items[I_HORSE]--;
			}
		}

		if (u->spells[SP_HEAL] || items[I_AMULET_OF_HEALING])
		{
			t->canheal = 1;

			if (!u->spells[SP_HEAL])
				items[I_AMULET_OF_HEALING]--;
		}

		if (items[I_RING_OF_POWER])
		{
			t->ring_of_power = 1;
			items[I_RING_OF_POWER]--;
		}

		if (items[I_SHIELDSTONE])
		{
			t->shieldstone = 1;
			items[I_SHIELDSTONE]--;
		}

		if (items[I_CLOAK_OF_INVULNERABILITY])
		{
			t->cloak_of_invulnerability = 1;
			items[I_CLOAK_OF_INVULNERABILITY]--;
		}
		else if (items[I_PLATE_ARMOR])
		{
			t->armor = 2;
			items[I_PLATE_ARMOR]--;
		}
		else if (items[I_CHAIN_MAIL])
		{
			t->armor = 1;
			items[I_CHAIN_MAIL]--;
		}

		if (u->in && u->in->sizeleft)
		{
			t->inside = 2;
			u->in->sizeleft--;
		}

		addlist2 (tp,t);
	}
}

contest (int a,int d)
{
	int ac,dc;
	int n;

	if (a > d)
	{
		ac = 1 << (a - d);
		dc = 1;
	}
	else
	{
		dc = 1 << (d - a);
		ac = 1;
	}

	n = (rnd () << 15) | rnd ();
	return n % (ac + dc) < ac;
}

hits (void)
{
	int k;

	if (rnd () & 1)
		return 0;

	attacker.attackskill -= (attacker.demoralized + attacker.dazzled);
	defender.defendskill -= (defender.demoralized + defender.dazzled);

	switch (attacker.weapon)
	{
		case 0:
		case I_SWORD:
			k = contest (attacker.attackskill,defender.defendskill + defender.inside);
			break;

		default:
			k = contest (attacker.attackskill,defender.inside);
	}

	if (defender.invulnerable && rnd () % 10000)
		k = 0;

	if (rnd () % 3 < defender.armor)
		k = 0;

	return k;
}

validtarget (int i)
{
	return !ta[i].status &&
			 ta[i].side == defender.side &&
			 (!ta[i].behind || !infront[defender.side]);
}

selecttarget (void)
{
	int i;

	do
		i = rnd () % ntroops;
	while (!validtarget (i));

	return i;
}

void terminate (int i)
{
	if (!ta[i].attacked)
	{
		ta[i].attacked = 1;
		toattack[defender.side]--;
	}

	ta[i].status = 1;
	left[defender.side]--;
	if (infront[defender.side])
		infront[defender.side]--;
}

void dozap (int n)
{
	n = lovar (n * (1 + attacker.ring_of_power));
	n = min (n,left[defender.side]);

	rpc ();
	rps ("inflicting");
	rpi (n);
	rps ((n == 1) ? "casualty" : "casualties");

	while (--n >= 0)
		terminate (selecttarget ());
}

void docombatspell (int i)
{
	z = tv[i].unit->combatspell;

	rps (unitid (tv[i].unit));
	rps ("casts");
	rps (spellnames[z]);
	rpc ();

	if (shields[defender.side])
		if (rnd () & 1)
		{
			rps ("and gets through the shield");
			shields[defender.side] -= 1 + attacker.ring_of_power;
		}
		else
		{
			rps ("but the spell is deflected by the shield");
			rpc ();
			return;
		}

	switch (z)
	{
	}
}

void doshot (void)
{
	int ai,di;

			// Select attacker

	do
		ai = rnd () % ntroops;
	while (tv[ai].attacked);

	attacker = tv[ai];
	tv[ai].attacked = 1;
	toattack[attacker.side]--;
	defender.side = 1 - attacker.side;

	tv[ai].dazzled = 0;

	if (attacker.behind &&
		 infront[attacker.side] &&
		 !attacker.missile)
		return;

	if (attacker.shieldstone)
		shields[attacker.side] += 1 + attacker.ring_of_power;

	if (attacker.unit->combatspell >= 0)
	{
		docombatspell (ai);
		return;
	}

	if (attacker.reload)
	{
		ta[ai].reload = 0;
		return;
	}

	if (attacker.weapon == I_CROSSBOW)
		ta[ai].reload = 1;

			// Select target

	di = selecttarget ();
	defender = ta[di];
	assert (defender.side == 1 - attacker.side);

			// Determine result of attack

	if (hits ())
		terminate (di);
}

void reportcasualties (unit *u)
{
	if (!u->temp)
		return;

	rps (unitid (u));

	if (u->number == 1)
		rps ("is dead");
	else
		if (u->number == u->temp)
			rps ("is wiped out");
		else
		{
			rps ("loses");
			rpi (u->temp);
		}

	rpp ();
}

void fight (void)
{
			// Create randomly sorted list of factions

	for (f = factions, i = 0; f; f = f->next, i++)
		fa[i] = f;

	scramble (fv,nfactions,sizeof (faction *));

			// Handle attacks on each faction

	for (fno = 0; fno != nfactions; fno++)
	{
				// Decide which faction is under attack

		f = fv[fno];

		if (!f->attackers)
			continue;

				// Decide which side each faction is on

		forfaction (f2)
			f2->side = -1;

		f->side = 1;

		forattacker (f,A)
			A->faction->side = 0;

		forfaction (f2)
			forattitude (f2,a)
				if (a->faction == f && a->attitude == A_ALLY)
				{
					if (f2->side == -1)
						f2->side = 1;
					else
						f2->side = 0;

					break;
				}

				// Draw up troops for the battle

		forobject (o)
			o->sizeleft = o->size;

		troops = 0;
		tp = &troops;

		initial[0] = 0;
		initial[1] = 0;
		infront[0] = 0;
		infront[1] = 0;

		forunit (u)
			maketroops (u);

		*tp = 0;

				// If they give a war and only one side comes, cancel

		if (initial[0] == 0 || initial[1] == 0)
		{
			freelist (troops);
			continue;
		}

				// Convert list of troops into an array

		ntroops = initial[0] + initial[1];
		tv = cmalloc (ntroops * sizeof (troop));

		for (t = troops, i = 0; t; t = t->next, i++)
			ta[i] = *t;

		freelist (troops);
		scramble (tv,ntroops,sizeof (troop));

				// Variables at start of battle

		left[0] = initial[0];
		left[1] = initial[1];

				// Does one side have an advantage in tactics?

		maxtactics[0] = -1;
		maxtactics[1] = -1;

		forunit (u)
			if (u->faction->side != -1)
			{
				i = effskill (u,SK_TACTICS);

				if (i > maxtactics[u->faction->side])
				{
					leader[u->faction->side] = u;
					maxtactics[u->faction->side] = i;
				}
			}

		attacker.side = -1;

		if (maxtactics[0] > maxtactics[1] && maxtactics[0] >= 0)
			attacker.side = 0;
		if (maxtactics[1] > maxtactics[0] && maxtactics[1] >= 0)
			attacker.side = 1;

				// Initial messages

		rps (unitid (leader[0]));
		rps ("attacks");
		rps (unitid (leader[1]));
		rps ("in");

		if (terrain[r] == T_OCEAN)
			rps ("the ocean");
		else
			rps (terrainnames[r]);

		rpp ();

				// Better leader gets free round of attacks

		if (attacker.side != -1)
		{
			rps (unitid (leader[attacker.side]));
			rps ("gets a free round of attacks");
			rpp ();

					// Troops to attack

			toattack[attacker.side] = 0;

			fori (i,ntroops)
			{
				tv[i].attacked = 1;

				if (tv[i].side == attacker.side)
				{
					tv[i].attacked = 0;
					toattack[attacker.side]++;
				}
			}

					// Do round of attacks

			do
				doshot ();
			while (toattack[attacker.side] && left[defender.side]);
		}

				// Do main body of battle

		toattack[0] = 0;
		toattack[1] = 0;

		while (left[defender.side])
		{
					// End of a round

			if (toattack[0] == 0 && toattack[1] == 0)
				fori (i,ntroops)
				{
					ta[i].attacked = 1;

					if (!ta[i].status)
					{
						ta[i].attacked = 0;
						toattack[ta[i].side]++;
					}
				}

			doshot ();
		}

				// Report on winner

		rps (unitid (leader[attacker.side]));
		rps ("wins the battle");
		rpp ();

				// Can wounded be healed?

		n = initial[attacker.side] - left[attacker.side];
		zerotemp ();

		fori (i,ntroops)
		{
			if (n == 0)
				break;

			if (ta[i].status)
				continue;

			fori (j,HEALNUMBER)
			{
				if (n == 0)
					break;

				if (!ta[i].canheal)
				{
					if (ta[i].herbs == 0)
						break;

					ta[i].herbs--;
				}

				if (rnd () & 1)
				{
					do
						k = rnd () % ntroops;
					while (!ta[k].status || ta[k].side != attacker.side);

					ta[k].status = 0;
					n--;
					ta[i].unit->temp++;
				}
			}
		}

		forunit (u)
			if (u->temp)
			{
				rps (unitid (u));
				rps ("heals");
				rpi (u->temp);
				rps ("wounded");
				rpp ();
			}

				// Count the casualties

		zerotemp ();

		fori (i,ntroops)
			ta[i].unit->temp += ta[i].status;

		reportcasualties (leader[attacker.side]);

		forunit (u)
			if (u->faction->side == attacker.side && u != leader[attacker.side])
				reportcasualties (u);

				// Adjust units

		memset (litems,0,sizeof litems);

		forunit (u)
		{
			k = u->number - u->temp;

			if (u->side == defender.side)
				fori (i,NITEMS)
				{
					j = distribute (u->number,k,u->items[i]);
					litems[i] += u->items[i] - j;
					u->items[i] = j;
				}

			fori (i,NSKILLS)
				u->skills[i] = distribute (u->number,k,u->skills[i]);

			u->number = k;
		}

				// Distribute loot

		fori (i,NITEMS)
			fori (n,litems[i])
				if (rnd () & 1)
				{
					do
						j = rnd () % ntroops;
					while (ta[j].status);

					if (!ta[j].unit->litems)
					{
						ta[j].unit->litems = cmalloc (NITEMS * sizeof (int));
						memset (ta[j].unit->litems,0,NITEMS * sizeof (int));
					}

					ta[j].unit->items[i]++;
					ta[j].unit->litems[i]++;
				}

		forunit (u)
			if (u->litems)
			{
				ms (u,unitid (u));
				ms (u,"finds");

				dh = 0;

				fori (i,NITEMS)
					if (u->litems[i])
					{
						if (dh)
							mc (u);

						dh = 1;

						if (i == I_SILVER)
							ms (u,itodollar (u->litems[i]));
						else
						{
							mi (u,u->litems[i]);
							ms (u,itemnames[u->litems[i] != 1][i]);
						}

				mp (u);

				free (u->litems);
				u->litems = 0;
			}

		free (tv);
	}
}

adjacent (int dir)
{
}

void processcommands (void)
{
	puts ("Processing FORM orders...");

	forregion
		forunit (u)
			for (S = u->commands; S;)
				switch (igetkeyword (S->s))
				{
					case K_FORM:
						u2 = createunit ();

						u2->alias = geti ();
						if (u2->alias == 0)
							u2->alias = geti ();

						u2->faction = u->faction;
						u2->in = u->in;
						u2->behind = u->behind;
						u2->guard = u->guard;

						S = S->next;

						while (S)
						{
							if (igetkeyword (S->s) == K_END)
							{
								S = S->next;
								break;
							}

							S2 = S->next;
							translist (&u->commands,&u2->commands,S);
							S = S2;
						}

						break;

					default:
						S = S->next;
				}

	puts ("Processing instant orders...");

	forregion
		forunit (u)
			forcommand (u,S)
			{
				case -1:
					ms (u,strupr (igetstr (S->s)));
					ms (u,"is not a recognized command");
					mp (u);
					break;

				case K_ADDRESS:
					freestr (u->faction->addr);
					u->faction->addr = cstrdup (getstr);

					for (s = u->faction->addr; *s; s++)
						if (*s == ' ')
							*s = '_';

					printf ("%s is changing address to %s.\n",factionid (u->faction),
																			u->faction->addr);
					break;

				case K_BEHIND:
					u->behind = geti ();
					break;

				case K_COMBAT:
					s = getstr ();

					if (!s[0])
					{
						u->combatspell = -1;
						break;
					}

					i = findspell (s);

					if (i < 0 || !cancast (u,i))
					{
						ms (u,"Spell");
						ms (u,strupr (s));
						ms ("not found");
						mp (u);
						break;
					}

					if (!iscombatspell[i])
					{
						ms (u,spellnames[i]);
						ms (u,"is not a combat spell");
						mp (u);
						break;
					}

					u->combatspell = i;
					break;

				case K_DESCRIBE:
					s = getstr ();

					if (findkeyword (s) == K_OBJECT)
					{
						if (!u->in)
						{
							ms (u,u->name);
							ms (u,"is not in an object");
							mp (u);
							break;
						}

						if (!u->owner)
						{
							ms (u,objectid (u->in));
							ms (u,"is not owned by");
							ms (u,unitid (u));
							mp (u);
							break;
						}

						s = getstr ();

						i = strlen (s);
						if (i && s[i - 1] == '.')
							s[i - 1] = 0;

						freestr (u->in->desc);
						u->in->desc = cstrdup (s);
						break;
					}

					i = strlen (s);
					if (i && s[i - 1] == '.')
						s[i - 1] = 0;

					freestr (u->desc);
					u->desc = cstrdup (s);
					break;

				case K_GUARD:
					if (!geti ())
						u->guard = 0;

					break;

				case K_NAME:
					s = getstr ();

					switch (findkeyword (s))
					{
						case K_FACTION:
							s = getstr ();

							if (hasbracket (s))
							{
								ms (u,"Names cannot contain brackets");
								mp (u);
								break;
							}

							freestr (u->faction->name);
							u->faction->name = cstrdup (s);
							break;

						case K_OBJECT:
							if (!u->in)
							{
								ms (u,u->name);
								ms (u,"is not in an object");
								mp (u);
								break;
							}

							if (!u->owner)
							{
								ms (u,unitid (u));
								ms (u,"does not own");
								ms (u,objectid (u->in));
								mp (u);
								break;
							}

							s = getstr ();

							if (hasbracket (s))
							{
								ms (u,"Names cannot contain brackets");
								mp (u);
								break;
							}

							freestr (u->in->name);
							u->in->name = cstrdup (s);
							break;

						default:
							if (hasbracket (s))
							{
								ms (u,"Names cannot contain brackets");
								mp (u);
								break;
							}

							freestr (u->name);
							u->name = cstrdup (s);
							break;
					}

					break;

				case K_RESHOW:
					s = getstr ();
					i = findspell (s);

					if (i < 0 || !u->faction->seendata[i])
					{
						ms (u,"Spell");
						ms (u,strupr (s));
						ms (u,"not found");
						mp (u);
						break;
					}

					u->faction->showdata[i] = 1;
					break;
			}

	puts ("Processing FIND orders...");

	forregion
		forunit (u)
			forcommand (u,S)
			{
				case K_FIND:
					i = geti ();
					f = findfaction (i);

					if (!f)
					{
						ms (u,"Faction");
						mi (u,i);
						ms (u,"not found");
						mp (u);
						break;
					}

					ms (u,"The address of");
					ms (u,factionid (f));
					ms (u,"is");
					ms (u,f->addr);
					mp (u);
					break;
			}

	puts ("Processing leaving and entering orders...");

	forregion
		forunit (u)
			forcommand (u,S)
			{
				case K_ENTER:
					i = geti ();
					o = findobject (i);

					if (!o)
					{
						ms (u,"Object");
						mi (u,i);
						ms (u,"not found");
						mp (u);
						break;
					}

					if (!mayenter (u,o)
					{
						ms (u,unitid (u));
						ms (u,"may not enter");
						ms (u,objectid (o));
						mp (u);
						break;
					}

					leave (u);
					u->in = o;

					u->owner = 0;
					if (objectowner (o)) == 0)
						u->owner = 1;

					break;

				case K_LEAVE:
					if (terrain[r] == T_OCEAN)
					{
						ms (u,unitid (u));
						ms (u,"is on board a ship at sea");
						mp (u);
						break;
					}

					leave (u);
					break;

				case K_PROMOTE:
					i = geti ();
					u2 = findunit (u,i);

					if (!u2)
					{
						ms (u,"Unit");
						mi (u,i);
						ms (u,"not found");
						mp (u);
						break;
					}

					if (!u->in)
					{
						ms (u,unitid (u));
						ms (u,"is not in an object");
						mp (u);
						break;
					}

					if (!u->owner)
					{
						ms (u,unitid (u));
						ms (u,"does not own");
						ms (u,objectid (u->in));
						mp (u);
						break;
					}

					if (u2->in != u->in)
					{
						ms (u,unitid (u2));
						ms (u,"is not in");
						ms (u,objectid (u->in));
						mp (u);
						break;
					}

					if (!accepts (u2,u))
					{
						ms (u,unitid (u2));
						ms (u,"does not accept ownership of");
						ms (u,objectid (u->in));
						mp (u);
						break;
					}

					u->owner = 0;
					u2->owner = 1;
					break;
			}

	puts ("Processing combat...");

	nfactions = listlen (factions);
	fv = cmalloc (nfactions * sizeof (faction *));

	forregion
	{
				// Do auto attacks based on HOSTILE status

		forfaction (f)
			if (ispresent (f))
			{
				if (f->default == A_HOSTILE)
				{
					forunit (u)
						addattacker (f,u->faction);

					continue;
				}

				forattitude (f,a)
					if (a->attitude == A_HOSTILE)
						forunit (u)
							if (u->faction == a->faction && cansee (f,u) == 2)
							{
								addattacker (f,a->faction);
								break;
							}
			}

				// Do ATTACK orders

		forunit (u)
			forcommand (u,S)
			{
				case K_ATTACK:
					i = geti ();
					u2 = findunit (u,i);

					if (!u2)
					{
						ms (u,"Unit");
						mi (u,i);
						ms ("not found");
						mp (u);
						break;
					}

					if (u2->faction == u->faction)
					{
						ms (u,unitid (u2));
						ms (u,"is one of your units");
						mp (u);
						break;
					}

					addattacker (u->faction,u2->faction);
			}

		fight ();
	}

	free (fv);

	puts ("Processing economic orders...");

	forregion
	{
		forunit (u)
			forcommand (u,S)
			{
				case K_DESTROY:
					o = u->in;

					if (!o)
					{
						ms (u,unitid (u));
						ms (u,"is not in an object");
						mp (u);
						break;
					}

					if (!u->owner)
					{
						ms (u,unitid (u));
						ms (u,"does not own");
						ms (u,objectid (o));
						mp (u);
						break;
					}

					if (terrain[r] == T_OCEAN)
					{
						ms (u,unitid (u));
						ms (u,"is on board a ship at sea");
						mp (u);
						break;
					}

					forunit (u2)
						if (u2->in == o)
						{
							u2->in = 0;
							u2->owner = 0;
						}

					rps (unitid (u));

					if (isship (o))
					{
						rps ("sinks");

						if (o->name)
							rps ("the");
					}
					else
						rps ("demolishes");

					rps (objectid (o));
					rpp ();
					break;

				case K_GIVE:
					i = geti ();

					if (!i)
					{
						n = geti ();

						s = getstr ();
						i = finditem (s);

						if (i < 0)
						{
							ms (u,"Item");
							ms (u,strupr (s));
							ms (u,"not found");
							mp (u);
							break;
						}

						n = min (n,u->items[i]);

						if (!n)
						{
							ms (u,unitid (u));
							ms (u,"has no");
							ms (u,itemnames[1][i]);
							mp (u);
							break;
						}

						u->items[i] -= n;

						ms (u,unitid (u));
						ms (u,"discards");
						mi (u,n);
						ms (u,itemnames[n != 1][i]);
						mp (u);
						break;
					}

					u2 = findunit (u,i);

					if (!u2)
					{
						ms (u,"Unit");
						mi (u,i);
						ms (u,"not found");
						mp (u);
						break;
					}

					if (!accepts (u2,u))
					{
						ms (u,unitid (u2));
						ms (u,"does not accept gifts");
						mp (u);
						break;
					}

					s = getstr ();
					i = findspell (s);

					if (i >= 0)
					{
						if (!u->spells[i])
						{
							ms (u,"Spell");
							ms (u,strupr (s));
							ms (u,"not found");
							mp (u);
							break;
						}

						if (spelllevel[i] > effskill (u2,SK_MAGIC))
						{
							ms (u,unitid (u2));
							ms (u,"is not able to learn the");
							ms (u,spellnames[i]);
							mp (u);
							break;
						}

						if (u->items[I_SILVER] < 10)
						{
							ms (u,unitid (u));
							ms (u,"has insufficient funds to give");
							ms (u,unitid (u2));
							ms (u,"the");
							ms (u,spellnames[i]);
							ms (u,"spell");
							mp (u);
							break;
						}

						u2->spells[i] = 1;
						u->items[I_SILVER] -= 10;

						ms (u,unitid (u));
						ms (u,"gives");
						ms (u,unitid (u2));
						ms (u,"the");
						ms (u,spellnames[i]);
						ms (u,"spell");
						mp (u);

						if (u->faction != u2->faction)
						{
							ms (u2,unitid (u));
							ms (u2,"gives");
							ms (u2,unitid (u2));
							ms (u2,"the");
							ms (u2,spellnames[i]);
							ms (u2,"spell");
							mp (u2);
						}

						if (!u2->faction->seendata[i])
							u2->faction->showdata[i] = 1;

						break;
					}

					n = atoip (s);

					s = getstr ();
					i = finditem (s);

					if (i < 0)
					{
						ms (u,"Item");
						ms (u,strupr (s));
						ms (u,"not found");
						mp (u);
						break;
					}

					n = min (n,u->items[i]);

					if (!n)
					{
						ms (u,unitid (u));
						ms (u,"has no");
						ms (u,itemnames[1][i]);
						mp (u);
						break;
					}

					u->items[i] -= n;
					u2->items[i] += n;

					ms (u,unitid (u));
					ms (u,"gives");
					ms (u,unitid (u2));
					mi (u,n);
					ms (u,itemnames[n != 1][i]);
					mp (u);

					if (u->faction != u2->faction)
					{
						ms (u2,unitid (u));
						ms (u2,"gives");
						ms (u2,unitid (u2));
						mi (u2,n);
						ms (u2,itemnames[n != 1][i]);
						mp (u2);
					}

					break;

				case K_PAY:
					i = geti ();

					if (!i)
					{
						n = geti ();
						n = min (n,u->items[I_SILVER]);

						if (!n)
						{
							ms (u,unitid (u));
							ms (u,"has no silver");
							mp (u);
							break;
						}

						u->items[I_SILVER] -= n;

						ms (u,unitid (u));
						ms (u,"discards");
						ms (u,"$");
						mi (u,n);
						mp (u);
						break;
					}

					u2 = findunit (u,i);

					if (!u2)
					{
						ms (u,"Unit");
						mi (u,i);
						ms (u,"not found");
						mp (u);
						break;
					}

					if (!accepts (u2,u))
					{
						ms (u,unitid (u2));
						ms (u,"does not accept gifts");
						mp (u);
						break;
					}

					n = geti ();
					n = min (n,u->items[I_SILVER]);

					if (!n)
					{
						ms (u,unitid (u));
						ms (u,"has no silver");
						mp (u);
						break;
					}

					u->items[I_SILVER] -= n;
					u2->items[I_SILVER] += n;

					ms (u,unitid (u));
					ms (u,"pays");
					ms (u,unitid (u2));
					ms (u,"$");
					mi (u,n);
					mp (u);

					if (u->faction != u2->faction)
					{
						ms (u2,unitid (u));
						ms (u2,"pays");
						ms (u2,unitid (u2));
						ms (u2,"$");
						mi (u2,n);
						mp (u2);
					}

					break;

				case K_TRANSFER:
					i = geti ();
					s = getstr ();

					if (findkeyword (s) == K_UNIT)
					{
						if (!i)
						{
							zerounit (u);

							ms (u,unitid (u));
							ms (u,"disbands");
							mp (u);
							break;
						}

						f = findfaction (i);

						if (!f)
						{
							ms (u,"Faction");
							mi (u,i);
							ms (u,"not found");
							mp (u);
							break;
						}

						forunit (u2)
							if (u2->faction == f && cansee (u->faction,u2))
								break;

						if (!u2)
						{
							ms (u,factionid (f));
							ms (u,"has no units available to accept transfer");
							mp (u);
							break;
						}

						if (!accepts (u2,u))
						{
							ms (u,factionid (f));
							ms (u,"does not accept transfer of");
							ms (u,unitid (u));
							mp (u);
							break;
						}

						if (f->type != F_MAGIC)
						{
							ms (u,factionid (f));
							ms (u,"may not accept magicians");
							mp (u);
							break;
						}

						u->faction = f;
						break;
					}

					n = atoip (s);
					n = min (n,u->number);

					if (n == 0)
					{
						ms (u,unitid (u));
						ms (u,"has no people");
						mp (u);
						break;
					}

					if (!i)
					{
						k = u->number - n;

						for (i = 0; i != NSKILLS; i++)
						{
							j = distribute (u->number,k,u->skills[i]);
							u2->skills[i] += u->skills[i] - j;
							u->skills[i] = j;
						}

						u->number = k;

						if (k == 0)
							memset (u->spells,0,sizeof u->spells);

						ms (u,unitid (u));
						ms (u,"disbands");

						if (k)
							mi (u,n);

						mp (u);
						break;
					}

					u2 = findunit (u,i);

					if (!u2)
					{
						ms (u,"Unit");
						mi (u,i);
						ms (u,"not found");
						mp (u);
						break;
					}

					if (u->skills[SK_MAGIC] || u2->skills[SK_MAGIC])
					{
						ms (u,"Cannot transfer to or from a magician unit");
						mp (u);
						break;
					}

					k = u->number - n;

					for (i = 0; i != NSKILLS; i++)
					{
						j = distribute (u->number,k,u->skills[i]);
						u2->skills[i] += u->skills[i] - j;
						u->skills[i] = j;
					}

					u->number = k;
					u2->number += n;

					ms (u,unitid (u));
					ms (u,"transfers");

					if (k)
						mi (u,n);

					ms (u,"to");
					ms (u,unitid (u2));
					mp (u);

					if (u->faction != u2->faction)
					{
						ms (u,unitid (u));
						ms (u,"transfers");

						if (k)
							mi (u,n);

						ms (u,"to");
						ms (u,unitid (u2));
						mp (u);
					}

					break;
			}

				// Pillaging

		n = 0;
		orders = 0;
		zerotemp ();

		forunit (u)
			for (S = u->commands; S; S = S->next)
				if (igetkeyword (S->s) == K_PILLAGE)
				{
					if (effskill (u,SK_COMBAT) == 0)
					{
						ms (u,unitid (u));
						ms (u,"is not combat trained");
						mp (u);
						break;
					}

					if ((u2 = guardagainst (u)) != 0)
					{
						ms (u,unitid (u2));
						ms (u,"does not permit");
						ms (u,unitid (u));
						ms (u,"to pillage");
						ms (u,regionnames[r]);
						mp (u);
						break;
					}

					O = cmalloc (sizeof (order));
					O->unit = u;
					O->n = u->number;
					addlist (&orders,O);

					n += u->number;
					break;
				}

		if (n < 200)
		{
			forfaction (f)
				foroder (O)
					if (O->unit->faction == f)
					{
						fms (f,"Insufficient forces to pillage");
						fms (f,regionnames[r]);
						fmp (f);
						break;
					}
		}
		else
		{
			while (taxqty[r])
			{
				O = randomorder (n);

				O->unit->items[I_SILVER] += 2;
				O->unit->temp += 2;

				taxqty[r]--;
			}

			recruitqty[r] /= 2;
			entertainqty[r] /= 2;
			workqty[r] /= 2;

			if (terrain[r] == T_CITY || terrain[r] == T_TOWN)
				fori (i,NITEMS)
					itemqty[r][i] /= 2;

			fororder
			{
				u = O->unit;

				ms (u,unitid (u));
				ms (u,"collects");
				ms (u,itodollar (u->temp));
				ms (u,"pillaging");
				mp (u);
			}
		}

		freelist (orders);

				// Taxation

		n = 0;
		orders = 0;
		zerotemp ();

		forunit (u)
			for (S = u->commands; S; S = S->next)
				if (igetkeyword (S->s) == K_TAX)
				{
					if (effskill (u,SK_COMBAT) == 0)
					{
						ms (u,unitid (u));
						ms (u,"is not combat trained");
						mp (u);
						break;
					}

					if ((u2 = guardagainst (u)) != 0)
					{
						ms (u,unitid (u2));
						ms (u,"does not permit");
						ms (u,unitid (u));
						ms (u,"to collect taxes in");
						ms (u,regionnames[r]);
						mp (u);
						break;
					}

					O = cmalloc (sizeof (order));
					O->unit = u;
					O->n = u->number * 200;
					addlist (&orders,O);

					n += u->number * 200;
					break;
				}

		m = taxqty[r];

		while (m && n)
		{
			O = randomorder (n);

			O->unit->items[I_SILVER]++;
			O->unit->temp++;

			m--;
			n--;
		}

		fororder
		{
			u = O->unit;

			ms (u,unitid (u));
			ms (u,"collects");
			ms (u,itodollar (u->temp));
			ms (u,"in taxes");
			mp (u);
		}

		freelist (orders);

				// GUARD 1 orders

		forunit (u)
			forcommand (u,S)
			{
				case K_GUARD:
					if (geti ())
						u->guard = 1;

					break;
			}

				// Selling

		fori (i,NITEMS)
		{
			n = 0;
			orders = 0;
			zerotemp ();

			forunit (u)
				for (S = u->commands; S; S = S->next)
					if (igetkeyword (S->s) == K_SELL)
					{
						j = geti ();

						if (getitem () != i)
							continue;

						j = min (j,u->items[i]);

						O = cmalloc (sizeof (order));
						O->unit = u;
						O->n = j;
						addlist (&orders,O);

						n += j;
						break;
					}

			m = itemqty[r][i];

			while (m && n)
			{
				O = randomorder (n);

				O->unit->items[i]--;
				O->unit->items[I_SILVER] += sellprice[r][i];
				O->unit->temp++;

				m--;
				n--;
			}

			fororder
			{
				u = O->unit;

				ms (u,unitid (u));
				ms (u,"sells");
				mi (u,u->temp);
				ms (u,itemnames[u->temp != 1][i]);

				if (u->temp)
				{
					ms (u,"for");
					ms (u,itodollar (u->temp) * sellprice[r][i]);
				}

				mp (u);
			}

			freelist (orders);
		}

				// Buying

		fori (i,NITEMS)
		{
			n = 0;
			orders = 0;
			zerotemp ();

			forunit (u)
				for (S = u->commands; S; S = S->next)
					if (igetkeyword (S->s) == K_BUY)
					{
						j = geti ();

						if (getitem () != i)
							continue;

						j = min (j,u->items[I_SILVER] / buyprice[r][i]);

						O = cmalloc (sizeof (order));
						O->unit = u;
						O->n = j;
						addlist (&orders,O);

						n += j;
						break;
					}

			m = itemqty[r][i] * 10;

			while (m && n)
			{
				O = randomorder (n);

				O->unit->items[i]++;
				O->unit->items[I_SILVER] -= buyprice[r][i];
				O->unit->temp++;

				m--;
				n--;
			}

			fororder
			{
				u = O->unit;

				ms (u,unitid (u));
				ms (u,"buys");
				mi (u,u->temp);
				ms (u,itemnames[u->temp != 1][i]);

				if (u->temp)
				{
					ms (u,"for");
					ms (u,itodollar (u->temp) * buyprice[r][i]);
				}

				mp (u);
			}

			freelist (orders);
		}

				// Recruiting

		n = 0;
		orders = 0;
		zerotemp ();

		forunit (u)
			for (S = u->commands; S; S = S->next)
				if (igetkeyword (S->s) == K_RECRUIT)
				{
					if (u->skills[SK_MAGIC])
					{
						ms (u,"Cannot recruit into a magician unit");
						mp (u);
						break;
					}

					i = geti ();
					i = min (i,u->items[I_SILVER]);

					O = cmalloc (sizeof (order));
					O->unit = u;
					O->n = i;
					addlist (&orders,O);

					n += i;
					break;
				}

		m = recruitqty[r];

		while (m && n)
		{
			O = randomorder (n);

			O->unit->number++;
			O->unit->items[I_SILVER] -= recruitprice[r];
			O->unit->temp++;

			m--;
			n--;
		}

		fororder
		{
			u = O->unit;

			ms (u,unitid (u));
			ms (u,"recruits");
			mi (u,u->temp);
			mp (u);
		}

		freelist (orders);
	}

	puts ("Processing faction removal...");

	forregion
		forunit (u)
			forcommand (u,S)
			{
				case K_QUIT:
					destroyfaction (u->faction);
					break;
			}

	forfaction (f)
		if (turn - f->lastcommands > ORDERGAP)
			destroyfaction (f);

	removeempty ();
	removenullfactions ();

	puts ("Setting full month orders...");

	forregion
		forunit (u)
		{
			u->thiscommand = cstrdup (u->lastcommand);

			forcommand (u,S)
			{
				case K_ADVANCE:
				case K_BUILD:
				case K_CAST:
				case K_ENTERTAIN:
				case K_MOVE:
				case K_PRODUCE:
				case K_RESEARCH:
				case K_SAIL:
				case K_STUDY:
				case K_TEACH:
				case K_WORK:
					freestr (u->thiscommand);
					u->thiscommand = cstrdup (S->s);
					break;
			}

			switch (igetkeyword (u->thiscommand))
			{
				case K_ADVANCE:
				case K_MOVE:
				case K_SAIL:
					break;

				default:
					freestr (u->lastcommand);
					u->lastcommand = cstrdup (u->thiscommand);
					strlwr (u->lastcommand);
			}
		}

	puts ("Processing movement...");

	forregion
		forunit (u)
		{
			u->mode = -1;

			fori (mp,8)
				u->move[mp] = -1;

			switch (igetkeyword (u->thiscommand))
			{
				case K_ADVANCE:
					u->advancing = 1;

				case K_MOVE:
					if (canfly (u))
					{
						u->mode = M_FLY;
						u->mp = 8;
					}
					else if (canride (u))
					{
						u->mode = M_RIDE;
						u->mp = 4;
					}
					else if (canwalk (u))
					{
						u->mode = M_WALK;
						u->mp = 2;
					}
					else
					{
						ms (u,unitid (u));
						ms (u,"is too heavily loaded to move");
						mp (u);
						break;
					}

					switch ((turn - 1) % 12)
					{
						case 0:
						case 1:
						case 11:
						case 12:
							u->mp /= 2;
					}

					fori (mp,8)
					{
						s = getstr ();

						if (!s[0])
							break;

						u->move[mp] = finddirection (s);

						if (u->move[mp] < 0)
						{
							ms (u,strupr (s));
							ms (u,"is not a valid direction");
							mp (u);
							break;
						}
					}
			}
		}

	fori (mp,8)
	{
		forregion
			forunit (u)
			{
				u->moveto = -1;

				if (u->mp[mp] < 0)
					u->mode = -1;

				if (u->mode < 0)
					continue;

				r2 = adjacent (u->mp[mp]);

				if (r2 < 0)
				{
					ms (u,unitid (u));
					ms (u,"cannot move");
					ms (u,directionnames[u->mp[mp]]);
					ms (u,"from");
					ms (u,regionnames[r]);
					ms (u,"as the climate becomes too extreme");
					mp (u);

					u->mode = -1;
					break;
				}

				if (terrain[r2] == T_OCEAN)
				{
					ms (u,unitid (u));
					ms (u,"cannot move into the ocean");
					ms (u,directionnames[u->mp[mp]]);
					ms (u,"of");
					ms (u,regionnames[r]);
					mp (u);

					u->mode = -1;
					break;
				}

				if (u->mode != M_FLY && terrain[r] == T_OCEAN)
				{
					ms (u,unitid (u));
					ms (u,"cannot disembark in the ocean");
					mp (u);

					u->mode = -1;
					break;
				}

				leave (u);
				u->moveto = r2;
			}

		forregion
			for (u = units[r]; u;)
			{
				u2 = u->next;

				if (u->moveto >= 0)
				{
					if (!u->advancing)
						for (u3 = units[u->moveto]; u3; u3 = u3->next)
							if (hasattitude (u3->faction,u->faction,A_UNFRIENDLY) &&
								!hasattitude (u->faction,u3->faction,A_HOSTILE) &&
								 cansee (u3->faction,u) == 2)
							{
					removelist (&units[r],u);
					addunit (u->moveto,u);
					u->moveto = -1;
				}

				u = u2;
			}
	}

	puts ("Processing production...");

	forregion
	{
				// Entertainment

		n = 0;
		orders = 0;
		zerotemp ();

		forunit (u)
			if (igetkeyword (u->thiscommand) == K_ENTERTAIN)
			{
				if (effskill (u,SK_ENTERTAINMENT) == 0)
				{
					ms (u,unitid (u));
					ms (u,"has no skill in entertainment");
					mp (u);
					continue;
				}

				O = cmalloc (sizeof (order));
				O->unit = u;
				O->n = u->number * effskill (u,SK_ENTERTAINMENT) * entertainprice[r];
				addlist (&orders,O);

				n += O->n;
			}

		m = entertainqty[r] * entertainprice[r];

		while (m && n)
		{
			O = randomorder (n);

			O->unit->items[I_SILVER]++;
			O->unit->temp++;

			m--;
			n--;
		}

		fororder
		{
			u = O->unit;

			ms (u,unitid (u));
			ms (u,"earns");
			ms (u,itodollar (u->temp));
			ms (u,"entertaining.");
			mp (u);
		}

		freelist (orders);

				// Work

		n = 0;
		orders = 0;
		zerotemp ();

		forunit (u)
			if (igetkeyword (u->thiscommand) == K_WORK)
			{
				O = cmalloc (sizeof (order));
				O->unit = u;
				O->n = u->number * workprice[r];
				addlist (&orders,O);

				n += O->n;
			}

		m = workqty[r] * workprice[r];

		while (m && n)
		{
			O = randomorder (n);

			O->unit->items[I_SILVER]++;
			O->unit->temp++;

			m--;
			n--;
		}

		fororder
		{
			u = O->unit;

			ms (u,unitid (u));
			ms (u,"earns");
			ms (u,itodollar (u->temp));
			ms (u,"working");
			mp (u);
		}

		freelist (orders);

				// Research

		forunit (u)
			if (igetkeyword (u->thiscommand) == K_RESEARCH)
			{
				l = effskill (u,SK_MAGIC);

				if (l < 2)
				{
					ms (u,unitid (u));
					ms (u,"has insufficient skill in magic to perform research");
					mp (u);
					continue;
				}

				if (u->items[I_SILVER] < 500)
				{
					ms (u,unitid (u));
					ms (u,"has insufficient funds to perform research");
					mp (u);
					continue;
				}

				u->items[I_SILVER] -= 500;

				k = (getkeyword () == K_COMBAT);
				i = geti ();

				if (i != 0 && i < l)
					i = j;

				j = 0;

				fori (i,NSPELLS)
					if (spelllevel[i] == l &&
						 xiscombatspell (i) == k &&
						 !u->spells[i])
					{
						j = 1;
						break;
					}

				if (j)
				{
					DORESEARCH:

					do
						i = rnd () % NSPELLS;
					while (!(spelllevel[i] == l &&
								xiscombatspell (i) &&
								!u->spells[i]);

					if (!u->faction->seendata[i])
						u->faction->showdata[i] = 1;

					ms (u,unitid (u));
					ms (u,"discovers the");
					ms (u,spellnames[i]);
					ms (u,"spell");
					mp (u);
					continue;
				}

				j = 0;

				fori (i,NSPELLS)
					if (spelllevel[i] == l &&
						 !u->spells[i])
					{
						j = 1;
						break;
					}

				if (!j)
				{
					ms (u,unitid (u));
					ms (u,"discovers that no more level");
					mi (u,l);
					ms (u,"spells exist");
					mp (u);
					continue;
				}

				k = 1 - k;
				goto DORESEARCH;
			}

				// Teaching

		zerotemp ();

		forunit (u)
			if (igetkeyword (u->thiscommand) == K_TEACH)
			{
				m = u->number * 10;

				l = 0;
				i = geti ();

				while (i != 0 && l != sizeof iv / sizeof (int))
				{
					iv[l++] = i;
					i = geti ();
				}

				fori (i,l)
				{
					u2 = iv[i];

					if (!u2)
					{
						ms (u,"Unit");
						ms (u,itobracket (iv[i]));
						ms (u,"not found");
						mp (u);
						continue;
					}

					if (!accepts (u2,u))
					{
						ms (u,unitid (u2));
						ms (u,"does not accept teaching");
						mp (u);
						continue;
					}

					k = igetkeyword (u2->thiscommand);

					if (k != K_STUDY || (k = getskill ()) < 0)
					{
						ms (u,unitid (u2));
						ms (u,"is not studying");
						mp (u);
						continue;
					}

					if (effskill (u,i) <= effskill (u2,i))
					{
						ms (u,unitid (u));
						ms (u,"cannot teach");
						ms (u,unitid (u2));
						mp (u);
						continue;
					}

					n = u2->number - u2->temp;
					n = min (n,m);

					if (n == 0)
						continue;

					u2->temp += n;
					m -= n;

					ms (u,unitid (u));
					ms (u,"teaches");
					ms (u,unitid (u2));
					ms (u,skillnames[k]);
					mp (u);

					if (u->faction != u2->faction)
					{
						ms (u2,unitid (u));
						ms (u2,"teaches");
						ms (u2,unitid (u2));
						ms (u2,skillnames[k]);
						mp (u2);
					}
				}

				// Studying

		forunit (u)
			if (igetkeyword (u->thiscommand) == K_STUDY)
			{
				s = getstr ();
				i = findskill (s);

				if (i < 0)
				{
					ms (u,"Skill");
					ms (u,strupr (s));
					ms (u,"not found");
					mp (u);
					continue;
				}

				n = u->number;
				n = min (n,u->items[I_SILVER] / studycost[i]);

				if (n == 0)
				{
					ms (u,unitid (u));
					ms (u,"has insufficient funds to study");
					ms (u,skillnames[i]);
					mp (u);
					continue;
				}

				u->skills[i] += n + u->temp;
				u->items[I_SILVER] -= n * studycost[i];

				ms (u,unitid (u));
				ms (u,"studies");
				ms (u,skillnames[i]);
				mp (u);
			}

				// Production

		fori (i,NNORMALITEMS)
			if (isprimary[i])
			{
				n = 0;
				orders = 0;
				zerotemp ();

				forunit (u)
					if (igetkeyword (u->thiscommand) == K_PRODUCE &&
						 getitem () == i)
					{
						k = effskill (u,itemskill[i]) * u->number;

						if (k == 0)
							goto NOSKILL;

						O = cmalloc (sizeof (order));
						O->unit = u;
						O->n = k;
						addlist (&orders,O);

						n += k;
					}

				m = itemqty[r];

				while (m && n)
				{
					O = randomorder (n);

					O->unit->items[i]++;
					O->unit->temp++;

					m--;
					n--;
				}

				fororder
				{
					u = O->unit;

					ms (u,unitid (u));
					ms (u,"produces");
					mi (u,u->temp);
					ms (u,itemnames[u->temp != 1][i]);
					mp (u);
				}

				freelist (orders);
			}
			else
				forunit (u)
					if (igetkeyword (u->thiscommand) == K_PRODUCE &&
						 getitem () == i)
					{
						k = effskill (u,itemskill[i]);

						if (i == I_PLATE_ARMOR)
							k /= 3;

						if (k == 0)
						{
							NOSKILL:

							ms (u,unitid (u));
							ms (u,"does not have the skill to produce");
							ms (u,itemnames[1][i]);
							mp (u);
							continue;
						}

						k *= u->number;
						k = min (k,u->items[rawmaterial[i]]);

						if (k == 0)
						{
							ms (u,unitid (u));
							ms (u,"does not have the material to produce");
							ms (u,itemnames[1][i]);
							mp (u);
							continue;
						}

						u->items[i] += k;
						u->items[rawmaterial[i]] -= k;

						ms (u,unitid (u));
						ms (u,"produces");
						mi (u,k);
						ms (u,itemnames[k != 1][i]);
						mp (u);
					}

				// Building

		if (terrain[r] == T_OCEAN)
			continue;

		forunit (u)
			if (igetkeyword (u->thiscommand) == K_BUILD)
			{
				s = getstr ();
				i = findobjecttype (s);

				if (i < 0)
					continue;

				if (effskill (u,objectskill[i]) == 0)
				{
					ms (u,unitid (u));
					ms (u,"does not have the skill");

					NOSTARTBUILD:
					ms (u,"to build a");
					ms (u,objecttypename[i]);
					mp (u);
					continue;
				}

				if (u->items[objectrawmaterial[i]] == 0)
				{
					ms (u,unitid (u));
					ms (u,"does not have the raw material");

					goto NOSTARTBUILD;
				}

				o = createobject ();

				o->alias = geti ();
				if (!o->alias)
					o->alias = geti ();

				o->type = i;
				o->remaining = objectcost[i];

				leave (u);
				u->in = o;
				u->owner = 1;

				goto DOBUILD;
			}

		forunit (u)
			if (igetkeyword (u->thiscommand) == K_BUILD)
			{
				s = getstr ();

				if (findobjecttype (s) >= 0)
					continue;

				o = findobject (atoi (s));

				if (o == 0)
				{
					ms (u,"Object");
					ms (u,strupr (s));
					ms (u,"not found");
					mp (u);
					continue;
				}

				if (o->remaining == 0)
				{
					if (isthe (o))
						ms (u,"The");

					ms (u,objectid (o));
					ms (u,"is complete");
					mp (u);
					continue;
				}

				n = effskill (u,objectskill[o->type]) * u->number;

				if (n == 0)
				{
					ms (u,unitid (u));
					ms (u,"does not have the skill");

					NOBUILD:
					ms (u,"to work on");

					if (isthe (o))
						ms (u,"the");

					ms (u,objectid (o));
					mp (u);
					continue;
				}

				n = min (n,objectrawmaterial[o->type]);

				if (n == 0)
				{
					ms (u,unitid (u));
					ms (u,"does not have the raw material");

					goto NOBUILD;
				}

				u2 = objectowner (o);

				if (u2 && !accepts (u2,u))
				{
					ms (u,unitid (u2));
					ms (u,"does not permit");
					ms (u,unitid (u));
					ms (u,"to work on");

					if (isthe (o))
						ms (u,"the");

					ms (u,objectid (o));
					mp (u);
					continue;
				}

				DOBUILD:

				n = min (n,o->remaining);
				o->remaining -= n;

				ms (u,unitid (u));
				ms (u,"adds");
				mi (u,n);
				ms (u,"to");

				if (isship (o))
					ms (u,"the");

				ms (u,objectid (o));
				mp (u);
			}
	}

	puts ("Processing demographics...");

	forregion
		forunit (u)
		{
			getsilver (u,u->number * MAINTENANCE);
			n = u->items[I_SILVER] / MAINTENANCE;

			if (u->number > n)
			{
				ms (u,unitid (u));

				if (n)
				{
					ms (u,"loses");
					mi (u,u->number - n);
					ms (u,"to starvation");
				}
				else
					ms (u,"starves to death");

				mp (u);

				for (i = 0; i != NSKILLS; i++)
					u->skills[i] = distribute (u->number,n,u->skills[i]);

				u->number = n;
			}

			u->items[I_SILVER] -= u->number * MAINTENANCE;
		}

	removeempty ();

	forfaction (f)
		if (turn - f->lastcommands == ORDERGAP)
		{
			fms (f,"Please send orders next turn if you wish to continue playing");
			fmp (f);
		}

	phrasev = cmalloc (nextphrasen * sizeof (char *));
	locatephrase (phrases);
}

void reports (void)
{
	struct FIND *fd;
	faction *f;

	mkdir ("reports");
	mkdir ("nreports");

	fd = findfirst ("reports/*.*",0);

	while (fd)
	{
		sprintf (buf,"reports/%s",fd->name);
		unlink (buf);
		fd = findnext ();
	}

	fd = findfirst ("nreports/*.*",0);

	while (fd)
	{
		sprintf (buf,"nreports/%s",fd->name);
		unlink (buf);
		fd = findnext ();
	}

	forfaction (f)
		report (f);

	cfopen ("send","w");
	puts ("Writing send file...");

	forfaction (f)
		if (strcmpl (f->addr,"n/a"))
		{
			fprintf (F,"mail %d.r\n",f->no);
			fprintf (F,"in%%\"%s\"\n",f->addr);
			fprintf (F,"Atlantis Report for %s\n",gamedate);
		}

	fclose (F);

	cfopen ("maillist","w");
	puts ("Writing maillist file...");

	for (f = factions; f; f = f->next)
		if (strcmpl (f->addr,"n/a"))
			fprintf (F,"%s\n",f->addr);

	fclose (F);
}

_cdecl main (void)
{
	puts ("Atlantis v2.0  " __DATE__ "\n"
			"Copyright 1993 by Russell Wallace.");

	rndno = time (0);

	F = fopen ("atlantis.dat","r");

	if (F)
	{
		readdata ();
		fclose (F);
	}
	else
		initworld ();

	turn++;
	sprintf (gamedate,"%s, Year %d",monthnames[(turn - 1) % 12],
											  ((turn - 1) / 12) + 1);

	cfopen ("/d/a","r");
	readcommands ();
	fclose (F);

	processcommands ();
	reports ();

	cfopen ("atlantis.dat","w");
	writedata ();
}


