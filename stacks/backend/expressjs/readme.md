# Learning Express

## Good [youtube tutorial](https://www.youtube.com/watch?v=Lr9WUkeYSA8&list=PL4cUxeGkcC9jsz4LDYc6kv3ymONOKxwBU&index=6)

## [Main site](https://expressjs.com/)
- Disappointing, I learnt better from youtube videos than the main site...

```javascript
const express = require('express')
const app = express()
 
app.get('/', function (req, res) {
  res.send('Hello World')
})
 
app.listen(3000)
```

## Routing
`app.get(), app.post(), app.put(), app.delete()`.

Express works in top down manner.
```javascript
app.get('/', (req, res) => { res.send('Welcome to index.html') }); // matches on root path

app.get('/about', (req, res) => { res.send('Welcome to about page') }); // matches with /about endpoint

app.use((req, res) => { res.status(404).send('This is the 404 page') }); // This will match any endpoint.
```
*if `app.use()` is called first, then app.get('/') and app.get('/about') wont be called.*

## Middleware

What the hell is middleware? *Middleware functions are functions that have access to the request object (req), the response object (res), and the next function in the application’s request-response cycle.*

First, a little on routing for Express: `app.get()` runs only for GET requests. `app.use()` runs for all requests, regardless of the method.

My feeling: *When you code in Express, you are always "chaining" functions together. When a request comes in, you could chain 1 to many different `middleware` functions to handle the request. Just a different way of thinking, which allows for flexibility! How? You could have 3rd party middleware, which helps speed up development really quickly.*

```javascript
var myLogger = function (req, res, next) { // This is a valid middleware function! Because it expects to receive request, response object and next function.
  console.log('LOGGED');
  next();
}

app.use(myLogger); // All middleware functions after this line will be called AFTER `myLogger`
```

Following the above example, you could simply chain lots of `app.use()` one after the other till you eventually return the response object back to the client.


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