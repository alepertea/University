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

const reservations = [];
const names = ['A', 'B', 'C', 'D'];
const doctors = ['D1', 'D2', 'D3', 'D4'];

for (let i = 0; i < 50; i++) {
  reservations.push({
    id: i + 1,
    nume: names[getRandomInt(0, names.length)] + i,
    doctor: doctors[getRandomInt(0, doctors.length)],
    data: getRandomInt(1, 30),
    ora: getRandomInt(0, 23),
    detalii: `test ${getRandomInt(1, 100)}`,
    status: i % 2 ? false : true,
  });
}

const router = new Router();
router.get('/open', ctx => {
  ctx.response.body = reservations.filter(product => product.status === false);
  ctx.response.status = 200;
});

const broadcast = (data) =>
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify(data));
    }
  });


router.post('/confirm', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const id = headers.id;
  if (typeof id !== 'undefined') {
    let obj = reservations.find(el => el.id === id);
    if (obj !== 'undefined') {
      obj.status = true;
      ctx.response.body = obj;
      ctx.response.status = 200;
    }else{
      console.log("No reservation with the specified id! id: " + id);
      ctx.response.body = { text: 'No reservation with the specified id!' };
      ctx.response.status = 404;
    }
  } else {
    console.log("Missing or invalid id!");
    ctx.response.body = { text: 'Missing or invalid id!' };
    ctx.response.status = 404;
  }
});

router.post('/create', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const nume = headers.nume;
  const doctor = headers.doctor;
  const data = headers.data;
  const ora = headers.ora;
  const detalii = headers.detalii;
  if (typeof nume !== 'undefined'
    && typeof doctor !== 'undefined'
    && typeof data !== 'undefined'
    && typeof ora !== 'undefined'
    && typeof detalii !== 'undefined') {
    const index = reservations.findIndex(obj => obj.nume == nume);
    if (index !== -1) {
      console.log("Reservation already exists!");
      ctx.response.body = { text: 'Reservation already exists!' };
      ctx.response.status = 404;
    } else {
      let maxId = Math.max.apply(Math, reservations.map(function (obj) {
        return obj.id;
      })) + 1;
      let obj = {
        id: maxId,
        nume,
        doctor,
        data,
        ora,
        detalii,
        status: false
      };
      // console.log("created: " + JSON.stringify(name));
      reservations.push(obj);
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

server.listen(2025);