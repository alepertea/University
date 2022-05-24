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

const obiecte = [];
const names = ['M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];

for (let i = 0; i < 50; i++) {
  obiecte.push({
    id: i + 1,
    nume: names[getRandomInt(0, names.length)] + i,
    an: getRandomInt(1700, 2022),
    luna: getRandomInt(1, 12),
    zi: getRandomInt(1, 28),
    valoare: getRandomInt(1, 100),
    rezervari: getRandomInt(1, 10),
    status: getRandomInt(0, 10) > 8 ? false : true,
  });
}

const router = new Router();
router.get('/obiecte', ctx => {
  ctx.response.body = obiecte;
  ctx.response.status = 200;
});

router.get('/valoare', ctx => {
  ctx.response.body = obiecte;
  ctx.response.status = 200;
});

const broadcast = (data) =>
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify(data));
    }
  });

router.post('/nou', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const nume = headers.nume;
  const an = headers.an;
  const luna = headers.luna;
  const zi = headers.zi;
  const valoare = headers.valoare;
  const rezervari = headers.rezervari;
  if (typeof nume !== 'undefined'
    && typeof an !== 'undefined'
    && typeof luna !== 'undefined'
    && typeof zi !== 'undefined'
    && typeof valoare !== 'undefined'
    && typeof rezervari !== 'undefined') {
    const index = obiecte.findIndex(obj => obj.nume == nume);
    if (index !== -1) {
      console.log("Object already exists!");
      ctx.response.body = { text: 'Object already exists!' };
      ctx.response.status = 404;
    } else {
      let maxId = Math.max.apply(Math, obiecte.map(function (obj) {
        return obj.id;
      })) + 1;
      let obj = {
        id: maxId,
        nume,
        an,
        luna,
        zi,
        valoare,
        rezervari,
        status: true
      };
      // console.log("created: " + JSON.stringify(name));
      obiecte.push(obj);
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

router.del('/distruge/:id', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.params;
  // console.log("body: " + JSON.stringify(headers));
  const id = headers.id;
  if (typeof id !== 'undefined') {
    const index = obiecte.findIndex(obj => obj.id == id);
    if (index === -1) {
      console.log("No object with id: " + id);
      ctx.response.body = { text: 'Invalid object id' };
      ctx.response.status = 404;
    } else {
      let obj = obiecte[index];
      // console.log("deleting: " + JSON.stringify(obj));
      obiecte.splice(index, 1);
      ctx.response.body = obj;
      ctx.response.status = 200;
    }
  } else {
    console.log("Missing or invalid fields!");
    ctx.response.body = { text: 'Id missing or invalid' };
    ctx.response.status = 404;
  }
});

router.get('/an/:an', ctx => {
  const headers = ctx.params;
  const an = headers.an;
  if (typeof an !== 'undefined') {
    ctx.response.body = obiecte.filter(obj => obj.an == an);
    ctx.response.status = 200;
  } else {
    console.log("Missing or invalid: an!");
    ctx.response.body = { text: 'Missing or invalid: an!' };
    ctx.response.status = 404;
  }
});


router.post('/imprumuta', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const id = headers.id;
  if (typeof id !== 'undefined') {
    const obj = obiecte.find(obj => obj.id == id);
    if (typeof obj !== 'undefined') {
      // console.log("found: " + JSON.stringify(obj));
      obj.rezervari = obj.rezervari + 1;
      ctx.response.body = obj;
      ctx.response.status = 200;
    } else {
      console.log("Specified object does not exists!");
      ctx.response.body = { text: 'Specified product object not exists!' };
      ctx.response.status = 404;
    }
  } else {
    console.log("Missing or invalid id!");
    ctx.response.body = { text: 'Missing or invalid id!' };
    ctx.response.status = 404;
  }
});

router.post('/restituie', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const id = headers.id;
  if (typeof id !== 'undefined') {
    const obj = obiecte.find(obj => obj.id == id);
    if (typeof obj !== 'undefined') {
      // console.log("found: " + JSON.stringify(obj));
      ctx.response.body = obj;
      ctx.response.status = 200;
    } else {
      console.log("Specified object does not exists!");
      ctx.response.body = { text: 'Specified product object not exists!' };
      ctx.response.status = 404;
    }
  } else {
    console.log("Missing or invalid id!");
    ctx.response.body = { text: 'Missing or invalid id!' };
    ctx.response.status = 404;
  }
});

app.use(router.routes());
app.use(router.allowedMethods());

server.listen(2019);
