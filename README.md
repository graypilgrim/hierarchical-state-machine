# Hierarchical State Machine
## Goal
The main goal of this project was to create a library that can provide functionality of hierarchical state machine. 

## Requirements
1. Project should be created with usage of modern C++.
1. State machine is driven by events which are being delivered by an external library. API of the library has been described [here](https://github.com/graypilgrim/hierarchical-state-machine/blob/master/src/QueueLibrary.h).
1. Events and States can hold additional data and it should be relatively easy to create new ones.
1. Transition table should be easy to maintain.

## Implementation
### State
This implementation provides base State class.
It takes care of keeping valid relations between nodes in parent-child hierarchy.
It also contains two functors which are called on activation and deactivation of state.
This can be a channel of communication between State Machine and particular State.
There is no virtual methods in base State class.

### Event
Events are described with their type which are literals.
If no additional data or specific behavior is required, different Events can be created with usage of only base class.
To provide derived class it is required to:
1. override `serializeImpl` method, which is responsible for transforming data of class into binary form. There is no need to serialize type of event, base class handles this.
1. register deserializer functor in static Event's collection. This allows to create valid object from binary data.

### State Machine
StateMachine class contains logic of making transitions between concrete states. It was assumed that all events are delivered by external library, so there is no methods allowing to change the current state directly. `run` method starts loop which call `QueueReceive` and tries to create events from received data.
If event is valid and transition from current state (or its ancestors) is present in transition table, state is changed.