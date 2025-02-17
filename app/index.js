// This is back end code - code run on the server
const express = require('express')
const path = require('path')
const app = express()
const port = 3000
const options = {
  //attributes: values - json notation
  root: path.join(__dirname)
}

const Pool = require('pg').Pool
const pool = new Pool({
  user: 'csci460', //don't do this in real life
  host: 'localhost',
  database: 'csci460',
  password: '206Rr153',
})

pool.query('SELECT id,first,last,salary FROM first1', (error, results) => {
  if(error) {
    throw error
  }
  console.log(results.rows)
})

app.get('/index.html', (req, res) => {
  res.sendFile('index.html',options)
  //console.log(req)
})

app.get('/styles.css',(req, res) => {
  res.sendFile('styles.css',options)
})

app.get('/script.js',(req, res) => {
  res.sendFile('script.js',options)
})

app.get('/getData',(req, res) => {
  res.send()
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
  console.log(`Running on website http://localhost:${port}/index.html`)
})
