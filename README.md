# WorldSimulation_Console

The project was implemented for the needs of *Object programming* course.

The task was to implement a 2D virtual world simulator, visualised as a two-dimensional NxM grid. The simulation is filled with simple life forms, each with different behaviour depending on its species. Every organism occupies exactly one cell and each cell contains only one organism at the moment.
All actions are performed in turns. Some of them will move (random) during turn, and some will remain static. Order of moves is determined by the organism's initiative (Higher moves first)  and its age (Older move first). In case of collision of two organisms, the victory depends on the strength of the organisms (If the strength is the same, the encounter is won by the attacker).
The game also includes a Human, which is controlled by a player. We can move him with arrows. The Human also possesses a special ability activated with the Z key. 
The program window includes a text box for displaying messages about the results of actions. It is located below the grid.

<p align="center"><b> Description of organisms </b></p>

**Human class**
| Strength | Initiative | Representation | Action | Collision |
| ----------- | ----------- | ------------ | --------- | ----------- |
|      5       |       4      | H | Human moves in same way as animals, but the direction of his movement corresponds to the arrow keys pressed by the player. For example, if the player presses the left arrow key, the human (in his turn) will move to the cell to the left of his initial position.  | Human possesses a special ability, which can be activated by a separate key on the keyboard. After activation, this ability kills all the animals in one cell radius from human |

**Animal classes**
| Animal | Strength | Initiative | Representation | Action | Collision |
| ------ | ----------- | ----------- | ------------ | --------- | ----------- |
| Wolf |      9       |       5      | w | Default for Animal | Default for Animal |
| Sheep |      4       |       4      | s | Default for Animal | Default for Animal |
| Fox |      3       |       7      | f | Will never move to a cell occupied by a stronger organism | Default for Animal |
| Turtle |      2       |       1      | t | Has 75% chance to stay in the same place | Reflects attacks of animal with strength less than 5. Attacker will return to the previous cell |
| Antelope |      4       |       4      | a | Has wider range of movement - 2 fields instead of 1 | Has 50% chance to escape from fight. In such case it moves to a free neighboring cell |
| Cyber-Sheep |      11       |       4      | c | Default for Animal | Eats Sosnowsky's hogweed |

**Plant classes**

