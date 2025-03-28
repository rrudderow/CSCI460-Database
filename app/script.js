/* This is Front-End Code */
/* Code run in the browser */

var apikey=0;

function login() { 
  apikey=11301;
  doLoad(); 
}
function logout() {
  apikey=0;
  doLoad();
}

function getData(tag) {
  fetch(`/getData?apikey=${apikey}`).then((response)=>{
    response.json().then((obj)=>{
        tag.innerHTML='';
        obj.forEach((d)=>{
          tag.innerHTML+=`<tr><td>${d.id}</td><td>${d.first}</td><td>${d.last}</td><td>${d.salary}</td></tr>`;
      })
    })
  })
}

function serverDelete(x){
  fetch(`/delete?id=${x}&apikey=${apikey}`).then((response)=>{
    response.json().then((obj)=>{
      doLoad();
    })
  })
}
function serverCreate(first,last,salary){
  fetch(`/create?first=${first}&last=${last}&salary=${salary}&apikey=${apikey}`).then((response)=>{
    response.json().then((obj)=>{
      doLoad();
    })
  })
}
function serverUpdate(id,first,last,salary){
  if (first.length>0) first=`first=${first}&`;
  if (last.length>0) last=`last=${last}&`;
  if (salary.length>0) salary=`salary=${salary}&`;
  if (salary.length==0 && first.length==0 && last.length==0) return;
  fetch(`/update?${first}${last}${salary}id=${id}&apikey=${apikey}`).then((response)=>{
    response.json().then((obj)=>{
      doLoad();
    })
  })
}

function doLoad() {
    let tag=document.getElementById('delete');
    if (tag) tag.addEventListener('click',doDelete)
    tag=document.getElementById('create');
    if (tag) tag.addEventListener('click',doCreate)
    tag=document.getElementById('update');
    if (tag) tag.addEventListener('click',doUpdate)
    tag=document.getElementById('login');
    if (tag) tag.addEventListener('click',login)
    tag=document.getElementById('logout');
    if (tag) tag.addEventListener('click',logout)    
    tag=document.getElementById('salaryTable');
    if (tag) getData(tag);
}

function doDelete() {
  let tag=document.getElementById('accountId');
  if (tag) serverDelete(tag.value);
}

function doUpdate(){
  let id="";
  let first="";
  let last="";
  let salary="";
  let tag=document.getElementById('update_id');
  if (tag) id=tag.value;
  tag=document.getElementById('update_first');
  if (tag) first=tag.value;
  tag=document.getElementById('update_last');
  if (tag) last=tag.value;
  tag=document.getElementById('update_salary');
  if (tag) salary=tag.value;
  serverUpdate(id,first,last,salary);
}

function doCreate(){
  let first="";
  let last="";
  let salary="";
  let tag=document.getElementById('first');
  if (tag) first=tag.value;
  tag=document.getElementById('last');
  if (tag) last=tag.value;
  tag=document.getElementById('salary');
  if (tag) salary=tag.value;
  serverCreate(first,last,salary);
}


window.addEventListener('load',doLoad);
