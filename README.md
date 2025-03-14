# Design_Patterns

Practicing useful software design patterns in C++.

Current list:

### :one: Singleton Design Pattern

Ensures that only one instance of a class exists, such as in the case of a government, a gaming engine, or a company name, etc. It is implemented by maintaining the only instance as a private and static member which can only be accessed via a static method. The constructor is also kept private. To ensure thread safety against copying, the accessibility of the singleton instance is locked with a mutex. 

### :factory: Factory Method

Introduces flexible object creation for different class requirements. This is done by defining an abstract class for the created object, aka a product. The actual products will inherit from the abstract product. To create different products, the client will call methods of different 'factories'. These factory classes all inherit from an abstract factory. 

### :electric_plug: Adapter Design Pattern

Provides a wrapper to convert one interface into another, such as a legacy to a new, or more simply, a round peg to a square hole. This wrapper inherits and extends the desired/target interface and internally calls the adaptee's interface. For example, in square pegs and circular holes, the adapter calls the width of a square when the radius of a desired circle is called.

### :eyes: Observer Design Pattern

Allows one object (the subject) to notify multiple dependent objects (observers) about state changes. The subject maintains a list of observers and provides methods to attach or detach them. When the subject's state changes, it triggers the update method of all registered observers. This pattern is commonly used in scenarios where a change in one object requires updates in many others, such as in event-driven systems like infotainment. It promotes loose coupling between the subject and its observers.

### :link: Mediator Design Pattern

Facilitates communication between multiple objects by centralizing complex interactions in a mediator object. Instead of objects communicating directly, they send requests to the mediator, which has a container of all the interconnected objects and a method that passes its argument to _every_ entity's message reception method. Each non-mediator entity is composed of the shared mediator object, which calls the mediator method to send messages to every other entity. The rest is just a black box to that entity. This decouples the whole system, making it easier to handle.

### :sparkles: Decorator Design Pattern

Allows the addition of new functionality to an object at runtime without altering its structure. This is achieved by creating a decorator class that wraps the original object, providing the same interface while extending its behavior. The decorator class holds a reference to the original object and delegates calls to it, adding additional behavior either before or after the delegation. This pattern is commonly used to dynamically augment the capabilities of objects. As a simple exapmle, it's like being given the ability to add various toppings to an ice cream given the base of a cone!

### :dart: Strategy Design Pattern

Enables an object to choose a behavior at *runtime* from a family of algorithms. The behavior is defined by a strategy interface, with multiple concrete strategy classes implementing different algorithms. The context class maintains a reference to a strategy and delegates the execution to it. This pattern promotes flexibility by decoupling the algorithm from the object that uses it, allowing easy switching of behaviors without altering the object's code. For example, a customer has various payment methods, each of which is implemented differently, such as credit card, PayPal, or cash.

### :shoe: Visitor Design Pattern

Allows a wide variety of operations to be implemented on object structures without modifying their class definitions, promoting flexibility and centralizing implementations of the same logic. This is done by creating various types of visitor classses, each dedicated to a function, and which all inherit from a parent visitor. 
Each visitor class's operation is implemented in a class with an `accept` method, that takes in an abstract visitor and executes the visitor's function, which by double dispatch can be any visitor and hence is adaptable to any task. One example is: converting/exporting various types of files to XML - that requires different logic for different file types.

### :performing_arts: State Design Pattern

Essentially a [finite-state machine](https://en.wikipedia.org/wiki/Finite-state_machine). The State Design Pattern allows an object to alter its behavior when its internal state changes. It is often used in situations where an object can be in multiple states, and each state affects the behavior of the object. Instead of having complex conditionals or switch statements in the object itself, the state pattern delegates responsibility to specific state objects. Each state is represented by a class that implements a common interface, allowing the behavior to change dynamically based on the current state.

A classic example is the "vending machine" scenario, where the machine can be in various states like Idle, Coin Processing, and Item Dispense. In each state, certain actions can occur, such as accepting a coin or dispensing an item. Each state class implements the same interface but provides its own behavior for each action.

### :loudspeaker: Command Design Pattern

The Command Design Pattern encapsulates a request as an object, thereby allowing parameterization of clients with queues, requests, and operations. It decouples the sender of a request from the object that processes the request. The pattern allows you to handle requests as objects, and can also support undo/redo functionality by maintaining a history of commands. Each command class typically implements an interface with an execute() method, and clients invoke this method to request a certain operation.

The flow of the Command Design Pattern goes as follows: command objects are stored by a class known as an *invoker*. Command classes contain a pointer to the receiver of the command that fulfills requests, such as a Chef to serve food. First, the invoker calls execute() methods of each command in a buffer of commands, for example. This is often used to track or hold up requests. Then, those execution methods call the receiver's methods to serve requests.

### :clipboard: Template Method Design Pattern

The Template Method Design Pattern defines the skeleton of an algorithm in the superclass but allows subclasses to override specific steps of the algorithm without changing its structure. This pattern helps promote code reuse by providing a common structure for algorithms, while still enabling flexibility by allowing subclasses to implement specialized behavior in certain steps. The template method is a method in the superclass that outlines the general steps, and subclasses provide specific implementations for some of those steps.

### :arrows_clockwise: Iterator Design Pattern

The Iterator Design Pattern provides a way to access elements of a collection (such as a list, set, or array) sequentially without exposing the underlying structure. This pattern allows the client to traverse the collection without needing to understand how the collection is organized or implemented. It is typically implemented by creating an iterator object that maintains a pointer to the current element and provides methods to move forward or backward in the collection. The iterator pattern simplifies the interaction with complex data structures and promotes decoupling.

For example, an iterator for a list would allow the client to access each element in sequence, regardless of whether the list is backed by an array or a linked list.

### :rocket: Curiously Recurring Template Pattern (CRTP)

The Curiously Recurring Template Pattern (CRTP) is a C++ idiom where a class X inherits from a template class that is parameterized with X itself. This pattern allows a class to gain behavior from a base class template while still being able to specialize the behavior for itself. CRTP can be used for compile-time polymorphism, enabling highly efficient code by eliminating the need for virtual function calls. It is often used in situations where static polymorphism or mixins are desired.
