const http = require('http');
const fs = require('fs');

/* Callback function given will be run every time a request comes to the server */
const server = http.createServer((req, res) => {
   res.setHeader('Content-Type', 'text/html');
    if (req.url === '/') {
        res.statusCode = 200;
        res.end(fs.readFileSync('./index.html'));
    }
    else if (req.url === '/about'){
        res.statusCode = 200;
        res.end(fs.readFileSync('./about.html'));
    }
    else{
        res.statusCode = 404;
        res.end(fs.readFileSync('./404.html'));
    }
});

server.listen(3000, 'localhost', () => {
    console.log('listening for request on port 3000');
});