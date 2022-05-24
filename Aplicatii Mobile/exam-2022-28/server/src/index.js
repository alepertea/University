var koa = require('koa');
var app = module.exports = new koa();
const server = require('http').createServer(app.callback());
const WebSocket = require('ws');
const wss = new WebSocket.Server({ server });
const Router = require('koa-router');
const cors = require('@koa/cors');
const bodyParser = require('koa-bodyparser');
const { obj } = require('pumpify');

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

const dosare = [];
const names = ['W', 'X', 'Y', 'Z'];

for (let i = 0; i < 50; i++) {
  dosare.push({
    id: i + 1,
    nume: names[getRandomInt(0, names.length)] + i,
    medie: getRandomInt(1, 10),
    etaj: getRandomInt(1, 10),
    camera: getRandomInt(10, 50),
    orientare: i % 2 ? false : true,
    status: i % 2 ? false : true,
  });
}

const router = new Router();
router.get('/toate', ctx => {
  ctx.response.body = dosare;
  ctx.response.status = 200;
});

const broadcast = (data) =>
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify(data));
    }
  });


router.post('/validare', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const id = headers.id;
  const etaj = headers.etaj;
  const camera = headers.camera;
  if (typeof id !== 'undefined'
    && typeof etaj !== 'undefined'
    && typeof camera !== 'undefined') {
    let obj = dosare.find(el => el.id === id);
    if (obj !== 'undefined') {
      obj.status = true;
      obj.etaj = etaj;
      obj.camera = camera;
      ctx.response.body = obj;
      ctx.response.status = 200;
    } else {
      console.log("No file with the specified id! id: " + id);
      ctx.response.body = { text: 'No file with the specified id!' };
      ctx.response.status = 404;
    }
  } else {
    console.log("Missing or invalid id!");
    ctx.response.body = { text: 'Missing or invalid id!' };
    ctx.response.status = 404;
  }
});

router.post('/inregistrare', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const nume = headers.nume;
  const medie = headers.medie;
  const etaj = headers.etaj;
  const orientare = headers.orientare;
  if (typeof nume !== 'undefined'
    && typeof medie !== 'undefined'
    && typeof etaj !== 'undefined'
    && typeof orientare !== 'undefined') {
    const index = dosare.findIndex(obj => obj.nume == nume);
    if (index !== -1) {
      console.log("File already exists!");
      ctx.response.body = { text: 'File already exists!' };
      ctx.response.status = 404;
    } else {
      let maxId = Math.max.apply(Math, dosare.map(function (obj) {
        return obj.id;
      })) + 1;
      let obj = {
        id: maxId,
        nume,
        medie,
        etaj,
        orientare,
        camera: getRandomInt(10, 20),
        status: false
      };
      // console.log("created: " + JSON.stringify(name));
      dosare.push(obj);
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

app.use(router.routes());
app.use(router.allowedMethods());

server.listen(2028);