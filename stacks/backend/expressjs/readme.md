# Learning Express

## Good [youtube tutorial](https://www.youtube.com/watch?v=Lr9WUkeYSA8&list=PL4cUxeGkcC9jsz4LDYc6kv3ymONOKxwBU&index=6)

## [Main site](https://expressjs.com/)
- Disappointing, I learnt better from youtube videos than the main site...

```
const express = require('express')
const app = express()
 
app.get('/', function (req, res) {
  res.send('Hello World')
})
 
app.listen(3000)
```

## Routing
`app.get(), app.post(), app.put(), app.delete()`.

There is a special `app.all()`

## Middleware

What the hell is middleware? I guess whatever logic that sits between the incoming request and outgoing response. Guess everything is middleware?

`app.get()` runs only for GET requests. But its a middleware too. `app.use()` runs for all requests, regardless of the method.

`app.use()`


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

## Gotchas
Express works in top down manner.
```
app.get('/', (req, res) => { res.send('Welcome to index.html') }); // matches on root path

app.get('/about', (req, res) => { res.send('Welcome to about page') }); // matches with /about endpoint

app.use((req, res) => { res.status(404).send('This is the 404 page') }); // This will match any endpoint.
```
*if `app.use()` is called first, then app.get('/') and app.get('/about') wont be called.*
