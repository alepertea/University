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
const names = ['A', 'B', 'C', 'D'];
const types = ['T1', 'T2', 'T3', 'T4'];

for (let i = 0; i < 50; i++) {
  products.push({
    id: i + 1,
    nume: names[getRandomInt(0, names.length)] + i,
    tip: types[getRandomInt(0, types.length)],
    cantitate: getRandomInt(10, 100),
    pret: getRandomInt(100, 500),
    discount: getRandomInt(0, 100),
    status: getRandomInt(0, 10) > 7 ? false : true,
  });
}

const router = new Router();
router.get('/products', ctx => {
  ctx.response.body = products;
  ctx.response.status = 200;
});

const broadcast = (data) =>
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify(data));
    }
  });

router.post('/product', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const nume = headers.nume;
  const tip = headers.tip;
  const cantitate = headers.cantitate;
  const pret = headers.pret;
  const discount = headers.discount;
  if (typeof nume !== 'undefined'
    && typeof tip !== 'undefined'
    && typeof cantitate !== 'undefined'
    && typeof pret !== 'undefined'
    && typeof discount !== 'undefined') {
    const index = products.findIndex(obj => obj.nume == nume);
    if (index !== -1) {
      console.log("Product already exists!");
      ctx.response.body = {text: 'Product already exists!'};
      ctx.response.status = 404;
    } else {
      let maxId = Math.max.apply(Math, products.map(function (obj) {
        return obj.id;
      })) + 1;
      let obj = {
        id: maxId,
        nume,
        tip,
        cantitate,
        pret,
        discount,
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
    ctx.response.body = {text: 'Missing or invalid fields!'};
    ctx.response.status = 404;
  }
});

app.use(router.routes());
app.use(router.allowedMethods());

server.listen(2025);