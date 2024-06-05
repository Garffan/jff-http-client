const http = require('http');

const host = '127.0.0.1';
const port = 9005;

const requestListener = function (req, res) {
    console.log(req.method, req.url);
    if (req.url === "/") {
        res.writeHead(200);
        res.end("My first server!");
        return
    }

    if (req.url === "/json" && req.method === "GET") {
        res.writeHead(200);
        res.end(JSON.stringify({ name: 'jake', age: 40 }));
        return
    }

    if (req.url === "/json" && req.method === "POST") {
        getBody(req).then((b) => {
            if (!b) {
                res.writeHead(400);
                res.end();
            } else {
                const obj = JSON.parse(b);
                res.writeHead(200);
                res.end(JSON.stringify({ acceptedJson: 'ok', N: obj.value }));
            }

        });
    }
};

function getBody(request) {
    return new Promise((resolve) => {
        const bodyParts = [];
        let body;
        request.on('data', (chunk) => {
            bodyParts.push(chunk);
        }).on('end', () => {
            body = Buffer.concat(bodyParts).toString();
            resolve(body)
        });
    });
}

const server = http.createServer(requestListener);
server.listen(port, host, () => {
    console.log(`Server is running on http://${host}:${port}`);
});




