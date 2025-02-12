const express = require('express')
const path = require('path')
const app = express()
const port = 3000

app.get('/', (req, res) => {
  const options = {
    root: path.join(__dirname)
  }
  res.sendFile('index.html',options)
  //console.log(req)
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
  console.log(`Running on website http://localhost:${port}/`)
})
