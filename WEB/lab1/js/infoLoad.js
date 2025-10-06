export function printUserInfo(){
    const name = document.getElementById("user");
    name.textContent = localStorage.getItem('tetris.username');
}

export function putRecords(){
    const records = JSON.parse(localStorage.getItem('records'));
    const listElement = document.getElementById("list_of_records");
    const sortedRecords = Object.fromEntries(Object.entries(records).sort((a, b) => b[1] - a[1]));
    listElement.innerHTML = '';
    for (let key in sortedRecords){
        listElement.innerHTML += `<li>${key}: ${sortedRecords[key]}</li>`;
    }
}

window.addEventListener('load', () => {
    printUserInfo();
    putRecords();
});