# Coursework of Advanced Game Development

This is a C++ game demo based on SFML. 

W, A, S, D: Move around;
Space: Chop wood;
Shift shoot fire;
ESC: Pause.

This demo implements the following features:

## 1)Entity Component System Architecture
### Big Array:
The ‘BigArray’ function is implemented in ‘Game’ class. It iterates over all systems and for each system, it iterates over all entities. If an entity has not been deleted and can be processed by the system, then the system will update that entity.

## 2)Game Programming Patterns

### 1.Flyweight

In the Flyweight pattern, the intrinsic state represents the information shared among different objects. The ‘TileIntrinsic’ (In TileIntrinsic.h) class encapsulates shared properties - texture and type, for tiles in a game map implementing the Flyweight pattern. Each ‘TileIntrinsic’ object is unique to a tile type (like CORRIDOR or WALL) and its texture. A tile’s texture is retrieved from a file, and the type is set at instantiation. These intrinsic properties are shared amongst many ‘Tile’ objects, significantly reducing memory usage. A tile accesses the shared properties via ‘getTexture()’ and ‘getType()’ methods, ensuring the appropriate texture and type are rendered in the game.

### 2.Observer

The Observer pattern is implemented by the ‘Observer’ (In Observer.h) and ‘AchievementManager’ (In AchievementManager.h) classes. The abstract ‘Observer’ class contains a pure virtual function ‘onNotify’, which every concrete ‘Observer’ must implement. A ‘notify’ function is defined both in ‘Game’ class and ‘Player’ class, then called in ‘Player::createFire’ and ‘Game::handlePotionCollision’.

In our code, the ‘AchievementManager’ is a concrete observer. It's notified when a player action occurs, such as shouting or getting a potion. It tracks these actions by incrementing ‘shoutCount’ and ‘potionCount’. The ‘onNotify’ function within the ‘AchievementManager’ handles the events. When a player has shouted 5 times or collected all the potions, it displays a message. The reset function resets the counts so that new rounds of achievements can be tracked. 

### 3.Service Locator

This pattern is implemented in ‘Audio’ file and ‘Locator’ file, containing following classes.

‘class Audio’: This is an abstract base class that defines the interface for audio services. It contains two pure virtual functions ‘playAudio’ and ‘stopAudio’ that accept ‘AUDIO_TYPE’ as a parameter.

‘class NullAudio’: a derived class from Audio that provides a Null Object implementation. The Null Object pattern provides a non-doing object of the class to avoid null references. Here, it provides empty ‘playAudio’ and ‘stopAudio’ methods that do nothing.

‘class ConsoleAudio’: a derived class from Audio that implements the ‘playAudio’ and ‘stopAudio’ methods. It uses the SFML library's ‘sf::Sound’ and ‘sf::SoundBuffer’ objects for different types of audio.

‘class Locator’: It provides a ‘getAudio’ method to retrieve the current audio service and a provide method to set a new audio service. ‘Locator’ class is initialized with a ‘NullAudio’ service to avoid null references. ‘getAudio’ returns a reference to the current audio service.

Then ‘Locator::getAudio().playAudio(AUDIO_TYPE)’ is called in ‘Player::createFire’, ‘Game::handlePotion-Collision’ and ‘Game::handleLogCollision’.

## 3)Other Features

### 1.Command

There are three main components in our code related to the Command Pattern: ‘KeyboardInputHandler’, ‘InputHandler’, and ‘PlayerInputHandler’ (all in ‘InputHandler.h’). The ‘KeyboardInputHandler’ is a utility class that abstracts the handling of keyboard events, specifically the pressing and releasing of the Escape key.

The ‘InputHandler’ class contains the main functionality of the Command pattern. It has a ‘handleInput()’ function that returns a Command object based on the state of the keyboard input. The ‘PauseCommand’ is instantiated and returned when the Escape key is pressed. This allows the main game loop to execute the returned command. The ‘PlayerInputHandler’ class handles player-specific input. It defines a set of commands (move right/left/up/down, attack, shout) and binds each command to a specific keyboard key. The handler's ‘handleInput()’ function checks the current keyboard state and returns a list of commands corresponding to the currently pressed keys. This class also implements the input mode switching feature using the Enter key.

‘handleInput()’ function is used to check the current keyboard state and generate the appropriate commands. The Command pattern is implemented by having the ‘handleInput()’ functions return Command objects that encapsulate the requested actions.

### 2.Collision Callbacks

Our ‘Game’ class employs a collision callback system which manages interactions between different entities (like ‘player’, ‘logs’, and ‘potions’) within the game. To set up the callback mechanism, we make ‘Game’ class maintains a ‘std::map<EntityType, CollisionCallback> collisionCallbacks’; mapping an ‘EntityType’ to a corresponding callback function (‘CollisionCallback’). During initialization, the callback functions for handling collisions with different types of entities (e.g., potion or log) are bound and stored in the map.

The ‘player’ entity managed by the ‘Player’ class, plays a vital role in this process. The ‘Player’ class comprises various components such as ‘PositionComponent’ and ‘HealthComponent’, defining player attributes such as position and health, also, the bool ‘Player::collidesWith(std::shared_ptr<Entity> otherEntity)’ function detects if the player entity collides with another game entity.

In the ‘Game::update’ method, the game checks for any collision between the player and other entities. If a collision is detected, it fetches the appropriate collision callback function for that entity type from the collisionCallbacks map and invokes it, which modifies the game state as necessary.

So, our Game class orchestrates the interaction logic between different entities in the game, while the ‘Player’ class offers the necessary structure to handle the player's actions, including collision detection and response.
