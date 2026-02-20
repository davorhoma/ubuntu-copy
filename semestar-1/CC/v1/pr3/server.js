const express = require("express");
const bodyParser = require("body-parser");

const app = express();

let userMessage = "Hello World!";

app.use(
  bodyParser.urlencoded({
    extended: false,
  })
);

app.use(express.static("public"));

app.get("/", (req, res) => {
  res.send(`
    <html>
      <head>
        <link rel="stylesheet" href="styles.css">
      </head>
      <body>
        <section>
          <h2>Message!</h2>
          <h3>${userMessage}</h3>
        </section>
        <form action="/store-message" method="POST">
          <div class="form-control">
            <label>Create new message</label>
            <input type="text" name="message">
          </div>
          <button>Set new message</button>
        </form>
      </body>
    </html>
  `);
});

app.post("/store-message", (req, res) => {
  const enteredMessage = req.body.message;
  console.log(enteredMessage);
  userMessage = enteredMessage;
  res.redirect("/");
});

app.listen(3001);
