# Basic Routing, Middleware and View Engine


## Some links:
- A good [youtube tutorial](https://www.youtube.com/watch?v=Lr9WUkeYSA8&list=PL4cUxeGkcC9jsz4LDYc6kv3ymONOKxwBU&index=6). Recommended!
- [Main site](https://expressjs.com/) Disappointing, I learnt better from youtube videos than the main site...

---

## Basic Express code snippet:
```javascript
const express = require('express')
const app = express()
 
app.get('/', function (req, res) {
  res.send('Hello World')
})
 
app.listen(3000)
```

---

## Routing
Express works in top down manner.
```javascript
app.get('/', (req, res) => { res.send('Welcome to index.html') }); // GET request matches root path

app.get('/about', (req, res) => { res.send('Welcome to about page') }); // GET request matches /about path

app.use((req, res) => { res.status(404).send('This is the 404 page') }); // Any METHOD, any path with match
```
> *if `app.use()` is called first, then app.get('/') and app.get('/about') wont be called as it returns the response with `res.send()`*

---

## [Middleware](https://expressjs.com/en/guide/using-middleware.html)
*Handling http requests comes down to `app.METHOD(PATH, HANDLER)`.Middleware functions are the `HANDLER()` functions, that have access to the `request object (req)`, the `response object (res)`, and the `next function` in the application’s request-response cycle. E.g. `app.get('/', function(req, res, next) {console.log("I'm a middleware function")})`*


```javascript
app.use((req, res, next) => {
  console.log(`I'm in the first middleware! About to call next()!`);
  next();
});

app.use((req, res, next) => {
  console.log(`I'm in the second middleware! About to call next()!`);
  next();
});

app.get('/', (req, res) => {
  console.log(`I have been through the 2 middlewares above me! Express is top-down!`);
  res.send('Welcome to index.html');
});
```

Following the above example, you could simply chain lots of `app.use()` one after the other till you eventually return the response object back to the client.

---

## View Engine
I didn't find the [main site's](https://expressjs.com/en/guide/using-template-engines.html) definition very helpful :(

My definition: *A view engine is basically a way to generate html dynamically. How does the engine generate? You create a template file (depending on the view engine you choose). The template file will have a certain format and contain variable names like `user_name`. When a user requests for a html page, the view engine takes the template file, converts it to .html, and also replaces `user_name` with whatever value you defined. BOOM. You have dynamically generated html files. (Does not have to be `user_name`. You decide whatever variable you want.)*

e.g. of a template file with the `pug` engine.
```
/* index.pug */
html
  head
    title= title
  body
    h1= message


/* app.js */
app.get('/', function (req, res) {
  res.render('index', { title: 'Hey', message: 'Hello there!' }) // replaces `title` and `message` in the index.pug file
})
```