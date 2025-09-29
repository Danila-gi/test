export function printUserInfo(){
    const name = document.getElementById("user");
    name.textContent = localStorage.getItem('tetris.username');
}

export function putRecords(){
    const arrayRecords = JSON.parse(localStorage.getItem('records'));
    arrayRecords.sort((a, b) => b - a);
    const listElement = document.getElementById("list_of_records");
    listElement.innerHTML = '';
    for (let i = 0; i < arrayRecords.length; i++){
        listElement.innerHTML += `<li>${arrayRecords[i]}</li>`;
    }
}

window.addEventListener('load', () => {
    printUserInfo();
    putRecords();
});