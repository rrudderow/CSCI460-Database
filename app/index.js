const express = require('express')
const app = express()
const port = 3000

app.get('/', (req, res) => {
  res.send('\n<center><H1>Hello World!<H1></center>')
  console.log(req)
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
  console.log(`Running on website http://localhost:${port}/`)
})
