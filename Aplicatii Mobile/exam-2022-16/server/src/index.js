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

const books = [];
const titleNames = ['M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];
const authorNames = ['A', 'B', 'C', 'D'];
const genders = ['G1', 'G2', 'G3', 'G4'];

for (let i = 0; i < 50; i++) {
  books.push({
    id: i + 1,
    titlu: titleNames[getRandomInt(0, titleNames.length)] + i,
    autor: authorNames[getRandomInt(0, authorNames.length)] + i,
    gen: genders[getRandomInt(0, genders.length)],
    descriere: "test descriere " + i,
    cantitate: getRandomInt(10, 100),
    rezervari: getRandomInt(1, 10),
    status: getRandomInt(0, 10) > 8 ? false : true,
  });
}

const router = new Router();
router.get('/carti', ctx => {
  ctx.response.body = books;
  ctx.response.status = 200;
});

router.get('/toate', ctx => {
  ctx.response.body = books;
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
  const titlu = headers.titlu;
  const autor = headers.autor;
  const gen = headers.gen;
  const descriere = headers.descriere;
  const cantitate = headers.cantitate;
  const rezervari = headers.rezervari;
  if (typeof titlu !== 'undefined'
    && typeof autor !== 'undefined'
    && typeof gen !== 'undefined'
    && typeof descriere !== 'undefined'
    && typeof cantitate !== 'undefined'
    && typeof rezervari !== 'undefined') {
    const index = books.findIndex(obj => obj.titlu == titlu);
    if (index !== -1) {
      console.log("Book already exists!");
      ctx.response.body = { text: 'Book already exists!' };
      ctx.response.status = 404;
    } else {
      let maxId = Math.max.apply(Math, books.map(function (obj) {
        return obj.id;
      })) + 1;
      let obj = {
        id: maxId,
        titlu,
        autor,
        gen,
        descriere,
        cantitate,
        rezervari,
        status: true
      };
      // console.log("created: " + JSON.stringify(name));
      books.push(obj);
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

router.del('/sterge/:id', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.params;
  // console.log("body: " + JSON.stringify(headers));
  const id = headers.id;
  if (typeof id !== 'undefined') {
    const index = books.findIndex(obj => obj.id == id);
    if (index === -1) {
      console.log("No book with id: " + id);
      ctx.response.body = { text: 'Invalid book id' };
      ctx.response.status = 404;
    } else {
      let obj = books[index];
      // console.log("deleting: " + JSON.stringify(obj));
      books.splice(index, 1);
      ctx.response.body = obj;
      ctx.response.status = 200;
    }
  } else {
    console.log("Missing or invalid fields!");
    ctx.response.body = { text: 'Id missing or invalid' };
    ctx.response.status = 404;
  }
});

router.get('/gen/:gen', ctx => {
  const headers = ctx.params;
  const gen = headers.gen;
  if (typeof gen !== 'undefined') {
    ctx.response.body = books.filter(obj => obj.gen === gen);
    ctx.response.status = 200;
  } else {
    console.log("Missing or invalid: gen!");
    ctx.response.body = { text: 'Missing or invalid: gen!' };
    ctx.response.status = 404;
  }
});


router.post('/rezerva', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const id = headers.id;
  if (typeof id !== 'undefined') {
    const obj = books.find(obj => obj.id == id);
    if (typeof obj !== 'undefined') {
      if (obj.cantitate >= 0) {
        // console.log("found: " + JSON.stringify(obj));
        obj.cantitate = obj.cantitate - 1;
        obj.rezervari = obj.rezervari + 1;
        ctx.response.body = obj;
        ctx.response.status = 200;
      } else {
        console.log("This book is not available anymore!");
        ctx.response.body = { text: 'This book is not available anymore!' };
        ctx.response.status = 404;
      }
    } else {
      console.log("Specified book does not exists!");
      ctx.response.body = { text: 'Specified product book not exists!' };
      ctx.response.status = 404;
    }
  } else {
    console.log("Missing or invalid id!");
    ctx.response.body = { text: 'Missing or invalid id!' };
    ctx.response.status = 404;
  }
});

router.post('/returneaza', ctx => {
  // console.log("ctx: " + JSON.stringify(ctx));
  const headers = ctx.request.body;
  // console.log("body: " + JSON.stringify(headers));
  const id = headers.id;
  if (typeof id !== 'undefined') {
    const obj = books.find(obj => obj.id == id);
    if (typeof obj !== 'undefined') {
      // console.log("found: " + JSON.stringify(obj));
      obj.cantitate = obj.cantitate + 1;
      ctx.response.body = obj;
      ctx.response.status = 200;
    } else {
      console.log("Specified book does not exists!");
      ctx.response.body = { text: 'Specified product book not exists!' };
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

server.listen(2016);
