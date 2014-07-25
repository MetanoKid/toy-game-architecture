# Toy Game Architectures

Videogames are one of the most beautiful and engaging kinds of software in the world. Not only they are fun to be played but they are fun to be developed.

Like every other software project, videogames divide their complexity into several subsystems to implement different functionalities. To name a few, these subsystems include *graphics*, *user input*, *audio*, *physics*, *net*, *GUI*, *AI* and *scripting*. If these subsystems are the limbs of the videogame, we're still missing the body to connect them altogether. We could, arguably, call that the *logic*.

Over the last years game architectures have evolved in different and varying ways, and they still do. We could separate them into two important **variants**:

- Deep entity hierarchies which use extensive inheritance.
- Flat entity hierarchies which use composition.

Game developers (and even non-game developers) seem to have agreed that the former is best used with caution, whenever we know the game design is really closed and won't change, or if it's a small project. They've also agreed that the latter is the best way of adapting to the constantly evolving nature of videogames, also allowing for behavior reuse. In fact, commercial game engines use this approach.

After attending a Master's Degree in Game Development at the Complutense University of Madrid, absorb every piece of knowledge from its teachers (some of which were professionals in the industry), read some literature about the topic and, most importantly, getting dirty with C++, I've decided to create this project.

This personal project aims for two **goals**:

- Implement a basic component-based game architecture taking as a reference the one learned during my Master's Degree.

- Evolve said architecture combining ideas from books and professional developers, adding different programming patterns and, with that, create a better architecture.

I'll try to achieve those goals by creating three variants of game architectures. All of them will be **single-threaded**, **component-based**, **data-driven** game architectures.

## Classic game architecture

**Completed**

Within this approach every entity is basically a *container of components*. Entities don't define behavior other than managing components and there's no entity hierarchy; instead, they relay on [duck typing](http://en.wikipedia.org/wiki/Duck_typing "Duck typing on Wikipedia").

Components are the ones to define behavior and have a flat hierarchy. It's usual to at least have one component to communicate with each subsystem (i.e. a graphics component to tell the Graphics Engine which model represents an entity and where in the space it is). These components try to be as reusable as possible, so we can plug them into different entities easily.

Entities communicate with each other by sending messages, which are processed by their components to execute behaviors. Different components may be interested in the same kind of message, abstracting *who* will process *what*. Imagine we have a game in which we want to draw models in the universe, and those models will move. A *graphics* component would be interested in `SetPosition` messages to tell the Graphics Engine to move it. Let's say that's an online game; we'd have a *net* component who's interested in the same message to send its properties over the net.

Also, we won't only explore a component-based game architecture but a data-driven one. Entity types are defined in a `blueprints` file and specific entity instances are defined in a `level` file.

Example `blueprints` file:

    EntityType1 ComponentName1 ComponentName2
    EntityType2 ComponentName3 ComponentName1

Example `level` file:

    Entity 1 : EntityType1
        position 0 0 0
        orientation 1
        model Entity with a long name and some spaces.fbx
    
    Entity 2: EntityType2
        model Model.fbx
        perception_type Alpha type
        valid true

These formats are arbitrary selected and used to prevent dependencies with external libraries to process XML or JSON. So, for the sake of simplicity, there are parsers for these files which aren't interesting for the goal of the project.

## Evolved game architecture

**To be started**

The first approach has the basics of a component-based game architecture. However, there are some parts of it that could be improved. This approach will try to evolve that base and create a better game architecture.

Entities won't exist as presented. They won't be a container of components, but just a number. That way, components will know what entity they live in by having that identifier.

Messaging changes as well. Components will register themselves in a *publish / subscribe topic* so there's no need to ask components if they are interested in a specific message. Messages will be managed through an *object pool*, trying to minimize the possible overhead of instantiating and destroying messages each frame.

Although I said level processing was out of the goal of the project, it will be evolved as well. Within the classic version we couldn't have properties named the same way for different components. Let's illustrate this.

Let's say we have a *light* component which knows which kind of light will be used, and we have a *perception* component which knows which type of perception is used. With the first approach we'd have to write:

    EntityName : EntityType
        light_type Directional
        perception_type Soldier

In this second approach we want to write this:

    EntityName : EntityType
        Light
            type Directional
        Perception
            type Soldier

Using this new way of defining levels we might argue that `blueprints` aren't necessary anymore and thus entity components can be inferred from level data.

## Frankenstein game architecture

**To be studied**

After we've created the evolved version of the game architecture there are still some things to be explored:

- The ability of creating entity `archetypes` so we could define *data-hierarchies*.

- One of my teachers at my Master's Degree once said: *There's no better message than a call to a function*. Within this approach, components will be able to access other components and won't be any messaging system to be used. Components may define a *dependency injection* section in their life cycle so they can receive references to those components. It creates coupling, but it's a nice feature to be explored.

- In game development we should always try to minimize the amount of time that takes to perform empty operations. If none of the entities in the level were active, that should take zero time to perform a tick. The same goes for individual components: if we want to turn off every component in an entity, processing the tick for the components should take zero time.

As the project evolves I might add or remove some of the features.

## Cloning and running

This project is developed using Visual Studio 2012 and a solution file is included in it. To get working, you'll have to:

- Clone the repository:

        git clone https://github.com/MetanoKid/toy-game-architecture.git

- Open `ToyGameArchitecture.sln` in Visual Studio 2012.
- If you want to launch it right from the IDE:
    - Right click the `ToyGameArchitecture` project.
    - Go to Properties.
    - Under Configuration properties choose Debugging.
    - Set Working directory to `$(OutDir)`.
- Compile solution.
- Execute.