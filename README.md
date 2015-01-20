# Toy Game Architectures

Status: **Completed (but always trying to improve)**

Videogames are one of the most beautiful and engaging kinds of software in the world. Not only they are fun to be played but they are fun to be developed.

Like every other software project, videogames divide their complexity into several subsystems to implement different functionalities. To name a few, these subsystems include *graphics*, *user input*, *audio*, *physics*, *net*, *GUI*, *AI*, *scripting* and *game-specific logic*. If these subsystems are the limbs of the videogame, we're still missing the body to connect them altogether. We could, arguably, call that the *logic*.

Over the last years game architectures have evolved in different and varying ways, and they still do. We could separate them into two main **categories**:

- Deep entity hierarchies which use extensive inheritance.
- Flat entity hierarchies which use composition.

Game developers (and other software engineers) seem to have agreed that the former is best used with caution, whenever we know the game design is really closed and won't change, or if it's a small project. They've also agreed that the latter is the best way of adapting to the constantly evolving nature of videogames, also allowing for behavior reuse. In fact, many commercial game engines use this approach.

After attending a Master's Degree in Game Development at the Complutense University of Madrid, absorb every piece of knowledge from its teachers (some of which were professionals in the industry), read some literature about the topic and getting dirty with C++, I've decided to create this project.

This personal project aims for two **goals**:

- Implement a basic component-based game architecture taking as a reference the one learned during my Master's Degree.

- Evolve said architecture combining ideas from books and professional developers, adding different design patterns and, with that, aim to create a better architecture.

I'll try to achieve those goals by creating three variants of game architectures. All of them will be **single-threaded**, **component-based**, **data-driven** game architectures.

## Classic game architecture

Status: **Completed**

We'll start the project with an approach in which every entity is basically a *container of components*. Entities don't define behavior other than managing components and there's no entity hierarchies; instead, they rely on [duck typing](http://en.wikipedia.org/wiki/Duck_typing "Duck typing on Wikipedia").

Components are the ones to define behavior and have a flat hierarchy. It's usual to have at least one component to communicate with each subsystem (i.e. a graphics component to tell the Graphics Engine which model represents an entity and what's its animation). These components try to be as reusable as possible, so we can plug them into different entities easily.

Entities communicate with each other by sending messages, which are processed by their components to execute behaviors. Different components may be interested in the same kind of message, abstracting *who* will process *what*. Imagine we have a game in which we want to draw models in the universe, and those models will move. A *graphics* component would be interested in `SetPosition` messages to tell the Graphics Engine to move it. Let's say it's also an online game; we'd have a *net* component who's interested in the same message to send its properties to a server. The sender of this kind of message doesn't know who's processing it, decoupling components.

Also, we won't only explore a component-based game architecture but a data-driven one. Entity types are defined in a `blueprints` file and specific entity instances are defined in a `level` file. When a level is created, entities are built in two steps: firstly they are all structure, and their components are instantiated out of the `blueprints` definitions; lastly they are fed some data, which is the one provided in the level file.

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

These formats are arbitrarily selected and used to prevent dependencies with external libraries to process XML or JSON. So, for the sake of simplicity, parsers for these files are also provided and aren't interesting for the goal of the project.

## Evolved game architecture

Status: **Completed**

The first approach had the basics of a component-based game architecture. However, there are some parts of it that could be improved. This approach will try to evolve that base and create a better game architecture.

Entities won't exist as presented. They won't be a container of components, but just a number. That way, components will know what entity they live in by having that identifier. Of course, since entities don't exist as such anymore someone has to manage components, and that will be the `Level` itself. This introduces a future lack: we don't have a place to set common data like position or other stuff. We'd have to use components for that.

Messaging changes as well. Components will register themselves in a *publish / subscribe topic* so there's no need to ask components if they are interested in a specific message.

Messages will be managed through an *object pool*, trying to minimize the possible overhead of instantiating and destroying messages each frame and the possible fragmentation it causes. Also, the amount of messages that should be created for the pool is also provided in a data file. An example would be:

    CSetPosition 10
    CTurnOn 2

Since we're aiming for a data-driven architecture, we'll also create a *Config file* to define some global properties which are interesting for parts of the architecture. An example of the *Config file* would be:

    blueprints blueprints.txt
    level Level_Evolved.txt
    messages MessagePool.txt
    controlled_delta_time 0.16

Although I said level processing was out of the goal of the project, it will be evolved as well. Within the classic version we couldn't have properties named the same way for different components. Let's illustrate this:

Imagine we have a *light* component which knows which kind of light will be used, and we have a *perception* component which knows which type of perception is used for a given entity. In the first approach we'd have to write this, or something similar:

    EntityName : EntityType
        light_type Directional
        perception_type Soldier

In this second approach we want to write this:

    EntityName : EntityType
        Light
            type Directional
        Perception
            type Soldier

Using this new way of defining levels we might argue that `blueprints` aren't necessary anymore and thus entity components can be inferred from level data. So, `blueprints` will be gone and components will be built out of level definitions.

## Evolved+ game architecture

Status: **Completed**

After creating the Evolved version of the game architecture, there are still some things to be explored further. We're developing those things in this last version of the toy game architecture.

First of all, we'll be adding the ability to define *data-hierarchies* when it comes to entities. It's a bit cumbersome having to define all of the data in the level every time, even when some of the entities are almost clones that just change one property for one component. To solve that, `archetypes` will provide a mechanism so we can do this (in a *data-driven approach*):

Level file:

    EntityName : [ArchetypeName]
        Physics
            radius 2.1

Archetypes file:

    ArchetypeName : EntityType
        Graphics
            model ModelFile.fbx
        Physics
            type capsule
        Perception
            type Soldier

With this, we can even define *archetype-hierarchies*. When a component tries to access a property in its data, we'll first look for it in the data defined in the level file, then in each subsequent archetype until the end of the hierarchy.

That means we can have an Archetypes file which looks like this:

    ArchetypeName : [Parent Archetype]
        Graphics
            model ModelFile.fbx
    
    Parent Archetype : [Grandparent Archetype]
        AI
            type Aggressive
            behaviour Soldier
        Perception
            type Enemy
            threshold 0.3
    
    Grandparent Archetype : Entity Type Alpha
        Physics
            type capsule
            radius 0.8
            height 2.0

And then have a `Level` in which we define entities:

    Entity 1 : [ArchetypeName]
    
    Entity 2 : [ArchetypeName]
        Graphics
            model Grunt.fbx

For the next feature I'll quote one of the teachers at my Master's Degree: *There's no better message than a function call*. Sending messages tends to introduce extra processing and, in our approach, a one-frame delay between a message is emitted and it's processed. Although it has some nice features like avoiding immediate infinite loops and processing everything `in bulk`, it has some bad ones like not being able to get a direct response from a message we've sent (asking for a position, the radius of a collider, ...).

For this, we'll provide a mechanism so components can ask for a pointer to another component from any entity (if it exists), and then execute its functions right away. This introduces coupling, but it's a nice feature to be explored. Also, some commercial game engines provide both mechanisms (messaging and function calls).

And finally, the last feature in this toy game architecture. In game development we always strive to minimize the amount of time it takes to perform any operation (more importantly, empty ones). We've already seen how we've transformed our components so they aren't called at all if they don't want any message. This time we're introducing a way of enabling/disabling components individually. That way, we don't need to turn off an entity but just some of its components.

#### Extra features

After completing the Evolved+ approach, I've added some extra features based on suggestions and things that I think are worth a try. These include:

- Components' priority: they declare a priority, are sorted by it and will be updated in that order.
- Components' variable update time: this way, we can update components only so many times a second (i.e. AI every 10 frames, Physics every 2 frames, ...). This allows three possibilities: don't tick anytime, tick every frame and tick with a fixed step.

This list will grow as new features are added.

## Cloning and running

This project is developed using Visual Studio 2012 and a solution file is included in it. To get working, you'll have to:

- Clone the repository:

        git clone https://github.com/MetanoKid/toy-game-architecture.git

- Open `ToyGameArchitecture.sln` in Visual Studio 2012.
- If you want to launch it right from the IDE:
    - Right click the `ToyGameArchitecture` project.
    - Go to Properties.
    - Select `All configurations` from the Configurations dropdown.
    - Under Configuration properties choose Debugging.
    - Change Working directory from `$(ProjectDir)` to `$(OutDir)`.
- Compile solution.
- Execute.