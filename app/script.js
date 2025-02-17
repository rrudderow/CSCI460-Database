/* This is Front-End Code */
/* Code run in the browser */

function getData(tag) {
    fetch("/getData").then((response)=>{
      //fetch is a network delay - does file exist, can I get file
      response.json().then((obj)=>{
        obj.forEach((d)=>{
          tag.innerHTML+=`<tr><td>${d.id}</td><td>${d.first}</td><td>${d.last}</td><td>${d.salary}</td><td>`
        })
      })
    })
  }

  /*
async function getData() {
    //let dbData=[{id:2,first:"Bob",last:"Smith",salary:20000},
    //  {id:1,first:"Karl",last:"Castleton",salary:10000}
    //];
    const url = "/getData";
    let dbData={};
    let returnValue='';
    try {
      const response = await fetch(url);
      if (!response.ok) {
        throw new Error(`Response status: ${response.status}`);
      }
      const json = await response.text();
      console.log(json);
      dbData=JSON.parse(json);
      dbData.forEach((data)=>{
          returnValue+=`<tr><td>${data.id}</td><td>${data.first}</td><td>${data.last}</td><td>${data.salary}</td></tr>`;
        });
      return returnValue;
      } catch (error) {
      console.error(error.message);
    }
  }*/
  
  async function doLoad() {
      let tag=document.getElementById('salaryTable');
      if (tag) getData(tag)
  }
  
  window.addEventListener('load',doLoad);
  