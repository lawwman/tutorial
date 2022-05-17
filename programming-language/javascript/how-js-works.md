# Super simplified version of how JS works
if you have time, please update.

# Execution context (EC)
> `"The Execution Context contains the code that's currently running, and everything that aids in its execution."`

there are 2 kinds:
- **Global Execution Context (GEC)**
  - default, contain global code
- **Function Execution Context (FEC)**
  - new FEC created on each function call
  - has access to GEC code (but GEC not access to FEC)

Execution `context` is related to execution `stack`. When a script is ran:
- GEC is always created at bottom of the stack.
- for each function called, FEC is created and pushed onto stack.
- each time a function returns, that FEC is poppedd from the stack.

## How are execution contexts created?
There are 2 phases: `creation` and `execution`.

# Creation Phase

has 3 things to do:
- Creation of the `Variable Object (VO)` or `Variable environment` (simpler to just think of it has memory)
- Creation of the Scope Chain
- Setting the value of the `this` keyword

## **Variable Object (VO)**
stores variables and function declarations defined within that Execution Context.

When the EC is created, all declared variables and functions are stored in this VO or variable environment (or simply, in memory) for this EC.

This explains why:
- you can call functions in the same execution context that you have yet to declare.
- variables on the other hand, are stored in VO initially as `undefined`.

*This process of storing variables and function declaration in memory prior to the execution of the code is known as `Hoisting`.*

*note that `const` and `let` are not hoisted. They are declared only. not initialised (like `var` which is initialised as `undefined`)*

For FEC, VO also includes the arguments as well.

## **Scope Chain**
`Scope in JavaScript is a mechanism that determines how accessible a piece of code is to other parts of the codebase. Scope answers the questions: from where can a piece of code be accessed? From where can't it be accessed? What can access it, and what can't?`

Each EC creates an environment where variables/functions can be accessed (a.k.a scoping). Javascript uses lexical scoping, i.e. `the ability for a function scope to access variables from the parent scope.`

The scope chain is created.

**Setting the value of the `this` keyword**

The JavaScript this keyword refers to the scope where an Execution Context belongs. Once the scope chain is created, the value of `this` is initialized by the JS engine.

# Execution Phase
At this stage, the JavaScript engine reads the code in the current Execution Context once more, then updates the VO with the actual values of these variables. Then the code is parsed by a parser, gets transpired to executable byte code, and finally gets executed.

