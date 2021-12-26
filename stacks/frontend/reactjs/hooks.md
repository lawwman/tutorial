# Learning about Hooks
`class components` are able to maintain state and access lifecycle methods. Hooks let `function components` use them.

Read them in this order:
- [Basics on function component](https://reactjs.org/docs/components-and-props.html)
- [How function component can maintain state](https://reactjs.org/docs/hooks-state.html)
- [What the heck are effects](https://reactjs.org/docs/hooks-effect.html)

## How I view function components
`Function Components` are just javascript functions that return what to render (in the form of `JSX`). That's how React know what the component looks like. There is no aspect of retaining 'state' since the variables within the function are scoped as such. If I run the same function again, I would expect the same html elements to be rendered!

Remember, they are functions. You are not in the global scope, you are not in a class. variables don't carry over information between each call to the function.

We need 'hooks' like `useState()` to remember the state between each function call.

> Small gotcha, [useState() is async](https://stackoverflow.com/questions/62900377/why-is-react-setstate-hook-not-updating-immediately). There is an internal queue that React uses. If you console log the state immediately after `useState()`, its not accurate.

## When does the render happen?? i.e when is the function component called?
When a component is first rendered into the DOM, the function is called (I'm referring to the `function component` being called). 

```jsx
import React, { useState } from 'react';

function Example() {
  const [count, setCount] = useState(0);

  console.log('being rendered');

  return (
    <div>
      <p>You clicked {count} times</p>
      <button onClick={() => setCount(count + 1)}>
        Click me
      </button>
    </div>
  );
}
```

The `Example()` function component is called once when it is first rendered. You can even console.log it to find out how often the function is called. When you click the button, the `count` state changes when we call `setCount()`.

When state changes, `Example()` function is called again (i.e. the component is re-rendered again). It will console log out 'being rendered' again.
> [StackOverFlow post about React rerendering components when state changes](https://stackoverflow.com/questions/59929482/functional-component-rerender-on-state-change)

## What I think of Effects hook
Its just a callback function that we give to `useEffect()` hooks. The callback is called **after** each render. The `return` of the callback function is the "clean up" function. The clean up function is also run after every render.