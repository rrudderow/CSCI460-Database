// This is back end code - code run on the server
const express = require('express')
const path = require('path')
const app = express()
const port = 3000
const options = {
  //attributes: values - json notation
  root: path.join(__dirname)
}

const pg = require('pg')
const {Pool}=pg

//const Pool = require('pg').Pool
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

app.get('/delete', (req, res) => {
  console.log(req.query.id)
  pool.query(`delete from first1 where id=${req.query.id}`, (error, results) => {
    if (error) {
      throw error
    }
    res.send('{"result":"ok"}')
  })
})

app.get('/getData',(req, res) => {
  pool.query('SELECT id,first,last,salary FROM first1', (error, results) => {
    if(error) {
      throw error
    }
    //console.log(results.rows)
    res.send(JSON.stringify(results.rows))
  })
})

//let tag=document.getElementById('delete')
//if(tag) tag.addEventListener('click',doDelete)
//window.addEventListener('load',doLoad)

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
  console.log(`Running on website http://localhost:${port}/index.html`)
})
