var koa = require('koa');
var app = module.exports = new koa();
const server = require('http').createServer(app.callback());
const WebSocket = require('ws');
const wss = new WebSocket.Server({ server });
const Router = require('koa-router');
const cors = require('@koa/cors');
const bodyParser = require('koa-bodyparser');

app.use(bodyParser());

app.use(cors());

app.use(middleware);

function middleware(ctx, next) {
  const start = new Date();
  return next().then(() => {
    const ms = new Date() - start;
    console.log(`${start.toLocaleTimeString()} ${ctx.request.method} ${ctx.request.url} - ${ms}ms`);
  });
}

const getRandomInt = (min, max) => {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min)) + min;
};

const products = [];
const names = ['M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'];

for (let i = 0; i < 50; i++) {
  products.push({
    id: i + 1,
    nume: names[getRandomInt(0, names.length)] + i,
    descriere: "test descriere " + i,
    pret: getRandomInt(10, 500),
    cantitate: getRandomInt(10, 100),
    status: getRandomInt(0, 10) > 8 ? false : true,
  });
}

const router = new Router();
router.get('/produse', ctx => {
  ctx.response.body = products;
  ctx.response.status = 200;
});

const broadcast = (data) =>
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify(data));
    }
  });

router.post('/adauga', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const nume = headers.nume;
  const descriere = headers.descriere;
  const pret = headers.pret;
  const cantitate = headers.cantitate;
  if (typeof nume !== 'undefined'
    && typeof descriere !== 'undefined'
    && typeof pret !== 'undefined'
    && typeof cantitate !== 'undefined') {
    const index = products.findIndex(obj => obj.nume == nume);
    if (index !== -1) {
      console.log("Product already exists!");
      ctx.response.body = { text: 'Product already exists!' };
      ctx.response.status = 404;
    } else {
      let maxId = Math.max.apply(Math, products.map(function (obj) {
        return obj.id;
      })) + 1;
      let obj = {
        id: maxId,
        nume,
        descriere,
        pret,
        cantitate,
        status: true
      };
      // console.log("created: " + JSON.stringify(name));
      products.push(obj);
      broadcast(obj);
      ctx.response.body = obj;
      ctx.response.status = 200;
    }
  } else {
    console.log("Missing or invalid fields!");
    ctx.response.body = { text: 'Missing or invalid fields!' };
    ctx.response.status = 404;
  }
});

router.post('/cumpara', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const id = headers.id;
  const cantitate = headers.cantitate;
  if (typeof id !== 'undefined'
    && typeof cantitate !== 'undefined') {
    const obj = products.find(obj => obj.id === id);
    if (obj !== 'undefined') {
      if (obj.cantitate >= cantitate) {
        // console.log("found: " + JSON.stringify(obj));
        obj.cantitate = obj.cantitate - cantitate;
        ctx.response.body = obj;
        ctx.response.status = 200;
      } else {
        console.log("Missing requested quantity!");
        ctx.response.body = { text: 'Missing requested quantity!' };
        ctx.response.status = 404;
      }
    } else {
      console.log("Specified product does not exists!");
      ctx.response.body = { text: 'Specified product does not exists!' };
      ctx.response.status = 404;
    }
  } else {
    console.log("Missing or invalid fields!");
    ctx.response.body = { text: 'Missing or invalid fields!' };
    ctx.response.status = 404;
  }
});

app.use(router.routes());
app.use(router.allowedMethods());

server.listen(2029);
