

/*
b.	Example Character: Cassie
    i.	Name – Cassie Mav
    1.	Title – Scrappy Space Lizard / Future Queen
    2.	Canon – Starbuster
    3.	Sub-Canon – -
ii.	Skills
    1.	Rocket Punch- Melee, RNG 1 Adjacent. Tension 2, Cassie’s default grounded combat skill. Also available during Airtime. Believe it or not, the non-metal hand hurts just as much.
    2.	360 Aiming – Ranged, Range 4, Tension 1, A weak but versatile combat skill. Sometimes, you should just shoot your troubles away.
    3.	Grappling Hook – x.
    4.	Grapple Attack – x. 
    5.	Guided Missile – x.
    6.	YEET
    7.	Charge Dash
iii.	Perks 
    1.	Pressure Suit – Improved movement in space.
    2.	Underwater Excellence – Most of your stats are unchanged underwater. You can also swim freely. (You can still drown.)
    3.	Extra Limbs (Tail) – Your tail can be partially manipulated to affect objects.
    4. 
iv.	Traits
    1.	Drinky Drinky  – Certain status-changing items last 3 extra turns. But you cannot drop or sell them from your inventory.
    2.	Once More – If you Tension is not already maxed, attacks that would otherwise Break you set your Tension to max instead. Only works once per battle. Can be refreshed with a full heal.
c.	Combat Stats
i.	FP: 6
ii.	AP: 3
iii.	PP: 12
iv.	MV: 4
v.	RM: 1
vi.	RR: 1
d.	Popularity: 69
e.	Notoriety: 2729
f.	Elements: 
i.	Affinity: Water
ii.	Resistance
1.	Wood - +
2.	Fire -
3.	Earth -
4.	Metal -1
5.	Water+1


*/


typedef struct {
	char displayName[200];
    int titleID;
    int canonID;
    int subCanonIDs[5];
    int traits[100];
    int perks[100];
    int items[5];
    int entities[200];
    //Canons
    // Notoriety
	// TemporaryStatus tempStatuses[MAX_TEMP_STATUSES];
	//TemporaryStatus tempStatuses[10];
} Character;