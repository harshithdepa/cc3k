## Reading in dragon/hoard pairs
Dragon/hoard pairings must be adjacent

# Grid generation
## Type
### Treasure
- Normal: 0 1 2 3 4
- Small: 5 6
- Dragon: 7
- Merchant: 
### Potion
Equal chance of each kind of potion
- RH: 0
- BA: 1
- BD: 2
- PH: 3
- WA: 4
- WD: 5
### Enemy
- Human: 0 1 2 3
- Dwarf: 4 5 6
- Halfling: 7 8 9 10 11
- Elf: 12 13
- Orc: 14 15
- Merchant: 16 17
## Location
### Player
1. Pick a random chamber
2. Pick a random tile within chamber
2. Set location of Player to that tile
### Stairway
1. Pick a random chamber that the Player is not located in
2. Pick a random tile within chamber
3. Set location of Stairs to that tile
### Potion
1. Pick a random chamber
2. Pick a random tile within chamber
3. Set location of Potion to that tile
### Treasure 
#### Hoard
Treasure hoards will be given locations first.
1. Find a random tile that has at least one free adjacent tile
2. Spawn treasure hoard on that location
3. Spawn dragon on adjacent tile
4. Pair dragon and hoard with each other
#### Other
1. Pick a random chamber
2. Pick a random tile within chamber
2. Set location of Potion to that tile
### Enemy
1. Pick a random chamber
2. Pick a random tile within chamber
2. Set location of Enemy to that tile

# Movement
## Player

## Enemy
1. Inspect all neighbouring tiles
2. If there are no empty adjacent tiles
- Then do nothing
3. Else
- put valid directions into an n-sized array of direction enums
- generate a number between 0 and n-1
- execute move(arr[num]);
