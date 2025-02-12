// This is back end code - code run on the server
const express = require('express')
const path = require('path')
const app = express()
const port = 3000

app.get('/index.html', (req, res) => {
  const options = {
    //attributes: values - json notation
    root: path.join(__dirname)
  }
  res.sendFile('index.html',options)
  //console.log(req)
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
  console.log(`Running on website http://localhost:${port}/index.html`)
})
