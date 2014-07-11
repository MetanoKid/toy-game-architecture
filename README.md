Toy Game Architecture
=====================

This project tries to explore different ways of managing entities in a component-based game architecture.

Any of the approaches we'll be exploring will have some common elements: `entities`, `components` and `factories` for both of them. Also, `messages` will play an important role in most of them, but we'll try to introduce at least a *message-less* system.
Several approaches to game architectures are planned:

- Classic version: an entity is basically a *container of components*. It will receive messages, process them if necessary and hand them to its components.
- Central messaging *topic*: using a pub-sub *topic* in which components register themselves, we'll start making entities unnecessary and have a better classification of components and the messages they'll be listening to. Messages will be managed through a pool, so we try to minimize the overhead of creating and deleting messages which are used constantly.
- Direct invocation: components will have a *dependency injection* section in which they'll be able to access other components and get a pointer to them. Using this approach, messages are not allowed.

There may be more or less approaches as the project evolves.
