# cc3k17

ChamberCrawler3000 (CC3k) is a simplified rogue-like (a genre of video game based upon the game Rogue -
http://en.wikipedia.org/wiki/Rogue_(video_game)

## Usage

```
make
./cc3k
```

## Game

### Commands

- `no`, `so`, `ea`, `we`, `ne`, `nw`, `se`, `sw`: moves the player in the specified direction
- `u <direction>`: uses the potion indicated by the direction (e.g. `no`, `so`, ...)
- `a <direction>`: attack the enemy in the specified direction, if the enemy is in the
  immediately specifed block
- `s`, `d`, `v`, `g`, `t`: specifies the race the player wishes to be when starting a game
- `r`: restarts the game

### Races

- Shade: 125 HP, 25 Atk, 25 Def
- Drow: 150 HP, 25 Atk, 15 Def, potions have effect magnified by 1.5
- Vampire: 50 HP, 25 Atk, 25 Def, gains 5 HP every attack and has no max HP
- Troll: 120 HP, 25 Atk, 15 Def, regains 5 HP every turn
- Goblin: 110 HP, 15 Atk, 20 Def, steal 5 gold from every slain enemy

### Hostile

- Human: 140 HP, 20 Atk, 20 def, drops 2 normal piles of gold
- Dwarf: 100 HP, 20 Atk, 30 Def, vampires are allergic and lose 5 HP rather than gain
- Elf: 140 HP, 30 Atk, 10 Def, gets two attacks against every race except drow
- Orcs: 180 HP, 30 Atk, 25 Def, does 50% more damage to goblins
- Merchant: 30 HP, 70 Atk, 5 Def, by default neutral, drops merchant hoard
- Dragon: 150 HP, 20 Atk, 20 Def, always guards a treasure hoard, doesn't move
- Halfling: 100 HP, 15 Atk, 20 Def, has a 50% chance to beguile character and cause them to miss

### Items

#### Potions

Positive Potions:
- Restore health (RH): restore up to 10 HP (cannot exceed maximum prescribed by race)
- Boost Atk (BA): increase ATK by 5
- Boost Def (BD): increase Def by 5

Negative Potions:
- Poison health (PH): lose up to 10 HP (cannot fall below 0 HP)
- Wound Atk (WA): decrease Atk by 5
- Wound Def (WD): decrease Def by 5

#### Treasure

Treasure in CC3k consists only of gold. Gold can be in several types of piles: small (value 1), normal
(value 2), merchant hoard (value 4), and dragon hoard (value 6). Recall, a dragon must always protect a
dragon hoard whenever it randomly spawns. A dragon hoard can only be picked up once the dragon guarding
it has been slain. Gold, regardless of type, is denoted by ‘G’ on the map. A merchant hoard is dropped
upon the death of a merchant.
