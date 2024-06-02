const http = require('http');

const host = '127.0.0.1';
const port = 9005;

const requestListener = function (req, res) {
    if (req.url === "/") {
        res.writeHead(200);
        res.end("My first server!");
        return
    }
    if (req.url === "/json") {
        res.writeHead(200);
        res.end(JSON.stringify({ name: 'jake', age: 40 }));
        return
    }
};


const server = http.createServer(requestListener);
server.listen(port, host, () => {
    console.log(`Server is running on http://${host}:${port}`);
});




