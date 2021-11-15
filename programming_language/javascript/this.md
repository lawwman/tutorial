# This

reads:
- [developer mozilla](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/this)
- [w3schools](https://www.w3schools.com/js/js_this.asp)


## `this` refers to the Global object when in `Global Context` (outside of any function) or `Function Context` (inside a function)
```javascript
function f1() {
  return this;
}

this === window   // true. In web browsers, the window object is the global object.
a = 37;           // this.a == window.a == 37
this.b = "MDN";   // window.b === b === "MDN"
f1() === window;  // true. f1() === undefined if this script is in strict mode
```

*strict mode is used to help prevent dumb syntax errors and generally code more safely i guess.*

## As an object method
When a function is called as a method of an object, its `this` is set to the object the method is called on.

```javascript
const obj = {
  someProperty: 'a',
  someMethod: function () {
    return this.someProperty;
  }
};
obj.someMethod(); // Returns 'a'
```

## With [`new`](new.md) operator!
`this` is set as the new object being created. Follow the link above to learn more.

## Class Context
Just like with regular functions, the value of this within methods depends on how they are called. Sometimes it is useful to override this behavior so that this within classes always refers to the class instance. To achieve this, bind the class methods in the constructor:

```javascript
class Car {
  constructor() {
    // Bind sayBye but not sayHi to show the difference
    this.sayBye = this.sayBye.bind(this);
  }
  sayHi() {
    console.log(`Hello from ${this.name}`);
  }
  sayBye() {
    console.log(`Bye from ${this.name}`);
  }
  get name() {
    return 'Ferrari';
  }
}

class Bird {
  get name() {
    return 'Tweety';
  }
}

const car = new Car();
const bird = new Bird();

// The value of 'this' in methods depends on their caller
car.sayHi(); // Hello from Ferrari
bird.sayHi = car.sayHi;
bird.sayHi(); // Hello from Tweety

// For bound methods, 'this' doesn't depend on the caller
bird.sayBye = car.sayBye;
bird.sayBye();  // Bye from Ferrari
```