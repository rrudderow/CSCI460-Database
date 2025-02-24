/* This is Front-End Code */
/* Code run in the browser */

function getData(tag) {
  fetch("/getData").then((response)=>{
    response.json().then((obj)=>{
      tag.innerHTML=''
        obj.forEach((d)=>{
          tag.innerHTML+=`<tr><td>${d.id}</td><td>${d.first}</td><td>${d.last}</td><td>${d.salary}</td></tr>`
      })
    })
  })
}

function serverDelete(x) {
  fetch(`/delete?id=${x}`).then((response)=>{
    response.json().then((obj)=>{
        doLoad()
    })
    })
  }

function doLoad() {
    let tag=document.getElementById('delete')
    if (tag) window.addEventListener('click',doDelete)
    tag=document.getElementById('salaryTable')
    if (tag) getData(tag)
}

function doDelete() {
  let tag=document.getElementById('accountID')
  if (tag) serverDelete(tag.value)
}

window.addEventListener('load',doLoad)
