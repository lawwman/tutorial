# Hard Parts

js runs through code line by line - thread of execution.

# execution context
- thread of execution
- memory

there is always a `global execution context` and `global memory`.

when we run code in a function, we create a new execution context with:
- arguments
- memory: variables within function
- thread of execution

# call stack
when we call functions, they are added to the call stack. sort of a stack of functions that the thread of execution visited.

by default, global() is always added to the stack first when javascript is executed.

when functions are done running, they are removed from the call stack.

# functions
`In Javascript, functions can be assigned to variables in the same way that strings or arrays can. They can be passed into other functions as parameters or returned from them as well. A “higher-order function” is a function that accepts functions as parameters and/or returns a function.`

functions are `first class` objects. (first class: they have all the features of objects)

callback: `the function we insert into another HOF`.

## arrow function

# closure
`A closure is the combination of a function bundled together (enclosed) with references to its surrounding state (the lexical environment).`

a function's context execution's local memory is also known as `variable environment`.

closure is sometimes referred to as `closed over variable environment`.

closure is also referred to as "persisent lexical scoped referenced data".

# Web browser
What the browser has that javascript does not have:
- devtools
- console (accessed by `console`)
- sockets
- ability to make network requests (accessed by `xhr / fetch`)
- HTML DOM (accessed by `document`)
- Timer (accessed by `setTimeOut()`)

# callback queue
example, for setTimeout of 0 ms, why is it not called immediately? It is not added to call stack, but rather to the callback queue.

> note: there are 2 types of callback queues. task queue and microtask queue.

**when does it exit the queue?** When all synchronous code is done... This is facilitated by the `Event loop`. It constantly checks if `call stack` is empty and no more code is left to run, then pop the call from the `callback queue` into the `call stack`.

# ES6 promises
when javascript uses `fetch` (web browser feature, called a facade function?), it returns a promise. 

