/* This is Back-End Code */
/* This Code runs on the Server */

const express = require('express');
const path = require('path');
const app = express()
const { env } = require('node:process');
const port = 3000
const options = {
  root: path.join(__dirname)
};

const pg = require('pg')
const {Pool}=pg

const pool = new Pool({
  user: env.MYAPPUSER,  // Do this in real life
  host: 'localhost',
  database: env.MYAPPDB,
  password: env.MYAPPPASSWORD,
  port: 5432,
}) 

async function checkAPIKey(req){
  if (req.query.apikey){
    let cleanKey=parseInt(req.query.apikey);
    response=await pool.query(`select from activeusers where apikey=${cleanKey}`);
    return response.rowCount==1; 
  } else return false;
}

app.get('/index.html', (req, res) => {
  res.sendFile('index.html',options);
})
app.get('/styles.css', (req, res) => {
  res.sendFile('styles.css',options);
})
app.get('/script.js', (req, res) => {
  res.sendFile('script.js',options);
})

app.get('/delete',async (req,res)=>{
  if (! await checkAPIKey(req))
    res.send(`{"result":"badkey"}`);
  else {
    let cleanId=parseInt(req.query.id);
    pool.query(`delete from first1 where id=${cleanId}`,(error,result)=>{
      res.send('{"result":"ok"}');
    })
  }
})

app.get('/create',async (req,res)=>{
  if (! await checkAPIKey(req))
    res.send(`{"result":"badkey"}`);
  else {
    let salary=parseInt(req.query.salary);
    let first=req.query.first.replace(/[;:{}=]/g,"");
    let last=req.query.last.replace(/[;:{}=]/g,"");
    pool.query(`insert into first1 (first,last,salary) values ('${first}','${last}',${salary})`,(error,result)=>{
      res.send('{"result":"ok"}');
    })
  }
}) 

app.get('/update',async (req,res)=>{
  if (! await checkAPIKey(req))
    res.send(`{"result":"badkey"}`);
  else {
    let id=parseInt(req.query.id);
    let salary="";
    let comma="";
    if (req.query.salary) {
      salary=parseInt(req.query.salary);
      salary=`${comma}salary=${salary}`;
      comma=",";
    }
    let first="";
    if (req.query.first){
      first=req.query.first.replace(/[;:{}=]/g,"");
      first=`${comma}first='${first}'`;
      comma=",";
    }
    let last="";
    if (req.query.last){
      last=req.query.last.replace(/[;:{}=]/g,"");
      last=`${comma}last='${last}'`;
      comma=",";
    }
    pool.query(`update first1 set ${salary}${first}${last} where id=${id}`,(error,result)=>{
      console.log(result);
      res.send(`{"result":"ok"}`);
    })
  }
})
app.get('/getData',async (req, res) => {
  if (! await checkAPIKey(req))
    res.send(`[]`);
  else {
    pool.query('SELECT id,first,last,salary FROM first1', (error, results) => {
    if (error) throw error
    res.send(JSON.stringify(results.rows));
  })
  }
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
  console.log(`Running on website http://localhost:${port}/index.html`)
})