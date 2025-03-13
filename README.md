# Design_Patterns

Practicing useful software design patterns in C++. 
Current list:

:one: Singleton Design Pattern

Ensures that only one instance of a class exists, such as in the case of a government, a gaming engine, or a company name, etc. It is implemented by maintaining the only instance as a private and static member which can only be accessed via a static method. The constructor is also kept private. To ensure thread safety against copying, accessibility of the singleton instance is locked with a mutex. 

:factory: Factory Method

Introduces flexible object creation for different class requirements. This is done by defining an abstract class for the created object, aka a product. The actual products will inherit from the abstract product. To create different products, the client will call methods of different 'factories'. These factory classes all inherit from an abstract factory. 

:electric_plug: Adapter Design Pattern

Provides a wrapper to convert one interface into another, such as a legacy to a new, or more simply, a round peg to a square hole. This wrapper inherits extends the desired/target interface and internally calls the adaptee's interface. For example, in square pegs and circular holes, the adapter calls width of a square when the radius of a desired circule is called.

:eyes: Observer Design Pattern

Allows one object (the subject) to notify multiple dependent objects (observers) about state changes. The subject maintains a list of observers and provides methods to attach or detach them. When the subject's state changes, it triggers the update method of all registered observers. This pattern is commonly used in scenarios where a change in one object requires updates in many others, such as in event-driven systems like infotainment. It promotes loose coupling between the subject and its observers.

5. Mediator Design Pattern

Facilitates communication between multiple objects by centralizing complex interactions in a mediator object. Instead of objects communicating directly, they send requests to the mediator, which then handles the communication between them. Each non-mediator entity only sees the mediator itself. The rest is a black box. This decouples the whole system, making it easier to handle.

6. Decorator Design Pattern

Allows the addition of new functionality to an object at runtime without altering its structure. This is achieved by creating a decorator class that wraps the original object, providing the same interface while extending its behavior. The decorator class holds a reference to the original object and delegates calls to it, adding additional behavior either before or after the delegation. This pattern is commonly used to dynamically augment the capabilities of objects. As a simple exapmle, it's like being given the ability to add various toppings to an ice cream given the base of a cone!

7. Strategy Design Pattern

Enables an object to choose a behavior at *runtime* from a family of algorithms. The behavior is defined by a strategy interface, with multiple concrete strategy classes implementing different algorithms. The context class maintains a reference to a strategy and delegates the execution to it. This pattern promotes flexibility by decoupling the algorithm from the object that uses it, allowing easy switching of behaviors without altering the object's code. For example, a customer has various payment methods, each of which is implemented differently, such as credit card, PayPal, or cash.

8. Visitor Design Pattern

Allows a wide variety of operations to be implemented on object structures without modifying their class definitions, promoting flexibility and centralizing implementations of the same logic. This is done by creating various types of visitor classses, each dedicated to a function, and which all inherit from a parent visitor. 
Each visitor class's operation is implemented in a class with an `accept` method, that takes in an abstract visitor and executes the visitor's function, which by double dispatch can be any visitor and hence is adaptable to any task. One example is: converting/exporting various types of files to XML - that requires diferent logic for different file types.

9. State Design Pattern

Essentially a [finite-state machine](https://en.wikipedia.org/wiki/Finite-state_machine). Personally, one of the most interesting ones by far, which harks back from our first year Digital Circuits & Systems course at UWaterloo. Except this time I have to implement actions, which are the "input" to any state. All states have the same set of actions, defined as methods in the abstract state. In each concrete state, I define an action taken and a possible transition. For example, I implemented the classic "vending machine" example, with idle, coin processing, & item dispense state. 
